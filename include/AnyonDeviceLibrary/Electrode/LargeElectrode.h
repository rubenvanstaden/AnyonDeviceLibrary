/******************************************************************************
*** Copyright (c) 2020 by Anyon Systems Inc. All rights reserved.           ***
*** This computer program is a property of Anyon Systems Inc.               ***
*** and may contain confidential trade secrets.                             ***
*** Use, examination, copying, transfer and disclosure to others,           ***
*** in whole or in part, are prohibited except with the express prior       ***
*** written consent of Anyon Systems Inc.                                   ***
******************************************************************************/

#ifndef ANYON_DEVICE_LIBRARY_LARGE_ELECTRODE_H
#define ANYON_DEVICE_LIBRARY_LARGE_ELECTRODE_H

#include <AnyonLayoutGenerator/GDS/PCell.h>

namespace AnyonDeviceLibrary {
    namespace PCell {

        class LargeElectrode : public AnyonLayoutGenerator::GDS::PCell {
        public:

            struct Parameters {
                double arm_dx = 1;
                double arm_dy = 10;
                double contact_dx = 2;
                double contact_dy = 2;
                double tee_width = 0.3;
                double tee_length = 0.5;
                double junction_dx = 0.2;
                double junction_dy = 0.15;
                double bridge_width = 0.2;
                double overlap_length = 5.0;
                double tee_top_length = 0.15;
                double neck_percentage = 0.2;
            };

            LargeElectrode(std::string name, const Parameters& params);

            const Parameters params;

        private:
            void createElements() override;
            void createPorts() override;

            AnyonCAD::ShapeValuePtr getTopArm() const;
            AnyonCAD::ShapeValuePtr getBottomElectrode() const;
            AnyonCAD::ShapeValuePtr getJunctionTeeConnector() const;
        };
    }
}

#endif
