#include "../include/FileHeader.hpp"

FileHeader::FileHeader(const ULong tableSize, const FileName* name) :
	_tableSize(tableSize), _name(name) {}

FileHeader::FileHeader(const FileHeader& header) :
	_tableSize(header._tableSize),
	_name(new const FileName(*(header._name))) {}

FileHeader::FileHeader(FileHeader&& header) noexcept :
	_tableSize(header._tableSize), _name(std::move(header._name)) {}

FileHeader::~FileHeader()
{
	if (_name)
		delete _name;
}

const ULong FileHeader::TableSize() const noexcept
{
	return _tableSize;
}

const FileName* FileHeader::Name() const noexcept
{
	return _name;
}

void __fastcall WriteHeader(const FileHeader& header, FILE& file)
{
	const ULong tableSize = header.TableSize();
	const FileName* name = header.Name();
	const Byte nameLenght = name->Lenght();

	fwrite(&tableSize, sizeof(ULong), 1, &file);
	fwrite(&nameLenght, sizeof(Byte), 1, &file);
	fwrite(name->Array(), sizeof(wchar_t), nameLenght, &file);
}

const FileHeader* __fastcall ReadHeader(FILE& file)
{
	ULong tableSize;
	Byte nameLenght;

	fread_s(&tableSize, 1 * sizeof(ULong), sizeof(ULong), 1, &file);
	fread_s(&nameLenght, 1, sizeof(Byte), 1, &file);

	wchar_t* fileName = new wchar_t[nameLenght];

	fread_s(fileName, sizeof(wchar_t) * nameLenght, sizeof(wchar_t), nameLenght, &file);

	return new const FileHeader(tableSize, new const FileName(fileName, nameLenght));
}