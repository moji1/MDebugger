/*
 * ParsingUtil.hh
 *
 *  Created on: Nov 12, 2016
 *      Author: mojtababagherzadeh
 */

#ifndef PARSINGUTIL_H_
#define PARSINGUTIL_H_
#include <stack>
#include <iostream>

namespace Util{
	inline std::string intToStr(int input){
		std::stringstream ss;
		ss << input;
		return ss.str();
	}
	inline std::string boolToStr(bool input){
		std::stringstream ss;
		ss << input;
		return ss.str();
	}
	inline std::string charToStr(char input){
		std::stringstream ss;
		ss << input;
		return ss.str();
	}
	inline std::vector<std::string> parseQoutedSeperatedString(std::string buffer,char seperator){
		std::vector<std::string> result;
		std::stack<char> tempStack;
		std::string tempString;
		for (int i=0;i<buffer.length();i++){
			if (buffer[i]=='\"')
				if (tempStack.empty())
					tempStack.push('\"');
				else if (buffer[i+1]== seperator)
					tempStack.pop();
		}
		return result;
	}

	inline std::vector<std::string> split(std::string buffer,char seperator){
		std::string tempS="";
		std::vector<std::string> tempVector;
		bool newVar=false;
		for (int i=0;i< buffer.length();i++){
				if ((buffer[i]==seperator) && newVar){
					newVar=false;
					tempVector.push_back(tempS);
					tempS="";
				}
				else if (buffer[i]!=seperator){
					tempS=tempS+(buffer[i]);
					newVar=true;
				}
			}
		if (newVar)
			tempVector.push_back(tempS);
		return tempVector;
	}
}



#endif /* PARSINGUTIL_H_ */
