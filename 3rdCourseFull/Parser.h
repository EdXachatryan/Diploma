#ifndef CPARSER_H
#define CPARSER_H
#include <istream>
#include <vector>
#include <string>
#include "Enums.h"
//namespace parse {
//namespace {  // Let's try anonymously namespace
	
using std::string;
class CTokenizer;
class ISyntaxRull;

struct SToken
{
	Etype m_type;
	std::string m_sValue;
};

class CParser
{
	// errorner@ petqa parser@ gci 
	//vrov vazi tokkenneri stugi vor +++ chlni kam 9av chlini ` validate ani eli
	// dra hamar karelia ruler` kanner mshakel vorov petqa stugvi tokkenner@
public:
	CParser(std::string);
	CParser(std::istream);
	~CParser() ;
	void parse(std::istream);
	
	void stringToTeken(std::string&);
	bool checkSyntaxis();
	void parse();

private:
	std::vector<SToken*> m_aTokenList;
	CTokenizer* m_Tokenizer;
	ISyntaxRull* m_pSyntRul;
	
	/*std::string nextToken();
	std::vector<std::string> aTokens;
	std::string m_str;*/
	// heta tali bajanvac tokenner@ vornel talisa lexerin lexernel joguma te ova u creata anum tvyal camandan u heta tali parserin vornel havaquma ira mej et comandaner@
	//bool isDelim();
	//bool isOperand();
	//bool isOperator();
};


// tarber classneri meji enumner@ karan conflict tan ?
class CTokenizer
{
	enum EOperator
	{
		e_Minus = '-',
		e_Plus = '+',
		e_Mul = '*',
		e_Div = '/',
		e_Assign = '=',
		e_LBracket = '(',
		e_RBrachet = ')'
		// unar minus@ u es minus@ nuyna voncvor
	};

public:
	CTokenizer(std::string& );
	void splitToTokens(std::vector<SToken*>& tokens);
	bool isDelim(char) const;
	
	// inline functions
	void deleteSpace();
	//int getCount() const;
	//inline std::vector<SToken*> getTokens() const;
	//inline SToken* getToken(int pos);
private:
	bool isNumber(char);
	bool isIdentifer(char);
	bool isOperator(char);//char ` 1 byte aveli araga qan * vortev pointeri size 8 byte e

	int m_nPos;
	std::string m_sText;
};


///////////////////////////////////////////////////////////////////////////////
//
// implementation of inline function CTokenizer
//
///////////////////////////////////////////////////////////////////////////////
//
//inline std::vector<SToken*> CTokenizer::getTokens()const
//{
//	(getCount()) ? m_aTokenList : std::vector<SToken*>();
//
//	//if (getCount())
//	//	return m_aTokenList;
//	//return std::vector<SToken>();
//}
//
//inline SToken* CTokenizer::getToken(int pos)
//{
//	return m_aTokenList.at(pos);
//}

inline bool CTokenizer::isNumber(char ch)
{
	if (isdigit(ch))
		return true;
	return false;
}


//}

#endif // ! CPARSER_H

