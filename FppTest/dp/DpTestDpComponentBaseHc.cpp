// ======================================================================
// \title  DpTestDpComponentBaseHc.cpp
// \author bocchino
// \brief  Hand-coded cpp file for DpTest Dp component base (to be auto-generated)
// ======================================================================

#include "FppTest/dp/DpTestDpComponentBaseHc.hpp"
#include "FppTest/dp/DpTest_PriorityEnumAc.hpp"
#include "Fw/Types/Assert.hpp"

namespace FppTest {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

DpTestDpComponentBaseHc ::DpTestDpComponentBaseHc(const char* const compName) : DpTestDpComponentBase(compName) {}

DpTestDpComponentBaseHc ::~DpTestDpComponentBaseHc() {}

// ----------------------------------------------------------------------
// Private Dp handling functions
// ----------------------------------------------------------------------

void DpTestDpComponentBaseHc::productRecvIn_handler(const NATIVE_INT_TYPE portNum,
                                                  FwDpIdType id,
                                                  const Fw::Buffer& buffer) {
    DpContainer container(id, buffer, this->getIdBase());
    this->Dp_Recv_handler(container);
}

void DpTestDpComponentBaseHc::Dp_Recv_handler(DpContainer& container) {
    // Convert global id to local id
    const auto idBase = this->getIdBase();
    const auto id = container.getId();
    FW_ASSERT(id >= idBase, id, idBase);
    const auto localId = id - idBase;
    // Switch on the local id
    switch (localId) {
        case ContainerId::Container1:
            // Set the priority
            container.setPriority(DpTest_Priority::Container1);
            // Call the handler
            this->Dp_Recv_Container1_handler(container);
            break;
        case ContainerId::Container2:
            // Set the priority
            container.setPriority(DpTest_Priority::Container2);
            // Call the handler
            this->Dp_Recv_Container2_handler(container);
            break;
        default:
            FW_ASSERT(0);
            break;
    }
}

}  // end namespace FppTest
