\page SvcDpManagerComponent Svc::DpManager Component
# Svc::DpManager (Active Component)

## 1. Introduction

`Svc::DpManager` is an active component for managing data products.
It does the following:

1. Receive requests for buffers to hold data products.

   1.  When a client component synchronously requests a data product buffer, 
       request an [`Fw::Buffer`](../../../Fw/Buffer/docs/sdd.md)
       from a buffer manager.
       Return the buffer to the client component so the component can fill it.

   1.  When a client component asynchronously requests a data product buffer, 
       request an [`Fw::Buffer`](../../../Fw/Buffer/docs/sdd.md)
       from a buffer manager.
       Send the buffer to the client component so the component can fill it.

1. Receive buffers filled with data products by
client components.
Upon receiving a buffer, send the buffer out on a port.
Another component such as
[`Svc::BufferAccumulator`](../../BufferAccumulator/docs/BufferAccumulator.md)
or [`Svc::DpWriter`](../../DpWriter/docs/sdd.md)
will process the buffer and then send it back to the buffer manager
for deallocation.

## 2. Requirements

Requirement | Description | Rationale | Verification Method
----------- | ----------- | ----------| -------------------
SVC-DPMANAGER-001 | `Svc::DpManager` shall provide ports for receiving and asynchronously responding to requests for data product buffers. | This capability supports the `product` `request` and `product` `recv` ports in the auto-generated code for components that define data products. | Unit test
SVC-DPMANAGER-002 | `Svc::DpManager` shall provide a port for synchronously requesting and receiving data product buffer. | This capability supports the `product` `get` port in the auto-generated code for components that define data products. | Unit test
SVC-DPMANAGER-003 | `Svc::DpManager` shall receive data product buffers and forward them for further processing. | This requirement provides a pass-through capability for sending data product buffers to downstream components. `Svc::DpManager` receives data product input on a port of type  `Fw::DpSend`. This input consists of a container ID and an `Fw::Buffer` _B_. `Svc::DpManager` sends _B_ on a port of type `Fw::BufferSend`. This port type is used by the standard F Prime components for managing and logging data, e.g., `Svc::BufferLogger`. | Unit test
SVC-DPMANAGER-004 | `Svc::DpManager` shall provide the ground interface described in the [Ground Interface section](#ground_interface) below. | This requirement establishes the ground interface for the component. | Unit test

## 3. Design

### 3.1. Component Diagram

The diagram below shows the `DpManager` component.

<div>
<img src="img/DpManager.png" width=700/>
</div>

### 3.2. Ports

`DpManager` has the following ports:

| Kind | Name | Port Type | Usage |
|------|------|-----------|-------|
| `async input` | `schedIn` | `Svc.Sched` | Schedule in port |
| `sync input` | `productGetIn` | `Fw.DpGet` | Port for responding to a data product get from a client component |
| `async input` | `productRequestIn` | `Fw.DpRequest` | Port for receiving data product buffer requests from a client component |
| `output` | `productResponseOut` | `Fw.DpResponse` | Port for sending requested data product buffers to a client component |
| `output` | `bufferGetOut` | `Fw.BufferGet` | Port for getting buffers from a Buffer Manager |
| `async input` | `productSendIn` | `Fw.DpSend` | Port for receiving filled data product buffers from a client component |
| `output` | `productSendOut` | `Fw.BufferSend` | Port for sending filled data product buffers to a downstream component |
| `time get` | `timeGetOut` | `Fw.Time` | Time get port |
| `telemetry` | `tlmOut` | `Fw.Tlm` | Telemetry port |
| `event` | `eventOut` | `Fw.Log` | Event port |
| `text event` | `textEventOut` | `Fw.LogText` | Text event port |

### 3.3. State

`DpManager` maintains the following state:

1. `numSuccessfulAllocations`: The number of successful buffer allocations.

1. `numFailedAllocations`: The number of failed buffer allocations.

1. `numDataProducts`: The number of data products handled.

1. `numBytes:` The number of bytes handled.

### 3.4. Runtime Setup

No special runtime setup is required.

### 3.5. Port Handlers

#### 3.5.1. schedIn

The handler for this port sends out the state variables as telemetry.

#### 3.5.2. productGetIn

This port receives a container ID `id`, a requested buffer size `size`,
and a mutable reference to a buffer `B`.
It does the following:

1. Set `status = FAILURE`.

1. Invoke `bufferGetOut` to get a buffer `B'`.

1. If `B'` is valid, then set `B = B'`, increment `numAllocations`,
   and set `status = SUCCESS`.

1. Otherwise increment `numFailedAllocations` and emit a warning event.

1. Return `status`.

#### 3.5.3. productRequestIn

This port receives a container ID `id` and a requested buffer size `size`.
It does the following:

1. Initialize the local variable `B` with an invalid buffer.

1. Set `status = productGetIn`handlerBase(id, size, B)`.

1. Send `(id, B, status)` on `productResponseOut`.

#### 3.5.4. productSendIn

This port receives a data product ID `I` and a buffer `B`.
It does the following:

1. Update `numDataProducts` and `numBytes`.

1. Send `B` on `productSendOut`.

<a name="ground_interface"></a>
## 4. Ground Interface

### 4.1. Telemetry

| Name | Type | Description |
|------|------|-------------|
| `NumSuccessfulAllocations` | `U32` | The number of successful buffer allocations |
| `NumFailedAllocations` | `U32` | The number of failed buffer allocations |
| `NumDataProds` | `U32` | Number of data products handled |
| `NumBytes` | `U32` | Number of bytes handled |

### 4.2. Events

| Name | Severity | Description |
|------|----------|-------------|
| `BufferAllocationFailed` | `warning high` | Buffer allocation failed |

## 5. Example Uses

<a name="top-diagrams"></a>
### 5.1. Topology Diagrams

The following topology diagrams show how to connect `Svc::DpManager`
to a client component, a buffer manager, and a data product writer.
The diagrams use the following instances:

* `dpWriter`: An instance of [`Svc::DpWriter`](../../DpWriter/docs/sdd.md).

* `bufferManager`: An instance of [`Svc::BufferManager`](../../BufferManager/docs/sdd.md).

* `client`: A client component that generates data products.
`productRequestOut` is the special `product request` port.
`productRecvIn` is the special `product recv` port.

* `dpManager`: An instance of `Svc::DpManager`.

#### 5.1.1. Requesting Data Product Buffers

<div>
<img src="img/top/buffer-request.png" width=800/>
</div>

#### 5.1.2. Sending Data Products

<div>
<img src="img/top/product-send.png" width=1000/>
</div>

### 5.2. Sequence Diagrams

#### 5.2.1. Requesting a Data Product Buffer

```mermaid
sequenceDiagram
    activate client
    activate dpManager
    client-)dpManager: Request buffer [productRequestIn]
    dpManager->>bufferManager: Request buffer B [bufferGetOut]
    bufferManager-->>dpManager: Return B
    dpManager-)client: Send B [productResponseOut]
    deactivate dpManager
    deactivate client
```

#### 5.2.2. Sending a Data Product

```mermaid
sequenceDiagram
    activate client
    activate dpManager
    activate dpWriter
    client-)dpManager: Send buffer B [productSendIn]
    dpManager-)dpWriter: Send B [productSendOut]
    dpWriter->>bufferManager: Deallocate B
    bufferManager-->>dpWriter: Return
    deactivate dpWriter
    deactivate dpManager
    deactivate client
```
