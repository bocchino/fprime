module Fw {

  @ Port for sending a request for a buffer that will hold a data product
  port DpBufferRequest(
      @ The buffer ID. Matches the container ID.
      $id: FwDpIdType
      @ The size of the requested buffer
      $size: FwDpBuffSizeType
  )

  @ TODO
  port DpBufferSend

}
