// ======================================================================
// \title  InputPairU16U32.hpp
// \author bocchino
// \brief  hpp file for InputPairU16U32 component implementation class
// ======================================================================

#ifndef FppTest_SmInstanceJunction_InputPairU16U32_HPP
#define FppTest_SmInstanceJunction_InputPairU16U32_HPP

#include "FppTest/state_machine/internal/harness/Harness.hpp"
#include "FppTest/state_machine/internal_instance/junction/InputPairU16U32ComponentAc.hpp"

namespace FppTest {

namespace SmInstanceJunction {

class InputPairU16U32 : public InputPairU16U32ComponentBase {
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

    //! The type FppTest_SmJunction_InputPairU16U32
    using SmJunction_InputPairU16U32 = FppTest_SmJunction_InputPairU16U32;

  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct InputPairU16U32 object
    InputPairU16U32(const char* const compName  //!< The component name
    );

    //! Destroy InputPairU16U32 object
    ~InputPairU16U32();

  PRIVATE:
    // ----------------------------------------------------------------------
    // Implementations for internal state machine actions
    // ----------------------------------------------------------------------

    //! Implementation for action a of state machine FppTest_SmJunction_InputPairU16U32
    //!
    //! Action a
    void FppTest_SmJunction_InputPairU16U32_action_a(SmId smId,  //!< The state machine id
                                                     FppTest_SmJunction_InputPairU16U32::Signal signal,  //!< The signal
                                                     U32 value                                           //!< The value
                                                     ) override;

  PRIVATE:
    // ----------------------------------------------------------------------
    // Implementations for internal state machine guards
    // ----------------------------------------------------------------------

    //! Implementation for guard g of state machine FppTest_SmJunction_InputPairU16U32
    //!
    //! Guard g
    bool FppTest_SmJunction_InputPairU16U32_guard_g(SmId smId,  //!< The state machine id
                                                    FppTest_SmJunction_InputPairU16U32::Signal signal,  //!< The signal
                                                    U32 value                                           //!< The value
    ) const override;

  public:
    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    //! Run the test with signal s1 and true guard
    void testS1True();

    //! Run the test with signal s1 and false guard
    void testS1False();

    //! Run the test with signal s2 and true guard
    void testS2True();

    //! Run the test with signal s2 and false guard
    void testS2False();

  private:
    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! The history associated with action a of smJunctionInputPairU16U32
    SmHarness::SignalValueHistory<SmJunction_InputPairU16U32::Signal, U32, historySize>
        m_smJunctionInputPairU16U32_action_a_history;

    //! The guard g of smJunctionInputPairU16U32
    SmHarness::Guard<SmJunction_InputPairU16U32::Signal, U32, historySize> m_smJunctionInputPairU16U32_guard_g;
};

}  // namespace SmInstanceJunction

}  // namespace FppTest

#endif
