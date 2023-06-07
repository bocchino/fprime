\page FwDp Framework Support for Data Products
# Framework Support for Data Products

## 1. Introduction

This build module defines FPP ports and C++ classes that support
the collection and storage of data products.

## 2. FPP Ports

This module defines the following FPP ports:

1. `DpRequest`: A port for sending a request for a data product buffer to back 
   a data product container.

2. `DpResponse`: A port for receiving a response to a buffer request.

3. `DpSend`: A port for sending a data product buffer.

For more information, see the file [`Dp.fpp`](../Dp.fpp) in the parent 
directory.

## 3. C++ Classes

This module defines a C++ class `DpContainer`.
`DpContainer` is the base class for a data product container.
When you specify a container _C_ in an FPP component model, 
the auto-generated C++ for the component defines a container
class for _C_.
The container class is derived from `DpContainer`.
It provides all the generic operations defined in `DpContainer`
plus the operations that are specific to _C_, for example
serializing the specific types of data that _C_ can store.

### 3.1. Serialized Container Format

In serialized form, each data product container consists of a header 
followed by a data payload.

#### 3.1.1. Header

The data product header has the following format.

|Field Name|Data Type|Serialized Size|Description|
|----------|---------|---------------|-----------|
|`PacketDescriptor`|`FwPacketDescriptorType`|`sizeof(FwPacketDescriptorType)`|The F Prime packet descriptor `FW_PACKET_DP`.|
|`Id`|`FwDpIdType`|`sizeof(FwDpIdType)`|The container ID|
|`Priority`|`FwDpPriorityType`|`sizeof(FwDpPriorityType)`|The container default priority|
|`TimeTag`|`Fw::Time`|`Fw::Time::SERIALIZED_SIZE`|The time tag associated with the container|
|`DataSize`|`FwSizeType`|`sizeof(FwSizeType)`|The size of the data payload in bytes|

#### 3.1.2. Data Payload

The data payload is a sequence of records.
The serialized format of each record _R_ depends on whether _R_ is a typed
record or a raw record.

**Typed records:**
A typed record is specified in FPP in the form `product record` _name_ `:` _type_.
It represents one item of data of type _type_.
Typed records with type _T_ have the following format:

|Field Name|Data Type|Serialized Size|Description|
|`Id`|`FwDpIdType`|`sizeof(FwDpIdType)`|The record ID|
|`Data`|_T_|sizeof(_T_) if _T_ is a primitive type; otherwise _T_`::SERIALIZED_SIZE`|The serialized data|

**Raw records:**
A raw record is specified in FPP in the form `product record` _name_ `: raw`.
It represents raw byte data.
Raw records have the following format:

|Field Name|Data Type|Serialized Size|Description|
|`Id`|`FwDpIdType`|`sizeof(FwDpIdType)`|The record ID|
|`Size`|`FwSizeType`|`sizeof(FwSizeType)`|The number _n_ of bytes in the record|
|`Data`|Array of bytes|_n_|_n_ bytes of raw data|

### 3.2. Further Information

For more information, see the file [`DpContainer.hpp`](../DpContainer.hpp) in 
the parent directory.
