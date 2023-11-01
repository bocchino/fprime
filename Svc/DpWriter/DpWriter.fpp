module Svc {

  @ A component for writing data products to disk
  active component DpWriter {

    # ----------------------------------------------------------------------
    # Scheduling ports
    # ----------------------------------------------------------------------

    @ Schedule in port
    async input port schedIn: Svc.Sched

    # ----------------------------------------------------------------------
    # Ports for handling data products
    # ----------------------------------------------------------------------

    @ Port for receiving data products to write to disk
    async input port bufferSendIn: Fw.BufferSend

    @ Port for processing data products
    output port procBufferSendOut: [DpWriterNumProcPorts] Fw.BufferSend

    # ----------------------------------------------------------------------
    # F' special ports
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

    # TODO

    # ----------------------------------------------------------------------
    # Telemetry
    # ----------------------------------------------------------------------

    # TODO

  }

}
