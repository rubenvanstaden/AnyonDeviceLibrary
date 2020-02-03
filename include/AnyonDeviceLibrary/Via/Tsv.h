/******************************************************************************
*** Copyright (c) 2020 by Anyon Systems Inc. All rights reserved.           ***
*** This computer program is a property of Anyon Systems Inc.               ***
*** and may contain confidential trade secrets.                             ***
*** Use, examination, copying, transfer and disclosure to others,           ***
*** in whole or in part, are prohibited except with the express prior       ***
*** written consent of Anyon Systems Inc.                                   ***
******************************************************************************/

#ifndef ANYON_LIBRARY_TSV_CELL_H
#define ANYON_LIBRARY_TSV_CELL_H

#include <AnyonCAD/Similarity.h>

#include <AnyonChipDesigner/QChip/ThroughSiliconVia.h>

#include <AnyonLayoutGenerator/GDS/Via.h>

namespace AnyonDeviceLibrary {
    namespace Via {

        class Tsv : public AnyonLayoutGenerator::GDS::Via {
        public:

            struct Parameters {
                AnyonChipDesigner::ThroughSiliconVia::TSVInfo tsv_info;

                size_t ground_number_via = 8;
                bool shouldIncludeBlankVia = false;

                double gap_width = 40;
                double signal_width = 20;
                double opening_percentage = 0.5;
                double signal_via_diameter = 200.0;
                double ground_via_diameter = 200.0;
                double ground_via_arc_radius = 500.0;
                double outer_ring_radius = 0.7*500.0;
                double wafer_thickness = 500.0;
            };

            Tsv(std::string name, const Parameters& params);

            double getSignalWidth() noexcept {
                return params.signal_width;
            };

            double getGapWidth() noexcept {
                return params.gap_width;
            };

            const Parameters params;

        private:
            void createElements() override;
            void createPorts() override;

            AnyonCAD::ShapeValuePtr getSignalViaShape() const;
            AnyonCAD::ShapeValuePtr getGroundViaShape() const;
            AnyonCAD::ShapeValuePtr getPadShape(const double portWidth, const double ringRadius) const;
        };
    }
}

#endif
