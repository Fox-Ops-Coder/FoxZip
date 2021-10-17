#ifndef COMPRESSOR_HPP
#define COMPRESSOR_HPP

#include "TypeDef.hpp"

const bool __fastcall CreateArchive(const FilePath& sourceFilePath,
	const FilePath& archiveFilePath,
	const ULong tableSize,
	int& step, bool& stop);

#endif // !COMPRESSOR_HPP
