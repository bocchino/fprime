module Svc {

  @ A component for developing data product code gen
  active component DpDev {

    # ---------------------------------------------------------------------- 
    # Types
    # ---------------------------------------------------------------------- 

    @ Data for a DataRecord
    struct Data {
      @ A U32 field
      u32Field: U32
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
    # General ports
    # ---------------------------------------------------------------------- 

    @ A schedIn port to run the data product generation
    async input port schedIn: Svc.Sched

    # ---------------------------------------------------------------------- 
    # Records
    # ---------------------------------------------------------------------- 

    @ Record 1
    product record U32Record: U32 id 100

    @ Record 2
    product record DataRecord: Data id 200

    # ----------------------------------------------------------------------
    # Containers
    # ----------------------------------------------------------------------

    @ Container 1
    product container Container1 id 300

    @ Container 2
    product container Container2 id 400

  }

}
