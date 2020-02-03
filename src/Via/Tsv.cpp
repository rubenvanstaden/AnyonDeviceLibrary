/******************************************************************************
*** Copyright (c) 2020 by Anyon Systems Inc. All rights reserved.           ***
*** This computer program is a property of Anyon Systems Inc.               ***
*** and may contain confidential trade secrets.                             ***
*** Use, examination, copying, transfer and disclosure to others,           ***
*** in whole or in part, are prohibited except with the express prior       ***
*** written consent of Anyon Systems Inc.                                   ***
******************************************************************************/

#include <AnyonLayoutGenerator/GDS/Polygon.h>
#include <AnyonLayoutGenerator/GDS/Layer.h>

#include <AnyonCAD/Shape/Compound.h>

#include <AnyonDeviceLibrary/Via/Tsv.h>

using namespace AnyonDeviceLibrary::Via;

Tsv::Tsv(std::string name, const Tsv::Parameters &params) : Via(name), params(params) {
    createElements();
    createPorts();
    moveToOrigin();
}

void Tsv::createElements() {

    auto layer_1 = AnyonLayoutGenerator::GDS::Layer(1, 0);
    auto layer_2 = AnyonLayoutGenerator::GDS::Layer(2, 0);
    auto layer_3 = AnyonLayoutGenerator::GDS::Layer(3, 0);

    auto signal_shape = this->getSignalViaShape();
    auto ground_shape = this->getGroundViaShape();

    AnyonCAD::ShapeValuePtr signal = getPadShape(params.signal_width, 0.5*params.signal_via_diameter);
    AnyonCAD::ShapeValuePtr gap = getPadShape(params.gap_width, params.outer_ring_radius);
    auto pad_shape = AnyonCAD::subtract(*gap, *signal);

    auto p0 = AnyonLayoutGenerator::GDS::Polygon(signal_shape, layer_3);
    auto p1 = AnyonLayoutGenerator::GDS::Polygon(ground_shape, layer_3);
    auto p2 = AnyonLayoutGenerator::GDS::Polygon(pad_shape, layer_1);
    auto p3 = AnyonLayoutGenerator::GDS::Polygon(pad_shape, layer_2);
    p3.rotate(180, {0,0,0});

    this->addElement<AnyonLayoutGenerator::GDS::Polygon>(p0);
    this->addElement<AnyonLayoutGenerator::GDS::Polygon>(p1);
    this->addElement<AnyonLayoutGenerator::GDS::Polygon>(p2);
    this->addElement<AnyonLayoutGenerator::GDS::Polygon>(p3);
}

void Tsv::createPorts() {
    auto p1 = AnyonLayoutGenerator::GDS::ElectricalPort({-params.ground_via_arc_radius, 0, 0}, 180);
    auto p2 = AnyonLayoutGenerator::GDS::ElectricalPort({params.ground_via_arc_radius, 0, 0}, 0);
    this->addPort<AnyonLayoutGenerator::GDS::ElectricalPort>(p1);
    this->addPort<AnyonLayoutGenerator::GDS::ElectricalPort>(p2);
}

AnyonCAD::ShapeValuePtr Tsv::getSignalViaShape() const {
    AnyonCAD::Solid shape = AnyonCAD::createCylinder(params.signal_via_diameter/2.0, params.wafer_thickness);
    AnyonCAD::Similarity t = AnyonCAD::translation(AnyonMath::Vector<double,3>{0, 0, -params.wafer_thickness});
    shape.applyTransformation(t);
    return AnyonCAD::createShapeValuePtr(shape);
}

AnyonCAD::ShapeValuePtr Tsv::getGroundViaShape() const {
    AnyonCAD::Compound result;
    for (size_t iv = 0; iv < params.ground_number_via; iv++) {
        double theta = 2*M_PI/(params.ground_number_via+1) * (iv+1);
        AnyonCAD::Solid shape = AnyonCAD::createCylinder(params.ground_via_diameter/2.0, params.wafer_thickness);
        AnyonCAD::Similarity t0 = AnyonCAD::translation({params.ground_via_arc_radius*cos(theta), params.ground_via_arc_radius*sin(theta),0.0});
        shape.applyTransformation(t0);
        AnyonCAD::Similarity t1 = AnyonCAD::translation(AnyonMath::Vector<double,3>{0, 0, -params.wafer_thickness});
        shape.applyTransformation(t1);
        result.add(shape);
    }
    return AnyonCAD::createShapeValuePtr(result);
}

AnyonCAD::ShapeValuePtr Tsv::getPadShape(const double portWidth, const double ringRadius) const {

    auto origin = AnyonCAD::Vertex({0, 0, 0});

    auto port = AnyonCAD::Vertex({params.ground_via_arc_radius, 0, 0});

    using Vec3D = AnyonMath::Vector<double, 3>;
    Vec3D axis{origin.toPoint() - port.toPoint()};
    double padLength = AnyonMath::twoNorm(axis);
    axis = AnyonMath::normalize(axis);
    Vec3D transverse = {axis[1], -axis[0], axis[2]};
    double omega = 0.1;

    AnyonCAD::Vertex v_1{port.toPoint()+portWidth*transverse};
    AnyonCAD::Vertex v_2{v_1.toPoint()+omega*padLength*axis};
    AnyonCAD::Vertex v_3{v_2.toPoint()+(params.opening_percentage-omega)*padLength*axis+(ringRadius-portWidth)*transverse};
    AnyonCAD::Vertex v_4{v_3.toPoint()+(1.-params.opening_percentage)*padLength*axis};

    auto createStraightWire=[](const std::vector<AnyonCAD::Vertex> vertices) {
        std::vector<AnyonCAD::Edge> edge;
        for (size_t iv = 0; iv < vertices.size()-1; iv++) {
            edge.emplace_back(vertices[iv], vertices[iv+1]);
        }
        return AnyonCAD::Wire(edge);
    };

    std::vector<AnyonCAD::Vertex> v = {v_1, v_2, v_3, v_4};
    AnyonCAD::Wire w = fillet(createStraightWire(v),0.1*padLength);
    AnyonCAD::Vertex v_5{origin.toPoint()+ringRadius*axis};
    AnyonCAD::Vertex v_6{origin.toPoint()-ringRadius*transverse};
    AnyonCAD::Edge arc_1 = AnyonCAD::createArc(origin, v_4, v_5);
    AnyonCAD::Edge arc_2 = AnyonCAD::createArc(origin, v_5, v_6);

    std::vector<AnyonCAD::Edge> allEdges = AnyonCAD::extract<AnyonCAD::Edge>(w).collect();

    for (auto&& e: AnyonCAD::extract<AnyonCAD::Edge>(arc_1).collect()) {
        allEdges.push_back(e);
    }

    for (auto&& e: AnyonCAD::extract<AnyonCAD::Edge>(arc_2).collect()) {
        allEdges.push_back(e);
    }

    AnyonCAD::Vertex v_1r{port.toPoint()-portWidth*transverse};
    AnyonCAD::Vertex v_2r{v_1r.toPoint()+omega*padLength*axis};
    AnyonCAD::Vertex v_3r{v_2r.toPoint()+(params.opening_percentage-omega)*padLength*axis-(ringRadius-portWidth)*transverse};

    AnyonCAD::Wire reflectedWire = fillet(createStraightWire({v_6, v_3r, v_2r, v_1r}), 0.1*padLength);
    for (auto&& e : AnyonCAD::extract<AnyonCAD::Edge>(reflectedWire).collect()) {
        allEdges.push_back(e);
    }
    allEdges.push_back(AnyonCAD::Edge(v_1r, v_1));
    AnyonCAD::Wire result(allEdges);
    return AnyonCAD::createShapeValuePtr(AnyonCAD::Face{result});
}