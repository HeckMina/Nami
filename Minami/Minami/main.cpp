#include "resource.h"
#include <Windows.h>

HINSTANCE g_hInstance;
bool die(int n)
{
	exit(n);
	return true;
}

static const wchar_t* kSplashScreenClass = L"UnitySplashWindow";

static HWND s_SplashWindow;
static HBITMAP s_SplashBitmap;

// We have to setup splash screen parent before hiding it.
// Otherwise when we're destroying the splash screen, Windows will activate some
// previous application because the parent of the window was null.
void SetSplashScreenParent( HWND window )
{
	if( !s_SplashWindow )
		return;
	HWND parent = GetParent(s_SplashWindow);
	SetParent( parent, window );
}


static HWND CreateSplashWindow()
{
	WNDCLASSW wc = { 0 };
	wc.lpfnWndProc = DefWindowProcW;
	wc.hInstance = g_hInstance;
	wc.hIcon = LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_APP_ICON));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = kSplashScreenClass;
	RegisterClassW(&wc);

	HWND hwndOwner = CreateWindowW(kSplashScreenClass, NULL, WS_POPUP, 0, 0, 0, 0, NULL, NULL, g_hInstance, NULL);
	return CreateWindowExW(WS_EX_LAYERED, kSplashScreenClass, NULL, WS_POPUP | WS_VISIBLE, 0, 0, 0, 0, hwndOwner, NULL, g_hInstance, NULL);
}

static const unsigned char* s_pngInputPtr;
static size_t s_pngInputSizeLeft;

static void png_user_read_func( png_structp png_ptr, png_bytep data, png_size_t len )
{
	// check for overflow
	if( len > s_pngInputSizeLeft )
		len = s_pngInputSizeLeft;
	memcpy( data, s_pngInputPtr, len );
	s_pngInputPtr += len;
	s_pngInputSizeLeft -= len;
}

static bool png_decode( const void* data, size_t size, unsigned char*& outData, int& outWidth, int& outHeight )
{
	s_pngInputPtr = reinterpret_cast<const unsigned char*>(data);
	s_pngInputSizeLeft = size;

	if( !s_pngInputPtr )
		return false;

	// check png header
	if( s_pngInputSizeLeft < 8 || !png_check_sig( const_cast<unsigned char*>(s_pngInputPtr), 8 ) )
		return false;

	png_structp png_ptr;
	png_infop info_ptr;
	png_uint_32 width, height;
	int bit_depth, color_type, interlace_type;

	double image_gamma = 0.45;
	int number_passes = 0;

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,NULL,NULL,&png_user_warning_fn);
	if( png_ptr == NULL )
		return false;

	info_ptr = png_create_info_struct(png_ptr);
	if( info_ptr == NULL )
	{
		png_destroy_read_struct(&png_ptr,(png_infopp)NULL,(png_infopp)NULL);
		return false;
	}

	if( setjmp(png_ptr->jmpbuf) )
	{
		png_destroy_read_struct(&png_ptr,&info_ptr,(png_infopp)NULL);
		return false;
	}

	png_set_read_fn( png_ptr,(void*)NULL,&png_user_read_func );
	png_read_info( png_ptr, info_ptr );

	png_get_IHDR( png_ptr,info_ptr,&width,&height,&bit_depth,&color_type, &interlace_type, NULL, NULL );

	png_set_strip_16(png_ptr); // strip 16 bit channels to 8 bit
	png_set_packing(png_ptr);  // separate palettized channels

	// figure out format
	int bpp = 4;
	outWidth = width;
	outHeight = height;

	// palette -> rgb
	if( color_type == PNG_COLOR_TYPE_PALETTE ) png_set_expand(png_ptr);

	// grayscale -> 8 bits
	if( !(color_type & PNG_COLOR_MASK_COLOR) && bit_depth < 8 ) png_set_expand(png_ptr);

	// if exists, expand tRNS to alpha channel
	if ( png_get_valid(png_ptr,info_ptr,PNG_INFO_tRNS) ) png_set_expand(png_ptr);

	// expand gray to RGB
	if( color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA )
		png_set_gray_to_rgb(png_ptr);

	double screen_gamma = 2.0f;

	image_gamma = 0.0;
	if ( png_get_gAMA(png_ptr,info_ptr,&image_gamma) )
	{
		png_set_gamma(png_ptr,screen_gamma,image_gamma);
	}
	else
	{
		png_set_gamma(png_ptr,screen_gamma,0.45);
	}

	png_set_bgr(png_ptr);         // flip RGBA to BGRA

	if (color_type == PNG_COLOR_TYPE_RGB)
		png_set_filler( png_ptr, 0xFF, PNG_FILLER_AFTER ); // force alpha byte

	number_passes = png_set_interlace_handling(png_ptr);
	png_read_update_info(png_ptr,info_ptr); // update gamma, etc.

	// allocate image
	int numbytes = width * height * bpp;
	outData = new unsigned char[numbytes];
	if( !outData )
	{
		png_destroy_read_struct(&png_ptr,&info_ptr,(png_infopp)NULL);
		return false;
	}

	memset( outData, 0, numbytes );

	png_bytep* row_pointers = new png_bytep[height];
	for( png_uint_32 row=0; row<height; ++row )
	{
		row_pointers[row] = outData + row*width*bpp;
	}

	for( int pass=0; pass<number_passes; pass++ )
	{
		png_read_rows(png_ptr,row_pointers,NULL,height);
	}

	// cleanup
	png_read_end( png_ptr,info_ptr );
	png_destroy_read_struct( &png_ptr,&info_ptr,(png_infopp)NULL );
	delete[] row_pointers;

	// premultiply alpha!
	unsigned int index = 0;
	for( unsigned int i = 0; i < width * height; ++i )
	{
		int alpha = outData[index+3];
		outData[index+0] = unsigned int(outData[index+0]) * alpha / 255;
		outData[index+1] = unsigned int(outData[index+1]) * alpha / 255;
		outData[index+2] = unsigned int(outData[index+2]) * alpha / 255;
		index += 4;
	}

	return true;
}

HBITMAP LoadPNGFromResource( HDC dc, unsigned int resourceID, int& width, int& height )
{
	HINSTANCE instance = g_hInstance;
	HBITMAP bitmap = NULL;
	width = 0;
	height = 0;
	HRSRC resource = FindResource( instance, MAKEINTRESOURCEA(resourceID), "BINARY" );
	if( resource )
	{
		DWORD size = SizeofResource( instance, resource );
		HGLOBAL glob = LoadResource( instance, resource );
		if( glob )
		{
			void* data = LockResource( glob );
			if( data )
			{
				unsigned char* bgra;
				if( !png_decode( data, size, bgra, width, height ) )
					return bitmap;

				BITMAPINFO bi;
				memset( &bi, 0, sizeof(bi) );
				bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
				bi.bmiHeader.biWidth = width;
				bi.bmiHeader.biHeight = -height;
				bi.bmiHeader.biBitCount = 32;
				bi.bmiHeader.biPlanes = 1;
				bi.bmiHeader.biCompression = BI_RGB;
				unsigned char* bitmapData = NULL;
				bitmap = CreateDIBSection( dc, &bi, DIB_RGB_COLORS, (void**)&bitmapData, NULL, 0 );
				if( bitmap ) {
					memcpy(bitmapData, bgra, width*height*4);
				}

				delete [] bgra;
			}
		}
	}
	return bitmap;
}
static void SetSplashImage(HWND hwndSplash, UINT resourceID, int ytopFromCenter)
{
	// get the primary monitor's info
	POINT ptZero = { 0 };
	HMONITOR hmonPrimary = MonitorFromPoint(ptZero, MONITOR_DEFAULTTOPRIMARY);
	MONITORINFO monitorinfo = { 0 };
	monitorinfo.cbSize = sizeof(monitorinfo);
	GetMonitorInfo(hmonPrimary, &monitorinfo);

	// create a memory DC holding the splash bitmap
	HDC hdcScreen = GetDC(NULL);
	HDC hdcMem = CreateCompatibleDC(hdcScreen);

	// load the bitmap
	int splashWidth, splashHeight;
	HBITMAP hbmpSplash = LoadPNGFromResource( hdcMem, resourceID, splashWidth, splashHeight );
	s_SplashBitmap = hbmpSplash;
	HBITMAP hbmpOld = (HBITMAP) SelectObject(hdcMem, hbmpSplash);

	// use the source image's alpha channel for blending
	BLENDFUNCTION blend = { 0 };
	blend.BlendOp = AC_SRC_OVER;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;

	// center the splash screen in the middle of the primary work area
	const RECT & rcWork = monitorinfo.rcWork;
	POINT ptOrigin;
	ptOrigin.x = rcWork.left + (rcWork.right - rcWork.left - splashWidth) / 2;
	ptOrigin.y = (rcWork.bottom - rcWork.top) / 2 - ytopFromCenter;

	// paint the window (in the right location) with the alpha-blended bitmap
	SIZE sizeSplash = { splashWidth, splashHeight };
	UpdateLayeredWindow(hwndSplash, hdcScreen, &ptOrigin, &sizeSplash, hdcMem, &ptZero, RGB(255, 0, 255), &blend, ULW_ALPHA);

	// delete temporary objects
	SelectObject(hdcMem, hbmpOld);
	DeleteDC(hdcMem);
	ReleaseDC(NULL, hdcScreen);
}

void ShowSplashScreen()
{
	s_SplashWindow = CreateSplashWindow();
	SetSplashImage( s_SplashWindow, IDR_BINARY1, 200 );
}

void HideSplashScreen()
{
	if( s_SplashWindow )
	{
		HWND parent = GetParent(s_SplashWindow);
		DestroyWindow(s_SplashWindow);
		DestroyWindow(parent);
		s_SplashWindow = NULL;
	}
	if( s_SplashBitmap )
	{
		DeleteObject(s_SplashBitmap);
		s_SplashBitmap = NULL;
	}
}

HRESULT CALLBACK WindowPorcesser(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_KEYDOWN:
		switch((int)wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		DefWindowProcW(hwnd,uMsg,wParam,lParam);
		break;
	}
	return DefWindowProcW(hwnd,uMsg,wParam,lParam);
}

INT WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd )
{
	g_hInstance=hInstance;
	WNDCLASSEXW wcex;
	memset( &wcex, 0, sizeof(wcex) );
	wcex.cbSize = sizeof(wcex); 
	wcex.style			=  CS_HREDRAW | CS_VREDRAW | CS_DROPSHADOW ;
	wcex.lpfnWndProc	= WindowPorcesser;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_APP_ICON);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= NULL;
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= L"MinamiEditor";
	ATOM classAtom = RegisterClassExW(&wcex);
	classAtom!=0 || die(1);
	HWND hwnd=CreateWindowExW((DWORD)NULL,
		L"MinamiEditor",
		L"Van Core Render Window",
		WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN|WS_CLIPSIBLINGS|!WS_MAXIMIZEBOX,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);
	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);
	MSG msg;
	while(1)
	{
		if (PeekMessageW(&msg,NULL,0,0,PM_REMOVE))
		{
			if (msg.message==WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}
	return 0;
}