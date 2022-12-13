module Fw {

  @ Port for sending a request for a data product buffer
  port DpBufferRequest(
      @ The buffer ID. Matches the container ID.
      $id: FwDpIdType
      @ The size of the requested buffer
      $size: FwDpBuffSizeType
  )

  @ Port for sending a data product buffer
  port DpBufferSend(
      @ The buffer ID. Matches the container ID.
      $id: FwDpIdType
      @ The buffer
      buffer: Fw.Buffer
  )

}
