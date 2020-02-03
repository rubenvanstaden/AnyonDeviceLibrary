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

#include <AnyonDeviceLibrary/Bandaid/RectangularBandaid.h>

using namespace AnyonDeviceLibrary::PCell;

RectangularBandaid::RectangularBandaid(std::string name, const RectangularBandaid::Parameters &params) : PCell(name), params(params) {
    createElements();
    createPorts();
    moveToOrigin();
}

void RectangularBandaid::createElements() {

    auto layer_1 = AnyonLayoutGenerator::GDS::Layer(1, 0);

    auto signal_shape = this->getRectangularBandaidShape();

    auto p0 = AnyonLayoutGenerator::GDS::Polygon(signal_shape, layer_1);

    this->addElement<AnyonLayoutGenerator::GDS::Polygon>(p0);
}

void RectangularBandaid::createPorts() {
    // auto p1 = AnyonLayoutGenerator::GDS::ElectricalPort({-params.ground_via_arc_radius, 0, 0}, 180);
    // auto p2 = AnyonLayoutGenerator::GDS::ElectricalPort({params.ground_via_arc_radius, 0, 0}, 0);
    // this->addPort<AnyonLayoutGenerator::GDS::ElectricalPort>(p1);
    // this->addPort<AnyonLayoutGenerator::GDS::ElectricalPort>(p2);
}

AnyonCAD::ShapeValuePtr RectangularBandaid::getRectangularBandaidShape() const {
    AnyonCAD::Face rectangle({{-params.width/2, -params.height/2, 0},
                              {+params.width/2, -params.height/2, 0},
                              {+params.width/2, +params.height/2, 0},
                              {-params.width/2, +params.height/2, 0}});
    return AnyonCAD::createShapeValuePtr(rectangle);
}
