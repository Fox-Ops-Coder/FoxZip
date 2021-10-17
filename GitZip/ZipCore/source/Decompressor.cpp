#include "../include/File.hpp"
#include "../include/FileHeader.hpp"
#include "../include/Decompressor.hpp"
#include "../include/HashTable.hpp"
#include "../include/BFile.hpp"

#pragma warning(disable: 6993)

const FilePath* __fastcall GetFileName(const FileHeader& header, const FilePath& outDir)
{
	const FileName& name = *(header.Name());

	const int totalLenght = (name.Lenght() + outDir.Lenght()) + 1;
	wchar_t* path = new wchar_t[totalLenght];

	#pragma omp parallel sections
	{
		#pragma omp section
		{
			#pragma omp parallel for schedule(dynamic)
			for (int index = 0; index < outDir.Lenght(); ++index)
				path[index] = outDir[index];
		}

		#pragma omp section
		{
			path[outDir.Lenght()] = L'\\';

			#pragma omp parallel for schedule(dynamic)
			for (int index = outDir.Lenght() + 1; index < totalLenght; ++index)
				path[index] = name[-(outDir.Lenght() - (index - 1))];
		}
	}

	return new const FilePath(path, Byte(totalLenght));
}

const bool __fastcall Expand(FILE* const outFile, const CodeData& codes, const ULong tableSize, int& step, bool& stop)
{
	const ULong clearTable = tableSize + 1;

	FileData bytes(codes.Capacity(), 1500000);
	HashTable encodingTable(tableSize);

	PopulateTable(encodingTable);

	ULong oldCode = codes[0];
	ULong newCode;
	Byte character;

	bytes += *encodingTable[oldCode];

	size_t index = 1;
	while (!stop && index < codes.Lenght())
	{
		step = int(((float)index / ((float)codes.Lenght() - 1)) * 100.0);

		if (codes[index] != tableSize + 1)
		{
			CodingString tempString(12);
			newCode = codes[index];

			if (!encodingTable[newCode])
			{
				tempString += *encodingTable[oldCode];
				tempString += character;
			}
			else
				tempString += *encodingTable[newCode];

			#pragma omp parallel sections
			{
				#pragma omp section
				bytes += tempString;

				#pragma omp section
				{
					character = tempString[0];

					CodingString newString(*encodingTable[oldCode]);
					newString += character;

					encodingTable.Add(newString);
				}
			}

			oldCode = newCode;
			++index;
		}
		else
		{
			oldCode = codes[index + 1];
			bytes += *encodingTable[oldCode];

			index += 2;

			encodingTable.Clear();
			PopulateTable(encodingTable);
		}
	}

	if (!stop)
		WriteData(*outFile, bytes);

	return true;
}

const bool __fastcall ExpandArchive(const FilePath& archiveFilePath, const FilePath& outPutDirPath, int& step, bool& stop)
{
	bool isSuccses = false;

	FILE* archiveFile = nullptr;
	FILE* outFile = nullptr;

	OpenFile(&archiveFile, archiveFilePath, L"rb");

	if (archiveFile)
	{
		const FileHeader* header = ReadHeader(*archiveFile);
		const FilePath* fileName = GetFileName(*header, outPutDirPath);

		_wfopen_s(&outFile, fileName->Array(), L"wb");

		if (outFile)
		{
			BFile* bFile = new BFile(archiveFile, BitsCount(header->TableSize() + 1));

			const CodeData* const codes = bFile->ReadData();

			delete bFile;

			archiveFile = nullptr;

			if (codes)
			{
				isSuccses = Expand(outFile, *codes, header->TableSize(), step, stop);

				delete codes;
			}

			fclose(outFile);

			if (stop)
				_wremove(fileName->Array());

		}

		delete fileName;
		delete header;

		if (archiveFile)
			fclose(archiveFile);
	}

	return isSuccses;
}