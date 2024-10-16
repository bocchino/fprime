// ======================================================================
// \title  Basic.hpp
// \author bocchino
// \brief  hpp file for Basic component implementation class
// ======================================================================

#ifndef FppTest_SmInstanceState_Basic_HPP
#define FppTest_SmInstanceState_Basic_HPP

#include "FppTest/state_machine/internal_instance/state/BasicComponentAc.hpp"

namespace FppTest {

namespace SmInstanceState {

class Basic : public BasicComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct Basic object
    Basic(const char* const compName  //!< The component name
    );

    //! Destroy Basic object
    ~Basic();

  PRIVATE:
    // ----------------------------------------------------------------------
    // Implementations for internal state machine actions
    // ----------------------------------------------------------------------

    //! Implementation for action a of state machine FppTest_SmInstanceState_Basic_Basic
    //!
    //! Action a
    void FppTest_SmInstanceState_Basic_Basic_action_a(
        SmId smId,                                          //!< The state machine id
        FppTest_SmInstanceState_Basic_Basic::Signal signal  //!< The signal
        ) override;

    //! Implementation for action a of state machine FppTest_SmState_Basic
    //!
    //! Action a
    void FppTest_SmState_Basic_action_a(SmId smId,                            //!< The state machine id
                                        FppTest_SmState_Basic::Signal signal  //!< The signal
                                        ) override;
};

}  // namespace SmInstanceState

}  // namespace FppTest

#endif
