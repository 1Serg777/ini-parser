#include "../include/Ini.h"

#include "../include/Error.h"

// Helper functions

//template <>
//std::string Stringify<std::string>(const std::string& value)
//{
//	return value;
//}

// IniGroup

IniGroup::IniGroup(const std::string& iniGroupName)
	: iniGroupName(iniGroupName)
{
}

const std::string& IniGroup::GetValueStr(const std::string& key) const
{
	auto find = options.find(key);
	if (find == options.end())
		throw IniSettingKeyNotFoundError(key);
	return find->second;
}

long long IniGroup::GetValueLongLong(const std::string& key) const
{
	auto find = options.find(key);
	if (find == options.end())
		throw IniSettingKeyNotFoundError(key);

	long long val{};
	try
	{
		val = std::stoll(find->second);
	}
	catch (std::invalid_argument iae)
	{
		throw IniSettingValueCastError(key, find->second, "long long");
	}
	catch (std::out_of_range oore)
	{
		throw IniSettingValueCastError(key, find->second, "long long");
	}

	return val;
}
int IniGroup::GetValueInt(const std::string& key) const
{
	auto find = options.find(key);
	if (find == options.end())
		throw IniSettingKeyNotFoundError(key);

	int val{};
	try
	{
		val = std::stoi(find->second);
	}
	catch (std::invalid_argument iae)
	{
		throw IniSettingValueCastError(key, find->second, "int");
	}
	catch (std::out_of_range oore)
	{
		throw IniSettingValueCastError(key, find->second, "int");
	}

	return val;
}

double IniGroup::GetValueDouble(const std::string& key) const
{
	auto find = options.find(key);
	if (find == options.end())
		throw IniSettingKeyNotFoundError(key);

	double val{};
	try
	{
		val = std::stod(find->second);
	}
	catch (std::invalid_argument iae)
	{
		throw IniSettingValueCastError(key, find->second, "double");
	}
	catch (std::out_of_range oore)
	{
		throw IniSettingValueCastError(key, find->second, "double");
	}

	return val;
}
float IniGroup::GetValueFloat(const std::string& key) const
{
	auto find = options.find(key);
	if (find == options.end())
		throw IniSettingKeyNotFoundError(key);

	float val{};
	try
	{
		val = std::stof(find->second);
	}
	catch (std::invalid_argument iae)
	{
		throw IniSettingValueCastError(key, find->second, "float");
	}
	catch (std::out_of_range oore)
	{
		throw IniSettingValueCastError(key, find->second, "float");
	}

	return val;
}

const std::string& IniGroup::GetGroupName() const
{
	return iniGroupName;
}

// IniSettings

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