// DialogProcess.cpp : 实现文件
//

#include "stdafx.h"
#include "TestMailV1.h"
#include "DialogProcess.h"
#include "afxdialogex.h"


// CDialogProcess 对话框

IMPLEMENT_DYNAMIC(CDialogProcess, CDialogEx)

CDialogProcess::CDialogProcess(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogProcess::IDD, pParent)
{

}

CDialogProcess::~CDialogProcess()
{
}

void CDialogProcess::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PROCESS, m_nProcess);
}


BEGIN_MESSAGE_MAP(CDialogProcess, CDialogEx)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDOK, &CDialogProcess::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogProcess 消息处理程序


int CDialogProcess::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	return 0;
}


BOOL CDialogProcess::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_nProcess.SetWindowText(TEXT("1"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


int CDialogProcess::GetProcess()
{	

	return m_nPrc;
}


void CDialogProcess::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CString temp;
	m_nProcess.GetWindowText(temp);
	m_nPrc = boost::lexical_cast<int>(temp.GetBuffer());
	CDialogEx::OnOK();
}
