#pragma once
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

        //vector(std::initializer_list) /** @todo */

        /* Destructor */
        ~vector()
        {
            delete[] m_beginIterator;
        }


        /*********************************************************************/
        /* Element accessors ----------------------------------------------- */
        inline ItemType& at(size_type index)
        { return *this->operator[](index); }
        inline const ItemType& at(size_type index) const 
        { return *this->operator[](index); }

        inline ItemType& front() { return *begin(); }
        inline ItemType& back()  { return *(end() - 1); }
        inline const ItemType& front() const { return *begin(); }
        inline const ItemType& back() const  { return *(end() - 1); }

        inline ItemType* data()             { return m_beginIterator; }
        inline const ItemType* data() const { return m_beginIterator; }


        inline void assign(const ItemType& value,
                           const size_type count,
                           const size_type offset = 0)
        {
            std::fill_n(begin() + offset, count, value);
        }
        //void assign(const std::initializer_list)  /** @todo */


        /*********************************************************************/
        /* Operator overloads ---------------------------------------------- */

        ItemType& operator[](size_type index)
        {
            if (index >= length())
            {
                throw std::length_error("Index out of range!");
            }

            return m_beginIterator[index];
        }

        const ItemType& operator[](size_type index) const
        {
            if (index >= length())
            {
                throw std::length_error("Index out of range!");
            }

            return m_beginIterator[index];
        }


        /*********************************************************************/
        /* Iterators ------------------------------------------------------- */
        inline vector_iterator begin() const { return m_beginIterator; }
        inline vector_iterator end()   const { return m_endIterator; }
        inline const vector_iterator cbegin() const { return m_beginIterator; }
        inline const vector_iterator cend()   const { return m_endIterator; }


        /*********************************************************************/
        /* Memory ---------------------------------------------------------- */
        const size_type& size() const     { return length(); }
        const size_type& length() const   { return m_length; }
        const size_type& capacity() const { return m_capacity; }

        void reserve(size_type newCapacity)
        {
            /* Check if resizing is necessary */
            if (newCapacity == capacity())
            {
                return;
            }

            /* Backup old begin operator */
            vector_iterator oldBegin = begin();
            vector_iterator oldEnd = end();


            /* Allocate a new memory segment */
            m_VectorConstructor(newCapacity);

            /* Copy old content in the new memory */
            std::copy(oldBegin, oldEnd, begin());

            /* Delete the old segment of allocated memory */
            delete[] oldBegin;
        }

        void resize(size_type newLength)
        {
            /* Check if reserving memory is necessary */
            if (newLength > capacity())
            {
                reserve(newLength);
            }

            /* Check if freeing some memory is necessary */
            /** @todo /

            /* Resize */
            m_addSize(newLength);
        }

        void clear()
        {
            std::destroy(begin(), end());

            m_length = 0;
            m_endIterator = m_beginIterator;
        }

        void push_back(const ItemType& value)
        {
            if (length() + 1 > capacity())
            {
                reserve(capacity() + s_stepSize());
            }

            m_addSize(1);

            *m_endIterator = value;
        }


        /*********************************************************************/
        /* Private methods ------------------------------------------------- */
    private:
        void m_VectorConstructor(size_type length)
        {
            m_capacity = length;
            m_beginIterator = new ItemType[length];
            m_endIterator = &m_beginIterator[length];
        }
        void m_addSize(size_type addedLength)
        {
            m_length = length() + addedLength;
            m_endIterator = &m_beginIterator[length()];
        }
#pragma endregion


        /*********************************************************************/
        /* Variables ------------------------------------------------------- */
#pragma region Variables
    private:
        size_type m_length;
        size_type m_capacity;
        vector_iterator m_beginIterator;
        vector_iterator m_endIterator;


        /*********************************************************************/
        /* Static variables ------------------------------------------------ */
        size_type s_stepSize() { return 4; }
#pragma endregion
    };
};

