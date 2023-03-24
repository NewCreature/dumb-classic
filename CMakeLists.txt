cmake_minimum_required(VERSION 3.1)
project(libdumb-classic C)
include(GNUInstallDirs)
include(CheckCCompilerFlag)

# Bump major (== soversion) on API breakages
set(DUMB_VERSION_MAJOR 0)
set(DUMB_VERSION_MINOR 9.3)
set(DUMB_VERSION ${DUMB_VERSION_MAJOR}.${DUMB_VERSION_MINOR})

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake-scripts)

option(BUILD_ALLEGRO_4 "Build Allegro 4 support" ON)
option(USE_SSE "Use SSE instructions" ON)

function(check_and_add_c_compiler_flag flag flag_variable_to_add_to)
    string(TOUPPER "${flag}" check_name)
    string(MAKE_C_IDENTIFIER "CC_HAS${check_name}" check_name)
    check_c_compiler_flag("${flag}" "${check_name}")
    if(${check_name})
        set(${flag_variable_to_add_to} "${flag} ${${flag_variable_to_add_to}}" PARENT_SCOPE)
    endif()
endfunction()

check_and_add_c_compiler_flag("-Wno-unused-variable" CMAKE_C_FLAGS)
check_and_add_c_compiler_flag("-Wno-unused-but-set-variable" CMAKE_C_FLAGS)
check_and_add_c_compiler_flag("-Wall" CMAKE_C_FLAGS)
add_definitions("-D_FILE_OFFSET_BITS=64")
add_definitions("-DDUMB_DECLARE_DEPRECATED")

set(CMAKE_C_FLAGS_DEBUG "-DDEBUGMODE=1 -D_DEBUG")
check_and_add_c_compiler_flag("-ggdb" CMAKE_C_FLAGS_DEBUG)
check_and_add_c_compiler_flag("-Zi" CMAKE_C_FLAGS_DEBUG)

set(CMAKE_C_FLAGS_RELEASE "-ffast-math -O2 -DNDEBUG")

set(CMAKE_C_FLAGS_RELWITHDEBINFO "-ffast-math -O2 -DNDEBUG")
check_and_add_c_compiler_flag("-g" CMAKE_C_FLAGS_RELWITHDEBINFO)
check_and_add_c_compiler_flag("-Zi" CMAKE_C_FLAGS_RELWITHDEBINFO)

set(CMAKE_C_FLAGS_MINSIZEREL "-ffast-math -Os -DNDEBUG")

if(USE_SSE)
    check_c_compiler_flag("-msse" "CC_HAS_MSSE")
    if(CC_HAS_MSSE)
        message(STATUS "Compiling with SSE support")
        set(CMAKE_C_FLAGS "-msse ${CMAKE_C_FLAGS}")
        add_definitions("-D_USE_SSE")
    else()
        message(STATUS "Compiling without SSE support")
    endif()
endif()

link_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(include/)

if(BUILD_ALLEGRO_4)
    find_path(ALLEGRO_4_INCLUDE_PATH allegro.h)
    find_library(ALLEGRO_4_LIBRARY liballeg.a)
else()
    message(STATUS "Not building Allegro 4 support")
endif()

SET(SOURCES
    src/core/unload.c
    src/core/rendsig.c
    src/core/rendduh.c
    src/core/register.c
    src/core/readduh.c
    src/core/rawsig.c
    src/core/makeduh.c
    src/core/loadduh.c
    src/core/dumbfile.c
    src/core/duhtag.c
    src/core/duhlen.c
    src/core/atexit.c
    src/helpers/stdfile.c
    src/helpers/silence.c
    src/helpers/sampbuf.c
    src/helpers/resample.c
    src/helpers/memfile.c
    src/helpers/clickrem.c
    src/it/xmeffect.c
    src/it/readxm2.c
    src/it/readxm.c
    src/it/reads3m2.c
    src/it/reads3m.c
    src/it/readmod2.c
    src/it/readmod.c
    src/it/loadxm2.c
    src/it/loadxm.c
    src/it/loads3m2.c
    src/it/loads3m.c
    src/it/loadmod2.c
    src/it/loadmod.c
    src/it/itunload.c
    src/it/itrender.c
    src/it/itread2.c
    src/it/itread.c
    src/it/itorder.c
    src/it/itmisc.c
    src/it/itload2.c
    src/it/itload.c
)

set(INSTALL_HEADERS
    include/dumb-classic.h
)

set(ALLEGRO_SOURCES
    src/allegro/alplay.c
    src/allegro/datitq.c
    src/allegro/dats3m.c
    src/allegro/datxm.c
    src/allegro/datduh.c
    src/allegro/datmod.c
    src/allegro/dats3mq.c
    src/allegro/datxmq.c
    src/allegro/datit.c
    src/allegro/datmodq.c
    src/allegro/datunld.c
    src/allegro/packfile.c
)


set(PKG_CONFIG_FILE "${CMAKE_CURRENT_BINARY_DIR}/dumb-classic.pc")

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/pkg-config.pc.in"
    ${PKG_CONFIG_FILE}
    @ONLY
)

add_library(dumb-classic ${SOURCES})
set_target_properties(dumb-classic PROPERTIES DEBUG_POSTFIX d)
set_target_properties(dumb-classic PROPERTIES VERSION ${DUMB_VERSION})
set_target_properties(dumb-classic PROPERTIES SOVERSION ${DUMB_VERSION_MAJOR})

if(BUILD_ALLEGRO_4)
    add_library(aldmb-classic ${ALLEGRO_SOURCES})
    set_target_properties(aldmb-classic PROPERTIES DEBUG_POSTFIX d)
    set_target_properties(aldmb-classic PROPERTIES VERSION ${DUMB_VERSION})
    set_target_properties(aldmb-classic PROPERTIES SOVERSION ${DUMB_VERSION_MAJOR})
    list(APPEND DUMB_TARGETS aldmb-classic)
    list(APPEND INSTALL_HEADERS include/aldumb-classic.h)
    target_include_directories(aldmb-classic PUBLIC ${ALLEGRO_4_INCLUDE_PATH})
    target_link_libraries(aldmb-classic ${ALLEGRO_LIBRARIES} dumb-classic)
endif()

# Make sure the dylib install name path is set on OSX so you can include dumb-classic in app bundles
IF(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set_target_properties(dumb-classic PROPERTIES INSTALL_NAME_DIR ${CMAKE_INSTALL_FULL_LIBDIR})
ENDIF(CMAKE_SYSTEM_NAME STREQUAL "Darwin")

target_link_libraries(dumb-classic m)

install(FILES ${PKG_CONFIG_FILE} DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
install(FILES ${INSTALL_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS dumb-classic ${DUMB_TARGETS}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
