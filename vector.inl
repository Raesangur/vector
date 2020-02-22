

/*****************************************************************************/
/* Constructors ------------------------------------------------------------ */
#pragma region Constructors
 /**
  * @function     vector
  *
  * @brief        Constructor for the vector class
  * @date         2020/02/07 - 22:39
  * @author       Pascal-Emmanuel Lachance
  *               https://www.github.com/Raesangur/
  *
  * @template     ItemType: Type of the elements contained in the vector.
  * @attributes   constexpr
  * 
  * @param        SizeType length: Number of elements to allocate
  *
  * @retval       pel::vector: Constructed vector
  */
template<typename ItemType>
constexpr
pel::vector<ItemType>::vector(SizeType length)
    : m_length(length)
{
    m_VectorConstructor(length);
}

/**
  * @function     vector
  *
  * @brief        Default-value constructor for the vector class
  * @date         2020/02/07 - 22:39
  * @author       Pascal-Emmanuel Lachance
  *               https://www.github.com/Raesangur/
  *
  * @template     ItemType: Type of the elements contained in the vector.
  * @attributes   constexpr
  *
  * @param        SizeType length: Number of elements to allocate
  * @param        ItemType& defaultValue:
  *               Value to initialize all the elements initially allocated with
  *
  * @retval       pel::vector: Constructed vector
  */
template<typename ItemType>
constexpr
pel::vector<ItemType>::vector(SizeType length, const ItemType& defaultValue)
    : m_length(length)
{
    m_VectorConstructor(length);

    std::fill(this->begin(), this->end(), defaultValue);
}

/**
  * @function     vector
  *
  * @brief        Iterator-based copy constructor for the vector class
  * @date         2020/02/07 - 22:39
  * @author       Pascal-Emmanuel Lachance
  *               https://www.github.com/Raesangur/
  *
  * @template     ItemType: Type of the elements contained in the vector.
  * @attributes   constexpr
  *
  * @param        vector_iterator beginIterator:
  *               Begin iterator of another vector to start copying from.
  * @param        vector_iterator endIterator:
  *               End iterator of another vector to end the copy.
  *
  * @retval       pel::vector: Constructed vector
  */
template<typename ItemType>
constexpr
pel::vector<ItemType>::vector(const vector_iterator<ItemType> beginIterator,
                              const vector_iterator<ItemType> endIterator)
{
    m_length = endIterator - beginIterator;
    m_VectorConstructor(length());

    std::copy(beginIterator, endIterator, begin());
}

/**
 * @function     vector
 *
 * @brief        Copy constructor for the vector class
 * @date         2020/02/07 - 22:39
 * @author       Pascal-Emmanuel Lachance
 *               https://www.github.com/Raesangur/
 *
 * @template     ItemType: Type of the elements contained in the vector.
 * @attributes   constexpr
 *
 * @param        vector& otherVector: Vector to copy data from.
 *
 * @retval       pel::vector: Constructed vector
 */
template<typename ItemType>
constexpr
pel::vector<ItemType>::vector(const vector<ItemType>& otherVector)
{
    m_length = otherVector.m_length;
    m_VectorConstructor(length());

    std::copy(otherVector.cbegin(), otherVector.cend(), begin);
}

/**
 * @function     vector
 *
 * @brief        Initializer list constructor for the vector class
 * @date         2020/02/07 - 22:39
 * @author       Pascal-Emmanuel Lachance
 *               https://www.github.com/Raesangur/
 *
 * @template     ItemType: Type of the elements contained in the vector.
 * @attributes   constexpr
 *
 * @param        std::initializer_list ilist:
 *               Initializer list of all the values to put in a new vector.
 *
 * @retval       pel::vector: Constructed vector
 */
template<typename ItemType>
constexpr
pel::vector<ItemType>::vector(const std::initializer_list<ItemType> ilist)
{
    m_length = ilist.size();
    m_VectorConstructor(length());

    std::copy(ilist.begin(), ilist.end(), begin());
}

/* Destructor */
 /**
  * @function     ~vector
  *
  * @brief        Destructor for the vector class
  * @date         2020/02/07 - 22:39
  * @author       Pascal-Emmanuel Lachance
  *               https://www.github.com/Raesangur/
  *
  * @template     ItemType: Type of the elements contained in the vector.
  *
  * @retval       pel::vector: destructed vector
  */
template<typename ItemType>
pel::vector<ItemType>::~vector()
{
    /* Destroy all the elements in the vector */
    std::destroy(begin(), end());

    /* Free allocated memory */
    std::free(begin());
}
#pragma endregion


/******************************************************************************/
/* Element accessors -------------------------------------------------------- */


/**
 * @function    at
 *
 * @brief       Obtain a reference to the element at a specified index
 *              in the vector.
 * @date        2020/02/07 - 22:39
 * @author      Pascal-Emmanuel Lachance
 *              https://www.github.com/Raesangur/
 *
 * @template    ItemType: Type of the elements contained in the vector.
 * @attributes  constexpr inline
 *
 * @param       SizeType index: Index of the element to get.
 *
 * @retval      ItemType&: Reference to the item at the specified index.
 */
template<typename ItemType>
constexpr inline
ItemType&
pel::vector<ItemType>::at(const SizeType index)
{
    return *this->operator[](index);
}

/**
 * @function    at
 *
 * @brief       Obtain a constant reference to the element at a specified index
 *              in the vector.
 * @date        2020/02/07 - 22:39
 * @author      Pascal-Emmanuel Lachance
 *              https://www.github.com/Raesangur/
 *
 * @template    ItemType: Type of the elements contained in the vector.
 * @attributes  constexpr inline - const
 *
 * @param       SizeType index: Index of the element to get.
 *
 * @retval      ItemType&: Const reference to the item at the specified index.
 */
template<typename ItemType>
constexpr inline
const ItemType&
pel::vector<ItemType>::at(const SizeType index) const
{
    return *this->operator[](index);
}


/**
 * @function    front
 *
 * @brief       Get the element at the front of the vector
 * @date        2020/02/07 - 22:39
 * @author      Pascal-Emmanuel Lachance
 *              https://www.github.com/Raesangur/
 *
 * @template    ItemType: Type of the elements contained in the vector
 * @attributes  constexpr inline
 *
 * @retval      ItemType&: Element at the front of the vector
 */
template<typename ItemType>
constexpr inline
ItemType&
pel::vector<ItemType>::front()
{
    return *begin();
}

/**
 * @function    back
 *
 * @brief       Get the element at the back of the vector
 * @date        2020/02/07 - 22:39
 * @author      Pascal-Emmanuel Lachance
 *              https://www.github.com/Raesangur/
 *
 * @template    ItemType: Type of the elements contained in the vector
 * @attributes  constexpr inline
 *
 * @retval      ItemType&: Element at the back of the vector
 */
template<typename ItemType>
constexpr inline
ItemType&
pel::vector<ItemType>::back()
{
    return *(end() - 1);
}


/**
 * @function    front
 *
 * @brief       Get the const element at the front of the vector
 * @date        2020/02/07 - 22:39
 * @author      Pascal-Emmanuel Lachance
 *              https://www.github.com/Raesangur/
 *
 * @template    ItemType: Type of the elements contained in the vector
 * @attributes  constexpr inline - const
 *
 * @retval      ItemType&: Const element at the front of the vector
 */
template<typename ItemType>
constexpr inline
const ItemType&
pel::vector<ItemType>::front() const
{
    return *begin();
}

/**
 * @function    front
 *
 * @brief       Get the const element at the back of the vector
 * @date        2020/02/07 - 22:39
 * @author      Pascal-Emmanuel Lachance
 *              https://www.github.com/Raesangur/
 *
 * @template    ItemType: Type of the elements contained in the vector
 * @attributes  constexpr inline - const
 *
 * @retval      ItemType&: Const element at the back of the vector
 */
template<typename ItemType>
constexpr inline
const ItemType&
pel::vector<ItemType>::back() const
{
    return *(end() - 1);
}

/**
 * @function    data
 *
 * @brief       Get a pointer to the beginning of the vector's data space
 * @date        2020/02/07 - 22:39
 * @author      Pascal-Emmanuel Lachance
 *              https://www.github.com/Raesangur/
 *
 * @template    ItemType: Type of the elements contained in the vector
 * @attributes  constexpr inline
 *
 * @retval      ItemType*: Pointer to the beginning of the vector's data
 */
template<typename ItemType>
constexpr inline
ItemType*
pel::vector<ItemType>::data()
{
    return m_beginIterator;
}

/**
 * @function    data
 *
 * @brief       Get a const pointer to the beginning of the vector's data space
 * @date        2020/02/07 - 22:39
 * @author      Pascal-Emmanuel Lachance
 *              https://www.github.com/Raesangur/
 *
 * @template    ItemType: Type of the elements contained in the vector
 * @attributes  constexpr inline - const
 *
 * @retval      ItemType*: Const pointer to the beginning of the vector's data
 */
template<typename ItemType>
constexpr inline
const ItemType*
pel::vector<ItemType>::data() const
{
    return m_beginIterator;
}


/**
 * @function    assign
 *
 * @brief       Assign a value to a certain offset in the vector for a 
                certain amount of elements.
 * @date        2020/02/07 - 22:39
 * @author      Pascal-Emmanuel Lachance
 *              https://www.github.com/Raesangur/
 *
 * @template    ItemType: Type of the elements contained in the vector
 * @attributes  constexpr inline
 *
 * @param       ItemType& value: Value to assign to the vector
 * @param       SizeType offset: Offset at which data should be assigned
 * @param       SizeType count:  Number of elements to be assigned a new value
 *
 * @retval      void: None
 */
template<typename ItemType>
constexpr inline
void
pel::vector<ItemType>::assign(const ItemType& value,
                              const SizeType offset,
                              const SizeType count)
{
    m_checkFit(count);

    std::fill_n(begin() + offset, count, value);
}

/**
 * @function    assign
 *
 * @brief       Assign values to a certain offset in the vector through an
                initializer's list.
 * @date        2020/02/07 - 22:39
 * @author      Pascal-Emmanuel Lachance
 *              https://www.github.com/Raesangur/
 *
 * @template    ItemType: Type of the elements contained in the vector
 * @attributes  constexpr inline
 *
 * @param       std::initializer_list ilist: Values to assign to the vector
 * @param       SizeType offset: Offset at which data should be assigned
 *
 * @retval      void: None
 */
template<typename ItemType>
constexpr inline
void
pel::vector<ItemType>::assign(const std::initializer_list<ItemType> ilist,
                              const SizeType offset)
{
    m_checkFit(ilist.size());

    std::copy(ilist.begin(), ilist.end(), begin() + offset);
}


/******************************************************************************/
/* Operator overloads ------------------------------------------------------- */

template<typename ItemType>
constexpr
ItemType&
pel::vector<ItemType>::operator[](const SizeType index)
{
    if (index >= length())
    {
        throw std::length_error("Index out of range!");
    }

    return m_beginIterator[index];
}

template<typename ItemType>
constexpr const
ItemType&
pel::vector<ItemType>::operator[](const SizeType index) const
{
    if (index >= length())
    {
        throw std::length_error("Index out of range!");
    }

    return m_beginIterator[index];
}

template<typename ItemType>
constexpr
pel::vector<ItemType>&
pel::vector<ItemType>::operator+=(const ItemType& rhs)
{
    emplace_back(rhs);
    return *this;
}

template<typename ItemType>
constexpr
pel::vector<ItemType>&
pel::vector<ItemType>::operator++(int)
{
    reserve(capacity() + 1);
    return *this;
}

template<typename ItemType>
constexpr
pel::vector<ItemType>&
pel::vector<ItemType>::operator--(int)
{
    if (capacity() == length())
    {
        pop_back();
    }

    reserve(capacity() - 1);
    return *this;
}

template<typename ItemType>
constexpr
pel::vector<ItemType>&
pel::vector<ItemType>::operator>>(int steps)
{
    std::shift_right(cbegin(), cend(), steps);

    return *this;
}

template<typename ItemType>
constexpr
pel::vector<ItemType>&
pel::vector<ItemType>::operator<<(int steps)
{
    std::shift_left(cbegin(), cend(), steps);

    return *this;
}


/******************************************************************************/
/* Iterators ---------------------------------------------------------------- */
template<typename ItemType>
constexpr inline
pel::vector_iterator<ItemType>
pel::vector<ItemType>::begin() const
{
    return m_beginIterator;
}

template<typename ItemType>
constexpr inline
pel::vector_iterator<ItemType>
pel::vector<ItemType>::end() const
{
    return m_endIterator;
}

template<typename ItemType>
constexpr inline const
pel::vector_iterator<ItemType>
pel::vector<ItemType>::cbegin() const
{
    return m_beginIterator;
}

template<typename ItemType>
constexpr inline const
pel::vector_iterator<ItemType>
pel::vector<ItemType>::cend() const
{
    return m_endIterator;
}


/******************************************************************************/
/* Element management ------------------------------------------------------- */
template<typename ItemType>
constexpr
void
pel::vector<ItemType>::push_back(const ItemType& value)
{
    m_checkFit(1);

    *m_endIterator = value;

    m_addSize(1);
}

template<typename ItemType>
constexpr
void
pel::vector<ItemType>::push_back(const std::initializer_list<ItemType> ilist)
{
    m_checkFit(ilist.size());

    std::copy(ilist.begin(), ilist.end(), end());

    m_addSize(ilist.size());
}

template<typename ItemType>
constexpr
void
pel::vector<ItemType>::pop_back()
{
    if (length() == 0)
    {
        return;
    }

    std::destroy_at(--m_endIterator);
    m_length--;
}


template<typename ItemType>
constexpr
pel::vector_iterator<ItemType>
pel::vector<ItemType>::insert(const ItemType& value,
                              vector_iterator<ItemType> position,
                              SizeType count)
{
    m_checkIfValid(position);
    if (count == 0)
    {
        return cbegin();
    }

    m_checkFit(1);
    m_addSize(count);

    std::shift_right(position, end(), count);

    for (SizeType i = 0; i < count; i++)
    {
        position[i] = value;
    }

    return position;
}

template<typename ItemType>
constexpr
pel::vector_iterator<ItemType>
pel::vector<ItemType>::insert(const ItemType& value,
                              const SizeType offset,
                              const SizeType count)
{
    if (offset > length())
    {
        throw std::invalid_argument("Invalid insert offset");
    }

    vector_iterator<ItemType> position = cbegin() + offset;

    return insert(value, position, count);
}

template<typename ItemType>
constexpr
pel::vector_iterator<ItemType>
pel::vector<ItemType>::insert(const vector_iterator<ItemType> sourceBegin,
                              const vector_iterator<ItemType> sourceEnd,
                              const vector_iterator<ItemType> position)
{
    m_checkIfValid(position);
    SizeType sourceSize = sourceEnd - sourceBegin;

    m_checkFit(sourceSize);
    m_addSize(sourceSize);

    std::shift_right(position, cend(), sourceSize);
    std::copy(sourceBegin, sourceEnd, position);

    return position;
}

template<typename ItemType>
constexpr
pel::vector_iterator<ItemType>
pel::vector<ItemType>::insert(const vector_iterator<ItemType> sourceBegin,
                              const vector_iterator<ItemType> sourceEnd,
                              const SizeType offset)
{
    if (offset > length())
    {
        throw std::invalid_argument("Invalid insert offset");
    }

    vector_iterator position = cbegin() + offset;

    return insert(sourceBegin, sourceEnd, position);
}

template<typename ItemType>
constexpr
pel::vector_iterator<ItemType>
pel::vector<ItemType>::insert(const std::initializer_list<ItemType> ilist,
                              const SizeType offset)
{
    if (offset > length())
    {
        throw std::invalid_argument("Invalid insert offset");
    }

    vector_iterator<ItemType> position = cbegin() + offset;

    return insert(ilist.begin(), ilist.end(), position);
}

template<typename ItemType>
constexpr
pel::vector_iterator<ItemType>
pel::vector<ItemType>::replace(const ItemType& value,
                               vector_iterator<ItemType> position)
{
    m_checkIfValid(position);

    *position = value;

    return position;
}

template<typename ItemType>
constexpr
pel::vector_iterator<ItemType>
pel::vector<ItemType>::replace_back(const ItemType& value)
{
    vector_iterator<ItemType> position = end() - 1;

    *position = value;

    return position;
}

template<typename ItemType>
constexpr
pel::vector_iterator<ItemType>
pel::vector<ItemType>::replace_front(const ItemType& value)
{
    vector_iterator<ItemType> position = begin();

    *position = value;

    return position;
}


/******************************************************************************/
/* Memory ------------------------------------------------------------------- */
template<typename ItemType>
constexpr inline const
typename pel::vector<ItemType>::SizeType&
pel::vector<ItemType>::length() const
{
    return m_length;
}

template<typename ItemType>
constexpr inline const
typename pel::vector<ItemType>::SizeType&
pel::vector<ItemType>::capacity() const
{
    return m_capacity;
}

template<typename ItemType>
constexpr inline const
bool
pel::vector<ItemType>::isEmpty() const
{
    return length() == 0;
}

template<typename ItemType>
constexpr
void
pel::vector<ItemType>::reserve(const SizeType newCapacity)
{
    /* Check if resizing is necessary */
    if (newCapacity == capacity())
    {
        return;
    }

    /* Allocate a new memory segment */
    m_VectorConstructor(newCapacity);
}

template<typename ItemType>
constexpr
void
pel::vector<ItemType>::resize(const SizeType newLength)
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

template<typename ItemType>
constexpr
void
pel::vector<ItemType>::clear()
{
    std::destroy(begin(), end());

    m_length = 0;
    m_endIterator = cbegin();
}

template<typename ItemType>
constexpr
void
pel::vector<ItemType>::shrink_to_fit()
{
    if (length() == capacity())
    {
        return;
    }

    reserve(length());
}


/******************************************************************************/
/* Private methods ---------------------------------------------------------- */
template<typename ItemType>
constexpr inline
void
pel::vector<ItemType>::m_VectorConstructor(const SizeType size)
{
    m_capacity = size;

    /* Reallocate block of memory */
    std::size_t blockSize = capacity() * sizeof(ItemType);
    void* tempPtr = std::realloc(begin(), blockSize);
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

template<typename ItemType>
constexpr inline
void
pel::vector<ItemType>::m_addSize(const SizeType addedLength)
{
    m_changeSize(length() + addedLength);
}

template<typename ItemType>
constexpr inline
void
pel::vector<ItemType>::m_changeSize(const SizeType newLength)
{
    m_length = newLength;
    m_endIterator = &m_beginIterator[length()];
}

template<typename ItemType>
constexpr inline
bool
pel::vector<ItemType>::m_checkFit(const SizeType extraLength)
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

template<typename ItemType>
constexpr inline
void
pel::vector<ItemType>::m_checkIfValid(const vector_iterator<ItemType> iterator)
{
    if ((iterator < cbegin()) || (iterator > cend()))
    {
        throw std::invalid_argument("Invalid iterator");
    }
}
#pragma endregion