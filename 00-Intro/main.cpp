/* =============================================================
INTRODUCTION TO GAME PROGRAMMING SE102

SAMPLE 00 - INTRODUCTORY CODE

This sample illustrates how to:

1/ Create a window
2/ Initiate DirectX 9, Direct3D, DirectX Sprite
3/ Draw a static brick sprite to the screen

WARNING: This example contains a hell LOT of *sinful* programming practices
================================================================ */
#include <cmath>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"It can fly ~"

#define BRICK_TEXTURE_PATH L"ngan.png"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(106, 166, 196)
#define SCREEN_WIDTH 620
#define SCREEN_HEIGHT 440

#define MAX_FRAME_RATE 60


LPDIRECT3D9 d3d = NULL;						// Direct3D handle
LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

LPDIRECT3DSURFACE9 backBuffer = NULL;
LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 

LPDIRECT3DTEXTURE9 texBrick;				// texture object to store brick image

float brick_x = 0.0f; //tọa độ x
float brick_vx = 0.15f;// vận tốc theo phương x
float brick_y = 100.0f;//tung độ y


LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
		/*xem message là kiểu gì, tương ứng với mỗi dạng
		message thì có một xử lý tương ứng
		ta không xử lý gì nhiều ngoài việc người dùng ấn cửa sổ
		*/
	case WM_DESTROY: // WM_... là một dạng số nguyên
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
hàm winproc để làm gì?
là hàm callback, nó sẽ được hệ thống gọi
khi nhận được sự tương tác của người dùng thì hàm này sẽ được gọi

*/

void DebugOut(wchar_t *fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);
	wchar_t dbg_out[4096];
	vswprintf_s(dbg_out, fmt, argp);
	va_end(argp);
	OutputDebugString(dbg_out);
	//outputDebugString để in ra kq debug, vì game chạy nhanh nên khi 
	//dùng breakpoint thì các giá trị tham số đã thay đổi đi mất tiêu
	//rồi. nó dở vì nhó nhập vô một input sting thôi, còn hàm DebugOut 
	//để in được nhiều tham số hơn(sẽ được dùng như hàm cout<< :D

}

void InitDirectX(HWND hWnd)
{
	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	RECT r;
	GetClientRect(hWnd, &r);	// retrieve window width & height 

	d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv);

	if (d3ddv == NULL)
	{
		OutputDebugString(L"[ERROR] CreateDevice failed\n");
		return;
	}

	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	// Initialize sprite helper from Direct3DX helper library
	D3DXCreateSprite(d3ddv, &spriteHandler);

	OutputDebugString(L"[INFO] InitGame is done\n");

}

/*
	Load all game resources. In this example, only load brick image
*/
// LoadResources(): ý tưởng là nạp hình viên gạch từ dưới đĩa lên trên
//bộ nhớ và nó tạo thành texture
void LoadResources()
{
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(BRICK_TEXTURE_PATH, &info);
	// gồm 2 bước là lấy thông tin D3DXGetImageInfoFromFile và
	// tạo D3DXCreateTextureFromFileEx
	//tạo xong rồi thì cất vào biến đặc biệt là &texBrick và đây là biến 
	//toàn cục lưu hình viên gạch
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", BRICK_TEXTURE_PATH);
		return;
	}

	result = D3DXCreateTextureFromFileEx(
		d3ddv,								// Pointer to Direct3D device object
		BRICK_TEXTURE_PATH,					//-> Path to the image to load
		info.Width,							//-> Texture width
		info.Height,						//-> Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 255, 255),			// Transparent color
		&info,
		NULL,
		&texBrick);								// Created texture pointer

	if (result != D3D_OK)
	{
		OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
		return;
	}

	DebugOut(L"[INFO] Texture loaded Ok: %s \n", BRICK_TEXTURE_PATH);
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/

/*void Update(DWORD dt): cập nhật trạng thái viên gạch*/
void Update(DWORD dt)
{
	//brick_x++;

	brick_x = brick_x + brick_vx*dt; 
	if ( (brick_x > (SCREEN_WIDTH - 32)) || brick_x < 0) brick_vx = -brick_vx;
}

/*
Render a frame
*/
void Render()
{
	if (d3ddv->BeginScene())
	{
		// Clear screen (back buffer) with a color
		d3ddv->ColorFill(backBuffer, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		D3DXVECTOR3 p(brick_x, cos(brick_x * 3.14 / 180.0)*20+100, 0);

		//D3DXVECTOR3 p(100.0f,10.0f, 0);
		spriteHandler->Draw(texBrick, NULL, NULL, &p, D3DCOLOR_XRGB(255, 255, 255));

		spriteHandler->End();
		d3ddv->EndScene();
		
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // nếu như window gửi thông điệp (PM_REMOVE)
			// thì nó sẽ lấy ra cất vào biến &msg
		{
			if (msg.message == WM_QUIT) done = 1;// nếu như thông điệp này là WM_QUIT thì nó 
			//sẽ thoát và tắt màn hình

			// còn nếu không thì lấy ra và tiếp tục gửi đến các cửa sổ, hai dòng dưới
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			Update(dt);

		// update để cập nhật lại trạng thái của thế giới khi mà đã có một thời gia dt trôi qua
		//
			Render();

		//render để chụp hình của thế giới tại thời điểm và vẽ lên màn hình
		//RENDER KHÔNG LÀM THAY ĐỔI GIÁ TRỊ CỦA BIẾN!!!!!!!!!
		// VÍ DỤ CẦM CAMERA QUAY HÌNH LẠI ANH ĐỘNG VIÊN THÌ KHÔNG LÀM ẢNH HƯỞNG GÌ HẾT ANH ĐỘNG VIÊN
		// NGƯỢC LẠI HÀM UPDATE CŨNG VẬY
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);
	//tạo cửa sổ
	InitDirectX(hWnd);
	//khởi động direct x

	LoadResources();
	//nạp hình lên
	Run();
	//chạy

	return 0;
}