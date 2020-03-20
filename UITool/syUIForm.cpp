// syUIForm.cpp: 구현 파일
//

#include "stdafx.h"
#include "UITool.h"
#include "syUIForm.h"
#include "afxdialogex.h"
#include "syTextureMgr.h"

// syUIForm 대화 상자

IMPLEMENT_DYNAMIC(syUIForm, CFormView)


syUIForm::syUIForm()
	: CFormView(IDD_syUIForm)
	, iRowLenth(4)
	
	, iCellCount(5)
	, icellSize(1)
	, b_SetHeight(FALSE)
	, b_SetTex(FALSE)
	, b_SetAlphaTex(FALSE)

	, iRadSlot(0)
{

}

syUIForm::~syUIForm()
{
}

syUIForm* syUIForm::CreateOne(CWnd* pParent)
{
	syUIForm* pForm = new syUIForm;
	pForm->Create(NULL, NULL, WS_CHILD | WS_VISIBLE,
		CRect(0, 0, 500, 500), pParent, 0, NULL);
	return pForm;
}

void syUIForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, iRowLen, iRowLenth);

	DDX_Text(pDX, iCellCnt, iCellCount);
	DDX_Text(pDX, iCellSize, icellSize);
	DDX_Check(pDX, chk_height, b_SetHeight);
	DDX_Check(pDX, chk_texture, b_SetTex);
	DDX_Check(pDX, chk_alphaDraw, b_SetAlphaTex);
	DDX_Control(pDX, IDC_SLIDER1, brushrad);
	DDX_Radio(pDX, IDC_RADIOR, iRadSlot);
	DDX_Control(pDX, IDC_LIST1, m_tex_list);
}


BEGIN_MESSAGE_MAP(syUIForm, CFormView)
	ON_BN_CLICKED(IDOK, &syUIForm::OnBnClickedOk)
	ON_EN_CHANGE(iRowLen, &syUIForm::OnEnChangeirowlen)
	ON_BN_CLICKED(chk_height, &syUIForm::OnBnClickedheight)
	ON_BN_CLICKED(chk_texture, &syUIForm::OnBnClickedtexture)
	ON_BN_CLICKED(BUTTON_LoadAlphaTex, &syUIForm::OnBnClickedLoadalphatex)
	ON_BN_CLICKED(chk_alphaDraw, &syUIForm::OnBnClickedalphadraw)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, &syUIForm::OnNMReleasedcaptureSlider1)
	ON_BN_CLICKED(IDC_RADIOR, &syUIForm::OnBnClickedRadior)
	ON_BN_CLICKED(IDC_RADIORG, &syUIForm::OnBnClickedRadiorg)
	ON_BN_CLICKED(IDC_RADIORB, &syUIForm::OnBnClickedRadiorb)
	ON_LBN_SELCHANGE(IDC_LIST1, &syUIForm::OnSelchangeList1)
	ON_BN_DOUBLECLICKED(IDC_RADIOR, &syUIForm::OnBnDoubleclickedRadior)
	ON_BN_DOUBLECLICKED(IDC_RADIORG, &syUIForm::OnBnDoubleclickedRadiorg)
	ON_BN_DOUBLECLICKED(IDC_RADIORB, &syUIForm::OnBnDoubleclickedRadiorb)
	ON_BN_CLICKED(IDC_BUTTON2, &syUIForm::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &syUIForm::OnBnClickedButton1)
END_MESSAGE_MAP()


// syUIForm 메시지 처리기


void syUIForm::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CUIToolApp* pApp = (CUIToolApp*)AfxGetApp();
	iRowLenth = pow(2, iRowLenth);
	iCellCount = pow(2, iCellCount);
	pApp->m_Tool.LoadMap(iRowLenth, iCellCount, icellSize);
	/*pApp->m_Tool.m_BaseParticle.m_vVelocity.x = m_fGravityX;
	pApp->m_Tool.m_BaseParticle.m_vVelocity.y = m_fGravityY;
	pApp->m_Tool.m_BaseParticle.m_vVelocity.z = m_fGravityZ;*/
}


void syUIForm::OnEnChangeirowlen()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void syUIForm::OnBnClickedheight()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CUIToolApp* pApp = (CUIToolApp*)AfxGetApp();
	pApp->m_Tool.IsSetMapHeight = b_SetHeight;
	 
}


void syUIForm::OnBnClickedtexture()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CUIToolApp* pApp = (CUIToolApp*)AfxGetApp();
	pApp->m_Tool.IsSetMapTex = b_SetTex;
}




void syUIForm::OnBnClickedLoadalphatex()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString selFileName;
	CFileDialog dlg(
		TRUE, L"dds", NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
		L"dds Files(*.dds)|*.dds|All Files(*.*)|*.*|", this
	);

	if (dlg.DoModal() == IDOK)
	{
		selFileName = dlg.GetPathName();

		//selFileName += dlg.GetFileName();		
		//AfxMessageBox(selFileName);
	
		int iID = I_TextureMgr.Load(g_pDevice, selFileName.GetBuffer());
		if (iID > 0)
		{
			
			CString texname = dlg.GetFileTitle() + "." + dlg.GetFileExt();
			m_tex_list.InsertString(m_tex_list.GetCount(), texname);
			m_texMap.insert(make_pair(texname, iID));
		}
	}
	

}
void syUIForm::OnSelchangeList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CUIToolApp* pApp = (CUIToolApp*)AfxGetApp();

	int i = 0;
	CString str;
	m_tex_list.GetText(m_tex_list.GetCurSel(), str);

	ITOR itor = m_texMap.find(str);

	if (itor != m_texMap.end())
	{
		int texidx = (*itor).second;
		pApp->m_Tool.m_changedtexID = texidx;
	}
	
}



void syUIForm::OnBnClickedalphadraw()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CUIToolApp* pApp = (CUIToolApp*)AfxGetApp();
	pApp->m_Tool.IsDrawAlpha = b_SetAlphaTex;
}



void syUIForm::OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CUIToolApp* pApp = (CUIToolApp*)AfxGetApp();
	float br = brushrad.GetPos();
	pApp->m_Tool.Setrad(br);
	*pResult = 0;
}


void syUIForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	brushrad.SetRange(-50, 50);
	brushrad.SetPos(0);
	brushrad.SetTicFreq(1);
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}




void syUIForm::OnBnClickedSetbrushcolor()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString selCol;
	CColorDialog dlg(RGB(0, 0, 0), CC_FULLOPEN);
	if (dlg.DoModal() == IDOK)
	{
		COLORREF color = dlg.GetColor();
		selCol.Format(L"%u,%u,%u",
			GetRValue(color),
			GetGValue(color),
			GetBValue(color));
		//AfxMessageBox(selCol);
		
	}
}


void syUIForm::OnBnClickedRadior()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CUIToolApp* pApp = (CUIToolApp*)AfxGetApp();
	pApp->m_Tool.m_brush.SetColor(D3DXVECTOR4(1,0,0,1));
}


void syUIForm::OnBnClickedRadiorg()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CUIToolApp* pApp = (CUIToolApp*)AfxGetApp();
	pApp->m_Tool.m_brush.SetColor(D3DXVECTOR4(0, 1, 0, 1));
}


void syUIForm::OnBnClickedRadiorb()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CUIToolApp* pApp = (CUIToolApp*)AfxGetApp();
	pApp->m_Tool.m_brush.SetColor(D3DXVECTOR4(0, 0, 1, 1));
}




void syUIForm::OnBnDoubleclickedRadior()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CString selFileName;
	CFileDialog dlg(
		TRUE, L"dds", NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
		L"dds Files(*.dds)|*.dds|All Files(*.*)|*.*|", this
	);

	if (dlg.DoModal() == IDOK)
	{
		selFileName = dlg.GetPathName();

		//selFileName += dlg.GetFileName();		
		//AfxMessageBox(selFileName);

		int iID = I_TextureMgr.Load(g_pDevice, selFileName.GetBuffer());
		CUIToolApp* pApp = (CUIToolApp*)AfxGetApp();
		pApp->m_Tool.m_Map.SetBGTex(0, iID);
		pApp->m_Tool.m_brush.SetColor(D3DXVECTOR4(1, 0, 0, 1));
	}
}


void syUIForm::OnBnDoubleclickedRadiorg()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CString selFileName;
	CFileDialog dlg(
		TRUE, L"dds", NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
		L"dds Files(*.dds)|*.dds|All Files(*.*)|*.*|", this
	);

	if (dlg.DoModal() == IDOK)
	{
		selFileName = dlg.GetPathName();

		//selFileName += dlg.GetFileName();		
		//AfxMessageBox(selFileName);

		int iID = I_TextureMgr.Load(g_pDevice, selFileName.GetBuffer());
		CUIToolApp* pApp = (CUIToolApp*)AfxGetApp();
		pApp->m_Tool.m_Map.SetBGTex(1, iID);
		pApp->m_Tool.m_brush.SetColor(D3DXVECTOR4(0, 1, 0, 1));
	}
}


void syUIForm::OnBnDoubleclickedRadiorb()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CString selFileName;
	CFileDialog dlg(
		TRUE, L"dds", NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
		L"dds Files(*.dds)|*.dds|All Files(*.*)|*.*|", this
	);

	if (dlg.DoModal() == IDOK)
	{
		selFileName = dlg.GetPathName();

		//selFileName += dlg.GetFileName();		
		//AfxMessageBox(selFileName);

		int iID = I_TextureMgr.Load(g_pDevice, selFileName.GetBuffer());
		CUIToolApp* pApp = (CUIToolApp*)AfxGetApp();
		pApp->m_Tool.m_Map.SetBGTex(2, iID);
		pApp->m_Tool.m_brush.SetColor(D3DXVECTOR4(0, 0, 1, 1));
	}
}


void syUIForm::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CUIToolApp* pApp = (CUIToolApp*)AfxGetApp();
	pApp->m_Tool.nodeTexList.clear();
	for (ITOR itor = m_texMap.begin(); itor != m_texMap.end(); itor++)
	{
		int texidx = (*itor).second;
		pApp->m_Tool.nodeTexList.push_back(texidx);
	}
	pApp->m_Tool.FileSave();
}


void syUIForm::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CUIToolApp* pApp = (CUIToolApp*)AfxGetApp();
	pApp->m_Tool.LoadMapFromFile();
}
