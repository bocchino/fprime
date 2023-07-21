set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/DpManager.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/DpManager.cpp"
)

register_fprime_module()

set(UT_SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/DpManager.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/Rules/BufferGetStatus.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/Rules/ProductRequestIn.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/Rules/ProductSendIn.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/Rules/SchedIn.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/Rules/Testers.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/Scenarios/Random.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/TestMain.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/Tester.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/TesterHelpers.cpp"
)

set(UT_MOD_DEPS
  STest
)

register_fprime_ut()
