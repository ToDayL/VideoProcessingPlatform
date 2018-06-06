/* ****************** GettingSamples.cpp ******************/
//
//  Author: Li Jin
//  Created time: 20171225
//  Platform: Ubuntu 16.04 x64
//  Used Libs: OpenCV 3.2
//  Description: Interface of gettingSamples, Used to 
//      get image samples in image, videos, sequence of 
//      images.
/* ********************************************************/
#ifndef MOUSEOPERATOR_H
#define MOUSEOPERATOR_H

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

class BoxDrawer
{
public:
    BoxDrawer();
    ~BoxDrawer();
    void static MouseCB(int event,int x,int y,int flags,void *ustc);
    cv::Point2d getStartPoint();
    cv::Point2d getEndPoint();
    cv::Rect2i getRect();
    bool getSav_Ind();
    void resetSav_Ind();
    bool getStatus();
    void reset();
private:
    static bool Bt_down;
    static bool Reserve1;
    static cv::Point2i Bt_down_start_pt;
    static cv::Point2i Bt_Up_end_pt;
    static bool save_ind;
};

#endif
