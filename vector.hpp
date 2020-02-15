#pragma once
//#include "vector_iterator.h"

#include <stdlib.h>
#include <algorithm>
#include <memory>
#include <stdexcept>


namespace pel
{
/** @todo Free memory automatically when not needed */
/** @todo Increase allocation step size automatically when needed */
/** @todo noexcept, ndebug-mode compiling without checks */


template<typename ItemType>
using vector_iterator = ItemType*;


template<typename ItemType>
class vector
{
public:
    /*********************************************************************/
    /* Type definitions ------------------------------------------------ */
    using SizeType = std::size_t;
    using DifferenceType = std::ptrdiff_t;


    /*********************************************************************/
    /* Methods --------------------------------------------------------- */
#pragma region Methods declarations

        /* Constructors */
    constexpr vector(SizeType length)
        : m_length(length)
    {
        m_VectorConstructor(length);
    }

    constexpr vector(SizeType length, const ItemType& defaultValue)
        : m_length(length)
    {
        m_VectorConstructor(length);

        std::fill(this->begin(), this->end(), defaultValue);
    }

    constexpr vector(const vector_iterator<ItemType> beginIterator,
           const vector_iterator<ItemType> endIterator)
    {
        m_length = endIterator - beginIterator;
        m_VectorConstructor(length());

        std::copy(beginIterator, endIterator, begin());
    }

    constexpr vector(const vector<ItemType>& otherVector)
    {
        m_length = otherVector.m_length;
        m_VectorConstructor(length());

        std::copy(otherVector.cbegin(), otherVector.cend(), begin);
    }

    constexpr vector(const std::initializer_list<ItemType> ilist)
    {
        m_length = ilist.size();
        m_VectorConstructor(length());

        std::copy(ilist.begin(), ilist.end(), begin());
    }

    /* Destructor */
    ~vector()
    {
        std::free(begin());
    }


    /*********************************************************************/
    /* Element accessors ----------------------------------------------- */
    constexpr inline ItemType& at(const SizeType index)
    {
        return *this->operator[](index);
    }
    constexpr inline const ItemType& at(const SizeType index) const
    {
        return *this->operator[](index);
    }

    constexpr inline ItemType& front() { return *begin(); }
    constexpr inline ItemType& back() { return *(end() - 1); }
    constexpr inline const ItemType& front() const { return *begin(); }
    constexpr inline const ItemType& back() const { return *(end() - 1); }

    constexpr inline ItemType* data() { return m_beginIterator; }
    constexpr inline const ItemType* data() const { return m_beginIterator; }


    constexpr inline void assign(const ItemType& value,
                       const SizeType count,
                       const SizeType offset = 0)
    {
        m_checkFit(count);

        std::fill_n(begin() + offset, count, value);
    }
    constexpr void assign(const std::initializer_list<ItemType> ilist,
                          const SizeType offset = 0)
    {
        m_checkFit(ilist.size());

        std::copy(ilist.begin(), ilist.end(), begin() + offset);
    }


    /*********************************************************************/
    /* Operator overloads ---------------------------------------------- */

    constexpr ItemType& operator[](const SizeType index)
    {
        if (index >= length())
        {
            throw std::length_error("Index out of range!");
        }

        return m_beginIterator[index];
    }

    constexpr const ItemType& operator[](const SizeType index) const
    {
        if (index >= length())
        {
            throw std::length_error("Index out of range!");
        }

        return m_beginIterator[index];
    }

    constexpr vector<ItemType>& operator+=(const ItemType& rhs)
    {
        emplace_back(rhs);
        return *this;
    }

    constexpr vector<ItemType>& operator++(int)
    {
        reserve(capacity() + 1);
        return *this;
    }

    constexpr vector<ItemType>& operator--(int)
    {
        if (capacity() == length())
        {
            pop_back();
        }

        reserve(capacity() - 1);
        return *this;
    }

    constexpr vector<ItemType>& operator>>(int steps)
    {
        std::shift_right(cbegin(), cend(), steps);

        return *this;
    }
    constexpr vector<ItemType>& operator<<(int steps)
    {
        std::shift_left(cbegin(), cend(), steps);

        return *this;
    }


    /*********************************************************************/
    /* Iterators ------------------------------------------------------- */
    constexpr inline vector_iterator<ItemType> begin() const { return m_beginIterator; }
    constexpr inline vector_iterator<ItemType> end()   const { return m_endIterator; }
    constexpr inline const vector_iterator<ItemType> cbegin() const { return m_beginIterator; }
    constexpr inline const vector_iterator<ItemType> cend()   const { return m_endIterator; }


    /*********************************************************************/
    /* Element management ---------------------------------------------- */
    constexpr void push_back(const ItemType& value)
    {
        m_checkFit(1);

        *m_endIterator = value;

        m_addSize(1);
    }
    constexpr void push_back(const std::initializer_list<ItemType> ilist)
    {
        m_checkFit(ilist.size());

        std::copy(ilist.begin(), ilist.end(), end());

        m_addSize(ilist.size());
    }

    constexpr void pop_back()
    {
        if (length() == 0)
        {
            return;
        }

        std::destroy_at(--m_endIterator);
        m_length--;
    }


    constexpr vector_iterator<ItemType> insert(const ItemType& value,
                                     vector_iterator<ItemType> position = begin(),
                                     SizeType count = 1)
    {
        m_checkIfValid(position);
        if (count == 0)
        {
            return cbegin();
        }

        m_checkFit(1);
        m_addSize(count);

        std::shift_right(position, end(), count);

        for (SizeType i = 0; i < count; i++)
        {
            position[i] = value;
        }

        return position;
    }

    constexpr vector_iterator<ItemType> insert(const ItemType& value,
                                     const SizeType offset = 0,
                                     const SizeType count = 1)
    {
        if (offset > length())
        {
            throw std::invalid_argument("Invalid insert offset");
        }

        vector_iterator<ItemType> position = cbegin() + offset;

        return insert(value, position, count);
    }

    constexpr vector_iterator<ItemType> insert(const vector_iterator<ItemType> sourceBegin,
                                     const vector_iterator<ItemType> sourceEnd,
                                     const vector_iterator<ItemType> position)
    {
        m_checkIfValid(position);
        SizeType sourceSize = sourceEnd - sourceBegin;

        m_checkFit(sourceSize);
        m_addSize(sourceSize);

        std::shift_right(position, cend(), sourceSize);
        std::copy(sourceBegin, sourceEnd, position);

        return position;
    }

    constexpr vector_iterator<ItemType> insert(const vector_iterator<ItemType> sourceBegin,
                                     const vector_iterator<ItemType> sourceEnd,
                                     const SizeType offset = 0)
    {
        if (offset > length())
        {
            throw std::invalid_argument("Invalid insert offset");
        }

        vector_iterator position = cbegin() + offset;

        return insert(sourceBegin, sourceEnd, position);
    }

    constexpr vector_iterator<ItemType> insert(const std::initializer_list<ItemType> ilist,
                                     const SizeType offset = 0)
    {
        if (offset > length())
        {
            throw std::invalid_argument("Invalid insert offset");
        }

        vector_iterator<ItemType> position = cbegin() + offset;

        return insert(ilist.begin(), ilist.end(), position);
    }

    constexpr vector_iterator<ItemType> replace(const ItemType& value,
                                      vector_iterator<ItemType> position = cbegin())
    {
        m_checkIfValid(position);

        *position = value;

        return position;
    }
    constexpr vector_iterator<ItemType> replace_back(const ItemType& value)
    {
        vector_iterator<ItemType> position = end() - 1;

        *position = value;

        return position;
    }
    constexpr vector_iterator<ItemType> replace_front(const ItemType& value)
    {
        vector_iterator<ItemType> position = begin();

        *position = value;

        return position;
    }


    /*********************************************************************/
    /* Memory ---------------------------------------------------------- */
    constexpr inline const SizeType& length() const { return m_length; }
    constexpr inline const SizeType& capacity() const { return m_capacity; }
    constexpr inline const bool isEmpty() const { return length() == 0; }

    constexpr void reserve(const SizeType newCapacity)
    {
        /* Check if resizing is necessary */
        if (newCapacity == capacity())
        {
            return;
        }

        /* Allocate a new memory segment */
        m_VectorConstructor(newCapacity);
    }

    constexpr void resize(const SizeType newLength)
    {
        /* Check if reserving memory is necessary */
        if (newLength > capacity())
        {
            reserve(newLength);
        }

        /* Check if freeing some memory is necessary */
        /** @todo /

        /* Resize */
        m_changeSize(newLength);
    }

    constexpr void clear()
    {
        std::destroy(begin(), end());

        m_length = 0;
        m_endIterator = cbegin();
    }

    constexpr void shrink_to_fit()
    {
        if (length() == capacity())
        {
            return;
        }

        reserve(length());
    }


    /*********************************************************************/
    /* Private methods ------------------------------------------------- */
private:
    constexpr inline void m_VectorConstructor(const SizeType size)
    {
        m_capacity = size;

        /* Reallocate block of memory */
        std::size_t blockSize = capacity() * sizeof(ItemType);
        void* tempPtr = std::realloc(begin(), blockSize);
        if (tempPtr == nullptr)
        {
            if (size != 0)
            {
                throw new std::bad_alloc();
            }
            else
            {
                m_beginIterator = nullptr;
                m_endIterator = nullptr;
                return;
            }
        }

        /* Set iterators */
        m_beginIterator = static_cast<ItemType*>(tempPtr);
        m_endIterator = &m_beginIterator[length()];
    }
    constexpr inline void m_addSize(const SizeType addedLength)
    {
        m_changeSize(length() + addedLength);
    }
    constexpr inline void m_changeSize(const SizeType newLength)
    {
        m_length = newLength;
        m_endIterator = &m_beginIterator[length()];
    }
    constexpr inline bool m_checkFit(const SizeType extraLength)
    {
        if (length() + extraLength > capacity())
        {
            reserve(capacity() + s_stepSize() + extraLength);
            return false;
        }
        else
        {
            return true;
        }
    }
    constexpr inline void m_checkIfValid(const vector_iterator<ItemType> iterator)
    {
        if ((iterator < cbegin()) || (iterator > cend()))
        {
            throw std::invalid_argument("Invalid iterator");
        }
    }
#pragma endregion


    /*********************************************************************/
    /* Variables ------------------------------------------------------- */
#pragma region Variables
private:
    SizeType m_length = 0;
    SizeType m_capacity = 0;
    vector_iterator<ItemType> m_beginIterator = nullptr;
    vector_iterator<ItemType> m_endIterator = nullptr;


    /*********************************************************************/
    /* Static variables ------------------------------------------------ */
    constexpr inline SizeType s_stepSize() { return 4; }
#pragma endregion
};

};

