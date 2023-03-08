#pragma once

#include <memory>
#include <sstream>
#include <string>
#include <type_traits>
#include <unordered_map>

// Helper functions

template <typename T>
std::string Stringify(const T& value)
{
	std::stringstream sstream{};
	sstream << value;
	return sstream.str();
}
template <> inline
std::string Stringify<std::string>(const std::string& value)
{
	return value;
}

//template <>
//std::string Stringify<std::string>(const std::string& value);

class IniGroup
{
public:

	IniGroup(const std::string& iniGroupName);

	template <typename T>
	void AddOption(const std::string& key, const T& value)
	{
		options.insert({key, Stringify(value)});
	}

	const std::string& GetValueStr(const std::string& key) const;

	long long GetValueLongLong(const std::string& key) const;
	int GetValueInt(const std::string& key) const;

	double GetValueDouble(const std::string& key) const;
	float GetValueFloat(const std::string& key) const;

	const std::string& GetGroupName() const;

private:

	std::unordered_map<std::string, std::string> options;
	std::string iniGroupName;
};

class IniSettings
{
public:

	void AddGroup(std::shared_ptr<IniGroup> iniGroup);
	std::shared_ptr<IniGroup> GetGroup(const std::string& groupName) const;

private:

	std::unordered_map<std::string, std::shared_ptr<IniGroup>> groups;
};