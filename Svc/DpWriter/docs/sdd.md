\page SvcDpWriterComponent Svc::DpWriter Component
# Svc::DpWriter (Active Component)

## 1. Introduction

`Svc::DpWriter` is an active component for writing data products to disk.
It does the following:

1. Receive buffers containing filled data product containers.
The buffers typically come from an instance of
[`Svc::DpManager`](../../DpManager/docs/sdd.md),
either directly or via an instance
of[`Svc::BufferAccumulator`](../../BufferAccumulator/docs/BufferAccumulator.md).

1. For each buffer _B_ received in step 1,

   1. Perform any requested processing, such as data compression, on _B_.

   1. Write _B_ to disk.

## 2. Requirements

Requirement | Description | Rationale | Verification Method
----------- | ----------- | ----------| -------------------
SVC-DPWRITER-001 | `Svc::DpWriter` shall provide a port for receiving `Fw::Buffer` objects pointing to filled data product containers. | The purpose of `DpWriter` is to write the data products to disk. | Unit Test
SVC-DPWRITER-002 | `Svc::DpWriter` shall provide an array of ports for sending `Fw::Buffer` objects for processing. | This requirement supports downstream processing of the data in the buffer. | Unit Test
SVC-DPWRITER-003 | On receiving a data product container _C_, `Svc::DpWriter` shall use the processing type field of the header of _C_ to select the port index to use for processing. An out-of-bounds index shall signify no processing. | This requirement allows the data product producer to control the type of processing done. | Unit Test
SVC-DPWRITER-004 | On receiving an `Fw::Buffer` _B_, and after performing any requested processing on _B_, `Svc::DpWriter` shall write _B_ to disk. _TBD: Should the writes occur in priority order?_ | The purpose of `DpWriter` is to write data products to the disk. | Unit Test
SVC-DPWRITER-005 | When writing a buffer containing a data product _C_ to disk, `DpWriter` shall prepend (1) the priority value stored in the header of _C_ and (2) a hash value guarding the priority value. | This requirement allows another component, such as [`Svc::DpCatalog`](../../DpCatalog/docs/sdd.md), to update the priority without recomputing the hash for _C_. | Unit Test
SVC-DPWRITER-006 | When writing a buffer containing a data product _C_ to disk, `DpWriter` shall append a hash value guarding the data in the buffer. | This requirement allows the ground to verify the integrity of the data in the buffer. | Unit Test
SVC-DPWRITER-007 | `Svc::DpManager` shall provide telemetry that reports the number of data products written. | This requirement establishes the telemetry interface for the component. | Unit test

## 3. Design

### 3.1. Component Diagram

The diagram below shows the `DpWriter` component.

<div>
<img src="img/DpWriter.png" width=700/>
</div>

### 3.2. Ports

`DpWriter` has the following ports:

| Kind | Name | Port Type | Usage |
|------|------|-----------|-------|
| `async input` | `schedIn` | `Svc.Sched` | Schedule in port |
| `async input` | `bufferSendIn` | `Fw.BufferSend` | Port for receiving data products to write to disk |
| `output` | `procBufferSendOut` | `[DpWriterNumProcPorts] Fw.BufferSend` | Port for processing data products |
| `time get` | `timeGetOut` | `Fw.Time` | Time get port |
| `telemetry` | `tlmOut` | `Fw.Tlm` | Telemetry port |
| `event` | `eventOut` | `Fw.Log` | Event port |
| `text event` | `textEventOut` | `Fw.LogText` | Text event port |

### 3.3. State

`DpWriter` maintains the following state:

1. `numDataProducts (U32)`: The number of data products written.

### 3.4. Compile-Time Setup

The configuration constant [`DpWriterNumProcPorts`](../../../config/AcConstants.fpp)
specifies the number of ports for connecting components that perform
processing.

### 3.5. Runtime Setup

The `config` function specifies the following constants:

1. `logFilePrefix (string)`: The prefix to use for log file names.

1. `logFileSuffix (string)`: The suffix to use for log file names.

### 3.6. Port Handlers

#### 3.6.1. schedIn

This handler sends out the state variables as telemetry.

#### 3.6.2. bufferSendIn

This handler receives a mutable reference to a buffer `B`.
It does the following:

1. Check that `B` is valid and that the first `sizeof(FwPacketDescriptorType)`
   bytes of the memory referred to by `B` hold the serialized value
   [`Fw_PACKET_DP`](../../../Fw/Com/ComPacket.hpp).
   If not, emit a warning event and stop processing.

1. Read the `ProcType` field out of the container header stored in the
   memory pointed to by `B`.
   If the value is a valid port number `N` for `procBufferSendOut`, then invoke
   `procBufferSendOut` at port number `N`, passing in `B`.
   This step updates the memory pointed to by `B` in place.

1. Write `B` to a file, using the format described in the [**File 
   Format**](#file_format) section. For the time stamp, use the time
   provided by `timeGetOut`.

<a name="file_format"></a>
## 4. File Format

The following table shows the format of the files written by `Svc::DpWriter`.

|Field Name|Serialized Size|Description|
|----------|---------------|-----------|
|`Priority`|`sizeof(FwDpPriorityType)`|The updated priority.|
|`Priority Hash`|[`HASH_DIGEST_LENGTH`](../../../Utils/Hash/README.md)|The hash value guarding the `Priority` field.|
|`Container Header`|See the definition [here](../../../Fw/Dp/docs/sdd.md).|The container header.|
|`Container Data`|Variable; given by the `DataSize` field in the container header.|The container data.|
|`Container Hash`|[`HASH_DIGEST_LENGTH`](../../../Utils/Hash/README.md)|The hash value guarding the `Container Header` and `Container Data` fields.|

The name of each file consists of `logFilePrefix` followed by a time stamp 
and `logFileSuffix`.
The time stamp consists of an underscore character `_` followed by a seconds 
value, an underscore character, and a microseconds value.
For example, suppose that the log file prefix is `container_data` and the log 
file suffix is `.dat`.
Suppose that the seconds value is 100000 and the microseconds value is 1000.
Then the file name is `container_data_100000_1000.dat`.

<a name="ground_interface"></a>
## 5. Ground Interface

### 5.1. Telemetry

| Name | Type | Description |
|------|------|-------------|
| `NumDataProducts` | `U32` | The number of data products handled |

### 5.2. Events

TODO

## 6. Example Uses

<a name="top-diagrams"></a>
### 6.1. Topology Diagrams

TODO

### 6.2. Sequence Diagrams

TODO
