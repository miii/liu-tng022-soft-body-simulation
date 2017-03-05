cmake_minimum_required(VERSION 3.6)


SET(APP_NAME softbody)
project(${APP_NAME})

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)



set(SOURCE_FILES
src/main.cpp src/Cube.cpp src/Cube.h src/Mass.cpp src/Mass.h src/Functions.cpp src/Functions.h)

add_executable(${APP_NAME} ${SOURCE_FILES} src/Cube.cpp src/Cube.h)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

if (WIN32)
    find_package(GLFW REQUIRED)
    SET(GLFW_INCLUDE_DIRS ${GLFW_INCLUDE_DIR})
    SET(GLFW_STATIC_LIBRARIES ${OPENGL_LIBRARY} ${GLFW_LIBRARIES})
    set(GLM_PATH "default value" CACHE PATH "GLM Path")
    include_directories(${GLM_PATH})
else()
    #If not WIN32 we use PkgConfig to find GLFW
    find_package(PkgConfig REQUIRED)
    pkg_search_module(GLFW REQUIRED glfw3)
    # use c++11
    SET(CMAKE_CXX_FLAGS "-std=c++11")
endif()

# OSX-specific requirements
if(APPLE)
    # use c++11
    SET(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
    set(CMAKE_OSX_ARCHITECTURES "x86_64")
    target_link_libraries(${APP_NAME} "-framework OpenGL")

    if(CMAKE_GENERATOR STREQUAL Xcode)
        find_library(COCOA_LIBRARY Cocoa REQUIRED)
        find_library(IOKIT_LIBRARY IOKit REQUIRED)
        find_library(COREVIDEO_LIBRARY CoreVideo REQUIRED)
        find_library(CARBON_LIBRARY Carbon REQUIRED)

        set(LIBS
                ${OPENGL_LIBRARY}
                ${COCOA_LIBRARY}
                ${IOKIT_LIBRARY}
                ${COREVIDEO_LIBRARY}
                ${CARBON_LIBRARY}
                )

        set(CMAKE_OSX_DEPLOYMENT_TARGET “10.9”)
    endif()
endif()

include_directories(${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${APP_NAME} ${GLEW_LIBRARIES} ${GLFW_STATIC_LIBRARIES} ${LIBS})