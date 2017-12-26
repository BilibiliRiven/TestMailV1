// DialogASDL.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestMailV1.h"
#include "DialogASDL.h"
#include "afxdialogex.h"


// CDialogASDL �Ի���

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


// CDialogASDL ��Ϣ�������


void CDialogASDL::OnEnChangeEditProcess()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CDialogASDL::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
}


BOOL CDialogASDL::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ctrlPerIp.SetWindowText(TEXT("����IP(0)"));
	m_nPerIp = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CDialogASDL::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
