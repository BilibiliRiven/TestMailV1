// DialogDelay.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestMailV1.h"
#include "DialogDelay.h"
#include "afxdialogex.h"


// CDialogDelay �Ի���

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


// CDialogDelay ��Ϣ�������


int CDialogDelay::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}


BOOL CDialogDelay::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ctrDelay.SetWindowText(TEXT("30"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


int CDialogDelay::GetDelay()
{

	return 0;
	//return 	m_ctrDelay.GetDlgItemInt(IDC_EDIT_DELAY, NULL, 1);
}


void CDialogDelay::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
}


void CDialogDelay::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString temp;
	m_ctrDelay.GetWindowText(temp);
	m_nDelay = boost::lexical_cast<int>(temp.GetBuffer());
	CDialogEx::OnOK();
}
