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

#include <AnyonDeviceLibrary/Electrode/LargeElectrode.h>

using namespace AnyonDeviceLibrary::PCell;

LargeElectrode::LargeElectrode(std::string name, const LargeElectrode::Parameters &params) : PCell(name), params(params) {
    createElements();
    createPorts();
    moveToOrigin();
}

void LargeElectrode::createElements() {

    auto layer_1 = AnyonLayoutGenerator::GDS::Layer(1, 0);

    AnyonCAD::ShapeValuePtr top_rectangle = getTopArm();
    AnyonCAD::ShapeValuePtr tees = getJunctionTeeConnector();
    // return AnyonCAD::fuse(*top_rectangle,*tees,true); 

    auto p0 = AnyonLayoutGenerator::GDS::Polygon(top_rectangle, layer_1);
    auto p1 = AnyonLayoutGenerator::GDS::Polygon(tees, layer_1);

    this->addElement<AnyonLayoutGenerator::GDS::Polygon>(p0);
    this->addElement<AnyonLayoutGenerator::GDS::Polygon>(p1);
}

void LargeElectrode::createPorts() {

}

AnyonCAD::ShapeValuePtr LargeElectrode::getTopArm() const {

    AnyonCAD::Vertex v0({params.contact_dx/2.,0.+params.contact_dy-params.overlap_length,0});
    AnyonCAD::Vertex v1(v0.toPoint()+AnyonMath::Vector<double,3>{0,-params.contact_dy,0});
    AnyonCAD::Vertex v2(v1.toPoint()+AnyonMath::Vector<double,3>{-params.contact_dx/2.+params.junction_dx/2.,-params.arm_dy*(1-params.neck_percentage)+params.overlap_length,0});
    AnyonCAD::Vertex v3(v2.toPoint()+AnyonMath::Vector<double,3>{0.,-params.arm_dy*params.neck_percentage,0});
    AnyonCAD::Vertex v0_r({-v0.toPoint()[0],v0.toPoint()[1],0.});
    AnyonCAD::Vertex v1_r({-v1.toPoint()[0],v1.toPoint()[1],0.});
    AnyonCAD::Vertex v2_r({-v2.toPoint()[0],v2.toPoint()[1],0.});
    AnyonCAD::Vertex v3_r({-v3.toPoint()[0],v3.toPoint()[1],0.});

    std::vector<AnyonCAD::Vertex> pathVertices={v3,v2,v1,v0,v0_r,v1_r,v2_r,v3_r};
    std::vector<AnyonCAD::Edge> edgeVector;
    for (size_t i_vertex=0;i_vertex<pathVertices.size()-1;i_vertex++){
        edgeVector.emplace_back(pathVertices[i_vertex],pathVertices[i_vertex+1]);
    }

    AnyonCAD::Wire path(edgeVector);
    double r_filet=std::min(std::initializer_list<double>({1.5,params.contact_dx/2.,params.contact_dy/2.}));
    path=AnyonCAD::fillet(path,r_filet);
    path.add(AnyonCAD::Edge(v3_r,v3));
    AnyonCAD::Face contactPad(path);
    // contactPad=AnyonCAD::transform(contactPad,AnyonCAD::translation(top_port.toPoint()));
    return createShapeValuePtr(contactPad);
}

AnyonCAD::ShapeValuePtr LargeElectrode::getJunctionTeeConnector() const {
    double y_top=-params.arm_dy;
    AnyonCAD::Face verticalRectangle({{params.junction_dx/2., y_top, 0.},{params.junction_dx/2., y_top-params.tee_length, 0.},
                                      {-params.junction_dx/2., y_top-params.tee_length, 0.},{-params.junction_dx/2., y_top, 0.}});
    double y1=-params.arm_dy-params.tee_length;
    AnyonCAD::Face horizontalRectangle({{params.tee_width/2., y1, 0.},{params.tee_width/2., y1-params.tee_top_length, 0.},
                                        {-params.tee_width/2., y1-params.tee_top_length, 0.},{-params.tee_width/2., y1, 0.}});
    return AnyonCAD::fuse(verticalRectangle, horizontalRectangle, true);
    // AnyonCAD::ShapeValuePtr tee=AnyonCAD::fuse(verticalRectangle,horizontalRectangle,true);
    // return AnyonCAD::transform(*tee, AnyonCAD::translation(top_port.toPoint()));
}

AnyonCAD::ShapeValuePtr LargeElectrode::getBottomElectrode() const {

    AnyonCAD::Vertex v0({-params.contact_dx/2.,-params.contact_dy+params.overlap_length,0.});
    AnyonCAD::Vertex v1(v0.toPoint()+AnyonMath::Vector<double,3>{0.,params.contact_dy,0.});
    AnyonCAD::Vertex v2(v1.toPoint()+AnyonMath::Vector<double,3>{params.contact_dx/2.-params.tee_width/2.,params.arm_dy*(1-params.neck_percentage)-params.overlap_length,0.});
    AnyonCAD::Vertex v3(v2.toPoint()+AnyonMath::Vector<double,3>{0.,params.arm_dy*params.neck_percentage-params.junction_dy,0.});

    AnyonCAD::Vertex v0_r({-v0.toPoint()[0],v0.toPoint()[1],0.});
    AnyonCAD::Vertex v1_r({-v1.toPoint()[0],v1.toPoint()[1],0.});
    AnyonCAD::Vertex v2_r({-v2.toPoint()[0],v2.toPoint()[1],0.});
    AnyonCAD::Vertex v3_r({-v3.toPoint()[0],v3.toPoint()[1],0.});


    std::vector<AnyonCAD::Vertex> pathVertices={v3,v2,v1,v0,v0_r,v1_r,v2_r,v3_r};
    std::vector<AnyonCAD::Edge> edgeVector;
    for (size_t i_vertex=0;i_vertex<pathVertices.size()-1;i_vertex++){
        edgeVector.emplace_back(pathVertices[i_vertex],pathVertices[i_vertex+1]);
    }
    AnyonCAD::Wire path(edgeVector);
    double r_filet=std::min(std::initializer_list<double>({1.5,params.contact_dx/2.,params.contact_dy/2.}));
    path=AnyonCAD::fillet(path,r_filet);
    path.add(AnyonCAD::Edge(v3,v3_r));
    AnyonCAD::Face contactPad(path);

    // double dx=(top_port.toPoint()[0]-bottom_port.toPoint()[0])+params.arm_dx/2.+params.tee_width;
    double dx = 0.5*params.arm_dx + params.tee_width;
    AnyonCAD::Vertex v4({v3.toPoint()[0]+dx, v3.toPoint()[1], 0});
    AnyonCAD::Vertex v5({v4.toPoint()[0], v4.toPoint()[1]+params.junction_dy, 0});
    AnyonCAD::Vertex v6({v5.toPoint()[0]-dx, v5.toPoint()[1], 0});
    AnyonCAD::ShapeValuePtr result = AnyonCAD::fuse(contactPad, AnyonCAD::Face({v4,v5,v6,v3}), true);

    return result;

    // return AnyonCAD::transform(*result, AnyonCAD::translation({bottom_port.toPoint()}));
}
