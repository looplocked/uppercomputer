#pragma once
#ifndef ERROR_H
#define ERROR_H

#include <exception>
#include <iostream>

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
	RobotException() : exception("ERROR! Robot is not connected!")
	{}
};


#endif