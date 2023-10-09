//#ifdef UNICODE
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
//#else
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
//#endif

#include <windows.h>

POINT startPoint = { 0 };
POINT endPoint = { 0 };

int isMouseLButtonPressed = 0;


RECT selectedRect = { 0 };

long xStart = 0;
long yStart = 0;

long xEnd = 0;
long yEnd = 0;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static RECT prevRect = { 0 }; // ������ �׸� �簢���� �����ϱ� ���� RECT ����ü

	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
	{
		xStart = LOWORD(lParam);
		yStart = HIWORD(lParam);
		isMouseLButtonPressed = 1;
	}
	break;

	case WM_MOUSEMOVE:
	{
		if (isMouseLButtonPressed)
		{
			endPoint.x = LOWORD(lParam);
			endPoint.y = HIWORD(lParam);

			HDC hdc = GetDC(hwnd);
			RECT rect = { xStart, yStart, endPoint.x, endPoint.y };
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));

			if (hBrush == NULL)
			{
				MessageBox(NULL, L"CreateSolidBrush failed!", L"Error", MB_ICONERROR);
				exit(-1);
			}

			// ���� �簢���� Ŭ�����ϰ� ���� �簢������ �׸�
			FillRect(hdc, &prevRect, (HBRUSH)GetStockObject(WHITE_BRUSH));
			FillRect(hdc, &rect, hBrush);

			ReleaseDC(hwnd, hdc);

			// ���� �簢���� ���� �簢������ ����
			prevRect = rect;
		}
	}
	break;

	case WM_LBUTTONUP:
	{
		isMouseLButtonPressed = 0;
		xEnd = LOWORD(lParam);
		yEnd = HIWORD(lParam);
	}
	break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		// ���� �簢���� �׸�
		if (!isMouseLButtonPressed)
		{
			FillRect(hdc, &prevRect, (HBRUSH)GetStockObject(WHITE_BRUSH));
		}

		EndPaint(hwnd, &ps);
	}
	break;

	case WM_RBUTTONDOWN:
	{

		
	}

	case WM_RBUTTONUP:
	{
		
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
	/* ������ Ŭ���� ����.*/
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));	// ��� 0���� �ʱ�ȭ.

	// ������ Ŭ���� �� ����
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT("Computer Software");
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;

	// ������ Ŭ���� ���.
	if (RegisterClass(&wc) == 0)
	{
		MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
		exit(-1);	//����
	}

	// Window viewport ���� ����
	RECT rect = { 150, 100, 800, 600 }; // 800 * 600
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// ������ ����
	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		TEXT("202207010 �Ӽ���"),
		WS_OVERLAPPEDWINDOW,
		0, 0,
		width, height,
		NULL, NULL,
		hInstance,
		NULL
	);

	// ���� �˻�.
	if (hwnd == NULL)
	{
		MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
		exit(-1);
	}

	// â ���̱�.
	ShowWindow(hwnd, SW_SHOW); // â ����
	UpdateWindow(hwnd); // ������Ʈ�ؾ� ����. �� ������ ���ٰ� ���� ��.



	// �޽��� ó�� ����.
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		// �޽��� ó��.
		if (GetMessage(&msg, hwnd, 0, 0))
			//if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) // PM_REMOVE�� �ڸ��� �� �޼����� ���� ��Ұų�.�� �ǹ��ε� ����ٴ� ����.
		{

			// �޽��� �ؼ�����.
			TranslateMessage(&msg);
			// �޽����� ó���ؾ��� ���� ��������.
			DispatchMessage(&msg);

		}
		/*else
		{

		}*/
	}

	//���� �޽��� ������
	return (int)msg.wParam;

}