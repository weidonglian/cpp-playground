include(FetchContent)

# continuable
message(STATUS "Fetching continuable and making continuable available and it could take a while to build continuable, take a coffee...")

# Add continuable package with specific options using CPM
CPMAddPackage(
  NAME continuable
  GIT_REPOSITORY https://github.com/Naios/continuable.git
  GIT_TAG 4.2.2
)