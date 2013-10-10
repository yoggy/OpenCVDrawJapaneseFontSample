#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <objidl.h>
#include <GdiPlus.h>
#pragma comment(lib, "Gdiplus.lib")

#include <locale.h>
#include <tchar.h>

#include "cv_draw_font.h"

class StaticGdiPlusUtil {
public:
	StaticGdiPlusUtil() {
		setlocale(LC_CTYPE, "jpn");
		Gdiplus::GdiplusStartup(&token, &input, NULL);
	};

	virtual ~StaticGdiPlusUtil() {
		Gdiplus::GdiplusShutdown(token);
	}

private:
	Gdiplus::GdiplusStartupInput input;
	ULONG_PTR token;
};

StaticGdiPlusUtil static_gdi_plus_util_;

/////////////////////////////////////////////////////////

wchar_t * create_wcs_(const char *mbs)
{
	if (mbs == NULL) return NULL;

	int mbs_len = strlen(mbs);
	size_t rv;
	mbstowcs_s(&rv, NULL, 0, mbs, _TRUNCATE);

	int wcs_len = rv;
	wchar_t *wcs = new wchar_t[wcs_len + 1];

	mbstowcs_s(&rv, wcs, wcs_len, mbs, _TRUNCATE);
	return wcs;
}

////////////////////////////////////////////////////////

CvDrawFont::CvDrawFont(const TCHAR *font_name, int font_size) : font_(NULL)
{
#ifdef _UNICODE
	font_ = new Gdiplus::Font(font_name, Gdiplus::REAL(font_size));
#else
	wchar_t *wcs = create_wcs_(font_name);
	font_ = new Gdiplus::Font(wcs, Gdiplus::REAL(font_size));
	delete wcs;
#endif
}

CvDrawFont::~CvDrawFont(void)
{
	delete (Gdiplus::Font*)font_;
	font_ = NULL;
}

void draw_(Gdiplus::Graphics &g, Gdiplus::Font* font, const TCHAR *str, const int &x, const int &y, const int &w, const int &h, const cv::Scalar &color)
{
	Gdiplus::StringFormat format;
		
	Gdiplus::Color c((BYTE)color[2], (BYTE)color[1], (BYTE)color[0]); // BGR
	Gdiplus::SolidBrush brush(c);

	Gdiplus::RectF rect((float)x, (float)y, (float)w, (float)h);

#ifdef _UNICODE
	int len = wcslen(str);
	g.DrawString(str, len, (Gdiplus::Font*)font, rect, &format, &brush); 
#else
	wchar_t *wcs = create_wcs_(str);
	int len = wcslen(wcs);

	g.DrawString(wcs, len, font, rect, &format, &brush); 

	delete wcs;
#endif
}

void CvDrawFont::draw(cv::Mat &image, const TCHAR *str, const int &x, const int &y, const cv::Scalar &color)
{
	Gdiplus::Bitmap bitmap(image.cols, image.rows, image.cols * image.channels(), PixelFormat24bppRGB, image.data);
	Gdiplus::Graphics g(&bitmap);
	g.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);

	draw_(g, (Gdiplus::Font* )font_, str, x, y, image.cols, image.rows, color);
}

void CvDrawFont::draw_outline(cv::Mat &image, const TCHAR *str, const int &x, const int &y, const cv::Scalar &inner_color, const cv::Scalar &outline_color, const int &outline_width)
{
	Gdiplus::Bitmap bitmap(image.cols, image.rows, image.cols * image.channels(), PixelFormat24bppRGB, image.data);
	Gdiplus::Graphics g(&bitmap);
	g.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);

	for (int dy = -outline_width; dy <= outline_width; ++dy) {
		for (int dx = -outline_width; dx <= outline_width; ++dx) {
			if (dx*dx + dy*dy > outline_width*outline_width) continue;
			draw_(g, (Gdiplus::Font* )font_, str, x+dx, y+dy, image.cols, image.rows, outline_color);
		}
	}
	draw_(g, (Gdiplus::Font* )font_, str, x, y, image.cols, image.rows, inner_color);
}