# Copyright 2018 Yi-Soo An <yisooan@gmail.com>
#
#  Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 2.8.7)
project(libgls2 C)

include(webOS/webOS)
webos_modules_init(1 0 0)
webos_component(0 1 0)

include(FindPkgConfig)

include_directories(include/public)

add_definitions(-DGLS2_COMPILATION)
add_definitions(-D_GNU_SOURCE)

webos_add_compiler_flags(ALL
                        -std=c99
                        -Wall -Werror -Wextra)
                        
pkg_check_modules(GLIB2 REQUIRED glib-2.0)
pkg_check_modules(GOBJECT2 REQUIRED gobject-2.0)
pkg_check_modules(LUNASERVICE2 REQUIRED luna-service2)
pkg_check_modules(PMLOGLIB REQUIRED PmLogLib)

include_directories(${GLIB2_INCLUDE_DIRS}
                    ${LUNASERVICE2_INCLUDE_DIRS}
                    ${PMLOGLIB_INCLUDE_DIRS})

link_directories(${GLIB2_LIBRARY_DIRS}
                 ${GOBJECT2_LIBRARY_DIRS}
                 ${LUNASERVICE2_LIBRARY_DIRS}
                 ${PMLOGLIB_LIBRARY_DIRS})

webos_add_compiler_flags(ALL ${GLIB2_CFLAGS_OTHER}
                             ${LUNASERVICE2_CFLAGS_OTHER}
                             ${PMLOGLIB_CFLAGS_OTHER})

SET(LIBS
    ${GLIB2_LIBRARIES}
    ${GOBJECT2_LIBRARIES}
    ${LUNASERVICE2_LIBRARIES}
    ${PMLOGLIB_LIBRARIES}
    dl
    pthread
)

SET(LIBS_LDFLAGS
    ${GLIB2_LDFLAGS_OTHER}
    ${GOBJECT2_LDFLAGS_OTHER}
    ${LUNASERVICE2_LDFLAGS_OTHER}
    ${PMLOGLIB_LDFLAGS_OTHER}
)

webos_include_install_paths()

file(GLOB SOURCES src/*.c)
list(FILTER SOURCES EXCLUDE REGEX ".*gls2-boxed-types.c$")

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBS})
webos_add_linker_options(ALL ${LIBS_LDFLAGS})

webos_build_pkgconfig(files/pkgconfig/${CMAKE_PROJECT_NAME})

# Documentation
if(GLS2_BUILD_DOC)
    webos_config_build_doxygen(doc Doxyfile)
else()
    message(STATUS "libgls2: skip building documentation")
endif()

webos_build_library(NAME ${PROJECT_NAME})
