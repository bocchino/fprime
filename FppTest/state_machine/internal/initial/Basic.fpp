module FppTest {

  @ A basic state machine
  state machine Basic {

    @ Action a
    action a

    initial do { a, a } enter S

    @ State S
    state S {
      entry do { a }
    }

  }

}
