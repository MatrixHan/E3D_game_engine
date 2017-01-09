#include "EGraphics.h"
#include "EUtil.h"

namespace E3D
{

	EBitmap::EBitmap(const EString& filename):name(filename),pixels(NULL),
		pitch(0),width(0),height(0),valid(false)
	{
		hBitmap = (HBITMAP)::LoadImage(GHInstance, GetPath(filename).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (hBitmap != NULL)
		{
			bitmapHDC = ::CreateCompatibleDC(NULL);
			::SelectObject(bitmapHDC,(HGDIOBJ)hBitmap);
			::GetObject(hBitmap, sizeof(BITMAP), &bitmap);

			width = bitmap.bmWidth;
			height = bitmap.bmHeight;

			pitch = bitmap.bmHeight;
			valid = true;

			pixels = new EColor[width*height];
			for (EInt i = 0; i < getHeight(); i++)
			{
				for (EInt j = 0; j < getWidth(); j++)
				{
					COLORREF color = ::GetPixel(bitmapHDC, i, j);
					pixels[j*width + i] = EColor(GetRValue(color),GetGValue(color),GetBValue(color));
				}
			}
		}
	}

	EBitmap::~EBitmap()
	{
		DeleteObject(hBitmap);
		DeleteDC(bitmapHDC);
		SafeDeleteArray(pixels);
	}

	EColor EBitmap::getPixel(EInt x,EInt y) 
	{
		return pixels[y*pitch+x];
	}
//graphics begin
	HINSTANCE  GHInstance;
	HBITMAP		EGraphics::GBufferHandle;
	HDC			EGraphics::GBufferedHDC;
	HBRUSH		EGraphics::GBgBrush;
	HPEN		EGraphics::GPen;
	HINSTANCE	 EGraphics::GInstance;
	BYTE		 *EGraphics::GDatas;
	EInt		 EGraphics::GPitch;
	DIBSECTION  EGraphics::GDiBSection;
	RECT		EGraphics::GBufferSize;
	EFloat		*EGraphics::GZBuffer;

	bool EGraphics::initGraphics(HINSTANCE hinstance)
	{
		GBufferedHDC = ::CreateCompatibleDC(NULL);

		BITMAPINFO info = { 0 };
		info.bmiHeader.biSize = sizeof(info.bmiHeader);
		info.bmiHeader.biWidth = SCREEN_WIDTH;
		info.bmiHeader.biHeight = -SCREEN_HEIGHT;
		info.bmiHeader.biPlanes = 1;
		info.bmiHeader.biBitCount = 32;
		info.bmiHeader.biCompression = BI_RGB;
		info.bmiHeader.biSizeImage = SCREEN_WIDTH*SCREEN_HEIGHT * 32 / 8;
		// 创建一块内存纹理并获取其数据指针
		void *pBits = NULL;
		GBufferHandle = ::CreateDIBSection(GBufferedHDC, &info, DIB_RGB_COLORS, &pBits, NULL, 0);
		::SelectObject(GBufferedHDC,GBufferHandle);

		::GetObject(GBufferHandle, sizeof(DIBSECTION), &GDiBSection);
		GDatas = (BYTE*)GDiBSection.dsBm.bmBits;
		GPitch = GDiBSection.dsBm.bmWidthBytes;//一行的字节数 字节步长
		
		::SetRect(&GBufferSize, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);//设置场地大小
		
		GPen = ::CreatePen(PS_SOLID,1,RGB(255,255,255));//创建画笔
		::SelectObject(GBufferedHDC,GPen);

		GBgBrush = ::CreateSolidBrush(RGB(0, 0, 0));
		::SelectObject(GBufferedHDC, GBgBrush);

		HFONT hfnt = (HFONT)GetStockObject(OEM_FIXED_FONT);//不用创建 直接从系统仓库拿字体
		::SelectObject(GBufferedHDC,hfnt);

		::SetBkMode(GBufferedHDC,TRANSPARENT);

		GZBuffer = new EFloat[SCREEN_WIDTH*SCREEN_HEIGHT];
		memset(GZBuffer, 0, sizeof(EFloat)*SCREEN_WIDTH*SCREEN_HEIGHT);

		return true;
	}

	void EGraphics::shutdownGraphics()
	{
		::DeleteObject(GPen);
		::DeleteObject(GBgBrush);
		::DeleteObject(GBufferHandle);
		::DeleteDC(GBufferedHDC);
	}

	void  EGraphics::ClearBuffer(const EColor &c /*= EColor()*/)
	{
		::FillRect(GBufferedHDC, &GBufferSize, GBgBrush);
		::memset(GZBuffer, 0, sizeof(EFloat)*SCREEN_WIDTH*SCREEN_HEIGHT);
	}

	void EGraphics::drawLine(EInt x0, EInt y0, EInt x1, EInt y1,const EColor &c)//画线 
	{
		::SelectObject(GBufferedHDC,GetStockObject(DC_PEN));
		::SetDCPenColor(GBufferedHDC, RGB(c.r, c.g, c.b));
		::MoveToEx(GBufferedHDC, x0, y0, NULL);
		::LineTo(GBufferedHDC, x1, y1);
	}

	void EGraphics::drawString(const EString& str, EInt x, EInt y, const EColor &c)//写字符串
	{
		::SetTextColor(GBufferedHDC, RGB(c.r, c.g, c.b));
		::TextOut(GBufferedHDC, x, y, str.c_str(), str.length());
	}
	void  EGraphics::fillTriangle(EInt x0, EInt y0, EInt x1, EInt y1, EInt x2, EInt y2, const EColor &c)//绘制三角形
	{
	
	}

	void  EGraphics::enableSmoothingMode(EBool enable)
	{
		
	}

	EBool  EGraphics::checkZ(EInt x, EInt y, EFloat z)
	{
		EInt index = y*SCREEN_WIDTH + x;
		EFloat divZ = 1.0f / z;
		if (GZBuffer[index] > divZ)
			return false;
		GZBuffer[index] = divZ;
		return true;
	}
	void   EGraphics::setPixel(EInt x, EInt y,const EColor &c)
	{
		BYTE * pSrcPix = GDatas + (GPitch * y);
		pSrcPix += x * 4;
		pSrcPix[0] = c.b;
		pSrcPix[1] = c.g;
		pSrcPix[2] = c.r;
		pSrcPix[3] = c.a;
	}
	EColor  EGraphics::getPixel(EInt x, EInt y)
	{
		BYTE * pSrcPix = GDatas + (GPitch * y);
		pSrcPix += x * 4;
		return EColor(pSrcPix[2],pSrcPix[1],pSrcPix[0]);
	}
	void  EGraphics::fillBuffer(HDC hdc)
	{
		::BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GBufferedHDC, 0, 0, SRCCOPY);
	}
}