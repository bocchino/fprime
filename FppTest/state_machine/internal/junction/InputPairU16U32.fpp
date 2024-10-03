module FppTest {

  module SmJunction {

    @ A state machine with two inputs to a junction
    state machine InputPairU16U32 {

      @ Action a
      action a: U32

      @ Signal s1
      signal s1: U16

      @ Signal s2
      signal s2: U32

      @ Guard g
      guard g: U32

      @ Initial transition
      initial enter S1

      @ State S1
      state S1 {

        @ State transition on s1
        on s1 enter J

        @ State transition on s2
        on s2 enter J

      }

      @ Junction J
      junction J {
        if g do { a } enter S2 else do { a } enter S3
      }

      @ State S2
      state S2

      @ State S3
      state S3

    }

  }

}
