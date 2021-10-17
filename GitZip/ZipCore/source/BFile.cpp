#include <functional>
#include <stdexcept>
#include <cstdio>

#include "../include/File.hpp"
#include "../include/BFile.hpp"

void BFile::WriteData(const CodeData& bytes)
{
	const ULong defaultMask = ULong(1L << (_bitsCount - 1));

	const std::function<void(const ULong)> writeByte = [this, defaultMask](const ULong code)
	{
		ULong tempMask = defaultMask;

		while (tempMask)
		{
			if (tempMask & code) _rack |= _mask;

			_mask >>= 1;

			if (!_mask)
			{
				putc(_rack, _file);
				_rack = 0;
				_mask = maskDefault;
			}

			tempMask >>= 1;
		}
	};

	for (size_t index = 0; index < bytes.Lenght(); ++index)
		writeByte(bytes[index]);

	if (_rack)
		putc(_rack, _file);

	const char end = 42;
	fwrite(&end, sizeof(char), 1, _file);
}

const size_t __fastcall GetEndPlace(FILE* const file)
{
	const size_t current = _ftelli64(file);
	_fseeki64(file, -int(sizeof(char)), SEEK_END);
	const size_t endPlace = _ftelli64(file);

	char end;
	fread_s(&end, sizeof(char), sizeof(char), 1, file);

	if (end != 42)
		throw new std::exception("Error File");

	_fseeki64(file, current, SEEK_SET);

	return endPlace;
}

const CodeData* BFile::ReadData()
{
	size_t endPlace;

	try
	{
		endPlace = GetEndPlace(_file);
	}
	catch (std::exception* err)
	{
		delete err;

		return nullptr;
	}

	const ULong defaultMask = ULong(1L << (_bitsCount - 1));

	const std::function<const ULong()> readByte = [this, defaultMask]() -> const ULong
	{
		ULong tempMask = defaultMask;
		ULong returnValue = 0;

		while (tempMask)
		{
			if (_mask == maskDefault)
			{
				_rack = getc(_file);
				if (_rack == EOF) throw new std::exception("EOF");
			}

			if (_rack & _mask) returnValue |= tempMask;

			tempMask >>= 1;
			_mask >>= 1;

			if (!_mask) _mask = maskDefault;
		}

		return returnValue;
	};

	const size_t fileSize = FileSize(*_file) / sizeof(ULong);

	CodeData data(fileSize, 15000);
	const CodeData* returnData = nullptr;

	try
	{
		while (size_t(_ftelli64(_file)) < endPlace)
			data += readByte();

		returnData = new const CodeData(data);
	}
	catch (std::exception* err)
	{
		delete err;
	}

	return returnData;
}

BFile::~BFile()
{
	fclose(_file);
}

BFile::BFile(FILE* const file, const Byte bitsCount) noexcept :
	_file(file),
	_mask(maskDefault), _bitsCount(bitsCount), _rack(0) {}