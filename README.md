OpenCVDrawJapaneseFontSample
====
OpenCV+Windows���œ��{��t�H���g�̕`��e�X�g�B

GDI+���g�p���ĕ�����`�悵�Ă��܂��B

How to use
====
<pre>

#include "cv_draw_font.h"
    �E
    �E
    �E
  cv::Mat image(cv::Size(640, 480), CV_8UC3);
  image = CV_RGB(0, 0, 64); // clear
  
  CvDrawFont font(_T("���C���I"), 24);
  font.draw(image, "�`�悷�镶��", 20, 100, CV_RGB(255, 255, 255));
    �E
    �E
    �E
</pre>

