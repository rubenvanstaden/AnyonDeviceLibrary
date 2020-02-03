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

#include <AnyonDeviceLibrary/Junction/JunctionHook.h>

using namespace AnyonDeviceLibrary::PCell;

JunctionHook::JunctionHook(std::string name, const JunctionHook::Parameters &params) : PCell(name), params(params) {
    createElements();
    createPorts();
    moveToOrigin();
}

void JunctionHook::createElements() {

    auto layer_1 = AnyonLayoutGenerator::GDS::Layer(1, 0);

    auto signal_shape = this->getHookShape();

    auto p0 = AnyonLayoutGenerator::GDS::Polygon(signal_shape, layer_1);

    this->addElement<AnyonLayoutGenerator::GDS::Polygon>(p0);
}

void JunctionHook::createPorts() {
}

AnyonCAD::ShapeValuePtr JunctionHook::getHookShape() const {
    AnyonCAD::Vertex v0({-params.min_width/2, 0,0});
    AnyonCAD::Vertex v1({v0.toPoint()[0], v0.toPoint()[1]+params.neck_length, 0});
    AnyonCAD::Vertex v2({-params.max_width/2, v1.toPoint()[1], 0});
    AnyonCAD::Vertex v3({v2.toPoint()[0], params.total_length, 0});
    AnyonCAD::Vertex v4({0, params.total_length, 0});
    AnyonCAD::Vertex v5({0,0,0});

    std::vector<AnyonCAD::Vertex> pathVertices({v0, v1, v2, v3, v4});
    std::vector<AnyonCAD::Edge> edgeVector;

    for (size_t i_vertex = 0; i_vertex < pathVertices.size()-1; i_vertex++){
        edgeVector.emplace_back(pathVertices[i_vertex], pathVertices[i_vertex+1]);
    }

    AnyonCAD::Wire path(edgeVector);
    // FIXME: WTF. Who uses initializer_list here.
    double r_filet = std::min(std::initializer_list<double>({1.0,0.49*(params.total_length-params.neck_length),0.99*params.neck_length,(params.max_width-params.min_width)/4.1}));
    path=AnyonCAD::fillet(path,r_filet);
    path.add(AnyonCAD::Edge(v4,v5));
    path.add(AnyonCAD::Edge(v5,v0));
    AnyonCAD::Face hook(path);

    // FIXME: Do we really need this?
    // if (params.orientation==Orientation::down) {
    //     hook = AnyonCAD::transform(hook,AnyonCAD::reflection({0.,1.,0.}));
    // }

    return AnyonCAD::createShapeValuePtr(hook);
}
