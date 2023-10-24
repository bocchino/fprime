\page SvcDpWriterComponent Svc::DpWriter Component
# Svc::DpWriter (Active Component)

## 1. Introduction

`Svc::DpWriter` is an active component for writing data products to disk.
It does the following:

1. Receive buffers containing filled data products.
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
SVC-DPWRITER-001 | `Svc::DpWriter` shall provide a port for receiving `Fw::Buffer` objects containing filled data products. | The purpose of `DpWriter` is to write the data products to disk. | Unit Test

## 3. Design

### 3.1. Component Diagram

TODO

### 3.2. Ports

`DpWriter` has the following ports:

TODO

### 3.3. State

`DpWriter` maintains the following state:

TODO

### 3.4. Runtime Setup

TODO

### 3.5. Port Handlers

TODO
<a name="ground_interface"></a>
## 4. Ground Interface

TODO

## 5. Example Uses

TODO
