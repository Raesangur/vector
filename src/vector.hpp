/**
 * \file
 * \author  Pascal-Emmanuel Lachance
 * \p       https://www.github.com/Raesangur
 * ------------------------------------------------------------------------------------------------
 * MIT License
 * Copyright (c) 2020 Pascal-Emmanuel Lachance | Ràësangür
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#pragma once

/*************************************************************************************************/
/* File includes ------------------------------------------------------------------------------- */
#include "./container_base/src/container_base.hpp"

#include <algorithm>
#include <compare>
#include <functional>
#include <memory>
#include <ostream>
#include <sstream>
#include <stdexcept>


namespace pel
{
constexpr bool vector_safeness = true;

template<typename ItemType>
using vector_iterator = iterator_base<ItemType>;

template<typename ItemType, typename AllocatorType = std::allocator<ItemType>>
class vector : public container_base<ItemType, vector_iterator<ItemType>, AllocatorType>
{
    static_assert(std::is_same_v<ItemType, typename AllocatorType::value_type>,
                  "Allocator must match element type");

public:
    /*********************************************************************************************/
    /* Type definitions ------------------------------------------------------------------------ */
    using AllocatorTraits = std::allocator_traits<AllocatorType>;

    using SizeType            = std::size_t;
    using DifferenceType      = std::ptrdiff_t;
    using IteratorType        = vector_iterator<ItemType>;
    using RIteratorType       = typename IteratorType::ReverseIteratorType;
    using InitializerListType = std::initializer_list<ItemType>;


    /*********************************************************************************************/
    /* Constructors ---------------------------------------------------------------------------- */
    explicit vector(SizeType length_ = 0, const AllocatorType& alloc_ = AllocatorType{});
    explicit vector(SizeType             length_,
                    const ItemType&      value_,
                    const AllocatorType& alloc_ = AllocatorType{});
    explicit vector(IteratorType         beginIterator_,
                    IteratorType         endIterator_,
                    const AllocatorType& alloc_ = AllocatorType{});

    /*-----------------------------------------------*/
    /* Copy constructor and copy-assignment operator */
    template<typename OtherAllocatorType = AllocatorType>
    explicit vector(const vector<ItemType, OtherAllocatorType>& otherVector_,
                    const AllocatorType&                        alloc_ = AllocatorType{});
    explicit vector(const vector& otherVector_);
    template<typename OtherAllocatorType = AllocatorType>
    vector& operator=(const vector<ItemType, OtherAllocatorType>& copy_);
    vector& operator=(const vector& copy_);

    /*-----------------------------------------------*/
    /* Move constructor and move-assignment operator */
    template<typename OtherAllocatorType = AllocatorType>
    explicit vector(vector<ItemType, OtherAllocatorType>&& move_,
                    AllocatorType&                         alloc_ = AllocatorType{});
    template<typename OtherAllocatorType = AllocatorType>
    vector& operator=(vector<ItemType, OtherAllocatorType>&& move_);


    /*----------------------*/
    /* Special constructors */
    vector(InitializerListType ilist_, const AllocatorType& alloc_ = AllocatorType{});

    template<typename... Args>
    explicit vector(SizeType length_,
                    Args&&... args_,
                    const AllocatorType& alloc_ = AllocatorType{});

    explicit vector(SizeType                      length_,
                    std::function<ItemType(void)> function_,
                    const AllocatorType&          alloc_ = AllocatorType{});

    /*------------*/
    /* Destructor */
    ~vector() override;


    /*********************************************************************************************/
    /* Element accessors ----------------------------------------------------------------------- */
    [[nodiscard]] ItemType*       data() noexcept;
    [[nodiscard]] const ItemType* data() const noexcept;

    void assign(const ItemType& value_, DifferenceType offset_ = 0, SizeType count_ = 1);
    void assign(InitializerListType ilist_, DifferenceType offset_ = 0);


    /*********************************************************************************************/
    /* Operator overloads ---------------------------------------------------------------------- */
    [[nodiscard]] ItemType&       operator[](SizeType index_) override;
    [[nodiscard]] const ItemType& operator[](SizeType index_) const override;

    vector<ItemType, AllocatorType>& operator+=(const ItemType& rhs_);

    const vector<ItemType, AllocatorType> operator++(int);
    const vector<ItemType, AllocatorType> operator--(int);

    vector<ItemType, AllocatorType>& operator>>(int steps_);
    vector<ItemType, AllocatorType>& operator<<(int steps_);


    /*********************************************************************************************/
    /* Element management ---------------------------------------------------------------------- */
    void pop_back();
    void push_back(const ItemType& value_);
    void push_back(InitializerListType ilist_);
    template<typename OtherAllocatorType = AllocatorType>
    void push_back(const vector<ItemType, OtherAllocatorType>& otherVector_);

    template<typename... Args>
    void emplace_back(Args&&... args_);

    template<typename... Args>
    IteratorType emplace(IteratorType position_, SizeType count_, Args&&... args_);

    template<typename... Args>
    IteratorType emplace(DifferenceType offset_, SizeType count_, Args&&... args_);

    IteratorType insert(const ItemType& value_, IteratorType position_, SizeType count_ = 1);

    IteratorType insert(const ItemType& value_, DifferenceType offset_, SizeType count_ = 1);

    IteratorType insert(IteratorType sourceBegin_, IteratorType sourceEnd_, IteratorType position_);

    IteratorType insert(IteratorType   sourceBegin_,
                        IteratorType   sourceEnd_,
                        DifferenceType offset_ = 0);

    IteratorType insert(InitializerListType ilist_, SizeType offset_ = 0);


    IteratorType replace_back(const ItemType& value_);
    IteratorType replace_front(const ItemType& value_);
    IteratorType replace(const ItemType& value_, SizeType offset_ = 0);


    /*********************************************************************************************/
    /* Memory ---------------------------------------------------------------------------------- */
    [[nodiscard]] SizeType capacity() const noexcept;

    void reserve(SizeType newCapacity_);
    void resize(SizeType newLength_);

    void shrink_to_fit();


    /*********************************************************************************************/
    /* Misc ------------------------------------------------------------------------------------ */
    [[nodiscard]] std::string to_string() const override;


    /*********************************************************************************************/
    /* Private methods ------------------------------------------------------------------------- */
private:
    void vector_constructor(SizeType size_);

    void add_size(SizeType addedLength_);
    void change_size(SizeType newLength_);

    void check_fit(SizeType extraLength_);

    SizeType step_size() noexcept;


    /*********************************************************************************************/
    /* Variables ------------------------------------------------------------------------------- */
private:
    SizeType      m_capacity      = 0;
    SizeType      m_stepSize      = 4;
};

}        // namespace pel


#include "./vector.inl"

/*************************************************************************************************/
/* ----- END OF FILE ----- */
