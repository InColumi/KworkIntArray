#include <iostream>

using namespace std;

template <class T>
class IntArray
{
private:
	T* _array;
	size_t _size;
public:
	IntArray(): _array(NULL), _size(0) {}

	IntArray(size_t size)
	{
		_size = size;
		_array = new T[_size];
		for(size_t i = 0; i < _size; i++)
		{
			_array[i] = 0;
		}
	}

	IntArray(const IntArray& arr)
	{
		_size = arr._size;
		_array = new T[_size];
		for(size_t i = 0; i < _size; i++)
		{
			_array[i] = arr._array[i];
		}
	}

	~IntArray()
	{
		delete[] _array;
		_size = 0;
	}


	size_t GetSize()
	{
		return _size;
	}

	T Pop()
	{
		T* newArray = new T[_size];
		T itemForDelete = _array[--_size];
		for(size_t i = 0; i < _size; i++)
		{
			newArray[i] = _array[i];
		}
		delete[] _array;
		_array = newArray;
		return itemForDelete;
	}

	void Append(T item)
	{
		T* newArray = new T[_size + 1];
		for(size_t i = 0; i < _size; i++)
		{
			newArray[i] = _array[i];
		}
		newArray[_size++] = item;
		delete[] _array;
		_array = newArray;
	}
};

int main()
{
	size_t size = 10;
	IntArray<int> a(size);

	std::cout << "pop" << endl;
	for(size_t i = 0; i < size; i++)
	{
		std::cout << a.Pop()  << ", " << a.GetSize() << endl;
	}

	std::cout << "size: " << a.GetSize() << endl;

	std::cout << "append" << endl;
	for(size_t i = 0; i < size; i++)
	{
		a.Append(i);
		std::cout << a.GetSize() << endl;
	}

	return 0;
}