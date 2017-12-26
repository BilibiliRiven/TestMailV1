
// TestMailV1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestMailV1.h"
#include "TestMailV1Dlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHelpAbout();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)

	ON_COMMAND(ID_32775, &CAboutDlg::OnHelpAbout)
END_MESSAGE_MAP()


// CTestMailV1Dlg 对话框



CTestMailV1Dlg::CTestMailV1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestMailV1Dlg::IDD, pParent)
	, m_nDelay(30)
	, m_nProcess(1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestMailV1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_ctrProgress);
	DDX_Control(pDX, IDC_LIST1, m_MailList);
	DDX_Control(pDX, IDC_EDIT3, m_ctrMailServer);
}

BEGIN_MESSAGE_MAP(CTestMailV1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CTestMailV1Dlg::OnBnClickedBtnExport)
	ON_BN_CLICKED(IDC_BUTTON1, &CTestMailV1Dlg::OnBnClickedBtnImport)
	ON_EN_CHANGE(IDC_EDIT2, &CTestMailV1Dlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDOK, &CTestMailV1Dlg::OnBnClickedOk)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CTestMailV1Dlg::OnLvnItemchangedList1)
	ON_COMMAND(ID_32771, &CTestMailV1Dlg::OnMenuImport)
	ON_UPDATE_COMMAND_UI(ID_32772, &CTestMailV1Dlg::OnMenuExport)
	ON_BN_CLICKED(IDC_BUTTON6, &CTestMailV1Dlg::OnBnClickedButton6)
	ON_COMMAND(ID_32773, &CTestMailV1Dlg::OnMenuSetProcess)
	ON_COMMAND(ID_32774, &CTestMailV1Dlg::OnMenuSetDelay)
	ON_WM_DESTROY()
	ON_COMMAND(ID_32776, &CTestMailV1Dlg::On32776)
END_MESSAGE_MAP()


// CTestMailV1Dlg 消息处理程序

BOOL CTestMailV1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	//CoInitialize(NULL);
	//m_cstrSeverName = TEXT("pop.163.com");
	SetDlgItemText(IDC_EDIT3, m_cstrSeverName);
	m_ctrProgress.SetRange(0, 100);
	m_CurrentProc = 0;
	system("regsvr32.exe jmail.dll");
	m_nPerIpForAccount = 0;

	m_MailList.InsertColumn(0, TEXT("编号"), LVCFMT_LEFT, 60);
	m_MailList.InsertColumn(1, TEXT("邮箱"), LVCFMT_LEFT, 120);
	m_MailList.InsertColumn(2, TEXT("密码"), LVCFMT_LEFT, 120);
	m_MailList.InsertColumn(3, TEXT("状态"), LVCFMT_LEFT, 50);
	m_MailList.InsertColumn(4, TEXT("Pop3服务器名"), LVCFMT_LEFT, 60);

	SYSTEM_INFO si;

	GetSystemInfo(&si);

	m_nCPUCore = si.dwNumberOfProcessors;

	LoadPop3Dictionary();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTestMailV1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestMailV1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTestMailV1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestMailV1Dlg::OnBnClickedBtnExport()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_nState == 0){
		MessageBox(TEXT("导入文件未检测\r\n"), MB_OK);
		return;
	}
	
	
	
	if (IsRunning()){
		MessageBox(TEXT("正在验证值邮箱，请耐心等待\r\n"),TEXT("提示"),MB_OK|MB_ICONWARNING);
		return;
	}



	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, TEXT("文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||"), this);

	if (IDOK == fileDlg.DoModal()){
		m_strDPath = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT2, m_strDPath.GetBuffer(0));
	}
	else{
		return;
	}


	HANDLE hFile2 = CreateFile(m_strDPath.GetBuffer(0),
		GENERIC_WRITE,
		NULL,
		NULL,
		CREATE_NEW,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (hFile2 == INVALID_HANDLE_VALUE){
		MessageBox(TEXT("创建源文件错误者，文件已经存在"), MB_OK);
		return;
	}

	m_ctrProgress.SetPos(0);
	for (unsigned int i = 0; i < m_SetsAccount.size(); ++i){
		if (m_SetsAccount[i].bValied == 1){
			CString temp;
			temp = m_SetsAccount[i].Mail;
			temp.Append(TEXT("----"));
			temp.Append(m_SetsAccount[i].Password);
			temp.Append(TEXT("\n"));
			DWORD dwWBtyes = NULL;
			CStringA temp2;
			temp2 = temp;
			WriteFile(hFile2, temp2.GetBuffer(0), temp2.GetLength(), &dwWBtyes, NULL);
			m_ctrProgress.SetPos(i*1.0 / m_SetsAccount.size() * 100);
		}
	}
	CloseHandle(hFile2);
	m_ctrProgress.SetPos(100);
	MessageBox(TEXT("导出完成\r\n"), TEXT("提示"), MB_OK);
}


void CTestMailV1Dlg::OnBnClickedBtnImport()
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, TEXT("文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||"), this);

	if (IDOK == fileDlg.DoModal()){
		m_strSPath = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT1, m_strSPath.GetBuffer(0));
	}
	else{
		return;
	}

	m_nState = 0; // 设置状态

	HANDLE hFile = CreateFile(m_strSPath.GetBuffer(0),
		GENERIC_READ,
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(TEXT("源文件错误或者被占用"), MB_OK);
		return;
	}

	HANDLE hMap = CreateFileMapping(
		hFile,
		NULL,
		PAGE_READONLY,
		0,
		0,
		NULL);

	if (hMap == NULL){
		MessageBox(TEXT("文件映射失败, 请结束程序"), MB_OK);
		//system("pause");
		return;
	}

	void* pvFile = MapViewOfFile(
		hMap,
		FILE_MAP_READ,
		0,
		0,
		0);

	std::string Tag((char *)pvFile);
	std::string Tag2 = boost::algorithm::erase_all_copy(Tag, "\r");

	boost::split(m_vecSegTag, Tag2, boost::is_any_of("-\n"));

	UnmapViewOfFile(pvFile);
	CloseHandle(hMap);
	CloseHandle(hFile);

	Clear();
	int k = 0;
	for (unsigned int i = 0; i + 4 < m_vecSegTag.size(); i += 5){
		ACCOUNT temp;
		temp.Mail = m_vecSegTag[i].c_str();
		temp.Password = m_vecSegTag[i + 4].c_str();
		temp.bValied = 0;
		m_SetsAccount.push_back(temp);

		CString num;
		num.Format(TEXT("%d"), m_SetsAccount.size());
		m_MailList.InsertItem(m_SetsAccount.size() - 1, num);
		m_MailList.SetItemText(m_SetsAccount.size() - 1, 1, temp.Mail);
		m_MailList.SetItemText(m_SetsAccount.size() - 1, 2, temp.Password);
		m_MailList.SetItemText(m_SetsAccount.size() - 1, 3, temp.bValied == 0? TEXT("未验证"):TEXT("异常"));
	}
}


void CTestMailV1Dlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}






typedef struct TAG_THREAD_ARG{
	LPVOID This;
	int nNum;
	int nStep; // 用来检查进度,计数用的
}THREAD_ARG;
THREAD_ARG g_ThreadArg[20] = {0};
void CTestMailV1Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_SetsAccount.size() == 0){
		MessageBox(TEXT("无导入文件\r\n"),MB_OK);
		return;
	}



	m_ctrMailServer.GetWindowText(m_cstrSeverName);
	if (!IsRunning()){
		m_nState = 1; // 改变状态量
		m_CurrentProc = m_nProcess;
		for (int i = 0; i < m_nProcess; ++i){
			g_ThreadArg[i].This = this;
			g_ThreadArg[i].nNum = i;
			g_ThreadArg[i].nStep = 0;
			CreateThread(NULL, NULL, Thread, g_ThreadArg + i, NULL, NULL);
		}
		CreateThread(NULL, NULL, ThreadProgress, this, NULL, NULL);
	}
	else{
		MessageBox(TEXT("请耐心等待，存在正在运行的线程\r\n"));
	}
}

DWORD WINAPI CTestMailV1Dlg::Thread(LPVOID lpParam){
	CoInitialize(NULL);
	THREAD_ARG * p = (THREAD_ARG *)lpParam;
	CTestMailV1Dlg * pThis = (CTestMailV1Dlg *)p->This;
	int nStemp = p->nNum;

	for (unsigned int i = p->nNum; i < pThis->m_SetsAccount.size(); i += pThis->m_nProcess){
		
		std::vector<std::string> MailTag;
		CStringA cstraMailAccount; 
		cstraMailAccount = (pThis->m_SetsAccount[i]).Mail.GetBuffer();
		std::string strMailAccount = cstraMailAccount;
		boost::split(MailTag, strMailAccount, boost::is_any_of("@")); // 分割有限账号
		CStringA Pop3SeverName = "";
		pThis->m_Pop3Dic.Lookup(MailTag[1].c_str(), Pop3SeverName);  // 根据分割后的关键后缀，查找Pop3服务器
		if (Pop3SeverName.IsEmpty()){
			Pop3SeverName.Format("pop.%s", MailTag[1].c_str());		// 查找失败，猜测Pop3服务器域名
		}
		CString cstrPop3SeverName;
		cstrPop3SeverName = Pop3SeverName;
		// 打印Pop3服务器名
		pThis->m_MailList.SetItemText(i, 4, cstrPop3SeverName);
		pThis->m_ctrMailServer.SetWindowTextW(cstrPop3SeverName);
		
		_bstr_t bstrServerName = Pop3SeverName;
		_bstr_t bstrAaccount = (pThis->m_SetsAccount[i]).Mail.GetBuffer(0);
		_bstr_t bstrPassword = (pThis->m_SetsAccount[i]).Password.GetBuffer(0);

		jmail::IPOP3Ptr pPOP3("JMail.POP3");
		pPOP3->Timeout = pThis->m_nDelay; // 设置连接服务器超时限制 30S

		try{
			pPOP3->Connect(bstrAaccount, bstrPassword, bstrServerName, 110);

			pThis->m_SetsAccount[i].bValied = 1;
			pThis->m_MailList.SetItemText(i,3,TEXT("*有效"));
		}
		catch (_com_error e)
		{
			pThis->m_SetsAccount[i].bValied = 2;
			pThis->m_MailList.SetItemText(i, 3, TEXT("无效"));
			TRACE(_T("ERROR"));
			OutputDebugString(e.Description());
		}
		p->nStep += 1;
	}
	p->nNum = 0;
	p->This = 0;
	CoUninitialize();
	return 0;
}

DWORD WINAPI CTestMailV1Dlg::ThreadProgress(LPVOID lpParam){
	CTestMailV1Dlg * pThis = (CTestMailV1Dlg *)lpParam;
	int nSum = 0;
	pThis->m_ctrProgress.SetPos(0);
	while (nSum != pThis->m_SetsAccount.size()){
		nSum = 0;
		for (int i = 0; i < pThis->m_nProcess; ++i){
			nSum += g_ThreadArg[i].nStep;
			pThis->m_ctrProgress.SetPos(nSum*1.0 / pThis->m_SetsAccount.size() * 100);

			if (pThis->m_nPerIpForAccount && 0 == (nSum%pThis->m_nPerIpForAccount)){
				// 在这里添加ASDL拨号命令
				//system("");
				pThis->MessageBox(TEXT("\r\n"));
			}
		}
		Sleep(10);
	}
	pThis->MessageBox(TEXT("检测完成\r\n"),TEXT("提示"),MB_OK);
	return 0;
}




void CTestMailV1Dlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}


void CTestMailV1Dlg::OnMenuImport()
{
	// TODO:  在此添加命令处理程序代码
	OnBnClickedBtnImport();
}


void CTestMailV1Dlg::OnMenuExport(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	OnBnClickedBtnExport();
}


void CTestMailV1Dlg::OnBnClickedButton6()
{
	// TODO:  在此添加控件通知处理程序代码
	MessageBox(TEXT("请先导入数据\r\n格式邮箱账号----邮箱密码\r\n注意：一行一条"), TEXT("批处理"), MB_OK|MB_ICONWARNING);
}


void CTestMailV1Dlg::OnMenuSetProcess()
{
	// TODO:  在此添加命令处理程序代码
	if (!IsRunning()){
		CDialogProcess Dlg;
		Dlg.DoModal();
		m_nProcess = Dlg.GetProcess();
	}
	else{
		MessageBox(TEXT("请耐心等待，存在正在运行的线程\r\n正在检测邮箱账号\r\n"));
	}
}







void CTestMailV1Dlg::OnMenuSetDelay()
{
	// TODO:  在此添加命令处理程序代码

	CDialogDelay Dlg;
	Dlg.DoModal();

	m_nDelay = Dlg.GetDelay();
}


void CTestMailV1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	//CoUninitialize();
	// TODO:  在此处添加消息处理程序代码
}


BOOL CTestMailV1Dlg::IsRunning()
{
	BOOL bRet = NULL;
	for (int i = 0; i < m_nProcess; ++i){
		if (g_ThreadArg[i].This != 0){
			bRet = TRUE;
			break;
		}
	}
	return bRet;
}


void CAboutDlg::OnHelpAbout()
{
	// TODO:  在此添加命令处理程序代码
	MessageBox(TEXT("本软件利用POP3协议验证邮箱是否有效\r\n请先导入数据文件\r\n数据文件格式格式邮箱账号----邮箱密码\r\n注意：一行一条"), TEXT("批处理"), MB_OK | MB_ICONWARNING);
}


void CTestMailV1Dlg::LoadPop3Dictionary(){
	HANDLE hFile = CreateFile( TEXT("Pop3Dict.txt"),
		GENERIC_READ,
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(TEXT("源文件错误或者被占用"), MB_OK);
		return;
	}

	HANDLE hMap = CreateFileMapping(
		hFile,
		NULL,
		PAGE_READONLY,
		0,
		0,
		NULL);

	if (hMap == NULL){
		MessageBox(TEXT("文件映射失败, 请结束程序"), MB_OK);
		//system("pause");
		return;
	}

	void* pvFile = MapViewOfFile(
		hMap,
		FILE_MAP_READ,
		0,
		0,
		0);

	std::string Tag((char *)pvFile);
	std::string Tag2 = boost::algorithm::erase_all_copy(Tag, "\r");


	std::vector<std::string> Pop3DictString;
	boost::split(Pop3DictString, Tag2, boost::is_any_of("-\n"));


	UnmapViewOfFile(pvFile);
	CloseHandle(hMap);
	CloseHandle(hFile);

	for (unsigned int i = 0; i + 4 < Pop3DictString.size(); i += 5){
		CStringA strMailSuffix = Pop3DictString[i].c_str();
		CStringA strPop3ServerName = Pop3DictString[i+4].c_str();
		if (strMailSuffix.IsEmpty() || strPop3ServerName.IsEmpty()){
			MessageBox(TEXT("Pop3Dict.txt格式错误，请检查Pop3Dict.txt文件"),TEXT("提示："),MB_OK||MB_ICONWARNING);
			ExitProcess(0);
		}
		m_Pop3Dic.SetAt(strMailSuffix, strPop3ServerName);
	}
}

void CTestMailV1Dlg::On32776()
{
	// TODO:  在此添加命令处理程序代码
	CDialogASDL Dlg;
	Dlg.DoModal();

	m_nPerIpForAccount = Dlg.GetASDL();
}
