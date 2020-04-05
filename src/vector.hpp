#pragma once

#include <stdlib.h>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <ostream>
#include <sstream>


namespace pel
{
/** @todo CMake Integration */
/** @todo Inherit from container_base */
/**       @todo Configure Git Subproject */
/** @todo Clear Clang-Tidy warnings */
/** @todo Free memory automatically when not needed */
/** @todo make things actually constexpr */
/** @todo Increase allocation step size automatically when needed */
/**       @todo Make allocation step sizes align with the implementation's
                memory allocations alignments and sizes. */

constexpr bool vector_safeness = true;


template<typename ItemType>
using vector_iterator = ItemType*;

template<typename ItemType>
using reverse_vector_iterator = std::reverse_iterator<vector_iterator<ItemType>>;


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
    constexpr vector(SizeType length = 0);
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

    constexpr inline ItemType* data() noexcept;
    constexpr inline const ItemType* data() const noexcept;


    constexpr inline SizeType index_of(const vector_iterator<ItemType> iterator) const;

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
    constexpr inline vector_iterator<ItemType> begin() const noexcept;
    constexpr inline vector_iterator<ItemType> end()   const noexcept;
    constexpr inline const vector_iterator<ItemType> cbegin() const noexcept;
    constexpr inline const vector_iterator<ItemType> cend()   const noexcept;
    constexpr inline reverse_vector_iterator<ItemType> rbegin() const noexcept;
    constexpr inline reverse_vector_iterator<ItemType> rend()   const noexcept;
    constexpr inline const reverse_vector_iterator<ItemType> crbegin() const noexcept;
    constexpr inline const reverse_vector_iterator<ItemType> crend()   const noexcept;


    /*********************************************************************/
    /* Element management ---------------------------------------------- */
    constexpr inline void push_back(const ItemType& value);
    constexpr inline void push_back(const std::initializer_list<ItemType> ilist);
    constexpr inline void pop_back();


    constexpr inline vector_iterator<ItemType> insert(const ItemType& value,
                                                      const vector_iterator<ItemType> position,
                                                      const SizeType count = 1);

    constexpr inline vector_iterator<ItemType> insert(const ItemType& value,
                                                      const SizeType offset,
                                                      const SizeType count = 1);

    constexpr inline vector_iterator<ItemType> insert(const vector_iterator<ItemType> sourceBegin,
                                                      const vector_iterator<ItemType> sourceEnd,
                                                      const vector_iterator<ItemType> position);

    constexpr inline vector_iterator<ItemType> insert(const vector_iterator<ItemType> sourceBegin,
                                                      const vector_iterator<ItemType> sourceEnd,
                                                      const SizeType offset = 0);

    constexpr inline vector_iterator<ItemType> insert(const std::initializer_list<ItemType> ilist,
                                                      const SizeType offset = 0);

    constexpr inline vector_iterator<ItemType> replace_back(const ItemType& value);
    constexpr inline vector_iterator<ItemType> replace_front(const ItemType& value);
    constexpr inline vector_iterator<ItemType> replace(const ItemType& value,
                                                       vector_iterator<ItemType> position = cbegin());


    /*********************************************************************/
    /* Memory ---------------------------------------------------------- */
    constexpr inline SizeType length() const noexcept;
    constexpr inline SizeType capacity() const noexcept;
    constexpr inline bool isEmpty() const noexcept;
    constexpr inline bool isNotEmpty() const noexcept;

    constexpr inline void reserve(const SizeType newCapacity);
    constexpr inline void resize(const SizeType newLength);

    constexpr inline void clear();

    constexpr inline void shrink_to_fit();


    /*********************************************************************/
    /* Misc ------------------------------------------------------------ */
    constexpr inline std::string to_string() const;


    /*********************************************************************/
    /* Private methods ------------------------------------------------- */
private:
    inline void vector_constructor(const SizeType size);

    constexpr inline void add_size(const SizeType addedLength);
    constexpr inline void change_size(const SizeType newLength);

    constexpr inline void check_fit(const SizeType extraLength);
    constexpr inline void check_if_valid(const vector_iterator<ItemType> iterator);
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
    constexpr inline SizeType m_stepSize() { return 4; }


#pragma endregion
};

};

#include "src/vector.inl"
