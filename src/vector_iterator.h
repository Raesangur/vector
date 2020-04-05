#pragma once
#include "vector.hpp"

#include <compare>
#include <iterator>


/**************************************/
/* THIS FILE IS DEPRECATED            */
/**************************************/
/* DO NOT USE                         */
/* DO NOT USE                         */
/* DO NOT USE                         */
/* (It should still be working though */
/**************************************/





namespace pel
{
/* Forward declaration */
template<typename ItemType>
class vector;


template<typename ItemType>
class vector_iterator_deprecated
{
    using SizeType = typename pel::vector<ItemType>::SizeType;
    using DifferenceType = typename pel::vector<ItemType>::DifferenceType;
    using PointerType = ItemType*;
    using ReferenceType = ItemType&;
    /*****************************************************************************/
    /* Public methods ---------------------------------------------------------- */
public:
    vector_iterator_deprecated() : m_ptr(nullptr) {}
    vector_iterator_deprecated(PointerType element) : m_ptr(element) {}
    vector_iterator_deprecated(const vector_iterator_deprecated<ItemType>& other) : m_ptr(other.m_ptr) {}

#pragma region Methods
    /*------------------------------------*/
    /* Memory operators */
    [[nodiscard]] const PointerType& ptr() const
    {
        return m_ptr;
    }
    [[nodiscard]] PointerType& ptr()
    {
        return m_ptr;
    }
    [[nodiscard]] const ReferenceType operator*() const
    {
        return *m_ptr;
    }
    [[nodiscard]] ReferenceType operator*()
    {
        return *m_ptr;
    }
    [[nodiscard]] const ReferenceType operator[](SizeType index) const
    {
        return m_ptr[index];
    }
    [[nodiscard]] ReferenceType operator[](SizeType index)
    {
        return m_ptr[index];
    }
    void operator=(const vector_iterator_deprecated<ItemType>& other)
    {
        m_ptr = other.m_ptr;
    }
    void operator=(const PointerType other)
    {
        m_ptr = other;
    }
    operator PointerType() const
    {
        return m_ptr;
    }

    /*------------------------------------*/
    /* Addition operators */
    [[nodiscard]] vector_iterator_deprecated operator+(DifferenceType rhs) const
    {
        return vector_iterator_deprecated(m_ptr + rhs);
    }
    [[nodiscard]] DifferenceType operator+(vector_iterator_deprecated rhs) const
    {
        return m_ptr + rhs.m_ptr;
    }
    vector_iterator_deprecated<ItemType> operator++()
    {
        ++ptr();
        return *this;
    }
    vector_iterator_deprecated<ItemType> operator++(int)
    {
        ptr()++;
        return *this;
    }
    vector_iterator_deprecated<ItemType> operator+=(DifferenceType rhs)
    {
        ptr() += rhs;
        return *this;
    }


    /*------------------------------------*/
    /* Substraction operators */

    [[nodiscard]] vector_iterator_deprecated operator-(DifferenceType rhs) const
    {
        return vector_iterator_deprecated(m_ptr - rhs);
    }
    [[nodiscard]] DifferenceType operator-(vector_iterator_deprecated rhs) const
    {
        return m_ptr - rhs.m_ptr;
    }
    vector_iterator_deprecated<ItemType> operator--()
    {
        --ptr();
        return *this;
    }
    vector_iterator_deprecated<ItemType> operator--(int)
    {
        ptr()--;
        return *this;
    }
    vector_iterator_deprecated<ItemType> operator-=(DifferenceType rhs)
    {
        ptr() -= rhs;
        return *this;
    }

    /*------------------------------------*/
    /* Comparison operators */
    [[nodiscard]] const bool operator==(vector_iterator_deprecated rhs) const
    {
        return (m_ptr == rhs.m_ptr);
    }
    [[nodiscard]] const bool operator!=(vector_iterator_deprecated rhs) const
    {
        return (m_ptr != rhs.m_ptr);
    }

    [[nodiscard]] const bool operator>(vector_iterator_deprecated rhs) const
    {
        return (m_ptr > rhs.m_ptr);
    }
    [[nodiscard]] const bool operator>=(vector_iterator_deprecated rhs) const
    {
        return (m_ptr >= rhs.m_ptr);
    }

    [[nodiscard]] const bool operator<(vector_iterator_deprecated rhs) const
    {
        return (m_ptr < rhs.m_ptr);
    }
    [[nodiscard]] const bool operator<=(vector_iterator_deprecated rhs) const
    {
        return (m_ptr <= rhs.m_ptr);
    }

    [[nodiscard]] const std::strong_ordering operator <=>(vector_iterator_deprecated rhs) const
    {
        if (*this < rhs)
        {
            return std::strong_ordering::greater;
        }
        if (*this > rhs)
        {
            return std::strong_ordering::less;
        }
        else /* *this == rhs */
        {
            return std::strong_ordering::equal;
        }
    }

#pragma endregion


    /*****************************************************************************/
    /* Private variables ------------------------------------------------------- */
private:
    PointerType m_ptr = NULL;
#pragma endregion
};

}
