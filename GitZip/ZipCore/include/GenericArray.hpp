#ifndef GENERICARRAY_HPP
#define GENERICARRAY_HPP

#include <algorithm>
#include <memory>

template<typename DataType, typename SizeType>
class GenericArray
{
	public:
		GenericArray(const SizeType capacity, const SizeType step = DefaultStep);
		GenericArray(DataType* const data, const SizeType lenght, const SizeType step = DefaultStep) noexcept;
		GenericArray(const GenericArray& genericArray);
		GenericArray(GenericArray&& genericArray) noexcept;

		~GenericArray();

		const SizeType Capacity() const noexcept;
		const SizeType Lenght() const noexcept;
		const DataType* Array() const noexcept;

		void Clean() noexcept;

		const bool operator==(const GenericArray& genericArray) const noexcept;
		const bool operator!=(const GenericArray& genericArray) const noexcept;

		DataType& operator[](const SizeType index);
		const DataType operator[](const SizeType index) const;

		void operator+=(const DataType& data);
		void operator+=(const GenericArray& string);

	private:
		const static size_t DefaultStep = 64;
		const size_t _currentStep;

		SizeType _lenght;
		SizeType _position;

		DataType* _array;
};

#pragma region	GenericArray realization

template<typename DataType, typename SizeType>
inline GenericArray<DataType, SizeType>::GenericArray(const SizeType capacity, const SizeType step) :
	_lenght(capacity), _position(0), _currentStep(step), _array(new DataType[capacity]) {}

template<typename DataType, typename SizeType>
inline GenericArray<DataType, SizeType>::GenericArray(DataType* const data, const SizeType lenght, const SizeType step) noexcept :
	_lenght(lenght), _position(lenght), _currentStep(step), _array(data) {}

template<typename DataType, typename SizeType>
inline GenericArray<DataType, SizeType>::GenericArray(const GenericArray& genericArray) :
	_lenght(genericArray._position), _position(genericArray._position), _currentStep(genericArray._currentStep),
	_array(new DataType[genericArray._position])
{
	std::copy(genericArray._array, genericArray._array + genericArray._position, _array);
}

template<typename DataType, typename SizeType>
inline GenericArray<DataType, SizeType>::GenericArray(GenericArray&& genericArray) noexcept :
	_lenght(genericArray._lenght), _position(genericArray._position), _currentStep(genericArray._currentStep),
	_array(std::move(genericArray._array)) {}

template<typename DataType, typename SizeType>
inline GenericArray<DataType, SizeType>::~GenericArray()
{
	if (_array)
		delete[] _array;
}

template<typename DataType, typename SizeType>
inline const SizeType GenericArray<DataType, SizeType>::Capacity() const noexcept
{
	return _lenght;
}

template<typename DataType, typename SizeType>
inline const SizeType GenericArray<DataType, SizeType>::Lenght() const noexcept
{
	return _position;
}

template<typename DataType, typename SizeType>
inline const DataType* GenericArray<DataType, SizeType>::Array() const noexcept
{
	return _array;
}

template<typename DataType, typename SizeType>
inline void GenericArray<DataType, SizeType>::Clean() noexcept
{
	_position = 0;
}

template<typename DataType, typename SizeType>
inline const bool GenericArray<DataType, SizeType>::operator==(const GenericArray& genericArray) const noexcept
{
	bool equal = _position == genericArray._position ? true : false;

	if (equal)
	{
		SizeType index = 0;
		while (equal && index < _position)
		{
			if (_array[index] != genericArray._array[index])
				equal = false;
			else
				++index;
		}
	}

	return equal;
}

template<typename DataType, typename SizeType>
inline const bool GenericArray<DataType, SizeType>::operator!=(const GenericArray& genericArray) const noexcept
{
	return !(*this == genericArray);
}

template<typename DataType, typename SizeType>
inline DataType& GenericArray<DataType, SizeType>::operator[](const SizeType index)
{
	return _array[index];
}

template<typename DataType, typename SizeType>
inline const DataType GenericArray<DataType, SizeType>::operator[](const SizeType index) const
{
	return _array[index];
}

template<typename DataType, typename SizeType>
inline void GenericArray<DataType, SizeType>::operator+=(const DataType& data)
{
	if (_lenght == _position)
	{
		const SizeType newLenght = SizeType(_lenght + _currentStep);
		DataType* const data = new DataType[newLenght];

		memmove_s(data, sizeof(DataType) * newLenght, _array, sizeof(DataType) * _position);

		delete[] _array;

		_array = data;
		_lenght = newLenght;
	}

	_array[_position] = data;
	++_position;
}

template<typename DataType, typename SizeType>
inline void GenericArray<DataType, SizeType>::operator+=(const GenericArray& string)
{
	SizeType totalLenght = _position + string._position;

	if (totalLenght >= _lenght)
	{
		totalLenght += _currentStep;

		DataType* const data = new DataType[totalLenght];

		memmove_s(data, sizeof(DataType) * totalLenght, _array, sizeof(DataType) * _position);

		delete[] _array;

		_array = data;
		_lenght = totalLenght;
	}

	memcpy_s(_array + _position * sizeof(DataType), sizeof(DataType) * (_lenght - _position), string._array, sizeof(DataType) * string._position);
	_position += string._position;
}

#pragma endregion

#endif // !GENERICARRAY_HPP