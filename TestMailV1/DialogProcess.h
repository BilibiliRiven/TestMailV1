#pragma once
#include "afxwin.h"


// CDialogProcess �Ի���

class CDialogProcess : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogProcess)

public:
	CDialogProcess(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogProcess();

// �Ի�������
	enum { IDD = IDD_PROCESSBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_nProcess;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	int GetProcess();
	int m_nPrc;
	afx_msg void OnBnClickedOk();
};
