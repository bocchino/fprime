// ======================================================================
// \title  JunctionToJunction.hpp
// \author bocchino
// \brief  hpp file for JunctionToJunction component implementation class
// ======================================================================

#ifndef FppTest_SmInstanceJunction_JunctionToJunction_HPP
#define FppTest_SmInstanceJunction_JunctionToJunction_HPP

#include "FppTest/state_machine/internal/harness/Harness.hpp"
#include "FppTest/state_machine/internal_instance/junction/JunctionToJunctionComponentAc.hpp"

namespace FppTest {

namespace SmInstanceJunction {

class JunctionToJunction : public JunctionToJunctionComponentBase {
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

    //! Action IDs
    enum class ActionId {
        EXIT_S1,
        A,
        ENTER_S2,
    };

    //! The type FppTest_SmJunction_JunctionToJunction
    using SmJunction_JunctionToJunction = FppTest_SmJunction_JunctionToJunction;

  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct JunctionToJunction object
    JunctionToJunction(const char* const compName  //!< The component name
    );

    //! Destroy JunctionToJunction object
    ~JunctionToJunction();

  PRIVATE:
    // ----------------------------------------------------------------------
    // Implementations for internal state machine actions
    // ----------------------------------------------------------------------

    //! Implementation for action exitS1 of state machine FppTest_SmJunction_JunctionToJunction
    //!
    //! Exit S1
    void FppTest_SmJunction_JunctionToJunction_action_exitS1(
        SmId smId,                                            //!< The state machine id
        FppTest_SmJunction_JunctionToJunction::Signal signal  //!< The signal
        ) override;

    //! Implementation for action a of state machine FppTest_SmJunction_JunctionToJunction
    //!
    //! Action a
    void FppTest_SmJunction_JunctionToJunction_action_a(
        SmId smId,                                            //!< The state machine id
        FppTest_SmJunction_JunctionToJunction::Signal signal  //!< The signal
        ) override;

    //! Implementation for action enterS2 of state machine FppTest_SmJunction_JunctionToJunction
    //!
    //! Enter S2
    void FppTest_SmJunction_JunctionToJunction_action_enterS2(
        SmId smId,                                            //!< The state machine id
        FppTest_SmJunction_JunctionToJunction::Signal signal  //!< The signal
        ) override;

  PRIVATE:
    // ----------------------------------------------------------------------
    // Implementations for internal state machine guards
    // ----------------------------------------------------------------------

    //! Implementation for guard g1 of state machine FppTest_SmJunction_JunctionToJunction
    //!
    //! Guard g1
    bool FppTest_SmJunction_JunctionToJunction_guard_g1(
        SmId smId,                                            //!< The state machine id
        FppTest_SmJunction_JunctionToJunction::Signal signal  //!< The signal
    ) const override;

    //! Implementation for guard g2 of state machine FppTest_SmJunction_JunctionToJunction
    //!
    //! Guard g2
    bool FppTest_SmJunction_JunctionToJunction_guard_g2(
        SmId smId,                                            //!< The state machine id
        FppTest_SmJunction_JunctionToJunction::Signal signal  //!< The signal
    ) const override;

  PRIVATE:
    // ----------------------------------------------------------------------
    // Overflow hook implementations for internal state machines
    // ----------------------------------------------------------------------

    //! Overflow hook implementation for smJunctionJunctionToJunction
    void smJunctionJunctionToJunction_stateMachineOverflowHook(SmId smId,               //!< The state machine ID
                                                               FwEnumStoreType signal,  //!< The signal
                                                               Fw::SerializeBufferBase& buffer  //!< The message buffer
                                                               ) override;

  public:
    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    //! Run the test with g1 true
    void testG1True();

    //! Run the test with g1 false and g2 true
    void testG1FalseG2True();

    //! Run the test with g1 false and g2 false
    void testG1FalseG2False();

    //! Test with queue overflow
    void testOverflow();

  private:
    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! Whether the overflow hook was called
    bool m_hookCalled = false;

    //! The action history for smJunctionJunctionToJunction
    SmHarness::SignalValueHistory<SmJunction_JunctionToJunction::Signal, ActionId, historySize>
        m_smJunctionJunctionToJunction_actionHistory;

    //! The guard g1 for smJunctionJunctionToJunction
    SmHarness::NoArgGuard<SmJunction_JunctionToJunction::Signal, historySize> m_smJunctionJunctionToJunction_guard_g1;

    //! The guard g2 for smJunctionJunctionToJunction
    SmHarness::NoArgGuard<SmJunction_JunctionToJunction::Signal, historySize> m_smJunctionJunctionToJunction_guard_g2;
};

}  // namespace SmInstanceJunction

}  // namespace FppTest

#endif
