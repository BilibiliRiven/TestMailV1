#pragma once
#include "afxwin.h"


// CDialogProcess 对话框

class CDialogProcess : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogProcess)

public:
	CDialogProcess(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogProcess();

// 对话框数据
	enum { IDD = IDD_PROCESSBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_nProcess;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	int GetProcess();
	int m_nPrc;
	afx_msg void OnBnClickedOk();
};
