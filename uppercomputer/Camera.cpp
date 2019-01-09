#include "camera.h"

Camera::Camera()
{

	target.resize(4);
	init_point = cv::Point(220, 140);

#if cube
		target[0] = cv::Point(189, 108);
		target[1] = cv::Point(427, 106);
		target[2] = cv::Point(434, 348);
		target[3] = cv::Point(194, 351);
	
#else
	
		target[0] = cv::Point(201, 36);
		target[1] = cv::Point(453, 36);
		target[2] = cv::Point(453, 441);
		target[3] = cv::Point(201, 441);
#endif
	


#if 0
	ls = cv_::createLineSegmentDetector(cv_::LSD_REFINE_STD);//或者两种LSD算法，这边用的是standard的
#else
	ls = cv_::createLineSegmentDetector(cv_::LSD_REFINE_NONE);
#endif

}

Camera::~Camera()
{

}

void Camera::imageProcessThread() {

	m_capture.open(0);

	int count = 0;
	cv::Mat frame, mask, gray;
	cv::Mat backframe;

	cv::Point init_point(220, 140);

	double fps;
	string fpstext;
	string text;

	cvflann::StartStopTimer timer;
	cvflann::StartStopTimer preprocessortimer;
	cvflann::StartStopTimer lineroitimer;
	cvflann::StartStopTimer pointtimer;

	string whole_time;
	string preprocess_time;
	string line_roi_time;
	string point_process_time;

	while(true) {
		while (m_capture.grab())
		{
			timer.start();
			count++;
			m_capture >> frame;

			if (frame.cols == 0 || frame.rows == 0)
			{
				continue;
			}

			while (true)
				if (ori_mutex.try_lock()) {
					origin_img = frame;
					ori_mutex.unlock();
					break;
				}

			timer.start();
			preprocessortimer.start();
#if cube
				r = cubePreprocessor(frame);
#else
				int ix = mousePreprocessor(frame);
#endif


			preprocessortimer.stop();
			preprocess_time = "ROI extract time is " + to_string(preprocessortimer.value * 1000) + "ms";
			preprocessortimer.reset();


			lineroitimer.start();
			vector<Point> points;
#if cube
				points = lineDetection(r);
#else
				points = pointDetection(mouse_Contour_Draw);
#endif
			lineroitimer.stop();
			line_roi_time = "line selection time is " + to_string(lineroitimer.value * 1000) + "ms";
			lineroitimer.reset();

			cv::Mat drawImg = frame.clone();
			cv::Mat drawImg2 = frame.clone();
			//ls->drawSegments(drawImg, lines_std);
			//imshow("2", drawImg);

			pointtimer.start();

			points = pointExtraction(points);


			pointtimer.stop();
			point_process_time = "points selection time is " + to_string(pointtimer.value * 1000) + "ms";
			pointtimer.reset();

			while (true)
				if (point_mutex.try_lock()) {
					feature_point = flatPoints(points);
					point_mutex.unlock();
					break;
				}

			//条件滤波 暂时关闭
			//selectPoints(Points);
			//******************************

			//画图
			int font_face = cv::FONT_HERSHEY_COMPLEX;
			double font_scale = 0.5;
			int thickness = 0.2;
			for (int i = 0; i < points.size(); i++)
			{
				circle(drawImg2, points[i], 5, cv::Scalar(0, 0, 255), 2, 18);
				circle(drawImg2, target[i], 5, cv::Scalar(255, 255, 0), 2, 18);
				string text = "point" + to_string(i);
				putText(drawImg2, text, points[i], font_face, font_scale, cv::Scalar(0, 255, 255), thickness, 8, 0);
				int j = i == points.size() - 1 ? 0 : i + 1;
				line(drawImg2, points[i], points[j], cv::Scalar(255, 0, 0), 2, 8);
			}

			line(drawImg2, cv::Point(r.x, r.y), cv::Point(r.x + r.width, r.y), cv::Scalar(0, 166, 0), 2, 8);
			line(drawImg2, cv::Point(r.x + r.width, r.y), cv::Point(r.x + r.width, r.y + r.height), cv::Scalar(0, 166, 0), 2, 8);
			line(drawImg2, cv::Point(r.x + r.width, r.y + r.height), cv::Point(r.x, r.y + r.height), cv::Scalar(0, 166, 0), 2, 8);
			line(drawImg2, cv::Point(r.x, r.y + r.height), cv::Point(r.x, r.y), cv::Scalar(0, 166, 0), 2, 8);
			//**********************

			timer.stop();
			whole_time = "the whole time is " + to_string(timer.value * 1000) + "ms";
			fps = 1.0 / timer.value;
			timer.reset();

			// draw the processing speed
			fpstext = "speed: " + to_string(fps) + " fps";
			text = fpstext;
			putText(drawImg2, text, cv::Point(20, 10), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 255, 255));
			putText(drawImg2, whole_time, cv::Point(20, 25), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 255, 255));
			putText(drawImg2, preprocess_time, cv::Point(20, 40), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 255, 255));
			putText(drawImg2, line_roi_time, cv::Point(20, 55), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 255, 255));
			putText(drawImg2, point_process_time, cv::Point(20, 85), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 255, 255));

			while (true)
				if (fea_mutex.try_lock()) {
					feature_img = drawImg2;
					fea_mutex.unlock();
					break;
				}

			frame.release();
		}
	}
}

void Camera::initial()
{
	deleteLog();
	thread imgThread(&Camera::imageProcessThread, this);
	imgThread.detach();
}

cv::Mat Camera::getOriginImg()
{
	cv::Mat img;
	while (true) 
		if (ori_mutex.try_lock()) {
			img = origin_img;
			ori_mutex.unlock();
			return img;
		}
}

cv::Mat Camera::getFeatureImg()
{
	cv::Mat img;
	while (true)
		if (fea_mutex.try_lock()) {
			img = feature_img;
			fea_mutex.unlock();
			return img;
		}
}

vector<double> Camera::getFeaturePoints()
{
	vector<double> point;
	while (true)
		if (point_mutex.try_lock()) {
			point = feature_point;
			point_mutex.unlock();
			return point;
		}
}

bool Camera::isReachedI(Mat target, double threshold)
{
	Mat curFea = Mat(getFeaturePoints());
	return norm(curFea - target) < threshold;
}

Rect Camera::cubePreprocessor(Mat &frame)
{
	resize(frame, frame, cv::Size(640, 480));//输入视频调整为800*800大小
	cvtColor(frame, gray, CV_RGB2GRAY);//图像灰度化

									   //二值化
	cv::Mat img_binary = gray.clone();

	//图像处理形态学计算
	threshold(img_binary, img_binary, 235, 255, CV_THRESH_BINARY);
	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(16, 16));
	morphologyEx(img_binary, img_binary, cv::MORPH_OPEN, element);


	cv::Mat showbinary = img_binary.clone();
	cv::resize(showbinary, showbinary, cv::Size(640, 480));

	//寻找合适的联通区域
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(img_binary, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	int maxArea = 0;
	cv::Rect r1;
	CvBox2D r2;

	std::vector<cv::Rect> rects;
	std::vector<cv::Rect> rects_all;
	for (int i = 0; i < contours.size(); i++)
	{
		maxArea = contours[i].size();
		r2 = cv::minAreaRect(contours[i]);
		r1 = cv::boundingRect(contours[i]);
		rects_all.push_back(r1);
		if (r1.area() < 10000 || r1.area() > 50000)
		{
			continue;
		}
		std::cout << r1.area() << " ";

		rects.push_back(r1);
	}
	std::cout << std::endl;
	//***************************
	//
	int max_dis = 999;
	cv::Rect r(0, 0, 0, 0);
	cv::Point P1, P2;
	P1.x = frame.cols*0.5;
	P1.y = frame.rows*0.5;

	for (int i = 0; i < rects.size(); i++)
	{
		P2.x = rects[i].x + 0.5*rects[i].width;
		P2.y = rects[i].y + 0.5*rects[i].height;

		double distance;
		distance = powf((P1.x - P2.x), 2) + powf((P1.y - P2.y), 2);
		distance = sqrtf(distance);

		if (distance < max_dis)
		{
			max_dis = distance;
			r = rects[i];
		}
	}

	int max_all = 0;
	if (r.area() == 0)
	{
		for (int i = 0; i < rects_all.size(); i++)
		{
			if (rects_all[i].area() > max_all)
			{
				max_all = rects_all[i].area();
				r = rects_all[i];
			}
		}
	}
	if (r.area() == 0)
	{
		r = cv::Rect(0, 0, 639, 479);
	}
	else
	{
		r.x = r.x >= 10 ? r.x - 10 : 0;
		r.y = r.y >= 10 ? r.y - 10 : 0;
		r.width = r.x + r.width <= 620 ? r.width + 20 : 640 - r.x;
		r.height = r.y + r.height <= 460 ? r.height + 20 : 460 - r.y;
	}
	return r;
}

int Camera::mousePreprocessor(Mat& srcImage)
{
	vector<Mat> ch;
	split(srcImage, ch);


	Mat grayImage, out_Canny;
	grayImage = ch[1];
	//cvtColor(srcImage, grayImage, CV_BGR2GRAY);

	//blur(grayImage, grayImage, Size(3, 3));
	//boxFilter(grayImage, grayImage, -1, Size(3, 3));
	GaussianBlur(grayImage, grayImage, Size(5, 5), 0, 0);

	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(grayImage, grayImage, element);
	erode(grayImage, grayImage, element);


	adaptiveThreshold(grayImage, grayImage, 120, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, 3);

	Canny(grayImage, out_Canny, 70, 240, 3);

	findContours(out_Canny, Contours, Hierarchy, CV_RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	/*画出所有轮廓*/
	mouse_Contour_Draw = Mat::zeros(out_Canny.size(), CV_8UC1);


	for (int i = 0; i < Contours.size(); i++)
	{
		drawContours(mouse_Contour_Draw, Contours, i, Scalar(255), 3, 8, Hierarchy, 0, Point());
	}


	if (Contours.size() > 40) return -1;



	return 1;
}

vector<Point> Camera::lineDetection(Rect& r)
{
	lines_std.reserve(1000);
	ls->detect(gray(r), lines_std);//这里把检测到的直线线段都存入了lines_std中，4个float的值，分别为起止点的坐标
	findPrimaryAngle(lines_std);

	std::vector<cv::Point> Points;
	for (int i = 0; i < lines_std.size(); i++)
	{
		cv::Point p1, p2;
		p1 = cv::Point(lines_std[i][0] + r.x, lines_std[i][1] + r.y);
		p2 = cv::Point(lines_std[i][2] + r.x, lines_std[i][3] + r.y);

		Points.push_back(p1);
		Points.push_back(p2);
	}

	return Points;
}

vector<Point> Camera::pointDetection(Mat &mouse_Contourimg)
{
	vector<Point> key, tempkey;
	RotatedRect box; //定义最小外接矩形
	Rect boundRect;  //用于存储外接矩形
	boundRect = boundingRect(mouse_Contourimg);

	rectangle(mouse_Contourimg, boundRect, Scalar(255, 0, 0), 2, 8);

	//最小外接矩形，是紧紧挨着轮廓的，可能有倾斜
	vector<Point> contourPoint;
	for (int i = 0; i < Contours.size(); i++)
	{
		contourPoint.insert(contourPoint.end(), Contours[i].begin(), Contours[i].end());
	}

	if (!contourPoint.empty())
		box = minAreaRect(contourPoint);

	Point2f* vertices = new cv::Point2f[4];
	box.points(vertices);

	//绘制box矩形
	for (int j = 0; j < 4; j++)
	{
		line(mouse_Contourimg, vertices[j], vertices[(j + 1) % 4], cv::Scalar(0, 255, 0));
		key.push_back(vertices[j]);
	}

	return key;
}

vector<Point> Camera::pointExtraction(vector<Point>& Points)
{

	enableClockWise(Points);

	if (Points.size() == 4) {
		int index = 0;
		double mindist = 1000;
		for (int i = 0; i < 4; i++) {
			double d = norm(init_point - Points[i]);
			if (d < mindist) {
				index = i;
				mindist = d;
			}
		}

		transPoints(Points, 4 - index);

		init_point = Points[0];
	}
	return Points;
}


Point Camera::getPointAffinedPos(const Point &src, const Point center, double angle)
{
	Point dst;
	int x = src.x - center.x;
	int y = src.y - center.y;

	dst.x = cvRound(x * cos(angle) + y * sin(angle) + center.x);
	dst.y = cvRound(-x * sin(angle) + y * cos(angle) + center.y);
	return dst;
}

vector<Point> Camera::findkeypoint(Mat image)
{
	bool flag = 0;
	vector<Point> tempkeypoint, keypoint;
	int temp = 0;

	//从右往左，从上往下 扫描
	for (int i = 0; i < image.rows; i++)
	{
		uchar *data = image.ptr<uchar>(i);
		for (int j = image.cols - 1; j>image.cols / 2; j--)      //这里55，可能不是最优值，好一点方法应该是按照入口参数image的尺寸比例来算
		{
			if (data[j] == 255 && j>image.cols / 2)
			{
				tempkeypoint.push_back(Point(j, i));
				flag = 1;
			}
		}
		if (flag) break;
	}

	if (tempkeypoint.size() == 0) return keypoint;
	for (int i = 0; i < tempkeypoint.size(); i++) temp += tempkeypoint[i].x;//没有考虑upkeypoint没有元素的情况
	keypoint.push_back(Point(temp / tempkeypoint.size(), tempkeypoint[0].y));
	tempkeypoint.clear();
	temp = 0;
	flag = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//从右往左，从下往上扫描
	for (int i = image.rows - 1; i>0; i--)
	{
		uchar *data = image.ptr<uchar>(i);
		for (int j = image.cols - 1; j>image.cols / 2; j--)
		{
			if (data[j] == 255 && j>image.cols / 2)                          //if (data[j] == 255 && j>55) 这里55，可能不是最优值，好一点方法应该是按照入口参数image的尺寸比例来算
			{
				tempkeypoint.push_back(Point(j, i));
				flag = 1;
			}
		}
		if (flag) break;
	}

	if (tempkeypoint.size() == 0) return keypoint;
	for (int i = 0; i < tempkeypoint.size(); i++) temp += tempkeypoint[i].x;//没有考虑upkeypoint没有元素的情况
	keypoint.push_back(Point(temp / tempkeypoint.size(), tempkeypoint[0].y));
	tempkeypoint.clear();
	temp = 0;
	flag = 0;

	//cout << keypoint << endl;
	//////////////////////////////////////////////////////////////////////

	//分割logitech这几个字的轮廓，如果扫描到这几个字轮廓的最左边一列，且这一列都为黑色的，则停止扫描
	int j;
	for (int i = keypoint[0].x; i>0; i--) //列
	{
		for (j = keypoint[0].y; j <image.rows; j++) // 行
		{
			uchar *data = image.ptr<uchar>(j);
			if (data[i] == 255) break;;
		}
		if (j == image.rows)
		{
			tempkeypoint.push_back(Point(i, j - 1));
			break;
		}
	}

	if (tempkeypoint.size() == 0) return keypoint;
	//cout << tempkeypoint << endl;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool witheflag = false;                   //由下往上，由右往左扫描，依据鼠标滚轮处（有一个圈），由黑到白，再到白，再到黑的过程
	bool blackflag = false;
	int i = tempkeypoint[0].x;
	tempkeypoint.clear();
	for (; i > 0; i--) //列
	{
		for (int j = image.rows - 1; j >0; j--) // 行
		{
			uchar *data = image.ptr<uchar>(j);
			if (data[i] == 255)
				witheflag = true;
			if (witheflag && (data[i] == 0) && (i<image.cols / 3))
			{
				tempkeypoint.push_back(Point(i, j));
				blackflag = true;
			}
			if (blackflag && (data[i] == 255)) {
				flag = true; break;
			}
		}
		if (flag) break;
		blackflag = false; witheflag = false;
		tempkeypoint.clear();
	}

	if (tempkeypoint.size() == 0) return keypoint;
	for (int i = 0; i < tempkeypoint.size(); i++) temp += tempkeypoint[i].y;//没有考虑upkeypoint没有元素的情况
	keypoint.push_back(Point(tempkeypoint[0].x, temp / tempkeypoint.size()));
	tempkeypoint.clear();
	temp = 0;
	flag = 0;
	/////////////////////////////////////////////////////////////////////


	for (int j = keypoint[2].x; j >0; j--) // 列
	{
		uchar *data = image.ptr<uchar>(keypoint[2].y);
		if ((data[j] == 255) && (j<image.cols / 5)) {
			keypoint.push_back(Point(j, keypoint[2].y));
			break;
		};
	}

	return keypoint;
}

bool Camera::needReverse(cv::Vec4f line1, cv::Vec4f line2)
{
	cv::Point2f ptr1(line1[2] - line1[0], line1[3] - line1[1]);
	cv::Point2f ptr2(line2[2] - line2[0], line2[3] - line2[1]);
	double con = ptr1.x * ptr2.x + ptr1.y * ptr2.y;
	return con > 0;
}

void Camera::enableClockWise(std::vector<cv::Point>& Points)
{
	if (Points.size() < 3) return;
	cv::Point vec1(Points[1].x - Points[0].x, Points[1].y - Points[0].y);
	cv::Point vec2(Points[2].x - Points[1].x, Points[2].y - Points[1].y);
	if (vec1.x * vec2.y - vec1.y * vec2.x < 0) {
		cv::Point temp(Points[1].x, Points[1].y);
		Points[1] = Points[3];
		Points[3] = temp;
	}
}

void Camera::transPoints(std::vector<cv::Point>& Points, int k)
{
	k = k % Points.size();
	reverse(begin(Points), begin(Points) + Points.size() - k);
	reverse(begin(Points) + Points.size() - k, Points.end());
	reverse(begin(Points), end(Points));
}

vector<double> Camera::flatPoints(vector<cv::Point>& points) {
	vector<double> feature;
	feature.resize(points.size() * 2);
	for (int i = 0; i < points.size(); i++) {
		feature[i * 2] = static_cast<double>(points[i].x);
		feature[i * 2 + 1] = static_cast<double>(points[i].y);
	}
	return feature;
}

bool Camera::findPrimaryAngle(std::vector<cv::Vec4f>& lines)
{
	if (lines.empty())
	{
		return false;
	}

	int linenum = lines.size();

	std::vector<cv::Vec4f> linsNew;

	int count = 0;
	sortType distlist;
	for (auto i : lines)
	{
		double dist = norm(cv::Point(i[0], i[1]) - cv::Point(i[2], i[3]));
		distlist.push_back(std::pair<double, int>(dist, count++));
	}

	//-----------------------------------------------
	int top_nun = 2;//获取最长直线的个数
	SortFaster(distlist, top_nun);

	int length = MIN(distlist.size(), top_nun);

	int mean_lenth = 0;
	for (int i = 0; i < length; i++)
	{
		//linsNew.push_back(lines[distlist[i].second]);
		mean_lenth += distlist[i].first;
	}

	mean_lenth /= length;

	std::cout << "m:  " << mean_lenth << std::endl;

	for (int i = 0; i < linenum; i++)
	{
		if (distlist[i].first>0.8*mean_lenth)
		{
			linsNew.push_back(lines[distlist[i].second]);
		}
	}

	if (linsNew.size() <= 1)
	{
		lines.clear();
		lines = linsNew;
		return true;
	}
	else if (linsNew.size() == 2) {
		if (needReverse(linsNew[0], linsNew[1])) {
			cv::Vec4f temp(linsNew[1][2], linsNew[1][3], linsNew[1][0], linsNew[1][1]);
			linsNew[1] = temp;
		}
		lines.clear();
		lines = linsNew;
		return true;
	}

	double min_angle = 1000000;

	int pos1 = 0, pos2 = 2;

	for (int i = 0; i < linsNew.size() - 1; i++)
	{
		double angle = double(linsNew[i][1] - linsNew[i][3]) / double(linsNew[i][0] - linsNew[i][2]);
		angle = abs(angle);

		for (int j = i + 1; j < linsNew.size(); j++)
		{
			double angle2 = double(linsNew[j][1] - linsNew[j][3]) / double(linsNew[j][0] - linsNew[j][2]);
			angle2 = abs(angle2);

			double dist = abs(angle2 - angle);
			double x1 = (linsNew[i][0] + linsNew[i][2]) / 2;
			double y1 = (linsNew[i][1] + linsNew[i][3]) / 2;
			double x2 = (linsNew[j][0] + linsNew[j][2]) / 2;
			double y2 = (linsNew[j][1] + linsNew[j][3]) / 2;
			double linesDis = norm(cv::Point(x1, y1) - cv::Point(x2, y2));

			if (dist < min_angle && linesDis > 0.1*mean_lenth) //平行且不重合的两条线
			{
				min_angle = dist;
				pos1 = i;
				pos2 = j;
			}
		}
	}

	if (needReverse(linsNew[pos1], linsNew[pos2])) {
		cv::Vec4f temp(linsNew[pos2][2], linsNew[pos2][3], linsNew[pos2][0], linsNew[pos2][1]);
		linsNew[pos2] = temp;
	}


	lines.clear();
	lines.push_back(linsNew[pos1]);
	lines.push_back(linsNew[pos2]);

	return true;
}

bool Camera::selectPoints(std::vector<cv::Point>& Points)
{
	std::vector<int> dels;
	std::vector<cv::Point> Points_out;
	for (int i = 0; i < Points.size() / 2 - 1; i++)
	{
		bool isF = true, isS = true;

		for (int k = 0; k < dels.size(); k++)
		{
			if (2 * i == dels[k])
			{
				isF = false;
			}

			if (2 * i + 1 == dels[k])
			{
				isS = false;
			}
		}

		for (int j = 2 * i + 2; j < Points.size(); j++)
		{
			if (isF)
			{
				double dist1 = norm(Points[i * 2] - Points[j]);

				if (dist1<50)
				{
					double l1 = norm(Points[i * 2] - Points[i * 2 + 1]);
					double l2;
					if (j % 2 == 0)
					{
						l2 = norm(Points[j] - Points[j + 1]);
					}
					else
					{
						l2 = norm(Points[j] - Points[j - 1]);
					}

					if (l1 >= l2)
					{
						Points_out.push_back(Points[i * 2]);
						dels.push_back(j);
					}
				}
				else
				{
					Points_out.push_back(Points[i * 2]);
				}

			}

			if (isS)
			{
				double dist2 = norm(Points[i * 2 + 1] - Points[j]);

				if (dist2 < 50)
				{
					double l1 = norm(Points[i * 2] - Points[i * 2 + 1]);
					double l2;
					if (j % 2 == 0)
					{
						l2 = norm(Points[j] - Points[j + 1]);
					}
					else
					{
						l2 = norm(Points[j] - Points[j - 1]);
					}

					if (l1 >= l2)
					{
						Points_out.push_back(Points[i * 2 + 1]);
						dels.push_back(j);
					}
				}
				else
				{
					Points_out.push_back(Points[i * 2 + 1]);
				}
			}
		}
	}
	Points = Points_out;

	return true;
}

cv::Mat Camera::mirrorMap(cv::Mat srcimg)
{
	cv::Mat originimg, map_x, map_y;
	originimg.create(srcimg.size(), srcimg.type());
	map_x.create(srcimg.size(), CV_32FC1);
	map_y.create(srcimg.size(), CV_32FC1);

	for (int j = 0; j < srcimg.rows; j++)
	{
		for (int i = 0; i < srcimg.cols; i++)
		{
			map_x.at<float>(j, i) = static_cast<float>(srcimg.cols - i);
			map_y.at<float>(j, i) = static_cast<float>(j);
		}
	}

	remap(srcimg, originimg, map_x, map_y, cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(0, 0, 0));

	return originimg;
}

bool Camera::SortFaster(sortType& dists, int Top_num)
{
	if (dists.size() < Top_num || Top_num == 0)
	{
		return false;
	}

	int length_dists = dists.size();

	int num = 0;

	while (num<Top_num)
	{
		for (int i = length_dists - 1; i > num; i--)
		{
			if (dists[i].first > dists[i - 1].first)
			{
				std::pair<double, int> temp;
				temp = dists[i];
				dists[i] = dists[i - 1];
				dists[i - 1] = temp;
			}
		}
		num++;
	}

	return true;
}

void Camera::printLog(string log) {
	ofstream fout;
	SYSTEMTIME sys;
	::GetLocalTime(&sys);

	fout.open("log.txt", ios_base::in | ios_base::app);
	fout << "[" << sys.wHour << ":" << sys.wMinute << ":" << sys.wSecond << "." << sys.wMilliseconds << "]\t" << log << endl;
	fout.close();
}

void Camera::deleteLog() {
	ofstream fout;
	fout.open("log.txt", ofstream::out | ofstream::trunc);
	fout.close();
}