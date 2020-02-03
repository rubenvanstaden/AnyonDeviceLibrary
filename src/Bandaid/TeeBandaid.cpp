/******************************************************************************
*** Copyright (c) 2020 by Anyon Systems Inc. All rights reserved.           ***
*** This computer program is a property of Anyon Systems Inc.               ***
*** and may contain confidential trade secrets.                             ***
*** Use, examination, copying, transfer and disclosure to others,           ***
*** in whole or in part, are prohibited except with the express prior       ***
*** written consent of Anyon Systems Inc.                                   ***
******************************************************************************/

#include <AnyonCAD/Shape/Compound.h>

#include <AnyonLayoutGenerator/GDS/Layer.h>
#include <AnyonLayoutGenerator/GDS/Polygon.h>

#include <AnyonDeviceLibrary/Bandaid/TeeBandaid.h>

using namespace AnyonDeviceLibrary::PCell;

TeeBandaid::TeeBandaid(std::string name, const TeeBandaid::Parameters &params) : PCell(name), params(params) {
    createElements();
    createPorts();
    moveToOrigin();
}

void TeeBandaid::createElements() {

    auto layer_1 = AnyonLayoutGenerator::GDS::Layer(1, 0);
    auto layer_2 = AnyonLayoutGenerator::GDS::Layer(2, 0);
    auto layer_3 = AnyonLayoutGenerator::GDS::Layer(3, 0);

    auto signal_shape = this->getTeeBandAidShape();

    auto p0 = AnyonLayoutGenerator::GDS::Polygon(signal_shape, layer_3);

    this->addElement<AnyonLayoutGenerator::GDS::Polygon>(p0);
}

void TeeBandaid::createPorts() {
    // auto p1 = AnyonLayoutGenerator::GDS::ElectricalPort({-params.ground_via_arc_radius, 0, 0}, 180);
    // auto p2 = AnyonLayoutGenerator::GDS::ElectricalPort({params.ground_via_arc_radius, 0, 0}, 0);
    // this->addPort<AnyonLayoutGenerator::GDS::ElectricalPort>(p1);
    // this->addPort<AnyonLayoutGenerator::GDS::ElectricalPort>(p2);
}

AnyonCAD::ShapeValuePtr TeeBandaid::getTeeBandAidShape() const {
    AnyonCAD::Vertex v0({params.center_width/2, 0, 0});
    AnyonCAD::Vertex v1({v0.toPoint()[0], v0.toPoint()[1]+params.total_height-params.tee_top_height, 0});
    AnyonCAD::Vertex v2({v1.toPoint()[0]+(params.total_width-params.center_width)/2, v1.toPoint()[1], 0});
    AnyonCAD::Vertex v3({v2.toPoint()[0], v2.toPoint()[1]+params.tee_top_height, 0});
    AnyonCAD::Vertex v4(reflectVertex(v3));
    AnyonCAD::Vertex v5(reflectVertex(v2));
    AnyonCAD::Vertex v6(reflectVertex(v1));
    AnyonCAD::Vertex v7(reflectVertex(v0));
    AnyonCAD::Face band_aid({v0,v1,v2,v3,v4,v5,v6,v7});
    return AnyonCAD::createShapeValuePtr(band_aid);
}

AnyonCAD::Vertex TeeBandaid::reflectVertex(const AnyonCAD::Vertex &vertex) const {
    return AnyonCAD::Vertex({-vertex.toPoint()[0], vertex.toPoint()[1], 0});
}
