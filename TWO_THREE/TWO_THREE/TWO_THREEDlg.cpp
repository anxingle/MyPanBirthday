
// TWO_THREEDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TWO_THREE.h"
#include "TWO_THREEDlg.h"
#include "afxdialogex.h"
#include "Flower.h"

#include <Vfw.H>
//////////// 界
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTWO_THREEDlg dialog



CTWO_THREEDlg::CTWO_THREEDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTWO_THREEDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTWO_THREEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LBK_PIC, m_lbkPic);
	DDX_Control(pDX, IDC_RBK_PIC, m_rbkPic);
	DDX_Control(pDX, IDC_XIAO_PIC, m_xiaoPic);
	DDX_Control(pDX, IDC_BLOOM_OR_FADE, m_checkBloom);
}

BEGIN_MESSAGE_MAP(CTWO_THREEDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BLOOM_OR_FADE, &CTWO_THREEDlg::OnClickedBloomOrFade)
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CTWO_THREEDlg message handlers

BOOL CTWO_THREEDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	InitDlg();
	CheckDlgButton(IDC_BLOOM_OR_FADE,1);
	OnClickedBloomOrFade();
	return TRUE;  // return TRUE  unless you set the focus to a control
}
void CTWO_THREEDlg::InitDlg()
{
	HBITMAP hBitmap, hBitmap_new;
	CImage img;
	int img_xLen, img_yLen;
	char chDirPath[MAX_PATH];
	/////////// 获取工作区左边背景图片 /////////////////////
	GetCurrentDirectory(MAX_PATH,(LPWSTR)chDirPath);
	CString csDirPath((LPCTSTR)chDirPath);
	csDirPath.Insert(555,_T("\\bir\\lbk_pic.jpg"));        /// 获取完整的图片路径
	img.Load(csDirPath);
	img_xLen = img.GetWidth();
	img_yLen = img.GetHeight();
	hBitmap = img.Detach();
	hBitmap_new = (HBITMAP)CopyImage(hBitmap,IMAGE_BITMAP,410,280,LR_COPYDELETEORG);
	m_lbkPic.SetBitmap(hBitmap_new);
	CString csDirPath1((LPCTSTR)chDirPath);
	csDirPath1.Insert(555,_T("\\bir\\1234.jpg"));        /// 获取完整的图片路径
	img.Load(csDirPath1);
	img_xLen = img.GetWidth();
	img_yLen = img.GetHeight();
	hBitmap = img.Detach();
	hBitmap_new = (HBITMAP)CopyImage(hBitmap,IMAGE_BITMAP,img_xLen,img_yLen,LR_COPYDELETEORG);
	m_rbkPic.SetBitmap(hBitmap_new);

	img.LoadFromResource(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BITMAP1));
	img_xLen = img.GetWidth();
	img_yLen = img.GetHeight();
	hBitmap = img.Detach();
	hBitmap_new = (HBITMAP)CopyImage(hBitmap,IMAGE_BITMAP,img_xLen/8,img_yLen/8,LR_COPYDELETEORG);
	m_xiaoPic.SetBitmap(hBitmap_new);
	//MP3
	HWND hMCI; 
	//CString choose = _T("C:\\My heart.mp3"); //音乐文件的路径
	CString csDirPath3((LPCTSTR)chDirPath);
	csDirPath3.Insert(555,_T("\\bir\\a.mp3"));
	hMCI = MCIWndCreate(NULL, NULL,WS_POPUP|MCIWNDF_NOPLAYBAR|MCIWNDF_NOMENU,csDirPath3);  
	MCIWndPlay(hMCI); //播放音乐   
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTWO_THREEDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTWO_THREEDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTWO_THREEDlg::OnClickedBloomOrFade()
{
	static int flag = 1;          // the status flag of the program, whether the flower to move
	static CUIntArray arrTimers;
	static CUIntArray arrPositions;

	if(flag == 1)
	{
		///////////// the initialize of the flower and font on the screen //////////
		CRect rcWorkArea;
		SystemParametersInfo(SPI_GETWORKAREA, 0, (PVOID)&rcWorkArea, 0);
		int nTimer, nPosX, nPosY;
		srand((unsigned)time(NULL));
		int i;
		for(i=0; i<DIS_NUM; i++)
		{
			nTimer = rand()*50/RAND_MAX + 10;
			arrTimers.Add(nTimer);
			nPosX = rand()*rcWorkArea.Width()/RAND_MAX;
			arrPositions.Add(nPosX);
		}
		for(i=0; i<DIS_NUM; i++)
		{
			nTimer = arrTimers.GetAt(i);
			nPosX  = arrPositions.GetAt(i);
			Flower *pFlower = new Flower(nPosX);
			m_arrFlowers.Add(pFlower);
			SetTimer(i+1,nTimer,NULL);
		}
		int averWidth = rcWorkArea.Width()/6;
		int ballPosX[6] = {100,averWidth,averWidth*2,averWidth*3,averWidth*4,averWidth*5-100 };
		TCHAR *dis_words[15]={_T("盼"),_T("盼"),_T("生"),_T("日"),_T("快"),_T("乐")};
		for(i=0;i<6;i++)
		{
			nPosX = ballPosX[i];
			nPosY = rand()%(BOUNCE_BOT-BOUNCE_TOP)+200;
			MyFont *pMyFont = new MyFont(nPosX, nPosY, (LPCTSTR)dis_words[i],1);
			m_arrMyFonts.Add(pMyFont);
			nTimer = (BOUNCE_BOT-nPosY)/2+2;
			SetTimer(DIS_NUM+i+1,nTimer, NULL);
		}
		flag = 2;
	}
	if(1==m_checkBloom.GetCheck()&&flag!=2)
	{
		flag = 2;
		int nTimer;
		int i;
		for(i=0; i<m_arrFlowers.GetSize(); i++)
		{
			Flower* pFlower = m_arrFlowers.GetAt(i);
			nTimer = arrTimers.GetAt(i);
			if(pFlower)
			{
				pFlower->move();
				SetTimer(i+1,nTimer,NULL);
			}
		}
	}
	else if(0==m_checkBloom.GetCheck()&&flag!=3)
	{
		flag = 3;
		for(int i=0; i<m_arrFlowers.GetSize(); i++)
		{
			Flower* pFlower = m_arrFlowers.GetAt(i);
			if(pFlower)
			{
				KillTimer(i+1);
				pFlower->stop();
			}
		}
	}
}


void CTWO_THREEDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent>=0 && nIDEvent <= m_arrFlowers.GetSize())
	{
		Flower* pFlower = m_arrFlowers.GetAt(nIDEvent-1);
		if(pFlower)
			pFlower->move();
	}
	if(nIDEvent>m_arrFlowers.GetSize())
	{
		int size = m_arrFlowers.GetSize();
		MyFont *pMyFont = m_arrMyFonts.GetAt(nIDEvent-size-1);
		int time;
		if(pMyFont)
			time = pMyFont->Bounce();
		KillTimer(nIDEvent);
		SetTimer(nIDEvent,time, NULL);
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CTWO_THREEDlg::OnDestroy()
{
	for(int i=0; i<m_arrFlowers.GetSize(); i++)
	{
		Flower* pFlower = m_arrFlowers.GetAt(i);
		if(pFlower)
		{
			delete pFlower;
			pFlower = NULL;
		}
	}
	for(int i=0; i<6;i++)
	{
		MyFont *pMyFont = m_arrMyFonts.GetAt(i);
		if(pMyFont)
		{
			delete pMyFont;
			pMyFont = NULL;
		}
	}
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}
