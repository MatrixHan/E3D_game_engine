#pragma once

#include "ECommon.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdarg.h>
#include <Windows.h>
#include <ctime>

namespace E3D
{
	extern std::ofstream *GLogStream;

	bool InitLog(const EString &fileName);

	void Log(const EChar *string ,...);

	void CloseLog();

	inline EString IntToString(EFloat num)
	{
		std::stringstream ss;
		ss << num;
		EString re;
		ss >> re;
		return re;
	}

	inline EInt RandomInt(EInt from = 0, EInt to = 10)
	{
		EInt ran = rand() % (to - from + 1) + from;
		return ran;
	}

	inline EInt StringToInt(const EString &str)
	{
		return atoi(str.c_str());
	}

	inline EFloat StringToFloat(const EString &str)
	{
		return (EFloat)atof(str.c_str());
	}

	inline EWString ToEWString(const EString &str)
	{
		int wcsLen = ::MultiByteToWideChar(CP_ACP,NULL,str.c_str(),str.size(),NULL,0);
		WCHAR *tString = new WCHAR[wcsLen + 1];
		::MultiByteToWideChar(CP_ACP,NULL,str.c_str(),str.size(),tString,wcsLen);
		tString[wcsLen] = '\0';
		return EWString(tString);
	}

	inline EBool EqualFloat(EFloat l ,EFloat r)
	{
		return abs(l-r)<=EPSILON_E6;
	}

	inline EString GetNameFromPath(const EString &path)
	{
		std::size_t beg = path.find_last_of("\\/");
		std::size_t end = path.find_last_of(".");
		if (beg == EString::npos)
		{
			beg = -1;
		}
		return path.substr(beg+1,end - beg - 1);
	}
	//È¥³ý\t\f\v\n\r ÕâÐ©·ûºÅ
	inline EString Trim(const EString &msg)
	{
		const static EString SPACE_CHAR = " \t\f\v\n\r";
		std::size_t beg = msg.find_first_not_of(SPACE_CHAR);

		if (beg > msg.length())
		{
			return EString();
		}
		EString result = msg.substr(beg);
		
		std::size_t end = result.find_last_not_of(SPACE_CHAR);
		if (end != EString::npos)
			end++;
		return result.substr(0, end);
	}
}