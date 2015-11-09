#pragma once

#include "stdafx.h"
#include "boost/filesystem.hpp"

using namespace std;
using namespace boost::filesystem;

class FileContentSearcher
{
private:
	int _maxFileSize;

	bool IsValidFileSize(uintmax_t fileSize) { return _maxFileSize < 0 || fileSize <= _maxFileSize; };
	
	void WriteError(wstring path, boost::filesystem::filesystem_error ex);
	void PrintFile(path filePath);
public:
	FileContentSearcher(int maxFileSize);
	~FileContentSearcher();

	void FindFiles(CString searchPath, CString fileContent);
};

