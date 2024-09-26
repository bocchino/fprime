set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/Basic.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/BasicGuard.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/BasicSelf.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/BasicU32.fpp"
)
register_fprime_module()

set(UT_SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/Basic.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/BasicGuard.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/BasicSelf.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/BasicU32.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/main.cpp"
)
set(UT_MOD_DEPS STest)
register_fprime_ut()
