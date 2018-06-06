
#include "imageSequence.h"
#include <opencv2/imgcodecs.hpp>
#include <iostream>

ImageSequence::ImageSequence()
{
    sourceType = -1;
    cur = 0;
}

ImageSequence::ImageSequence(const std::vector<std::string> &imglst)
{
    sourceType = 0;
    cur = 0;
    for(auto c:imglst)
    {
        imgPaths.push_back(c);
    }
}

ImageSequence::ImageSequence(const std::string &vidpath)
{
    sourceType = 1;
    cur = 0;
    vid.open(vidpath);
}

ImageSequence::~ImageSequence()
{
    sourceType = -1;
    imgPaths.resize(0);
    
    if(vid.isOpened())
    {
        vid.release();
    }
}

void ImageSequence::open(const std::vector<std::string> &imglst)
{
    sourceType = 0;
    cur = 0;
    imgPaths.resize(0);
    for(auto c:imglst)
    {
        imgPaths.push_back(c);
    }
}

void ImageSequence::open(const std::string &vidpath)
{
    sourceType = 1;
    cur = 0;
    std::cout<<vidpath<<std::endl;
    vid.open(vidpath);
}


bool ImageSequence::get(cv::Mat &m)
{
    cv::Mat grabber;
    if(sourceType == 0)
    {
        if(cur >= imgPaths.size())
        {
            return IMSEQ_STAT_END;
        }

        grabber = cv::imread(imgPaths[cur]);
        if(grabber.empty())
        {
            cur++;
            return IMSEQ_STAT_IMGERR;
        }
        
    }
    else if(sourceType == 1)
    {
        if(!vid.isOpened())
        {
            std::cout<<"get1"<<std::endl;
            return IMSEQ_STAT_END;
        }

        vid>>grabber;
        if(grabber.empty())
        {
            std::cout<<"get2"<<std::endl;
            return IMSEQ_STAT_END;
        }
    }
    cur++;
    m = grabber.clone();
    return IMSEQ_STAT_OK;
}

bool ImageSequence::stepForward(int n)
{
    cur+=n;
    if(sourceType == 1)
    {
        for(int i = 0; i < n; ++i)
        {
			if (false == vid.grab())
				return false;
        }
    }
    cur+=n;
	return true;
}
