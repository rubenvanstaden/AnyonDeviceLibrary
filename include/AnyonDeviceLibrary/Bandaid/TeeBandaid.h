/******************************************************************************
*** Copyright (c) 2020 by Anyon Systems Inc. All rights reserved.           ***
*** This computer program is a property of Anyon Systems Inc.               ***
*** and may contain confidential trade secrets.                             ***
*** Use, examination, copying, transfer and disclosure to others,           ***
*** in whole or in part, are prohibited except with the express prior       ***
*** written consent of Anyon Systems Inc.                                   ***
******************************************************************************/

#ifndef ANYON_DEVICE_LIBRARY_TEE_BANDAID_H
#define ANYON_DEVICE_LIBRARY_TEE_BANDAID_H

#include <AnyonCAD/Similarity.h>

#include <AnyonChipDesigner/QChip/ThroughSiliconVia.h>

#include <AnyonLayoutGenerator/GDS/PCell.h>

namespace AnyonDeviceLibrary {
    namespace PCell {

        class TeeBandaid : public AnyonLayoutGenerator::GDS::PCell {
        public:

            struct Parameters {
                double center_width = 6;
                double total_width = 10;
                double tee_top_height = 3;
                double total_height = 10;
                double orientation_in_degrees = 0;
            };

            TeeBandaid(std::string name, const Parameters& params);

            const Parameters params;

        private:
            void createElements() override;
            void createPorts() override;

            AnyonCAD::ShapeValuePtr getTeeBandAidShape() const;
            AnyonCAD::Vertex reflectVertex(const AnyonCAD::Vertex &vertex) const;
        };
    }
}

#endif
