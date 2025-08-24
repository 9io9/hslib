cmake_minimum_required(VERSION 3.25.1)

project(hslib VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/include/ec.h 
    COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/tools/pec/pec.py ${CMAKE_CURRENT_SOURCE_DIR}/.ec ${CMAKE_CURRENT_SOURCE_DIR}/include/ec.h _LJW_HSLIB_EC_H_
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/.ec ${CMAKE_CURRENT_SOURCE_DIR}/tools/pec/pec.py
    COMMENT "convert .ec to error code header file"
)

add_custom_target(hslgech DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/ec.h)

add_library(hslib STATIC src/hst.c src/strh.c)
add_dependencies(hslib hslgech)

target_include_directories(hslib PRIVATE include lib)

set_target_properties(hslib PROPERTIES EXPORT_NAME hslib)

install(
    TARGETS hslib
    EXPORT hslibTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
install(DIRECTORY include DESTINATION .)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    hslibConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_file(hslibConfig.cmake.in hslibConfig.cmake @ONLY)

install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/hslibConfig.cmake" "${CMAKE_CURRENT_BINARY_DIR}/hslibConfigVersion.cmake"
    DESTINATION lib/cmake/hslib
)
install(
    EXPORT hslibTargets
    FILE hslibTargets.cmake
    NAMESPACE hslib::
    DESTINATION lib/cmake/hslib
)


enable_testing()
add_subdirectory(test)