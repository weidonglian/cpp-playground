message(STATUS "Fetching catch2 and making it available and it could take a while to build, take a coffee...")

# Add abseil package with specific options using CPM
CPMAddPackage(
        NAME catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.7.0
        OPTIONS
        "CATCH_INSTALL_DOCS OFF"
        "CATCH_INSTALL_EXTRAS OFF"
)
