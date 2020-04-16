#pragma once

#include "./container_base/src/container_base.h"

#include <algorithm>
#include <memory>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>


namespace pel
{
/** @todo Inherit from container_base */
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
class vector : container_base<ItemType, vector_iterator<ItemType>>
{
    public:
    /*********************************************************************/
    /* Type definitions ------------------------------------------------ */
    using SizeType            = std::size_t;
    using DifferenceType      = std::ptrdiff_t;
    using IteratorType        = vector_iterator<ItemType>;
    using RIteratorType       = reverse_vector_iterator<ItemType>;
    using InitializerListType = std::initializer_list<ItemType>;


    /*********************************************************************/
    /* Methods --------------------------------------------------------- */
#pragma region Methods declarations

    /* Constructors */
    constexpr vector(SizeType length = 0);
    constexpr vector(SizeType length, const ItemType& defaultValue);
    constexpr vector(const IteratorType beginIterator, const IteratorType endIterator);
    constexpr vector(const vector<ItemType>& otherVector);
    constexpr vector(const InitializerListType ilist);

    /* Destructor */
    ~vector();


    /*********************************************************************/
    /* Element accessors ----------------------------------------------- */
    constexpr ItemType&       at(SizeType index) override;
    constexpr const ItemType& at(SizeType index) const override;

    constexpr ItemType&       front() override;
    constexpr ItemType&       back() override;
    constexpr const ItemType& front() const override;
    constexpr const ItemType& back() const override;

    constexpr ItemType*       data() noexcept;
    constexpr const ItemType* data() const noexcept;


    constexpr SizeType index_of(const IteratorType iterator) const;

    constexpr void assign(const ItemType& value, SizeType offset = 0, SizeType count = 1);
    constexpr void assign(const InitializerListType ilist, SizeType offset = 0);


    /*********************************************************************/
    /* Operator overloads ---------------------------------------------- */
    constexpr ItemType&       operator[](SizeType index) override;
    constexpr const ItemType& operator[](SizeType index) const override;

    constexpr vector<ItemType>& operator+=(const ItemType& rhs);

    constexpr vector<ItemType>& operator++(int);
    constexpr vector<ItemType>& operator--(int);

    constexpr vector<ItemType>& operator>>(int steps);
    constexpr vector<ItemType>& operator<<(int steps);


    /*********************************************************************/
    /* Iterators ------------------------------------------------------- */
    constexpr IteratorType        begin() const noexcept override;
    constexpr IteratorType        end() const noexcept override;
    constexpr const IteratorType  cbegin() const noexcept override;
    constexpr const IteratorType  cend() const noexcept override;
    constexpr RIteratorType       rbegin() const noexcept;
    constexpr RIteratorType       rend() const noexcept;
    constexpr const RIteratorType crbegin() const noexcept;
    constexpr const RIteratorType crend() const noexcept;


    /*********************************************************************/
    /* Element management ---------------------------------------------- */
    constexpr void push_back(const ItemType& value);
    constexpr void push_back(const InitializerListType ilist);
    constexpr void pop_back();


    constexpr vector_iterator<ItemType> insert(const ItemType&    value,
                                               const IteratorType position,
                                               SizeType           count = 1);

    constexpr vector_iterator<ItemType> insert(const ItemType& value,
                                               SizeType        offset,
                                               SizeType        count = 1);

    constexpr vector_iterator<ItemType> insert(const IteratorType sourceBegin,
                                               const IteratorType sourceEnd,
                                               const IteratorType position);

    constexpr vector_iterator<ItemType> insert(const IteratorType sourceBegin,
                                               const IteratorType sourceEnd,
                                               SizeType           offset = 0);

    constexpr vector_iterator<ItemType> insert(const InitializerListType ilist,
                                               SizeType                  offset = 0);

    constexpr vector_iterator<ItemType> replace_back(const ItemType& value);
    constexpr vector_iterator<ItemType> replace_front(const ItemType& value);
    constexpr vector_iterator<ItemType> replace(const ItemType& value,
                                                IteratorType    position = cbegin());


    /*********************************************************************/
    /* Memory ---------------------------------------------------------- */
    constexpr SizeType length() const noexcept override;
    constexpr SizeType capacity() const noexcept;
    constexpr bool     is_empty() const noexcept override;
    constexpr bool     is_not_empty() const noexcept override;

    constexpr void reserve(SizeType newCapacity);
    constexpr void resize(SizeType newLength);

    constexpr void clear();

    constexpr void shrink_to_fit();


    /*********************************************************************/
    /* Misc ------------------------------------------------------------ */
    constexpr std::string to_string() const override;


    /*********************************************************************/
    /* Private methods ------------------------------------------------- */
    private:
    inline void vector_constructor(SizeType size);

    constexpr void add_size(SizeType addedLength);
    constexpr void change_size(SizeType newLength);

    constexpr void check_fit(SizeType extraLength);
    constexpr void check_if_valid(const IteratorType iterator);
#pragma endregion


    /*********************************************************************/
    /* Variables ------------------------------------------------------- */
#pragma region Variables
    private:
    SizeType     m_length        = 0;
    SizeType     m_capacity      = 0;
    IteratorType m_beginIterator = nullptr;
    IteratorType m_endIterator   = nullptr;


    /*********************************************************************/
    /* Static variables ------------------------------------------------ */
    constexpr inline SizeType
    m_stepSize()
    {
        return 4;
    }


#pragma endregion
};

};        // namespace pel

#include "./vector.inl"