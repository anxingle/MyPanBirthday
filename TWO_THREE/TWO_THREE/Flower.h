
#pragma once
///////////////// ���巽�� ////////////////////
#define LEFT  -1 
#define CENTER 0
#define RIGHT  1
#define TIME_TO_CHANGE 15

#define PIC_MOVE_STEP   1       // �½��ķ���
#define DIVE   180

#define PIC_NUM 50      // the total number of picture that would be show
#define DIS_NUM 10      // the number of picture that displayed on the screen
class Flower
{
private:
	int m_curPosX,m_curPosY;          // ��ǰ��λ��X��y
	int m_curDireciton, m_timeDir;    // �����Լ��ı䷽���ʱ��
	long m_picWidth, m_picHeight;
	CDC m_cdcDesk, m_cdcMem;
	HDC m_hdcDesk;
	HWND m_hwndDesktop;
	HBITMAP m_hBitmapTemp, m_hBitmapDis;
	LPPICTURE m_lppicShow;
	CImage img;
public:
	Flower(int posX);
	~Flower();
	void move();
	void stop();
};