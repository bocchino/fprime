// ======================================================================
// \title  DpManager.cpp
// \author bocchino
// \brief  cpp file for DpManager component implementation class
// ======================================================================

#include "FpConfig.hpp"
#include "Svc/DpManager/DpManager.hpp"

namespace Svc {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

DpManager::DpManager(const char* const compName)
    : DpManagerComponentBase(compName),
      numSuccessfulAllocations(0),
      numFailedAllocations(0),
      numDataProducts(0),
      numBytes(0) {}

DpManager::~DpManager() {}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void DpManager::productRequestIn_handler(const NATIVE_INT_TYPE portNum, FwDpIdType id, FwSizeType size) {
    // portNum is unused
    (void) portNum;
    // Get a buffer
    Fw::Buffer buffer = this->bufferGetOut_out(0, size);
    Fw::Success status(Fw::Success::FAILURE);
    if (buffer.isValid()) {
        // Buffer is valid
        this->numSuccessfulAllocations++;
        status = Fw::Success::SUCCESS;
    } else {
        // Buffer is invalid
        this->numFailedAllocations++;
        this->log_WARNING_HI_BufferAllocationFailed(id);
    }
    // Send buffer on productResponseOut
    this->productResponseOut_out(0, id, buffer, status);
}

void DpManager::productSendIn_handler(const NATIVE_INT_TYPE portNum, FwDpIdType id, const Fw::Buffer& buffer) {
    // portNum and id are unused
    (void) portNum;
    (void) id;
    // Update state variables
    this->numDataProducts++;
    this->numBytes += buffer.getSize();
    // Send the buffer on productSendOut
    Fw::Buffer sendBuffer = buffer;
    this->productSendOut_out(0, sendBuffer);
}

void DpManager::schedIn_handler(const NATIVE_INT_TYPE portNum, NATIVE_UINT_TYPE context) {
    // Emit telemetry
    this->tlmWrite_NumSuccessfulAllocations(this->numSuccessfulAllocations);
    this->tlmWrite_NumFailedAllocations(this->numFailedAllocations);
    this->tlmWrite_NumDataProducts(this->numDataProducts);
    this->tlmWrite_NumBytes(this->numBytes);
}

}  // end namespace Svc
