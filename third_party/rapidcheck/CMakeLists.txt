# rapidcheck
message(STATUS "Fetching rapidcheck and making rapidcheck available and it could take a while to build rapidcheck, take a coffee...")

# Add rapidcheck package with specific options using CPM
CPMAddPackage(
  NAME rapidcheck
  GIT_REPOSITORY https://github.com/emil-e/rapidcheck.git
  GIT_TAG ff6af6fc683159deb51c543b065eba14dfcf329b
  OPTIONS
    "RC_ENABLE_CATCH OFF"
)
