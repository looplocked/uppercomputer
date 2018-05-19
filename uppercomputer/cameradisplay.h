#ifndef CAMERADISPLAY_H    //Ԥ����ͷ����Ҫ
#define CAMERADISPLAY_H    //���ӻ����ʧ��


#include <stdlib.h>  
#include <iostream>  
#include <string>  
#include "OpenNI.h"  
#include "opencv2/core/core.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp"  
#include "error.h"

using namespace std;
using namespace cv;
using namespace openni;

//Device deviceparam;
//VideoStream oniColorStreamparam;

//void CheckOpenNIError(Status result, string status)
//{
//	if (result != STATUS_OK)
//		cerr << status << " Error: " << OpenNI::getExtendedError() << endl;
//}

class CameraDisplay
{
public:
	CameraDisplay();
	~CameraDisplay();
	void initialize(Device& device, VideoStream& oniColorStream);
	Mat getImage(VideoStream& oniColorStream);
	void close(Device& device, VideoStream& oniColorStream);
//private:
//	static Device deviceparam;
//	static VideoStream oniColorStreamparam;
};

#endif
