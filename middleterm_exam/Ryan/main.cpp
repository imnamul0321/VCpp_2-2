#include <windows.h>
#include "yuhanCG.h"
//
// 메모 2023 / 12 / 8 23:00
//  
// 큐브HRGN
// #include <cmath> 이용
// 
// 큐브 그리는거 까진 성공
// 뷰 영역 설정 creat window로 다시 할려고 싹다 갈아엎음
// 구글링 참고했음
//
// 해야될것
// 
// 큐브 이동 및 크기조정
//  
// 고쳐야될것
// 
// 오래쓰면 팅김
// 아마도 메모리관리 같은데 어딘질 모르겠음
// 
// 
//뷰 색상 RGB 255 240 200
HBRUSH hBrush_background = CreateSolidBrush(RGB(255, 240, 200));
// 흰 배경 브러쉬 RGB 255 255 255
HBRUSH hBrush_background1 = CreateSolidBrush(RGB(255, 255, 255));

// True or False
bool LbuttonPressed = false;
bool SpaceBarPressed = false;
bool LbuttonCube = false;

// 마우스 좌표 초기화
POINT mouse = { 0 };

// 사각형 그리기 작업을 위한 시작점 및 끝점 초기화
POINT startPoint = { 0 };
POINT endPoint = { 0 };

// 직사각형(RECT) 및 원(RECT) 영역 초기화
RECT rectnemo = { 0, 0, 0, 0 };
RECT circle = { 0, 0, 0, 0 };

// 사각형 및 원을 그릴 기본적인 영역(RECT) 초기화
RECT box = { 8, 8, 792, 472 };

// 초기화
POINT noamrlPoint = { 0 };

//큐브 초기화
HRGN cube = NULL;

int move = 0;
int num = 0;

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message) {

	case WM_KEYDOWN:

		if (wParam == VK_SPACE)
		{
			if (SpaceBarPressed == false) {
				SpaceBarPressed = true;
			}

			InvalidateRect(hwnd, NULL, TRUE);
		}
		break;
		 
	case WM_KEYUP:

		if (wParam == VK_SPACE) {
			if (SpaceBarPressed == true) {
				SpaceBarPressed = false;
			}
			InvalidateRect(hwnd, NULL, TRUE);
		}
		break;

	case WM_GETMINMAXINFO: {
		// 클라이언트 영역의 크기
		RECT rect = { 0, 0, 800, 480 }; 
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

		// 윈도우창 조절될때 크기 폭 조정
		// 포인터 이용
		//
		MINMAXINFO* minmax = (MINMAXINFO*)lParam;
		minmax->ptMinTrackSize.x = rect.right - rect.left;
		minmax->ptMinTrackSize.y = rect.bottom - rect.top;
		minmax->ptMaxTrackSize.x = rect.right - rect.left;
		minmax->ptMaxTrackSize.y = rect.bottom - rect.top;
	}
						 return 0;
	case WM_COMMAND:
		// 안해주면 제대로 안지워짐
		if (LOWORD(wParam) == 1) {

			rectnemo = { 0, 0, 0, 0 };
			
			num = 1;
			SetFocus(hwnd);  // 버튼 눌러져있는거 포커스 해제
			InvalidateRect(hwnd, NULL, TRUE); // 그렸던거 지우기
		}
		else if (LOWORD(wParam) == 2) {
			circle = { 0, 0, 0, 0 };
			
			num = 2;
			SetFocus(hwnd);  // 버튼 눌러져있는거 포커스 해제
			InvalidateRect(hwnd, NULL, TRUE); // 그렸던거 지우기
		}
		else if (LOWORD(wParam) == 3) {
			
			num = 3;
			SetFocus(hwnd);  // 버튼 눌러져있는거 포커스 해제
			InvalidateRect(hwnd, NULL, TRUE); // 그렸던거 지우기
		}
		else if (LOWORD(wParam) == 4) {
			startPoint = { 0 };
			endPoint = { 0 };
			num = 4;
			SetFocus(hwnd);  // 버튼 눌러져있는거 포커스 해제
			InvalidateRect(hwnd, NULL, TRUE); // 그렸던거 지우기
		}
		else if (LOWORD(wParam) == 5) {
			startPoint = { 0 };
			endPoint = { 0 };
			num = 5;
			SetFocus(hwnd);  // 버튼 눌러져있는거 포커스 해제
			InvalidateRect(hwnd, NULL, TRUE); // 그렸던거 지우기
		}
		break;

	case WM_PAINT: {

		RECT rect;
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		SelectObject(hdc, hBrush_background);
		Rectangle(hdc, box.left, box.top, box.right, box.bottom);

		EndPaint(hwnd, &ps);
		break;
	}
				 break;

	case WM_DESTROY:

		PostQuitMessage(0);
		break;

	default:

		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK drawingViewWndProc(HWND drawingView, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message) {

	case WM_PAINT: {

		RECT rect;
		GetClientRect(drawingView, &rect);
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(drawingView, &ps);
		FillRect(hdc, &rect, hBrush_background1);

		if (num == 1) {
			Rectangle(hdc, rectnemo.left, rectnemo.top, rectnemo.right, rectnemo.bottom);
		}
		if (num == 2) {
			Ellipse(hdc, circle.left, circle.top, circle.right, circle.bottom);
		}
		if (num == 3) {
			int blink = SpaceBarPressed;
			DrawBonobono(drawingView, hdc, blink);
		}
		if (num == 4) {
			int left = startPoint.x;
			int top = startPoint.y;
			int right = endPoint.x;
			int bottom = endPoint.y;

			DrawRyan(drawingView, hdc, left, top, right, bottom);
		}
		if (num == 5) {
			cube = Drawcube(drawingView, hdc, startPoint, endPoint);
		}

		EndPaint(drawingView, &ps);
		break;
	}
				 break;

	case WM_LBUTTONDOWN: {

		if (PtInRegion(cube, LOWORD(lParam), HIWORD(lParam))) {
			LbuttonCube = true;
		
		}
		else {
			LbuttonPressed = true;
		}	

		//1~5 버튼  좌표받기
		if (num == 1) {

			startPoint.x = LOWORD(lParam);
			startPoint.y = HIWORD(lParam);
		}
		if (num == 2) {
			startPoint.x = LOWORD(lParam);
			startPoint.y = HIWORD(lParam);
		}
		if ( num == 4) {
			startPoint.x = LOWORD(lParam);
			startPoint.y = HIWORD(lParam);
		}
		if (num == 5) {
			if (LbuttonCube == true) {
				noamrlPoint.x = LOWORD(lParam);
				noamrlPoint.y = HIWORD(lParam);
			}
			else {
				startPoint.x = LOWORD(lParam);
				startPoint.y = HIWORD(lParam);
			}
		}

	}break;
		
	case WM_LBUTTONUP: {
		LbuttonPressed = false;
		if (LbuttonCube)
		{
			LbuttonCube = false;
		}
	}break;

	case WM_RBUTTONDOWN:
	{
		//도형 윤곽 판정
		if (PtInRect(&rectnemo, { LOWORD(lParam), HIWORD(lParam) }))
		{
			//사각형 이동
			move = 1;
			startPoint.x = LOWORD(lParam);
			startPoint.y = HIWORD(lParam);
		}

	}
	return 0;

	case WM_RBUTTONUP:
	{
		if (move > 0)
		{
			move = 0;
		}
	}
	return 0;

	case WM_MOUSEMOVE:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(drawingView, &ps);
		POINT currentPoint = { 0 };

		currentPoint.x = LOWORD(lParam);
		currentPoint.y = HIWORD(lParam);

		// 얼마나 벌어졌는디 계산
		int distanseX = 0;
		int distanseY = 0;
		distanseX = currentPoint.x - noamrlPoint.x;
		distanseY = currentPoint.y - noamrlPoint.y;

		if (LbuttonPressed) {
			endPoint.x = LOWORD(lParam);
			endPoint.y = HIWORD(lParam);
			if (num == 1)
			{
				rectnemo = Drawrect(rectnemo, startPoint, endPoint);
			}
			if (num == 2)
			{
				circle = Drawrect(circle, startPoint, endPoint);
			}
			InvalidateRect(drawingView, NULL, TRUE);
		}

		if (move == 1)
		{
			rectnemo = Move_ract(lParam, rectnemo, startPoint);
			circle = Resize_circle(lParam, circle, startPoint);

			int mouseX = LOWORD(lParam);
			int mouseY = HIWORD(lParam);

			startPoint.x = mouseX;
			startPoint.y = mouseY;

			// WM_PAINT 메시지를 유발하여 도형을 화면에 그립니다.
			InvalidateRect(drawingView, NULL, TRUE);
		}
		else if (move == 2) {
			// 큐브 이동
			
			//InvalidateRect(drawingView, NULL, TRUE);
		}

		if (LbuttonCube) {
			
			cube = Drawcube(drawingView, hdc, startPoint, endPoint);
			noamrlPoint = currentPoint;
			InvalidateRect(drawingView, NULL, TRUE);
		}

	}
	return 0;

	default:
		return CallWindowProc(DefWindowProc, drawingView, message, wParam, lParam);
	}
	return 0;
}

// 프로그램 진입점
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
	//버튼 선언
	HWND hButton1, hButton2, hButton3, hButton4, hButton5;

	// 배경 브러시 생성 (RGB 값 255, 240, 200으로 설정)
	HBRUSH hBrush_background = CreateSolidBrush(RGB(255, 240, 200));

	// 윈도우 클래스 구조체 초기화
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);        // 윈도우 클래스 구조체의 크기
	wcex.lpszMenuName = NULL;                // 메뉴 이름
	wcex.lpszClassName = L"ButtonWindowClass";           // 클래스 이름
	wcex.style = CS_HREDRAW | CS_VREDRAW;     // 윈도우 스타일
	wcex.lpfnWndProc = WndProc;               // 윈도우 프로시저 함수
	wcex.cbClsExtra = 0;                      // 클래스의 여분 메모리
	wcex.cbWndExtra = 0;                      // 윈도우의 여분 메모리
	wcex.hInstance = hInstance;               // 인스턴스 핸들
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);    // 아이콘 핸들
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);          // 커서 핸들
	wcex.hbrBackground = (HBRUSH)(hBrush_background);    // 배경 브러시 핸들
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);   // 작은 아이콘 핸들


	if (!RegisterClassEx(&wcex)) {
		return FALSE;
	}

	//뷰 영역 조정
	RECT rect = { 0, 0, 800, 480 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// 윈도우 생성 함수 호출
	HWND hwnd = CreateWindow(
		wcex.lpszClassName,             // 사용할 윈도우 클래스 이름
		TEXT("202207010 임성진"),        // 윈도우 타이틀 텍스트
		WS_OVERLAPPEDWINDOW,            // 윈도우 스타일 (오버랩 윈도우, 최소/최대 버튼, 타이틀 바 포함)
		0, 0,                            // 윈도우의 x, y 좌표 (화면 좌상단 기준)
		width, height,                   // 윈도우의 너비와 높이
		NULL,                            // 부모 윈도우 핸들 (없음)
		NULL,                            // 메뉴 핸들 (없음)
		hInstance,                       // 인스턴스 핸들
		NULL                             // 윈도우를 생성할 때 사용할 데이터 (없음)
	);


	// 드로잉뷰를 위한 윈도우 클래스 구조체 초기화
	WNDCLASSEX wcDrawing;
	wcDrawing.cbSize = sizeof(WNDCLASSEX);        // 윈도우 클래스 구조체의 크기
	wcDrawing.style = CS_HREDRAW | CS_VREDRAW;     // 윈도우 스타일 (가로 및 세로 변경시 다시 그리기)
	wcDrawing.lpfnWndProc = drawingViewWndProc;   // 윈도우 프로시저 함수 설정 (드로잉뷰의 메시지 처리 함수)
	wcDrawing.hIcon = NULL;                        // 아이콘 핸들 (없음)
	wcDrawing.hCursor = LoadCursor(NULL, IDC_CROSS);  // 마우스 커서를 십자가로 설정
	wcDrawing.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));  // 배경 브러시 (흰색)
	wcDrawing.lpszMenuName = NULL;                 // 메뉴 이름 (없음)
	wcDrawing.lpszClassName = L"DrawingViewClass";  // 윈도우 클래스 이름
	wcDrawing.hIconSm = NULL;                       // 작은 아이콘 핸들 (없음)
	wcDrawing.cbClsExtra = 0;                       // 클래스의 여분 메모리
	wcDrawing.cbWndExtra = 0;                       // 윈도우의 여분 메모리
	wcDrawing.hInstance = hInstance;                // 인스턴스 핸들


	RegisterClassEx(&wcDrawing);


	// 드로잉뷰 윈도우 생성 함수 호출
	HWND drawingView = CreateWindow(
		L"DrawingViewClass",   // 드로잉뷰 윈도우 클래스 이름
		L"",                   // 윈도우 타이틀 없음
		WS_CHILD | WS_VISIBLE, // 윈도우 스타일 (자식 윈도우 및 가시성 설정)
		16, 88,                 // 윈도우의 x, y 좌표 (부모 윈도우 내에서의 상대 위치)
		768, 376,               // 윈도우의 너비와 높이
		hwnd,                  // 부모 윈도우 핸들
		NULL,                  // 메뉴 핸들 (없음)
		hInstance,             // 인스턴스 핸들
		NULL                   // 윈도우를 생성할 때 사용할 데이터 (없음)
	);

	// drawingView 윈도우에 사용자 정의 데이터 연결 (예: 부모 윈도우의 핸들)
	SetWindowLongPtr(drawingView, GWLP_USERDATA, (LONG_PTR)hwnd);

	// drawingView 윈도우의 윈도우 프로시저를 drawingViewWndProc로 변경
	SetWindowLongPtr(drawingView, GWLP_WNDPROC, (LONG_PTR)drawingViewWndProc);


	if (!drawingView) {
		return -1;
	}

	if (!hwnd) {
		return FALSE;
	}

	// 드로우 영역 전면 갈아 엎음
	// 새로 만들기 예정 
	

	//버튼 1 ~ 5
	hButton1 = CreateWindow(
		L"BUTTON", L"Box", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		16, 16, 140, 64, hwnd, (HMENU)1, hInstance, NULL);

	hButton2 = CreateWindow(
		L"BUTTON", L"Circle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		172, 16, 140, 64, hwnd, (HMENU)2, hInstance, NULL);

	hButton3 = CreateWindow(
		L"BUTTON", L"Bonobono", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		328, 16, 140, 64, hwnd, (HMENU)3, hInstance, NULL);

	hButton4 = CreateWindow(
		L"BUTTON", L"Ryan", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		484, 16, 140, 64, hwnd, (HMENU)4, hInstance, NULL);

	hButton5 = CreateWindow(
		L"BUTTON", L"Cube", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		640, 16, 140, 64, hwnd, (HMENU)5, hInstance, NULL);

	//없으면 안나옴
	ShowWindow(hwnd, nCmdShow); 
	UpdateWindow(hwnd);


	//메시지 루프
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}