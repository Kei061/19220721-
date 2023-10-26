#pragma once
#include "Configure.h"

using uint32 = unsigned int;
class Student
{
public:
	Student();
	Student(uint32 number, const std::string& name, const std::string& grade, uint32 math, uint32 chinese, uint32 english);
	std::string formatInfo();	//格式化数据
	static Student fromString(const std::string& str);
public:
	//id name grade Math Chinese English
	uint32 number;
	std::string name;
	std::string grade;
	uint32 math;
	uint32 chinese;
	uint32 english;
};