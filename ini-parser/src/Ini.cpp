#include "../include/Ini.h"

// Helper functions

//template <>
//std::string Stringify<std::string>(const std::string& value)
//{
//	return value;
//}

std::string IniOptionTypeToString(IniOptionType optionType)
{
	switch (optionType)
	{
	case IniOptionType::STRING:
		return "STRING";
		break;
	case IniOptionType::INTEGER:
		return "INTEGER";
		break;
	case IniOptionType::FLOAT:
		return "FLOAT";
		break;
	}
	return "UNDEFINED";
}

// Ini Option

IniOption::IniOption(
	const std::string& key,
	const std::string& value,
	IniOptionType optionType)
	: key(key), value(value), optionType(optionType)
{
}

const std::string& IniOption::GetKey() const
{
	return key;
}

IniOptionType IniOption::GetOptionType() const
{
	return optionType;
}

// Ini Group

IniGroup::IniGroup(const std::string& iniGroupName)
	: iniGroupName(iniGroupName)
{
}

void IniGroup::AddOption(std::shared_ptr<IniOption> iniOption)
{
	options.insert({ iniOption->GetKey(), iniOption });
}

bool IniGroup::OptionExists(const std::string& key) const
{
	std::shared_ptr<IniOption> option = GetOption(key);
	return option ? true : false;
}

std::shared_ptr<IniOption> IniGroup::GetOption(const std::string& key) const
{
	auto find = options.find(key);
	if (find == options.end())
		return std::shared_ptr<IniOption>{};
	return find->second;
}

const std::string& IniGroup::GetGroupName() const
{
	return iniGroupName;
}

// Ini Settings

void IniSettings::AddGroup(std::shared_ptr<IniGroup> iniGroup)
{
	groups.insert({ iniGroup->GetGroupName(), iniGroup });
}
std::shared_ptr<IniGroup> IniSettings::GetGroup(const std::string& groupName) const
{
	auto find = groups.find(groupName);
	if (find == groups.end())
		return std::shared_ptr<IniGroup>{};
	return find->second;
}

void PrintIniSettings(std::ostream& outputStream, std::shared_ptr<IniSettings> iniSettings)
{

}