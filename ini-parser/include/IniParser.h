#pragma once

#include "Ini.h"
#include "IniScanner.h"

#include <memory>

// Parser related errors

class IniParserError : public std::runtime_error
{
public:

	IniParserError(const Token& errorToken, std::string_view errMsg);

	_NODISCARD const char* what() const override;

private:

	void CreateErrorMessage(std::string_view errMsg);

	Token errorToken;
	std::string errMsg;
};

// Ini Parser

class IniParser
{
public:

	IniParser();
	~IniParser();

	void Parse(const std::string& iniSource);

	std::shared_ptr<IniSettings> GetIniSettings() const;

private:

	void InitializeIniParser();

	std::shared_ptr<IniGroup> Group();
	std::string GroupId();
	std::shared_ptr<IniOption> Option();

	Token Advance();
	Token Peek() const;
	Token Previous() const;
	Token Consume(TokenType type, std::string_view errMsg);

	bool Check(TokenType type);
	bool AtEnd() const;

	void Clear();

	std::unique_ptr<IniScanner> iniScanner;
	std::vector<Token>* tokens{ nullptr };

	std::shared_ptr<IniSettings> iniSettings;

	int current{ 0 };
};