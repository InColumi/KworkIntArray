#include <iostream>

using namespace std;

template <class T>
class IntArray
{
private:
	T* _array;
	size_t _size;

	IntArray(T* arr, size_t size)
	{
		_size = size;
		_array = new T[_size];
		for(size_t i = 0; i < _size; i++)
		{
			_array[i] = arr[i];
		}
	}
public:
	IntArray()
	{
		_size = 0;
		_array = new T[_size];
	}

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
		T* newArray = new T[_size - 1];
		T itemForDelete = _array[--_size];
		for(size_t i = 0; i < _size; i++)
		{
			newArray[i] = _array[i];
		}
		delete[] _array;
		_array = newArray;
		return itemForDelete;
	}

	T Pop(size_t index)
	{
		if(index >= _size)
		{
			throw std::invalid_argument("Index must be less _size");
		}

		T* newArray = new T[--_size];
		T itemForDelete = _array[index];
		for(size_t i = 0; i < index; i++)
		{
			newArray[i] = _array[i];
		}

		for(size_t i = index; i < _size; i++)
		{
			newArray[i] = _array[i + 1];
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

	IntArray operator + (IntArray arr)
	{
		if(arr._size != _size && _size != NULL)
		{
			throw std::invalid_argument("Sizes must be equals!");
		}

		T* newArray = new T[_size];
		for(size_t i = 0; i < _size; i++)
		{
			newArray[i] = _array[i] + arr._array[i];
		}

		return IntArray(newArray, _size);
	}
};

int main()
{
	try
	{
		size_t size = 10;
		IntArray<int> a(size);

		std::cout << "pop" << endl;
		for(size_t i = 0; i < size; i++)
		{
			std::cout << a.Pop() << ", " << a.GetSize() << endl;
		}

		std::cout << "size: " << a.GetSize() << endl;

		std::cout << "append" << endl;
		for(size_t i = 0; i < size; i++)
		{
			a.Append(i);
			std::cout << a.GetSize() << endl;
		}
	
		IntArray<int> b;
		IntArray<int> c;

		b.Append(5);
		c.Append(5);

		b + c;
	}
	catch(const std::invalid_argument& err)
	{
		std::cout << err.what() << endl;
	}
	return 0;
}