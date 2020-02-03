cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

anyon_add_library(ElectrodeLibrary OBJECT
    Electrode.cpp
    CompactElectrode.cpp
    LargeElectrode.cpp
)
