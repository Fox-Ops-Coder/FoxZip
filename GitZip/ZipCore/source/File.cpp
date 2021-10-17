#include "../include/File.hpp"
#include "../include/CorrectPath.hpp"

void __fastcall OpenFile(FILE** file, const FilePath& path, const wchar_t* const mode)
{
	const wchar_t* filePath = CreatePath(path);
	_wfopen_s(file, filePath, mode);

	delete[] filePath;
}

const size_t __fastcall FileSize(FILE& file)
{
	const size_t current = _ftelli64(&file);
	_fseeki64(&file, 0, SEEK_END);
	
	const size_t size = _ftelli64(&file);
	_fseeki64(&file, current, SEEK_SET);

	return size;
}

const FileData* __fastcall ReadFile(FILE& file)
{
	const size_t fileSize = FileSize(file);
	Byte* data = new Byte[fileSize];

	fread_s(data, fileSize, sizeof(Byte), fileSize, &file);

	return new const FileData(data, fileSize);
}

void __fastcall WriteData(FILE& file, const FileData& data)
{
	fwrite(data.Array(), sizeof(Byte), data.Lenght(), &file);
}

const Byte __fastcall BitsCount(const ULong maxValue)
{
	Byte bitsCount = 1;
	ULong value = 1;

	while (value < maxValue)
	{
		value <<= 1;
		++bitsCount;
	}

	return bitsCount;
}