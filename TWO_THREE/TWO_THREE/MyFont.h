#pragma once
#define BALL_NUM    6
#define BOUNCE_TOP  200
#define BOUNCE_BOT  500

class MyFont
{
private:
	int m_curPosX, m_curPosY;              //  the current potision x,y
	bool m_dirDown;
	TCHAR m_content[50];                     //  the content displayed on the desktop
	HWND m_hWndDesktop;                      //  the handler of desktop
	HDC hdcDesk;
	CDC cdcDesk;

	CFont m_font;                           
public:
	MyFont(int x,int y,LPCTSTR str,UINT type);
	~MyFont();
	int Bounce();
	void Stop();
};