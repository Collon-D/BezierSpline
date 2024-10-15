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

public:  // ������ � ����� ���� �Լ�
	float bernoulli_trial(float u, int n, int k);		// �������� ���� ����
	int combination(int n, int k);						// ���� 
	float spline_x(float u, int n);						// ��� �׸��� ���� x ��ǥ ����
	float spline_y(float u, int n);						// ��� �׸��� ���� y ��ǥ ����
	void draw_spline(HWND hWnd, HDC hdc, int n);		// ������ � �׸���
	void line_DDA(HWND hWnd, HDC hdc, int x1, int y1, int x2, int y2);
	
	void set_coord(LPARAM lParam);
	int x_size() { return x.size(); }
	int y_size() { return y.size(); }
	void reset();
};

