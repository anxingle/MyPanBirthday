
#include "stdafx.h"
#include "Flower.h"

Flower::Flower(int posX)
{
	CRect rcWorkArea;
	SystemParametersInfo(SPI_GETWORKAREA, 0, (PVOID)&rcWorkArea, 0);
	//////////////////// get the handler of desktop ////////////////////////////
	HWND hProgMan = FindWindow(_T("ProgMan"),NULL); // return the highest level window
	if(hProgMan)
	{
		HWND hShellDefView = FindWindowEx(hProgMan, NULL,_T("SHELLDLL_DefView"), NULL);
		if(hShellDefView)
		{
			m_hwndDesktop = FindWindowEx(hShellDefView, NULL, _T("SysListView32"), NULL);
		}
		else
		{
			MessageBox(NULL, _T("cannot find the desktop after SHELLDLL_DefView"), NULL, MB_OK);
			return;
		}
	}
	else 
	{
		MessageBox(NULL, _T("cannot find the desktop"), NULL, MB_OK);
		return;
	}
	////////////////////////////////////////////////////////////////////////////////////
	m_curPosX = posX;
	m_curPosY = 0;
	m_curDireciton = CENTER;
	m_timeDir = 0;

	m_hdcDesk = GetDC(m_hwndDesktop);
	m_cdcDesk.Attach(m_hdcDesk);
	m_cdcMem.CreateCompatibleDC(&m_cdcDesk);
	/////////////////////// load the picture under the specific directory //////////////////
	
	int nImgNum  = rand()%PIC_NUM + 1;              // create the number of picture that would be show
	CString csImgName;
	csImgName.Format(_T("\\bir\\xiao%d.jpg"),nImgNum);
	char DirPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,(LPWSTR)DirPath);
	CString csDirPath((LPCTSTR)DirPath);
	csDirPath.Insert(555,csImgName);                        // get the final path of picture, include the directory and filename
	
	/////////////////////// load the picture ///////////////////////
	OleLoadPicturePath(csDirPath.AllocSysString(), NULL, NULL, NULL, IID_IPicture, (LPVOID*)&m_lppicShow);
	if(m_lppicShow==NULL)
	{
		MessageBox(NULL, _T("cannot find the image~!"), NULL, MB_OK);
		return;
	}
	m_lppicShow->get_Width(&m_picWidth);
	m_lppicShow->get_Height(&m_picHeight);
	m_lppicShow->get_Handle((UINT*)&m_hBitmapTemp);       // get the handler of picture
	m_hBitmapDis = (HBITMAP)CopyImage(m_hBitmapTemp, IMAGE_BITMAP, m_picWidth/DIVE, m_picHeight/DIVE, LR_COPYDELETEORG);
	m_cdcMem.SelectObject(m_hBitmapDis);
	m_cdcDesk.BitBlt(m_curPosX, m_curPosY, m_picWidth/DIVE, m_picHeight/DIVE, &m_cdcMem, 0,0, SRCCOPY);
}
Flower::~Flower()
{
	CRect rect;
	SetRect(rect, m_curPosX, m_curPosY, m_curPosX+m_picWidth/DIVE, m_curPosY+m_picHeight/DIVE);
	RedrawWindow(m_hwndDesktop, &rect, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW);
	m_cdcMem.DeleteDC();
	m_cdcDesk.DeleteDC();
}

void Flower::move()
{
	CRect rcWorkArea, rect;
	SystemParametersInfo(SPI_GETWORKAREA, 0, (PVOID)&rcWorkArea, 0);
	
	int nDesktopWidth =  rcWorkArea	.Width();
	int nDesktopHeight = rcWorkArea.Height();
	if(m_hdcDesk == NULL)
		return;
	
	SetRect(rect, m_curPosX, m_curPosY, m_curPosX+m_picWidth/DIVE, m_curPosY+m_picHeight/DIVE);
	RedrawWindow(m_hwndDesktop, &rect, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW);
	m_curPosY += PIC_MOVE_STEP;
	m_timeDir ++;
	if(m_timeDir >= TIME_TO_CHANGE)
	{
		//int temp = rand()%3;
		switch(rand()%3)
		{
		case 0:
			m_curDireciton = -1;
			break;
		case 1:
			m_curDireciton = 0;
			break;
		case 2:
			m_curDireciton = 1;
			break;
		}
		m_timeDir = 0;
	}
	m_curPosX += m_curDireciton;
	if(m_curPosY > nDesktopHeight)
	{
		m_curPosX = rand()*nDesktopWidth/RAND_MAX;
		m_curPosY = 0;

		/////////////////////// load the picture under the specific directory //////////////////
		int nImgNum  = rand()%PIC_NUM + 1;              // create the number of picture that would be show
		CString csImgName;
		csImgName.Format(_T("\\bir\\xiao%d.jpg"),nImgNum);
		char DirPath[MAX_PATH];
		GetCurrentDirectory(MAX_PATH,(LPWSTR)DirPath);
		CString csDirPath((LPCTSTR)DirPath);
		csDirPath.Insert(555,csImgName);                        // get the final path of picture, include the directory and filename

		/////////////////////// load the picture ///////////////////////
		OleLoadPicturePath(csDirPath.AllocSysString(), NULL, NULL, NULL, IID_IPicture, (LPVOID*)&m_lppicShow);
		if(m_lppicShow==NULL)
		{
			MessageBox(NULL, _T("cannot find the image~!"), NULL, MB_OK);
			return;
		}
		m_lppicShow->get_Width(&m_picWidth);
		m_lppicShow->get_Height(&m_picHeight);
		m_lppicShow->get_Handle((OLE_HANDLE*)&m_hBitmapTemp);       // get the handler of picture
		m_hBitmapDis = (HBITMAP)CopyImage(m_hBitmapTemp, IMAGE_BITMAP, m_picWidth/DIVE, m_picHeight/DIVE, LR_COPYDELETEORG);
		m_cdcMem.SelectObject(m_hBitmapDis);
	}
	m_cdcDesk.BitBlt(m_curPosX, m_curPosY, m_picWidth/DIVE, m_picHeight/DIVE, &m_cdcMem, 0,0, SRCCOPY);
}
void Flower::stop()
{
	CRect rect;
	SetRect(rect, m_curPosX, m_curPosY, m_curPosX+m_picWidth/DIVE, m_curPosY+m_picHeight/DIVE);
	RedrawWindow(m_hwndDesktop, &rect, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW);
}