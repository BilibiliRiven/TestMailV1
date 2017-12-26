// DialogProcess.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestMailV1.h"
#include "DialogProcess.h"
#include "afxdialogex.h"


// CDialogProcess �Ի���

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


// CDialogProcess ��Ϣ�������


int CDialogProcess::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	return 0;
}


BOOL CDialogProcess::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_nProcess.SetWindowText(TEXT("1"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


int CDialogProcess::GetProcess()
{	

	return m_nPrc;
}


void CDialogProcess::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString temp;
	m_nProcess.GetWindowText(temp);
	m_nPrc = boost::lexical_cast<int>(temp.GetBuffer());
	CDialogEx::OnOK();
}
