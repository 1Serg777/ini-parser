#pragma once

#include <stdexcept>
#include <string>

// [GROUP]
// "key = value"

class IniSettingValueCastError : std::runtime_error
{
public:

	IniSettingValueCastError(
		const std::string& key,
		const std::string& value,
		const std::string& castType);

	_NODISCARD char const* what() const override;

private:

	void SetupErrorMessage(
		const std::string& key,
		const std::string& value,
		const std::string& castType);

	std::string message;
};

class IniSettingOptionNotFoundError : std::runtime_error
{
public:

	IniSettingOptionNotFoundError(const std::string& key);

	_NODISCARD char const* what() const override;

private:

	void SetupErrorMessage(const std::string& key);

	std::string message;
};