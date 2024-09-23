module FppTest {

  module State {

    @ A basic state machine
    state machine StateBasic {

      @ Action a
      action a

      @ Signal s
      signal s

      initial enter S

      @ State S
      state S {
        @ A state transition
        on s do { a } enter T
      }

      @ State T
      state T

    }

  }

}
