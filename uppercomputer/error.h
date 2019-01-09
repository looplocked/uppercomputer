#pragma once
#ifndef ERROR_H
#define ERROR_H

#include <exception>
#include <iostream>
#include <string>

using namespace std;

class CameraException : public exception
{
public:
	CameraException() :exception("ERROR! Camera is not open!")
	{}
};

class RobotException : public exception
{
public:
	RobotException(string str="") : exception(str.c_str())
	{}
};


#endif