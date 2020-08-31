# vector
My own vector implementation in C++, using features of C++20, and a lot of different toolings.
This is mostly a project I made to try out new features and tooling such as static analyzers, sanitizers, documentation generators and various compilers.


Tools used:  
On Ubuntu 20.04 (running on WSL)

- `g++` 10.1
- `clang++` 10.0
- `clang-tidy` 10.0
- `clang-format` 11
- `cmake` 3.17.1
- `doxygen` 1.8.16

Plus `msbuild` 16.5 with Visual Studio 16 2019 on Windows 10



# These vectors have the following functions:

## Constructors
(1) `vector(SizeType length_ = 0, const AllocatorType& alloc_ = AllocatorType{});`
(2) `vector(SizeType length_, const ItemType& value_, const AllocatorType& alloc_ = AllocatorType{});`
(3) `vector(IteratorType beginIterator_, IteratorType endIterator_, const AllocatorType& alloc_ = AllocatorType{});`
(4) `vector(const vector<ItemType, OtherAllocatorType>& otherVector_, const AllocatorType& alloc_ = AllocatorType{});`
(4) `vector(const vector& otherVector_);`
(5) `vector& operator=(const vector<ItemType, OtherAllocatorType>& copy_);`
(5) `vector& operator=(const vector& copy_);`
(6) `vector(vector<ItemType, OtherAllocatorType>&& move_, AllocatorType& alloc_ = AllocatorType{});`
(7) `vector& operator=(vector<ItemType, OtherAllocatorType>&& move_);`
(8) `vector(InitializerListType ilist_, const AllocatorType& alloc_ = AllocatorType{});`
(9) `vector(SizeType length_, Args&&... args_, const AllocatorType& alloc_ = AllocatorType{});` 
(10) `vector(SizeType length_, std::function<ItemType(void)> function_, const AllocatorType& alloc_ = AllocatorType{});`

(1) Constructs with `length_` default-constructed elements
(2) Constructs with `length_` elements with value `value_`
(3) Constructs from an iterator pair, copying the elements from the source
(4) Copy constructor
(5) Copy assignment operator
(6) Move constructor
(7) Move assignment operator
(8) Constructs from an `std::initializer_list`, copying its elements.
(9) Constructs in-place `length_` elements, calling their constructors with `args_` arguments
(10) Constructs `length_` elements intialized with a generator function.

## Element accessors
(1) `ItemType& at(SizeType index_); `
(2) `IteratorType iterator_at(DifferenceType index_);`
(3) `ItemType& front();`
(4) `ItemType& back();`
(5) `ItemType* data();`
(6) `DifferenceType index_of(IteratorType iterator_);`
(7) `void assign(const ItemType& value_, DifferenceType offset_ = 0, SizeType count_ = 1);`
(8) `void assign(InitializerListType ilist_, DifferenceType offset_ = 0);`
