# Data Products

## 1. Introduction

F' provides several features for managing the generation, storage,
and downlink of data products.
In this section, we document those features.

## 2. Basic Concepts

First we explain some basic concepts.

### 2.1. Records, Containers, and Dictionaries

F' data products are based on **records** and **containers**.
A record specifies the shape of a data element.
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

3. The global identifiers _I.c_ for all the instances in a topology _T_ form
the data product dictionary for _T_.

### 2.2. F' Components

A data product system typically consists of the following interacting
components:

1. One or more **producer** components that produce data products.
   These components are typically mission-specific.
   For example, they may produce science data.

2. A **data product manager** component.
   T

The general procedure for managing data products is as follows:

1. Each producer component does the following:

   a. Request an empty container _c_ from a data product manager component.

   b. Fill _c_ by serializing records into it.

   c. Send _c_ to a data product writer component.

2. The data product writer receives filled data product containers
   from one or more producer components and writes them to
   non-volatile storage.

3. The data product catalog manages a database of data products
   that are available for downlink.

## 3. FPP Models

In this section we summarize the features of the FPP modeling
language that support data products.
These features are fully documented in _The FPP User's Guide_
and _The FPP Language Specification_.

### 3.1. Ports

FPP provides the following special ports for managing data products:

1. A **product request port** of type `Fw::DpRequest`.
   This is an output port for requesting an emnpty container from a
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
   ```

   
The port definitions are documented [here](../../Fw/Dp/docs/sdd.md).

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
