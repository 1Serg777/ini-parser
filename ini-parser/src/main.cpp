#include <cassert>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

#include "../include/Error.h"
#include "../include/Ini.h"
#include "../include/IniParser.h"

constexpr std::string_view iniFileExt{ ".ini" };

void PrintUsage();
bool CheckFile(const std::filesystem::path& iniFilePath);

std::unordered_map<std::filesystem::path, std::shared_ptr<IniSettings>> iniSettings;

int main(int argc, char* argv[])
{
	if (argc == 1)
		PrintUsage();

	for (int i = 1; i < argc; i++)
	{
		std::filesystem::path iniFilePath = std::filesystem::path{ argv[i] };
		if (!CheckFile(iniFilePath))
			continue;

		IniParser iniParser{};
		try
		{
			iniParser.Parse(iniFilePath);
		}
		catch (IniScannerError scannerException)
		{
			std::cerr << scannerException.what() << std::endl;
		}
		catch (IniParserError parserException)
		{
			std::cerr << parserException.what() << std::endl;
		}

		std::shared_ptr<IniSettings> iniSettings = iniParser.GetIniSettings();
		IniSettingsPrinter::PrintIniSettings(std::cout, iniSettings);

		std::cout << "\n";
	}

	return EXIT_SUCCESS;
}

void PrintUsage()
{
	std::cout << "Usage: ini-parser [PATH1, PATH2, ...]\n";
	std::cout << "Where [PATH(N)] is the path to an .ini file\n";
}
bool CheckFile(const std::filesystem::path& iniFilePath)
{
	std::filesystem::path filePath = iniFilePath;
	std::string fileExt = filePath.extension().generic_string();
	if (fileExt != iniFileExt)
	{
		std::cout << "The following path is not a path to an .ini file!\n";
		std::cout << "[PATH]: " << iniFilePath << "\n";
		return false;
	}
	return true;
}