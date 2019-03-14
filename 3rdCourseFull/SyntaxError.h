#ifndef CSYNTAXERROR_H
#define CSYNTAXERROR_H
#include <exception>
#include <string>
class CSyntaxError : public std::exception
{
public:
	typedef enum class ESyntaxError 
	{
		e_IncompatibleArgument,
		e_FirstArgument,
		e_LastArgument,
		e_UndefinedArgument,
		e_NoEqualBracket

	} t_eSntErr;

public:
	CSyntaxError();
	~CSyntaxError();
	static std::string printError(const ESyntaxError&, const std::string& ="");

};
#endif // CSYNTAXERROR_H