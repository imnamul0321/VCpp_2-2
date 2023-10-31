#include <windows.h>

HWND hArea1, hArea2, hButton1, hButton2, hButton3, hButton4, hButton5;

POINT startPoint = { 0 };
POINT endPoint = { 0 };

bool bobono_paint = false;

// �������� �̺�Ʈ�� ó���ϴ� �ݹ�(Callback) �Լ�.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetDC(hwnd);

    //�⺻�귯��
    // ����
    HBRUSH hBrush_Black = CreateSolidBrush(RGB(0, 0, 0));
    // ���
    HBRUSH hBrush_White = CreateSolidBrush(RGB(255, 255, 255));
    //���뺸�� �귯��
    HBRUSH hBrush_BNFace = CreateSolidBrush(RGB(91, 155, 213));
    HBRUSH hBrush_BNTung = CreateSolidBrush(RGB(251, 150, 251));



    switch (uMsg)
    {
    case WM_MOUSEMOVE:
        //if hArea2 ����(16, 90, 788, 400)�� ���콺�� ������
        //wc.hCursor = LoadCursor(NULL, IDC_ARROW); ->IDC_CROSS �Ƹ���

        break;

    case WM_PAINT:
    {
        //���뺸�� �׸���
        //����
        SelectObject(hdc, hBrush_Black);

        //��
        Ellipse(hdc, 270, 170, 290, 190); // ������ Ÿ��

        //��
        SelectObject(hdc, hBrush_BNFace);
        Ellipse(hdc, 200, 100, 550, 450); // ������ Ÿ��

        //DeleteObject(hBrush_BNFace); �������� �������ֱ�
        
        ReleaseDC(hwnd, hdc); //�̰� ����


    }

    break;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;


    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    ReleaseDC(hwnd, hdc);

    return S_OK;
}


#ifdef UNICODE
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
#else
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
#endif
{


    /* ������ Ŭ���� ����.*/
    WNDCLASS wc;
    ZeroMemory(&wc, sizeof(wc));   // ��� 0���� �ʱ�ȭ.

    // ������ Ŭ���� �� ����
    wc.hInstance = hInstance;
    wc.lpszClassName = TEXT("Computer Software");
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpfnWndProc = WindowProc;

    // ������ Ŭ���� ���.
    if (RegisterClass(&wc) == 0)
    {
        MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
        exit(-1);   //����
    }

    // Window viewport ���� ����
    RECT rect = { 0, 0, 800, 480 };
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

    // ���� �˻�
    if (hwnd == NULL)
    {
        MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
        exit(-1);
    }
    // �ڽ� 2�� ��ư 5�� ��� 8px
    hArea1 = CreateWindow(TEXT("STATIC"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 8, 8, 808, 488, hwnd, NULL, hInstance, NULL);
    //����� ����
    hArea2 = CreateWindow(TEXT("STATIC"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 16, 90, 788, 400, hwnd, NULL, hInstance, NULL);

    //��ư 1~5
    hButton1 = CreateWindow(TEXT("BUTTON"), TEXT("Box Mode"), WS_VISIBLE | WS_CHILD, 16, 16, 140, 64, hwnd, (HMENU)1, NULL, NULL);
    hButton2 = CreateWindow(TEXT("BUTTON"), TEXT("Circle Mode"), WS_VISIBLE | WS_CHILD, 164, 16, 140, 64, hwnd, (HMENU)2, NULL, NULL);
    hButton3 = CreateWindow(TEXT("BUTTON"), TEXT("Bonobono Mode"), WS_VISIBLE | WS_CHILD, 312, 16, 140, 64, hwnd, (HMENU)3, NULL, NULL);
    hButton4 = CreateWindow(TEXT("BUTTON"), TEXT("Ryan Mode"), WS_VISIBLE | WS_CHILD, 460, 16, 140, 64, hwnd, (HMENU)4, NULL, NULL);
    hButton5 = CreateWindow(TEXT("BUTTON"), TEXT("Cube Mode"), WS_VISIBLE | WS_CHILD, 608, 16, 140, 64, hwnd, (HMENU)5, NULL, NULL);
    // â ���̱�.
    ShowWindow(hwnd, SW_SHOW); // â ����
    UpdateWindow(hwnd); // ������Ʈ�ؾ� ����. �� ������ ���ٰ� ���� ��.



    // �޽��� ó�� ����.
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    // �޽��� ó��.
    while (msg.message != WM_QUIT)
    {
        if (GetMessage(&msg, NULL, 0, 0))
        {
            // �޽��� �ؼ�����.
            TranslateMessage(&msg);
            // �޽����� ó���ؾ��� ���� ��������.
            DispatchMessage(&msg);
        }
        //if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        //{
        //   // �޽��� �ؼ�����.
        //   TranslateMessage(&msg);
        //   // �޽����� ó���ؾ��� ���� ��������.
        //   DispatchMessage(&msg);
        //} // PM_REMOVE�� �ڸ��� �� �޼����� ���� ��Ұų�.�� �ǹ��ε� ����ٴ� ����.
        //else{}
    }

    UnregisterClass(wc.lpszClassName, wc.hInstance);

    //���� �޽��� ������
    return (int)msg.wParam;
}