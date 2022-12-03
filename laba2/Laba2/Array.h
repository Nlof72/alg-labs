#ifndef ARRAY_H
#define ARRAY_H

template <typename T>
class Array final
{

private:
	T* _elements;
	int _capacity;
	int _size;

	static constexpr int _DEFAULT_CAPACITY = 4 ;
	static constexpr float _EXTEND_KOEF = 1.6f;

	void Resize();
	void MoveElement(int from, T *destination);
	int CheckIndexInArrayRange(int index);
		
	class InnerIterator {
		friend Array;

		int _direction;
		T* _pointer;
		Array* _arrayPointer;
	public:

		InnerIterator(int direction, T* pointer, Array<T>* arrayPointer);
		T& Get();
		void Set(T& value);
		void Next();
		bool HasNext() const;
	};

	class InnerConstIterator {
		friend Array;

		int _direction;
		T* _pointer;
		Array* _arrayPointer;
	public:
		InnerConstIterator(int direction, T* pointer, Array<T>* arrayPointer);
		const T& Get() const;
		void Set(const T& value);
		void Next();
		bool HasNext() const;
	};

public:
	Array();
	Array(int capacity);
	~Array();
	int Insert(const T& value);
	int Insert(int index, const T& value);
	void Remove(int index);
	const T& operator[](int index) const;
	T& operator[](int index);
	int Size() const;
	InnerIterator Iterator();
	InnerConstIterator Iterator() const;
	InnerIterator ReverseIterator();
	InnerConstIterator ReverseIterator() const;
};

#endif