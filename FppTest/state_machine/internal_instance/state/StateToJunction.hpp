// ======================================================================
// \title  StateToJunction.hpp
// \author bocchino
// \brief  hpp file for StateToJunction component implementation class
// ======================================================================

#ifndef FppTest_SmInstanceState_StateToJunction_HPP
#define FppTest_SmInstanceState_StateToJunction_HPP

#include "FppTest/state_machine/internal/harness/Harness.hpp"
#include "FppTest/state_machine/internal_instance/state/StateToJunctionComponentAc.hpp"

namespace FppTest {

namespace SmInstanceState {

class StateToJunction : public StateToJunctionComponentBase {
    // ----------------------------------------------------------------------
    // Constants
    // ----------------------------------------------------------------------

    //! The history size
    static constexpr FwSizeType historySize = 10;

    //! The queue depth
    static constexpr FwSizeType queueDepth = 10;

    //! The instance ID
    static constexpr FwEnumStoreType instanceId = 0;

  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct StateToJunction object
    StateToJunction(const char* const compName  //!< The component name
    );

    //! Destroy StateToJunction object
    ~StateToJunction();

  private:
    // ----------------------------------------------------------------------
    // Types
    // ----------------------------------------------------------------------

    //! The type FppTest_SmState_StateToJunction
    using SmState_StateToJunction = FppTest_SmState_StateToJunction;

    //! Action IDs
    enum class ActionId { EXIT_S1, EXIT_S2, EXIT_S3, A, ENTER_S1, ENTER_S2, ENTER_S3, ENTER_S4 };

  PRIVATE:
    // ----------------------------------------------------------------------
    // Implementations for internal state machine actions
    // ----------------------------------------------------------------------

    //! Implementation for action exitS1 of state machine FppTest_SmState_StateToJunction
    //!
    //! Exit S1
    void FppTest_SmState_StateToJunction_action_exitS1(SmId smId,  //!< The state machine id
                                                       FppTest_SmState_StateToJunction::Signal signal  //!< The signal
                                                       ) override;

    //! Implementation for action exitS2 of state machine FppTest_SmState_StateToJunction
    //!
    //! Exit S2
    void FppTest_SmState_StateToJunction_action_exitS2(SmId smId,  //!< The state machine id
                                                       FppTest_SmState_StateToJunction::Signal signal  //!< The signal
                                                       ) override;

    //! Implementation for action exitS3 of state machine FppTest_SmState_StateToJunction
    //!
    //! Exit S3
    void FppTest_SmState_StateToJunction_action_exitS3(SmId smId,  //!< The state machine id
                                                       FppTest_SmState_StateToJunction::Signal signal  //!< The signal
                                                       ) override;

    //! Implementation for action a of state machine FppTest_SmState_StateToJunction
    //!
    //! Action a
    void FppTest_SmState_StateToJunction_action_a(SmId smId,  //!< The state machine id
                                                  FppTest_SmState_StateToJunction::Signal signal  //!< The signal
                                                  ) override;

    //! Implementation for action enterS1 of state machine FppTest_SmState_StateToJunction
    //!
    //! Enter S1
    void FppTest_SmState_StateToJunction_action_enterS1(SmId smId,  //!< The state machine id
                                                        FppTest_SmState_StateToJunction::Signal signal  //!< The signal
                                                        ) override;

    //! Implementation for action enterS2 of state machine FppTest_SmState_StateToJunction
    //!
    //! Enter S2
    void FppTest_SmState_StateToJunction_action_enterS2(SmId smId,  //!< The state machine id
                                                        FppTest_SmState_StateToJunction::Signal signal  //!< The signal
                                                        ) override;

    //! Implementation for action enterS3 of state machine FppTest_SmState_StateToJunction
    //!
    //! Enter S3
    void FppTest_SmState_StateToJunction_action_enterS3(SmId smId,  //!< The state machine id
                                                        FppTest_SmState_StateToJunction::Signal signal  //!< The signal
                                                        ) override;

    //! Implementation for action enterS4 of state machine FppTest_SmState_StateToJunction
    //!
    //! Enter S4
    void FppTest_SmState_StateToJunction_action_enterS4(SmId smId,  //!< The state machine id
                                                        FppTest_SmState_StateToJunction::Signal signal  //!< The signal
                                                        ) override;

  PRIVATE:
    // ----------------------------------------------------------------------
    // Implementations for internal state machine guards
    // ----------------------------------------------------------------------

    //! Implementation for guard g of state machine FppTest_SmState_StateToJunction
    //!
    //! Guard g
    bool FppTest_SmState_StateToJunction_guard_g(SmId smId,  //!< The state machine id
                                                 FppTest_SmState_StateToJunction::Signal signal  //!< The signal
    ) const override;

  public:
    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    //! Test initial transition
    void testInit();

    //! Test transition S2 to J
    void testS2_to_J();

    //! Test transition S2 to S3
    void testS2_to_S3();

    //! Test transition S2 to S4
    void testS2_to_S4();

    //! Test transition S3 to J
    void testS3_to_J();

    //! Test transition S3 to S4
    void testS3_to_S4();

  private:
    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! The action history for SmStateStateToJunction
    SmHarness::SignalValueHistory<SmState_StateToJunction::Signal, ActionId, historySize>
        m_smStateStateToJunction_actionHistory;

    //! The guard g for SmStateStateToJunction
    SmHarness::NoArgGuard<SmState_StateToJunction::Signal, historySize> m_smStateStateToJunction_guard_g;
};

}  // namespace SmInstanceState

}  // namespace FppTest

#endif
