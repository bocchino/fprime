# DpManager Component Tests

## 1. Abstract State

### 1.1. Types

* `BufferGetStatus`: The status of the `bufferGet` response in
  the test harness (`VALID` or `INVALID`).

* `OnChangeChannel<T>`: A model of an on-change telemetry channel that
  stores type `T`.

### 1.2. Variables

| Variable | Type | Description | Initial Value |
|----------|------|-------------|---------------|
| `bufferGetStatus` | `BufferGetStatus` | The buffer get status | `VALID` |
| `NumSuccessfulAllocations` | `OnChangeChannel<U32>` | The number of successful buffer allocations | 0 |
| `NumFailedAllocations` | `OnChangeChannel<U32>` | The number of failed buffer allocations | 0 |
| `NumDataProducts` | `OnChangeChannel<U32>` | The number of data products handled | 0 |
| `NumBytes` | `OnChangeChannel<U32>` | The number of bytes handled | 0 |

## 2. Rule Groups

### 2.1. BufferGetStatus

This rule group manages the buffer get status in the test harness.

#### 2.1.1. Valid

TODO

#### 2.1.2. Invalid

TODO

### 2.2. ProductRequestIn

This rule group sends test input to the `productRequestIn` port.

#### 2.2.1. BufferInvalid

TODO

#### 2.2.2. BufferValid

TODO

### 2.3. SchedIn

This rule group sends test input to the `schedIn` port.

#### 2.3.1. OK
