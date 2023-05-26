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
For example, it may be a struct, an array of typed objects of
statically known size, or an array of bytes of statically unknown size.
A container has an identifier and a priority and stores records.

The set of all containers forms the **data product dictionary**.
To manage the data product dictionary, F Prime uses the same general approach
as for commands, telemetry, events, and parameters:

1. Each component _C_ defines records and containers.
The container IDs are local to _C_.
Typically they have the values 0, 1, 2, ... .

2. Each instance _I_ of _C_ contributes one container _I.c_ to the 
dictionary for each container _c_ defined in _C_.
The global identifier for _I.c_ is the base identifier of _I_ plus
the local identifier for _c_.
For example, if the base identifier is 0x1000, then the global identifiers
might be 0x1000, 0x1001, 0x1002, ... .

3. For any topology _T_, the global identifiers _I.c_ for all the instances _T_
form the data product dictionary for _T_.

### 2.2. F' Components

Typically a data product system in an F' application consists of the following
components:

1. One or more **data product producers**.
   These components produce data products and are typically mission-specific.
   For example, they may produce science data.

1. Standard F Prime components for managing data products.

   1. A **data product manager**.
      This component allocates memory for empty containers.
      It also forwards filled containers to the data product writer.
      See [`Svc::DpManager`](../../Svc/DpManager/docs/sdd.md).

   1. A **data product writer**.
      This component receives filled containers from data product
      producers. It writes the contents of the containers to non-volatile
      storage. (TBR)
      See TODO.

   1. A **data product catalog**.
      This component maintains a database of available data
      products. By command, it downlinks and deletes data products. (TBR)
      See TODO.

Note that when using data products, you need to develop only the
producer components. The other components are provided by F'.

## 3. Producer Components

In this section we provide more detail about producer components.

### 3.1. FPP Modeling

First we summarize the features of the FPP modeling
language used in constructing data product producer components.
Each of these features is fully documented in _The FPP User's Guide_
and _The FPP Language Specification_.

#### 3.1.1. Ports

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

Each data product producer component must have each of these ports
in its FPP component model.

#### 3.1.2. Records

A record is a unit of data.
When defining a producer component, you can specify one or more
records.
A record specification consists of a name, a type, and an optional identifier.
The type specifier may be `raw`, in which case the record
is a raw array of bytes, of statically unknown size.
Example syntax:
```
array FixedSizeData = [1024] F32
product record FixedSizedataRecord: FixedSizeData
product record RawDataRecord: raw
```

#### 3.1.3. Containers

A container is a data structure that stores records.
When defining a producer component, you can specify one or more containers.
Each container specified in a component can store
any of the records specified in the component.

A container specification consists of a name, an optional
identifier, and an optional default priority.
The default priority is the priority to use if no
other priority is specified for the container
during ground operations.
Example syntax:
```
product container C1
product container C2 default priority 10
```

### 3.2. Autocoded C++

The autocoded C++ base class for a producer component _C_ provides
the following API elements:

1. Enumerations defining the available container IDs, container
priorities, and record IDs.

1. A member class _C_ `::DpRecord`. This class is derived from
[`Fw::DpRecord`](../../Fw/Dp/docs/sdd.md).
Each instance of _C_ `::DpRecord` is a wrapper for an `Fw::Buffer` _B_,
which points to allocated memory.
The class provides operations for serializing the records
defined in _C_ into the memory pointed to by _B_.
There is one operation _C_ `::DpRecord::serialize_` _R_
for each record _R_ defined in _C_.

1. A member function `Dp_Request` for requesting a fresh
data product container.
This function takes a container ID and a size.
It sends out a request on `productRequestOut`, which is
typically connected to a data product manager component.

1. For each container _c_ defined in _C_, a pure virtual
member function `Dp_Recv_` _c_ `_handler`.
When a fresh container arrives in response to a
`Dp_Request` invocation, the autocoded C++ uses the container ID to
select and invoke the appropriate `Dp_Recv` handler.
The implementation of _C_ must override each handler
to provide the mission-specific behavior for filling
in the corresponding container.
The arguments to `Dp_Recv_` _c_ `_handler` provide
(1) a reference to the container, which the implementation can fill in;
and (2) a status value indicating whether the container
is valid. An invalid container can result if the buffer
allocation fails.

1. A member function `Dp_Send` for sending a filled
data product container.
This function takes a reference to a container _c_ and an
optional time tag.
It does the following:

   1. If no time tag is provided, then invoke `timeGetOut`
      to get the system time and use it to set the time tag.

   1. Stores the time tag into _c_.

   1. Send _c_ on `productSendOut`.

## 4. Use Cases

In this section we discuss several common use cases involving
data products.

**Requesting and sending data products:**
See the example uses in the documentation for
[`Svc::DpManager`](../..Svc/DpManager/docs/sdd.md#5-example-uses).
The component referred to as `client` in that document
is a data product producer.

**Writing data products to non-volatile storage:**
TODO

**Cataloging and downlinking data products:**
TODO
