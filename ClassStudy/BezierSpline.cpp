#include "BezierSpline.h"

BezierSpline::BezierSpline() :
	x(), y(),
	LoD(1000)
{
	curve_x.resize(LoD);
	curve_y.resize(LoD);
}

BezierSpline::~BezierSpline()
{
}

float BezierSpline::bernoulli_trial(float u, int n, int k)
{
	return static_cast<float>(pow(u, k) * pow((1 - u), n - k));
}

int BezierSpline::combination(int n, int k)
{
	int comb = 1;
	
	for (int i = 0; i < k; ++i) comb *= n--;
	for (int i = 1; i <= k; ++i) comb /= i;

	return comb;
}

float BezierSpline::spline_x(float u, int n)
{
	float answer = 0.f;

	for (int i = 0; i < n; ++i)
	{
		answer += static_cast<float>(x[i]) * static_cast<float>(combination(n - 1, i)) * bernoulli_trial(u, n - 1, i);
	}
	
	return answer;
}

float BezierSpline::spline_y(float u, int n)
{
	float answer = 0.f;

	for (int i = 0; i < n; ++i)
	{
		answer += static_cast<float>(y[i]) * static_cast<float>(combination(n - 1, i)) * bernoulli_trial(u, n - 1, i);
	}

	return answer;
}

void BezierSpline::draw_spline(HWND hWnd, HDC hdc, int n)
{
	float u = 0;
	float step = 1.f / static_cast<float>(LoD);

	for (int i = 0; i < LoD - 1; i++)
	{
		curve_x[i] = ROUND(spline_x(u, n));
		curve_y[i] = ROUND(spline_y(u, n));
		u += step;
	}
	curve_x[LoD - 1] = x[n - 1];
	curve_y[LoD - 1] = y[n - 1];

	for (int i = 0; i < LoD - 1; i++)
	{
		line_DDA(hWnd, hdc, curve_x[i], curve_y[i], curve_x[i + 1], curve_y[i + 1]);
	}
}

void BezierSpline::line_DDA(HWND hWnd, HDC hdc, int x1, int y1, int x2, int y2)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int step;
	float xinc, yinc, x = static_cast<float>(x1), y = static_cast<float>(y1);

	step = (abs(dx > abs(dy)) ? abs(dx) : abs(dy));
	xinc = dx / static_cast<float>(step);
	yinc = dy / static_cast<float>(step);
	
	
	//hdc = GetDC(hWnd);
	for (int k = 0; k < step; k++)
	{
		if (k == 0) {
			MoveToEx(hdc, ROUND(x1), ROUND(y1), nullptr);
			x += xinc; y += yinc;
			LineTo(hdc, ROUND(x), ROUND(y));
		}
		else {
			MoveToEx(hdc, ROUND(x), ROUND(y), nullptr);
			x += xinc; y += yinc;
			LineTo(hdc, ROUND(x), ROUND(y));
		}
	}
	//ReleaseDC(hWnd, hdc);
}

void BezierSpline::set_coord(LPARAM lParam)
{
	x.push_back(LOWORD(lParam));
	y.push_back(HIWORD(lParam));
}

void BezierSpline::reset()
{
	x.clear();
	y.clear();
	curve_x.clear();
	curve_y.clear();
	curve_x.resize(LoD);
	curve_y.resize(LoD);
}
