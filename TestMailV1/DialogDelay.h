#pragma once
#include "afxwin.h"


// CDialogDelay 对话框

class CDialogDelay : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogDelay)

public:
	CDialogDelay(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogDelay();

// 对话框数据
	enum { IDD = IDD_DELAYBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//CEdit m_nDelay;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	int GetDelay();
	int m_nDelay;
	CEdit m_ctrDelay;
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedOk();
};
