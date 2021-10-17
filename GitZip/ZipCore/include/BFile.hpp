#ifndef BFILE_HPP
#define BFILE_HPP

#include <cstdio>
#include "TypeDef.hpp"

class BFile
{
	public:
		BFile(FILE* const file, const Byte bitsCount) noexcept;
		BFile(const BFile& bFile) = delete;
		BFile(BFile&& bFile) = delete;

		void WriteData(const CodeData& codes);
		const CodeData* ReadData();

		~BFile();

	private:
		FILE* const _file;

		static const Byte maskDefault = 0x80;

		int _rack;
		const Byte _bitsCount;
		Byte _mask;
};

#endif // !BFILE_HPP