#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <Windows.h>

#define ROUND(num) (static_cast<int>(num + 0.5))

class BezierSpline
{
private:
	std::vector<int> x;
	std::vector<int> y;
	std::vector<int> curve_x;
	std::vector<int> curve_y;
	int LoD;

public:
	BezierSpline();
	~BezierSpline();

public:  // 베지어 곡선 계산을 위한 함수
	float bernoulli_trial(float u, int n, int k);		// 베르누이 독립 시행
	int combination(int n, int k);						// 조합 
	float spline_x(float u, int n);						// 곡선을 그리기 위한 x 좌표 모음
	float spline_y(float u, int n);						// 곡선을 그리기 위한 y 좌표 모음
	void draw_spline(HWND hWnd, HDC hdc, int n);		// 베지어 곡선 그리기
	void line_DDA(HWND hWnd, HDC hdc, int x1, int y1, int x2, int y2);
	
	void set_coord(LPARAM lParam);
	int x_size() { return x.size(); }
	int y_size() { return y.size(); }
	void reset();
};

