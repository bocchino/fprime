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
`bufferGetStatus != VALID`

**Action:**
`bufferGetStatus = VALID`

**Test:**

1. Apply rule `BufferGetStatus::Invalid`.
1. Apply rule `BufferGetStatus::Valid`.

**Requirements tested:**
None (helper rule).

#### 2.1.2. Invalid

Sets the buffer get status to valid.

**Precondition:**
TODO

**Action:**
TODO

**Test:**
TODO

**Requirements tested:**
None (helper rule).


### 2.2. ProductRequestIn

This rule group sends test input to the `productRequestIn` port.

#### 2.2.1. BufferInvalid

Invokes `productRequestIn` in a state where the test harness returns
an invalid buffer.

**Precondition:**
TODO

**Action:**
TODO

**Test:**
TODO

**Requirements tested:**
TODO


#### 2.2.2. BufferValid

Invokes `productRequestIn` in a state where the test harness returns
a valid buffer.

**Precondition:**
TODO

**Action:**
TODO

**Test:**
TODO

**Requirements tested:**
TODO

### 2.3. SchedIn

This rule group sends test input to the `schedIn` port.

#### 2.3.1. OK

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
