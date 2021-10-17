#include "../include/CorrectPath.hpp"

#pragma warning(disable: 6993)

const wchar_t* __fastcall CreatePath(const FilePath& path)
{
	wchar_t* filePath = new wchar_t[(size_t)path.Lenght() + 1];

	#pragma omp parallel for schedule(dynamic)
	for (int index = 0; index < path.Lenght(); ++index)
		filePath[index] = path[index];

	filePath[path.Lenght()] = L'\000';

	return filePath;
}