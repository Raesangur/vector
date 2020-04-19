#pragma once
#include "./vector.hpp"

/*****************************************************************************/
/* CONSTRUCTORS & DESTRUCTORS ---------------------------------------------- */
/*****************************************************************************/
#pragma region Constructors
/******************************************************************************
 * @brief       Constructor for the vector class
 *
 * @param       SizeType length: Number of elements to allocate
 *              [defaults : 0]
 *
 * @retval      Constructed vector
 *****************************************************************************/
template<typename ItemType>
constexpr pel::vector<ItemType>::vector(SizeType length) : m_length(length)
{
    vector_constructor(length);
}


/******************************************************************************
 * @brief       Default-value constructor for the vector class
 *
 * @param       SizeType length: Number of elements to allocate
 * @param       ItemType& defaultValue:
 *              Value to initialize all the elements initially allocated with
 *
 * @retval      Constructed vector
 *****************************************************************************/
template<typename ItemType>
constexpr pel::vector<ItemType>::vector(SizeType length, const ItemType& defaultValue)
: m_length(length)
{
    vector_constructor(length);

    std::fill(this->begin(), this->end(), defaultValue);
}


/******************************************************************************
 * @brief       Iterator-based copy constructor for the vector class
 *
 * @param       IteratorType beginIterator:
 *              Begin iterator of another vector to start copying from.
 * @param       IteratorType endIterator:
 *              End iterator of another vector to end the copy.
 *
 * @retval      Constructed vector
 *****************************************************************************/
template<typename ItemType>
constexpr pel::vector<ItemType>::vector(const IteratorType beginIterator,
                                        const IteratorType endIterator)
{
    m_length = endIterator - beginIterator;
    vector_constructor(length());

    std::copy(beginIterator, endIterator, begin());
}


/******************************************************************************
 * @brief       Copy constructor for the vector class
 *
 * @param       vector& otherVector: Vector to copy data from.
 *
 * @retval      Constructed vector
 *****************************************************************************/
template<typename ItemType>
constexpr pel::vector<ItemType>::vector(const vector<ItemType>& otherVector)
{
    m_length = otherVector.m_length;
    vector_constructor(length());

    std::copy(
      otherVector.m_beginIterator.ptr(), otherVector.m_endIterator.ptr(), m_beginIterator.ptr());
}


/******************************************************************************
 * @brief       Initializer list constructor for the vector class
 *
 * @param       std::initializer_list ilist:
 *              Initializer list of all the values to put in a new vector.
 *
 * @retval      Constructed vector
 *****************************************************************************/
template<typename ItemType>
constexpr pel::vector<ItemType>::vector(InitializerListType ilist) : m_length(ilist.size())
{
    vector_constructor(length());

    std::copy(ilist.begin(), ilist.end(), m_beginIterator.ptr());
}


/* Destructor */
/******************************************************************************
 * @brief       Destructor for the vector class
 *
 * @retval      Destructed vector
 *****************************************************************************/
template<typename ItemType>
pel::vector<ItemType>::~vector()
{
    /* Destroy all the elements in the vector */
    std::destroy(m_beginIterator.ptr(), m_endIterator.ptr());

    /* Free allocated memory */
    std::free(m_beginIterator.ptr());
}
#pragma endregion


/*****************************************************************************/
/* ELEMENT ACCESSORS ------------------------------------------------------- */
/*****************************************************************************/
#pragma region Element accessors

/******************************************************************************
 * @brief       Obtain a reference to the element at a specified index
 *              in the vector.
 *
 * @param       SizeType index: Index of the element to get.
 *
 * @retval      ItemType&: Reference to the item at the specified index.
 *****************************************************************************/
template<typename ItemType>
[[nodiscard]] constexpr inline ItemType&
pel::vector<ItemType>::at(SizeType index)
{
    return this->operator[](index);
}


/******************************************************************************
 * @brief       Obtain a constant reference to the element at a specified index
 *              in the vector.
 *
 * @param       SizeType index: Index of the element to get.
 *
 * @retval      ItemType&: Const reference to the item at the specified index.
 *****************************************************************************/
template<typename ItemType>
[[nodiscard]] constexpr inline const ItemType&
pel::vector<ItemType>::at(SizeType index) const
{
    return this->operator[](index);
}


/******************************************************************************
 * @brief       Get the element at the front of the vector
 *
 * @retval      ItemType&: Element at the front of the vector
 *
 * @throw       std::length_error
 *              If there was no memory allocated for the elements, accessing
 *              even just the first element would cause errors.
 *****************************************************************************/
template<typename ItemType>
[[nodiscard]] constexpr inline ItemType&
pel::vector<ItemType>::front()
{
    if constexpr(vector_safeness == true)
    {
        if(capacity() == 0)
        {
            throw std::length_error("Could not access element - No memory allocated");
        }
    }
    return *m_beginIterator.ptr();
}


/******************************************************************************
 * @brief       Get the element at the back of the vector
 *
 * @retval      ItemType&: Element at the back of the vector
 *
 * @throw       std::length_error
 *              If there was no memory allocated for the elements, accessing
 *              even just the first element would cause errors.
 *****************************************************************************/
template<typename ItemType>
[[nodiscard]] constexpr inline ItemType&
pel::vector<ItemType>::back()
{
    if constexpr(vector_safeness == true)
    {
        if(capacity() == 0)
        {
            throw std::length_error("Could not access element - No memory allocated");
        }
    }
    return *(m_endIterator.ptr() - 1);
}


/******************************************************************************
 * @brief       Get the const element at the front of the vector
 *
 * @retval      ItemType&: Const element at the front of the vector
 *
 * @throw       std::length_error
 *              If there was no memory allocated for the elements, accessing
 *              even just the first element would cause errors.
 *****************************************************************************/
template<typename ItemType>
[[nodiscard]] constexpr inline const ItemType&
pel::vector<ItemType>::front() const
{
    if constexpr(vector_safeness == true)
    {
        if(capacity() == 0)
        {
            throw std::length_error("Could not access element - No memory allocated");
        }
    }
    return *m_beginIterator.ptr();
}


/******************************************************************************
 * @brief       Get the const element at the back of the vector
 *
 * @retval      ItemType&: Const element at the back of the vector
 *
 * @throw       std::length_error
 *              If there was no memory allocated for the elements, accessing
 *              even just the first element would cause errors.
 *****************************************************************************/
template<typename ItemType>
[[nodiscard]] constexpr inline const ItemType&
pel::vector<ItemType>::back() const
{
    if constexpr(vector_safeness == true)
    {
        if(capacity() == 0)
        {
            throw std::length_error("Could not access element - No memory allocated");
        }
    }
    return *(m_endIterator.ptr() - 1);
}


/******************************************************************************
 * @brief       Get a pointer to the beginning of the vector's data space
 *
 * @retval      ItemType*: Pointer to the beginning of the vector's data
 *****************************************************************************/
template<typename ItemType>
[[nodiscard]] constexpr inline ItemType*
pel::vector<ItemType>::data() noexcept
{
    return m_beginIterator;
}


/******************************************************************************
 * @brief       Get a const pointer to the beginning of the vector's data space
 *
 * @retval      ItemType*: Const pointer to the beginning of the vector's data
 *****************************************************************************/
template<typename ItemType>
[[nodiscard]] constexpr inline const ItemType*
pel::vector<ItemType>::data() const noexcept
{
    return m_beginIterator;
}


/******************************************************************************
 * @brief       Return the index of an iterator from the start of the vector.
 *
 * @param       IteratorType iterator:
 *              Iterator in the vector to get the index of.
 *
 * @retval      SizeType: index of the iterator
 *****************************************************************************/
template<typename ItemType>
[[nodiscard]] constexpr inline typename pel::vector<ItemType>::SizeType
pel::vector<ItemType>::index_of(IteratorType iterator) const
{
    if constexpr(pel::vector_safeness == true)
    {
        check_if_valid(iterator);
    }

    return iterator - m_beginIterator.ptr();
}


/******************************************************************************
 * @brief       Assign a value to a certain offset in the vector for a
 *              certain amount of elements.
 *
 * @param       ItemType& value: Value to assign to the vector
 * @param       SizeType offset: Offset at which data should be assigned
 *              [defaults : 0]
 * @param       SizeType count:  Number of elements to be assigned a new value
 *              [defaults : 1]
 *****************************************************************************/
template<typename ItemType>
constexpr inline void
pel::vector<ItemType>::assign(const ItemType& value, SizeType offset, SizeType count)
{
    if constexpr(vector_safeness == true)
    {
        check_fit(count);
    }

    std::fill_n(m_beginIterator.ptr() + offset, count, value);
}


/******************************************************************************
 * @brief       Assign values to a certain offset in the vector through an
 *              initializer list.
 *
 * @param       std::initializer_list ilist: Values to assign to the vector
 * @param       SizeType offset: Offset at which data should be assigned
 *              [defaults : 0]
 *****************************************************************************/
template<typename ItemType>
constexpr inline void
pel::vector<ItemType>::assign(InitializerListType ilist, SizeType offset)
{
    if constexpr(vector_safeness == true)
    {
        check_fit(ilist.size());
    }

    std::copy(ilist.begin(), ilist.end(), m_beginIterator.ptr() + offset);
}
#pragma endregion


/*****************************************************************************/
/* OPERATOR OVERLOADS ------------------------------------------------------ */
/*****************************************************************************/
#pragma region Operator overloads

/******************************************************************************
 * @brief       Overload of the brackets[] operator to access an element at a
 *              specific index
 *
 * @param       SizeType index: Index of the element to access
 *
 * @retval      ItemType&: Reference to the element at the index
 *
 * @throws      std::length_error("Index out of range")
 *              If the index is out of the vector's length
 *****************************************************************************/
template<typename ItemType>
[[nodiscard]] constexpr inline ItemType&
pel::vector<ItemType>::operator[](SizeType index)
{
    if constexpr(pel::vector_safeness == true)
    {
        if(index >= length())
        {
            throw std::length_error("Index out of range");
        }
    }

    return m_beginIterator.ptr()[index];
}


/******************************************************************************
 * @brief       Overload of the brackets[] operator to access a const
 *              element at a specific index
 *
 * @param       SizeType index: Index of the element to access
 *
 * @retval      ItemType&: Const reference to the element at the index
 *
 * @throws      std::length_error("Index out of range")
 *              If the index is out of the vector's length
 *****************************************************************************/
template<typename ItemType>
[[nodiscard]] constexpr inline const ItemType&
pel::vector<ItemType>::operator[](SizeType index) const
{
    if constexpr(pel::vector_safeness == true)
    {
        if(index >= length())
        {
            throw std::length_error("Index out of range!");
        }
    }

    return m_beginIterator.ptr()[index];
}


/******************************************************************************
 * @brief       Overload of the arithmetic += operator to add an element at
 *              the end of the vector.
 *
 * @param       ItemType& rhs:
 *              Item at the right-hand-size of the addition, to be added at
 *              the end off the array.
 *
 * @retval      vector&: Reference the vector itself.
 *****************************************************************************/
template<typename ItemType>
constexpr inline pel::vector<ItemType>&
pel::vector<ItemType>::operator+=(const ItemType& rhs)
{
    push_back(rhs);
    return *this;
}


/******************************************************************************
 * @brief       Overload of the post-increment ++ operator to reserve one element
 *              of memory at the end of the vector.
 *
 * @retval      vector&: Reference the vector itself.
 *****************************************************************************/
template<typename ItemType>
constexpr inline pel::vector<ItemType>
pel::vector<ItemType>::operator++(int)
{
    reserve(capacity() + 1);
    return *this;
}


/******************************************************************************
 * @brief       Overload of the post-decrement -- operator to free one element
 *              of memory at the end of the vector.
 *
 * @retval      vector&: Reference the vector itself.
 *
 * @note        If the shrinking of the capacity of the vector causes it to
 *              shrink smaller than it's current size, the last element of the
 *              vector will be popped back and destroyed (safely).
 *****************************************************************************/
template<typename ItemType>
constexpr inline pel::vector<ItemType>
pel::vector<ItemType>::operator--(int)
{
    if(capacity() == length())
    {
        pop_back();
    }

    reserve(capacity() - 1);
    return *this;
}


/******************************************************************************
 * @brief       Overload of the right-shift >> operator to shift the vector's
 *              elements to the right.
 *
 * @param       int step: Shifts to the rights
 *
 * @retval      vector&: Reference the vector itself.
 *****************************************************************************/
template<typename ItemType>
constexpr inline pel::vector<ItemType>&
pel::vector<ItemType>::operator>>(int steps)
{
    std::shift_right(cbegin().ptr(), cend().ptr(), steps);

    return *this;
}


/******************************************************************************
 * @brief       Overload of the left-shift << operator to shift the vector's
 *              elements to the left.
 *
 * @param       int step: Shifts to the left
 *
 * @retval      vector&: Reference the vector itself.
 *****************************************************************************/
template<typename ItemType>
constexpr inline pel::vector<ItemType>&
pel::vector<ItemType>::operator<<(int steps)
{
    std::shift_left(cbegin().ptr(), cend().ptr(), steps);

    return *this;
}
#pragma endregion


/*****************************************************************************/
/* ITERATORS --------------------------------------------------------------- */
/*****************************************************************************/
#pragma region Iterators

/******************************************************************************
 * @brief       Returns an iterator to the beginning of the allocated data.
 *
 * @retval      IteratorType: Iterator to the start of the vector's memory.
 *****************************************************************************/
template<typename ItemType>
[[nodiscard]] constexpr inline typename pel::vector<ItemType>::IteratorType
pel::vector<ItemType>::begin() const noexcept
{
    return m_beginIterator;
}


/******************************************************************************
 * @brief       Returns an iterator to the end of the allocated data.
 *
 * @retval      IteratorType: Iterator to the end of the vector's memory.
 *
 * @note        This iterator does not point directly to the end of the
 *              memory, but to one element after the end of the memory.
 *****************************************************************************/
template<typename ItemType>
[[nodiscard]] constexpr inline typename pel::vector<ItemType>::IteratorType
pel::vector<ItemType>::end() const noexcept
{
    return m_endIterator;
}


/******************************************************************************
 * @brief       Returns a const iterator to the beginning of the allocated data.
 *
 * @retval      IteratorType:
 *              Const iterator to the start of the vector's memory.
 *****************************************************************************/
template<typename ItemType>
[[nodiscard]] constexpr inline const typename pel::vector<ItemType>::IteratorType
pel::vector<ItemType>::cbegin() const noexcept
{
    return m_beginIterator;
}


/******************************************************************************
 * @brief       Returns a const iterator to the end of the allocated data.
 *
 * @retval      IteratorType:
 *              Const iterator to the end of the vector's memory.
 *****************************************************************************/
template<typename ItemType>
[[nodiscard]] constexpr inline const typename pel::vector<ItemType>::IteratorType
pel::vector<ItemType>::cend() const noexcept
{
    return m_endIterator;
}


/******************************************************************************
 * @brief       Returns a reverse iterator to the reversed beginning of the
 *              allocated data.
 *
 * @retval      IteratorType:
 *              Iterator to the reversed start of the vector's memory.
 *              (end - 1)
 *****************************************************************************/
template<typename ItemType>
[[nodiscard]] constexpr inline typename pel::vector<ItemType>::RIteratorType
pel::vector<ItemType>::rbegin() const noexcept
{
    return reverse_IteratorType<ItemType>(m_endIterator);
}


/******************************************************************************
 * @brief       Returns a reverse iterator to the reversed end of the
 *              allocated data.
 *
 * @retval      IteratorType:
 *              Iterator to the reversed of the vector's memory.
 *              (begin - 1)
 *****************************************************************************/
template<typename ItemType>
[[nodiscard]] constexpr inline typename pel::vector<ItemType>::RIteratorType
pel::vector<ItemType>::rend() const noexcept
{
    return reverse_IteratorType<ItemType>(m_beginIterator);
}


/******************************************************************************
 * @brief       Returns a const reverse iterator to the reversed beginning of
 *              the allocated data.
 *
 * @retval      IteratorType:
 *              Const iterator to the reversed start of the vector's memory.
 *              (end - 1)
 *****************************************************************************/
template<typename ItemType>
[[nodiscard]] constexpr inline const typename pel::vector<ItemType>::RIteratorType
pel::vector<ItemType>::crbegin() const noexcept
{
    return reverse_IteratorType<ItemType>(m_endIterator);
}


/******************************************************************************
 * @brief       Returns a const reverse iterator to the reversed end of the
 *              allocated data.
 *
 * @retval      IteratorType:
 *              Const iterator to the reversed of the vector's memory.
 *              (begin - 1)
 *****************************************************************************/
template<typename ItemType>
[[nodiscard]] constexpr inline const typename pel::vector<ItemType>::RIteratorType
pel::vector<ItemType>::crend() const noexcept
{
    return reverse_IteratorType<ItemType>(m_beginIterator);
}
#pragma endregion


/*****************************************************************************/
/* ELEMENT MANAGEMENT ------------------------------------------------------ */
/*****************************************************************************/
#pragma region Element management

/******************************************************************************
 * @brief       Add an element to the end of the vector, after the current
 *              last item.
 *
 * @param       ItemType& value: Element to push back at the end of the vector.
 *****************************************************************************/
template<typename ItemType>
constexpr inline void
pel::vector<ItemType>::push_back(const ItemType& value)
{
    check_fit(1);

    *m_endIterator = value;
    add_size(1);
}


/******************************************************************************
 * @brief       Add elements from an initializer list to the end of the vector,
 *              after the current last item.
 *
 * @param       initializer_list ilist:
 *              Initializer list containing elements to push back at the end
 *              of the vector.
 *****************************************************************************/
template<typename ItemType>
constexpr inline void
pel::vector<ItemType>::push_back(const InitializerListType ilist)
{
    check_fit(ilist.size());

    std::copy(ilist.begin(), ilist.end(), end());
    add_size(ilist.size());
}


/******************************************************************************
 * @brief       Remove the last element of the vector.
 *****************************************************************************/
template<typename ItemType>
constexpr inline void
pel::vector<ItemType>::pop_back()
{
    if(length() == 0)
    {
        return;
    }

    std::destroy_at(--m_endIterator);
    m_length--;
}


/******************************************************************************
 * @brief       Insert an element in the middle of the vector, right-shifting
 *              items on the right to fit.
 *
 * @param       ItemType& value: Element to insert in the vector
 * @param       IteratorType position: Position to insert the element at
 * @param       SizeType count:
 *              Number of elements to insert from the initial offset
 *              [defaults : 1]
 *
 * @retval      IteratorType:
 *              Position at which the element has been inserted.
 *              (if multiple elements have been inserted, return position of
 *               the last inserted element).
 *****************************************************************************/
template<typename ItemType>
constexpr inline typename pel::vector<ItemType>::IteratorType
pel::vector<ItemType>::insert(const ItemType& value, const IteratorType position, SizeType count)
{
    if constexpr(pel::vector_safeness == true)
    {
        check_if_valid(position);
    }

    if(count == 0)
    {
        return begin();
    }

    check_fit(1);
    add_size(count);

    std::shift_right(position, end(), count);

    for(SizeType i = 0; i < count; i++)
    {
        position[i] = value;
    }

    return position + count;
}


/******************************************************************************
 * @brief       Insert an element in the middle of the vector, right-shifting
 *              items on the right to fit.
 *
 * @param       ItemType& value: Element to insert in the vector
 * @param       SizeType offset: Position to insert the element at
 * @param       SizeType count:
 *              Number of elements to insert from the initial offset
 *              [defaults : 1]
 *
 * @retval      IteratorType:
 *              Position at which the element has been inserted.
 *              (if multiple elements have been inserted, return position of
 *               the last inserted element).
 *
 * @throws      std::invalid_argument("Invalid insert offset")
 *              Offset was out of bounds
 *****************************************************************************/
template<typename ItemType>
constexpr inline typename pel::vector<ItemType>::IteratorType
pel::vector<ItemType>::insert(const ItemType& value, SizeType offset, SizeType count)
{
    if(offset > length())
    {
        throw std::invalid_argument("Invalid insert offset");
    }

    IteratorType<ItemType> position = cbegin() + offset;

    return insert(value, position, count);
}


/******************************************************************************
 * @brief       Insert elements in the middle of the vector from another vector,
 *              right-shifting items on the right to fit.
 *
 * @param       IteratorType sourceBegin: Begin iterator from another vector
 * @param       IteratorType sourceEnd:   End iterator from another vector
 * @param       IteratorType position:
 *              Position in vector to start copy-inserting data at
 *
 * @retval      IteratorType:
 *              Position at which the element has been inserted.
 *              (if multiple elements have been inserted, return position of
 *               the last inserted element).
 *****************************************************************************/
template<typename ItemType>
constexpr inline typename pel::vector<ItemType>::IteratorType
pel::vector<ItemType>::insert(const IteratorType sourceBegin,
                              const IteratorType sourceEnd,
                              const IteratorType position)
{
    if constexpr(pel::vector_safeness == true)
    {
        check_if_valid(position);
    }

    SizeType sourceSize = sourceEnd - sourceBegin;

    check_fit(sourceSize);
    add_size(sourceSize);

    std::shift_right(position, cend(), sourceSize);
    std::copy(sourceBegin, sourceEnd, position);

    return position + sourceSize;
}


/******************************************************************************
 * @brief       Insert elements in the middle of the vector from another vector,
 *              right-shifting items on the right to fit.
 *
 * @param       IteratorType sourceBegin: Begin iterator from another vector
 * @param       IteratorType sourceEnd:   End iterator from another vector
 * @param       SizeType offset:
 *              Offset in vector to start copy-inserting data at
 *              [defaults : 0]
 *
 * @retval      IteratorType:
 *              Position at which the element has been inserted.
 *              (if multiple elements have been inserted, return position of
 *               the last inserted element).
 *
 * @throws      std::invalid_argument("Invalid insert offset")
 *              Offset was out of bounds
 *****************************************************************************/
template<typename ItemType>
constexpr inline typename pel::vector<ItemType>::IteratorType
pel::vector<ItemType>::insert(const IteratorType sourceBegin,
                              const IteratorType sourceEnd,
                              SizeType           offset)
{
    if(offset > length())
    {
        throw std::invalid_argument("Invalid insert offset");
    }

    IteratorType position = cbegin() + offset;

    return insert(sourceBegin, sourceEnd, position);
}


/******************************************************************************
 * @brief       Insert elements in the middle of the vector from an initializer
 *              list, right-shifting items on the right to fit.
 *
 * @param       std::initializer_list ilist:
 *              Initializer list containing element to copy-insert into vector
 * @param       SizeType offset:
 *              Offset in vector to start copy-inserting data at
 *              [defaults : 0]
 *
 * @retval      IteratorType:
 *              Position at which the element has been inserted.
 *              (if multiple elements have been inserted, return position of
 *               the last inserted element).
 *
 * @throws      std::invalid_argument("Invalid insert offset")
 *              Offset was out of bounds
 *****************************************************************************/
template<typename ItemType>
constexpr inline typename pel::vector<ItemType>::IteratorType
pel::vector<ItemType>::insert(const InitializerListType ilist, SizeType offset)
{
    if(offset > length())
    {
        throw std::invalid_argument("Invalid insert offset");
    }

    IteratorType<ItemType> position = cbegin() + offset;

    return insert(ilist.begin(), ilist.end(), position);
}


/******************************************************************************
 * @brief       Replace the element at a specified position with a new
 *              element.
 *
 * @param       ItemType& value: Value that will replace element
 * @param       IteratorType position: Position of the element to replace
 *              [defaults : cbegin()]
 *
 * @retval      IteratorType:
 *              Position at which the element has been replaced.
 *****************************************************************************/
template<typename ItemType>
constexpr inline typename pel::vector<ItemType>::IteratorType
pel::vector<ItemType>::replace(const ItemType& value, SizeType offset)
{
    this->operator[](offset) = value;

    return m_beginIterator + offset;
}


/******************************************************************************
 * @brief       Replace the last element with a new element.
 *
 * @param       ItemType& value: Value that will replace element
 *
 * @retval      IteratorType: Iterator to the element that was replaced.
 *                               (end iterator - 1)
 *****************************************************************************/
template<typename ItemType>
constexpr inline typename pel::vector<ItemType>::IteratorType
pel::vector<ItemType>::replace_back(const ItemType& value)
{
    IteratorType<ItemType> position = end() - 1;

    *position = value;
    return position;
}


/******************************************************************************
 * @brief       Replace the first element with a new element.
 *
 * @param       ItemType& value: Value that will replace element
 *
 * @retval      IteratorType: Iterator to the element that was replaced.
 *                               (begin iterator)
 *****************************************************************************/
template<typename ItemType>
constexpr inline typename pel::vector<ItemType>::IteratorType
pel::vector<ItemType>::replace_front(const ItemType& value)
{
    IteratorType<ItemType> position = begin();

    *position = value;

    return position;
}
#pragma endregion


/*****************************************************************************/
/* MEMORY ------------------------------------------------------------------ */
/*****************************************************************************/
#pragma region Memory
/******************************************************************************
 * @brief       Simple accessor, return the length (number of elements)
 *              of the vector.
 *
 * @retval      SizeType: Number of elements of the vector.
 *
 * @note        Equivalent to std::vector's `size()` method
 *****************************************************************************/
template<typename ItemType>
[[nodiscard]] constexpr inline typename pel::vector<ItemType>::SizeType
pel::vector<ItemType>::length() const noexcept
{
    return m_length;
}


/******************************************************************************
 * @brief       Simple accessor, return the capacity (allocated size)
 *              of the vector.
 *
 * @retval      SizeType: Elements that can fit in the allocated space.
 *****************************************************************************/
template<typename ItemType>
[[nodiscard]] constexpr inline typename pel::vector<ItemType>::SizeType
pel::vector<ItemType>::capacity() const noexcept
{
    return m_capacity;
}


/******************************************************************************
 * @brief       Simple accessor, returns true if there are no elements
 *              in the vector.
 *
 * @retval      bool: True if there are no elements in the vector
 *                    False if there are elements in the vector
 *****************************************************************************/
template<typename ItemType>
[[nodiscard]] constexpr inline bool
pel::vector<ItemType>::is_empty() const noexcept
{
    return length() == 0;
}


/******************************************************************************
 * @brief       Simple accessor, returns true if there are elements in the
 *              vector.
 *
 * @retval      bool: True if there are elements in the vector
 *                    False if there are not elements in the vector
 *****************************************************************************/
template<typename ItemType>
[[nodiscard]] constexpr inline bool
pel::vector<ItemType>::is_not_empty() const noexcept
{
    return !is_empty();
}


/******************************************************************************
 * @brief       Allocate memory for the vector.
 *
 * @param       SizeType newCapacity:
 *              Size in elements of the memory to allocate
 *
 * @note        This function works for shrinking as well as expanding the
 *              vector's allocated memory space.
 *****************************************************************************/
template<typename ItemType>
constexpr inline void
pel::vector<ItemType>::reserve(SizeType newCapacity)
{
    /* Check if resizing is necessary */
    if(newCapacity == capacity())
    {
        return;
    }

    /* Allocate a new memory segment */
    vector_constructor(newCapacity);
}


/******************************************************************************
 * @brief       Change amount of elements currently stocked in the vector.
 *
 * @param       SizeType newLength: Size in elements of the vector
 *
 * @note        This function is different than @ref reserve().
 *              @ref reserve() allocates memory space, but doesn't make changes to
 *              the iterators or elements (unless shrinking below current
 *              vector's length).
 *              resize() changes the amount of elements contained in the vector,
 *              and can call @ref reserve() if in need of more memory.
 *****************************************************************************/
template<typename ItemType>
constexpr inline void
pel::vector<ItemType>::resize(SizeType newLength)
{
    /* Check if reserving memory is necessary */
    if(newLength > capacity())
    {
        reserve(newLength);
    }

    /* Check if freeing some memory is necessary */
    /** @todo /

    /* Resize */
    change_size(newLength);
}


/******************************************************************************
 * @brief       Destroy all elements currently in the vector and set its
 *              length to 0.
 *****************************************************************************/
template<typename ItemType>
constexpr inline void
pel::vector<ItemType>::clear()
{
    std::destroy(begin(), end());

    m_length      = 0;
    m_endIterator = cbegin();
}


/******************************************************************************
 * @brief       Shrink allocated memory to fit exactly the number of elements
 *              currently being contained in the vector.
 *****************************************************************************/
template<typename ItemType>
constexpr inline void
pel::vector<ItemType>::shrink_to_fit()
{
    if(length() == capacity())
    {
        return;
    }

    reserve(length());
}
#pragma endregion


/*****************************************************************************/
/* MISC -------------------------------------------------------------------- */
/*****************************************************************************/
#pragma region Misc
/******************************************************************************
 * @brief       Convert the content
 *
 * @param       SizeType size: Size (in elements) to allocate
 *
 * @throws      std::bad_alloc: Could not allocate block of memory
 *****************************************************************************/
template<typename ItemType>
[[nodiscard]] constexpr inline std::string
pel::vector<ItemType>::to_string() const
{
    std::ostringstream os;
    os << *this;
    return os.str();
}
#pragma endregion


/*****************************************************************************/
/* PRIVATE METHODS --------------------------------------------------------- */
/*****************************************************************************/
#pragma region Private Methods

/******************************************************************************
 * @brief       Allocates or reallocates memory on the heap. Also resize
 *              iterators.
 *
 * @param       SizeType size: Size (in elements) to allocate
 *
 * @throws      std::bad_alloc: Could not allocate block of memory
 *****************************************************************************/
template<typename ItemType>
inline void
pel::vector<ItemType>::vector_constructor(SizeType size)
{
    m_capacity = size;

    /* Reallocate block of memory */
    std::size_t blockSize = capacity() * sizeof(ItemType);
    void*       tempPtr   = std::realloc(m_beginIterator.ptr(), blockSize);
    if(tempPtr == nullptr)
    {
        if(size != 0)
        {
            throw new std::bad_alloc();
        }
        else
        {
            m_beginIterator = IteratorType((ItemType*)(void*)this);
            m_endIterator   = IteratorType((ItemType*)(void*)this);
            return;
        }
    }

    /* Set iterators */
    m_beginIterator = IteratorType(static_cast<ItemType*>(tempPtr));
    m_endIterator   = IteratorType(&(m_beginIterator.ptr()[length()]));
}


/******************************************************************************
 * @brief       Add a number of elements to the current length of the vector
 *
 * @param       SizeType addedLength:
 *              Numbers of elements to add to the current length.
 *****************************************************************************/
template<typename ItemType>
constexpr inline void
pel::vector<ItemType>::add_size(SizeType addedLength)
{
    change_size(length() + addedLength);
}


/******************************************************************************
 * @brief       Change the current length (in elements) of the vector.
 *
 * @param       SizeType newLength:
 *              New length (in elements) of the vector.
 *
 * @warning     This function does not check if the capacity is big enough
 *              before modifying the length of the vector.
 *              It should only be called when sure that the vector can hold
 *              all the added elements.
 *              (using a function such as @ref m_checkFit() is recommanded)
 *****************************************************************************/
template<typename ItemType>
constexpr inline void
pel::vector<ItemType>::change_size(SizeType newLength)
{
    m_length      = newLength;
    m_endIterator = &(m_beginIterator.ptr()[length()]);
}


/******************************************************************************
 * @brief       Check if the vector is big enough to hold the required extra
 *              elements.
 *              If it is not currently big enough, reserve some memory.
 *
 * @param       SizeType extraLength:
 *              Numbers of elements to add to the current length.
 *****************************************************************************/
template<typename ItemType>
constexpr inline void
pel::vector<ItemType>::check_fit(SizeType extraLength)
{
    if(length() + extraLength > capacity())
    {
        reserve(capacity() + m_stepSize() + extraLength);
    }
}


/******************************************************************************
 * @brief       Check if an iterator is located within the vector's bounds.
 *              If it is not, throw an exception.
 *
 * @param       IteratorType iterator: Iterator to check.
 *
 * @throws      std::invalid_argument("Invalid iterator"):
 *              If the iterator does not belong in the vector's boundaries.
 *****************************************************************************/
template<typename ItemType>
constexpr inline void
pel::vector<ItemType>::check_if_valid(const IteratorType iterator)
{
    if constexpr(pel::vector_safeness == true)
    {
        if((iterator < cbegin()) || (iterator > cend()))
        {
            throw std::invalid_argument("Invalid iterator");
        }
    }
}
#pragma endregion

/******************************************************************************
 * @brief       Overload of the left-shift << operator to print a vector's
 *              content to an output stream.
 *
 * @param       std::ostream& os: Left-hand-side output stream
 * @param       vector<ItemType>& vec: Right-hand-side vector to print
 *
 * @retval      std::ostream&: Reference the output stream after appending data
 *
 * @note        This method is not directly part of the pel::vector class, and
 *              is rather appended to the std::ostream class.
 *****************************************************************************/
template<typename ItemType>
constexpr inline std::ostream&
operator<<(std::ostream& os, const pel::vector<ItemType>& vec)
{
    os << "[" << vec.capacity() << "] [" << vec.length() << "]\n";
    for(ItemType& element: vec)
    {
        os << element << '\n';
    }
    return os;
}

/*****************************************************************************/
/* END OF FILE ------------------------------------------------------------- */
/*****************************************************************************/
