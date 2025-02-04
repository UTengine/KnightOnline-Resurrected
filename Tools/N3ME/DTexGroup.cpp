// DTexGroup.cpp: implementation of the CDTexGroup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "n3me.h"
#include "LyTerrainDef.h"
#include "MainFrm.h"
#include "DTexMng.h"
#include "DTex.h"

#include "DTexGroup.h"

CDTexGroup::CDTexGroup()
{
	ZeroMemory(m_Name, 40);
	m_ID = 0;
}

CDTexGroup::~CDTexGroup()
{
	Release();
}


//
//	Release..
//
void CDTexGroup::Release()
{
	for(int i = DTEX_FULL; i < DTEX_MAX; i++)
	{
		it_DTexTileAttr it = m_Attributes[i].begin();
		int iSize = m_Attributes[i].size();
		for(int j = 0; j < iSize; j++, it++)
		{
			DTEXTILEATTR* pTile = *it;
			delete pTile;
		}
		m_Attributes[i].clear();
	}
}


//
//	Init..
//
void CDTexGroup::Init()
{
	Release();

	ZeroMemory(m_Name, 40);
	m_ID = 0;
}


//
//	SetAttr..
//
void CDTexGroup::SetAttr(int attr, DTEXTILEATTR tile)
{
	if( ( attr >= DTEX_FULL ) && ( attr < DTEX_MAX ) )
	{
		LPDTEXTILEATTR pTile = new DTEXTILEATTR;
		pTile->TexID = tile.TexID;
		pTile->TileX = tile.TileX;
		pTile->TileY = tile.TileY;
		m_Attributes[attr].push_back(pTile);
	}
}


//
//	DelAttr..
//
void CDTexGroup::DelAttr(int attr, DTEXTILEATTR tile)
{
	if( ( attr >= DTEX_FULL ) && ( attr < DTEX_MAX ) )
	{
		it_DTexTileAttr it = m_Attributes[attr].begin();
		int iSize = m_Attributes[attr].size();
		for(int i = 0; i < iSize; i++, it++)
		{
			DTEXTILEATTR* pTile = *it;
			if((pTile->TexID == tile.TexID) && (pTile->TileX == tile.TileX) && (pTile->TileY == tile.TileY))
			{
				delete pTile;
				it = m_Attributes[attr].erase(it);
				break;
			}
		}
	}
}


//
//
//
void CDTexGroup::DelAttrByDTexID(int DTexID)
{
	it_DTexTileAttr it; 
	for(int i=DTEX_FULL; i<DTEX_MAX; i++)
	{
		//리스트 돌면서 DTexIndx와 같은거 나오면 다 없애버려...
		it = m_Attributes[i].begin();
		while(it!=m_Attributes[i].end())
		{
			DTEXTILEATTR* pTile = *it;
			if(pTile->TexID == DTexID)
			{
				//지우자...
				delete (*it);
				it = m_Attributes[i].erase(it);
			}
			else it++;
		}		
	}
}


//
//	DTexMng에 있는 정보들 청소...
//	DTex에 저장되어 있는 현재 그룹 정보를 NONE으로 셋팅..
//
void CDTexGroup::ClearDTex()
{
	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	CDTexMng* pDTexMng = pFrm->GetDTexMng();

	for(int i=DTEX_FULL; i<DTEX_MAX; i++)
	{
		it_DTexTileAttr it = m_Attributes[i].begin();
		int iSize = m_Attributes[i].size();
		for(int j = 0; j < iSize; j++, it++)
		{
			DTEXTILEATTR* pTile = *it;
			CDTex* pDTex = pDTexMng->GetDTexByID(pTile->TexID);

			if(pDTex)
			{
				pDTex->m_Attr[pTile->TileX][pTile->TileY].Group = 0;
				pDTex->m_Attr[pTile->TileX][pTile->TileY].Attr = pTile->TileX;
			}
		}
	}
}
