#ifndef FILEHEADER_HPP
#define FILEHEADER_HPP

#include <cstdio>
#include "TypeDef.hpp"

class FileHeader
{
	public:
		FileHeader(const ULong tableSize, const FileName* name);
		FileHeader(const FileHeader& header);
		FileHeader(FileHeader&& header) noexcept;

		~FileHeader();

		const ULong TableSize() const noexcept;
		const FileName* Name() const noexcept;

	private:
		const ULong _tableSize;
		const FileName* _name;
};

void __fastcall WriteHeader(const FileHeader& header, FILE& file);
const FileHeader* __fastcall ReadHeader(FILE& file);

#endif // !FILEHEADER_HPP