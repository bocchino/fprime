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

    @ Incoming buffer is too small to hold a data product container
    event BufferTooSmall(
                          $size: U32 @< The buffer size
                        ) \
      severity warning high \
      format "Buffer of size {} is too small to hold a data product container"

    @ Incoming buffer had an invalid packet descriptor
    event InvalidPacketDescriptor(
                                   descriptor: U32 @< The descriptor
                                 ) \
      severity warning high \
      format "Packet descriptor {} is invalid"

    # ----------------------------------------------------------------------
    # Telemetry
    # ----------------------------------------------------------------------

    @ The number of data products handled
    telemetry NumDataProducts: U32 update on change

  }

}
