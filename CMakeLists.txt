cmake_minimum_required(VERSION 3.13)
project(pdp_jags VERSION 0.0.1 DESCRIPTION "PDP functions for JAGS" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})

find_package(JAGS REQUIRED)

include_directories(${JAGS_INCLUDE_DIRS})
include_directories(src)

ADD_LIBRARY(Pdp SHARED "")
add_subdirectory(src)
set_target_properties(Pdp PROPERTIES PREFIX "")


INSTALL(
	TARGETS Pdp 
	DESTINATION ${JAGS_MODULE_DIR}
)