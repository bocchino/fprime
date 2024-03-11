set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/DpWriter.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/DpWriter.fpp"
)

set(MOD_DEPS
  Fw/Dp
)

register_fprime_module()

set(UT_SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/DpWriter.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/DpWriterTestMain.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/DpWriterTester.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/Rules/FileOpenStatus.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/Rules/FileWriteStatus.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/Rules/SchedIn.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/Rules/Testers.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/Scenarios/Random.cpp"
)

set(UT_MOD_DEPS
  STest
)

set(UT_AUTO_HELPERS ON)
register_fprime_ut()
