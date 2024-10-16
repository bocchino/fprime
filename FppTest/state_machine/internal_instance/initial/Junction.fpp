module FppTest {

  module SmInstanceInitial {

    active component Junction {

      include "../../internal/initial/include/Junction.fppi"

      state machine instance $junction: Junction priority 1 assert

      state machine instance smInitialJunction: SmInitial.Junction priority 2 block

    }

  }

}
