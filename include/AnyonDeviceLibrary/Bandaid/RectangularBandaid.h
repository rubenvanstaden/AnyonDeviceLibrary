/******************************************************************************
*** Copyright (c) 2020 by Anyon Systems Inc. All rights reserved.           ***
*** This computer program is a property of Anyon Systems Inc.               ***
*** and may contain confidential trade secrets.                             ***
*** Use, examination, copying, transfer and disclosure to others,           ***
*** in whole or in part, are prohibited except with the express prior       ***
*** written consent of Anyon Systems Inc.                                   ***
******************************************************************************/

#ifndef ANYON_DEVICE_LIBRARY_RECTANGULAR_BANDAID_H
#define ANYON_DEVICE_LIBRARY_RECTANGULAR_BANDAID_H

#include <AnyonLayoutGenerator/GDS/PCell.h>

namespace AnyonDeviceLibrary {
    namespace PCell {

        class RectangularBandaid : public AnyonLayoutGenerator::GDS::PCell {
        public:

            struct Parameters {
                double width = 6;
                double height = 10;
                double edge_clearance = 1;
            };

            RectangularBandaid(std::string name, const Parameters& params);

            const Parameters params;

        private:
            void createElements() override;
            void createPorts() override;

            AnyonCAD::ShapeValuePtr getRectangularBandaidShape() const;
        };
    }
}

#endif
