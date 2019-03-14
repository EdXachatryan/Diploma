#include <iostream>
#include <fstream>
#include <string>
#include "Parser.h"
int main(int argc, char** argv)
{
	/*std::string str;
	std::ifstream inFile("file1.txt");
	if (inFile.is_open())
	{
		std::getline(inFile, str);

	}
*/
	//enum EOOO :char {

	//	plus = '+',
	//	minus = '-',
	//	mul = '*',
	//	both = plus + minus
	//	
	//};
	//int g = EOOO::both;

	//EOOO a = EOOO::plus; //ascii codov porcenq 
	//EOOO c = EOOO::minus ;
	////EOOO cc = c + a;
	//int bbbbbb = static_cast<int>(EOOO::plus);
	//char ch = '+';
	//std::string str;
	//str.push_back(ch);

	//int ccsad = a;
	//int sd = static_cast<EOOO>(str.at(0));
	//EOOO cc = static_cast<EOOO>(str.at(0));

	//char ch1 = '^';
	//std::string str1;
	//str1.push_back(ch1);
	//EOOO cc1 = static_cast<EOOO>(str1.at(0));






	std::string sExpr = "4)+9*6";
	CParser oPaser(sExpr);

	system("pause");
	return 0;
}