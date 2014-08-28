#include "stdafx.h"
#include "MyFont.h"

MyFont::MyFont(int x, int y,LPCTSTR str,UINT type)
{
	int nLen = wsprintf(m_content,str);
	
	HWND hProgMan = FindWindow(_T("ProgMan"),NULL);
	if(hProgMan)
	{
		m_hWndDesktop = FindWindowEx(hProgMan, NULL, _T("SHELLDLL_DefView"), NULL);
		if(m_hWndDesktop)
		{
			m_hWndDesktop = FindWindowEx(m_hWndDesktop, NULL, _T("SysListView32"), NULL);
		}
		else
			MessageBox(NULL, _T("error~"),NULL,MB_OK);
	}
	hdcDesk = GetDC(m_hWndDesktop);
	cdcDesk.Attach(hdcDesk);
	m_font.CreateFont(70,35, 0,0, FW_NORMAL, false,false,false,
		             CHINESEBIG5_CHARSET, OUT_CHARACTER_PRECIS,
					 CLIP_CHARACTER_PRECIS, DRAFT_QUALITY,
					 FF_MODERN,_T("Î¢ÈíÑÅºÚ"));
	HGDIOBJ oldFont = (HGDIOBJ)cdcDesk.SelectObject(m_font);
	cdcDesk.SetBkMode(TRANSPARENT);
	cdcDesk.SetTextColor(0x000000f0);
	cdcDesk.ExtTextOutW(x,y, ETO_OPAQUE, NULL, m_content,NULL);
	m_curPosX = x;
	m_curPosY = y;
	m_dirDown = true;
	//cdcDesk.SelectObject(&oldFont);
}
MyFont::~MyFont()
{
	CRect rect;
	SetRect(rect, m_curPosX, m_curPosY,m_curPosX+85,m_curPosY+70);
	RedrawWindow(m_hWndDesktop,&rect,0,RDW_INVALIDATE | RDW_ERASE  | RDW_UPDATENOW );
	cdcDesk.DeleteDC();
}
int MyFont::Bounce()
{
	if(m_dirDown)
		m_curPosY+=2;
	else m_curPosY-=2;
	if(m_curPosY>=BOUNCE_BOT)
	{
		m_curPosY = BOUNCE_BOT;
		m_dirDown = false;
	}
	else if(m_curPosY<=BOUNCE_TOP)
	{
		m_curPosY = BOUNCE_TOP;
		m_dirDown = true;
	}
	CRect rect;
	SetRect(rect, m_curPosX, m_curPosY,m_curPosX+85,m_curPosY+70);
	
	CFont *oldFont = (CFont*)cdcDesk.SelectObject(m_font);
	cdcDesk.SetBkMode(TRANSPARENT);
	cdcDesk.SetTextColor(0x000000f0);
	RedrawWindow(m_hWndDesktop,&rect,0,RDW_INVALIDATE | RDW_ERASE  | RDW_UPDATENOW );
	cdcDesk.ExtTextOutW(m_curPosX,m_curPosY, ETO_OPAQUE, NULL, m_content,NULL);
	int time = (BOUNCE_BOT-m_curPosY)/3+2;
	return time;
}

