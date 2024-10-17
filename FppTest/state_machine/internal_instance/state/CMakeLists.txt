set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/Basic.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/BasicGuard.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/BasicGuardString.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/BasicGuardTestAbsType.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/BasicGuardTestArray.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/BasicGuardTestEnum.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/BasicGuardTestStruct.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/BasicGuardU32.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/BasicInternal.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/BasicSelf.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/BasicString.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/BasicTestAbsType.fpp"
)
set(MOD_DEPS FppTest/state_machine/internal/harness)
register_fprime_module()

set(UT_SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/Basic.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/BasicGuard.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/BasicGuardString.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/BasicGuardTestAbsType.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/BasicGuardTestArray.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/BasicGuardTestEnum.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/BasicGuardTestStruct.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/BasicGuardU32.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/BasicInternal.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/BasicSelf.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/BasicString.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/BasicTestAbsType.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/main.cpp"
)
set(UT_MOD_DEPS STest)
register_fprime_ut()
