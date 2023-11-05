#include <windows.h>

HWND hArea1, hArea2, hButton1, hButton2, hButton3, hButton4, hButton5;

//POINT startPoint = { 0 }; //왼클릭 사각형
//POINT endPoint = { 0 }; //왼클릭 사각형

int isBoxButtonPressed = 0; // 박스 버튼 눌렸는지 확인
int isCircleButtonPressed = 0; // 원 버튼 눌렸는지 확인
int isBonobonoButtonPressed = 0; // 보노보노 버튼 눌렸는지 확인
int isRyanButtonPressed = 0; // 라이언 버튼 눌렸는지 확인
int isCubeButtonPressed = 0; // 큐브 버튼 눌렸는지 확인

int spacebarPressed = 0; //스페이스바 눌렸는지

//기본브러쉬
// 검정
HBRUSH hBrush_Black = CreateSolidBrush(RGB(0, 0, 0));
// 흰색
HBRUSH hBrush_White = CreateSolidBrush(RGB(255, 255, 255));

//보노보노용 브러쉬 파랑, 핑크
HBRUSH hBrush_BNFace = CreateSolidBrush(RGB(127, 200, 255));
HBRUSH hBrush_BNTung = CreateSolidBrush(RGB(255, 150, 255));

//보노보노 눈감은거 그리기
void SpacebarBonobono(HWND hwnd, HDC hdc) {
    
    //파랑색
    SelectObject(hdc, hBrush_BNFace);
    Ellipse(hdc, 200, 100, 550, 450); //얼굴 

    //핑크색
    SelectObject(hdc, hBrush_BNTung);
    Ellipse(hdc, 354, 250, 404, 350);

    //검정
    SelectObject(hdc, hBrush_Black);

    //흰색
    SelectObject(hdc, hBrush_White);

    Ellipse(hdc, 380, 260, 440, 310); //입쪽 왼
    Ellipse(hdc, 320, 260, 380, 310); //입쪽 오

    //검정
    SelectObject(hdc, hBrush_Black);
    MoveToEx(hdc, 245, 220, NULL); //보노보노 눈 왼
    LineTo(hdc, 260, 230);
    MoveToEx(hdc, 245, 240, NULL);
    LineTo(hdc, 260, 230);

    MoveToEx(hdc, 500, 240, NULL); //보노보노 눈 오
    LineTo(hdc, 485, 230);
    MoveToEx(hdc, 500, 220, NULL);
    LineTo(hdc, 485, 230);

    MoveToEx(hdc, 335, 275, NULL); //수염 왼 위
    LineTo(hdc, 285, 255);
    MoveToEx(hdc, 300, 305, NULL); // 수염 왼 아
    LineTo(hdc, 340, 295);

    MoveToEx(hdc, 425, 275, NULL); //수염 오 위
    LineTo(hdc, 455, 260);
    MoveToEx(hdc, 420, 295, NULL); //수염 오 아 
    LineTo(hdc, 470, 300);

    //코
    Ellipse(hdc, 354, 243, 404, 293);


    //DeleteObject(hBrush_White);
    //DeleteObject(hBrush_Black);
    //DeleteObject(hBrush_BNTung); 
    //DeleteObject(hBrush_BNFace); 
    // 웬지 모르겠는데 자꾸 색 지워짐
    // 안지우면 메모리 누수 가능성있음
    // 마지막에 삭제해주기
    

    ReleaseDC(hwnd, hdc); // 삭제
}
//보노보노 그리기
void DrawBonobono(HWND hwnd, HDC hdc) {

    //파랑색
    SelectObject(hdc, hBrush_BNFace);
    Ellipse(hdc, 200, 100, 550, 450); //얼굴 

    //핑크색
    SelectObject(hdc, hBrush_BNTung);
    Ellipse(hdc, 354, 250, 404, 350);

    //검정
    SelectObject(hdc, hBrush_Black);

    Ellipse(hdc, 245, 215, 260, 235); // 눈 왼 검은자
    Ellipse(hdc, 485, 215, 500, 235); // 눈 오 검은자

    //흰색
    SelectObject(hdc, hBrush_White); 

    //Ellipse(  hdc Left Top  Right  Bottom)
    Ellipse(hdc, 250, 220, 255, 226); // 눈 왼 흰자
    Ellipse(hdc, 490, 220, 495, 226); // 눈 오 흰자

    Ellipse(hdc, 380, 260, 440, 310); //입쪽 왼
    Ellipse(hdc, 320, 260, 380, 310); //입쪽 오
    

    //검정
    SelectObject(hdc, hBrush_Black);

    MoveToEx(hdc, 335, 275, NULL); //수염 왼 위
    LineTo(hdc, 285, 255);
    MoveToEx(hdc, 300, 305, NULL); // 수염 왼 아
    LineTo(hdc, 340, 295);

    MoveToEx(hdc, 425, 275, NULL); //수염 오 위
    LineTo(hdc, 455, 260);
    MoveToEx(hdc, 420, 295, NULL); //수염 오 아 
    LineTo(hdc, 470, 300);

    //코
    Ellipse(hdc, 354, 243, 404, 293);

    
    //DeleteObject(hBrush_White);
    //DeleteObject(hBrush_Black);
    //DeleteObject(hBrush_BNTung); 
    //DeleteObject(hBrush_BNFace); 
    // 웬지 모르겠는데 자꾸 색 지워짐
    // 안지우면 메모리 누수 가능성있음
    // 마지막에 삭제해주기
    

    ReleaseDC(hwnd, hdc); // 삭제

}

// 윈도우의 이벤트를 처리하는 콜백(Callback) 함수.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetDC(hwnd);

    switch (uMsg)
    {
    case WM_COMMAND:
        //버튼 기능부여 //지우는거 아직안함
        switch (LOWORD(wParam)) 
        {
            
        case 1: //박스버튼
            isBoxButtonPressed = 1;
            isCircleButtonPressed = 0; 
            isBonobonoButtonPressed = 0;
            isRyanButtonPressed = 0; 
            isCubeButtonPressed = 0; 

            SetFocus(hwnd); //포커스 해제
            InvalidateRect(hwnd, NULL, TRUE); //이전에 그렸던거 삭제

            break;
        case 2: //원버튼
            isBoxButtonPressed = 0;
            isCircleButtonPressed = 1;
            isBonobonoButtonPressed = 0;
            isRyanButtonPressed = 0;
            isCubeButtonPressed = 0;

            SetFocus(hwnd); //포커스 해제
            //InvalidateRect(hwnd, NULL, TRUE);

            break;
        case 3: //보노보노버튼
            isBoxButtonPressed = 0;
            isCircleButtonPressed = 0;
            isBonobonoButtonPressed = 1;
            isRyanButtonPressed = 0;
            isCubeButtonPressed = 0;
            
            DrawBonobono(hwnd, hdc);
            SetFocus(hwnd); //포커스 해제
            //InvalidateRect(hwnd, NULL, TRUE);

            break;
        case 4: //라이언버튼
            isBoxButtonPressed = 0;
            isCircleButtonPressed = 0;
            isBonobonoButtonPressed = 0;
            isRyanButtonPressed = 1;
            isCubeButtonPressed = 0;

            SetFocus(hwnd); //포커스 해제
            //InvalidateRect(hwnd, NULL, TRUE);

            break;
        case 5: //큐브버튼
            isBoxButtonPressed = 0;
            isCircleButtonPressed = 0;
            isBonobonoButtonPressed = 0;
            isRyanButtonPressed = 0;
            isCubeButtonPressed = 1;

            SetFocus(hwnd); //포커스 해제
            //InvalidateRect(hwnd, NULL, TRUE);

            break;
        }

        break;
        //보노보노 스페이스바 기능 누를때
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
    case WM_MOUSEMOVE:
        //그리기 영역 판별
        //if hArea2 영역(16, 90, 788, 400)에 마우스가 있으면
        //wc.hCursor = LoadCursor(NULL, IDC_ARROW); ->IDC_CROSS 아마도

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