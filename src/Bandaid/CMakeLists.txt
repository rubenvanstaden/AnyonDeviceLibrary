cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

anyon_add_library(BandaidLibrary OBJECT
    Bandaid.cpp
    TeeBandaid.cpp
    ThreeTierBandaid.cpp
    RectangularBandaid.cpp
)
