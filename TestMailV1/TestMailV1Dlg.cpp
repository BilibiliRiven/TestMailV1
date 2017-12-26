
// TestMailV1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestMailV1.h"
#include "TestMailV1Dlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CTestMailV1Dlg �Ի���



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


// CTestMailV1Dlg ��Ϣ�������

BOOL CTestMailV1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	//CoInitialize(NULL);
	//m_cstrSeverName = TEXT("pop.163.com");
	SetDlgItemText(IDC_EDIT3, m_cstrSeverName);
	m_ctrProgress.SetRange(0, 100);
	m_CurrentProc = 0;
	system("regsvr32.exe jmail.dll");
	m_nPerIpForAccount = 0;

	m_MailList.InsertColumn(0, TEXT("���"), LVCFMT_LEFT, 60);
	m_MailList.InsertColumn(1, TEXT("����"), LVCFMT_LEFT, 120);
	m_MailList.InsertColumn(2, TEXT("����"), LVCFMT_LEFT, 120);
	m_MailList.InsertColumn(3, TEXT("״̬"), LVCFMT_LEFT, 50);
	m_MailList.InsertColumn(4, TEXT("Pop3��������"), LVCFMT_LEFT, 60);

	SYSTEM_INFO si;

	GetSystemInfo(&si);

	m_nCPUCore = si.dwNumberOfProcessors;

	LoadPop3Dictionary();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestMailV1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTestMailV1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestMailV1Dlg::OnBnClickedBtnExport()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_nState == 0){
		MessageBox(TEXT("�����ļ�δ���\r\n"), MB_OK);
		return;
	}
	
	
	
	if (IsRunning()){
		MessageBox(TEXT("������ֵ֤���䣬�����ĵȴ�\r\n"),TEXT("��ʾ"),MB_OK|MB_ICONWARNING);
		return;
	}



	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, TEXT("�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||"), this);

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
		MessageBox(TEXT("����Դ�ļ������ߣ��ļ��Ѿ�����"), MB_OK);
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
	MessageBox(TEXT("�������\r\n"), TEXT("��ʾ"), MB_OK);
}


void CTestMailV1Dlg::OnBnClickedBtnImport()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, TEXT("�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||"), this);

	if (IDOK == fileDlg.DoModal()){
		m_strSPath = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT1, m_strSPath.GetBuffer(0));
	}
	else{
		return;
	}

	m_nState = 0; // ����״̬

	HANDLE hFile = CreateFile(m_strSPath.GetBuffer(0),
		GENERIC_READ,
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(TEXT("Դ�ļ�������߱�ռ��"), MB_OK);
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
		MessageBox(TEXT("�ļ�ӳ��ʧ��, ���������"), MB_OK);
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
		m_MailList.SetItemText(m_SetsAccount.size() - 1, 3, temp.bValied == 0? TEXT("δ��֤"):TEXT("�쳣"));
	}
}


void CTestMailV1Dlg::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}






typedef struct TAG_THREAD_ARG{
	LPVOID This;
	int nNum;
	int nStep; // ����������,�����õ�
}THREAD_ARG;
THREAD_ARG g_ThreadArg[20] = {0};
void CTestMailV1Dlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_SetsAccount.size() == 0){
		MessageBox(TEXT("�޵����ļ�\r\n"),MB_OK);
		return;
	}



	m_ctrMailServer.GetWindowText(m_cstrSeverName);
	if (!IsRunning()){
		m_nState = 1; // �ı�״̬��
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
		MessageBox(TEXT("�����ĵȴ��������������е��߳�\r\n"));
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
		boost::split(MailTag, strMailAccount, boost::is_any_of("@")); // �ָ������˺�
		CStringA Pop3SeverName = "";
		pThis->m_Pop3Dic.Lookup(MailTag[1].c_str(), Pop3SeverName);  // ���ݷָ��Ĺؼ���׺������Pop3������
		if (Pop3SeverName.IsEmpty()){
			Pop3SeverName.Format("pop.%s", MailTag[1].c_str());		// ����ʧ�ܣ��²�Pop3����������
		}
		CString cstrPop3SeverName;
		cstrPop3SeverName = Pop3SeverName;
		// ��ӡPop3��������
		pThis->m_MailList.SetItemText(i, 4, cstrPop3SeverName);
		pThis->m_ctrMailServer.SetWindowTextW(cstrPop3SeverName);
		
		_bstr_t bstrServerName = Pop3SeverName;
		_bstr_t bstrAaccount = (pThis->m_SetsAccount[i]).Mail.GetBuffer(0);
		_bstr_t bstrPassword = (pThis->m_SetsAccount[i]).Password.GetBuffer(0);

		jmail::IPOP3Ptr pPOP3("JMail.POP3");
		pPOP3->Timeout = pThis->m_nDelay; // �������ӷ�������ʱ���� 30S

		try{
			pPOP3->Connect(bstrAaccount, bstrPassword, bstrServerName, 110);

			pThis->m_SetsAccount[i].bValied = 1;
			pThis->m_MailList.SetItemText(i,3,TEXT("*��Ч"));
		}
		catch (_com_error e)
		{
			pThis->m_SetsAccount[i].bValied = 2;
			pThis->m_MailList.SetItemText(i, 3, TEXT("��Ч"));
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
				// ���������ASDL��������
				//system("");
				pThis->MessageBox(TEXT("\r\n"));
			}
		}
		Sleep(10);
	}
	pThis->MessageBox(TEXT("������\r\n"),TEXT("��ʾ"),MB_OK);
	return 0;
}




void CTestMailV1Dlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CTestMailV1Dlg::OnMenuImport()
{
	// TODO:  �ڴ���������������
	OnBnClickedBtnImport();
}


void CTestMailV1Dlg::OnMenuExport(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������
	OnBnClickedBtnExport();
}


void CTestMailV1Dlg::OnBnClickedButton6()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	MessageBox(TEXT("���ȵ�������\r\n��ʽ�����˺�----��������\r\nע�⣺һ��һ��"), TEXT("������"), MB_OK|MB_ICONWARNING);
}


void CTestMailV1Dlg::OnMenuSetProcess()
{
	// TODO:  �ڴ���������������
	if (!IsRunning()){
		CDialogProcess Dlg;
		Dlg.DoModal();
		m_nProcess = Dlg.GetProcess();
	}
	else{
		MessageBox(TEXT("�����ĵȴ��������������е��߳�\r\n���ڼ�������˺�\r\n"));
	}
}







void CTestMailV1Dlg::OnMenuSetDelay()
{
	// TODO:  �ڴ���������������

	CDialogDelay Dlg;
	Dlg.DoModal();

	m_nDelay = Dlg.GetDelay();
}


void CTestMailV1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	//CoUninitialize();
	// TODO:  �ڴ˴������Ϣ����������
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
	// TODO:  �ڴ���������������
	MessageBox(TEXT("���������POP3Э����֤�����Ƿ���Ч\r\n���ȵ��������ļ�\r\n�����ļ���ʽ��ʽ�����˺�----��������\r\nע�⣺һ��һ��"), TEXT("������"), MB_OK | MB_ICONWARNING);
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
		MessageBox(TEXT("Դ�ļ�������߱�ռ��"), MB_OK);
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
		MessageBox(TEXT("�ļ�ӳ��ʧ��, ���������"), MB_OK);
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
			MessageBox(TEXT("Pop3Dict.txt��ʽ��������Pop3Dict.txt�ļ�"),TEXT("��ʾ��"),MB_OK||MB_ICONWARNING);
			ExitProcess(0);
		}
		m_Pop3Dic.SetAt(strMailSuffix, strPop3ServerName);
	}
}

void CTestMailV1Dlg::On32776()
{
	// TODO:  �ڴ���������������
	CDialogASDL Dlg;
	Dlg.DoModal();

	m_nPerIpForAccount = Dlg.GetASDL();
}
