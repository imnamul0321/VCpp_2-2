#include <windows.h>

HWND hArea1, hArea2, hButton1, hButton2, hButton3, hButton4, hButton5;

//POINT startPoint = { 0 }; //��Ŭ�� �簢��
//POINT endPoint = { 0 }; //��Ŭ�� �簢��

int isBoxButtonPressed = 0; // �ڽ� ��ư ���ȴ��� Ȯ��
int isCircleButtonPressed = 0; // �� ��ư ���ȴ��� Ȯ��
int isBonobonoButtonPressed = 0; // ���뺸�� ��ư ���ȴ��� Ȯ��
int isRyanButtonPressed = 0; // ���̾� ��ư ���ȴ��� Ȯ��
int isCubeButtonPressed = 0; // ť�� ��ư ���ȴ��� Ȯ��

int spacebarPressed = 0; //�����̽��� ���ȴ���


//�⺻�귯��
// ����
HBRUSH hBrush_Black = CreateSolidBrush(RGB(0, 0, 0));
// ���
HBRUSH hBrush_White = CreateSolidBrush(RGB(255, 255, 255));

//���뺸��� �귯�� �Ķ�, ��ũ
HBRUSH hBrush_BNFace = CreateSolidBrush(RGB(127, 200, 255));
HBRUSH hBrush_BNTung = CreateSolidBrush(RGB(255, 150, 255));

//���뺸�� �������� �׸���
void SpacebarBonobono(HWND hwnd, HDC hdc) {
    
    //�Ķ���
    SelectObject(hdc, hBrush_BNFace);
    Ellipse(hdc, 200, 100, 550, 450); //�� 

    //��ũ��
    SelectObject(hdc, hBrush_BNTung);
    Ellipse(hdc, 354, 250, 404, 350);

    //����
    SelectObject(hdc, hBrush_Black);

    //���
    SelectObject(hdc, hBrush_White);

    Ellipse(hdc, 380, 260, 440, 310); //���� ��
    Ellipse(hdc, 320, 260, 380, 310); //���� ��

    //����
    SelectObject(hdc, hBrush_Black);
    MoveToEx(hdc, 245, 220, NULL); //���뺸�� �� ��
    LineTo(hdc, 260, 230);
    MoveToEx(hdc, 245, 240, NULL);
    LineTo(hdc, 260, 230);

    MoveToEx(hdc, 500, 240, NULL); //���뺸�� �� ��
    LineTo(hdc, 485, 230);
    MoveToEx(hdc, 500, 220, NULL);
    LineTo(hdc, 485, 230);

    MoveToEx(hdc, 335, 275, NULL); //���� �� ��
    LineTo(hdc, 285, 255);
    MoveToEx(hdc, 300, 305, NULL); // ���� �� ��
    LineTo(hdc, 340, 295);

    MoveToEx(hdc, 425, 275, NULL); //���� �� ��
    LineTo(hdc, 455, 260);
    MoveToEx(hdc, 420, 295, NULL); //���� �� �� 
    LineTo(hdc, 470, 300);

    //��
    Ellipse(hdc, 354, 243, 404, 293);


    //DeleteObject(hBrush_White);
    //DeleteObject(hBrush_Black);
    //DeleteObject(hBrush_BNTung); 
    //DeleteObject(hBrush_BNFace); 
    // ���� �𸣰ڴµ� �ڲ� �� ������
    // ������� �޸� ���� ���ɼ�����
    // �������� �������ֱ�
    

    ReleaseDC(hwnd, hdc); // ����
}
//���뺸�� �׸���
void DrawBonobono(HWND hwnd, HDC hdc) {

    //�Ķ���
    SelectObject(hdc, hBrush_BNFace);
    Ellipse(hdc, 200, 100, 550, 450); //�� 

    //��ũ��
    SelectObject(hdc, hBrush_BNTung);
    Ellipse(hdc, 354, 250, 404, 350);

    //����
    SelectObject(hdc, hBrush_Black);

    Ellipse(hdc, 245, 215, 260, 235); // �� �� ������
    Ellipse(hdc, 485, 215, 500, 235); // �� �� ������

    //���
    SelectObject(hdc, hBrush_White); 

    //Ellipse(  hdc Left Top  Right  Bottom)
    Ellipse(hdc, 250, 220, 255, 226); // �� �� ����
    Ellipse(hdc, 490, 220, 495, 226); // �� �� ����

    Ellipse(hdc, 380, 260, 440, 310); //���� ��
    Ellipse(hdc, 320, 260, 380, 310); //���� ��
    

    //����
    SelectObject(hdc, hBrush_Black);

    MoveToEx(hdc, 335, 275, NULL); //���� �� ��
    LineTo(hdc, 285, 255);
    MoveToEx(hdc, 300, 305, NULL); // ���� �� ��
    LineTo(hdc, 340, 295);

    MoveToEx(hdc, 425, 275, NULL); //���� �� ��
    LineTo(hdc, 455, 260);
    MoveToEx(hdc, 420, 295, NULL); //���� �� �� 
    LineTo(hdc, 470, 300);

    //��
    Ellipse(hdc, 354, 243, 404, 293);

    
    //DeleteObject(hBrush_White);
    //DeleteObject(hBrush_Black);
    //DeleteObject(hBrush_BNTung); 
    //DeleteObject(hBrush_BNFace); 
    // ���� �𸣰ڴµ� �ڲ� �� ������
    // ������� �޸� ���� ���ɼ�����
    // �������� �������ֱ�
  

   ReleaseDC(hwnd, hdc); // ����

}

// �������� �̺�Ʈ�� ó���ϴ� �ݹ�(Callback) �Լ�.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetDC(hwnd);

    switch (uMsg)
    {
    case WM_COMMAND:
        //��ư ��ɺο� //����°� ��������
        switch (LOWORD(wParam)) 
        {
            
        case 1: //�ڽ���ư
            isBoxButtonPressed = 1;
            isCircleButtonPressed = 0; 
            isBonobonoButtonPressed = 0;
            isRyanButtonPressed = 0; 
            isCubeButtonPressed = 0; 

            SetFocus(hwnd); //��Ŀ�� ����
            //InvalidateRect(hwnd, NULL, TRUE); //������ �׷ȴ��� ����

            break;
        case 2: //����ư
            isBoxButtonPressed = 0;
            isCircleButtonPressed = 1;
            isBonobonoButtonPressed = 0;
            isRyanButtonPressed = 0;
            isCubeButtonPressed = 0;

            SetFocus(hwnd); //��Ŀ�� ����
            //InvalidateRect(hwnd, NULL, TRUE);

            break;
        case 3: //���뺸���ư
            isBoxButtonPressed = 0;
            isCircleButtonPressed = 0;
            isBonobonoButtonPressed = 1;
            isRyanButtonPressed = 0;
            isCubeButtonPressed = 0;
            
            DrawBonobono(hwnd, hdc);
            SetFocus(hwnd); //��Ŀ�� ����
            //InvalidateRect(hwnd, NULL, TRUE);

            break;
        case 4: //���̾��ư
            isBoxButtonPressed = 0;
            isCircleButtonPressed = 0;
            isBonobonoButtonPressed = 0;
            isRyanButtonPressed = 1;
            isCubeButtonPressed = 0;

            SetFocus(hwnd); //��Ŀ�� ����
            //InvalidateRect(hwnd, NULL, TRUE);

            break;
        case 5: //ť���ư
            isBoxButtonPressed = 0;
            isCircleButtonPressed = 0;
            isBonobonoButtonPressed = 0;
            isRyanButtonPressed = 0;
            isCubeButtonPressed = 1;

            SetFocus(hwnd); //��Ŀ�� ����
            //InvalidateRect(hwnd, NULL, TRUE);

            break;
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
    case WM_MOUSEMOVE:
        //�׸��� ���� �Ǻ�
        //if hArea2 ����(16, 90, 788, 400)�� ���콺�� ������
        //wc.hCursor = LoadCursor(NULL, IDC_ARROW); ->IDC_CROSS �Ƹ���

        break;
    case WM_PAINT:
    {

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