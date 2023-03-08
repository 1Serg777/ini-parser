#include <cstdio>
#include <iostream>
#include <string>
#include <unordered_map>

#include "../include/Error.h"
#include "../include/Ini.h"

void InitializeSettings(IniGroup* iniGroup);

std::unordered_map<std::string, std::string> settings;

int main()
{
	IniGroup iniGroup{ "General" };
	InitializeSettings(&iniGroup);
	try
	{
		int filter_type = iniGroup.GetValueInt("filter_type");
		std::cout << "filter_type = " << filter_type << "\n";

		// Error casting a path to an int variable!
		// 
		// filter_type = iniGroup.GetValueInt("path");
		// std::cout << "filter_type = " << filter_type << "\n";

		float version = iniGroup.GetValueFloat("version");
		std::cout << "version = " << version << "\n";
	}
	catch (const IniSettingValueCastError& isvce)
	{
		std::cerr << isvce.what() << std::endl;
		return EXIT_FAILURE;
	}
	catch (const IniSettingKeyNotFoundError& isknfe)
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
	iniGroup->AddOption("filter_type", std::string{ "2" });
	iniGroup->AddOption("type", std::string{ "Texture" });
	iniGroup->AddOption("version", std::string{ "2.5f" });
}