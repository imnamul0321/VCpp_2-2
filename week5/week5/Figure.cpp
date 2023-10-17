//#ifdef UNICODE
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
//#else
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
//#endif

#include <windows.h>
#include <iostream>
//시작, 끝 점 왼
POINT LstartPoint = { 0 };
POINT LendPoint = { 0 };
//시작, 끝 점 오
POINT RstartPoint = { 0 };
POINT RendPoint = { 0 };

////마우스 커서 위치 받는 함수  bool형식임 long
//void GetMouseCursorPosition(HWND hwnd, int* x, int* y)
//{
//	POINT cursorPos;
//	//GetCursorPos(&cursorPos);	//화면 상의 위치
//	ScreenToClient(hwnd, &cursorPos);	//클라이언트 영역의 좌표
//	const int x = cursorPos.x;
//	const int y = cursorPos.y;
//}


//버튼 초기화
//L
int isMouseLButtonPressed = 0;
//R
int isMouseRButtonPressed = 0;



LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static RECT prevRect = { 0 }; // 이전에 그린 사각형을 저장하기 위한 RECT 구조체

	switch (uMsg)
	{

	case WM_GETMINMAXINFO: //창 크기 고정
	{
		MINMAXINFO* lpMMI = (MINMAXINFO*)lParam;
		lpMMI->ptMinTrackSize.x = 800;
		lpMMI->ptMinTrackSize.y = 600;
		lpMMI->ptMaxTrackSize.x = 800;
		lpMMI->ptMaxTrackSize.y = 600;
	}
	break;

	//왼클릭
	case WM_LBUTTONDOWN:
	{
		LstartPoint.x = LOWORD(lParam);
		LstartPoint.y = HIWORD(lParam);
		isMouseLButtonPressed = 1;
	}
	break;

	//우클릭
	case WM_RBUTTONDOWN:
	{
		RstartPoint.x = LOWORD(lParam);
		RstartPoint.y = HIWORD(lParam);

		isMouseRButtonPressed = 1;
	}
	break;

	case WM_MOUSEMOVE:
	{

		//R 커서 움직인만큼 더해주기
		if (isMouseRButtonPressed) {
			
			RendPoint.x = LOWORD(lParam);
			RendPoint.y = HIWORD(lParam);

			//마우스 좌표가 사각형안에있을때 실행
			if (RstartPoint.x >= LstartPoint.x && RendPoint.x <= LendPoint.x && RstartPoint.y >= LstartPoint.y && RendPoint.x <= LendPoint.y)
			{
				
				int result_x = 0;
				int result_y = 0;

				//움직인 거리 구하기
				// 
				//계산
				result_x = RendPoint.x - RstartPoint.x;
				result_y = RendPoint.y - RstartPoint.y;

				LstartPoint.x += result_x;
				LstartPoint.y += result_y;
				LendPoint.x += result_x;
				LendPoint.y += result_y;
				//다시 초기화 안해주면 처음값 다시받아서 움직일수록 더멀리감
				RstartPoint.x = RendPoint.x;
				RstartPoint.y = RendPoint.y;




				HDC hdc = GetDC(hwnd);
				RECT rect = { LstartPoint.x, LstartPoint.y, LendPoint.x, LendPoint.y };
				HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));

				if (hBrush == NULL)
				{
					MessageBox(NULL, L"CreateSolidBrush failed!", L"Error", MB_ICONERROR);
					exit(-1);
				}

				// 이전 사각형을 클리어하고 현재 사각형만을 그림
				FillRect(hdc, &prevRect, (HBRUSH)GetStockObject(WHITE_BRUSH));
				FillRect(hdc, &rect, hBrush);

				ReleaseDC(hwnd, hdc);

				// 현재 사각형을 이전 사각형으로 저장
				prevRect = rect;
			}
		}

			//L
		if (isMouseLButtonPressed)
		{
			
			LendPoint.x = LOWORD(lParam);
			LendPoint.y = HIWORD(lParam);

			HDC hdc = GetDC(hwnd);
			RECT rect = { LstartPoint.x, LstartPoint.y, LendPoint.x, LendPoint.y };
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));

			if (hBrush == NULL)
			{
				MessageBox(NULL, L"CreateSolidBrush failed!", L"Error", MB_ICONERROR);
				exit(-1);
			}

			// 이전 사각형을 클리어하고 현재 사각형만을 그림
			FillRect(hdc, &prevRect, (HBRUSH)GetStockObject(WHITE_BRUSH));
			FillRect(hdc, &rect, hBrush);

			ReleaseDC(hwnd, hdc);

			// 현재 사각형을 이전 사각형으로 저장
			prevRect = rect;
		}
	}
	break;
	//좌클릭 땔때
	case WM_LBUTTONUP:
	{
		isMouseLButtonPressed = 0;
		//LendPoint.x = LOWORD(lParam);
		//LendPoint.y = HIWORD(lParam);

	}
	break;
	//우클릭 땔때
	case WM_RBUTTONUP: //블럭 다시 그리기
	{
		isMouseRButtonPressed = 0;
	}
	break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		// 현재 사각형을 그림
		if (!isMouseLButtonPressed)
		{
			FillRect(hdc, &prevRect, (HBRUSH)GetStockObject(WHITE_BRUSH));
		}

		EndPaint(hwnd, &ps);
	}
	break;

	

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return S_OK;
}
#ifdef UNICODE
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
#else
int WINAPI Win




(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
#endif
{
	/* 윈도우 클래스 선언.*/
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));	// 모두 0으로 초기화.

	// 윈도우 클래스 값 설정
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT("Computer Software");
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;

	// 윈도우 클래스 등록.
	if (RegisterClass(&wc) == 0)
	{
		MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
		exit(-1);	//예외
	}

	// Window viewport 영역 조정
	RECT rect = { 150, 100, 800, 600 }; // 800 * 600
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// 윈도우 생성
	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		TEXT("202207010 임성진"),
		WS_OVERLAPPEDWINDOW,
		0, 0,
		width, height,
		NULL, NULL,
		hInstance,
		NULL
	);

	// 오류 검사.
	if (hwnd == NULL)
	{
		MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
		exit(-1);
	}

	// 창 보이기.
	ShowWindow(hwnd, SW_SHOW); // 창 띄우고
	UpdateWindow(hwnd); // 업데이트해야 보임. 한 쌍으로 쓴다고 보면 됨.



	// 메시지 처리 루프.
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		// 메시지 처리.
		if (GetMessage(&msg, hwnd, 0, 0))
			//if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) // PM_REMOVE의 자리는 이 메세지를 쓰고 어떡할거냐.의 의미인데 지운다는 것임.
		{

			// 메시지 해석해줘.
			TranslateMessage(&msg);
			// 메시지를 처리해야할 곳에 전달해줘.
			DispatchMessage(&msg);

		}
		/*else
		{

		}*/
	}

	//종료 메시지 보내기
	return (int)msg.wParam;

}