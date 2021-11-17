#include <iostream>

using namespace std;

template <class T>
class IntArray
{
private:
	T* _array;
	size_t _size;

	IntArray(T*& arr, size_t size)
	{
		_size = size;
		_array = new T[_size];
		for(size_t i = 0; i < _size; i++)
		{
			_array[i] = arr[i];
			std::cout << arr[i] << endl;
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

	IntArray(const IntArray& arr): _array(nullptr), _size(arr._size)
	{
		_array = new T[_size];
		for(size_t i = 0; i < _size; i++)
		{
			_array[i] = arr._array[i];
		}
	}

	IntArray& operator=(const IntArray& arr)
	{
		if(_array)
			delete[] _array;

		_size = arr._size;
		_array = new T[_size];
		memcpy(_array, arr._array, _size);
		return *this;
	}

	IntArray(IntArray&& arr): _array(arr._array), _size(arr._size)
	{
		arr._array = nullptr;
	}

	IntArray& operator=(IntArray&& arr)
	{
		if(_array)
			delete[] _array;

		_size = arr._size;
		_array = arr._array;
		arr.pBuff = nullptr;
		return *this;
	}

	~IntArray()
	{
		delete[] _array;
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

	IntArray operator + (IntArray& arr)
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

	IntArray operator += (IntArray& arr)
	{
		if(arr._size != _size && _size != NULL)
		{
			throw std::invalid_argument("Sizes must be equals!");
		}

		for(size_t i = 0; i < _size; i++)
		{
			_array[i] += arr._array[i];
		}

		return *this;
	}

	IntArray operator * (size_t size)
	{
		if(size == 0 || size == 1)
		{
			return *this;
		}

		size_t newSize = _size * size;
		IntArray newArray(newSize);
		size_t index = 0;
		for(size_t i = 0; i < size; i++)
		{
			for(size_t j = 0; j < _size; j++)
			{
				newArray._array[j + i] = _array[j];
			}
		}

		return newArray;
	}

	IntArray operator *= (size_t size)
	{
		if(size == 0 || size == 1)
		{
			return *this;
		}

		size_t newSize = _size * size;
		T* newArray = new T[newSize];
		size_t index = 0;
		for(size_t i = 0; i < size; i++)
		{
			for(size_t j = 0; j < _size; j++)
			{
				newArray[j + i] = _array[j];
			}
		}

		delete[] _array;
		_array = newArray;
		_size = newSize;

		return *this;
	}

	void operator () (T row)
	{
		for(size_t i = 0; i < _size; i++)
		{
			_array[i] += row;
		}
	}

	const int operator[] (const size_t index) const
	{
		return _array[index];
	}

	friend std::istream& operator >> (std::istream& in, IntArray& arr)
	{
		in >> arr._size;
		arr._array = new T[arr._size];
		for(size_t i = 0; i < arr._size; i++)
		{
			in >> arr._array[i];
		}
		return in;
	}

	friend std::ostream& operator << (std::ostream& os, const IntArray& arr)
	{
		for(size_t i = 0; i < arr._size - 1; i++)
		{
			os << arr._array[i] << ' ';
		}
		os << arr._array[arr._size - 1];
		return os;
	}
};

int main()
{
	try
	{
		size_t size = 10;
		/*IntArray<int> a(size);

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
		}*/

		IntArray<int> b;
		//IntArray<int> c;

		b.Append(5);

		std::cout << b << endl;

		b *= 100;
		std::cout << b << endl;

		std::cout << b * 2 << endl;;

	}
	catch(const std::invalid_argument& err)
	{
		std::cout << err.what() << endl;
	}
	return 0;
}