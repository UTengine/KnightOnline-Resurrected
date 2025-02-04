// UILoadingDlg.cpp: implementation of the UILoadingDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UILoadingDlg.h"
#include "GameDef.h"
#include "../N3Base/N3UIProgress.h"
#include "../N3Base/N3UIString.h"

CUILoadingDlg::CUILoadingDlg()
{
	CUILoadingDlg::Release();
}

CUILoadingDlg::~CUILoadingDlg()
{
	CUILoadingDlg::Release();
}

void CUILoadingDlg::Release()
{
	CN3UIBase::Release();
}

CN3UIProgress* CUILoadingDlg::GetProcCtrl(char* str)
{
	return (CN3UIProgress*)(CN3UIBase::GetChildByID("pro_loading"));
}

bool CUILoadingDlg::Load(HANDLE hFile)
{
	if(CN3UIBase::Load(hFile)==false) return false;

	CN3UIString* pText = (CN3UIString*)(CN3UIBase::GetChildByID("Text_Version")); __ASSERT(pText, "NULL UI Component!!");
	if(pText)
	{
		char szVersion[128];
		sprintf(szVersion, "%.3f", CURRENT_VERSION/1000.0f);
		pText->SetString(szVersion);
	}
	
	return true;
}
