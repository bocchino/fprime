\page FwDp Framework Support for Data Products
# Framework Support for Data Products

## 1. Introduction

This build module defines FPP ports and C++ classes that support
the collection and storage of data products.
For more information on data products and records, see the
[data products documentation](../../../docs/Design/data-products.md).

## 2. Configuration

The following types and constants are configurable via the file
[`config/DpCfg.hpp`](../../../config/DpCfg.hpp):

| Name | Kind | Description |
| ---- | ---- | ---- |
| `Fw::DpCfg::ProcId` | Type | The type of the identifier for the kind of processing to perform on a container before writing it to disk. |
| `Fw::DpCfg::CONTAINER_DATA_SIZE` | Constant | The size of the user-configurable data in the container packet header. |

## 3. FPP Ports

This module defines the following FPP ports:

1. `DpGet`: A port for synchronously getting a buffer to back
   a data product container.

1. `DpRequest`: A port for sending a request for a buffer to back
   a data product container.

1. `DpResponse`: A port for receiving a response to a buffer request.

1. `DpSend`: A port for sending a buffer holding data products.

For more information, see the file [`Dp.fpp`](../Dp.fpp) in the parent
directory.

## 4. C++ Classes

This module defines a C++ class `DpContainer`.
`DpContainer` is the base class for a data product container.
When you specify a container _C_ in an FPP component model,
the auto-generated C++ for the component defines a container
class for _C_.
The container class is derived from `DpContainer`.
It provides all the generic operations defined in `DpContainer`
plus the operations that are specific to _C_, for example
serializing the specific types of data that _C_ can store.

### 4.1. Serialized Container Format

In serialized form, each data product container consists of a header
followed by a data payload.

#### 4.1.1. Header

The data product header has the following format.

|Field Name|Data Type|Serialized Size|Description|
|----------|---------|---------------|-----------|
|`PacketDescriptor`|`FwPacketDescriptorType`|`sizeof(FwPacketDescriptorType)`|The F Prime packet descriptor [`FW_PACKET_DP`](../../../Fw/Com/ComPacket.hpp)|
|`Id`|`FwDpIdType`|`sizeof(FwDpIdType)`|The container ID|
|`Priority`|`FwDpPriorityType`|`sizeof(FwDpPriorityType)`|The container default priority|
|`TimeTag`|`Fw::Time`|`Fw::Time::SERIALIZED_SIZE`|The time tag associated with the container|
|`ProcType`|`Fw::DpCfg::ProcType`|`Fw::DpCfg::ProcType::SERIALIZED_SIZE`|The processing type|
|`UserData`|Array of `U8`|Fw::DpCfg::CONTAINER_USER_DATA_SIZE`|User-configurable data|
|`DataSize`|`FwSizeType`|`sizeof(FwSizeType)`|The size of the data payload in bytes|

#### 4.1.2. Data Payload

The data payload is a sequence of records.
The serialized format of each record _R_ depends on whether _R_ is a typed
record or a raw record.

**Typed records:**
A typed record is specified in FPP in the form `product record` _name_ `:` _type_.
The record has name _name_ and represents one item of data of type _type_.
The type may be a struct type with several fields or an array type with
several indexed elements.
Typed records with type _T_ have the following format:

|Field Name|Data Type|Serialized Size|Description|
|----------|---------|---------------|-----------|
|`Id`|`FwDpIdType`|`sizeof(FwDpIdType)`|The record ID|
|`Data`|_T_|`sizeof(`_T_`)` if _T_ is a primitive type; otherwise _T_`::SERIALIZED_SIZE`|The serialized data|

**Raw records:**
A raw record is specified in FPP in the form `product record` _name_ `: raw`.
The record has name _name_ and represents raw byte data.
Raw records have the following format:

|Field Name|Data Type|Serialized Size|Description|
|----------|---------|---------------|-----------|
|`Id`|`FwDpIdType`|`sizeof(FwDpIdType)`|The record ID|
|`Size`|`FwSizeType`|`sizeof(FwSizeType)`|The number _n_ of bytes in the record|
|`Data`|Array of bytes|_n_|_n_ bytes of raw data|

### 4.2. Further Information

For more information on the `DpContainer` class, see the file [`DpContainer.hpp`](../DpContainer.hpp) in
the parent directory.
