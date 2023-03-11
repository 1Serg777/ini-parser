#include <cassert>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include "../include/Error.h"
#include "../include/Ini.h"
#include "../include/IniScanner.h"
#include "../include/IniParser.h"

void InitializeSettings(IniGroup* iniGroup);
std::string LoadIniFile(const std::filesystem::path& iniFile);

std::unordered_map<std::string, std::string> settings;

int main(int argc, char* argv[])
{
	std::filesystem::path assetsRootPath = std::filesystem::path{ argv[0] }.remove_filename();
	assetsRootPath = assetsRootPath / "Assets";

	std::filesystem::path testIniPath = assetsRootPath / "test.ini";

	std::string iniSrc = LoadIniFile(testIniPath);

	IniParser iniParser{};
	try
	{
		iniParser.Parse(iniSrc);
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

	std::cout << std::endl;
	
	IniGroup iniGroup{ "General" };
	InitializeSettings(&iniGroup);
	try
	{
		int filter_type = iniGroup.GetOptionValue<int>("filter_type");
		std::cout << "filter_type = " << filter_type << "\n";

		// Error casting a path to an int variable!
		// we get 0 instead of an error
		// You think it's better to throw an error
		// or just default construct an object of specified type?
		// 
		// filter_type = iniGroup.GetOptionValue<int>("path");
		// std::cout << "filter_type = " << filter_type << "\n";

		float version = iniGroup.GetOptionValue<float>("version");
		std::cout << "version = " << version << "\n";

		std::string uuid_str = iniGroup.GetOptionValue<std::string>("uuid");
		std::cout << "uuid = " << uuid_str << "\n";
	}
	catch (const IniSettingValueCastError& isvce)
	{
		std::cerr << isvce.what() << std::endl;
		return EXIT_FAILURE;
	}
	catch (const IniSettingOptionNotFoundError& isknfe)
	{
		std::cerr << isknfe.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

void InitializeSettings(IniGroup* iniGroup)
{
	iniGroup->AddOption("double_val", double{ 3.14 });
	iniGroup->AddOption("str_val", std::string{ "val" });

	iniGroup->AddOption("path", std::string{ "Assets\\blocks.png" });
	iniGroup->AddOption("uuid", std::string{ "18AED8496FACA81" });
	iniGroup->AddOption("uuid_short", std::string{ "18AED849" });

	// iniGroup->AddOption("filter_type", std::string{ "2" });
	iniGroup->AddOption("filter_type", 2);

	iniGroup->AddOption("type", std::string{ "Texture" });

	// iniGroup->AddOption("version", std::string{ "2.5f" });
	iniGroup->AddOption("version", 2.5f);
}

std::string LoadIniFile(const std::filesystem::path& iniFile)
{
	assert(!iniFile.empty() && "The path to an ini file must not be empty!");
	std::ifstream file{ iniFile , std::ios::binary };

	if (file.fail())
	{
		throw std::ifstream::failure{ "I/O runtime error was thrown openning a shader file!" };
	}

	std::ostringstream ostream{};
	ostream << file.rdbuf();

	std::string shaderSrc = ostream.str();
	return shaderSrc;
}