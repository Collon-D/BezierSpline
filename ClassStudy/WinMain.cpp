#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include "BezierSpline.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = _T("Windows API");

BezierSpline bs;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG msg;
	WNDCLASS WndClass;
	g_hInst = hInstance;
	
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;

	RegisterClass(&WndClass);
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	static bool bDraw = false;
	static int x, y;

	switch(iMessage)
	{
	case WM_CREATE:
		AllocConsole();
		SetConsoleTitle(_T("WindowsAPI Console"));

		// ! AllocConsole 함수를 호출하여 콘솔창을 띄웠다면 freopen 함수로 기본 입출력 위치를 지정해야 합니다.
		_tfreopen(_T("CONOUT$"), _T("w"), stdout);
		_tfreopen(_T("CONIN$"), _T("r"), stdin);
		_tfreopen(_T("CONERR$"), _T("w"), stderr);
		// ! setlocale 함수로 기본 입출력에 대한 로케일을 설정합니다.
		_tsetlocale(LC_ALL, _T(""));

		return 0;

	case WM_LBUTTONDOWN:
		bs.set_coord(lParam);
		std::cout << "X : " << LOWORD(lParam) << ", Y : " << HIWORD(lParam) << std::endl;

		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	
	case WM_LBUTTONUP:
		hdc = GetDC(hWnd);
		bs.draw_spline(hWnd, hdc, bs.x_size());
		ReleaseDC(hWnd, hdc);
		return 0;

	//case WM_MOUSEMOVE:
	//	if (bDraw)
	//	{
	//		hdc = GetDC(hWnd);
	//		MoveToEx(hdc, x, y, nullptr);
	//		x = LOWORD(lParam);
	//		y = HIWORD(lParam);
	//		LineTo(hdc, x, y);
	//		ReleaseDC(hWnd, hdc);
	//	}
	//	return 0;

	case WM_RBUTTONDOWN:
		bs.reset();
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;

	case WM_DESTROY:
		FreeConsole();
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
