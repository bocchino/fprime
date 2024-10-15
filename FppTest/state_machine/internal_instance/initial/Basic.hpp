// ======================================================================
// \title  Basic.hpp
// \author bocchino
// \brief  hpp file for Basic component implementation class
// ======================================================================

#ifndef FppTest_SmInstanceInitial_Basic_HPP
#define FppTest_SmInstanceInitial_Basic_HPP

#include "FppTest/state_machine/internal_instance/initial/BasicComponentAc.hpp"

namespace FppTest {

namespace SmInstanceInitial {

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

    //! Implementation for action a of state machine FppTest_SmInitial_Basic
    //!
    //! Action a
    void FppTest_SmInitial_Basic_action_a(SmId smId,                              //!< The state machine id
                                          FppTest_SmInitial_Basic::Signal signal  //!< The signal
                                          ) override;

    //! Implementation for action a of state machine FppTest_SmInstanceInitial_Basic_Basic
    //!
    //! Action a
    void FppTest_SmInstanceInitial_Basic_Basic_action_a(
        SmId smId,                                            //!< The state machine id
        FppTest_SmInstanceInitial_Basic_Basic::Signal signal  //!< The signal
        ) override;
};

}  // namespace SmInstanceInitial

}  // namespace FppTest

#endif
