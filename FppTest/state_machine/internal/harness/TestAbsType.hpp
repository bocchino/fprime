// ======================================================================
//
// \title  TestAbsType.hpp
// \author R. Bocchino
// \brief  An abstract type for testing
//
// \copyright
// Copyright 2024, by the California Institute of Technology.
// ALL RIGHTS RESERVED. United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef FppTest_History_HPP
#define FppTest_History_HPP

#include "Fw/Types/Serializable.hpp"

namespace FppTest {

namespace SmHarness {

//! An abstract type for testing
struct TestAbsType final : public Fw::Serializable {
    //! The serialized size
    static constexpr FwSizeType SERIALIZED_SIZE = sizeof(U32);

    //! Default-argument constructor
    TestAbsType() : m_data(0) {}

    //! Supplied-argument constructor
    TestAbsType(U32 data  //!< The data
                )
        : m_data(data) {}

    //! Comparison operator
    bool operator==(const TestAbsType& obj) const { return this->m_data == obj.m_data; }

    //! Serialize function
    //! \return Status
    Fw::SerializeStatus serialize(Fw::SerializeBufferBase& sbb  //!< The serialize buffer base
    ) const final {
        return sbb.serialize(this->m_data);
    }

    //! Deserialize method
    //! \return status
    Fw::SerializeStatus deserialize(Fw::SerializeBufferBase& sbb  //!< The serialize buffer base
                                    ) final {
        return sbb.deserialize(this->m_data);
    }

    //! The data
    U32 m_data;
};

}  // namespace SmHarness

}  // namespace FppTest

#endif
