#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include "TypeDef.hpp"

class HashTable
{
	public:
		HashTable(const ULong tableSize);
		HashTable(const HashTable& table) = delete;
		HashTable(HashTable&& table) = delete;

		~HashTable();

		const ULong Add(const CodingString& newData);
		const ULong* Find(const CodingString& target) const;
		const bool IsFull() const noexcept;

		void Clear();

		const CodingString* operator[](const ULong index) const;

	private:

		const ULong _tableSize;
		ULong _itemsCount;

		const CodingString** const _codes;
};

void __fastcall PopulateTable(HashTable& encodingTable);

#endif // !HASHTABLE_HPP