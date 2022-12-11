#include "./Array.h"
#include <cstdlib>
#include <utility>

template <typename T>
Array<T>::Array(int capacity)
{
	if (capacity <= 0)
	{
		_capacity = _DEFAULT_CAPACITY;
	}
	else
	{
		_capacity = capacity;
	}

	_size = 0;
	_elements = (T*)(std::malloc(sizeof(T) * _capacity));
}

template <typename T>
Array<T>::Array() : Array(_DEFAULT_CAPACITY) {}

template <typename T>
Array<T>::~Array()
{
	for (int i = 0; i < _size; i++)
	{
		_elements[i].~T();
	}
	std::free(_elements);
}

template <typename T>
int Array<T>::CheckIndexInArrayRange(int index) 
{
	return index >= _size || index < 0;
}

template <typename T>
int Array<T>::Size() const
{
	return _size;
}

template <typename T>
void Array<T>::MoveElement(int from, T *destination)
{
	new (destination) T(std::move(_elements[from]));
	_elements[from].~T();
}

template <typename T>
void Array<T>::Resize()
{
	_capacity = (int)(_capacity * _EXTEND_KOEF);
	T* newElements = (T*)std::malloc(_capacity* sizeof(T));


	for (int i = 0; i < _size; i++)
	{
		MoveElement(i, newElements + i);
	}

	std::free(_elements);
	_elements = newElements;
}

template <typename T>
int Array<T>::Insert(const T& value)
{
	if (_size == _capacity)
	{
		Resize();
	}
	new (_elements + _size) T(std::move(value));
	_size += 1;
	return _size - 1;
}

template <typename T>
int Array<T>::Insert(int index, const T& value)
{
	if (CheckIndexInArrayRange(index)) return -1;

	if (_size == _capacity)
	{
		Resize();
	}


	new(_elements + _size) T(std::move(_elements[_size  - 1]));

	for (int i = _size - 1; i > index; i--) 
	{
		_elements[i] = std::move(_elements[i - 1]);
	}

	_elements[index] = value;
 	_size += 1;

	return index;
}

template <typename T>
const T& Array<T>::operator[](int index) const
{
	return _elements[index];
}

template <typename T>
T& Array<T>::operator[](int index)
{
	return _elements[index];
}

template <typename T>
void Array<T>::Remove(int index) {

	if (CheckIndexInArrayRange(index)) return;

	for (int i = index; i < _size - 1; i++) {
		_elements[i].~T();
		new (_elements + i) T(std::move(_elements[i + 1]));
	}

	_elements[_size - 1].~T();

	_size -= 1;
}

template <typename T>
Array<T>::InnerIterator::InnerIterator(int direction, T* pointer, Array<T>* arrayPointer)
{
	_direction = direction;
	_pointer = pointer;
	_arrayPointer = arrayPointer;
}

template <typename T>
Array<T>::InnerConstIterator::InnerConstIterator(int direction, T* pointer, Array<T>* arrayPointer)
{
	_direction = direction;
	_pointer = pointer;
	_arrayPointer = arrayPointer;
}

template <typename T>
T& Array<T>::InnerIterator::Get()
{
	return *_pointer;
}

template <typename T>
void Array<T>::InnerIterator::Set(T& value)
{
	*_pointer = value;
}

template <typename T>
void Array<T>::InnerIterator::Next()
{
	_pointer += _direction;
}

template <typename T>
bool Array<T>::InnerIterator::HasNext() const
{
	return ((_pointer + _direction >= _arrayPointer->_elements - 1) && (_pointer + _direction < _arrayPointer->_elements + _arrayPointer->Size()+1));
}


template <typename T>
const T& Array<T>::InnerConstIterator::Get() const
{
	return *_pointer;
}

template <typename T>
void Array<T>::InnerConstIterator::Set(const T& value)
{
	*_pointer = value;
}

template <typename T>
void Array<T>::InnerConstIterator::Next()
{
	_pointer += _direction;
}

template <typename T>
bool Array<T>::InnerConstIterator::HasNext() const
{
	return ((_pointer + _direction >= _arrayPointer->_elements) && (_pointer + _direction <= _arrayPointer->_elements + _arrayPointer->Size() - 1));
}

template <typename T>
typename Array<T>::InnerIterator Array<T>::Iterator() 
{
	return *(new InnerIterator(1, _elements, this));
}

template <typename T>
typename Array<T>::InnerConstIterator Array<T>::Iterator() const
{
	return *(new InnerConstIterator(1, _elements, this));
}

template <typename T>
typename Array<T>::InnerIterator Array<T>::ReverseIterator()
{
	return *(new InnerIterator(-1, _elements + _size - 1, this));
}

template <typename T>
typename Array<T>::InnerConstIterator Array<T>::ReverseIterator() const
{
	return *(new InnerConstIterator(-1, _elements + _size - 1, this));
}