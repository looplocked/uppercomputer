#include "cameradisplay.h"

CameraDisplay::CameraDisplay()
{

}

CameraDisplay::~CameraDisplay()
{

}

void CameraDisplay::initialize(Device& device, VideoStream& oniColorStream)
{
	Status result = STATUS_OK;

	result = OpenNI::initialize();
	//CheckOpenNIError(result, "initialize context");
  
	//Device device;
	result = device.open(openni::ANY_DEVICE);
	
	if (result != STATUS_OK)
		throw CameraException();
 
	//VideoStream oniColorStream;
	result = oniColorStream.create(device, openni::SENSOR_COLOR);
	VideoMode modeColor;
	modeColor.setResolution(640, 480);
	modeColor.setFps(30);
	modeColor.setPixelFormat(PIXEL_FORMAT_RGB888);
	oniColorStream.setVideoMode(modeColor);

	if (device.isImageRegistrationModeSupported(IMAGE_REGISTRATION_DEPTH_TO_COLOR))
	{
		device.setImageRegistrationMode(IMAGE_REGISTRATION_DEPTH_TO_COLOR);
	}
	// start color stream  
	result = oniColorStream.start();

}

Mat CameraDisplay::getImage(VideoStream& oniColorStream)
{
	//OpenNI2 image  
	VideoFrameRef oniColorImg;
	//OpenCV image  
	//cv::Mat cvBGRImg;
	if (oniColorStream.readFrame(&oniColorImg) == STATUS_OK)
	{
		// convert data into OpenCV type  
		cv::Mat cvRGBImg(oniColorImg.getHeight(), oniColorImg.getWidth(), CV_8UC3, (void*)oniColorImg.getData());    // 将openni图片转换为opencv图片
		//cv::cvtColor(cvRGBImg, cvBGRImg, CV_RGB2BGR);  // 将RGB转换为BGR
		//imshow("src", cvBGRImg);
		return cvRGBImg;
	}
	else
		throw CameraException();
}

void CameraDisplay::close(Device& device, VideoStream& oniColorStream)
{
	//OpenNI2 destroy  
	oniColorStream.destroy();
	device.close();
	OpenNI::shutdown();
}
	