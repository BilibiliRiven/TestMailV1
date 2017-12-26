
// TestMailV1Dlg.h : 头文件
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

// CTestMailV1Dlg 对话框
class CTestMailV1Dlg : public CDialogEx
{
// 构造
public:
	CTestMailV1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TESTMAILV1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	int m_nProcess; // 线程数量
	int m_nCPUCore; // CPU核心数量

	int m_nDelay;   // 延迟时间
	int m_CurrentProc; // 以开启线程数量
	std::vector<std::string> m_vecSegTag;
	int m_nState;   // 对应3种状态 0：未导入 1：导入未检测
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
	*	加载Pop3字典
	*	例如：邮箱958403316@qq.com
	*	根据qq.com，查询Pop3字典，可以知道必须连接QQ的Pop3的邮件服务器。
	*/
	void LoadPop3Dictionary();
	afx_msg void On32776();
};
