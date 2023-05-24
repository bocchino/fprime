# Data Products

## 1. Introduction

F' provides several features for managing the generation, storage,
and downlink of data products.
In this section, we document those features.

## 2. Basic Concepts

First we explain some basic concepts.

### 2.1. Records, Containers, and Dictionaries

F' data products are based on **records** and **containers**.
A record is a basic unit of data.
For example, it may be a struct, an array of statically known size,
or an array of dynamically known size.
A container has an identifier and a priority and stores records.

The set of all containers forms the **data product dictionary**.
To manage the data product dictionary, F Prime uses the same general approach
as for commands, telemetry, events, and parameters:

1. Each component _C_ defines records and containers.
The container IDs are local to _C_.

2. Each component instance _I_ of _C_ contributes one container _I.c_ to the 
dictionary for each container _c_ defined in _C_.
The identifier for _I.c_ is the base identifier of _I_ plus
the local identifier for _c_.

3. Given a topology _T_, the global identifiers _I.c_ for all the instances _T_
form the data product dictionary for _T_.

### 2.2. F' Components

Typically a data product system in an F' application consists of the following
components:

1. One or more **data product producers**.
   These components produce data products and are typically mission-specific.
   For example, they may produce science data.

2. A **data product manager**.
   This component allocates memory for empty containers.
   It also forwards filled containers to the data product writer.

3. A **data product writer**.
   This component receives filled containers from data product
   producers. It writes the contents of the containers to non-volatile
   storage. (TBR)

4. A **data product catalog**.
   This component maintains a database of available data
   products. By command, it downlinks and deletes data products. (TBR)

## 3. FPP Models

In this section we summarize the features of the FPP modeling
language that support data products.
These features are fully documented in _The FPP User's Guide_
and _The FPP Language Specification_.

### 3.1. Ports

FPP provides the following special ports for managing data products:

1. A **product request port** of type `Fw::DpRequest`.
   This is an output port for requesting an empty container from a
   data product manager. Example syntax:
   ```
   product request port productRequestOut
   ```

2. A **product receive port** of type `Fw::DpResponse`.
   This is an input port for receiving an empty container in response
   to a request. Example syntax:
   ```
   async product recv port productRecvIn
   ```

3. A **product send port** of type `Fw::DpSend`.
   This is an output port for sending a filled container
   to a data product writer. Example syntax:
   ```
   product send port productSendOut
   ```
   
The port types are documented [here](../../Fw/Dp/docs/sdd.md).

### 3.2. Records

TODO

### 3.3. Containers

TODO

## 4. Autocoded C++

TODO

1. **Special ports:** When defining an FPP component that manages
data products, you must specify the following port instances:

   a. A port in

TODO
