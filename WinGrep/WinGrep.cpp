// WinGrep.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "boost\program_options.hpp"
#include "FileContentSearcher.h"
#include <iostream>
#include <fcntl.h>
#include <io.h>

using namespace std;
using namespace boost ::program_options;

int _tmain(int argc, _TCHAR* argv[])
{
	locale::global(locale(""));

	options_description desc;
	desc.add_options() ("help", "Produce help message.");
	desc.add_options() ("paths", wvalue<vector<wstring>>()->multitoken(), "Space separated paths to search in.");
	desc.add_options() ("search", wvalue<wstring>(), "Exact string to search in files.");
	desc.add_options() ("maxsize", value<int>()->default_value(-1), "The maximum file size in bytes to search in. Enter -1 to search all files.");
	desc.add_options() ("unicode", "Output in Unicode.");
	desc.add_options() ("debug", "Print debug information.");
	variables_map vm;
	store(parse_command_line(argc, argv, desc), vm);
	notify(vm);

	if (vm.count("help") || 
		vm.count("paths") == 0 ||
		vm.count("search") == 0) {
		cout << "WinGrep Usage:" << endl << "\tWinGrep --paths=(Paths to search) --search=(Exact string to search) [--maxsize=(Max file size in bytes to search in)]" << endl << endl;

		cout << desc << endl;
		
		return 0;
	}

	bool isDebug = (vm.count("debug") > 0);

	CString searchQuery(vm["search"].as<wstring>().c_str());
	vector<wstring> searchPaths = vm["paths"].as< vector<wstring> >();
	int maxFileSize = vm["maxsize"].as<int>();
	bool useUnicode = (vm.count("unicode") > 0);

	if (useUnicode)
	{
		_setmode(_fileno(stdout), _O_U16TEXT);
	}
	
	if (isDebug)
	{
		wcout<< L"DEBUG: Search string to search: " << searchQuery.GetString() << endl;
		wcout << L"DEBUG: Max file size to search: " << maxFileSize << endl;
	}

	FileContentSearcher contentSearcher(maxFileSize);
	
	for (vector<wstring>::iterator itr = searchPaths.begin(); itr != searchPaths.end(); ++itr)
	{
		CString path(itr->c_str());

		if (path.ReverseFind(L'\\') != path.GetLength() - 1)
		{
			path.AppendChar(L'\\');
		}

		if (isDebug)
		{
			wcout << L"DEBUG: Searching in path: " << path.GetString() << endl;
		}

		contentSearcher.FindFiles(path, searchQuery);
	}

	return 0;
}