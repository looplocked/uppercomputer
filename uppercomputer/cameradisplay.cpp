#include "cameradisplay.h"

CameraDisplay::CameraDisplay()
{
	device = new Device();
	oniColorStream = new VideoStream();
}

CameraDisplay::~CameraDisplay()
{
	oniColorStream->destroy();
	device->close();
	OpenNI::shutdown();
}

void CameraDisplay::initialize()
{
	Status result = STATUS_OK;

	result = OpenNI::initialize();
	//CheckOpenNIError(result, "initialize context");
  
	//Device device;
	result = device->open(openni::ANY_DEVICE);
	
	if (result != STATUS_OK)
		throw CameraException();
 
	//VideoStream oniColorStream;
	result = oniColorStream->create(*device, openni::SENSOR_COLOR);
	VideoMode modeColor;
	modeColor.setResolution(640, 480);
	modeColor.setFps(30);
	modeColor.setPixelFormat(PIXEL_FORMAT_RGB888);
	oniColorStream->setVideoMode(modeColor);

	if (device->isImageRegistrationModeSupported(IMAGE_REGISTRATION_DEPTH_TO_COLOR))
	{
		device->setImageRegistrationMode(IMAGE_REGISTRATION_DEPTH_TO_COLOR);
	}
	// start color stream  
	result = oniColorStream->start();

}

vector<Mat> CameraDisplay::getImageAndFeature(vector<Point>& points)
{
	//OpenNI2 image  
	VideoFrameRef oniColorImg;
	//OpenCV image  
	//cv::Mat cvBGRImg;
	if (oniColorStream->readFrame(&oniColorImg) == STATUS_OK)
	{
		// convert data into OpenCV type  
		cv::Mat cvRGBImg(oniColorImg.getHeight(), oniColorImg.getWidth(), CV_8UC3, (void*)oniColorImg.getData());    // 将openni图片转换为opencv图片
		//cv::cvtColor(cvRGBImg, cvBGRImg, CV_RGB2BGR);  // 将RGB转换为BGR
		//imshow("src", cvBGRImg);

		vector<Mat> res;
		Mat originimg = mirrorMap(cvRGBImg);
		res.push_back(originimg);

		Mat drawImg2 = processAndGetFeature(originimg, points);

		res.push_back(drawImg2);
		return res;
	}
	else
		throw CameraException();
}

	