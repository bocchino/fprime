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

Sets the buffer get status to valid.

**Precondition:**
`bufferGetStatus != VALID`.

**Action:**
`bufferGetStatus = VALID`.

**Test:**

1. Apply rule `BufferGetStatus::Invalid`.
1. Apply rule `BufferGetStatus::Valid`.

**Requirements tested:**
None (helper rule).

#### 2.1.2. Invalid

Sets the buffer get status to invalid.

**Precondition:**
`bufferGetStatus != INVALID`.

**Action:**
`bufferGetStatus = INVALID`.

**Test:**
Apply rule `BufferGetStatus::Invalid`.

**Requirements tested:**
None (helper rule).


### 2.2. ProductRequestIn

This rule group sends test input to the `productRequestIn` port.

#### 2.2.1. BufferInvalid

Invokes `productRequestIn` in a state where the test harness returns
an invalid buffer.

**Precondition:**
`bufferGetStatus == INVALID`.

**Action:**
TODO

**Test:**
TODO

**Requirements tested:**
`SVC-DPMANAGER-001`.

#### 2.2.2. BufferValid

Invokes `productRequestIn` in a state where the test harness returns
a valid buffer.

**Precondition:**
`bufferGetStatus == VALID`.

**Action:**

1. Clear history.
1. Invoke `productRequestIn` with a random id and size.
1. Assert that the event history is empty.
1. Assert that the from port history contains two items.
1. Assert that the `from_bufferGetOut` history contains one item.
1. Assert that the `from_productResponseOut` history contains one item.
1. Assert that the `from_productResponseOut` history contains the
   expected buffer value and status `SUCCESS` at index zero.

**Test:**

1. Apply rule `ProductRequestIn::BufferValid`.
1. Apply rule `SchedIn::OK`.

**Requirements tested:**
`SVC-DPMANAGER-001`, `SVC-DP-MANAGER-003`.

### 2.3. ProductSendIn

This rule group sends test input to the `productSendIn` port.

#### 2.3.1. OK

Invokes `productSendIn` with nominal input.

**Precondition:**
TODO

**Action:**
TODO

**Test:**
TODO

**Requirements tested:**
`SVC-DPMANAGER-002`.

### 2.4. SchedIn

This rule group sends test input to the `schedIn` port.

#### 2.4.1. OK

Invokes `schedIn` with nominal input.

**Precondition:** `true`

**Action:**

1. Clear history.
1. Invoke `schedIn` with a random context.
1. Check telemetry.

**Test:**

1. Apply rule `SchedIn::OK`.

**Requirements tested:**
`SVC-DPMANAGER-003`.
