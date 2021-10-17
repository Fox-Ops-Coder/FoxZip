#ifndef TYPEDEF_HPP
#define TYPEDEF_HPP

#include "GenericArray.hpp"

typedef unsigned char Byte;
typedef unsigned int UInt;
typedef unsigned long ULong;

typedef GenericArray<wchar_t, Byte> FilePath;
typedef GenericArray<wchar_t, Byte> FileName;
typedef GenericArray<Byte, size_t> CodingString;
typedef GenericArray<Byte, size_t> FileData;
typedef GenericArray<ULong, size_t> CodeData;

#endif // !TYPEDEF_HPP