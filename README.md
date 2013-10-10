OpenCVDrawJapaneseFontSample
====
OpenCV+Windows環境で日本語フォントの描画テスト。

GDI+を使用して文字を描画しています。

How to use
====
<pre>

#include "cv_draw_font.h"
    ・
    ・
    ・
  cv::Mat image(cv::Size(640, 480), CV_8UC3);
  image = CV_RGB(0, 0, 64); // clear
  
  CvDrawFont font(_T("メイリオ"), 24);
  font.draw(image, _T("描画する文字"), 20, 100, CV_RGB(255, 255, 255));
    ・
    ・
    ・
</pre>

