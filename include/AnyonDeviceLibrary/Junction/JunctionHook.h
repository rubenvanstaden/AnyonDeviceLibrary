/******************************************************************************
*** Copyright (c) 2020 by Anyon Systems Inc. All rights reserved.           ***
*** This computer program is a property of Anyon Systems Inc.               ***
*** and may contain confidential trade secrets.                             ***
*** Use, examination, copying, transfer and disclosure to others,           ***
*** in whole or in part, are prohibited except with the express prior       ***
*** written consent of Anyon Systems Inc.                                   ***
******************************************************************************/

#ifndef ANYON_DEVICE_LIBRARY_JUNCTION_HOOK_H
#define ANYON_DEVICE_LIBRARY_JUNCTION_HOOK_H

#include <AnyonLayoutGenerator/GDS/PCell.h>

namespace AnyonDeviceLibrary {
    namespace PCell {

        class JunctionHook : public AnyonLayoutGenerator::GDS::PCell {
        public:

            struct Parameters {
                double max_width = 6;
                double min_width = 2.5;
                double neck_length = 2;
                double total_length = 5;
                double box_width = 4.25;
                double box_height = 7;
            };

            JunctionHook(std::string name, const Parameters& params);

            const Parameters params;

        private:
            void createElements() override;
            void createPorts() override;

            AnyonCAD::ShapeValuePtr getHookShape() const;
        };
    }
}

#endif
