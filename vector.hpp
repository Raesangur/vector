#pragma once
#include <stdlib.h>
#include <algorithm>
#include <memory>
#include <stdexcept>

namespace pel
{
    template<typename ItemType>
    class vector
    {
    public:
        /*********************************************************************/
        /* Type definitions ------------------------------------------------ */
        using size_type = typename std::size_t;
        /** @todo Better iterators */
        /** @todo reverse iterators */
        using vector_iterator = ItemType*;


        /*********************************************************************/
        /* Methods --------------------------------------------------------- */
#pragma region Methods declarations

        /* Constructors */
        vector(size_type length)
            : m_length(length)
        {
            m_VectorConstructor(length);
        }

        vector(size_type length, const ItemType& defaultValue)
            : m_length(length)
        {
            m_VectorConstructor(length);

            std::fill(this->begin(), this->end(), defaultValue);
        }

        vector(const vector_iterator& beginIterator,
               const vector_iterator& endIterator)
        {
            m_length = endIterator - beginIterator;
            m_VectorConstructor(length());

            std::copy(beginIterator, endIterator, begin());
        }

        vector(const vector<ItemType>& otherVector)
        {
            m_length = otherVector.m_length;
            m_VectorConstructor(length());

            std::copy(otherVector.cbegin(), otherVector.cend(), begin);
        }

        vector(const std::initializer_list<ItemType> ilist)
        {
            /** @todo */
        }

        /* Destructor */
        ~vector()
        {
            std::free(m_beginIterator);
        }


        /*********************************************************************/
        /* Element accessors ----------------------------------------------- */
        inline ItemType& at(const size_type index)
        {
            return *this->operator[](index);
        }
        inline const ItemType& at(const size_type index) const
        {
            return *this->operator[](index);
        }

        inline ItemType& front() { return *begin(); }
        inline ItemType& back() { return *(end() - 1); }
        inline const ItemType& front() const { return *begin(); }
        inline const ItemType& back() const { return *(end() - 1); }

        inline ItemType* data() { return m_beginIterator; }
        inline const ItemType* data() const { return m_beginIterator; }


        inline void assign(const ItemType& value,
                           const size_type count,
                           const size_type offset = 0)
        {
            std::fill_n(begin() + offset, count, value);
        }
        void assign(const std::initializer_list<ItemType> ilist)
        {
            /** @todo */
        }


        /*********************************************************************/
        /* Operator overloads ---------------------------------------------- */

        ItemType& operator[](const size_type index)
        {
            if (index >= length())
            {
                throw std::length_error("Index out of range!");
            }

            return m_beginIterator[index];
        }

        const ItemType& operator[](const size_type index) const
        {
            if (index >= length())
            {
                throw std::length_error("Index out of range!");
            }

            return m_beginIterator[index];
        }

        vector<ItemType>& operator+=(const ItemType& rhs)
        {
            emplace_back(rhs);
            return *this;
        }

        vector<ItemType>& operator++(int)
        {
            reserve(capacity() + 1);
            return *this;
        }

        vector<ItemType>& operator--(int)
        {
            if (capacity() == length())
            {
                pop_back();
            }

            reserve(capacity() - 1);
            return *this;
        }

        vector<ItemType>& operator>>(int steps)
        {
            std::shift_right(cbegin(), cend(), steps);

            return *this;
        }
        vector<ItemType>& operator<<(int steps)
        {
            std::shift_left(cbegin(), cend(), steps);

            return *this;
        }


        /*********************************************************************/
        /* Iterators ------------------------------------------------------- */
        inline vector_iterator begin() const { return m_beginIterator; }
        inline vector_iterator end()   const { return m_endIterator; }
        inline const vector_iterator cbegin() const { return m_beginIterator; }
        inline const vector_iterator cend()   const { return m_endIterator; }


        /*********************************************************************/
        /* Element management ---------------------------------------------- */
        void push_back(const ItemType& value)
        {
            m_checkFit(1);

            *m_endIterator = value;

            m_addSize(1);
        }

        void pop_back()
        {
            if (length() == 0)
            {
                return;
            }

            std::destroy_at(--m_endIterator);
            m_length--;
        }


        vector_iterator insert(const ItemType& value,
                               const vector_iterator& position = cbegin(),
                               const size_type count = 1)
        {
            m_checkIfValid(position);
            if (count == 0)
            {
                return cbegin();
            }

            m_checkFit(1);
            m_addSize(count);

            std::shift_right(position, cend(), count);

            for (size_type i = 0; i < count; i++)
            {
                position[i] = value;
            }

            return position;
        }

        vector_iterator insert(const ItemType& value,
                               const size_type offset = 0,
                               const size_type count = 1)
        {
            if (offset > length())
            {
                throw std::invalid_argument("Invalid insert offset");
            }

            vector_iterator position = cbegin() + offset;

            return insert(value, position, count);
        }

        vector_iterator insert(const vector_iterator& sourceBegin,
                               const vector_iterator& sourceEnd,
                               const vector_iterator& position = cbegin())
        {
            m_checkIfValid(position);
            size_type sourceSize = sourceEnd - sourceBegin;
            
            m_checkFit(sourceSize);
            m_addSize(sourceSize);

            std::shift_right(position, cend(), sourceSize);
            std::copy(sourceBegin, sourceEnd, position);

            return position;
        }

        vector_iterator insert(const vector_iterator& sourceBegin,
                               const vector_iterator& sourceEnd,
                               const size_type offset = 0)
        {
            if (offset > length())
            {
                throw std::invalid_argument("Invalid insert offset");
            }

            vector_iterator position = cbegin() + offset;

            return insert(sourceBegin, sourceEnd, position);
        }

        vector_iterator insert(const std::initializer_list<ItemType>& ilist,
                               const vector_iterator& position = cbegin())
        {
            /** @todo */
        }
        vector_iterator insert(const std::initializer_list<ItemType>& ilist,
                               const size_type offset = 0)
        {
            if (offset > length())
            {
                throw std::invalid_argument("Invalid insert offset");
            }

            vector_iterator position = cbegin() + offset;

            return insert(ilist, position);
        }

        vector_iterator emplace(const ItemType& value,
                                const vector_iterator& position = cbegin())
        {
            m_checkIfValid(position);

            *position = value;

            return position;
        }
        vector_iterator emplace_back(const ItemType& value)
        {
            vector_iterator position = m_endIterator - 1;

            *position = value;

            return position;
        }


        /*********************************************************************/
        /* Memory ---------------------------------------------------------- */
        const size_type& length() const { return m_length; }
        const size_type& capacity() const { return m_capacity; }
        const bool isEmpty() const { return length() == 0; }

        void reserve(const size_type newCapacity)
        {
            /* Check if resizing is necessary */
            if (newCapacity == capacity())
            {
                return;
            }

            /* Allocate a new memory segment */
            m_VectorConstructor(newCapacity);
        }

        void resize(const size_type newLength)
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

        void clear()
        {
            std::destroy(begin(), end());

            m_length = 0;
            m_endIterator = m_beginIterator;
        }

        void shrink_to_fit()
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
        void m_VectorConstructor(const size_type size)
        {
            m_capacity = size;

            /* Reallocate block of memory */
            std::size_t blockSize = capacity() * sizeof(ItemType);
            void* tempPtr = std::realloc(m_beginIterator, blockSize);
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
        void m_addSize(const size_type addedLength)
        {
            m_changeSize(length() + addedLength);
        }
        void m_changeSize(const size_type newLength)
        {
            m_length = newLength;
            m_endIterator = &m_beginIterator[length()];
        }
        bool m_checkFit(const size_type extraLength)
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
        void m_checkIfValid(const vector_iterator& iterator)
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
        size_type m_length;
        size_type m_capacity;
        vector_iterator m_beginIterator = nullptr;
        vector_iterator m_endIterator = nullptr;


        /*********************************************************************/
        /* Static variables ------------------------------------------------ */
        constexpr size_type s_stepSize() { return 4; }
#pragma endregion
    };
};

