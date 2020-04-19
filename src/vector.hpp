#pragma once

#include "./container_base/src/container_base.h"

#include <algorithm>
#include <cstdlib>
#include <memory>
#include <ostream>
#include <sstream>
#include <stdexcept>


namespace pel
{
/** @todo Clear Clang-Tidy warnings */
/** @todo Free memory automatically when not needed */
/** @todo make things actually constexpr */
/** @todo working reverse iterators */
/** @todo Increase allocation step size automatically when needed */
/**       @todo Make allocation step sizes align with the implementation's
                memory allocations alignments and sizes. */


constexpr bool vector_safeness = true;

template<typename ItemType>
using vector_iterator = iterator_base<ItemType>;
// using vector_iterator = ItemType*;

template<typename ItemType>
using reverse_vector_iterator = iterator_base<ItemType>;
// using reverse_vector_iterator = std::reverse_iterator<vector_iterator<ItemType>>;


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
    constexpr explicit vector(SizeType length_ = 0);
    constexpr explicit vector(SizeType length_, const ItemType& defaultValue_);
    constexpr explicit vector(IteratorType beginIterator_, IteratorType endIterator_);
    constexpr vector(InitializerListType ilist_);
    constexpr vector(const vector<ItemType>& otherVector_);
    constexpr vector& operator=(const vector<ItemType>& copy_);
    constexpr vector(vector<ItemType>&& movedVector_) noexcept;
    constexpr vector& operator=(vector<ItemType>&& move_) noexcept;

    /* Destructor */
    ~vector() override;


    /*********************************************************************/
    /* Element accessors ----------------------------------------------- */
    [[nodiscard]] constexpr ItemType&       at(SizeType index_) override;
    [[nodiscard]] constexpr const ItemType& at(SizeType index_) const override;

    [[nodiscard]] constexpr ItemType&       front() override;
    [[nodiscard]] constexpr ItemType&       back() override;
    [[nodiscard]] constexpr const ItemType& front() const override;
    [[nodiscard]] constexpr const ItemType& back() const override;

    [[nodiscard]] constexpr ItemType*       data() noexcept;
    [[nodiscard]] constexpr const ItemType* data() const noexcept;


    [[nodiscard]] constexpr DifferenceType index_of(IteratorType iterator_) const;

    constexpr void assign(const ItemType& value_, DifferenceType offset_ = 0, SizeType count_ = 1);
    constexpr void assign(InitializerListType ilist_, DifferenceType offset_ = 0);


    /*********************************************************************/
    /* Operator overloads ---------------------------------------------- */
    [[nodiscard]] constexpr ItemType&       operator[](SizeType index_) override;
    [[nodiscard]] constexpr const ItemType& operator[](SizeType index_) const override;

    constexpr vector<ItemType>& operator+=(const ItemType& rhs_);

    constexpr vector<ItemType> operator++(int);
    constexpr vector<ItemType> operator--(int);

    constexpr vector<ItemType>& operator>>(int steps_);
    constexpr vector<ItemType>& operator<<(int steps_);


    /*********************************************************************/
    /* Iterators ------------------------------------------------------- */
    [[nodiscard]] constexpr IteratorType        begin() const noexcept override;
    [[nodiscard]] constexpr IteratorType        end() const noexcept override;
    [[nodiscard]] constexpr const IteratorType  cbegin() const noexcept override;
    [[nodiscard]] constexpr const IteratorType  cend() const noexcept override;
    [[nodiscard]] constexpr RIteratorType       rbegin() const noexcept;
    [[nodiscard]] constexpr RIteratorType       rend() const noexcept;
    [[nodiscard]] constexpr const RIteratorType crbegin() const noexcept;
    [[nodiscard]] constexpr const RIteratorType crend() const noexcept;


    /*********************************************************************/
    /* Element management ---------------------------------------------- */
    constexpr void push_back(const ItemType& value_);
    constexpr void push_back(InitializerListType ilist_);
    constexpr void pop_back();


    constexpr IteratorType insert(const ItemType& value_,
                                  IteratorType    position_,
                                  SizeType        count_ = 1);

    constexpr IteratorType insert(const ItemType& value_,
                                  DifferenceType  offset_,
                                  SizeType        count_ = 1);

    constexpr IteratorType insert(IteratorType sourceBegin_,
                                  IteratorType sourceEnd_,
                                  IteratorType position_);

    constexpr IteratorType insert(IteratorType   sourceBegin_,
                                  IteratorType   sourceEnd_,
                                  DifferenceType offset_);

    constexpr IteratorType insert(InitializerListType ilist_, SizeType offset_ = 0);

    constexpr IteratorType replace_back(const ItemType& value_);
    constexpr IteratorType replace_front(const ItemType& value_);
    constexpr IteratorType replace(const ItemType& value_, SizeType offset_ = 0);


    /*********************************************************************/
    /* Memory ---------------------------------------------------------- */
    [[nodiscard]] constexpr SizeType length() const noexcept override;
    [[nodiscard]] constexpr SizeType capacity() const noexcept;
    [[nodiscard]] constexpr bool     is_empty() const noexcept override;
    [[nodiscard]] constexpr bool     is_not_empty() const noexcept override;

    constexpr void reserve(SizeType newCapacity_);
    constexpr void resize(SizeType newLength_);

    constexpr void clear();

    constexpr void shrink_to_fit();


    /*********************************************************************/
    /* Misc ------------------------------------------------------------ */
    [[nodiscard]] constexpr std::string to_string() const override;


    /*********************************************************************/
    /* Private methods ------------------------------------------------- */
    private:
    inline void vector_constructor(SizeType size_);

    constexpr void add_size(SizeType addedLength_);
    constexpr void change_size(SizeType newLength_);

    constexpr void check_fit(SizeType extraLength_);
    constexpr void check_if_valid(IteratorType iterator_);
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
