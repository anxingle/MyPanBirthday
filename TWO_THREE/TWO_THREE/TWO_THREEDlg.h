
// TWO_THREEDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "Flower.h"
#include "MyFont.h"


// CTWO_THREEDlg dialog
class CTWO_THREEDlg : public CDialogEx
{
// Construction
public:
	CTWO_THREEDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TWO_THREE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClickedBloomOrFade();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()
private:
	void InitDlg();
public:
	CStatic m_lbkPic, m_rbkPic, m_xiaoPic;
	CArray<Flower*, Flower*> m_arrFlowers;
	CArray<MyFont*, MyFont*> m_arrMyFonts;
	CButton m_checkBloom;
	
};
