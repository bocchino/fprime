// ======================================================================
// @file   String.hpp
// @author F Prime
// @brief  A general purpose string backed by a fixed-size buffer
// ======================================================================

#ifndef FW_STRING_HPP
#define FW_STRING_HPP

#include <FpConfig.hpp>

#include "Fw/Cfg/SerIds.hpp"
#include "Fw/Types/StringBase.hpp"

namespace Fw {

class String : public StringBase {
  public:
    enum {
        SERIALIZED_TYPE_ID = FW_TYPEID_FIXED_LENGTH_STRING,
        STRING_SIZE = FW_FIXED_LENGTH_STRING_SIZE,
        SERIALIZED_SIZE = STRING_SIZE + sizeof(FwSizeStoreType)
    };

    String() : StringBase() { *this = ""; }

    String(const String& src) : StringBase() { *this = src; }

    String(const StringBase& src) : StringBase() { *this = src; }

    String(const char* src) : StringBase() { *this = src; }

    String& operator=(const String& src) {
        (void)StringBase::operator=(src);
        return *this;
    }

    String& operator=(const StringBase& src) {
        (void)StringBase::operator=(src);
        return *this;
    }

    String& operator=(const char* src) {
        (void)StringBase::operator=(src);
        return *this;
    }

    const char* toChar() const { return this->m_buf; }

    StringBase::SizeType getCapacity() const { return sizeof this->m_buf; }

  private:
    char m_buf[String::STRING_SIZE];
};
}  // namespace Fw

#endif
