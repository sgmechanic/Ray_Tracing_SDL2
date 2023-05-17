cmake_minimum_required(VERSION 3.26)

project(LIGHTS)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
#aux_source_directory(. SRC_LIST)

set(LIGHTS_SRC Application.cpp Box.cpp Camera.cpp Figure.cpp GeometricTransforms.cpp Img.cpp LightBase.cpp LinAlgMatrix.cpp LinAlgVector.cpp main.cpp MaterialBase.cpp Plane.cpp PointLight.cpp Pyramid.cpp Ray.cpp scene.cpp SimpleMaterial.cpp Sphere.cpp Triangle.cpp)
set(LIGHTS_HDR Box.h Calc.h Camera.h Factory.h FactoryBox.h FactoryPyramid.h FactorySphere.h Figure.h GeometricTransforms.h Header.h Img.h Include.h LightBase.h LinAlgMatrix.h LinAlgVector.h MaterialBase.h Plane.h PointLight.h Pyramid.h Ray.h scene.h SimpleMaterial.h Sphere.h Triangle.h)
#target_link_libraries(main.cpp ${PROJECT_NAME} SDL2)
#add_executable(${PROJECT_NAME} ${SRC_LIST})
add_executable(${PROJECT_NAME} ${LIGHTS_SRC} ${LIGHTS_HDR})

target_link_libraries(${PROJECT_NAME} SDL2::SDL2 SDL2::SDL2main)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#Cmake
