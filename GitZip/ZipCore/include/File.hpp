#ifndef FILE_HPP
#define FILE_HPP

#include <cstdio>
#include "TypeDef.hpp"

void __fastcall OpenFile(FILE** file, const FilePath& path, const wchar_t* const mode);

const size_t __fastcall FileSize(FILE& file);

const FileData* __fastcall ReadFile(FILE& file);

void __fastcall WriteData(FILE& file, const FileData& data);

const Byte __fastcall BitsCount(const ULong maxValue);

#endif // !FILE_HPP