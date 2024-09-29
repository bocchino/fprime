module FppTest {

  module SmState {

    @ A state machine for testing state-to-junction transitions
    @ with hierarchy
    state machine StateToJunction {

      @ Exit S1
      action exitS1

      @ Exit S2
      action exitS2

      @ Exit S3
      action exitS3

      @ Action a
      action a

      @ Enter S1
      action enterS1

      @ Enter S2
      action enterS2

      @ Enter S3
      action enterS3

      @ Enter S4
      action enterS4

      @ Guard g
      guard g

      @ Signal for going from S1 to S4
      signal S1_to_S4

      @ Signal for going from S1 to J
      signal S1_to_J

      @ Signal for going from S2 to S3
      signal S2_to_S3

      @ Initial transition
      initial enter S1

      @ State S1
      state S1 {

        @ Initial transition
        initial enter S2

        @ Enter S1
        entry do { enterS1 }

        @ Exit S1
        exit do { exitS1 }

        @ State S2
        state S2 {

          @ Enter S2
          entry do { enterS2 }

          @ Exit S2
          exit do { exitS2 }

          @ State transition to S3
          on S2_to_S3 enter S3

        }

        @ State S3
        state S3 {

          @ Enter S3
          entry do { enterS3 }

          @ Exit S3
          exit do { exitS3 }

        }

        @ State transition to S4
        on S1_to_S4 do { a } enter S4

        @ State transition to J
        on S1_to_J do { a } enter S4.J

      }

      @ State S4
      state S4 {

        @ Initial transition
        initial enter J

        @ Enter S4
        entry do { enterS4 }

        @ Junction J
        junction J { if g enter S5 else enter S6 }

        @ State S5
        state S5

        @ State S6
        state S6

      }

    }

  }

}
