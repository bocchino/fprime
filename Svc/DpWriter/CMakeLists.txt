set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/DpWriter.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/DpWriter.fpp"
)

set(MOD_DEPS
  Fw/Dp
)

register_fprime_module()

#set(UT_SOURCE_FILES
#  "${CMAKE_CURRENT_LIST_DIR}/DpWriter.fpp"
#)
#
#set(UT_MOD_DEPS
#  STest
#)
#
#set(UT_AUTO_HELPERS ON)
#register_fprime_ut()
