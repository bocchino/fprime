#ifndef FW_FILENAMESTRING_HPP
#define FW_FILENAMESTRING_HPP

#include "Fw/Cfg/SerIds.hpp"
#include "Fw/Types/StringType.hpp"
#include "config/FpConfig.hpp"
#include "config/FppConstantsAc.hpp"

namespace Fw {

    class FileNameString : public Fw::StringBase {
        public:

            enum {
                SERIALIZED_TYPE_ID = FW_TYPEID_FIXED_LENGTH_STRING, //!< typeid for string type
                STRING_SIZE = FW_FIXED_LENGTH_STRING_SIZE, //!< Storage for string
                SERIALIZED_SIZE = STRING_SIZE + sizeof(FwBuffSizeType) //!< Serialized size is size of buffer + size field
            };

            FileNameString(const char* src); //!< char* source constructor
            FileNameString(const StringBase& src); //!< other string constructor
            FileNameString(const FileNameString& src); //!< String string constructor
            FileNameString(); //!< default constructor
            FileNameString& operator=(const FileNameString& other); //!< assignment operator
            FileNameString& operator=(const StringBase& other); //!< other string assignment operator
            FileNameString& operator=(const char* other); //!< char* assignment operator
            ~FileNameString(); //!< destructor

            const char* toChar() const; //!< gets char buffer
            NATIVE_UINT_TYPE getCapacity() const ; //!< return buffer size

        private:

            char m_buf[FileNameStringSize]; //!< storage for string data
    };
}

#endif
