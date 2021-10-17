#include "../include/Compressor.hpp"
#include "../include/HashTable.hpp"
#include "../include/FileHeader.hpp"
#include "../include/File.hpp"
#include "../include/BFile.hpp"
#include "../include/CorrectPath.hpp"

#pragma warning(disable: 6993)

const FileName* __fastcall GetFileName(const FilePath& filePath)
{
	Byte index = filePath.Lenght() - 1;
	while (index != 1 && filePath[index - 1] != L'\\')
		--index;

	const Byte fileNameLenght = (filePath.Lenght() - index) + 1;

	wchar_t* tempName = new wchar_t[fileNameLenght];

	std::copy(filePath.Array() + index, filePath.Array() + filePath.Lenght(), tempName);
	tempName[fileNameLenght - 1] = L'\000';

	return new const FileName(tempName, fileNameLenght);
}

const bool __fastcall Compress(FILE* const archiveFile, const FileData& bytes, const ULong tableSize, int& step, bool& stop)
{
	CodeData codeData(bytes.Lenght());

	HashTable encodingTable(tableSize);
	PopulateTable(encodingTable);

	CodingString currentString(12);
	currentString += bytes[0];

	size_t index = 1;
	while (!stop && index < bytes.Lenght())
	{
		step = int(((float)index / ((float)bytes.Lenght() - 1)) * 100.0);

		CodingString tempString(currentString);
		tempString += bytes[index];

		const ULong* tableIndex = encodingTable.Find(tempString);

		if (tableIndex)
		{
			currentString += bytes[index];
			delete tableIndex;
		}
		else
		{
			tableIndex = encodingTable.Find(currentString);

			#pragma omp parallel sections
			{
				#pragma omp section
				{
					codeData += *tableIndex;
					delete tableIndex;
				}

				#pragma omp section
				{
					currentString.Clean();
					currentString += bytes[index];
				}
			}

			if (encodingTable.IsFull())
			{
				#pragma omp parallel sections
				{
					#pragma omp section
					codeData += ULong(tableSize + 1);

					#pragma omp section
					{
						encodingTable.Clear();
						PopulateTable(encodingTable);
					}
				}
			}

			encodingTable.Add(tempString);
		}

		++index;
	}

	bool isSuccses = false;

	if (!stop)
	{
		const ULong* tableIndex = encodingTable.Find(currentString);

		codeData += *tableIndex;

		delete tableIndex;

		BFile bFile(archiveFile, BitsCount(tableSize + 1));
		bFile.WriteData(codeData);

		isSuccses = true;
	}

	return isSuccses;
}

const bool __fastcall CreateArchive(const FilePath& sourceFilePath,
	const FilePath& archiveFilePath,
	const ULong tableSize, int& step, bool& stop)
{
	bool isSuccses = false;

	FILE* sourceFile = nullptr;
	FILE* archiveFile = nullptr;

	#pragma omp parallel sections
	{
		#pragma omp section
		OpenFile(&sourceFile, sourceFilePath, L"rb");

		#pragma omp section
		OpenFile(&archiveFile, archiveFilePath, L"wb");
	}

	if (sourceFile && archiveFile)
	{
		const FileData* bytes = nullptr;
		const ULong encodingTableSize = tableSize >= 512 ? tableSize : ULong(FileSize(*sourceFile));

		#pragma omp parallel sections
		{
			#pragma omp section
			{
				bytes = ReadFile(*sourceFile);
				fclose(sourceFile);
			}

			#pragma omp section
			{
				const FileHeader header(encodingTableSize, GetFileName(sourceFilePath));
				WriteHeader(header, *archiveFile);
			}
		}

		isSuccses = Compress(archiveFile, *bytes, encodingTableSize, step, stop);

		fclose(archiveFile);

		if (stop)
		{
			const wchar_t* path = CreatePath(archiveFilePath);

			_wremove(path);

			delete[] path;
		}

		delete bytes;
	}

	return isSuccses;
}
