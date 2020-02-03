cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

add_subdirectory(Squid)
add_subdirectory(Junction)
add_subdirectory(Bandaid)
add_subdirectory(Electrode)
add_subdirectory(Via)
add_subdirectory(Qubit)

anyon_add_library(${PROJECT_NAME}
    $<TARGET_OBJECTS:SquidLibrary>
    $<TARGET_OBJECTS:JunctionLibrary>
    $<TARGET_OBJECTS:BandaidLibrary>
    $<TARGET_OBJECTS:ElectrodeLibrary>
    $<TARGET_OBJECTS:ViaLibrary>
    $<TARGET_OBJECTS:QubitLibrary>
)

anyon_target_link_libraries(${PROJECT_NAME} PUBLIC AnyonLayoutGenerator)

anyon_add_executable(run_devices main_components.cpp)
anyon_target_link_libraries(run_devices ${PROJECT_NAME})
