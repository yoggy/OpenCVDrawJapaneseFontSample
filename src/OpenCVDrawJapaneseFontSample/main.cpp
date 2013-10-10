#pragma once

#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <tchar.h>

#include <opencv2/highgui/highgui.hpp>

#ifdef _DEBUG
	#pragma comment(lib, "opencv_core246d.lib")
	#pragma comment(lib, "opencv_highgui246d.lib")
#else
	#pragma comment(lib, "opencv_core246.lib")
	#pragma comment(lib, "opencv_highgui246.lib")
#endif

#include "cv_draw_font.h"

int main(int argc, TCHAR* argv[])
{
	CvDrawFont font_meiryo(_T("メイリオ"), 24);
	CvDrawFont font_msgothic(_T("ＭＳ Ｐゴシック"), 24);
	CvDrawFont font_msmincho(_T("ＭＳ Ｐ明朝"), 24);

	cv::Mat image(cv::Size(640, 480), CV_8UC3);

	TCHAR *str = _T("日本語のフォントで描画してみるテスト");

	while(true) {
		image = CV_RGB(0, 0, 64);
		font_meiryo.draw(image, str, 20, 100, CV_RGB(255, 255, 255));
		font_msgothic.draw(image, str, 20, 200, CV_RGB(255, 255, 255));
		font_msmincho.draw(image, str, 20, 300, CV_RGB(255, 255, 255));
		font_meiryo.draw_outline(image, str, 20, 400, CV_RGB(255, 255, 255), CV_RGB(0,0,0), 3);

		cv::imshow("image", image);

		int c = cv::waitKey();
		if (c == 27) break;
	}
	cv::destroyAllWindows();

	return 0;
}

