#include "SyntaxRull.h"

CSyntaxRull::CSyntaxRull(std::vector<SToken*>& tokens)
{
	m_aTokenList = &tokens;
}

CSyntaxRull::~CSyntaxRull()
{
}

CSyntaxRull::operator bool()
{
	return checkTokenList();
}

bool CSyntaxRull::checkOperators(const Etype& m_ePrevType, const Etype& m_eCurrType)
{
	//petqa stugvi hamatexeli en te che typer@
	return false;
}

bool CSyntaxRull::checkNeighborTokens()
{
	checkUndefined();
	switch (m_ePrevType)
	{
	case Etype::e_Identifier:
	{
		if (m_eCurrType == Etype::e_Operator)
		{
			int op1 = static_cast<int>(m_aTokenList->at(m_nPos)->m_sValue.at(0));
			if (op1 != 40)
				++m_CBracket;
			if ((m_CBracket > 0) && op1 == 41) // (5+a) ok  8-a) error
				--m_CBracket;
			return true;
		}
		std::string sMsg = m_aTokenList->at(m_nPos)->m_sValue + m_aTokenList->at(m_nPos - 1)->m_sValue;
		CSyntaxError::printError(CSyntaxError::ESyntaxError::e_UndefinedArgument, sMsg);//stex exeption petqa qcvi u exeptionum concret nshvi te vortexer syntax error@
	}
	case Etype::e_Operand:
	{

		// 4( f (4 t a+8  
		if (m_eCurrType == Etype::e_Operator)
		{
			int op1 = static_cast<int>(m_aTokenList->at(m_nPos)->m_sValue.at(0));
			if (op1 != 40)
				++m_CBracket;
			if ((m_CBracket > 0) && op1 == 41) // (5+a) ok  8-a) error
				--m_CBracket;
			return true;
		}
		std::string sMsg = m_aTokenList->at(m_nPos)->m_sValue + m_aTokenList->at(m_nPos - 1)->m_sValue;
		CSyntaxError::printError(CSyntaxError::ESyntaxError::e_IncompatibleArgument, sMsg);
	}
	case Etype::e_Operator:
	{
		// 5 - )9  4 + (9       )4  (4
		if (m_eCurrType == Etype::e_Operand || m_eCurrType == Etype::e_Identifier)
		{
			int nPrevOp = static_cast<int>(m_aTokenList->at(m_nPos - 1)->m_sValue.at(0));
			if (nPrevOp == 41) //)4
			{
				std::string sMsg = m_aTokenList->at(m_nPos)->m_sValue + m_aTokenList->at(m_nPos - 1)->m_sValue;
				CSyntaxError::printError(CSyntaxError::ESyntaxError::e_IncompatibleArgument, sMsg);
			}
			return true;
		}
		else if (m_eCurrType == Etype::e_Operator)
		{
			// (* (/ error (+ (+
			int nPrevOp = static_cast<int>(m_aTokenList->at(m_nPos - 1)->m_sValue.at(0));
			if (nPrevOp == 40)

			{
				// ( or ) next another operator
				int nCurrOp = static_cast<int>(m_aTokenList->at(m_nPos)->m_sValue.at(0));
				if (nCurrOp == 43 || nCurrOp == 45)
				{
					++m_CBracket;
					return true;
				}
			}
			else
			{	// +) error  menak +( true 
				int nCurrOp = static_cast<int>(m_aTokenList->at(m_nPos)->m_sValue.at(0));
				if (nCurrOp == 40) // (5+a) ok  8-a) error
				{
					++m_CBracket;
					return true;
				}
			}
			std::string sMsg = m_aTokenList->at(m_nPos)->m_sValue + m_aTokenList->at(m_nPos - 1)->m_sValue;
			CSyntaxError::printError(CSyntaxError::ESyntaxError::e_IncompatibleArgument, sMsg);
		}
	}
	default:
		break;
	}
}

bool CSyntaxRull::checkTokenList()
{ 
	int nCount = m_aTokenList->size();
	m_nPos = 0;
	m_ePrevType = m_aTokenList->at(m_nPos++)->m_type;
	checkFirstToken();
	for (m_nPos ; m_nPos < nCount; m_nPos)
	{
		m_eCurrType = m_aTokenList->at(m_nPos++)->m_type;
		checkNeighborTokens();
		m_ePrevType = m_eCurrType;
	}
	checkLastToken();
	checkBrakets();
	return true;
}
