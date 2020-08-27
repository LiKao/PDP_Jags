add_executable(test2 test2.cpp)
target_link_libraries(test2 Eigen3::Eigen)

target_sources(test PRIVATE test.cpp)