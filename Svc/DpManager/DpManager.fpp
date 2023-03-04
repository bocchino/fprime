module Svc {

  @ A component for managing data products
  queued component DpManager {

    # ---------------------------------------------------------------------- 
    # General ports
    # ---------------------------------------------------------------------- 

    @ Schedule in port
    sync input port schedIn: Svc.Sched

    @ Port for receiving buffer requests
    async input port dpBufferRequestIn: Fw.DpBufferRequest

    @ Port for getting a buffer from a Buffer Manager
    output port bufferGetOut: Fw.BufferGet

    @ Port for sending requested buffers
    output port dpBufferSendOut: Fw.DpBufferSend

    @ Port for receiving data product buffers
    async input port dpBufferSendIn: Fw.DpBufferSend

    @ Port for sending data products
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
