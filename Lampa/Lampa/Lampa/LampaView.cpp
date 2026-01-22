
// LampaView.cpp : implementation of the CLampaView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Lampa.h"
#endif

#include "LampaDoc.h"
#include "LampaView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLampaView

IMPLEMENT_DYNCREATE(CLampaView, CView)

BEGIN_MESSAGE_MAP(CLampaView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CLampaView construction/destruction

CLampaView::CLampaView() noexcept
{
	// TODO: add construction code here
	base->Load(CString("C:\\Users\\Milos Milenkovic\\Desktop\\git\\Racunarska-Grafika\\Lampa\\Lampa\\resursi\\base.png"));
	base_shadow->Load(CString("C:\\Users\\Milos Milenkovic\\Desktop\\git\\Racunarska-Grafika\\Lampa\\Lampa\\resursi\\base_shadow.png"));
	arm1->Load(CString("C:\\Users\\Milos Milenkovic\\Desktop\\git\\Racunarska-Grafika\\Lampa\\Lampa\\resursi\\arm1.png"));
	arm2->Load(CString("C:\\Users\\Milos Milenkovic\\Desktop\\git\\Racunarska-Grafika\\Lampa\\Lampa\\resursi\\arm2.png"));
	arm1_shadow->Load(CString("C:\\Users\\Milos Milenkovic\\Desktop\\git\\Racunarska-Grafika\\Lampa\\Lampa\\resursi\\arm1_shadow.png"));
	arm2_shadow->Load(CString("C:\\Users\\Milos Milenkovic\\Desktop\\git\\Racunarska-Grafika\\Lampa\\Lampa\\resursi\\arm2_shadow.png"));
	head->Load(CString("C:\\Users\\Milos Milenkovic\\Desktop\\git\\Racunarska-Grafika\\Lampa\\Lampa\\resursi\\head.png"));
	head_shadow->Load(CString("C:\\Users\\Milos Milenkovic\\Desktop\\git\\Racunarska-Grafika\\Lampa\\Lampa\\resursi\\head_shadow.png"));
	pozadina->Load(CString("C:\\Users\\Milos Milenkovic\\Desktop\\git\\Racunarska-Grafika\\Lampa\\Lampa\\resursi\\pozadina.jpg"));
}

CLampaView::~CLampaView()
{
	delete base;
	delete base_shadow;
	delete arm1;
	delete arm1_shadow;
	delete arm2;
	delete arm2_shadow;
	delete head;
	delete head_shadow;
	delete pozadina;
}

void CLampaView::DrawLamp(CDC* pDC, bool bIsShadow)
{
	XFORM xformOld;
	pDC->GetWorldTransform(&xformOld);
	DrawLampBase(pDC, bIsShadow);
	DrawLampArm1(pDC, bIsShadow);
	DrawLampHead(pDC, bIsShadow);
	DrawLampArm2(pDC, bIsShadow);
	pDC->SetWorldTransform(&xformOld);

}

void CLampaView::DrawLampShadow(CDC* pDC)
{
	XFORM xform;
	pDC->GetWorldTransform(&xform);
	Scale(pDC, 1, 0.25, false);
	Rotate(pDC, -90, false);
	DrawLamp(pDC, true);
	pDC->SetWorldTransform(&xform);
}

BOOL CLampaView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CLampaView drawing

void CLampaView::OnDraw(CDC* pDC)
{
	CLampaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rt;
	GetClientRect(rt);

	CDC* MemDC = new CDC();
	MemDC->CreateCompatibleDC(pDC);

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(pDC, rt.Width(), rt.Height());

	MemDC->SelectObject(bitmap);

	int old = MemDC->SetGraphicsMode(GM_ADVANCED);

	XFORM xform;
	MemDC->GetWorldTransform(&xform);

	DrawBackground(MemDC);
	Translate(MemDC, rt.Width() / 2, rt.Height() - 200, false);
	DrawLampShadow(MemDC);
	DrawLamp(MemDC, false);


	
	MemDC->SetWorldTransform(&xform);
	MemDC->SetGraphicsMode(old);
	pDC->BitBlt(0, 0, rt.Width(), rt.Height(), MemDC, 0, 0, SRCCOPY);


	MemDC->DeleteDC();
	delete MemDC;
	// TODO: add draw code for native data here
}

void CLampaView::Translate(CDC* pDC, float dX, float dY, bool rightMultiply)
{
	XFORM xform;
	xform.eM11 = 1;
	xform.eM12 = 0;
	xform.eM21 = 0;
	xform.eM22 = 1;
	xform.eDx = dX;
	xform.eDy = dY;

	pDC->ModifyWorldTransform(&xform, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CLampaView::Rotate(CDC* pDC, float angle, bool rightMultiply)
{
	XFORM xform;
	xform.eM11 = cos(angle* 3.14159265358979323846/180);
	xform.eM12 = sin(angle * 3.14159265358979323846 / 180);
	xform.eM21 = -sin(angle * 3.14159265358979323846 / 180);
	xform.eM22 = cos(angle * 3.14159265358979323846 / 180);
	xform.eDx = 0;
	xform.eDy = 0;

	pDC->ModifyWorldTransform(&xform, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CLampaView::Scale(CDC* pDC, float sX, float sY, bool rightMultiply)
{
	XFORM xform;
	xform.eM11 = sX;
	xform.eM12 = 0;
	xform.eM21 = 0;
	xform.eM22 = sY;
	xform.eDx = 0;
	xform.eDy = 0;

	pDC->ModifyWorldTransform(&xform, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CLampaView::DrawBackground(CDC* pDC)
{
	CRect rt;
	GetClientRect(rt);
	int x, y, w, h;
	x = (rt.Width() - pozadina->Width()) / 2;
	w = x + pozadina->Width();
	y = rt.Height() - pozadina->Height();
	h = y + pozadina->Height();

	pozadina->Draw(pDC, CRect(0, 0, pozadina->Width(), pozadina->Height()), CRect(x, y, w, h));
}

void CLampaView::DrawImgTransparent(CDC* pDC, DImage* pImage)
{
	int w = pImage->Width();
	int h = pImage->Height();
	
	CRect novo(0, 0, w, h);
	BYTE* b = pImage->GetDIBBits();
	COLORREF boja = RGB(b[2], b[1], b[0]);

	pImage->DrawTransparent(pDC, novo, novo, boja);
}

void CLampaView::DrawLampBase(CDC* pDC, bool bIsShadow)
{
	Translate(pDC, -80, -70, false);
	DrawImgTransparent(pDC, bIsShadow ? base_shadow : base);
}

void CLampaView::DrawLampArm1(CDC* pDC, bool bIsShadow)
{

	Translate(pDC, 158, 10, false);
	Rotate(pDC, arm1_angle, false);
	Translate(pDC, -58, -61, false);
	DrawImgTransparent(pDC, bIsShadow ? arm1_shadow : arm1);
}

void CLampaView::DrawLampArm2(CDC* pDC, bool bIsShadow)
{
	Translate(pDC, 309, 61, false);
	Rotate(pDC, arm2_angle, false);
	Translate(pDC, -36, -40, false);
	DrawImgTransparent(pDC, bIsShadow ? arm2_shadow : arm2);
    
}

void CLampaView::DrawLampHead(CDC* pDC, bool bIsShadow)
{
	XFORM xform;
	pDC->GetWorldTransform(&xform);
	Translate(pDC, 309, 61, false);
	Rotate(pDC, arm2_angle, false);
	Translate(pDC, -36, -40, false);

	Translate(pDC, 272, 40, false);
	Rotate(pDC, head_angle, false);
	Translate(pDC, -178, -100, false);

	DrawImgTransparent(pDC, bIsShadow ? head_shadow : head);

	pDC->SetWorldTransform(&xform);
}


// CLampaView printing

BOOL CLampaView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLampaView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLampaView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CLampaView diagnostics

#ifdef _DEBUG
void CLampaView::AssertValid() const
{
	CView::AssertValid();
}

void CLampaView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLampaDoc* CLampaView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLampaDoc)));
	return (CLampaDoc*)m_pDocument;
}
#endif //_DEBUG


// CLampaView message handlers

void CLampaView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (nChar == '1')
		arm1_angle += 10;
	if (nChar == '2')
		arm1_angle -= 10;
	if (nChar == '3')
		arm2_angle += 10;
	if (nChar == '4')
		arm2_angle -= 10;
	if (nChar == '5')
		head_angle += 10;
	if (nChar == '6')
		head_angle -= 10;

	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CLampaView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE;
}
