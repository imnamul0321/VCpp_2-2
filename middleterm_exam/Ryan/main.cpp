#include <windows.h>
#include "yuhanCG.h"
//
// �޸� 2023 / 12 / 8 23:00
//  
// ť��HRGN
// #include <cmath> �̿�
// 
// ť�� �׸��°� ���� ����
// �� ���� ���� creat window�� �ٽ� �ҷ��� �ϴ� ���ƾ���
// ���۸� ��������
//
// �ؾߵɰ�
// 
// ť�� �̵� �� ũ������
//  
// ���ľߵɰ�
// 
// �������� �ñ�
// �Ƹ��� �޸𸮰��� ������ ����� �𸣰���
// 
// 
//�� ���� RGB 255 240 200
HBRUSH hBrush_background = CreateSolidBrush(RGB(255, 240, 200));
// �� ��� �귯�� RGB 255 255 255
HBRUSH hBrush_background1 = CreateSolidBrush(RGB(255, 255, 255));

// True or False
bool LbuttonPressed = false;
bool SpaceBarPressed = false;
bool LbuttonCube = false;

// ���콺 ��ǥ �ʱ�ȭ
POINT mouse = { 0 };

// �簢�� �׸��� �۾��� ���� ������ �� ���� �ʱ�ȭ
POINT startPoint = { 0 };
POINT endPoint = { 0 };

// ���簢��(RECT) �� ��(RECT) ���� �ʱ�ȭ
RECT rectnemo = { 0, 0, 0, 0 };
RECT circle = { 0, 0, 0, 0 };

// �簢�� �� ���� �׸� �⺻���� ����(RECT) �ʱ�ȭ
RECT box = { 8, 8, 792, 472 };

// �ʱ�ȭ
POINT noamrlPoint = { 0 };

//ť�� �ʱ�ȭ
HRGN cube = NULL;

int move = 0;
int num = 0;

// ������ ���ν���
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
		// Ŭ���̾�Ʈ ������ ũ��
		RECT rect = { 0, 0, 800, 480 }; 
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

		// ������â �����ɶ� ũ�� �� ����
		// ������ �̿�
		//
		MINMAXINFO* minmax = (MINMAXINFO*)lParam;
		minmax->ptMinTrackSize.x = rect.right - rect.left;
		minmax->ptMinTrackSize.y = rect.bottom - rect.top;
		minmax->ptMaxTrackSize.x = rect.right - rect.left;
		minmax->ptMaxTrackSize.y = rect.bottom - rect.top;
	}
						 return 0;
	case WM_COMMAND:
		// �����ָ� ����� ��������
		if (LOWORD(wParam) == 1) {

			rectnemo = { 0, 0, 0, 0 };
			
			num = 1;
			SetFocus(hwnd);  // ��ư �������ִ°� ��Ŀ�� ����
			InvalidateRect(hwnd, NULL, TRUE); // �׷ȴ��� �����
		}
		else if (LOWORD(wParam) == 2) {
			circle = { 0, 0, 0, 0 };
			
			num = 2;
			SetFocus(hwnd);  // ��ư �������ִ°� ��Ŀ�� ����
			InvalidateRect(hwnd, NULL, TRUE); // �׷ȴ��� �����
		}
		else if (LOWORD(wParam) == 3) {
			
			num = 3;
			SetFocus(hwnd);  // ��ư �������ִ°� ��Ŀ�� ����
			InvalidateRect(hwnd, NULL, TRUE); // �׷ȴ��� �����
		}
		else if (LOWORD(wParam) == 4) {
			startPoint = { 0 };
			endPoint = { 0 };
			num = 4;
			SetFocus(hwnd);  // ��ư �������ִ°� ��Ŀ�� ����
			InvalidateRect(hwnd, NULL, TRUE); // �׷ȴ��� �����
		}
		else if (LOWORD(wParam) == 5) {
			startPoint = { 0 };
			endPoint = { 0 };
			num = 5;
			SetFocus(hwnd);  // ��ư �������ִ°� ��Ŀ�� ����
			InvalidateRect(hwnd, NULL, TRUE); // �׷ȴ��� �����
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

		//1~5 ��ư  ��ǥ�ޱ�
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
		//���� ���� ����
		if (PtInRect(&rectnemo, { LOWORD(lParam), HIWORD(lParam) }))
		{
			//�簢�� �̵�
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

		// �󸶳� �������µ� ���
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

			// WM_PAINT �޽����� �����Ͽ� ������ ȭ�鿡 �׸��ϴ�.
			InvalidateRect(drawingView, NULL, TRUE);
		}
		else if (move == 2) {
			// ť�� �̵�
			
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

// ���α׷� ������
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
	//��ư ����
	HWND hButton1, hButton2, hButton3, hButton4, hButton5;

	// ��� �귯�� ���� (RGB �� 255, 240, 200���� ����)
	HBRUSH hBrush_background = CreateSolidBrush(RGB(255, 240, 200));

	// ������ Ŭ���� ����ü �ʱ�ȭ
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);        // ������ Ŭ���� ����ü�� ũ��
	wcex.lpszMenuName = NULL;                // �޴� �̸�
	wcex.lpszClassName = L"ButtonWindowClass";           // Ŭ���� �̸�
	wcex.style = CS_HREDRAW | CS_VREDRAW;     // ������ ��Ÿ��
	wcex.lpfnWndProc = WndProc;               // ������ ���ν��� �Լ�
	wcex.cbClsExtra = 0;                      // Ŭ������ ���� �޸�
	wcex.cbWndExtra = 0;                      // �������� ���� �޸�
	wcex.hInstance = hInstance;               // �ν��Ͻ� �ڵ�
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);    // ������ �ڵ�
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);          // Ŀ�� �ڵ�
	wcex.hbrBackground = (HBRUSH)(hBrush_background);    // ��� �귯�� �ڵ�
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);   // ���� ������ �ڵ�


	if (!RegisterClassEx(&wcex)) {
		return FALSE;
	}

	//�� ���� ����
	RECT rect = { 0, 0, 800, 480 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// ������ ���� �Լ� ȣ��
	HWND hwnd = CreateWindow(
		wcex.lpszClassName,             // ����� ������ Ŭ���� �̸�
		TEXT("202207010 �Ӽ���"),        // ������ Ÿ��Ʋ �ؽ�Ʈ
		WS_OVERLAPPEDWINDOW,            // ������ ��Ÿ�� (������ ������, �ּ�/�ִ� ��ư, Ÿ��Ʋ �� ����)
		0, 0,                            // �������� x, y ��ǥ (ȭ�� �»�� ����)
		width, height,                   // �������� �ʺ�� ����
		NULL,                            // �θ� ������ �ڵ� (����)
		NULL,                            // �޴� �ڵ� (����)
		hInstance,                       // �ν��Ͻ� �ڵ�
		NULL                             // �����츦 ������ �� ����� ������ (����)
	);


	// ����׺並 ���� ������ Ŭ���� ����ü �ʱ�ȭ
	WNDCLASSEX wcDrawing;
	wcDrawing.cbSize = sizeof(WNDCLASSEX);        // ������ Ŭ���� ����ü�� ũ��
	wcDrawing.style = CS_HREDRAW | CS_VREDRAW;     // ������ ��Ÿ�� (���� �� ���� ����� �ٽ� �׸���)
	wcDrawing.lpfnWndProc = drawingViewWndProc;   // ������ ���ν��� �Լ� ���� (����׺��� �޽��� ó�� �Լ�)
	wcDrawing.hIcon = NULL;                        // ������ �ڵ� (����)
	wcDrawing.hCursor = LoadCursor(NULL, IDC_CROSS);  // ���콺 Ŀ���� ���ڰ��� ����
	wcDrawing.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));  // ��� �귯�� (���)
	wcDrawing.lpszMenuName = NULL;                 // �޴� �̸� (����)
	wcDrawing.lpszClassName = L"DrawingViewClass";  // ������ Ŭ���� �̸�
	wcDrawing.hIconSm = NULL;                       // ���� ������ �ڵ� (����)
	wcDrawing.cbClsExtra = 0;                       // Ŭ������ ���� �޸�
	wcDrawing.cbWndExtra = 0;                       // �������� ���� �޸�
	wcDrawing.hInstance = hInstance;                // �ν��Ͻ� �ڵ�


	RegisterClassEx(&wcDrawing);


	// ����׺� ������ ���� �Լ� ȣ��
	HWND drawingView = CreateWindow(
		L"DrawingViewClass",   // ����׺� ������ Ŭ���� �̸�
		L"",                   // ������ Ÿ��Ʋ ����
		WS_CHILD | WS_VISIBLE, // ������ ��Ÿ�� (�ڽ� ������ �� ���ü� ����)
		16, 88,                 // �������� x, y ��ǥ (�θ� ������ �������� ��� ��ġ)
		768, 376,               // �������� �ʺ�� ����
		hwnd,                  // �θ� ������ �ڵ�
		NULL,                  // �޴� �ڵ� (����)
		hInstance,             // �ν��Ͻ� �ڵ�
		NULL                   // �����츦 ������ �� ����� ������ (����)
	);

	// drawingView �����쿡 ����� ���� ������ ���� (��: �θ� �������� �ڵ�)
	SetWindowLongPtr(drawingView, GWLP_USERDATA, (LONG_PTR)hwnd);

	// drawingView �������� ������ ���ν����� drawingViewWndProc�� ����
	SetWindowLongPtr(drawingView, GWLP_WNDPROC, (LONG_PTR)drawingViewWndProc);


	if (!drawingView) {
		return -1;
	}

	if (!hwnd) {
		return FALSE;
	}

	// ��ο� ���� ���� ���� ����
	// ���� ����� ���� 
	

	//��ư 1 ~ 5
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

	//������ �ȳ���
	ShowWindow(hwnd, nCmdShow); 
	UpdateWindow(hwnd);


	//�޽��� ����
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}