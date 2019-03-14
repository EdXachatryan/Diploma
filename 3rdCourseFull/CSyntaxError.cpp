#include "SyntaxError.h"



CSyntaxError::CSyntaxError()
{
}


CSyntaxError::~CSyntaxError()
{
}

std::string CSyntaxError::printError(const ESyntaxError& eType, const std::string& sError)
{
	switch (eType)
	{
		case ESyntaxError::e_FirstArgument:
		{
			return sError + std::string(" first argument is not true");
		}
		case ESyntaxError::e_LastArgument:
		{
			return sError + std::string(" last argument is not true");
		}
		case ESyntaxError::e_UndefinedArgument:
		{
			return sError + std::string(" argument is undefined");
		}
		case ESyntaxError::e_IncompatibleArgument:
		{
			return sError + std::string(" arguments are incompatible");
		}
		case ESyntaxError::e_NoEqualBracket:
		{
			return std::string(" brackets count is not true");
		}
		default:
			return "undefined error";
			break;
		}
}
