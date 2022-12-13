module Svc {

  @ A component for developing data product code gen
  active component DpDev {

    # ----------------------------------------------------------------------
    # Data product ports
    # Once we have the code gen in place, these will be special ports
    # ----------------------------------------------------------------------

    @ Data product request port
    output port productRequestOut: Fw.DpBufferRequest

    @ Data product receive port
    async input port productRecvIn: Fw.DpBufferSend

    @ Data product send port
    output port productSendOut: Fw.DpBufferSend

  }

}
