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

    @ Received buffer is invalid
    event InvalidBuffer \
      severity warning high \
      format "Received buffer is invalid" \
      throttle 10

    @ Error occurred when deserializing the packet header
    event InvalidPacketHeader(
                               errorCode: U32 @< The error code
                             ) \
      severity warning high \
      format "Deserialization of packet header failed with error code {}" \
      throttle 10

    @ Received buffer is too small to hold a data product packet
    event BufferTooSmall(
                          bufferSize: U32 @< The incoming buffer size
                          minSize: U32 @< The minimum required size
                        ) \
      severity warning high \
      format "Received buffer has size {}; minimum required size is {}" \
      throttle 10

    @ An error occurred when opening a file
    event FileOpenError(
                         file: string size FileNameStringSize @< The file
                         status: U32 @< The status code returned from the open operation
                       ) \
      severity warning high \
      format "Error {} opening file {}" \
      throttle 10

    @ An error occurred when writing to a file
    event FileWriteError(
                          file: string size FileNameStringSize @< The file
                          bytesToWrite: U32 @< The number of bytes attempted
                          bytesWritten: U32 @< The number of bytes successfully written
                          status: U32 @< The status code returned from the write operation
                        ) \
      severity warning high \
      format "Error {} while writing {} of {} bytes to {}" \
      throttle 10

    @ File written
    event FileWritten(
                       file: string size FileNameStringSize @< The file name
                     ) \
      severity activity low \
      format "Wrote file {}"

    # ----------------------------------------------------------------------
    # Telemetry
    # ----------------------------------------------------------------------

    @ The number of buffers received
    telemetry NumBuffersReceived: U32 update on change

    @ The number of bytes written
    telemetry NumBytesWritten: U64 update on change

    @ The number of successful writes
    telemetry NumSuccessfulWrites: U32 update on change

    @ The number of failed writes
    telemetry NumFailedWrites: U32 update on change

    @ The number of errors
    telemetry NumErrors: U32 update on change

  }

}