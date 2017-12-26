// DialogDelay.cpp : 实现文件
//

#include "stdafx.h"
#include "TestMailV1.h"
#include "DialogDelay.h"
#include "afxdialogex.h"


// CDialogDelay 对话框

IMPLEMENT_DYNAMIC(CDialogDelay, CDialogEx)

CDialogDelay::CDialogDelay(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogDelay::IDD, pParent)
	, m_nDelay(30)
{

}

CDialogDelay::~CDialogDelay()
{
}

void CDialogDelay::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_EDIT1, m_nDelay);
	DDX_Control(pDX, IDC_EDIT_DELAY, m_ctrDelay);
}


BEGIN_MESSAGE_MAP(CDialogDelay, CDialogEx)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDOK, &CDialogDelay::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogDelay 消息处理程序


int CDialogDelay::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}


BOOL CDialogDelay::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ctrDelay.SetWindowText(TEXT("30"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


int CDialogDelay::GetDelay()
{

	return 0;
	//return 	m_ctrDelay.GetDlgItemInt(IDC_EDIT_DELAY, NULL, 1);
}


void CDialogDelay::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
}


void CDialogDelay::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CString temp;
	m_ctrDelay.GetWindowText(temp);
	m_nDelay = boost::lexical_cast<int>(temp.GetBuffer());
	CDialogEx::OnOK();
}
