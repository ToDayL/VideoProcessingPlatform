#include "MouseOperator.h"
#include <iostream>

#define min(a,b) a>b?b:a 
#define max(a,b) a<b?b:a 


bool BoxDrawer::Bt_down;
cv::Point2i BoxDrawer::Bt_down_start_pt;
cv::Point2i BoxDrawer::Bt_Up_end_pt;
bool BoxDrawer::save_ind;
bool BoxDrawer::Reserve1;

void BoxDrawer::MouseCB(int event,int x,int y,int flags,void *ustc)
{
    if(event ==cv::EVENT_LBUTTONDOWN)
    {
        Bt_down = true;
        Bt_down_start_pt = cv::Point2i(x,y);
        Bt_Up_end_pt = cv::Point2i(x,y);
        save_ind = false;
    }

    if(event == cv::EVENT_LBUTTONUP && Bt_down)
    {
        Bt_down = false;
        Bt_Up_end_pt = cv::Point2i(x,y);
        save_ind = true;
    }

    if(event == cv::EVENT_MOUSEMOVE && Bt_down)
    {
        Bt_Up_end_pt = cv::Point2i(x,y);
        save_ind = false;
    }
}

BoxDrawer::BoxDrawer()
{
    Bt_down = false;
    Reserve1 = false;
    cv::Point2i Bt_down_start_pt = cv::Point2i(-1,-1);
    cv::Point2i Bt_Up_end_pt = cv::Point2i(-1,-1);
    save_ind = false;
}

BoxDrawer::~BoxDrawer()
{
    Bt_down = false;
    Reserve1 = false;
    cv::Point2i Bt_down_start_pt = cv::Point2i(-1,-1);
    cv::Point2i Bt_Up_end_pt = cv::Point2i(-1,-1);
    save_ind = false;
}

cv::Point2d BoxDrawer::getStartPoint()
{
    return Bt_down_start_pt;
}

cv::Point2d BoxDrawer::getEndPoint()
{
    return Bt_down_start_pt;
}

cv::Rect2i BoxDrawer::getRect()
{
    int left = min(Bt_down_start_pt.x, Bt_Up_end_pt.x);
    int right = max(Bt_down_start_pt.x, Bt_Up_end_pt.x);
    int top = min(Bt_down_start_pt.y, Bt_Up_end_pt.y);
    int bottom = max(Bt_down_start_pt.y, Bt_Up_end_pt.y);
    // std::cout << left <<"  "<< right <<"  "<< top <<"  " << bottom <<std::endl;
    return cv::Rect2i(cv::Point2i(left, top), cv::Point2i(right, bottom));
}

bool BoxDrawer::getSav_Ind()
{
    return save_ind;
}

void BoxDrawer::resetSav_Ind()
{
    save_ind = false;
}

bool BoxDrawer::getStatus()
{
    return Bt_down;
}

void BoxDrawer::reset()
{
    Bt_down = false;
    Reserve1 = false;
    Bt_down_start_pt = cv::Point2i(-1,-1);
    Bt_Up_end_pt = cv::Point2i(-1,-1);
    save_ind = false;
}
