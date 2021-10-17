#include <stdexcept>
#include <omp.h>
#include <climits>

#include "../include/HashTable.hpp"

#pragma warning(disable: 6993)

const ULong __fastcall GetHash(const CodingString& codingString)
{
	ULong hash = 1;

	for (size_t index = 0; index < codingString.Lenght(); ++index)
		hash = codingString[index] + (hash << 6) + (hash << 16) - hash;

	return hash;
}

HashTable::HashTable(const ULong tableSize) :
	_tableSize(tableSize), _itemsCount(0), _codes(new const CodingString* [tableSize])
{
	std::fill(_codes, _codes + tableSize, nullptr);
}

HashTable::~HashTable()
{
	Clear();

	delete[] _codes;
}

const ULong HashTable::Add(const CodingString& newData)
{
	if (_itemsCount < _tableSize)
	{
		const ULong hash = GetHash(newData) % _tableSize;
		ULong index = hash;

		while (_codes[index] && index < _tableSize)
			++index;

		if (index == _tableSize)
		{
			index = 0;

			while (_codes[index] && index < hash)
				++index;
		}

		_codes[index] = new const CodingString(newData);
		++_itemsCount;

		return index;
	}

	throw new std::overflow_error("Table is full");
}

const ULong* HashTable::Find(const CodingString& target) const
{
	const ULong* returnIndex = nullptr;

	if (_itemsCount)
	{
		const ULong hash = GetHash(target) % _tableSize;
		ULong index = hash;

		while (!returnIndex && _codes[index] && index < _tableSize)
		{
			if (*(_codes[index]) == target)
				returnIndex = new const ULong(index);
			else
				++index;
		}

		if (!returnIndex)
		{
			index = 0;

			while (!returnIndex && _codes[index] && index < hash)
			{
				if (*(_codes[index]) == target)
					returnIndex = new const ULong(index);
				else
					++index;
			}
		}
	}

	return returnIndex;
}

const bool HashTable::IsFull() const noexcept
{
	return _tableSize == _itemsCount;
}

void HashTable::Clear()
{
	const int chunkSize = int(_tableSize / omp_get_max_threads());

	#pragma omp parallel for schedule(dynamic, chunkSize)
	for (long long index = 0; index < _tableSize; ++index)
		if (_codes[index])
		{
			delete _codes[index];
			_codes[index] = nullptr;
		}

	_itemsCount = 0;
}

const CodingString* HashTable::operator[](const ULong index) const
{
	return _codes[index];
}

void __fastcall PopulateTable(HashTable& encodingTable)
{
	for (int byte = 0; byte <= UCHAR_MAX; ++byte)
	{
		CodingString string(1);
		string += (Byte)byte;

		encodingTable.Add(string);
	}
}