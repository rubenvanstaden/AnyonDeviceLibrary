/******************************************************************************
*** Copyright (c) 2020 by Anyon Systems Inc. All rights reserved.           ***
*** This computer program is a property of Anyon Systems Inc.               ***
*** and may contain confidential trade secrets.                             ***
*** Use, examination, copying, transfer and disclosure to others,           ***
*** in whole or in part, are prohibited except with the express prior       ***
*** written consent of Anyon Systems Inc.                                   ***
******************************************************************************/

#include <iostream>

#include <AnyonLayoutGenerator/GDS/Library.h>

#include <AnyonDeviceLibrary/Via/Tsv.h>
#include <AnyonDeviceLibrary/Bandaid/TeeBandaid.h>
#include <AnyonDeviceLibrary/Bandaid/ThreeTierBandaid.h>
#include <AnyonDeviceLibrary/Bandaid/RectangularBandaid.h>
#include <AnyonDeviceLibrary/Junction/JunctionHook.h>
#include <AnyonDeviceLibrary/Electrode/LargeElectrode.h>
#include <AnyonDeviceLibrary/Electrode/CompactElectrode.h>

using namespace AnyonLayoutGenerator;
using namespace AnyonDeviceLibrary;

void tsvTest() {

    GDS::Library lib("Library");

    Via::Tsv::Parameters tsv_params;
    tsv_params.ground_number_via = 0;
    auto D0 = Via::Tsv("TsvDevice", tsv_params);

    lib.addCell<Via::Tsv>(D0);
    lib.outputGDSII("tsv.gds");
}

void teeBandaidTest() {

    GDS::Library lib("Library");

    PCell::TeeBandaid::Parameters tee_bandaid_params;
    auto D0 = PCell::TeeBandaid("TeeBandaid", tee_bandaid_params);

    lib.addCell<PCell::TeeBandaid>(D0);
    lib.outputGDSII("tee_bandaid.gds");
}

void threeTierBandaidTest() {

    GDS::Library lib("Library");

    PCell::ThreeTierBandaid::Parameters three_tier_bandaid_params;
    auto D0 = PCell::ThreeTierBandaid("ThreeTierBandaid", three_tier_bandaid_params);

    lib.addCell<PCell::ThreeTierBandaid>(D0);
    lib.outputGDSII("three_tier_bandaid.gds");
}

void rectangularBandaid() {

    GDS::Library lib("Library");

    PCell::RectangularBandaid::Parameters rectangular_bandaid_params;
    auto D0 = PCell::RectangularBandaid("RectangularBandaid", rectangular_bandaid_params);

    lib.addCell<PCell::RectangularBandaid>(D0);
    lib.outputGDSII("rectangular_bandaid.gds");
}

void junctionHookTest() {

    GDS::Library lib("Library");

    PCell::JunctionHook::Parameters junction_hook_params;
    auto D0 = PCell::JunctionHook("JunctionHook", junction_hook_params);

    lib.addCell<PCell::JunctionHook>(D0);
    lib.outputGDSII("junction_hook.gds");
}

void largeElectrodeTest() {

    GDS::Library lib("Library");

    PCell::LargeElectrode::Parameters large_electrode_params;
    auto D0 = PCell::LargeElectrode("LargeElectrode", large_electrode_params);

    lib.addCell<PCell::LargeElectrode>(D0);
    lib.outputGDSII("large_electrode.gds");
}

void compactElectrodeTest() {

    GDS::Library lib("Library");

    PCell::CompactElectrode::Parameters compact_electrode_params;
    auto D0 = PCell::CompactElectrode("CompactElectrode", compact_electrode_params);

    lib.addCell<PCell::CompactElectrode>(D0);
    lib.outputGDSII("compact_electrode.gds");
}

int main() {

    std::cout << "\nStart program..." << std::endl;

    // tsvTest();
    // teeBandaidTest();
    // threeTierBandaidTest();
    // rectangularBandaid();
    // junctionHookTest();
    // largeElectrodeTest();
    compactElectrodeTest();

    std::cout << "End program...\n" << std::endl;
}
