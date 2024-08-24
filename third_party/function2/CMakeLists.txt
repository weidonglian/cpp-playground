message(STATUS "Fetching function2 and make it available and it could take a while, take a coffee...")

CPMAddPackage(
  NAME function2
  GIT_REPOSITORY https://github.com/Naios/function2.git
  GIT_TAG 4.2.4
)