// VideoProcessingPlatform.cpp: 定义控制台应用程序的入口点。
//

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include <opencv2/shape.hpp>
#include <opencv2/highgui.hpp>

#include "CMDParser.h"
#include "imageSequence.h"
#include "MouseOperator.h"


int main(int argc, char *argv[])
{
	std::vector<std::string> Key_map;

	Key_map.push_back("-v --video | @vidPath | Get samples from video");
	Key_map.push_back("-l --list  | @lstPath | Get samples from image sequence");
	Key_map.push_back("-q --quiet |  quiet   | Quiet Mode(No Image Show)");
	Key_map.push_back("-h --help  |  help    | Get Help");

	CMDParser cmdParcer(argc, argv, Key_map);

	if (cmdParcer.error())
	{
		std::cout << cmdParcer.about() << std::endl;
		std::cout << "Parser Error " << cmdParcer.error() << std::endl;
		return 0;
	}

	if (cmdParcer.has("help"))
	{
		std::cout << cmdParcer.about() << std::endl;
		return 0;
	}

	ImageSequence imgseq;

	int datatype = -1;
	std::vector<std::string> imgPaths;

	if (cmdParcer.has("vidPath"))
	{
		datatype = 1;
		std::cout << cmdParcer["vidPath"] << std::endl;
		imgseq.open(cmdParcer["vidPath"]);
	}
	else if (cmdParcer.has("lstPath"))
	{
		datatype = 2;
		std::ifstream ifs(cmdParcer["lstPath"]);
		if (!ifs.is_open())
		{
			std::cout << "Error Openning file list" << std::endl;
			return 0;
		}
		std::string path;
		while (ifs >> path)
		{
			imgPaths.push_back(path);
		}
		imgseq.open(imgPaths);
	}
	else
	{
		std::cout << cmdParcer.about() << std::endl;
		std::cout << "No Input Sequence!" << std::endl;
		return 0;
	}

	bool quiet = false;
	if (cmdParcer.has("quiet"))
	{
		quiet = true;
	}

	BoxDrawer box_drawer;
	if (!quiet)
	{
		cv::namedWindow("Display");
		cv::setMouseCallback("Display", BoxDrawer::MouseCB);
	}
	
	cv::Rect rec;
	cv::Mat img;

	bool ff = false;
	bool run = false;

	while (1)
	{
		if (run || ff || img.empty())
		{
			if (IMSEQ_STAT_OK != imgseq.get(img))
			{
				break;
			}
		}
		
		if (!quiet)
		{
			cv::Mat display = img.clone();
			if (run || ff)
			{
				box_drawer.reset();
			}

			rec = box_drawer.getRect();
			cv::rectangle(display, rec, cv::Scalar(0, 255, 0), 2);
			cv::imshow("Display", display);
			char c = cv::waitKey(1);

			switch (c)
			{
			case ' ':
				run = run ? false : true;
				ff = false;
				break;
			case 'f':
				ff = ff ? false : true;
				break;
			}

			if (c == 'q')
			{
				break;
			}
		}

		if (ff)
		{
			imgseq.stepForward(50);
		}
	}

    return 0;
}

