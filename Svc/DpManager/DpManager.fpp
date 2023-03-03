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

    @ Port for sending requested buffers
    output port dpBufferSendOut: Fw.DpBufferSend

    # ---------------------------------------------------------------------- 
    # Special ports
    # ---------------------------------------------------------------------- 

    # TODO


  }

}
