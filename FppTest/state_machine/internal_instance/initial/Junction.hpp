// ======================================================================
// \title  Junction.hpp
// \author bocchino
// \brief  hpp file for Junction component implementation class
// ======================================================================

#ifndef FppTest_SmInstanceInitial_Junction_HPP
#define FppTest_SmInstanceInitial_Junction_HPP

#include "FppTest/state_machine/internal/harness/Harness.hpp"
#include "FppTest/state_machine/internal_instance/initial/JunctionComponentAc.hpp"

namespace FppTest {

namespace SmInstanceInitial {

class Junction : public JunctionComponentBase {
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

    //! The type FppTest_SmInstanceInitial_Junction_Junction
    using Junction_Junction = FppTest_SmInstanceInitial_Junction_Junction;

    //! The type FppTest_SmInitial_Junction
    using SmInitial_Junction = FppTest_SmInitial_Junction;

  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct Junction object
    Junction(const char* const compName  //!< The component name
    );

    //! Destroy Junction object
    ~Junction();

  PRIVATE:
    // ----------------------------------------------------------------------
    // Implementations for internal state machine actions
    // ----------------------------------------------------------------------

    //! Implementation for action a of state machine FppTest_SmInitial_Junction
    //!
    //! Action a
    void FppTest_SmInitial_Junction_action_a(SmId smId,                                 //!< The state machine id
                                             FppTest_SmInitial_Junction::Signal signal  //!< The signal
                                             ) override;

    //! Implementation for action a of state machine FppTest_SmInstanceInitial_Junction_Junction
    //!
    //! Action a
    void FppTest_SmInstanceInitial_Junction_Junction_action_a(
        SmId smId,                                                  //!< The state machine id
        FppTest_SmInstanceInitial_Junction_Junction::Signal signal  //!< The signal
        ) override;

  PRIVATE:
    // ----------------------------------------------------------------------
    // Implementations for internal state machine guards
    // ----------------------------------------------------------------------

    //! Implementation for guard g of state machine FppTest_SmInitial_Junction
    //!
    //! Guard g
    bool FppTest_SmInitial_Junction_guard_g(SmId smId,                                 //!< The state machine id
                                            FppTest_SmInitial_Junction::Signal signal  //!< The signal
    ) const override;

    //! Implementation for guard g of state machine FppTest_SmInstanceInitial_Junction_Junction
    //!
    //! Guard g
    bool FppTest_SmInstanceInitial_Junction_Junction_guard_g(
        SmId smId,                                                  //!< The state machine id
        FppTest_SmInstanceInitial_Junction_Junction::Signal signal  //!< The signal
    ) const override;

  public:
    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    //! Test with true guard
    void testTrue();

    //! Test with false guard
    void testFalse();

  private:
    // ----------------------------------------------------------------------
    // Helper functions
    // ----------------------------------------------------------------------

    //! Helper function for checking actions and guards
    void checkActionsAndGuards(FwSizeType expectedActionSize,  //!< The expected action size
                               FwSizeType expectedGuardSize    //!< The expected guard size
    );

  private:
    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! The history associated with action a of junction
    SmHarness::History<Junction_Junction::Signal, historySize> m_junction_action_a_history;

    //! The history associated with action a of smInitialJunction
    SmHarness::History<SmInitial_Junction::Signal, historySize> m_smInitialJunction_action_a_history;

    //! The guard g of junction
    SmHarness::NoArgGuard<Junction_Junction::Signal, historySize> m_junction_guard_g;

    //! The guard g of smInitialJunction
    SmHarness::NoArgGuard<SmInitial_Junction::Signal, historySize> m_smInitialJunction_guard_g;
};

}  // namespace SmInstanceInitial

}  // namespace FppTest

#endif
