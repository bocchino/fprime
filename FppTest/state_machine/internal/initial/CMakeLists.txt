set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/Basic.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/Junction.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/Nested.fpp"
)
register_fprime_module()
set(MOD_DEPS FppTest/state_machine/internal/harness)

set(UT_SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/Basic.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Junction.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Nested.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/main.cpp"
)
set(UT_MOD_DEPS STest)
register_fprime_ut()
