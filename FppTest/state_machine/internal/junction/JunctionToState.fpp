module FppTest {

  module SmJunction {

    @ A state machine for testing junction-to-state transitions
    @ with hierarchy
    state machine JunctionToState {

      @ Exit S1
      action exitS1

      @ Action a
      action a

      @ Enter S2
      action enterS2

      @ Enter S3
      action enterS3

      @ Signal s
      signal s

      @ Guard g
      guard g

      @ Initial transition
      initial enter S1

      @ State S1
      state S1 {

        @ Exit S1
        exit do { exitS1 }

        @ Junction J
        junction J {
          if g do { a } enter S2 else do { a } enter S2.S3
        }

        @ State transition to J
        on s enter J

      }

      @ State S2
      state S2 {

        @ Enter S2
        entry do { enterS2 }

        @ Initial transition
        initial do { a } enter S3

        @ State S3
        state S3 {

          @ Enter S3
          entry do { enterS3 }

        }

      }

    }

  }

}
