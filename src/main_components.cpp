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

// void airbridgeTest() {

//     GDS::Library lib("Library");

//     TwelveQubit::Airbridge::Info airbridge_info;
//     auto D0 = TwelveQubit::Airbridge("AirbridgeCell", airbridge_info);

//     lib.addCell<TwelveQubit::Airbridge>(D0);
//     lib.outputGDSII("airbridge.gds");
// }

// void clawTest() {

//     GDS::Library lib("Library");

//     TwelveQubit::Claw::Info claw_info;
//     auto D0 = TwelveQubit::Claw("ClawCell", claw_info);

//     lib.addCell<TwelveQubit::Claw>(D0);
//     lib.outputGDSII("claw.gds");
// }

// void couplerIslandTest() {

//     GDS::Library lib("Library");

//     TwelveQubit::CouplerIsland::Info coupler_island_info;
//     auto D0 = TwelveQubit::CouplerIsland("CouplerCell", coupler_island_info);

//     lib.addCell<TwelveQubit::CouplerIsland>(D0);
//     lib.outputGDSII("coupler_island.gds");
// }

int main() {

    std::cout << "\nStart program..." << std::endl;

    tsvTest();
    // airbridgeTest();
    // clawTest();
    // couplerIslandTest();

    std::cout << "End program...\n" << std::endl;
}
