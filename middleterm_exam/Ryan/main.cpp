#include <windows.h>
#include "yuhanCG.h"

HWND hArea1, hArea2, hButton1, hButton2, hButton3, hButton4, hButton5;

POINT startPoint = { 0 }; 
POINT endPoint = { 0 }; 

POINT mouse = { 0 }; // ���콺 ��ġ, ��ο쿵���̿�

int isBoxButtonPressed = 0; // �ڽ� ��ư ���ȴ��� Ȯ��
int isCircleButtonPressed = 0; // �� ��ư ���ȴ��� Ȯ��
int isBonobonoButtonPressed = 0; // ���뺸�� ��ư ���ȴ��� Ȯ��
int isRyanButtonPressed = 0; // ���̾� ��ư ���ȴ��� Ȯ��
int isCubeButtonPressed = 0; // ť�� ��ư ���ȴ��� Ȯ��
int isMouseLButtonPressed = 0;//���콺 ���� ���ȴ���
int spacebarPressed = 0; //�����̽��� ���ȴ���

int draw_ok = 0; //��ο� ����

int left = 0; //���̾�� ��ǥ�ޱ�
int top = 0;
int right = 0;
int bottom = 0;

HBRUSH DrawingBrush = CreateSolidBrush(RGB(255, 255, 255));   //����� ���� �귯��

// �������� �̺�Ʈ�� ó���ϴ� �ݹ�(Callback) �Լ�.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetDC(hwnd);

    switch (uMsg)
    {
    case WM_COMMAND:
        
        switch (LOWORD(wParam)) 
        {
            
        case 1: //�ڽ���ư
            isBoxButtonPressed = 1;
            isCircleButtonPressed = 0; 
            isBonobonoButtonPressed = 0;
            isRyanButtonPressed = 0; 
            isCubeButtonPressed = 0; 

            SetFocus(hwnd); //��Ŀ�� ����
            InvalidateRect(hArea2, NULL, TRUE); //������ �׷ȴ��� ����

            break;
        case 2: //����ư
            isBoxButtonPressed = 0;
            isCircleButtonPressed = 1;
            isBonobonoButtonPressed = 0;
            isRyanButtonPressed = 0;
            isCubeButtonPressed = 0;

            SetFocus(hwnd); //��Ŀ�� ����
            InvalidateRect(hArea2, NULL, TRUE); //������ �׷ȴ��� ����

            break;
        case 3: //���뺸���ư
            isBoxButtonPressed = 0;
            isCircleButtonPressed = 0;
            isBonobonoButtonPressed = 1;
            isRyanButtonPressed = 0;
            isCubeButtonPressed = 0;

            
            
            SetFocus(hwnd); //��Ŀ�� ����
            InvalidateRect(hArea2, NULL, TRUE); //������ �׷ȴ��� ����

            break;
        case 4: //���̾��ư
            isBoxButtonPressed = 0;
            isCircleButtonPressed = 0;
            isBonobonoButtonPressed = 0;
            isRyanButtonPressed = 1;
            isCubeButtonPressed = 0;

            left = startPoint.x;
            top = startPoint.y;
            right = endPoint.x;
            bottom = endPoint.y;

            

            SetFocus(hwnd); //��Ŀ�� ����
            InvalidateRect(hArea2, NULL, TRUE); //������ �׷ȴ��� ����
            

            break;
        case 5: //ť���ư
            isBoxButtonPressed = 0;
            isCircleButtonPressed = 0;
            isBonobonoButtonPressed = 0;
            isRyanButtonPressed = 0;
            isCubeButtonPressed = 1;

            SetFocus(hwnd); //��Ŀ�� ����
            InvalidateRect(hArea2, NULL, TRUE); //������ �׷ȴ��� ����
            

            break;
        }
        break;
        //���콺 ��Ŭ�� ������
    case WM_LBUTTONDOWN: {

        if (isRyanButtonPressed == 1) {
            startPoint.x = LOWORD(lParam);
            startPoint.y = HIWORD(lParam);
        }
        isMouseLButtonPressed = 1;
        
    }
    break;
    //���콺 ��Ŭ�� �� ��
    case WM_LBUTTONUP: {

        isMouseLButtonPressed = 0;
        
    }
    break;
    case WM_MOUSEMOVE:
        if (isBonobonoButtonPressed == 1) {
            DrawBonobono(hwnd, hdc);
        }
        if (isRyanButtonPressed == 1) {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            if (isMouseLButtonPressed == 1) {
                DrawRyan(hwnd, hdc, left, top, right, bottom);
                InvalidateRect(hArea2, NULL, TRUE); //������ �׷ȴ��� ����}

            }
        }
       
        
        mouse.x = LOWORD(lParam);// ���콺 ��ǥ�� ���
        mouse.y = HIWORD(lParam);

        //�׸��� ���� �Ǻ�
        //if hArea2 ����(16, 90, 788, 400)�� ���콺�� ��
        break;
    
    case WM_SETCURSOR:
    {
        //����׿����̸� ���콺cross���� �ƴϸ� �⺻
        // 
        //==================================�۵�����=========================================
        //
        //
        if ((mouse.x >= 16 && mouse.x <= 90) && (mouse.y >= 788 && mouse.y <= 400)) {
            SetCursor(LoadCursor(NULL, IDC_CROSS));
            draw_ok = 1;
        }
        else {
            SetCursor(LoadCursor(NULL, IDC_ARROW));
            draw_ok = 0;
        }
    }
    case WM_PAINT:
    {   
        //��Ŭ�� ������ ���̾� �׸���
        if (isMouseLButtonPressed == 1)  {
            DrawRyan(hwnd, hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
        }
    }
    break;
    //���뺸�� �����̽��� ��� ���� ��
    case WM_KEYDOWN:
    {
        //isBonobonoButtonPressed == 1 �׳� �����̽��� ������ �׷����� �� ����
        if (wParam == VK_SPACE && isBonobonoButtonPressed == 1) { //�����̽��ٸ� ������ ������
            SpacebarBonobono(hwnd, hdc);
        }
    }
    break;
    //���뺸�� �����̽��� ��� �� ��
    case WM_KEYUP:
    {
        if (wParam == VK_SPACE && isBonobonoButtonPressed == 1) { //�����̽��ٸ� ���� �� ���߰�
            DrawBonobono(hwnd, hdc);
        }
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
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
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
    RECT GetClientRect = { 0, 0, 800, 480 };
    AdjustWindowRect(&GetClientRect, WS_OVERLAPPEDWINDOW, 0);
    int width = GetClientRect.right - GetClientRect.left;
    int height = GetClientRect.bottom - GetClientRect.top;

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

    //FrameRect�� �����ϰ� ������ �⺻ background �� �ٲ��ֱ�
    // paint ���� �ֱ�? ����� �غ��ߵ�
    // 
    // �ڽ� 2�� ��ư 5�� ��� 8px
    hArea1 = CreateWindow(TEXT("STATIC"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 0, 0, 800, 480, hwnd, NULL, hInstance, NULL);
    //����� ����
    hArea2 = CreateWindow(TEXT("STATIC"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 0, 90, 800, 400, hwnd, NULL, hInstance, NULL);

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