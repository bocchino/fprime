// ======================================================================
// \title  JunctionToState.hpp
// \author bocchino
// \brief  hpp file for JunctionToState component implementation class
// ======================================================================

#ifndef FppTest_SmInstanceJunction_JunctionToState_HPP
#define FppTest_SmInstanceJunction_JunctionToState_HPP

#include "FppTest/state_machine/internal/harness/Harness.hpp"
#include "FppTest/state_machine/internal_instance/junction/JunctionToStateComponentAc.hpp"

namespace FppTest {

namespace SmInstanceJunction {

class JunctionToState : public JunctionToStateComponentBase {
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
        ENTER_S3,
    };

    //! The type FppTest_SmJunction_JunctionToState
    using SmJunction_JunctionToState = FppTest_SmJunction_JunctionToState;

  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct JunctionToState object
    JunctionToState(const char* const compName  //!< The component name
    );

    //! Destroy JunctionToState object
    ~JunctionToState();

  PRIVATE:
    // ----------------------------------------------------------------------
    // Implementations for internal state machine actions
    // ----------------------------------------------------------------------

    //! Implementation for action exitS1 of state machine FppTest_SmJunction_JunctionToState
    //!
    //! Exit S1
    void FppTest_SmJunction_JunctionToState_action_exitS1(
        SmId smId,                                         //!< The state machine id
        FppTest_SmJunction_JunctionToState::Signal signal  //!< The signal
        ) override;

    //! Implementation for action a of state machine FppTest_SmJunction_JunctionToState
    //!
    //! Action a
    void FppTest_SmJunction_JunctionToState_action_a(SmId smId,  //!< The state machine id
                                                     FppTest_SmJunction_JunctionToState::Signal signal  //!< The signal
                                                     ) override;

    //! Implementation for action enterS2 of state machine FppTest_SmJunction_JunctionToState
    //!
    //! Enter S2
    void FppTest_SmJunction_JunctionToState_action_enterS2(
        SmId smId,                                         //!< The state machine id
        FppTest_SmJunction_JunctionToState::Signal signal  //!< The signal
        ) override;

    //! Implementation for action enterS3 of state machine FppTest_SmJunction_JunctionToState
    //!
    //! Enter S3
    void FppTest_SmJunction_JunctionToState_action_enterS3(
        SmId smId,                                         //!< The state machine id
        FppTest_SmJunction_JunctionToState::Signal signal  //!< The signal
        ) override;

  PRIVATE:
    // ----------------------------------------------------------------------
    // Implementations for internal state machine guards
    // ----------------------------------------------------------------------

    //! Implementation for guard g of state machine FppTest_SmJunction_JunctionToState
    //!
    //! Guard g
    bool FppTest_SmJunction_JunctionToState_guard_g(SmId smId,  //!< The state machine id
                                                    FppTest_SmJunction_JunctionToState::Signal signal  //!< The signal
    ) const override;

  public:
    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    //! Run the test with the true guard
    void testTrue();

    //! Run the test with the false guard
    void testFalse();

  private:
    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! The action history for smJunctionJunctionToState
    SmHarness::SignalValueHistory<SmJunction_JunctionToState::Signal, ActionId, historySize>
        m_smJunctionJunctionToState_actionHistory;

    //! The guard g for smJunctionJunctionToState
    SmHarness::NoArgGuard<SmJunction_JunctionToState::Signal, historySize> m_smJunctionJunctionToState_guard_g;
};

}  // namespace SmInstanceJunction

}  // namespace FppTest

#endif
