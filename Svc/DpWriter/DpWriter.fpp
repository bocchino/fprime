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

    @ Port for sending DpWritten notifications
    output port dpWrittenOut: DpWritten

    @ Port for deallocating data product buffers
    output port deallocBufferSendOut: Fw.BufferSend

    # ----------------------------------------------------------------------
    # F' special ports
    # ----------------------------------------------------------------------

    @ Command receive port
    command recv port cmdIn

    @ Command registration port
    command reg port cmdRegIn

    @ Command response port
    command resp port cmdResponseOut

    @ Time get port
    time get port timeGetOut

    @ Telemetry port
    telemetry port tlmOut

    @ Event port
    event port eventOut

    @ Text event port
    text event port textEventOut

    # ----------------------------------------------------------------------
    # Commands 
    # ----------------------------------------------------------------------

    @ Clear event throttling
    async command CLEAR_EVENT_THROTTLE

    # ----------------------------------------------------------------------
    # Events
    # ----------------------------------------------------------------------

    @ Incoming buffer is invalid
    event BufferInvalid \
      severity warning high \
      format "Received buffer is invalid" \
      throttle 10

    @ Incoming buffer is too small to hold a data product container
    event BufferTooSmall(
                          $size: U32 @< The buffer size
                        ) \
      severity warning high \
      format "Received buffer of size {} is too small to hold a data product container" \
      throttle 10

    @ Incoming buffer has an invalid packet descriptor
    event InvalidPacketDescriptor(
                                   descriptor: U32 @< The descriptor
                                 ) \
      severity warning high \
      format "Packet descriptor {} is invalid" \
      throttle 10

    @ An error occurred when opening a file
    event FileOpenError(
                         errorNum: U32 @< The error number returned from the open operation
                         file: string size FileNameStringSize @< The file
                       ) \
      severity warning high \
      format "Error {} opening file {}" \
      throttle 10

    @ An error occurred when writing to a file
    event FileWriteError(
                          errornum: U32 @< The error number returned from the write operation
                          bytesWritten: U32 @< The number of bytes successfully written
                          bytesToWrite: U32 @< The number of bytes attempted
                          file: string size FileNameStringSize @< The file
                        ) \
      severity warning high \
      format "Error {} while writing {} of {} bytes to {}" \
      throttle 10

    # ----------------------------------------------------------------------
    # Telemetry
    # ----------------------------------------------------------------------

    @ The number of data products handled
    telemetry NumDataProducts: U32 update on change

    @ The number of bytes written
    telemetry NumBytes: U64 update on change

  }

}
