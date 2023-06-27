set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/DpManager.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/DpManager.cpp"
)

register_fprime_module()

set(UT_SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/DpManager.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/TestMain.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/Tester.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/TesterHelpers.cpp"
)
register_fprime_ut()
