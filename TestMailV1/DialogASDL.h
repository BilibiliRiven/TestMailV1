#pragma once
#include "afxwin.h"


// CDialogASDL �Ի���

class CDialogASDL : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogASDL)

public:
	CDialogASDL(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogASDL();

// �Ի�������
	enum { IDD = IDD_PREADSL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
