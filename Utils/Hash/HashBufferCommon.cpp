#include <Utils/Hash/HashBuffer.hpp>
#include <cstring>

#include "Fw/Types/Serializable.hpp"

namespace Utils {

HashBuffer::HashBuffer() {}

HashBuffer::HashBuffer(const U8* args, NATIVE_UINT_TYPE size) {
    Fw::SerializeStatus stat = Fw::SerializeBufferBase::setBuff(args, size);
    FW_ASSERT(Fw::FW_SERIALIZE_OK == stat, static_cast<NATIVE_INT_TYPE>(stat));
}

HashBuffer::~HashBuffer() {}

HashBuffer::HashBuffer(const HashBuffer& other) : Fw::SerializeBufferBase() {
    Fw::SerializeStatus stat = Fw::SerializeBufferBase::setBuff(other.m_bufferData, other.getBuffLength());
    FW_ASSERT(Fw::FW_SERIALIZE_OK == stat, static_cast<NATIVE_INT_TYPE>(stat));
}

HashBuffer& HashBuffer::operator=(const HashBuffer& other) {
    if (this == &other) {
        return *this;
    }

    Fw::SerializeStatus stat = Fw::SerializeBufferBase::setBuff(other.m_bufferData, other.getBuffLength());
    FW_ASSERT(Fw::FW_SERIALIZE_OK == stat, static_cast<NATIVE_INT_TYPE>(stat));
    return *this;
}

bool HashBuffer::operator==(const HashBuffer& other) const {
    if ((this->getBuffLength() == other.getBuffLength()) &&
        (memcmp(this->getBuffAddr(), other.getBuffAddr(), this->getBuffLength()) != 0)) {
        return false;
    }
    return true;
}

bool HashBuffer::operator!=(const HashBuffer& other) const {
    return !(*this == other);
}

const U8* HashBuffer::getBuffAddr() const {
    return this->m_bufferData;
}

U8* HashBuffer::getBuffAddr() {
    return this->m_bufferData;
}

NATIVE_UINT_TYPE HashBuffer::getBuffCapacity() const {
    return sizeof(this->m_bufferData);
}

U32 HashBuffer::asBigEndianU32() const {
    U32 result = 0;
    const FwSignedSizeType bufferSize = sizeof this->m_bufferData;
    const FwSignedSizeType numBytes = (bufferSize < sizeof(U32)) ? bufferSize : sizeof(U32);
    for (FwSignedSizeType i = numBytes - 1; i >= 0; i--) {
        result <<= 8;
        FW_ASSERT((i >= 0) && (i < bufferSize), static_cast<FwAssertArgType>(i),
                  static_cast<FwAssertArgType>(bufferSize));
        result += this->m_bufferData[i];
    }
    return result;
}
}  // namespace Utils
