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
#include "./vector.hpp"

namespace pel
{


/**
 **************************************************************************************************
 * \brief       Overload of the left-shift << operator to print a vector's
 *              content to an output stream.
 *
 * \param       os_:  Left-hand-side output stream.
 * \param       vec_: Right-hand-side vector to print.
 *
 * \retval      std::ostream&: Reference the output stream after appending data.
 *
 * \note        This method is not directly part of the pel::vector class, and is rather appended
 *              to the std::ostream class.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
inline static std::ostream&
operator<<(std::ostream& os_, const vector<ItemType, AllocatorType>& vec_) noexcept
{
    /* Add capacity and length header */
    os_ << "Capacity : [" << vec_.capacity() << "]   |   Length: [" << vec_.length() << "]\n";

    for(ItemType& element : vec_)
    {
        os_ << element << '\n';
    }

    return os_;
}


/*************************************************************************************************/
/* CONSTRUCTORS & DESTRUCTORS ------------------------------------------------------------------ */
/*************************************************************************************************/

/**
 **************************************************************************************************
 * \brief       Constructor for the vector class.
 *
 * \param       length_: Number of elements to allocate.
 *              [defaults : 0]
 * \param       alloc_:  Allocator to use for all memory allocations
 *              [defaults : AllocatorType{}]
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
vector<ItemType, AllocatorType>::vector(SizeType length_, const AllocatorType& alloc_)
: m_allocator{alloc_}
{
    vector_constructor(length_);
}


/**
 **************************************************************************************************
 * \brief       Default-value constructor for the vector class.
 *
 * \param       length_: Number of elements to allocate.
 * \param       value_:  Value to initialize all the elements initially allocated with.
 * \param       alloc_:  Allocator to use for all memory allocations
 *              [defaults : AllocatorType{}]
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
vector<ItemType, AllocatorType>::vector(SizeType             length_,
                                        const ItemType&      value_,
                                        const AllocatorType& alloc_)
: m_allocator{alloc_}
{
    vector_constructor(length_);
    add_size(length_);

    /* clang-format off */
    std::for_each(begin(), end(),
                  [&](ItemType& item)
                  {
                      AllocatorTraits::construct(m_allocator, &item, value_);
                  });
    /* clang-format on */
}


/**
 **************************************************************************************************
 * \brief       Iterator-based copy constructor for the vector class.
 *
 * \param       beginIterator_: Begin iterator of another vector to start copying from.
 * \param       endIterator_:   End iterator of another vector to end the copy.
 * \param       alloc_:         Allocator to use for all memory allocations
 *              [defaults : AllocatorType{}]
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
vector<ItemType, AllocatorType>::vector(const IteratorType   beginIterator_,
                                        const IteratorType   endIterator_,
                                        const AllocatorType& alloc_)
: m_allocator{alloc_}
{
    vector_constructor(endIterator_ - beginIterator_);

    std::copy(beginIterator_, endIterator_, begin());
}


/**
 **************************************************************************************************
 * \brief       Move-based constructor for the vector class.
 *              Takes the arguments used to  an `ItemType` object, and forwards them.
 *
 * \param       length_ : Number of elements to create
 * \param       args_ :   Arguments to forward to the `ItemType` constructor
 * \param       alloc_:   Allocator to use for all memory allocations
 *              [defaults : AllocatorType{}]
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
template<typename... Args>
vector<ItemType, AllocatorType>::vector(SizeType length_,
                                        Args&&... args_,
                                        const AllocatorType& alloc_)
: m_allocator{alloc_}
{
    vector_constructor(length_);
    add_size(length_);

    /* clang-format off */
    auto builder = [&](ItemType& element)
                   {
                       AllocatorTraits::construct(m_allocator,
                                                  &element,
                                                  std::forward<Args>(args_)...);
                   };
    /* clang-format on */
    std::for_each(begin(), end(), builder);
}


/**
 **************************************************************************************************
 * \brief       Copy constructor for the vector class.
 *
 * \param       otherVector_: Vector to copy data from.
 * \param       alloc_:       Allocator to use for all memory allocations
 *              [defaults : AllocatorType{}]
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
template<typename OtherAllocatorType>
vector<ItemType, AllocatorType>::vector(const vector<ItemType, OtherAllocatorType>& otherVector_,
                                        const AllocatorType&                        alloc_)
: m_allocator{alloc_}
{
    vector_constructor(otherVector_.length());

    std::copy(otherVector_.begin(), otherVector_.begin(), begin());
}

template<typename ItemType, typename AllocatorType>
vector<ItemType, AllocatorType>&
vector<ItemType, AllocatorType>::operator=(const vector<ItemType, AllocatorType>& copy_)
{
    return operator=<ItemType, AllocatorType>(copy_);
}

/**
 **************************************************************************************************
 * \brief       Copy assignment operator for the vector class.
 *
 * \param       copy_: Vector to copy data from.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
template<typename OtherAllocatorType>
typename vector<ItemType, AllocatorType>&
vector<ItemType, AllocatorType>::operator=(const vector<ItemType, OtherAllocatorType>& copy_)
{
    vector_constructor(copy_.length());

    std::copy(copy_.begin(), copy_.begin(), begin());
    m_allocator = copy_.get_allocator();
}


/**
 **************************************************************************************************
 * \brief       Move constructor for the vector class.
 *
 * \param       otherVector_: Vector to move data from.
 * \param       alloc_:       Allocator to use for all memory allocations
 *              [defaults : AllocatorType{}]
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
template<typename OtherAllocatorType>
vector<ItemType, AllocatorType>::vector(vector<ItemType, OtherAllocatorType>&& move_,
                                        AllocatorType&                         alloc_)
: m_allocator{alloc_},
  m_beginIterator{std::move(move_.m_beginIterator)},
  m_endIterator{std::move(move_.m_endIterator)},
  m_capacity{move_.m_capacity}
{
}

/**
 **************************************************************************************************
 * \brief       Move assignment operator for the vector class.
 *
 * \param       move__: Vector to move data from.
 *
 * \note        Will do nothing if attempting to move a vector into itself
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
template<typename OtherAllocatorType>
typename vector<ItemType, AllocatorType>&
vector<ItemType, AllocatorType>::operator=(vector<ItemType, OtherAllocatorType>&& move_)
{
    if(this != std::addressof(move_))
    {
        /* Grab the other vector's resources */
        m_allocator     = move_.get_allocator();
        m_beginIterator = move_.begin();
        m_endIterator   = move_.end();
        m_capacity      = move_.capacity();

        /* Invalidate the other vector */
        move_.m_beginIterator = IteratorType{nullptr};
        move_.m_endIterator   = IteratorType{nullptr};
    }
    return *this;
}

/**
 **************************************************************************************************
 * \brief       Initializer list constructor for the vector class.
 *
 * \param       ilist_: Initializer list of all the values to put in a new vector.
 * \param       alloc_: Allocator to use for all memory allocations
 *              [defaults : AllocatorType{}]
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
vector<ItemType, AllocatorType>::vector(InitializerListType ilist_, const AllocatorType& alloc_)
: m_allocator{alloc_}
{
    vector_constructor(ilist_.size());

    std::copy(ilist_.begin(), ilist_.end(), begin());
    change_size(ilist_.size());
}


/**
 **************************************************************************************************
 * \brief       Destructor for the vector class.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
vector<ItemType, AllocatorType>::~vector()
{
    /* Free and destroy elements in the allocated memory */
    AllocatorTraits::deallocate(m_allocator, begin().ptr(), capacity());
}


/*************************************************************************************************/
/* ELEMENT ACCESSORS --------------------------------------------------------------------------- */
/*************************************************************************************************/

/**
 **************************************************************************************************
 * \brief       Obtain a reference to the element at a specified index in the vector.
 *
 * \param       index_: Index of the element to get.
 *
 * \retval      ItemType&: Reference to the item at the specified index.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
[[nodiscard]] inline ItemType&
vector<ItemType, AllocatorType>::at(SizeType index_)
{
    return this->operator[](index_);
}


/**
 **************************************************************************************************
 * \brief       Obtain a constant reference to the element at a specified index in the vector.
 *
 * \param       index_: Index of the element to get.
 *
 * \retval      ItemType&: Const reference to the item at the specified index.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
[[nodiscard]] inline const ItemType&
vector<ItemType, AllocatorType>::at(SizeType index_) const
{
    return this->operator[](index_);
}


/**
**************************************************************************************************
* \brief       Obtain the iterator to the element at the specified index.
*
* \param       index_: Index of the element to get.
*
* \retval      IteratorType: Iterator to the item at the specified index.
*************************************************************************************************/
template<typename ItemType, typename AllocatorType>
[[nodiscard]] inline typename vector<ItemType, AllocatorType>::IteratorType
vector<ItemType, AllocatorType>::iterator_at(DifferenceType index_) const
{
    return cbegin() + index_;
}


/**
 **************************************************************************************************
 * \brief       Get the element at the front of the vector.
 *
 * \retval      ItemType&: Element at the front of the vector.
 *
 * \throw       std::length_error
 *              If there was no memory allocated for the elements, accessing even just the first
 *              element would cause errors.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
[[nodiscard]] inline ItemType&
vector<ItemType, AllocatorType>::front()
{
    if constexpr(vector_safeness == true)
    {
        if(capacity() == 0)
        {
            throw std::length_error("Could not access element - No memory allocated");
        }
    }
    return *begin();
}


/**
 **************************************************************************************************
 * \brief       Get the element at the back of the vector.
 *
 * \retval      ItemType&: Element at the back of the vector.
 *
 * \throw       std::length_error
 *              If there was no memory allocated for the elements, accessing even just the first
 *              element would cause errors.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
[[nodiscard]] inline ItemType&
vector<ItemType, AllocatorType>::back()
{
    if constexpr(vector_safeness == true)
    {
        if(capacity() == 0)
        {
            throw std::length_error("Could not access element - No memory allocated");
        }
    }
    return *(end() - 1);
}


/**
 **************************************************************************************************
 * \brief       Get the const element at the front of the vector.
 *
 * \retval      ItemType&: Const element at the front of the vector.
 *
 * \throw       std::length_error
 *              If there was no memory allocated for the elements, accessing even just the first
 *              element would cause errors.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
[[nodiscard]] inline const ItemType&
vector<ItemType, AllocatorType>::front() const
{
    if constexpr(vector_safeness == true)
    {
        if(capacity() == 0)
        {
            throw std::length_error("Could not access element - No memory allocated");
        }
    }
    return *cbegin();
}


/**
 **************************************************************************************************
 * \brief       Get the const element at the back of the vector.
 *
 * \retval      ItemType&: Const element at the back of the vector.
 *
 * \throw       std::length_error
 *              If there was no memory allocated for the elements, accessing even just the first
 *              element would cause errors.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
[[nodiscard]] inline const ItemType&
vector<ItemType, AllocatorType>::back() const
{
    if constexpr(vector_safeness == true)
    {
        if(capacity() == 0)
        {
            throw std::length_error("Could not access element - No memory allocated");
        }
    }
    return *(end() - 1);
}


/**
 **************************************************************************************************
 * \brief       Get a pointer to the beginning of the vector's data space.
 *
 * \retval      ItemType*: Pointer to the beginning of the vector's data.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
[[nodiscard]] inline ItemType*
vector<ItemType, AllocatorType>::data() noexcept
{
    return begin().ptr();
}


/**
 **************************************************************************************************
 * \brief       Get a const pointer to the beginning of the vector's data space.
 *
 * \retval      ItemType*: Const pointer to the beginning of the vector's data.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
[[nodiscard]] inline const ItemType*
vector<ItemType, AllocatorType>::data() const noexcept
{
    return begin().ptr();
}


/**
 **************************************************************************************************
 * \brief       Return the index of an iterator from the start of the vector.
 *
 * \param       iterator_: Iterator in the vector to get the index of.
 *
 * \retval      SizeType: index of the iterator.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
[[nodiscard]] inline typename vector<ItemType, AllocatorType>::DifferenceType
vector<ItemType, AllocatorType>::index_of(IteratorType iterator_) const
{
    if constexpr(vector_safeness == true)
    {
        check_if_valid(iterator_);
    }

    return iterator_ - begin();
}


/**
 **************************************************************************************************
 * \brief       Assign a value to a certain offset in the vector for a certain amount of elements.
 *
 * \param       value_:  Value to assign to the vector.
 * \param       offset_: Offset at which data should be assigned.
 *              [defaults : 0]
 * \param       count_:  Number of elements to be assigned a new value.
 *              [defaults : 1]
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
inline void
vector<ItemType, AllocatorType>::assign(const ItemType& value_,
                                        DifferenceType  offset_,
                                        SizeType        count_)
{
    if constexpr(vector_safeness == true)
    {
        check_fit(count_);
    }

    std::fill_n(begin() + offset_, count_, value_);
}


/**
 **************************************************************************************************
 * \brief       Assign values to a certain offset in the vector through an initializer list.
 *
 * \param       ilist_:  Values to assign to the vector.
 * \param       offset_: Offset at which data should be assigned.
 *              [defaults : 0]
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
inline void
vector<ItemType, AllocatorType>::assign(InitializerListType ilist_, DifferenceType offset_)
{
    if constexpr(vector_safeness == true)
    {
        check_fit(ilist_.size());
    }

    std::copy(ilist_.begin(), ilist_.end(), begin() + offset_);
}


/*************************************************************************************************/
/* OPERATOR OVERLOADS -------------------------------------------------------------------------- */
/*************************************************************************************************/

/**
 **************************************************************************************************
 * \brief       Overload of the brackets[] operator to access an element at a specific index.
 *
 * \param       index_: Index of the element to access.
 *
 * \retval      ItemType&: Reference to the element at the index.
 *
 * \throws      std::length_error("Index out of range")
 *              If the index is out of the vector's length.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
[[nodiscard]] inline ItemType&
vector<ItemType, AllocatorType>::operator[](SizeType index_)
{
    if constexpr(vector_safeness == true)
    {
        if(index_ >= length())
        {
            throw std::length_error("Index out of range");
        }
    }

    return begin()[index_];
}


/**
 **************************************************************************************************
 * \brief       Overload of the brackets[] operator to access a const element at a specific index.
 *
 * \param       index_: Index of the element to access.
 *
 * \retval      ItemType&: Const reference to the element at the index.
 *
 * \throws      std::length_error("Index out of range")
 *              If the index is out of the vector's length.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
[[nodiscard]] inline const ItemType&
vector<ItemType, AllocatorType>::operator[](SizeType index_) const
{
    if constexpr(vector_safeness == true)
    {
        if(index_ >= length())
        {
            throw std::length_error("Index out of range!");
        }
    }

    return begin()[index_];
}


/**
 **************************************************************************************************
 * \brief       Overload of the arithmetic += operator to add an element at the end of the vector.
 *
 * \param       rhs_: Item at the right-hand-size of the addition, to be added at the end of the
 *                    vector.
 *
 * \retval      vector&: Reference the vector itself.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
inline vector<ItemType, AllocatorType>&
vector<ItemType, AllocatorType>::operator+=(const ItemType& rhs_)
{
    push_back(rhs_);
    return *this;
}


/**
 **************************************************************************************************
 * \brief       Overload of the post-increment ++ operator to reserve one element of memory at the
 *              end of the vector.
 *
 * \retval      vector&: Reference the vector itself.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
inline const vector<ItemType, AllocatorType>
vector<ItemType, AllocatorType>::operator++(int)
{
    reserve(capacity() + 1);
    return *this;
}


/**
 **************************************************************************************************
 * \brief       Overload of the post-decrement -- operator to free one element of memory at the end
 *              of the vector.
 *
 * \retval      vector&: Reference the vector itself.
 *
 * \note        If the shrinking of the capacity of the vector causes it to shrink smaller than
 *              it's current size, the last element of the vector will be popped back and
 *              destroyed (safely).
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
inline const vector<ItemType, AllocatorType>
vector<ItemType, AllocatorType>::operator--(int)
{
    if(capacity() == length())
    {
        pop_back();
    }

    reserve(capacity() - 1);
    return *this;
}


/**
 **************************************************************************************************
 * \brief       Overload of the right-shift >> operator to shift the vector's elements to the right.
 *
 * \param       steps_: Shifts to the rights.
 *
 * \retval      vector&: Reference the vector itself.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
inline vector<ItemType, AllocatorType>&
vector<ItemType, AllocatorType>::operator>>(int steps_)
{
    std::shift_right(cbegin(), cend(), steps_);

    return *this;
}


/**
 **************************************************************************************************
 * \brief       Overload of the left-shift << operator to shift the vector's elements to the left.
 *
 * \param       steps_: Shifts to the left.
 *
 * \retval      vector&: Reference the vector itself.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
inline vector<ItemType, AllocatorType>&
vector<ItemType, AllocatorType>::operator<<(int steps_)
{
    std::shift_left(cbegin(), cend(), steps_);

    return *this;
}


/*************************************************************************************************/
/* ITERATORS ----------------------------------------------------------------------------------- */
/*************************************************************************************************/

/**
 **************************************************************************************************
 * \brief       Returns an iterator to the beginning of the allocated data.
 *
 * \retval      IteratorType: Iterator to the start of the vector's memory.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
[[nodiscard]] inline typename vector<ItemType, AllocatorType>::IteratorType
vector<ItemType, AllocatorType>::begin() const noexcept
{
    return m_beginIterator;
}


/**
 **************************************************************************************************
 * \brief       Returns an iterator to the end of the allocated data.
 *
 * \retval      IteratorType: Iterator to the end of the vector's memory.
 *
 * \note        This iterator does not point directly to the end of the memory, but to one element
 *              after the end of the memory.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
[[nodiscard]] inline typename vector<ItemType, AllocatorType>::IteratorType
vector<ItemType, AllocatorType>::end() const noexcept
{
    return m_endIterator;
}


/**
 **************************************************************************************************
 * \brief       Returns a const iterator to the beginning of the allocated data.
 *
 * \retval      IteratorType: Const iterator to the start of the vector's memory.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
[[nodiscard]] inline const typename vector<ItemType, AllocatorType>::IteratorType
vector<ItemType, AllocatorType>::cbegin() const noexcept
{
    return m_beginIterator;
}


/**
 **************************************************************************************************
 * \brief       Returns a const iterator to the end of the allocated data.
 *
 * \retval      IteratorType: Const iterator to the end of the vector's memory.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
[[nodiscard]] inline const typename vector<ItemType, AllocatorType>::IteratorType
vector<ItemType, AllocatorType>::cend() const noexcept
{
    return m_endIterator;
}


/**
 **************************************************************************************************
 * \brief       Returns a reverse iterator to the reversed beginning of the allocated data.
 *
 * \retval      IteratorType: Iterator to the reversed start of the vector's memory.
 *                            (end - 1)
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
[[nodiscard]] inline typename vector<ItemType, AllocatorType>::RIteratorType
vector<ItemType, AllocatorType>::rbegin() const noexcept
{
    return RIteratorType(end());
}


/**
 **************************************************************************************************
 * \brief       Returns a reverse iterator to the reversed end of the allocated data.
 *
 * \retval      IteratorType: Iterator to the reversed of the vector's memory.
 *                            (begin - 1)
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
[[nodiscard]] inline typename vector<ItemType, AllocatorType>::RIteratorType
vector<ItemType, AllocatorType>::rend() const noexcept
{
    return RIteratorType(begin());
}


/**
 **************************************************************************************************
 * \brief       Returns a const reverse iterator to the reversed beginning of the allocated data.
 *
 * \retval      IteratorType: Const iterator to the reversed start of the vector's memory.
 *                            (end - 1)
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
[[nodiscard]] inline const typename vector<ItemType, AllocatorType>::RIteratorType
vector<ItemType, AllocatorType>::crbegin() const noexcept
{
    return RIteratorType(end());
}


/**
 **************************************************************************************************
 * \brief       Returns a const reverse iterator to the reversed end of the allocated data.
 *
 * \retval      IteratorType: Const iterator to the reversed of the vector's memory.
 *                            (begin - 1)
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
[[nodiscard]] inline const typename vector<ItemType, AllocatorType>::RIteratorType
vector<ItemType, AllocatorType>::crend() const noexcept
{
    return RIteratorType(begin());
}


/*************************************************************************************************/
/* ELEMENT MANAGEMENT -------------------------------------------------------------------------- */
/*************************************************************************************************/

/**
 **************************************************************************************************
 * \brief       Add an element to the end of the vector, after the current last item.
 *
 * \param       value_: Element to push back at the end of the vector.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
inline void
vector<ItemType, AllocatorType>::push_back(const ItemType& value_)
{
    check_fit(1);

    end().value() = value_;
    add_size(1);
}


/**
 **************************************************************************************************
 * \brief       Add elements from an initializer list to the end of the vector, after the current
 *              last item.
 *
 * \param       ilist_: Initializer list containing elements to push back at the end of the vector.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
inline void
vector<ItemType, AllocatorType>::push_back(const InitializerListType ilist_)
{
    check_fit(ilist_.size());

    std::copy(ilist_.begin(), ilist_.end(), end());
    add_size(ilist_.size());
}


/**
 **************************************************************************************************
 * \brief       Remove the last element of the vector.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
inline void
vector<ItemType, AllocatorType>::pop_back()
{
    if(length() == 0)
    {
        return;
    }

    std::destroy_at(--end());
}


/**
 **************************************************************************************************
 * \brief       Constructs an element at the last position.
 *              This function is often to be favored instead of 'push_back' when building new
 *              items, since it avoids a copy.
 *
 * \param       args: The arguments needed to be passed to the constructor of an element.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
template<typename... Args>
inline void
vector<ItemType, AllocatorType>::emplace_back(Args&&... args_)
{
    check_fit(1);

    end().value() = ItemType(std::forward<Args>(args_)...);

    add_size(1);
}


/**
 **************************************************************************************************
 * \brief       Constructs an element in the middle of the vector, right-shifting items on the
 *              right to fit.
 *
 * \param       position_: Position in vector to insert the element.
 * \param       count_:    Number of elements to insert from the initial offset.
 * \param       args:      The arguments needed to be passed to the constructor of an element.
 *
 * \retval      IteratorType: Position at which the element has been constructed.
 *                            (if multiple elements have been inserted, return position of the last
 *                             inserted element).
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
template<typename... Args>
inline typename vector<ItemType, AllocatorType>::IteratorType
vector<ItemType, AllocatorType>::emplace(IteratorType position_, SizeType count_, Args&&... args_)
{
    if constexpr(vector_safeness == true)
    {
        check_if_valid(position_);
    }

    check_fit(count_);
    add_size(count_);

    std::shift_right(position_, end(), count_);

    for(SizeType i = 0; i < count_; i++)
    {
        position_[i] = ItemType(std::forward<Args>(args_)...);
    }

    return position_ + count_;
}


/**
**************************************************************************************************
* \brief       Constructs an element in the middle of the vector, right-shifting items on the
*              right to fit.
*
* \param       offset_:   Position to insert the element at.
* \param       count_:    Number of elements to insert from the initial offset.
* \param       args:      The arguments needed to be passed to the constructor of an element.
*
* \retval      IteratorType: Position at which the element has been constructed.
*                            (if multiple elements have been inserted, return position of the last
*                             inserted element).
*************************************************************************************************/
template<typename ItemType, typename AllocatorType>
template<typename... Args>
inline typename vector<ItemType, AllocatorType>::IteratorType
vector<ItemType, AllocatorType>::emplace(DifferenceType offset_, SizeType count_, Args&&... args_)
{
    IteratorType position = cbegin() + offset_;

    return emplace(position, count_, std::forward<Args>(args)...);
}


/**
 **************************************************************************************************
 * \brief       Insert an element in the middle of the vector, right-shifting items on the right to
 *              fit.
 *
 * \param       value_:    Element to insert in the vector.
 * \param       position_: Position in vector to insert the element.
 * \param       count_:    Number of elements to insert from the initial offset.
 *                         [defaults : 1]
 *
 * \retval      IteratorType: Position at which the element has been inserted.
 *                            (if multiple elements have been inserted, return position of the last
 *                             inserted element).
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
inline typename vector<ItemType, AllocatorType>::IteratorType
vector<ItemType, AllocatorType>::insert(const ItemType&    value_,
                                        const IteratorType position_,
                                        SizeType           count_)
{
    if constexpr(vector_safeness == true)
    {
        check_if_valid(position_);
    }

    check_fit(count_);
    add_size(count_);

    std::shift_right(position_, end(), count_);

    for(SizeType i = 0; i < count_; i++)
    {
        position_[i] = value_;
    }

    return position_ + count_;
}


/**
 **************************************************************************************************
 * \brief       Insert an element in the middle of the vector, right-shifting items on the right to
 *              fit.
 *
 * \param       value_:  Element to insert in the vector.
 * \param       offset_: Position to insert the element at.
 * \param       count_:  Number of elements to insert from the initial offset.
 *                       [defaults : 1]
 *
 * \retval      IteratorType: Position at which the element has been inserted.
 *                            (if multiple elements have been inserted, return position of the last
 *                             inserted element).
 *
 * \throws      std::invalid_argument("Invalid insert offset")
 *              Offset was out of bounds.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
inline typename vector<ItemType, AllocatorType>::IteratorType
vector<ItemType, AllocatorType>::insert(const ItemType& value_,
                                        DifferenceType  offset_,
                                        SizeType        count_)
{
    IteratorType position = cbegin() + offset_;

    return insert(value_, position, count_);
}


/**
 **************************************************************************************************
 * \brief       Insert elements in the middle of the vector from another vector, right-shifting
 *              items on the right to fit.
 *
 * \param       sourceBegin_: Begin iterator from another vector.
 * \param       sourceEnd_:   End iterator from another vector.
 * \param       position_:    Position in vector to start copy-inserting data at.
 *
 * \retval      IteratorType: Position at which the element has been inserted.
 *                            (if multiple elements have been inserted, return position of the last
 *                             inserted element).
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
inline typename vector<ItemType, AllocatorType>::IteratorType
vector<ItemType, AllocatorType>::insert(const IteratorType sourceBegin_,
                                        const IteratorType sourceEnd_,
                                        const IteratorType position_)
{
    if constexpr(vector_safeness == true)
    {
        check_if_valid(position_);
    }

    SizeType sourceSize = sourceEnd_ - sourceBegin_;

    check_fit(sourceSize);
    add_size(sourceSize);

    std::shift_right(position_, cend(), sourceSize);
    std::copy(sourceBegin_, sourceEnd_, position_);

    return position_ + sourceSize;
}


/**
 **************************************************************************************************
 * \brief       Insert elements in the middle of the vector from another vector, right-shifting
 *              items on the right to fit.
 *
 * \param       sourceBegin_: Begin iterator from another vector.
 * \param       sourceEnd_:   End iterator from another vector.
 * \param       offset_:      Offset in vector to start copy-inserting data at.
 *              [defaults : 0]
 *
 * \retval      IteratorType: Position at which the element has been inserted.
 *                            (if multiple elements have been inserted, return position of the last
 *                             inserted element).
 *
 * \throws      std::invalid_argument("Invalid insert offset")
 *              Offset was out of bounds.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
inline typename vector<ItemType, AllocatorType>::IteratorType
vector<ItemType, AllocatorType>::insert(const IteratorType sourceBegin_,
                                        const IteratorType sourceEnd_,
                                        DifferenceType     offset_)
{
    if constexpr(vector_safeness)
    {
        if(offset_ > length())
        {
            throw std::invalid_argument("Invalid insert offset");
        }
    }

    IteratorType position = cbegin() + offset_;

    return insert(sourceBegin_, sourceEnd_, position);
}


/**
 **************************************************************************************************
 * \brief       Insert elements in the middle of the vector from an initializer list,
 *              right-shifting items on the right to fit.
 *
 * \param       ilist_:  Initializer list containing element to copy-insert into vector.
 * \param       offset_: Offset in vector to start copy-inserting data at.
 *                       [defaults : 0]
 *
 * \retval      IteratorType: Position at which the element has been inserted.
 *                            (if multiple elements have been inserted, return position of the last
 *                             inserted element).
 *
 * \throws      std::invalid_argument("Invalid insert offset")
 *              Offset was out of bounds.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
inline typename vector<ItemType, AllocatorType>::IteratorType
vector<ItemType, AllocatorType>::insert(const InitializerListType ilist_, SizeType offset_)
{
    if constexpr(vector_safeness == true)
    {
        if(offset_ > length())
        {
            throw std::invalid_argument("Invalid insert offset");
        }
    }

    IteratorType position = cbegin() + offset_;

    return insert(ilist_.begin(), ilist_.end(), position);
}


/**
 **************************************************************************************************
 * \brief       Replace the element at a specified position with a new element.
 *
 * \param       value_:  Value that will replace element.
 * \param       offset_: Position of the element to replace.
 *                       [defaults : cbegin()]
 *
 * \retval      IteratorType: Position at which the element has been replaced.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
inline typename vector<ItemType, AllocatorType>::IteratorType
vector<ItemType, AllocatorType>::replace(const ItemType& value_, SizeType offset_)
{
    at(offset_) = value_;

    return begin() + offset_;
}


/**
 **************************************************************************************************
 * \brief       Replace the last element with a new element.
 *
 * \param       value_: Value that will replace element.
 *
 * \retval      IteratorType: Iterator to the element that was replaced.
 *                            (end iterator - 1)
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
inline typename vector<ItemType, AllocatorType>::IteratorType
vector<ItemType, AllocatorType>::replace_back(const ItemType& value_)
{
    IteratorType position = end() - 1;

    position.value() = value_;
    return position;
}


/**
 **************************************************************************************************
 * \brief       Replace the first element with a new element.
 *
 * \param       value_: Value that will replace element.
 *
 * \retval      IteratorType: Iterator to the element that was replaced.
 *                            (begin iterator)
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
inline typename vector<ItemType, AllocatorType>::IteratorType
vector<ItemType, AllocatorType>::replace_front(const ItemType& value_)
{
    IteratorType position = begin();

    position.value() = value_;
    return position;
}


/*************************************************************************************************/
/* MEMORY -------------------------------------------------------------------------------------- */
/*************************************************************************************************/

/**
 **************************************************************************************************
 * \brief       Simple accessor, return the length (number of elements) of the vector.
 *
 * \retval      SizeType: Number of elements of the vector.
 *
 * \note        Equivalent to std::vector's `size()` method.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
[[nodiscard]] inline typename vector<ItemType, AllocatorType>::SizeType
vector<ItemType, AllocatorType>::length() const noexcept
{
    DifferenceType diff = end() - begin();
    return static_cast<SizeType>(diff);
}


/**
 **************************************************************************************************
 * \brief       Simple accessor, return the capacity (allocated size) of the vector.
 *
 * \retval      SizeType: Elements that can fit in the allocated space.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
[[nodiscard]] inline typename vector<ItemType, AllocatorType>::SizeType
vector<ItemType, AllocatorType>::capacity() const noexcept
{
    return m_capacity;
}


/**
 **************************************************************************************************
 * \brief       Simple accessor, returns true if there are no elements in the vector.
 *
 * \retval      bool: True if there are no elements in the vector.
 *                    False if there are elements in the vector.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
[[nodiscard]] inline bool
vector<ItemType, AllocatorType>::is_empty() const noexcept
{
    return length() == 0;
}


/**
 **************************************************************************************************
 * \brief       Simple accessor, returns true if there are elements in the vector.
 *
 * \retval      bool: True if there are elements in the vector.
 *                    False if there are not elements in the vector.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
[[nodiscard]] inline bool
vector<ItemType, AllocatorType>::is_not_empty() const noexcept
{
    return !is_empty();
}

/**
 **************************************************************************************************
 * \brief       Simple accessor, returns a const reference to the vector's allocator.
 *
 * \retval      AllocatorType&: The vector's allocator
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
[[nodiscard]] const AllocatorType&
vector<ItemType, AllocatorType>::get_allocator() const noexcept
{
    return m_allocator;
}


/**
 **************************************************************************************************
 * \brief       Allocate memory for the vector.
 *
 * \param       newCapacity_: Size in elements of the memory to allocate.
 *
 * \note        This function works for shrinking as well as expanding the vector's allocated
 *              memory space.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
inline void
vector<ItemType, AllocatorType>::reserve(SizeType newCapacity_)
{
    /* Check if resizing is necessary */
    if(newCapacity_ == capacity())
    {
        return;
    }

    /* Allocate a new memory segment */
    vector_constructor(newCapacity_);
}


/**
 **************************************************************************************************
 * \brief       Change amount of elements currently stocked in the vector.
 *
 * \param       newLength_: Size in elements of the vector.
 *
 * \note        This function is different than \ref reserve().
 *              \ref reserve() allocates memory space, but doesn't make changes to  the iterators
 *              or elements (unless shrinking below current vector's length).
 *              resize() changes the amount of elements contained in the vector, and can call
 *              \ref reserve() if in need of more memory.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
inline void
vector<ItemType, AllocatorType>::resize(SizeType newLength_)
{
    /* Check if reserving memory is necessary */
    if(newLength_ > capacity())
    {
        reserve(newLength_);
    }

    /* Check if freeing some memory is necessary */
    /** \todo */

    /* Resize */
    change_size(newLength_);
}


/**
 **************************************************************************************************
 * \brief       Destroy all elements currently in the vector and set its length to 0.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
inline void
vector<ItemType, AllocatorType>::clear()
{
    std::destroy(begin(), end());

    m_endIterator = cbegin();
}


/**
 **************************************************************************************************
 * \brief       Shrink allocated memory to fit exactly the number of elements currently being
 *              contained in the vector.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
inline void
vector<ItemType, AllocatorType>::shrink_to_fit()
{
    if(length() == capacity())
    {
        return;
    }

    reserve(length());
}


/*************************************************************************************************/
/* MISC ---------------------------------------------------------------------------------------- */
/*************************************************************************************************/

/**
 **************************************************************************************************
 * \brief       Convert the content of a vector to a string.
 *
 * \retval      A string containing the capacity, the size, and all the elements converted to a
 *              string.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
[[nodiscard]] inline std::string
vector<ItemType, AllocatorType>::to_string() const
{
    std::ostringstream os;
    os << *this;
    return os.str();
}


/*************************************************************************************************/
/* PRIVATE METHODS ----------------------------------------------------------------------------- */
/*************************************************************************************************/

/**
 **************************************************************************************************
 * \brief       Allocates or reallocates memory on the heap. Also resize iterators.
 *
 * \param       size_: Size (in elements) to allocate.
 *
 * \throws      std::bad_alloc: Could not allocate block of memory.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
inline void
vector<ItemType, AllocatorType>::vector_constructor(SizeType size_)
{
    /* Reallocate block of memory */
    ItemType* tempPtr = AllocatorTraits::allocate(m_allocator, size_);
    ItemType* oldPtr  = begin().ptr();

    /* Move data from old vector memory to new memory */
    std::move(begin(), end(), tempPtr);

    /* Set iterators */
    DifferenceType diff = length();
    m_beginIterator     = IteratorType(static_cast<ItemType*>(tempPtr));
    m_endIterator       = IteratorType(begin() + diff);

    /* Deallocate old memory */
    m_allocator.deallocate(oldPtr, capacity());
    m_capacity = size_;
}


/**
 **************************************************************************************************
 * \brief       Add a number of elements to the current length of the vector.
 *
 * \param       addedLength_: Numbers of elements to add to the current length.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
inline void
vector<ItemType, AllocatorType>::add_size(SizeType addedLength_)
{
    change_size(length() + addedLength_);
}


/**
 **************************************************************************************************
 * \brief       Change the current length (in elements) of the vector.
 *
 * \param       newLength_: New length (in elements) of the vector.
 *
 * \warning     This function does not check if the capacity is big enough before modifying the
 *              length of the vector.
 *              It should only be called when sure that the vector can hold all the added elements.
 *              (using a function such as \ref check_fit() is recommended).
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
inline void
vector<ItemType, AllocatorType>::change_size(SizeType newLength_)
{
    m_endIterator = IteratorType(&(begin()[newLength_]));
}


/**
 **************************************************************************************************
 * \brief       Check if the vector is big enough to hold the required extra elements.
 *              If it is not currently big enough, reserve some memory.
 *
 * \param       extraLength_: Numbers of elements to add to the current length.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
inline void
vector<ItemType, AllocatorType>::check_fit(SizeType extraLength_)
{
    if(length() + extraLength_ > capacity())
    {
        reserve(capacity() + m_stepSize() + extraLength_);
    }
}


/**
 **************************************************************************************************
 * \brief       Check if an iterator is located within the vector's bounds.
 *              If it is not, throw an exception.
 *
 * \param       iterator_: Iterator to check.
 *
 * \throws      std::invalid_argument("Invalid iterator"):
 *              If the iterator does not belong in the vector's boundaries.
 *************************************************************************************************/
template<typename ItemType, typename AllocatorType>
inline void
vector<ItemType, AllocatorType>::check_if_valid(IteratorType iterator_)
{
    if constexpr(vector_safeness == true)
    {
        if((iterator_ < cbegin()) || (iterator_ > cend()))
        {
            throw std::invalid_argument("Invalid iterator");
        }
    }
}

}        // namespace pel

/*************************************************************************************************/
/* END OF FILE --------------------------------------------------------------------------------- */
/*************************************************************************************************/
