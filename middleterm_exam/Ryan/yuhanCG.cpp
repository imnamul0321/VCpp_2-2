#include "yuhanCG.h"
#include <Windows.h>
#include <cmath>

//기본브러쉬
// 검정
HBRUSH hBrush_Black = CreateSolidBrush(RGB(0, 0, 0));
// 흰색
HBRUSH hBrush_White = CreateSolidBrush(RGB(255, 255, 255));

//라이언용 브러쉬
HBRUSH hBrush_RyanFace = CreateSolidBrush(RGB(255, 200, 15));

//보노보노용 브러쉬 파랑, 핑크
HBRUSH hBrush_BNFace = CreateSolidBrush(RGB(127, 200, 255));
HBRUSH hBrush_BNTung = CreateSolidBrush(RGB(255, 150, 255));

//사각형 그리기
RECT Drawrect(RECT rect, POINT startPoint, POINT endPoint) {
	//위치받기
	rect.left = min(startPoint.x, endPoint.x);
	rect.top = min(startPoint.y, endPoint.y);
	rect.right = max(startPoint.x, endPoint.x);
	rect.bottom = max(startPoint.y, endPoint.y);

	return rect;
}

//사각형 옮기기
RECT Move_ract(LPARAM lParam, RECT rectnemo, POINT start) {
	//위치 받기
	int mouseX = LOWORD(lParam);
	int mouseY = HIWORD(lParam);

	// 위치 가산
	int deltaX = mouseX - start.x;
	int deltaY = mouseY - start.y;

	// 사각형 이동
	rectnemo.left += deltaX;
	rectnemo.top += deltaY;
	rectnemo.right += deltaX;
	rectnemo.bottom += deltaY;

	return rectnemo;
}

//원 크기 조절
RECT Resize_circle(LPARAM lParam, RECT circle, POINT start) {
	//위치 받기
	int mouseX = LOWORD(lParam);
	int mouseY = HIWORD(lParam);

	//위치 가산
	int deltaX = mouseX - start.x;
	int deltaY = mouseY - start.y;
	double scaleFactor = 1;
	
	if (deltaX > 0) {
		// 오른쪽 이동 크기 +
		//static_cast<double> 
		scaleFactor = 1.0 + static_cast<double>(deltaX) / 100.0;  
	}
	else if (deltaX < 0) {
		// 왼쪽 이동 크기 -
		scaleFactor = 1.0 / (1.0 - static_cast<double>(deltaX) / 100.0); 
	}
	else {
		// 이동x 크기변화x
		scaleFactor = 1.0; 
	}
	int width = circle.right - circle.left;
	int height = circle.bottom - circle.top;
	int centerX = circle.left + width / 2;
	int centerY = circle.top + height / 2;

	width = static_cast<int>(width * scaleFactor);
	height = static_cast<int>(height * scaleFactor);

	circle.left = centerX - width / 2;
	circle.top = centerY - height / 2;
	circle.right = circle.left + width;
	circle.bottom = circle.top + height;
	return circle;
}

//보노보노 그리기
void DrawBonobono(HWND drawingView, HDC hdc, int blink) {
	if (blink == 0) {
		//눈 뜬거 보통상태
		PAINTSTRUCT ps;
		//검정
		HBRUSH hBrush_Black = CreateSolidBrush(RGB(0, 0, 0));
		// 흰색
		HBRUSH hBrush_White = CreateSolidBrush(RGB(255, 255, 255));

		// 피부색 (스포이드로 뽑아옴)
		HBRUSH hBrush_BNFace = CreateSolidBrush(RGB(127, 200, 255));

		SelectObject(hdc, hBrush_BNFace);
		//얼굴 
		Ellipse(hdc, 212, 24, 544, 364); 


		// 핑크색
		HBRUSH hBrush_BNTung = CreateSolidBrush(RGB(255, 150, 255));
		SelectObject(hdc, hBrush_BNTung);
		Ellipse(hdc, 356, 182, 398, 305);

		// 흰 코 부분
		
		SelectObject(hdc, hBrush_White);
		Ellipse(hdc, 329, 197, 379, 237);
		Ellipse(hdc, 379, 197, 427, 237);

		// 눈 부분
		
		SelectObject(hdc, hBrush_Black);
		Ellipse(hdc, 259, 157, 269, 177);
		Ellipse(hdc, 499, 157, 489, 177);

		//코 
		Ellipse(hdc, 359, 177, 399, 217);

		//흰자
		SelectObject(hdc, hBrush_White);
		Ellipse(hdc, 261, 162, 269, 167);
		Ellipse(hdc, 490, 162, 499, 167);

		//수염 1 
		MoveToEx(hdc, 349, 212, NULL);
		LineTo(hdc, 319, 197);
		//수염 2
		MoveToEx(hdc, 409, 212, NULL);
		LineTo(hdc, 439, 197);
		//수염 3
		MoveToEx(hdc, 349, 222, NULL);
		LineTo(hdc, 319, 237);
		//수염 4
		MoveToEx(hdc, 409, 222, NULL);
		LineTo(hdc, 439, 237);

		//지우기
		DeleteObject(hBrush_Black);
		DeleteObject(hBrush_White);
		DeleteObject(hBrush_BNFace);
		DeleteObject(hBrush_BNTung);

		EndPaint(drawingView, &ps);
	}
	else if (blink == 1) {
		
		PAINTSTRUCT ps;
		
		HBRUSH hBrush_BNFace = CreateSolidBrush(RGB(127, 200, 255));
		SelectObject(hdc, hBrush_BNFace);
		//얼굴 
		Ellipse(hdc, 212, 24, 544, 364);
		
		// 핑크색
		HBRUSH hBrush_BNTung = CreateSolidBrush(RGB(255, 150, 255));
		SelectObject(hdc, hBrush_BNTung);
		Ellipse(hdc, 356, 182, 398, 305);

		HBRUSH hBrush_White = CreateSolidBrush(RGB(255, 255, 255));
		SelectObject(hdc, hBrush_White);
		Ellipse(hdc, 329, 197, 379, 237);
		Ellipse(hdc, 379, 197, 427, 237);

		MoveToEx(hdc, 263, 161, NULL);
		LineTo(hdc, 248, 151);
		MoveToEx(hdc, 263, 161, NULL);
		LineTo(hdc, 248, 171);
		
		MoveToEx(hdc, 493, 161, NULL);
		LineTo(hdc, 508, 151);
		MoveToEx(hdc, 493, 161, NULL);
		LineTo(hdc, 508, 171);
		
		HBRUSH hBrush_Black = CreateSolidBrush(RGB(0, 0, 0));
		SelectObject(hdc, hBrush_Black);
		Ellipse(hdc, 358, 176, 398, 216);
				
		MoveToEx(hdc, 348, 211, NULL);
		LineTo(hdc, 318, 196);

		MoveToEx(hdc, 408, 211, NULL);
		LineTo(hdc, 438, 196);

		MoveToEx(hdc, 348, 221, NULL);
		LineTo(hdc, 318, 236);

		MoveToEx(hdc, 408, 221, NULL);
		LineTo(hdc, 438, 236);
		
		DeleteObject(hBrush_BNFace);
		DeleteObject(hBrush_BNTung);
		DeleteObject(hBrush_Black);
		DeleteObject(hBrush_White);

		EndPaint(drawingView, &ps);
	}
}

//라이언 그리기
void DrawRyan(HWND drawingView, HDC hdc, int left, int top, int right, int bottom) {
	{
		int startPointX = left;
		int startPointY = top;
		int endPointX = right;
		int endPointY = bottom;
	
		POINT MINPOINT = { 0 };
		POINT MAXPOINT = { 0 };

		// 얼굴
		MINPOINT.x = min(startPointX, endPointX);
		MINPOINT.y = min(startPointY, endPointY);
		MAXPOINT.x = max(startPointX, endPointX);
		MAXPOINT.y = max(startPointY, endPointY);

		RECT face = { MINPOINT.x, MINPOINT.y,MAXPOINT.x,MAXPOINT.y };
		//ads 절대값
		int width = abs(MINPOINT.x - MAXPOINT.x);
		int height = abs(MINPOINT.y - MAXPOINT.y);
		int centerX = width / 2;
		int centerY = height / 2;

		POINT centerPoint = { MINPOINT.x + centerX, MINPOINT.y + centerY };

		// 피부색 (스포이드 뽑아옴)
		HBRUSH hBrush_RyanFace = CreateSolidBrush(RGB(255, 200, 15));
		SelectObject(hdc, hBrush_RyanFace);

		// 귀
		RECT lear = { MINPOINT.x , MINPOINT.y, MINPOINT.x + width / 3, MINPOINT.y + height / 3 };
		RECT rear = { MAXPOINT.x , MINPOINT.y, MAXPOINT.x - width / 3, MINPOINT.y + height / 3 };

		// 왼 귀
		Ellipse(hdc, lear.left, lear.top, lear.right, lear.bottom);
		// 오 귀
		Ellipse(hdc, rear.left, rear.top, rear.right, rear.bottom);
		// 얼굴
		Ellipse(hdc, face.left, face.top, face.right, face.bottom);

		POINT leye1 = { MINPOINT.x + centerX / 2, MINPOINT.y + (centerY / 6 * 5) };
		POINT reye1 = { MAXPOINT.x - centerX / 2, MINPOINT.y + (centerY / 6 * 5) };
		RECT leyes2 = { leye1.x, leye1.y, leye1.x + width / 20, leye1.y + height / 20 };
		RECT reyes2 = { reye1.x, reye1.y, reye1.x - width / 20, reye1.y + height / 20 };

		// 눈
		HBRUSH hBrush_Black = CreateSolidBrush(RGB(0, 0, 0));
		
		SelectObject(hdc, hBrush_Black);
		Ellipse(hdc, leyes2.left, leyes2.top, leyes2.right, leyes2.bottom);
		Ellipse(hdc, reyes2.left, reyes2.top, reyes2.right, reyes2.bottom);

		// 눈썹 왼 1
		MoveToEx(hdc, MINPOINT.x + centerX / 4, MINPOINT.y + centerY / 3 * 2, NULL);
		LineTo(hdc, MINPOINT.x + (centerX / 4 * 3), MINPOINT.y + (centerY / 3 * 2));
		// 눈썹 왼 2
		MoveToEx(hdc, MINPOINT.x + centerX / 4, MINPOINT.y + centerY / 3 * 2 + 2, NULL);
		LineTo(hdc, MINPOINT.x + (centerX / 4 * 3), MINPOINT.y + (centerY / 3 * 2) + 2);
		// 눈썹 왼 3
		MoveToEx(hdc, MINPOINT.x + centerX / 4, MINPOINT.y + centerY / 3 * 2 + 4, NULL);
		LineTo(hdc, MINPOINT.x + (centerX / 4 * 3), MINPOINT.y + (centerY / 3 * 2) + 4);
		// 눈썹 오 1
		MoveToEx(hdc, MAXPOINT.x - centerX / 4, MINPOINT.y + centerY / 3 * 2, NULL);
		LineTo(hdc, MAXPOINT.x - (centerX / 4 * 3), MINPOINT.y + (centerY / 3 * 2));
		// 눈썹 오 2
		MoveToEx(hdc, MAXPOINT.x - centerX / 4, MINPOINT.y + centerY / 3 * 2 + 2, NULL);
		LineTo(hdc, MAXPOINT.x - (centerX / 4 * 3), MINPOINT.y + (centerY / 3 * 2) + 2);
		// 눈썹 오 3
		MoveToEx(hdc, MAXPOINT.x - centerX / 4, MINPOINT.y + centerY / 3 * 2 + 4, NULL);
		LineTo(hdc, MAXPOINT.x - (centerX / 4 * 3), MINPOINT.y + (centerY / 3 * 2) + 4);

		// 코
		RECT lnose = { centerPoint.x - centerX / 5, centerPoint.y, centerPoint.x, centerPoint.y + centerY / 5 };
		RECT rnose = { centerPoint.x, centerPoint.y, centerPoint.x + centerX / 5, centerPoint.y + centerY / 5 };

		HBRUSH hBrush_White = CreateSolidBrush(RGB(255, 255, 255));
		SelectObject(hdc, hBrush_White);
		Ellipse(hdc, lnose.left, lnose.top, lnose.right, lnose.bottom);
		Ellipse(hdc, rnose.left, rnose.top, rnose.right, rnose.bottom);
		
		DeleteObject(hBrush_RyanFace);
		DeleteObject(hBrush_White);
		DeleteObject(hBrush_Black);

	}
}

//큐브 그리기
HRGN Drawcube(HWND hWnd, HDC hdc, POINT startPoint, POINT endPoint) {
	//abs 절대값, 길이 구하기 
	int width = abs(startPoint.x - endPoint.x);
	int height = abs(startPoint.y - endPoint.y);
	//중심 구하기
	int centerX = width / 2;
	int centerY = height / 2;

	POINT MINPOINT = { 0 };
	POINT MAXPOINT = { 0 };
	//좌표저장
	MINPOINT.x = min(startPoint.x, endPoint.x);
	MINPOINT.y = min(startPoint.y, endPoint.y);
	MAXPOINT.x = max(startPoint.x, endPoint.x);
	MAXPOINT.y = max(startPoint.y, endPoint.y);

	POINT centerPoint = { MINPOINT.x + centerX, MINPOINT.y + centerY };

		MoveToEx(hdc, MINPOINT.x, MAXPOINT.y, NULL); 
		LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y);
		LineTo(hdc, MAXPOINT.x, MAXPOINT.y - centerY / 2);
		LineTo(hdc, MINPOINT.x + centerX / 2, MAXPOINT.y - centerY / 2);
		LineTo(hdc, MINPOINT.x, MAXPOINT.y);

		MoveToEx(hdc, MAXPOINT.x, MAXPOINT.y - centerY / 2, NULL); 
		LineTo(hdc, MAXPOINT.x, MINPOINT.y);
		LineTo(hdc, MINPOINT.x + centerX / 2, MINPOINT.y);
		LineTo(hdc, MINPOINT.x + centerX / 2, MAXPOINT.y - centerY / 2);

		MoveToEx(hdc, MINPOINT.x + centerX / 2, MINPOINT.y, NULL);
		LineTo(hdc, MINPOINT.x, MINPOINT.y + centerY / 2);
		LineTo(hdc, MINPOINT.x, MAXPOINT.y);

		POINT cubearray[6] = {
		   {MINPOINT.x, MAXPOINT.y},
		   {MAXPOINT.x - centerX / 2, MAXPOINT.y},
		   {MAXPOINT.x, MAXPOINT.y - centerY / 2},
		   {MAXPOINT.x, MINPOINT.y},
		   {MINPOINT.x + centerX / 2, MINPOINT.y},
		   {MINPOINT.x, MINPOINT.y + centerY / 2}
		};
		HRGN cube_p = CreatePolygonRgn(cubearray, 6, WINDING);
		return cube_p;
	}
	