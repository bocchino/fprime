// ======================================================================
// \title  Basic.hpp
// \author bocchino
// \brief  hpp file for Basic component implementation class
// ======================================================================

#ifndef FppTest_SmInstanceState_Basic_HPP
#define FppTest_SmInstanceState_Basic_HPP

#include "FppTest/state_machine/internal/harness/Harness.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicComponentAc.hpp"

namespace FppTest {

namespace SmInstanceState {

class Basic : public BasicComponentBase {
  private:
    // ----------------------------------------------------------------------
    // Constants
    // ----------------------------------------------------------------------

    //! The history size
    static constexpr FwSizeType historySize = 10;

    //! The queue depth
    static constexpr FwSizeType queueDepth = 10;

    //! The instance ID
    static constexpr FwEnumStoreType instanceId = 0;

  private:
    // ----------------------------------------------------------------------
    // Types
    // ----------------------------------------------------------------------

    //! The type FppTest_SmInstanceState_Basic_Basic
    using Basic_Basic = FppTest_SmInstanceState_Basic_Basic;

    //! The type FppTest_SmState_Basic
    using SmState_Basic = FppTest_SmState_Basic;

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

  public:
    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    //! Run the test
    void test();

  private:
    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! The history associated with action a of basic
    SmHarness::History<Basic_Basic::Signal, historySize> m_basic_action_a_history;

    //! The history associated with action a of smStateBasic
    SmHarness::History<SmState_Basic::Signal, historySize> m_smStateBasic_action_a_history;
};

}  // namespace SmInstanceState

}  // namespace FppTest

#endif
