module FppTest {

  module SmInstanceInitial {

    active component Basic {

      include "../../internal/initial/include/Basic.fppi"

      state machine instance basic: Basic

      state machine instance smInitialBasic: SmInitial.Basic

    }

  }

}
