
// TestMailV1.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTestMailV1App: 
// �йش����ʵ�֣������ TestMailV1.cpp
//

class CTestMailV1App : public CWinApp
{
public:
	CTestMailV1App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestMailV1App theApp;