// DialogASDL.cpp : 实现文件
//

#include "stdafx.h"
#include "TestMailV1.h"
#include "DialogASDL.h"
#include "afxdialogex.h"


// CDialogASDL 对话框

IMPLEMENT_DYNAMIC(CDialogASDL, CDialogEx)

CDialogASDL::CDialogASDL(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogASDL::IDD, pParent)
{

}

CDialogASDL::~CDialogASDL()
{
}

void CDialogASDL::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PROCESS, m_ctrlPerIp);
}


BEGIN_MESSAGE_MAP(CDialogASDL, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_PROCESS, &CDialogASDL::OnEnChangeEditProcess)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDOK, &CDialogASDL::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogASDL 消息处理程序


void CDialogASDL::OnEnChangeEditProcess()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CDialogASDL::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
}


BOOL CDialogASDL::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	// TODO:  在此添加额外的初始化
	m_ctrlPerIp.SetWindowText(TEXT("无序换IP(0)"));
	m_nPerIp = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CDialogASDL::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CString temp;
	m_ctrlPerIp.GetWindowText(temp);
	try{
		m_nPerIp = boost::lexical_cast<int>(temp.GetBuffer());
	}
	catch (...){
		m_nPerIp = 0;
	}
	CDialogEx::OnOK();
}
