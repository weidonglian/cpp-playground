message(STATUS "Fetching libcoro and make it available and it could take a while, take a coffee...")

CPMAddPackage(
  NAME libcoro
  GIT_REPOSITORY https://github.com/jbaldwin/libcoro.git
  GIT_TAG v0.12.1
  OPTIONS
    "LIBCORO_BUILD_TESTS OFF"
    "LIBCORO_BUILD_EXAMPLES OFF"
    "LIBCORO_FEATURE_NETWORKING OFF"
    "LIBCORO_FEATURE_TLS OFF"
)