set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/Basic.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/BasicU32.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/InputPairU16U32.fpp"
)
set(MOD_DEPS FppTest/state_machine/internal/harness)
register_fprime_module()

set(UT_SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/Basic.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/BasicU32.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/InputPairU16U32.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/main.cpp"
)
set(UT_MOD_DEPS STest)
register_fprime_ut()
