#include "pch.h"

std::wstring ExePath() {
	TCHAR buffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
	return std::wstring(buffer).substr(0, pos);
}

void DumpExeFiles()
{
	auto currentPath = ExePath();
	for (const auto& file : std::filesystem::directory_iterator(currentPath))
	{
		//Dump all exe files
		if (!file.is_directory() && file.path().extension() == ".exe")
		{
			std::cout << file.path() << std::endl;
			std::ifstream infile;
			std::ofstream outfile;
			outfile.open(std::wstring(file.path().stem()) + std::wstring(L".dump") + std::wstring(file.path().extension()), std::ios::binary);
			infile.open(file.path(), std::ios::binary | std::ios::ate);
			auto size = infile.tellg();
			infile.seekg(0, std::ios::beg);
			auto data = new char[size];
			infile.read(data, size);
			outfile.write(data, size);
			infile.close();
			outfile.close();
		}
	}
	std::cout << "DONE" << std::endl;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		AllocConsole();
		FILE* fDummy;
		freopen_s(&fDummy, "CONIN$", "r", stdin);
		freopen_s(&fDummy, "CONOUT$", "w", stderr);
		freopen_s(&fDummy, "CONOUT$", "w", stdout);
		DumpExeFiles();
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

