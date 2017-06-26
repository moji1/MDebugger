# Generated 2017-02-13 19:43:49

cmake_minimum_required(VERSION 2.8.7)
set(TARGET Parcer_RouterMain)
project(${TARGET})

# require location of supporting RTS
if (NOT UMLRTS_ROOT)
  if (DEFINED ENV{UMLRTS_ROOT})
    set(UMLRTS_ROOT $ENV{UMLRTS_ROOT})
  else ()
    set(UMLRTS_ROOT /Users/mojtababagherzadeh/.p2/pool/plugins/org.eclipse.papyrusrt.rts_0.8.0.201611081307/umlrts)
  endif ()
endif ()

# setup primary envars - provides tooling config
include(${UMLRTS_ROOT}/build/buildenv.cmake)

# model sources
set(SRCS Parcer_RouterMain.cc Parcel.cc transmission.cc Gen.cc Stage.cc Bin.cc Chute.cc Switcher.cc detection.cc Sensor.cc switchProtocol.cc Parcer_Router.cc Parcer_RouterControllers.cc )

# specify target
add_executable(${TARGET} ${SRCS})

# setup lib dependency support after defining TARGET
include(${UMLRTS_ROOT}/build/rtslib.cmake)

# compiler parameters
set_target_properties(${TARGET} PROPERTIES COMPILE_OPTIONS "${COPTS}")
set_target_properties(${TARGET} PROPERTIES COMPILE_DEFINITIONS "${CDEFS}")
include_directories(${INCS})

# linker parameters
set_target_properties(${TARGET} PROPERTIES CMAKE_EXE_LINKER_FLAGS "${LOPTS}")
target_link_libraries(${TARGET} ${LIBS})

