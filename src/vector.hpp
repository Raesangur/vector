/**
 * @file    vector.hpp
 * @author  Pascal-Emmanuel Lachance
 * @p       https://www.github.com/Raesangur
 * ----------------------------------------------------------------------------
 * MIT License
 * Copyright (c) 2020 Pascal-Emmanuel Lachance | Ràësangür
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#pragma once

/*****************************************************************************/
/* File includes ----------------------------------------------------------- */
#include "./container_base/src/container_base.h"

#include <algorithm>
#include <cstdlib>
#include <memory>
#include <ostream>
#include <sstream>
#include <stdexcept>


namespace pel
{
{
/** @todo Emplace_back function to construct at the end instead of copy at the end */
/** @todo Clear Clang-Tidy warnings */
/** @todo Lambda constructor */
/** @todo Use new and delete operators rather than realloc and free */
/** @todo Free memory automatically when not needed */
/** @todo make things actually constexpr */
/** @todo working reverse iterators */
/** @todo Increase allocation step size automatically when needed */
/**       @todo Make allocation step sizes align with the implementation's
                memory allocations alignments and sizes. */


constexpr bool vector_safeness = true;

template<typename ItemType>
using vector_iterator = iterator_base<ItemType>;

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

    /* Constructors */
    explicit vector(SizeType length_ = 0);
    explicit vector(SizeType length_, const ItemType& defaultValue_);
    explicit vector(IteratorType beginIterator_, IteratorType endIterator_);
    vector(InitializerListType ilist_);
    vector(const vector<ItemType>& otherVector_);
    vector& operator=(const vector<ItemType>& copy_);
    vector(vector<ItemType>&& movedVector_) noexcept;
    vector& operator=(vector<ItemType>&& move_) noexcept;

    /* Destructor */
    ~vector() override;


    /*********************************************************************/
    /* Element accessors ----------------------------------------------- */
    [[nodiscard]] ItemType&       at(SizeType index_) override;
    [[nodiscard]] const ItemType& at(SizeType index_) const override;

    [[nodiscard]] ItemType&       front() override;
    [[nodiscard]] ItemType&       back() override;
    [[nodiscard]] const ItemType& front() const override;
    [[nodiscard]] const ItemType& back() const override;

    [[nodiscard]] ItemType*       data() noexcept;
    [[nodiscard]] const ItemType* data() const noexcept;


    [[nodiscard]] DifferenceType index_of(IteratorType iterator_) const;

    void assign(const ItemType& value_, DifferenceType offset_ = 0, SizeType count_ = 1);
    void assign(InitializerListType ilist_, DifferenceType offset_ = 0);


    /*********************************************************************/
    /* Operator overloads ---------------------------------------------- */
    [[nodiscard]] ItemType&       operator[](SizeType index_) override;
    [[nodiscard]] const ItemType& operator[](SizeType index_) const override;

    vector<ItemType>& operator+=(const ItemType& rhs_);

    const vector<ItemType> operator++(int);
    const vector<ItemType> operator--(int);

    vector<ItemType>& operator>>(int steps_);
    vector<ItemType>& operator<<(int steps_);


    /*********************************************************************/
    /* Iterators ------------------------------------------------------- */
    [[nodiscard]] IteratorType        begin() const noexcept override;
    [[nodiscard]] IteratorType        end() const noexcept override;
    [[nodiscard]] const IteratorType  cbegin() const noexcept override;
    [[nodiscard]] const IteratorType  cend() const noexcept override;
    [[nodiscard]] RIteratorType       rbegin() const noexcept;
    [[nodiscard]] RIteratorType       rend() const noexcept;
    [[nodiscard]] const RIteratorType crbegin() const noexcept;
    [[nodiscard]] const RIteratorType crend() const noexcept;


    /*********************************************************************/
    /* Element management ---------------------------------------------- */
    void push_back(const ItemType& value_);
    void push_back(InitializerListType ilist_);
    void pop_back();


    IteratorType insert(const ItemType& value_,
                                  IteratorType    position_,
                                  SizeType        count_ = 1);

    IteratorType insert(const ItemType& value_,
                                  DifferenceType  offset_,
                                  SizeType        count_ = 1);

    IteratorType insert(IteratorType sourceBegin_,
                                  IteratorType sourceEnd_,
                                  IteratorType position_);

    IteratorType insert(IteratorType   sourceBegin_,
                                  IteratorType   sourceEnd_,
                                  DifferenceType offset_ = 0);

    IteratorType insert(InitializerListType ilist_, SizeType offset_ = 0);

    IteratorType replace_back(const ItemType& value_);
    IteratorType replace_front(const ItemType& value_);
    IteratorType replace(const ItemType& value_, SizeType offset_ = 0);


    /*********************************************************************/
    /* Memory ---------------------------------------------------------- */
    [[nodiscard]] SizeType length() const noexcept override;
    [[nodiscard]] SizeType capacity() const noexcept;
    [[nodiscard]] bool     is_empty() const noexcept override;
    [[nodiscard]] bool     is_not_empty() const noexcept override;

    void reserve(SizeType newCapacity_);
    void resize(SizeType newLength_);

    void clear();

    void shrink_to_fit();


    /*********************************************************************/
    /* Misc ------------------------------------------------------------ */
    [[nodiscard]] std::string to_string() const override;


    /*********************************************************************/
    /* Private methods ------------------------------------------------- */
    private:
    inline void vector_constructor(SizeType size_);

    void add_size(SizeType addedLength_);
    void change_size(SizeType newLength_);

    void check_fit(SizeType extraLength_);
    void check_if_valid(IteratorType iterator_);


    /*********************************************************************/
    /* Variables ------------------------------------------------------- */
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
};

};        // namespace pel

#include "./vector.inl"
