add_subdirectory(simple_svg)
add_subdirectory(catch2)
add_subdirectory(function2)
add_subdirectory(asio)

option(CTI_CONTINUABLE_WITH_NO_EXCEPTIONS "Disable exception support" ON)
add_subdirectory(continuable)