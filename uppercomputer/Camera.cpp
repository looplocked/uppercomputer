#include "camera.h"

Camera::Camera()
{
	init_point = cv::Point(220, 140);
}

Camera::~Camera()
{

}

void Camera::imageProcessThread() {

	m_capture.open(0);

	cv::Ptr<cv_::LineSegmentDetector> ls;
#if 0
	ls = cv_::createLineSegmentDetector(cv_::LSD_REFINE_STD);//或者两种LSD算法，这边用的是standard的
#else
	ls = cv_::createLineSegmentDetector(cv_::LSD_REFINE_NONE);
#endif

	int count = 0;
	cv::Mat frame, mask, gray;
	cv::Mat backframe;

	cv::Point init_point(220, 140);

	double fps;
	string fpstext;
	string text;

	cvflann::StartStopTimer timer;
	cvflann::StartStopTimer roitimer;
	cvflann::StartStopTimer linedetectiontimer;
	cvflann::StartStopTimer lineselectiontimer;
	cvflann::StartStopTimer pointtimer;

	string whole_time;
	string roi_process_time;
	string line_detect_time;
	string line_select_time;
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
			printLog("original image stored successfully!");

			timer.start();
			roitimer.start();
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

			//感兴趣区域扩展
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
			roitimer.stop();
			roi_process_time = "ROI extract time is " + to_string(roitimer.value * 1000) + "ms";
			roitimer.reset();

			linedetectiontimer.start();
			std::vector<cv::Vec4f> lines_std;
			lines_std.reserve(1000);
			ls->detect(gray(r), lines_std);//这里把检测到的直线线段都存入了lines_std中，4个float的值，分别为起止点的坐标
			linedetectiontimer.stop();
			line_detect_time = "line detection time is " + to_string(linedetectiontimer.value * 1000) + "ms";
			linedetectiontimer.reset();

			//去除干扰线段
			lineselectiontimer.start();
			findPrimaryAngle(lines_std);
			lineselectiontimer.stop();
			line_select_time = "line selection time is " + to_string(lineselectiontimer.value * 1000) + "ms";
			lineselectiontimer.reset();

			//*****************************

			cv::Mat drawImg = frame.clone();
			cv::Mat drawImg2 = frame.clone();
			//ls->drawSegments(drawImg, lines_std);
			//imshow("2", drawImg);

			pointtimer.start();
			std::vector<cv::Point> Points;
			for (int i = 0; i < lines_std.size(); i++)
			{
				cv::Point p1, p2;
				p1 = cv::Point(lines_std[i][0] + r.x, lines_std[i][1] + r.y);
				p2 = cv::Point(lines_std[i][2] + r.x, lines_std[i][3] + r.y);

				Points.push_back(p1);
				Points.push_back(p2);
			}

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


			pointtimer.stop();
			point_process_time = "points selection time is " + to_string(pointtimer.value * 1000) + "ms";
			pointtimer.reset();

			while (true)
				if (point_mutex.try_lock()) {
					feature_point = flatPoints(Points);
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
			for (int i = 0; i < Points.size(); i++)
			{
				circle(drawImg2, Points[i], 5, cv::Scalar(0, 0, 255), 2, 18);
				string text = "point" + to_string(i);
				putText(drawImg2, text, Points[i], font_face, font_scale, cv::Scalar(0, 255, 255), thickness, 8, 0);
				int j = i == Points.size() - 1 ? 0 : i + 1;
				line(drawImg2, Points[i], Points[j], cv::Scalar(255, 0, 0), 2, 8);
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
			putText(drawImg2, roi_process_time, cv::Point(20, 40), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 255, 255));
			putText(drawImg2, line_detect_time, cv::Point(20, 55), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 255, 255));
			putText(drawImg2, line_select_time, cv::Point(20, 70), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 255, 255));
			putText(drawImg2, point_process_time, cv::Point(20, 85), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 255, 255));

			while (true)
				if (fea_mutex.try_lock()) {
					feature_img = drawImg2;
					fea_mutex.unlock();
					break;
				}

			printLog("feature image " + to_string(count) + "stored successfully!");

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
	for (int i = 0; i < points.size(); i += 2) {
		feature[i] = static_cast<double>(points[i].x);
		feature[i+1] = static_cast<double>(points[i].y);
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