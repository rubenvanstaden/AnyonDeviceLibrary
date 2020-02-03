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

#include <AnyonDeviceLibrary/Bandaid/ThreeTierBandaid.h>

using namespace AnyonDeviceLibrary::PCell;

ThreeTierBandaid::ThreeTierBandaid(std::string name, const ThreeTierBandaid::Parameters &params) : PCell(name), params(params) {
    createElements();
    createPorts();
    moveToOrigin();
}

void ThreeTierBandaid::createElements() {

    auto layer_1 = AnyonLayoutGenerator::GDS::Layer(1, 0);

    auto signal_shape = this->getThreeTierBandaidShape();

    auto p0 = AnyonLayoutGenerator::GDS::Polygon(signal_shape, layer_1);

    this->addElement<AnyonLayoutGenerator::GDS::Polygon>(p0);
}

void ThreeTierBandaid::createPorts() {
    // auto p1 = AnyonLayoutGenerator::GDS::ElectricalPort({-params.ground_via_arc_radius, 0, 0}, 180);
    // auto p2 = AnyonLayoutGenerator::GDS::ElectricalPort({params.ground_via_arc_radius, 0, 0}, 0);
    // this->addPort<AnyonLayoutGenerator::GDS::ElectricalPort>(p1);
    // this->addPort<AnyonLayoutGenerator::GDS::ElectricalPort>(p2);
}

AnyonCAD::ShapeValuePtr ThreeTierBandaid::getThreeTierBandaidShape() const {

    AnyonCAD::Vertex v0({-params.top_width/2.,0.,0});
    AnyonCAD::Vertex v1(v0.toPoint()+AnyonMath::Vector<double,3>{0.,-params.top_length,0.});
    AnyonCAD::Vertex v2({-params.mid_width/2.,v1.toPoint()[1]-params.top_width/2.,0});
    AnyonCAD::Vertex v3(v2.toPoint()+AnyonMath::Vector<double,3>{0.,-params.mid_length,0.});
    AnyonCAD::Vertex v4({-params.bottom_width/2.,v3.toPoint()[1],0.});
    AnyonCAD::Vertex v5({v4.toPoint()[0],v4.toPoint()[1]-params.bottom_length,0.});
    AnyonCAD::Vertex v5_r({-v5.toPoint()[0],v5.toPoint()[1],0.});
    AnyonCAD::Vertex v4_r({-v4.toPoint()[0],v4.toPoint()[1],0.});
    AnyonCAD::Vertex v3_r({-v3.toPoint()[0],v3.toPoint()[1],0.});
    AnyonCAD::Vertex v2_r({-v2.toPoint()[0],v2.toPoint()[1],0.});
    AnyonCAD::Vertex v1_r({-v1.toPoint()[0],v1.toPoint()[1],0.});
    AnyonCAD::Vertex v0_r({-v0.toPoint()[0],v0.toPoint()[1],0.});

    AnyonCAD::Face band_aid({v0,v1,v2,v3,v4,v5,v5_r,v4_r,v3_r,v2_r,v1_r,v0_r});

    return AnyonCAD::createShapeValuePtr(band_aid);
}
