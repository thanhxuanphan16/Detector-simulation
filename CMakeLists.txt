cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(Scintillation_Detector)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include
                     ${Geant4_INCLUDE_DIR})

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

file(GLOB DATA_FILES
   "*.dat"
)

file(GLOB MACRO_FILES
     "*.mac"
)

file(COPY ${DATA_FILES} DESTINATION ${PROJECT_BINARY_DIR})
file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

add_executable(scin_det scin_det.cc ${sources} ${headers})

target_link_libraries(scin_det ${Geant4_LIBRARIES})

#add_custom_target(Scintillation_Detector DPENDS scin_det)
install(TARGETS scin_det DESTINATION bin)
