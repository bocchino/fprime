set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/Basic.fpp"
)
register_fprime_module()

set(UT_SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/Basic.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/main.cpp"
)
set(UT_MOD_DEPS STest)
register_fprime_ut()
