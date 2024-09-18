set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/BasicStateMachineAc.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/JunctionStateMachineAc.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/NestedStateMachineAc.cpp"
)
register_fprime_module()

set(UT_SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/Basic.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Junction.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Nested.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/main.cpp"
)
set(UT_MOD_DEPS STest)
register_fprime_ut()
