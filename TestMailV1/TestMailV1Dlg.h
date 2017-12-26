
// TestMailV1Dlg.h : ͷ�ļ�
//

#pragma once
#include "DialogProcess.h"
#include "DialogDelay.h"
#include "DialogASDL.h"
#include "afxcmn.h"
#include "afxwin.h"
typedef struct TAG_ACCOUNT{
	CString Mail;
	CString Password;
	BOOL bValied;
}ACCOUNT;

// CTestMailV1Dlg �Ի���
class CTestMailV1Dlg : public CDialogEx
{
// ����
public:
	CTestMailV1Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TESTMAILV1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnExport();
	afx_msg void OnBnClickedBtnImport();
private:
	CString m_strSPath;
	CString m_strDPath;
	CString m_cstrSeverName;
	std::vector<ACCOUNT> m_SetsAccount;
	int m_nProcess; // �߳�����
	int m_nCPUCore; // CPU��������

	int m_nDelay;   // �ӳ�ʱ��
	int m_CurrentProc; // �Կ����߳�����
	std::vector<std::string> m_vecSegTag;
	int m_nState;   // ��Ӧ3��״̬ 0��δ���� 1������δ���
	int m_nPerIpForAccount;
	CMap<CStringA, const char *, CStringA, const char *> m_Pop3Dic;
public:
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedOk();
	CProgressCtrl m_ctrProgress;
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_MailList;
	CEdit m_ctrMailServer;
	afx_msg void OnMenuImport();
	afx_msg void OnMenuExport(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedButton6();
	afx_msg void OnMenuSetProcess();
	afx_msg void OnMenuSetDelay();
	void Clear(){
		m_MailList.DeleteAllItems();
		m_SetsAccount.clear();
	}
	static DWORD WINAPI Thread(LPVOID lpParam);
	static DWORD WINAPI ThreadProgress(LPVOID lpParam);
	afx_msg void OnDestroy();
	BOOL IsRunning();
	/*
	*	����Pop3�ֵ�
	*	���磺����958403316@qq.com
	*	����qq.com����ѯPop3�ֵ䣬����֪����������QQ��Pop3���ʼ���������
	*/
	void LoadPop3Dictionary();
	afx_msg void On32776();
};
