cmake_minimum_required(VERSION 3.9)
project(cpp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(LIBRARY_OUTPUT_PATH build/)
set(BINARY_OUTPUT_PATH build/)

include(External_GTest.cmake)

set(GILDED_ROSE_SOURCE_FILES
    GildedRose.cc
    GildedRose.h
    GildedRoseUnitTests.cc)

set(GILDED_ROSE_TEXT_TESTS_SOURCE_FILES
    GildedRose.cc
    GildedRose.h
    GildedRoseTextTests.cc)

set(SOURCE_FILES
    ${GILDED_ROSE_SOURCE_FILES}
    ${GILDED_ROSE_TEXT_TESTS_SOURCE_FILES})



add_executable(GildedRose ${GILDED_ROSE_SOURCE_FILES})
target_link_libraries(GildedRose ${GTEST_MAIN_LIBRARY}
                              ${GTEST_LIBRARY}
                              ${GMOCK_MAIN_LIBRARY}
                              ${GMOCK_LIBRARY}
                              ${GTEST_BOTH_LIBRARIES})

add_executable(GildedRoseTextTests ${GILDED_ROSE_TEXT_TESTS_SOURCE_FILES})
target_link_libraries(GildedRoseTextTests ${GTEST_BOTH_LIBRARIES}
                                          ${GTEST_MAIN_LIBRARY}
                                          ${GTEST_LIBRARY}
                                          ${GMOCK_MAIN_LIBRARY}
                                          ${GMOCK_LIBRARY})
