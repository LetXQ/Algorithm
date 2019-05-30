/*
 * autho: leo
 * date: 2019-05-30
 *
 * Description:
 * transfer string data to definited precision
 * eg: all data divides by 100
 * 123  		-> 		1.23
 * 123.0 		->		1.230
 * 123.00		->		1.2300
 * 
 */

#pragma once

#include <cstring>
#include <strstream>
#include <iomanip>

template<class T>
T StringToType(const string &str)
{
	T val;
	strstream ss;
	ss << str;
	ss >> val;
	return val;
}

template<class T>
void ConvertToString(const T &val, int inum, string &r_str)
{
	strstream ss;
	ss << std::fixed << std::setprecision(inum) << val;
	ss >> r_str;
}

size_t GetOriginStrPrecision(const string &str)
{
	int num = 0;
	size_t fpos = str.find('.');
	if (std::string::npos == fpos) {
		return 0;
	}
	else {
		return str.length() - fpos - 1;
	}
}

int GetDecimalExponent(unsigned int val)
{
	int tmp = 1, exp = 0;
	
	while(1) {
		if (tmp == val) {
			return exp;
		}
		else if (tmp > val) {
			return 0;
		}
		else {
			++exp;
			tmp *= 10;
		}
	}
	return 0;
}

void GetStringOfPrecision(const string &str, string &r_str, int i_div = 100)
{
	if (str.empty())
		return;
	
	int i_dec_exp = i_div> 0 ? GetDecimalExponent(i_div) : 0;
	int i_precision = GetOriginStrPrecision(str) + i_dec_exp;
	std::cout << "i_dec_exp: " << i_dec_exp << ", i_precision: " << i_precision << std::endl; 

	ConvertToString(StringToType<double>(str), i_precision, r_str);
}

void TestGetStringOfPrecision()
{
	string tmp;
	GetStringOfPrecision("100", tmp);
	std::cout << "100: " << tmp << std::endl;
	
	GetStringOfPrecision("20.0", tmp);
	std::cout << "20.0: " << tmp << std::endl;

	GetStringOfPrecision("1.123", tmp);
	std::cout << "1.123: " << tmp << std::endl;
	
	GetStringOfPrecision("0.002", tmp);
	std::cout << "0.002: " << tmp << std::endl;
}