include(FetchContent)

# disable the compiler warning as error
biosol_disable_warnings_as_errors()

# abseil
message(STATUS "Fetching abseil and making abseil available and it could take a while to build abseil, take a coffee...")

# Add abseil package with specific options using CPM
CPMAddPackage(
  NAME absl
  GIT_REPOSITORY https://github.com/abseil/abseil-cpp.git
  GIT_TAG 20240116.2
  OPTIONS
    "BUILD_TESTING OFF"
    "ABSL_PROPAGATE_CXX_STD ON"
)