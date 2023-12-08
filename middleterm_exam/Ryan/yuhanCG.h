#pragma once
#include <Windows.h>
#include <cmath>
RECT Drawrect(RECT rect, POINT startPoint, POINT endPoint);

RECT Move_ract(LPARAM lParam, RECT ractangles, POINT start);

RECT Resize_circle(LPARAM lParam, RECT Ellipse, POINT start);

void DrawBonobono(HWND hWnd, HDC hdc, int blink);

void DrawRyan(HWND hWnd, HDC hdc, int left, int top, int right, int bottom);

HRGN Drawcube(HWND hWnd, HDC hdc, POINT MINPOINT, POINT MAXPOINT);


