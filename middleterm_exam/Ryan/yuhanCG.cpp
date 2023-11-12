#include <windows.h>
#include "yuhanCG.h"

//기본브러쉬
// 검정
HBRUSH hBrush_Black = CreateSolidBrush(RGB(0, 0, 0));
// 흰색
HBRUSH hBrush_White = CreateSolidBrush(RGB(255, 255, 255));

//라이언용 브러쉬
HBRUSH hBrush_RyanFace = CreateSolidBrush(RGB(255, 200, 15));
 
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
//라이언 그리기
void DrawRyan(HWND hwnd, HDC hdc, int left, int top, int right, int bottom) {
    //좌표받기
    int startPointX = left;
    int startPointY = top;
    int endPointX = right;
    int endPointY = bottom;
    //좌표의 크기에따라 MIN MAX지점받기
    POINT MINPOINT = { 0 };
    POINT MAXPOINT = { 0 };

    // 얼굴 위치 
    MINPOINT.x = min(startPointX, endPointX);
    MINPOINT.y = min(startPointY, endPointY);
    MAXPOINT.x = max(startPointX, endPointX);
    MAXPOINT.y = max(startPointY, endPointY);

    RECT face = { MINPOINT.x, MINPOINT.y,MAXPOINT.x,MAXPOINT.y };
    //abs == 절대값
    //좌표 뺴준거 절대값씌워서 크기 구하기
    int width = abs(MINPOINT.x - MAXPOINT.x);
    int height = abs(MINPOINT.y - MAXPOINT.y);
    int centerX = width / 2;
    int centerY = height / 2;
    POINT centerPoint = { MINPOINT.x + centerX, MINPOINT.y + centerY };

    // 피부색
    HBRUSH RskinBrush = CreateSolidBrush(RGB(255, 200, 15));
    SelectObject(hdc, RskinBrush);
    //r = right, l = left
    // 귀
    RECT lear = { MINPOINT.x , MINPOINT.y, MINPOINT.x + width / 3, MINPOINT.y + height / 3 };
    RECT rear = { MAXPOINT.x , MINPOINT.y, MAXPOINT.x - width / 3, MINPOINT.y + height / 3 };

    // 왼 귀
    Ellipse(hdc, lear.left, lear.top, lear.right, lear.bottom);
    // 오 귀
    Ellipse(hdc, rear.left, rear.top, rear.right, rear.bottom);
    // 얼굴
    Ellipse(hdc, face.left, face.top, face.right, face.bottom);
    //센터찾기
    // p = point, r = right, l = left
    POINT leyep = { MINPOINT.x + centerX / 2, MINPOINT.y + (centerY / 6 * 5) };
    POINT reyep = { MAXPOINT.x - centerX / 2, MINPOINT.y + (centerY / 6 * 5) };
    RECT leyer = { leyep.x, leyep.y, leyep.x + width / 20, leyep.y + height / 20 };
    RECT reyer = { reyep.x, reyep.y, reyep.x - width / 20, reyep.y + height / 20 };
    
    // 눈
    
    SelectObject(hdc, hBrush_Black);
    Ellipse(hdc, leyer.left,leyer.top, leyer.right, leyer.bottom);
    Ellipse(hdc, reyer.left, reyer.top, reyer.right, reyer.bottom);

    // 눈썹 3개 왼
    MoveToEx(hdc, MINPOINT.x + centerX / 4, MINPOINT.y + centerY / 3 * 2, NULL);
    LineTo(hdc, MINPOINT.x + (centerX / 4 * 3), MINPOINT.y + (centerY / 3 * 2));
    MoveToEx(hdc, MINPOINT.x + centerX / 4, MINPOINT.y + centerY / 3 * 2 + 2, NULL);
    LineTo(hdc, MINPOINT.x + (centerX / 4 * 3), MINPOINT.y + (centerY / 3 * 2) + 2);
    MoveToEx(hdc, MINPOINT.x + centerX / 4, MINPOINT.y + centerY / 3 * 2 + 4, NULL);
    LineTo(hdc, MINPOINT.x + (centerX / 4 * 3), MINPOINT.y + (centerY / 3 * 2) + 4);
    // 눈썹 3개 오
    MoveToEx(hdc, MAXPOINT.x - centerX / 4, MINPOINT.y + centerY / 3 * 2, NULL);
    LineTo(hdc, MAXPOINT.x - (centerX / 4 * 3), MINPOINT.y + (centerY / 3 * 2));
    MoveToEx(hdc, MAXPOINT.x - centerX / 4, MINPOINT.y + centerY / 3 * 2 + 2, NULL);
    LineTo(hdc, MAXPOINT.x - (centerX / 4 * 3), MINPOINT.y + (centerY / 3 * 2) + 2);
    MoveToEx(hdc, MAXPOINT.x - centerX / 4, MINPOINT.y + centerY / 3 * 2 + 4, NULL);
    LineTo(hdc, MAXPOINT.x - (centerX / 4 * 3), MINPOINT.y + (centerY / 3 * 2) + 4);

    // 코
    RECT L_nose = { centerPoint.x - centerX / 5, centerPoint.y, centerPoint.x, centerPoint.y + centerY / 5 };
    RECT R_nose = { centerPoint.x, centerPoint.y, centerPoint.x + centerX / 5, centerPoint.y + centerY / 5 };
    
    SelectObject(hdc, hBrush_White);
    Ellipse(hdc, L_nose.left, L_nose.top, L_nose.right, L_nose.bottom);
    Ellipse(hdc, R_nose.left, R_nose.top, R_nose.right, R_nose.bottom);

    ReleaseDC(hwnd, hdc); // 삭제
}
