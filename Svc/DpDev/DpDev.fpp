module Svc {

  @ A component for developing data product code gen
  active component DpDev {

    # ---------------------------------------------------------------------- 
    # Types
    # ---------------------------------------------------------------------- 

    @ Data for a DataRecord
    struct Data {
      @ An F32 field
      field1: F32
    }

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
    # Records
    # ---------------------------------------------------------------------- 

    @ Record 1
    product record U32Record: U32

    @ Record 2
    product record DataRecord: Data

    # ----------------------------------------------------------------------
    # Containers
    # ----------------------------------------------------------------------

    @ Container 1
    product container Container1

    @ Container 2
    product container Container2

  }

}
