
// Kol1ponovoView.cpp : implementation of the CKol1ponovoView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Kol1ponovo.h"
#endif

#include "Kol1ponovoDoc.h"
#include "Kol1ponovoView.h"
#include"DImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKol1ponovoView

IMPLEMENT_DYNCREATE(CKol1ponovoView, CView)

BEGIN_MESSAGE_MAP(CKol1ponovoView, CView)
	// Standard printing commands
	ON_WM_KEYDOWN() // <-- DODAJ OVO
	ON_WM_ERASEBKGND() // <-- DODAJ OVO
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CKol1ponovoView construction/destruction

CKol1ponovoView::CKol1ponovoView() noexcept
{
	// TODO: add construction code here
	img3->Load(CString("C:\\Users\\Milos Milenkovic\\Desktop\\Racunarska-Grafika\\slike\\body1.png"));
	img1->Load(CString("C:\\Users\\Milos Milenkovic\\Desktop\\Racunarska-Grafika\\slike\\arm1.png"));
	img2->Load(CString("C:\\Users\\Milos Milenkovic\\Desktop\\Racunarska-Grafika\\slike\\arm2.png"));
	img4->Load(CString("C:\\Users\\Milos Milenkovic\\Desktop\\Racunarska-Grafika\\slike\\leg1.png"));
	img5->Load(CString("C:\\Users\\Milos Milenkovic\\Desktop\\Racunarska-Grafika\\slike\\leg2.png"));
	img6->Load(CString("C:\\Users\\Milos Milenkovic\\Desktop\\Racunarska-Grafika\\slike\\background.jpg"));
}

CKol1ponovoView::~CKol1ponovoView()
{
	delete img1;
	delete img2;
	delete img3;
	delete img4;
	delete img5;
	delete img6;
}



BOOL CKol1ponovoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CKol1ponovoView drawing

void CKol1ponovoView::OnDraw(CDC* pDC)
{
	CKol1ponovoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;
	GetClientRect(&rect);
	CDC* pMemDC = new CDC();
	pMemDC->CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	pMemDC->SelectObject(&bmp);

	int oldMode = pMemDC->SetGraphicsMode(GM_ADVANCED);
	XFORM xformOld;
	pMemDC->GetWorldTransform(&xformOld);

	DrawBackground(pMemDC, CRect(0, 0, rect.Width(), rect.Height()));

	//Translate(pMemDC, 300, 200, false);
	DrawTransformer(pMemDC);


	pMemDC->SetWorldTransform(&xformOld);
	pMemDC->SetGraphicsMode(oldMode);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), pMemDC, 0, 0, SRCCOPY);
	pMemDC->DeleteDC();
	delete pMemDC;

	// TODO: add draw code for native data here
}

void CKol1ponovoView::DrawBackground(CDC* pDC, CRect rc)
{
	int w = img6->Width();
	int h = img6->Height();

	CRect novo(0, 0, w, h);
	img6->Draw(pDC, novo, rc);
}

void CKol1ponovoView::DrawImgTransparent(CDC* pDC, DImage* pImage)
{
	int w = pImage->Width();
	int h = pImage->Height();

	CRect rect(0, 0, w, h);
	BYTE* bytes = pImage->GetDIBBits();
	COLORREF color = RGB(bytes[2], bytes[1], bytes[0]);
	pImage->DrawTransparent(pDC, rect, rect, color);
}

void CKol1ponovoView::Translate(CDC* pDC, float dX, float dY, bool rightMultiply)
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

void CKol1ponovoView::Rotate(CDC* pDC, float angle, bool rightMultiply)
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

void CKol1ponovoView::DrawBody1(CDC* pDC)
{
	XFORM xform;
	pDC->GetWorldTransform(&xform);
	Translate(pDC, 315, 598, false);
	Rotate(pDC, body1angle, false);
	XFORM bodyBaseXform;
	pDC->GetWorldTransform(&bodyBaseXform);
	Translate(pDC, -26, -133, false);
	DrawImgTransparent(pDC, img3);
	pDC->SetWorldTransform(&bodyBaseXform);
	Translate(pDC, 185, -47, false);
	DrawArm1(pDC);
	pDC->SetWorldTransform(&bodyBaseXform);
	Translate(pDC, -210, -3, false);
	DrawLeg1(pDC);
	pDC->SetWorldTransform(&xform);
}
void CKol1ponovoView::DrawArm1(CDC* pDC)
{
	XFORM xform;
	pDC->GetWorldTransform(&xform);
	Rotate(pDC, arm1angle, false);
	XFORM arm1BaseXform;
	pDC->GetWorldTransform(&arm1BaseXform);
	Translate(pDC, -34, -31, false);
	DrawImgTransparent(pDC, img1);
	pDC->SetWorldTransform(&arm1BaseXform);
	Translate(pDC, 175, 70, false);
	DrawArm2(pDC);

	pDC->SetWorldTransform(&xform);
}
void CKol1ponovoView::DrawArm2(CDC* pDC)
{
	Rotate(pDC, arm2angle, false);
	Translate(pDC, -23, -61, false);
	DrawImgTransparent(pDC, img2);
}

void CKol1ponovoView::DrawLeg1(CDC* pDC)
{
	XFORM xform;
	pDC->GetWorldTransform(&xform);
	Translate(pDC, 210, 3, false);
	Rotate(pDC, leg1angle, false);
	Translate(pDC, -210, -3, false);
	XFORM leg1BaseXform;
	pDC->GetWorldTransform(&leg1BaseXform);
	Translate(pDC, 0, 0, false);
	DrawLeg2(pDC);
	pDC->SetWorldTransform(&leg1BaseXform);
	Translate(pDC, -30, -125, false);
	DrawImgTransparent(pDC, img4);
	pDC->SetWorldTransform(&xform);
}

void CKol1ponovoView::DrawLeg2(CDC* pDC)
{
	Rotate(pDC, leg2angle, false);
	Translate(pDC, -35, -60, false);
	DrawImgTransparent(pDC, img5);
}


void CKol1ponovoView::DrawTransformer(CDC* pDC)
{
	DrawBody1(pDC);
}


// CKol1ponovoView printing

BOOL CKol1ponovoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CKol1ponovoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CKol1ponovoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CKol1ponovoView diagnostics

#ifdef _DEBUG
void CKol1ponovoView::AssertValid() const
{
	CView::AssertValid();
}

void CKol1ponovoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

BOOL CKol1ponovoView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CKol1ponovoView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 'Q' || nChar == 'q')
		arm1angle += 10;
	if (nChar == 'A' || nChar == 'a')
		arm1angle -= 10;
	if (nChar == 'T' || nChar == 't')
		arm2angle += 10;
	if (nChar == 'G' || nChar == 'g')
		arm2angle -= 10;
	if (nChar == 'R' || nChar == 'r')
		leg2angle += 10;
	if (nChar == 'F' || nChar == 'f')
		leg2angle -= 10;
	if (nChar == 'W' || nChar == 'w')
		body1angle += 10;
	if (nChar == 'S' || nChar == 's')
		body1angle -= 10;
	if (nChar == 'Y' || nChar == 'y')
		leg1angle += 10;
	if (nChar == 'H' || nChar == 'h')
		leg1angle -= 10;

	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

CKol1ponovoDoc* CKol1ponovoView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKol1ponovoDoc)));
	return (CKol1ponovoDoc*)m_pDocument;
}
#endif //_DEBUG


// CKol1ponovoView message handlers
