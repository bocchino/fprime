# DpWriter Component Tests

## 1. Abstract State

### 1.1. Variables

| Variable | Type | Description | Initial Value |
|----------|------|-------------|---------------|
| `NumBuffersReceived` | `OnChangeChannel<U32>` | The number of buffers received | 0 |
| `NumBytesWritten` | `OnChangeChannel<U64>` | The number of bytes written | 0 |
| `NumFailedWrites | `OnChangeChannel<U32>` | The number of failed writes | 0 |
| `NumSuccessfulWrites | `OnChangeChannel<U32>` | The number of successful writes | 0 |
| `bufferInvalidEventCount` | `FwSizeType` | The number of buffer invalid events since the last throttle clear |0 |
| `bufferTooSmallEventCount` | `FwSizeType` | The number of buffer too small events since the last throttle clear |0 |
| `fileOpenErrorEventCount` | `FwSizeType` | The number of file open error events since the last throttle clear |0 |
| `fileOpenStatus` | `Os::File::Status` | The status returned by `Os::File::open` in the test harness | `Os::File::OP_OK` |
| `fileWriteErrorEventCount` | `FwSizeType` | The number of file write error events since the last throttle clear |0 |
| `fileWriteStatus` | `Os::File::Status` | The status returned by `Os::File::write` in the test harness | `Os::File::OP_OK` |
| `invalidPacketDescriptorEventCount` | `FwSizeType` | The number of invalid packet descriptor events since the last throttle clear |0 |

## 2. Rule Groups

### 2.1. FileOpenStatus

This rule group manages the file open status in the test harness.

#### 2.1.1. OK

This rule sets the file open status to `Os::File::OP_OK`, simulating a system state
in which a file open call succeeds.

**Precondition:**
`fileOpenStatus != Os::File::OP_OK`.

**Action:**
`fileOpenStatus = Os::File::OP_OK`.

**Test:**

1. Apply rule `FileOpenStatus::Error`.
1. Apply rule `FileOpenStatus::OK`.

**Requirements tested:**
None (helper rule).

#### 2.1.2. Error

This rule sets the file open status to an error value, simulating a system state
in which a file open call fails.

**Precondition:**
`fileOpenStatus == Os::File::OP_OK`.

**Action:**
Set `fileOpenStatus` to a random value other than `Os::File::OP_OK`.

**Test:**

1. Apply rule `FileOpenStatus::Error`.

**Requirements tested:**
None (helper rule).

### 2.2. FileWriteStatus

This rule group manages the file write status in the test harness.

#### 2.2.1. OK

This rule sets the file open status to `Os::File::OP_OK`, simulating a system state
in which a file write call succeeds.

**Precondition:**
`fileWriteStatus != Os::File::OP_OK`.

**Action:**
`fileWriteStatus = Os::File::OP_OK`.

**Test:**

1. Apply rule `FileWriteStatus::Error`.
1. Apply rule `FileWriteStatus::OK`.

**Requirements tested:**
None (helper rule).

#### 2.2.2. Error

This rule sets the file write status to an error value, simulating a system state
in which a file write call fails.

**Precondition:**
`fileWriteStatus == Os::File::OP_OK`.

**Action:**
Set `fileWriteStatus` to a random value other than `Os::File::OP_OK`.

**Test:**

1. Apply rule `FileWriteStatus::Error`.

**Requirements tested:**
None (helper rule).

### 2.3. SchedIn

This rule group sends test input to the `schedIn` port.

#### 2.3.1. OK

This rule invokes `schedIn` with nominal input.

**Precondition:** `true`

**Action:**

1. Clear history.
1. Invoke `schedIn` with a random context.
1. Check telemetry.

**Test:**

1. Apply rule `SchedIn::OK`.

**Requirements tested:**
`SVC-DPWRITER-006`.

### 2.4. BufferSendIn

This rule group sends test input to the `bufferSendIn` port.

#### 2.4.1. OK

This rule invokes `bufferSendIn` with nominal input.

**Precondition:**
`fileOpenStatus == Os::File::OP_OK` and
`fileWriteStatus == Os::File::OP_OK`.

**Action:**
1. Clear history.
1. Construct a random buffer _B_ with valid packet data.
1. In _B_, randomly set the processing bits.
1. Send _B_ to `bufferSendIn`.
1. Check there are no events.
1. Check output on processing ports.
1. Check output on notification port.
1. Check output on deallocation port.
1. Verify existence and contents of data product file.

**Test:**
1. Apply rule `BufferSendIn::OK`.

**Requirements tested:**
`SVC-DPWRITER-001`,
`SVC-DPWRITER-002`,
`SVC-DPWRITER-003`,
`SVC-DPWRITER-004`,
`SVC-DPWRITER-005`

### 2.5. CLEAR_EVENT_THROTTLE

This rule group tests the `CLEAR_EVENT_THROTTLE` command.

#### 2.5.1. OK

This rule sends the `CLEAR_EVENT_THROTTLE` command.

**Precondition:** `true`

**Action:**

1. Clear the history.
1. Send command `CLEAR_EVENT_THROTTLE`.
1. Check the command response.
1. Assert `DpManagerComponentBase::m_BufferInvalidThrottle` == 0.
1. Set `bufferInvalidEventCount` = 0.
1. Set `bufferTooSmallEventCount` = 0.
1. Set `invalidPacketDescriptorEventCount` = 0.
1. Set `fileOpenErrorEventCount` = 0.
1. Set `fileWriteErrorEventCount` = 0.

**Test:**

1. Apply rule `BufferGetStatus::Invalid`.
1. Apply rule `ProductRequestIn::BufferInvalid` `DpManagerComponentBase::EVENTID_BUFFERALLOCATIONFAILED_THROTTLE` + 1 times.
1. Apply rule `CLEAR_EVENT_THROTTLE::OK`.
1. Apply rule `ProductRequestIn::BufferInvalid`

## 3. Implementation

See [the DpManager test README](../../DpManager/test/ut/README.md)
for a description of the pattern used to implement the tests.
