#include <windows.h>

HWND hArea1, hArea2, hButton1, hButton2, hButton3, hButton4, hButton5;

POINT startPoint = { 0 };
POINT endPoint = { 0 };

bool bobono_paint = false;

// 윈도우의 이벤트를 처리하는 콜백(Callback) 함수.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetDC(hwnd);

    //기본브러쉬
    // 검정
    HBRUSH hBrush_Black = CreateSolidBrush(RGB(0, 0, 0));
    // 흰색
    HBRUSH hBrush_White = CreateSolidBrush(RGB(255, 255, 255));
    //보노보노 브러쉬
    HBRUSH hBrush_BNFace = CreateSolidBrush(RGB(91, 155, 213));
    HBRUSH hBrush_BNTung = CreateSolidBrush(RGB(251, 150, 251));



    switch (uMsg)
    {
    case WM_MOUSEMOVE:
        //if hArea2 영역(16, 90, 788, 400)에 마우스가 있으면
        //wc.hCursor = LoadCursor(NULL, IDC_ARROW); ->IDC_CROSS 아마도

        break;

    case WM_PAINT:
    {
        //보노보노 그리기
        //검정
        SelectObject(hdc, hBrush_Black);

        //코
        Ellipse(hdc, 270, 170, 290, 190); // 까지의 타원

        //얼굴
        SelectObject(hdc, hBrush_BNFace);
        Ellipse(hdc, 200, 100, 550, 450); // 까지의 타원

        //DeleteObject(hBrush_BNFace); 마지막에 삭제해주기
        
        ReleaseDC(hwnd, hdc); //이게 뭘까


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


    /* 윈도우 클래스 선언.*/
    WNDCLASS wc;
    ZeroMemory(&wc, sizeof(wc));   // 모두 0으로 초기화.

    // 윈도우 클래스 값 설정
    wc.hInstance = hInstance;
    wc.lpszClassName = TEXT("Computer Software");
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpfnWndProc = WindowProc;

    // 윈도우 클래스 등록.
    if (RegisterClass(&wc) == 0)
    {
        MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
        exit(-1);   //예외
    }

    // Window viewport 영역 조정
    RECT rect = { 0, 0, 800, 480 };
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

    // 오류 검사
    if (hwnd == NULL)
    {
        MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
        exit(-1);
    }
    // 박스 2개 버튼 5개 페딩 8px
    hArea1 = CreateWindow(TEXT("STATIC"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 8, 8, 808, 488, hwnd, NULL, hInstance, NULL);
    //드로잉 영역
    hArea2 = CreateWindow(TEXT("STATIC"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 16, 90, 788, 400, hwnd, NULL, hInstance, NULL);

    //버튼 1~5
    hButton1 = CreateWindow(TEXT("BUTTON"), TEXT("Box Mode"), WS_VISIBLE | WS_CHILD, 16, 16, 140, 64, hwnd, (HMENU)1, NULL, NULL);
    hButton2 = CreateWindow(TEXT("BUTTON"), TEXT("Circle Mode"), WS_VISIBLE | WS_CHILD, 164, 16, 140, 64, hwnd, (HMENU)2, NULL, NULL);
    hButton3 = CreateWindow(TEXT("BUTTON"), TEXT("Bonobono Mode"), WS_VISIBLE | WS_CHILD, 312, 16, 140, 64, hwnd, (HMENU)3, NULL, NULL);
    hButton4 = CreateWindow(TEXT("BUTTON"), TEXT("Ryan Mode"), WS_VISIBLE | WS_CHILD, 460, 16, 140, 64, hwnd, (HMENU)4, NULL, NULL);
    hButton5 = CreateWindow(TEXT("BUTTON"), TEXT("Cube Mode"), WS_VISIBLE | WS_CHILD, 608, 16, 140, 64, hwnd, (HMENU)5, NULL, NULL);
    // 창 보이기.
    ShowWindow(hwnd, SW_SHOW); // 창 띄우고
    UpdateWindow(hwnd); // 업데이트해야 보임. 한 쌍으로 쓴다고 보면 됨.



    // 메시지 처리 루프.
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    // 메시지 처리.
    while (msg.message != WM_QUIT)
    {
        if (GetMessage(&msg, NULL, 0, 0))
        {
            // 메시지 해석해줘.
            TranslateMessage(&msg);
            // 메시지를 처리해야할 곳에 전달해줘.
            DispatchMessage(&msg);
        }
        //if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        //{
        //   // 메시지 해석해줘.
        //   TranslateMessage(&msg);
        //   // 메시지를 처리해야할 곳에 전달해줘.
        //   DispatchMessage(&msg);
        //} // PM_REMOVE의 자리는 이 메세지를 쓰고 어떡할거냐.의 의미인데 지운다는 것임.
        //else{}
    }

    UnregisterClass(wc.lpszClassName, wc.hInstance);

    //종료 메시지 보내기
    return (int)msg.wParam;
}