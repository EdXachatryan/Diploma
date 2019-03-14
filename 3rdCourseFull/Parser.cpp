#include "Parser.h"
#include <algorithm>
#include "SyntaxRull.h"

CTokenizer::CTokenizer(  std::string& str) : m_nPos(0)
{	 
	m_sText = str;
}

bool CTokenizer::isDelim(char ch) const
{
	return static_cast<EOperator>(ch);// should check
}

void CTokenizer::splitToTokens(std::vector<SToken*>& tokens)
{
	//auto isSameType  = [](Etype a, Etype b) { return a == b; };
	deleteSpace();
	string temp;
	Etype tempType = e_Undefined;
	Etype m_eCurrTypeype;

	while (m_nPos!=m_sText.size()) // or size -1 last character is /0 or not ??????????
	{
		// ad + 45 -l*(i-dddd+459)
		char ch = m_sText.at(m_nPos);
		if (isNumber(ch))
		{
			m_eCurrTypeype = Etype::e_Operand;
			(m_nPos == 0) ? tempType = m_eCurrTypeype : tempType;
			bool bSameType = (tempType == m_eCurrTypeype) ? true : false;
			if (bSameType)
			{
				temp.push_back(ch);
				tempType = m_eCurrTypeype;
			}
			else
			{
				switch (tempType)
				{
				case Etype::e_Operator:
				{
					SToken *pTok = new SToken{ tempType ,temp };
					tokens.push_back(pTok);
					break;
				};
				case Etype::e_Identifier:
				{
					SToken *pTok = new SToken{ tempType, temp };
					tokens.push_back(pTok);
					break;
				};
				}
				temp.clear();
				temp.push_back(ch);
				m_eCurrTypeype = Etype::e_Operand;
				tempType = m_eCurrTypeype;
			}
		}
		else if (isOperator(ch))
		{
			switch (tempType)
			{
			case Etype::e_Operand:
				{
					SToken *pTok = new SToken{ tempType ,temp};
					tokens.push_back(pTok);
					break;
				};
			case Etype::e_Identifier:
				{
					SToken *pTok = new SToken{ tempType, temp };
					tokens.push_back(pTok);
					break;
				};
			}
			temp.clear();
			temp.push_back(ch);
			m_eCurrTypeype = Etype::e_Operator;
			tempType = m_eCurrTypeype;
		}
		else if (isIdentifer(ch))
		{
			m_eCurrTypeype = Etype::e_Identifier;
			(m_nPos == 0) ? tempType = m_eCurrTypeype : tempType;
			bool bSameType = (tempType == m_eCurrTypeype) ? true : false;
			if (bSameType)
			{
				temp.push_back(ch);
				tempType = m_eCurrTypeype;
			}
			else
			{
				switch (tempType)
				{
					case Etype::e_Operand:
					{
						SToken *pTok = new SToken{ tempType ,temp };
						tokens.push_back(pTok);
						break;
					};
					case Etype::e_Operator:
					{
						SToken *pTok = new SToken{ tempType, temp };
						tokens.push_back(pTok);
						break;
					};
				}
				temp.clear();
				temp.push_back(ch);
				m_eCurrTypeype = Etype::e_Identifier;
				tempType = m_eCurrTypeype;
			}
		}
		else
		{
			m_eCurrTypeype = Etype::e_Undefined;
			(m_nPos == 0) ? tempType = m_eCurrTypeype : tempType;
			bool bSameType = (tempType == m_eCurrTypeype) ? true : false;
			if (bSameType)
			{
				temp.push_back(ch);
				tempType = m_eCurrTypeype;
			}
			else
			{
				switch (tempType)
				{
					case Etype::e_Operand:
					{
						SToken *pTok = new SToken{ tempType ,temp };
						tokens.push_back(pTok);
						break;
					};
					case Etype::e_Operator:
					{
						SToken *pTok = new SToken{ tempType, temp };
						tokens.push_back(pTok);
						break;
					};
					case Etype::e_Identifier:
					{
						SToken *pTok = new SToken{ tempType, temp };
						tokens.push_back(pTok);
						break;
					};
				}
				temp.clear();
				temp.push_back(ch);
				m_eCurrTypeype = Etype::e_Undefined;
				tempType = m_eCurrTypeype;
			}
		}
		++m_nPos;// ete es chgrei avtomat ++ chi anum u anverj cikl kli vortev araj chi gna position
	}
	SToken *pTok = new SToken{ tempType, temp }; // last Token
	tokens.push_back(pTok);
}

bool CTokenizer::isOperator(char ch)
{
	return static_cast<EOperator> (ch); // ba vor sxal character ekac lini incha return anelu ?
}

bool CTokenizer::isIdentifer(char ch)
{
	if (isalpha(ch))   //sranqel petqa inline linen vortev ham karchen hamel sjat en kanchvelu.bayc porcenq mi hat senq heto inline u tarberutyun@ real tesnenq
		return true;
	return false;
}

inline void CTokenizer::deleteSpace()
{
	m_sText.erase(std::remove_if(m_sText.begin(), m_sText.end(), isspace), m_sText.end());
	//another way loop from string and create new string without space 
}

//inline int CTokenizer::getCount() const
//{
//	return m_aTokenList.size();
//}

CParser::CParser(std::string str)
{
	m_pSyntRul = new CSyntaxRull;
	m_Tokenizer = new CTokenizer(str);
	parse();
}

CParser::~CParser()
{
	delete m_pSyntRul;
	delete m_Tokenizer;//poxi smart pointer ogtagorci!!!!!!!!!!!!!!!!!!!!!!!!
	m_pSyntRul = 0;
	m_Tokenizer = 0;
}

bool CParser::checkSyntaxis()
{
	if (m_pSyntRul)
	{
		m_pSyntRul->setTokens(m_aTokenList);
		return m_pSyntRul->checkTokenList();
	}
	return false;
}

void CParser::parse()
{
	m_Tokenizer->splitToTokens(m_aTokenList);
	checkSyntaxis();
}
