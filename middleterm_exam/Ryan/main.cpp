#include <windows.h>
#include "yuhanCG.h"

HWND hArea1, hArea2, hButton1, hButton2, hButton3, hButton4, hButton5;

POINT startPoint = { 0 }; 
POINT endPoint = { 0 }; 

POINT mouse = { 0 }; // 마우스 위치, 드로우영역이용

int isBoxButtonPressed = 0; // 박스 버튼 눌렸는지 확인
int isCircleButtonPressed = 0; // 원 버튼 눌렸는지 확인
int isBonobonoButtonPressed = 0; // 보노보노 버튼 눌렸는지 확인
int isRyanButtonPressed = 0; // 라이언 버튼 눌렸는지 확인
int isCubeButtonPressed = 0; // 큐브 버튼 눌렸는지 확인
int isMouseLButtonPressed = 0;//마우스 왼쪽 눌렸는지
int spacebarPressed = 0; //스페이스바 눌렸는지

int draw_ok = 0; //드로우 영역

int left = 0; //라이언용 좌표받기
int top = 0;
int right = 0;
int bottom = 0;

HBRUSH DrawingBrush = CreateSolidBrush(RGB(255, 255, 255));   //드로잉 영역 브러쉬

// 윈도우의 이벤트를 처리하는 콜백(Callback) 함수.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetDC(hwnd);

    switch (uMsg)
    {
    case WM_COMMAND:
        
        switch (LOWORD(wParam)) 
        {
            
        case 1: //박스버튼
            isBoxButtonPressed = 1;
            isCircleButtonPressed = 0; 
            isBonobonoButtonPressed = 0;
            isRyanButtonPressed = 0; 
            isCubeButtonPressed = 0; 

            SetFocus(hwnd); //포커스 해제
            InvalidateRect(hArea2, NULL, TRUE); //이전에 그렸던거 삭제

            break;
        case 2: //원버튼
            isBoxButtonPressed = 0;
            isCircleButtonPressed = 1;
            isBonobonoButtonPressed = 0;
            isRyanButtonPressed = 0;
            isCubeButtonPressed = 0;

            SetFocus(hwnd); //포커스 해제
            InvalidateRect(hArea2, NULL, TRUE); //이전에 그렸던거 삭제

            break;
        case 3: //보노보노버튼
            isBoxButtonPressed = 0;
            isCircleButtonPressed = 0;
            isBonobonoButtonPressed = 1;
            isRyanButtonPressed = 0;
            isCubeButtonPressed = 0;

            
            
            SetFocus(hwnd); //포커스 해제
            InvalidateRect(hArea2, NULL, TRUE); //이전에 그렸던거 삭제

            break;
        case 4: //라이언버튼
            isBoxButtonPressed = 0;
            isCircleButtonPressed = 0;
            isBonobonoButtonPressed = 0;
            isRyanButtonPressed = 1;
            isCubeButtonPressed = 0;

            left = startPoint.x;
            top = startPoint.y;
            right = endPoint.x;
            bottom = endPoint.y;

            

            SetFocus(hwnd); //포커스 해제
            InvalidateRect(hArea2, NULL, TRUE); //이전에 그렸던거 삭제
            

            break;
        case 5: //큐브버튼
            isBoxButtonPressed = 0;
            isCircleButtonPressed = 0;
            isBonobonoButtonPressed = 0;
            isRyanButtonPressed = 0;
            isCubeButtonPressed = 1;

            SetFocus(hwnd); //포커스 해제
            InvalidateRect(hArea2, NULL, TRUE); //이전에 그렸던거 삭제
            

            break;
        }
        break;
        //마우스 왼클릭 누를때
    case WM_LBUTTONDOWN: {

        if (isRyanButtonPressed == 1) {
            startPoint.x = LOWORD(lParam);
            startPoint.y = HIWORD(lParam);
        }
        isMouseLButtonPressed = 1;
        
    }
    break;
    //마우스 왼클릭 땔 때
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
                InvalidateRect(hArea2, NULL, TRUE); //이전에 그렸던거 삭제}

            }
        }
       
        
        mouse.x = LOWORD(lParam);// 마우스 좌표를 얻기
        mouse.y = HIWORD(lParam);

        //그리기 영역 판별
        //if hArea2 영역(16, 90, 788, 400)에 마우스가 있
        break;
    
    case WM_SETCURSOR:
    {
        //드로잉영역이면 마우스cross변경 아니면 기본
        // 
        //==================================작동안함=========================================
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
        //왼클릭 들어오면 라이언 그리기
        if (isMouseLButtonPressed == 1)  {
            DrawRyan(hwnd, hdc, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
        }
    }
    break;
    //보노보노 스페이스바 기능 누를 때
    case WM_KEYDOWN:
    {
        //isBonobonoButtonPressed == 1 그냥 스페이스바 누르면 그려지는 거 방지
        if (wParam == VK_SPACE && isBonobonoButtonPressed == 1) { //스페이스바를 누르면 눈감게
            SpacebarBonobono(hwnd, hdc);
        }
    }
    break;
    //보노보노 스페이스바 기능 땔 때
    case WM_KEYUP:
    {
        if (wParam == VK_SPACE && isBonobonoButtonPressed == 1) { //스페이스바를 땠을 때 눈뜨게
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
    RECT GetClientRect = { 0, 0, 800, 480 };
    AdjustWindowRect(&GetClientRect, WS_OVERLAPPEDWINDOW, 0);
    int width = GetClientRect.right - GetClientRect.left;
    int height = GetClientRect.bottom - GetClientRect.top;

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

    //FrameRect로 변경하고 윈도우 기본 background 색 바꿔주기
    // paint 영역 넣기? 고민좀 해봐야됨
    // 
    // 박스 2개 버튼 5개 페딩 8px
    hArea1 = CreateWindow(TEXT("STATIC"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 0, 0, 800, 480, hwnd, NULL, hInstance, NULL);
    //드로잉 영역
    hArea2 = CreateWindow(TEXT("STATIC"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 0, 90, 800, 400, hwnd, NULL, hInstance, NULL);

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