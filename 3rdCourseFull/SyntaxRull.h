#ifndef CSYNTAX_RULL_H
#define CSYNTAX_RULL_H

#include "Enums.h"
#include <vector>
#include "Parser.h"
#include "SyntaxError.h"


class ISyntaxRull
{
public:
	virtual bool checkTokenList() = 0;
	virtual void setTokens(std::vector <SToken*> &) = 0;
};

class CSyntaxRull : public ISyntaxRull
{
	// +( (+  -(-8 unar minusna  )) ete ka ((  ,(+)   *+ sxala (* sxala bayc (+ u (- chishta
	enum class EOperators : char
	{
		e_Plus = '+',//ascii codna galu
		e_Minus = '-',
		e_Mul = '*',
		e_Div = '/',
		e_LBracket = '(',
		e_RBracket = ')',
		e_Unar,// -5 ,(-4) tiv * -1 unar minusna tali ???????
		e_PlusLBracket = e_Plus + e_LBracket,//+(  0 + 10 //chista cuyc talu sra valuen = 43 + 40
		e_LBracketPlus = e_LBracket + e_Plus, // (+  4 + 10
		e_MinusLBracket = e_Minus + e_LBracket,//-( 
		e_LBracketMinus = e_LBracket + e_Minus, // (-
		// -) chi kara lini
		//bayc kara ) + 4 lini bayc voch ) + u verj 
		// (a+b)*c kara bayc (a+b)* chi kara lini
		e_RBracketPlus = e_RBracket + e_Plus,
		e_RBracketMinus = e_RBracket + e_Minus,
		e_RBracketDiv = e_RBracket + e_Div,
		e_RBracketMul = e_RBracket + e_Mul,
		//petqa stugvi mer unecac operatorner@ enumi het brnum en te che ete che uremn sxal operator ka
	};

	// if have + operator and ekela *opertor  kunenam +* static_cast<eoprators> (+*); 

public:
	CSyntaxRull(std::vector <SToken*> &bbb);
	CSyntaxRull() = default;
	~CSyntaxRull();

	operator bool();
	bool checkOperators(const Etype& m_ePrevType, const Etype& m_eCurrType);
	bool checkNeighborTokens();
	bool checkUndefined();
	bool checkFirstToken();
	bool checkLastToken();
	bool checkBrakets();
	void clear();
	inline void setTokens(std::vector <SToken*> &);
	bool checkTokenList() override;
private:
	std::vector<SToken*>* m_aTokenList;
	Etype m_ePrevType;
	Etype m_eCurrType;
	int m_nPos;
	int m_CBracket;// ete ( es++ karvi ete ) -- karvi => ete aranc (sra )es lini apa esi 0 ic poqr tiv klni 

};




////////////////////////////////////////////////////////////////////////////////
//
//  inline implementations CSyntaxRull
//
////////////////////////////////////////////////////////////////////////////////

inline bool CSyntaxRull::checkUndefined()
{
	if (m_eCurrType == Etype::e_Undefined || m_ePrevType == Etype::e_Undefined)
		CSyntaxError::printError(CSyntaxError::ESyntaxError::e_UndefinedArgument, m_aTokenList->at(m_nPos)->m_sValue);
	return true;
}

inline bool CSyntaxRull::checkFirstToken()
{
	if (m_ePrevType == Etype::e_Operator)
	{
		int nFirstOp = static_cast<int>(m_aTokenList->at(m_nPos)->m_sValue.at(0));
		if (nFirstOp == 41 || nFirstOp == 42 || nFirstOp == 47)
			CSyntaxError::printError(CSyntaxError::ESyntaxError::e_FirstArgument, m_aTokenList->at(m_nPos)->m_sValue);
	}
	return true;
}

inline bool CSyntaxRull::checkLastToken()
{
	if (m_eCurrType == Etype::e_Operator)
	{
		int nFirstOp = static_cast<int>(m_aTokenList->at(m_nPos)->m_sValue.at(0));
		if (nFirstOp != 41)//only ) operator true
			CSyntaxError::printError(CSyntaxError::ESyntaxError::e_LastArgument, m_aTokenList->at(m_nPos)->m_sValue);
	}
	return true;
}

inline bool CSyntaxRull::checkBrakets()
{
	if (!m_CBracket) 
		return true;
	CSyntaxError::printError(CSyntaxError::ESyntaxError::e_NoEqualBracket);
}
inline void CSyntaxRull::clear()
{
	m_aTokenList->clear();
}

inline void CSyntaxRull::setTokens(std::vector<SToken*>& tokens)
{
	if (m_aTokenList != nullptr)
		clear();
	m_aTokenList = &tokens;
}
#endif // !CSYNTAX_RULL_H
