#pragma once

#include <string>
#include <opencv2/core/core.hpp>

class CvDrawFont
{
public:
	CvDrawFont(const TCHAR *font_name, int size);
	virtual ~CvDrawFont(void);

	void draw(cv::Mat &image, const TCHAR *str, const int &x, const int &y, const cv::Scalar &color);
	void draw_outline(cv::Mat &image, const TCHAR *str, const int &x, const int &y, const cv::Scalar &inner_color, const cv::Scalar &outline_color, const int &outline_width);

private:
	void *font_;
};

