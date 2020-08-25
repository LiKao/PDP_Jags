cmake_minimum_required(VERSION 3.13)
project(pdp_jags VERSION 0.0.1 DESCRIPTION "PDP functions for JAGS" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})

find_package(JAGS REQUIRED)
find_package(Eigen3 3.3 REQUIRED)

include_directories(${JAGS_INCLUDE_DIRS})
include_directories(src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_SHARED_LINKER_FLAGS "")

ADD_LIBRARY(Pdp SHARED "")
target_link_libraries(Pdp Eigen3::Eigen)
add_subdirectory(src)
add_subdirectory(examples)
set_target_properties(Pdp PROPERTIES PREFIX "")


INSTALL(
	TARGETS Pdp 
	DESTINATION ${JAGS_MODULE_DIR}
)