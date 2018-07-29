#pragma once
#ifndef HELPER_H
#define HELPER_H

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "opencv2/core/core.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp"
#include "OpenNI.h" 


using namespace std;
using namespace cv;


void printLog(string log);
void deleteLog();

#endif