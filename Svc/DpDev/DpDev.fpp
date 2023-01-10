module Svc {

  @ A component for developing data product code gen
  active component DpDev {

    # ----------------------------------------------------------------------
    # Data product ports
    # ----------------------------------------------------------------------

    @ Data product request port
    product request port productRequestOut

    @ Data product receive port
    async product recv port productRecvIn

    @ Data product send port
    product send port productSendOut

    # ----------------------------------------------------------------------
    # Containers
    # ----------------------------------------------------------------------

    @ Container 1
    product container Container1

    @ Container 2
    product container Container2

  }

}
