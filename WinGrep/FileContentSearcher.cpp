#include "FileContentSearcher.h"
#include <iostream>

using namespace std;

FileContentSearcher::FileContentSearcher(int maxFileSize)
	:
	_maxFileSize(maxFileSize)
{
}


FileContentSearcher::~FileContentSearcher()
{
}

void FileContentSearcher::FindFiles(CString searchPathString, CString fileContent)
{
	path searchPath(searchPathString);

	if (!is_directory(searchPath) || !exists(searchPath) || is_symlink(searchPath))
	{
		return;
	}

	directory_iterator end_itr;

	try
	{
		for (directory_iterator itr(searchPath); itr != end_itr; ++itr)
		{
			try
			{
				if (is_directory(itr->status()))
				{
					FindFiles(itr->path().c_str(), fileContent);
				}
				else if (is_regular_file(itr->status()) &&
					file_size(itr->path()) > 0 &&
					IsValidFileSize(file_size(itr->path())))
				{
					ifstream fstream(itr->path().c_str());

					bool lineFound = false;

					while (fstream.good() && !fstream.eof() && !lineFound)
					{
						string line;
						getline(fstream, line);

						CString cLine(line.c_str());
						lineFound = (cLine.Find(fileContent) >= 0);
					}

					fstream.close();

					if (lineFound)
					{
						PrintFile(itr->path());
					}
				}
			}
			catch (const boost::filesystem::filesystem_error& ex)
			{
				WriteError(itr->path().wstring(), ex);
			}
		}
	}
	catch (const boost::filesystem::filesystem_error& ex)
	{
		WriteError(searchPath.wstring(), ex);
	}
}

void FileContentSearcher::WriteError(wstring path, boost::filesystem::filesystem_error ex)
{
	wcout << L"Error: Failed to read path:\"" << path << L"\". Exception: " << ex.what() << endl;
}

void FileContentSearcher::PrintFile(path filePath)
{
	wcout << filePath.wstring() << endl;
}