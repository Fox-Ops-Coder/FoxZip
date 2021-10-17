#ifndef DECOMPRESSOR_HPP
#define DECOMPRESSOR_HPP

#include "TypeDef.hpp"

const bool __fastcall ExpandArchive(const FilePath& archiveFilePath,
	const FilePath& outPutDirPath,
	int& step, bool& stop);

#endif // !DECOMPRESSOR_HPP