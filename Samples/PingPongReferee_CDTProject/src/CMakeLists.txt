# Generated 2017-08-14 14:55:43

cmake_minimum_required(VERSION 2.8.7)
set(TARGET Debug__TopMain)
project(${TARGET})

# require location of supporting RTS
if (NOT UMLRTS_ROOT)
  if (DEFINED ENV{UMLRTS_ROOT})
    set(UMLRTS_ROOT $ENV{UMLRTS_ROOT})
  else ()
    set(UMLRTS_ROOT /home/osboxes/.p2/pool/plugins/org.eclipse.papyrusrt.rts_0.9.0.201706080437/umlrts)
  endif ()
endif ()

# setup primary envars - provides tooling config
include(${UMLRTS_ROOT}/build/buildenv.cmake)

# model sources
set(SRCS Debug__TopMain.cc PingPongProtocol.cc Pinger.cc Ponger.cc ExtInterface.cc StartProtocol.cc Referee.cc endProtocol.cc Top.cc GateWay.cc Debug__Top.cc Debug__TopControllers.cc )

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

