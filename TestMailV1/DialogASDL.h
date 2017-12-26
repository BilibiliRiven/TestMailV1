#pragma once
#include "afxwin.h"


// CDialogASDL 对话框

class CDialogASDL : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogASDL)

public:
	CDialogASDL(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogASDL();

// 对话框数据
	enum { IDD = IDD_PREADSL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ctrlPerIp;
	int m_nPerIp;
	afx_msg void OnEnChangeEditProcess();
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	int GetASDL(){ return m_nPerIp; }
};
