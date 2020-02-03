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

#include <AnyonDeviceLibrary/Electrode/CompactElectrode.h>

using namespace AnyonDeviceLibrary::PCell;

CompactElectrode::CompactElectrode(std::string name, const CompactElectrode::Parameters &params) : PCell(name), params(params) {

    // bridge_center = AnyonCAD::Vertex{topPort.toPoint()[0], params.bridge_center_ratio*(topPort.toPoint()[1])+(1-params.bridge_center_ratio)*(bottomPort.toPoint()[1]), 0};

    top_port = {0,0,5};
    bottom_port = {0,0,0};

    createElements();
    createPorts();
    moveToOrigin();
}

void CompactElectrode::createElements() {

    auto layer_1 = AnyonLayoutGenerator::GDS::Layer(1, 0);

    auto top_rectangle = this->getTopRectangle();
    // auto tees = this->getJunctionTeeConnectors();
    // auto bot_arm_shape = this->getBottomArmShape();

    auto p0 = AnyonLayoutGenerator::GDS::Polygon(top_rectangle, layer_1);
    // auto p1 = AnyonLayoutGenerator::GDS::Polygon(tees, layer_1);
    // auto p2 = AnyonLayoutGenerator::GDS::Polygon(bot_arm_shape, layer_1);

    this->addElement<AnyonLayoutGenerator::GDS::Polygon>(p0);
    // this->addElement<AnyonLayoutGenerator::GDS::Polygon>(p1);
    // this->addElement<AnyonLayoutGenerator::GDS::Polygon>(p2);
}

void CompactElectrode::createPorts() {

}

// AnyonCAD::ShapeValuePtr CompactElectrode::getTopArmShape() const {
//     AnyonCAD::ShapeValuePtr topRectangle = getTopRectangle();
//     AnyonCAD::ShapeValuePtr tees = getJunctionTeeConnectors();
//     return AnyonCAD::fuse(*topRectangle, *tees, true);
// }

AnyonCAD::ShapeValuePtr CompactElectrode::getTopRectangle() const {
    double arm_length = top_port.toPoint()[1]-0.5*params.bridge_width-params.tee_length-params.contact_clearance;
    // double y_tee = -params.contact_clearance-arm_length-params.tee_length+params.tee_termination_width;

    AnyonCAD::Vertex v0({-params.tee_x_position-params.junction_dx/2, -params.contact_clearance-arm_length-params.tee_length, 0});
    AnyonCAD::Vertex v1({v0.toPoint()[0], v0.toPoint()[1]+params.tee_length, 0});
    AnyonCAD::Vertex v2({v1.toPoint()[0]-params.top_arm_width/2+params.junction_dx/2, -params.contact_clearance, 0});
    AnyonCAD::Vertex v3({-params.top_contact_dx/2-params.contact_clearance, v2.toPoint()[1], 0});
    AnyonCAD::Vertex v4({v3.toPoint()[0], v3.toPoint()[1]+params.top_contact_dy, 0});
    AnyonCAD::Vertex v5({0, v4.toPoint()[1], 0});
    AnyonCAD::Vertex v6({0, -params.contact_clearance, 0});
    AnyonCAD::Vertex v7({v2.toPoint()[0]+params.top_arm_width, v6.toPoint()[1], 0});
    AnyonCAD::Vertex v8({v1.toPoint()[0]+params.junction_dx, v1.toPoint()[1], 0});
    AnyonCAD::Vertex v9({v0.toPoint()[0]+params.junction_dx, v0.toPoint()[1], 0});
    
    AnyonCAD::Wire topWire = createWireFromVertices({v0, v1, v2, v3, v4, v5, v6, v7, v8, v9});

    // AnyonCAD::Wire topWire = createWireFromVertices({v0, v1, v2, v3, v4, v5, v6});
    // AnyonCAD::Wire bottomWire = createWireFromVertices({v6, v7, v8, v9});
    // // double r_filet = std::min(0.25, 0.5*(params.top_contact_dx/2-params.tee_x_position-params.top_arm_width/2));
    // // std::cout << r_filet << std::endl;
    // // topWire = AnyonCAD::fillet(topWire, r_filet);
    // // bottomWire = AnyonCAD::fillet(bottomWire, r_filet);
    // bottomWire.add(AnyonCAD::Edge(v9, v0));

    // std::vector<AnyonCAD::Edge> edgesToAdd = bottomWire.getSortedEdges();
    // for (size_t i_edge = 0; i_edge < edgesToAdd.size(); i_edge++){
    //     topWire.add(edgesToAdd[i_edge]);
    // }

    return AnyonCAD::createShapeValuePtr(AnyonCAD::Face(topWire));

    // return AnyonCAD::createShapeValuePtr(AnyonCAD::transform(AnyonCAD::Face(topWire), AnyonCAD::translation({top_port.toPoint()})));
}

AnyonCAD::ShapeValuePtr CompactElectrode::getJunctionTeeConnectors() const {
    // double x0 = params.tee_x_position;
    // double y_tee = -params.contact_clearance-params.arm_length-params.tee_length+params.tee_termination_width;
    // double y1 = y_tee;
    // AnyonCAD::Face tee({{-x0+0.5*params.tee_width, y1, 0},
    //                     {-x0+0.5*params.tee_width, y1-params.tee_termination_width, 0},
    //                     {-x0-0.5*params.tee_width, y1-params.tee_termination_width, 0},
    //                     {-x0-0.5*params.tee_width, y1, 0}});
    // return AnyonCAD::createShapeValuePtr(AnyonCAD::transform(tee, AnyonCAD::translation(top_port.toPoint())));
}

AnyonCAD::ShapeValuePtr CompactElectrode::getBottomArmShape() const {
    // AnyonCAD::Vertex v0({bottom_port.toPoint()[0]-params.bottom_electrode_x_offset+params.contact_clearance, bottom_port.toPoint()[1]-params.bottom_contact_dy, 0});
    // AnyonCAD::Vertex v1(v0.toPoint()+AnyonMath::Vector<double,3>{-params.bottom_contact_dx, 0, 0});
    // AnyonCAD::Vertex v2({v1.toPoint()[0], -0.5*params.bridge_width, 0});
    // AnyonCAD::Vertex v3({top_port.toPoint()[0]-params.tee_x_position+params.tee_width/2.+params.contact_clearance, v2.toPoint()[1], 0});
    // AnyonCAD::Vertex v4({v3.toPoint()[0], v3.toPoint()[1]-params.junction_dy, 0});
    // AnyonCAD::Vertex v5({v2.toPoint()[0]+params.bottom_electrode_neck_width, v4.toPoint()[1], 0});
    // AnyonCAD::Vertex v6({v5.toPoint()[0], v5.toPoint()[1]-params.bottom_electrode_neck_length, 0});
    // AnyonCAD::Vertex v7({v0.toPoint()[0], v6.toPoint()[1], 0});

    // AnyonCAD::Wire leftWire = createWireFromVertices({v6, v7, v0, v1, v2, v3});
    // double r_filet = std::min(0.75,0.5*(params.bottom_contact_dx));
    // leftWire = AnyonCAD::fillet(leftWire, r_filet);
    // leftWire.add(AnyonCAD::Edge(v3, v4));
    // leftWire.add(AnyonCAD::Edge(v4, v5));
    // leftWire.add(AnyonCAD::Edge(v5, v6));

    // AnyonCAD::Face leftArm(leftWire);

    // return AnyonCAD::createShapeValuePtr(leftArm);
}

AnyonCAD::ShapeValuePtr CompactElectrode::getBottomArmsOutward() const {

    // AnyonCAD::Vertex v0({bottom_port.toPoint()[0]-params.bottom_electrode_x_offset+params.contact_clearance,
    //                      bridge_center.toPoint()[1]-params.bridge_width/2.-params.junction_dy-params.bottom_contact_dy-params.bottom_electrode_neck_length,0.});
    // AnyonCAD::Vertex v1({v0.toPoint()[0]-params.bottom_contact_dx,v0.toPoint()[1],0.});
    // AnyonCAD::Vertex v2({v1.toPoint()[0],v1.toPoint()[1]+params.bottom_contact_dy,0.});
    // AnyonCAD::Vertex v3({v0.toPoint()[0]-params.bottom_electrode_neck_width,v2.toPoint()[1],0.});
    // AnyonCAD::Vertex v4({v3.toPoint()[0],bridge_center.toPoint()[1]-params.bridge_width/2.,0.});
    // AnyonCAD::Vertex v5({top_port.toPoint()[0]-params.tee_x_position+params.tee_width/2.+params.contact_clearance,v4.toPoint()[1],0.});
    // AnyonCAD::Vertex v6({v5.toPoint()[0],v5.toPoint()[1]-params.junction_dy,0.});
    // AnyonCAD::Vertex v7({v0.toPoint()[0],v6.toPoint()[1],0.});

    // AnyonCAD::Wire leftWire;

    // if (params.merge_bottom_electrodes){
    //     AnyonCAD::Vertex v8({v0.toPoint()[0],v0.toPoint()[1]+params.merge_width,0.});
    //     AnyonCAD::Vertex v9({bottom_port.toPoint()[0],v8.toPoint()[1],0.});
    //     AnyonCAD::Vertex v10({bottom_port.toPoint()[0],v0.toPoint()[1],0.});

    //     double r_filet=std::min(0.75,0.5*params.merge_width);
    //     leftWire=createWireFromVertices({v10,v1,v2,v3,v4});
    //     leftWire=AnyonCAD::fillet(leftWire,r_filet);
    //     leftWire.add(AnyonCAD::Edge(v4,v5));
    //     leftWire.add(AnyonCAD::Edge(v5,v6));
    //     leftWire.add(AnyonCAD::Edge(v6,v7));
    //     leftWire.add(AnyonCAD::Edge(v7,v8));
    //     leftWire.add(AnyonCAD::Edge(v8,v9));
    //     leftWire.add(AnyonCAD::Edge(v9,v10));
    // }
    // else{
    //     double r_filet=std::min(0.75,0.5*(params.bottom_contact_dx));
    //     leftWire=createWireFromVertices({v7,v0,v1,v2,v3,v4});
    //     leftWire=AnyonCAD::fillet(leftWire,r_filet);
    //     leftWire.add(AnyonCAD::Edge(v4,v5));
    //     leftWire.add(AnyonCAD::Edge(v5,v6));
    //     leftWire.add(AnyonCAD::Edge(v6,v7));
    // };

    // AnyonCAD::Face leftArm(leftWire);
    // return AnyonCAD::createShapeValuePtr(leftArm);
}

AnyonCAD::Wire CompactElectrode::createWireFromVertices(std::vector<AnyonCAD::Vertex> pathVertices) const {
    std::vector<AnyonCAD::Edge> edgeVector;
    for (size_t i_vertex = 0; i_vertex<pathVertices.size()-1; i_vertex++){
        edgeVector.emplace_back(pathVertices[i_vertex], pathVertices[i_vertex+1]);
    }
    return AnyonCAD::Wire(edgeVector);
}
