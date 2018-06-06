#ifndef IMAGESEQUENCE_H
#define IMAGESEQUENCE_H

#include <vector>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

#define IMSEQ_STAT_OK 0
#define IMSEQ_STAT_END 1
#define IMSEQ_STAT_IMGERR 2


class ImageSequence
{
public:
    ImageSequence();
    ImageSequence(const std::vector<std::string> &);
    ImageSequence(const std::string &);
    ~ImageSequence();
    void open(const std::vector<std::string> &);
    void open(const std::string &);
    bool get(cv::Mat &);
	bool stepForward(int n);

private:
    int sourceType;
    std::vector<std::string> imgPaths;
    int cur;
    cv::VideoCapture vid;
};

#endif
