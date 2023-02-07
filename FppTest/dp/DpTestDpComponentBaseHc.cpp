// ======================================================================
// \title  DpTestDpComponentBaseHc.cpp
// \author bocchino
// \brief  Hand-coded cpp file for DpTest Dp component base (to be auto-generated)
// ======================================================================

#include "FppTest/dp/DpTestDpComponentBaseHc.hpp"
#include "Fw/Types/Assert.hpp"

namespace FppTest {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

DpTestDpComponentBaseHc ::DpTestDpComponentBaseHc(const char* const compName) : DpTestDpComponentBase(compName) {}

DpTestDpComponentBaseHc ::~DpTestDpComponentBaseHc() {}

#if 0
// ----------------------------------------------------------------------
// Private Dp handling functions
// ----------------------------------------------------------------------

void DpTestDpComponentBaseHc::productRecvIn_handler(const NATIVE_INT_TYPE portNum,
                                                    FwDpIdType id,
                                                    const Fw::Buffer& buffer) {
    DpContainer container(id, buffer, this->getIdBase());
    // Convert global id to local id
    const auto idBase = this->getIdBase();
    FW_ASSERT(id >= idBase, id, idBase);
    const auto localId = id - idBase;
    // Switch on the local id
    switch (localId) {
        case ContainerId::Container1:
            // Set the priority
            container.setPriority(10);
            // Call the handler
            this->Dp_Recv_Container1_handler(container);
            break;
        case ContainerId::Container2:
            // Set the priority
            container.setPriority(20);
            // Call the handler
            this->Dp_Recv_Container2_handler(container);
            break;
        default:
            FW_ASSERT(0);
            break;
    }
}
#endif

}  // end namespace FppTest
