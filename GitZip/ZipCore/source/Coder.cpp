#include "../include/TypeDef.hpp"
#include "../include/Coder.hpp"
#include "../include/Compressor.hpp"
#include "../include/Decompressor.hpp"

#pragma warning(disable: 6993)

const FilePath* GetPath(array<wchar_t>^ path)
{
	const int lenght = path->Length;
	wchar_t* filePath = new wchar_t[lenght];

	#pragma omp parallel for schedule(dynamic)
	for (int index = 0; index < lenght; ++index)
		filePath[index] = path[index];

	return new const FilePath(filePath, Byte(lenght));
}

FoxCoder::Coder::Coder() : 
	step(new int(0)), stop(new bool(false)), ended(false) {}

FoxCoder::Coder::~Coder()
{
	delete step;
	delete stop;
}

const bool FoxCoder::Coder::CompressFile(System::String^ sourceFilePath, System::String^ archiveFilePath, unsigned long tableSize)
{
	*stop = false;
	ended = false;

	const FilePath* sourceFile = nullptr;
	const FilePath* archiveFile = nullptr;

	#pragma omp parallel sections
	{
		#pragma omp section
		{
			array<wchar_t>^ path = sourceFilePath->ToCharArray();
			sourceFile = GetPath(path);
		}

		#pragma omp section
		{
			array<wchar_t>^ path = archiveFilePath->ToCharArray();
			archiveFile = GetPath(path);
		}
	}

	const bool isSuccess = CreateArchive(*sourceFile, *archiveFile, tableSize, *step, *stop);

	delete sourceFile;
	delete archiveFile;

	ended = true;

	return isSuccess;
}

const bool FoxCoder::Coder::DecompressFile(System::String^ archiveFilePath, System::String^ outPutDir)
{
	*stop = false;
	ended = false;

	const FilePath* sourceFile = nullptr;
	const FilePath* archiveFile = nullptr;

	#pragma omp parallel sections
	{
		#pragma omp section
		{
			array<wchar_t>^ path = archiveFilePath->ToCharArray();
			sourceFile = GetPath(path);
		}

		#pragma omp section
		{
			array<wchar_t>^ path = outPutDir->ToCharArray();
			archiveFile = GetPath(path);
		}
	}

	const bool isSuccess = ExpandArchive(*sourceFile, *archiveFile, *step, *stop);

	delete sourceFile;
	delete archiveFile;

	ended = true;

	return isSuccess;
}

int FoxCoder::Coder::GetStep()
{
	return *step;
}

void FoxCoder::Coder::Stop()
{
	*stop = true;
}

bool FoxCoder::Coder::Interupted()
{
	return *stop;
}
