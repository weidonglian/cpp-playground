project(boost)

set(BOOST_SOURCE ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(CheckBoostVersion)
message(STATUS "Boost found: ${BOOST_VERSION} ${BOOST_SOURCE}")

include(PlatformDetect)
include(AddBoostLib)


# include the boost modules
include(boost)
include(context)
include(fiber)