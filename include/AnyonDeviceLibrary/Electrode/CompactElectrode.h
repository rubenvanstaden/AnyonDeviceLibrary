/******************************************************************************
*** Copyright (c) 2020 by Anyon Systems Inc. All rights reserved.           ***
*** This computer program is a property of Anyon Systems Inc.               ***
*** and may contain confidential trade secrets.                             ***
*** Use, examination, copying, transfer and disclosure to others,           ***
*** in whole or in part, are prohibited except with the express prior       ***
*** written consent of Anyon Systems Inc.                                   ***
******************************************************************************/

#ifndef ANYON_DEVICE_LIBRARY_COMPACT_ELECTRODE_H
#define ANYON_DEVICE_LIBRARY_COMPACT_ELECTRODE_H

#include <AnyonLayoutGenerator/GDS/PCell.h>

namespace AnyonDeviceLibrary {
    namespace PCell {

        class CompactElectrode : public AnyonLayoutGenerator::GDS::PCell {
        public:

            struct Parameters {
                bool merge_bottom_electrodes = false;

                // double arm_length = 5;

                double bottom_contact_dx = 5;
                double bottom_contact_dy = 2;
                double top_contact_dx = 2;
                double top_contact_dy = 10;
                double junction_dx = 0.2;
                double junction_dy = 0.15;

                double tee_width = 0.3;
                double merge_width = -1;
                double top_arm_width = 1.5;
                double bridge_width = 0.275;
                double tee_termination_width = 0.15;
                double bottom_electrode_neck_width = 1.2;

                double contact_clearance = 0.3;
                double tee_length = 1.5;
                double tee_x_position = 2.0;
                double bottom_electrode_x_offset = 3;
                double bottom_electrode_neck_length = 3;
                double bridge_center_ratio = 0.33;
            };

            CompactElectrode(std::string name, const Parameters& params);

            const Parameters params;

        private:
            void createElements() override;
            void createPorts() override;

            // AnyonCAD::ShapeValuePtr getTopArmShape() const;
            AnyonCAD::ShapeValuePtr getBottomArmShape() const;

            AnyonCAD::ShapeValuePtr getTopRectangle() const;
            AnyonCAD::ShapeValuePtr getBottomArmsOutward() const;
            AnyonCAD::ShapeValuePtr getJunctionTeeConnectors() const;

            // TODO: Remove this. 
            AnyonCAD::Wire createWireFromVertices(std::vector<AnyonCAD::Vertex> pathVertices) const;

            AnyonCAD::Vertex top_port;
            AnyonCAD::Vertex bottom_port;
        };
    }
}

#endif
