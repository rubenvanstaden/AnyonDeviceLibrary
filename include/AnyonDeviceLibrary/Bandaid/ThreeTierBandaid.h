/******************************************************************************
*** Copyright (c) 2020 by Anyon Systems Inc. All rights reserved.           ***
*** This computer program is a property of Anyon Systems Inc.               ***
*** and may contain confidential trade secrets.                             ***
*** Use, examination, copying, transfer and disclosure to others,           ***
*** in whole or in part, are prohibited except with the express prior       ***
*** written consent of Anyon Systems Inc.                                   ***
******************************************************************************/

#ifndef ANYON_DEVICE_LIBRARY_THREE_TIER_BANDAID_H
#define ANYON_DEVICE_LIBRARY_THREE_TIER_BANDAID_H

#include <AnyonLayoutGenerator/GDS/PCell.h>

namespace AnyonDeviceLibrary {
    namespace PCell {

        class ThreeTierBandaid : public AnyonLayoutGenerator::GDS::PCell {
        public:

            struct Parameters {
                double bottom_width = 25;
                double mid_width = 15;
                double top_width = 5;
                double bottom_length = 15;
                double mid_length = 11;
                double top_length = 4;
            };

            ThreeTierBandaid(std::string name, const Parameters& params);

            const Parameters params;

        private:
            void createElements() override;
            void createPorts() override;

            AnyonCAD::ShapeValuePtr getThreeTierBandaidShape() const;
        };
    }
}

#endif
