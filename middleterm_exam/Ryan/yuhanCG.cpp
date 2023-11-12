#include <windows.h>
#include "yuhanCG.h"

//�⺻�귯��
// ����
HBRUSH hBrush_Black = CreateSolidBrush(RGB(0, 0, 0));
// ���
HBRUSH hBrush_White = CreateSolidBrush(RGB(255, 255, 255));

//���̾�� �귯��
HBRUSH hBrush_RyanFace = CreateSolidBrush(RGB(255, 200, 15));
 
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
//���̾� �׸���
void DrawRyan(HWND hwnd, HDC hdc, int left, int top, int right, int bottom) {
    //��ǥ�ޱ�
    int startPointX = left;
    int startPointY = top;
    int endPointX = right;
    int endPointY = bottom;
    //��ǥ�� ũ�⿡���� MIN MAX�����ޱ�
    POINT MINPOINT = { 0 };
    POINT MAXPOINT = { 0 };

    // �� ��ġ 
    MINPOINT.x = min(startPointX, endPointX);
    MINPOINT.y = min(startPointY, endPointY);
    MAXPOINT.x = max(startPointX, endPointX);
    MAXPOINT.y = max(startPointY, endPointY);

    RECT face = { MINPOINT.x, MINPOINT.y,MAXPOINT.x,MAXPOINT.y };
    //abs == ���밪
    //��ǥ ���ذ� ���밪������ ũ�� ���ϱ�
    int width = abs(MINPOINT.x - MAXPOINT.x);
    int height = abs(MINPOINT.y - MAXPOINT.y);
    int centerX = width / 2;
    int centerY = height / 2;
    POINT centerPoint = { MINPOINT.x + centerX, MINPOINT.y + centerY };

    // �Ǻλ�
    HBRUSH RskinBrush = CreateSolidBrush(RGB(255, 200, 15));
    SelectObject(hdc, RskinBrush);
    //r = right, l = left
    // ��
    RECT lear = { MINPOINT.x , MINPOINT.y, MINPOINT.x + width / 3, MINPOINT.y + height / 3 };
    RECT rear = { MAXPOINT.x , MINPOINT.y, MAXPOINT.x - width / 3, MINPOINT.y + height / 3 };

    // �� ��
    Ellipse(hdc, lear.left, lear.top, lear.right, lear.bottom);
    // �� ��
    Ellipse(hdc, rear.left, rear.top, rear.right, rear.bottom);
    // ��
    Ellipse(hdc, face.left, face.top, face.right, face.bottom);
    //����ã��
    // p = point, r = right, l = left
    POINT leyep = { MINPOINT.x + centerX / 2, MINPOINT.y + (centerY / 6 * 5) };
    POINT reyep = { MAXPOINT.x - centerX / 2, MINPOINT.y + (centerY / 6 * 5) };
    RECT leyer = { leyep.x, leyep.y, leyep.x + width / 20, leyep.y + height / 20 };
    RECT reyer = { reyep.x, reyep.y, reyep.x - width / 20, reyep.y + height / 20 };
    
    // ��
    
    SelectObject(hdc, hBrush_Black);
    Ellipse(hdc, leyer.left,leyer.top, leyer.right, leyer.bottom);
    Ellipse(hdc, reyer.left, reyer.top, reyer.right, reyer.bottom);

    // ���� 3�� ��
    MoveToEx(hdc, MINPOINT.x + centerX / 4, MINPOINT.y + centerY / 3 * 2, NULL);
    LineTo(hdc, MINPOINT.x + (centerX / 4 * 3), MINPOINT.y + (centerY / 3 * 2));
    MoveToEx(hdc, MINPOINT.x + centerX / 4, MINPOINT.y + centerY / 3 * 2 + 2, NULL);
    LineTo(hdc, MINPOINT.x + (centerX / 4 * 3), MINPOINT.y + (centerY / 3 * 2) + 2);
    MoveToEx(hdc, MINPOINT.x + centerX / 4, MINPOINT.y + centerY / 3 * 2 + 4, NULL);
    LineTo(hdc, MINPOINT.x + (centerX / 4 * 3), MINPOINT.y + (centerY / 3 * 2) + 4);
    // ���� 3�� ��
    MoveToEx(hdc, MAXPOINT.x - centerX / 4, MINPOINT.y + centerY / 3 * 2, NULL);
    LineTo(hdc, MAXPOINT.x - (centerX / 4 * 3), MINPOINT.y + (centerY / 3 * 2));
    MoveToEx(hdc, MAXPOINT.x - centerX / 4, MINPOINT.y + centerY / 3 * 2 + 2, NULL);
    LineTo(hdc, MAXPOINT.x - (centerX / 4 * 3), MINPOINT.y + (centerY / 3 * 2) + 2);
    MoveToEx(hdc, MAXPOINT.x - centerX / 4, MINPOINT.y + centerY / 3 * 2 + 4, NULL);
    LineTo(hdc, MAXPOINT.x - (centerX / 4 * 3), MINPOINT.y + (centerY / 3 * 2) + 4);

    // ��
    RECT L_nose = { centerPoint.x - centerX / 5, centerPoint.y, centerPoint.x, centerPoint.y + centerY / 5 };
    RECT R_nose = { centerPoint.x, centerPoint.y, centerPoint.x + centerX / 5, centerPoint.y + centerY / 5 };
    
    SelectObject(hdc, hBrush_White);
    Ellipse(hdc, L_nose.left, L_nose.top, L_nose.right, L_nose.bottom);
    Ellipse(hdc, R_nose.left, R_nose.top, R_nose.right, R_nose.bottom);

    ReleaseDC(hwnd, hdc); // ����
}
