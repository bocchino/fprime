module Svc {

  @ A component for managing data products
  active component DpManager {

    # ----------------------------------------------------------------------
    # General ports
    # ----------------------------------------------------------------------

    @ Schedule in port
    async input port schedIn: Svc.Sched

    @ Port for receiving buffer requests from a client component
    async input port dpBufferRequestIn: Fw.DpBufferRequest

    @ Port for getting buffers from a Buffer Manager
    output port bufferGetOut: Fw.BufferGet

    @ Port for sending requested buffers to a client component
    output port dpBufferSendOut: Fw.DpBufferSend

    @ Port for receiving data products from a client component
    async input port dpBufferSendIn: Fw.DpBufferSend

    @ Port for sending data products to a downstream component
    output port bufferSendOut: Fw.BufferSend

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
    # Telemetry
    # ----------------------------------------------------------------------

    # TODO

    # ----------------------------------------------------------------------
    # Events
    # ----------------------------------------------------------------------

    # TODO

  }

}
