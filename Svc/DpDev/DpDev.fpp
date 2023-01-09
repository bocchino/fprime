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

    # ----------------------------------------------------------------------
    # Containers
    # Commented out for now because we don't have the special ports in place
    # ----------------------------------------------------------------------

    #@ Container 1
    #product container Container1

    #@ Container 2
    #product container Container2

  }

}
