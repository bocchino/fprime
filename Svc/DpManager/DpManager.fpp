module Svc {

  @ A component for managing data products
  active component DpManager {

    # ----------------------------------------------------------------------
    # General ports
    # ----------------------------------------------------------------------

    @ Schedule in port
    async input port schedIn: Svc.Sched

    @ Port for receiving data product buffer requests from a client component
    async input port productRequestIn: Fw.DpRequest

    @ Port for getting buffers from a Buffer Manager
    output port bufferGetOut: Fw.BufferGet

    @ Port for sending requested data product buffers to a client component
    output port productResponseOut: Fw.DpSend

    @ Port for receiving filled data product buffers from a client component
    async input port productSendIn: Fw.DpSend

    @ Port for sending filled data product buffers to a downstream component
    output port productSendOut: Fw.BufferSend

    # ----------------------------------------------------------------------
    # Special ports
    # ----------------------------------------------------------------------

    @ Time get port
    time get port timeGetOut

    @ Telemetry port
    telemetry port tlmOut

    @ Event port
    event port eventOut

    @ Text event port
    text event port textEventOut

    # ----------------------------------------------------------------------
    # Events
    # ----------------------------------------------------------------------

    @ Buffer allocation failed
    event BufferAllocationFailed(
                                  $id: U32 @< The container ID
                                ) \
      severity warning high \
      format "Buffer allocation failed for container id {}"

    # ----------------------------------------------------------------------
    # Telemetry
    # ----------------------------------------------------------------------

    @ The number of successful buffer allocations
    telemetry NumSuccessfulAllocations: U32 update on change

    @ The number of failed buffer allocations
    telemetry NumFailedAllocations: U32 update on change

    @ Number of data products handled
    telemetry NumDataProducts: U32 update on change

    @ Number of bytes handled
    telemetry NumBytes: U32 update on change

  }

}
