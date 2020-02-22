#pragma once
//#include "vector_iterator.h"

#include <stdlib.h>
#include <algorithm>
#include <memory>
#include <stdexcept>


namespace pel
{
/** @todo Complete comments */
/** @todo Free memory automatically when not needed */
/** @todo Increase allocation step size automatically when needed */
/**       @todo Make allocation step sizes align with the implementation's
                memory allocations alignments and sizes. */
                /** @todo noexcept, ndebug-mode compiling without checks */
                /** @todo make things actually constexpr */


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
    constexpr vector(SizeType length);
    constexpr vector(SizeType length, const ItemType& defaultValue);
    constexpr vector(const vector_iterator<ItemType> beginIterator,
                     const vector_iterator<ItemType> endIterator);
    constexpr vector(const vector<ItemType>& otherVector);
    constexpr vector(const std::initializer_list<ItemType> ilist);

    /* Destructor */
    ~vector();


    /*********************************************************************/
    /* Element accessors ----------------------------------------------- */
    constexpr inline ItemType& at(const SizeType index);
    constexpr inline const ItemType& at(const SizeType index) const;

    constexpr inline ItemType& front();
    constexpr inline ItemType& back();
    constexpr inline const ItemType& front() const;
    constexpr inline const ItemType& back() const;

    constexpr inline ItemType* data();
    constexpr inline const ItemType* data() const;


    constexpr inline void assign(const ItemType& value,
                                 const SizeType offset = 0,
                                 const SizeType count = 1);
    constexpr inline void assign(const std::initializer_list<ItemType> ilist,
                                 const SizeType offset = 0);


    /*********************************************************************/
    /* Operator overloads ---------------------------------------------- */
    constexpr inline ItemType& operator[](const SizeType index);
    constexpr inline const ItemType& operator[](const SizeType index) const;

    constexpr inline vector<ItemType>& operator+=(const ItemType& rhs);

    constexpr inline vector<ItemType>& operator++(int);
    constexpr inline vector<ItemType>& operator--(int);

    constexpr inline vector<ItemType>& operator>>(int steps);
    constexpr inline vector<ItemType>& operator<<(int steps);


    /*********************************************************************/
    /* Iterators ------------------------------------------------------- */
    constexpr inline vector_iterator<ItemType> begin() const;
    constexpr inline vector_iterator<ItemType> end()   const;
    constexpr inline const vector_iterator<ItemType> cbegin() const;
    constexpr inline const vector_iterator<ItemType> cend()   const;


    /*********************************************************************/
    /* Element management ---------------------------------------------- */
    constexpr void push_back(const ItemType& value);
    constexpr void push_back(const std::initializer_list<ItemType> ilist);
    constexpr void pop_back();


    constexpr inline vector_iterator<ItemType>
        insert(const ItemType& value,
               vector_iterator<ItemType> position,
               SizeType count = 1);

    constexpr inline vector_iterator<ItemType>
        insert(const ItemType& value,
               const SizeType offset,
               const SizeType count = 1);

    constexpr inline vector_iterator<ItemType>
        insert(const vector_iterator<ItemType> sourceBegin,
               const vector_iterator<ItemType> sourceEnd,
               const vector_iterator<ItemType> position);

    constexpr inline vector_iterator<ItemType>
        insert(const vector_iterator<ItemType> sourceBegin,
               const vector_iterator<ItemType> sourceEnd,
               const SizeType offset = 0);

    constexpr inline vector_iterator<ItemType>
        insert(const std::initializer_list<ItemType> ilist,
               const SizeType offset = 0);

    constexpr inline vector_iterator<ItemType> replace_back(const ItemType& value);
    constexpr inline vector_iterator<ItemType> replace_front(const ItemType& value);
    constexpr inline vector_iterator<ItemType>
        replace(const ItemType& value,
                vector_iterator<ItemType> position = cbegin());


    /*********************************************************************/
    /* Memory ---------------------------------------------------------- */
    constexpr inline const SizeType& length() const;
    constexpr inline const SizeType& capacity() const;
    constexpr inline const bool isEmpty() const;

    constexpr void reserve(const SizeType newCapacity);
    constexpr void resize(const SizeType newLength);

    constexpr void clear();

    constexpr void shrink_to_fit();


    /*********************************************************************/
    /* Private methods ------------------------------------------------- */
private:
    constexpr inline void m_VectorConstructor(const SizeType size);

    constexpr inline void m_addSize(const SizeType addedLength);
    constexpr inline void m_changeSize(const SizeType newLength);

    constexpr inline bool m_checkFit(const SizeType extraLength);
    constexpr inline void m_checkIfValid(const vector_iterator<ItemType> iterator);
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

#include "vector.inl"
