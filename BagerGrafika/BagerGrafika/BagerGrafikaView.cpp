
// BagerGrafikaView.cpp : implementation of the CBagerGrafikaView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "BagerGrafika.h"
#endif

#include "BagerGrafikaDoc.h"
#include "BagerGrafikaView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBagerGrafikaView

IMPLEMENT_DYNCREATE(CBagerGrafikaView, CView)

BEGIN_MESSAGE_MAP(CBagerGrafikaView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CBagerGrafikaView construction/destruction

CBagerGrafikaView::CBagerGrafikaView() noexcept
{
	// TODO: add construction code here
	bager->Load(CString("C:\\Users\\Milos Milenkovic\\Downloads\\GDI2018Resursi\\bager.png"));
	arm1->Load(CString("C:\\Users\\Milos Milenkovic\\Downloads\\GDI2018Resursi\\arm1.png"));
	arm2->Load(CString("C:\\Users\\Milos Milenkovic\\Downloads\\GDI2018Resursi\\arm2.png"));
	pozadina->Load(CString("C:\\Users\\Milos Milenkovic\\Downloads\\GDI2018Resursi\\pozadina.png"));
	viljuska = GetEnhMetaFile(CString("C:\\Users\\Milos Milenkovic\\Downloads\\GDI2018Resursi\\viljuska.emf"));
}

CBagerGrafikaView::~CBagerGrafikaView()
{
	delete bager;
	delete arm1;
	delete arm2;
	delete pozadina;
	DeleteEnhMetaFile(viljuska);
}


BOOL CBagerGrafikaView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CBagerGrafikaView drawing

void CBagerGrafikaView::OnDraw(CDC* pDC)
{
	CBagerGrafikaDoc* pDoc = GetDocument();
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
	Translate(MemDC, pozadina->Width()/1.3, pozadina->Height()/1.7, false);
	DrawExcavator(MemDC);

	MemDC->SetWorldTransform(&xform);
	pDC->BitBlt(0, 0, rt.Width(), rt.Height(), MemDC, 0, 0, SRCCOPY);
	MemDC->DeleteDC();
	delete MemDC;
	// TODO: add draw code for native data here
}

void CBagerGrafikaView::Translate(CDC* pDC, float dX, float dY, bool rightMultiply)
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

void CBagerGrafikaView::Rotate(CDC* pDC, float angle, bool rightMultiply)
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

void CBagerGrafikaView::Scale(CDC* pDC, float sX, float sY, bool rightMultiply)
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

void CBagerGrafikaView::DrawBackground(CDC* pDC)
{
	CRect rt;
	GetClientRect(rt);

	int x, y, w, h;

	x = (rt.Width() - pozadina->Width()) / 2;
	y = rt.Height() - pozadina->Height();

	w = x + pozadina->Width();
	h = y + pozadina->Height();

	pozadina->Draw(pDC, CRect(0, 0, pozadina->Width(), pozadina->Height()), CRect(x, y, w, h));
}

void CBagerGrafikaView::DrawImgTransparent(CDC* pDC, DImage* pImage)
{
	int w = pImage->Width();
	int h = pImage->Height();
	CRect rt(0, 0, w, h);

	BYTE* b = pImage->GetDIBBits();
	COLORREF boja = RGB(b[2], b[1], b[0]);

	pImage->DrawTransparent(pDC, rt, rt, boja);

}

void CBagerGrafikaView::DrawExcavator(CDC* pDC)
{
	DrawBody(pDC);
	DrawArm1(pDC);
	DrawArm2(pDC);
	DrawFork(pDC);
}

void CBagerGrafikaView::DrawBody(CDC* pDC)
{
	Translate(pDC, 0 + pomeraj, 0, false);
	DrawImgTransparent(pDC, bager);
}

void CBagerGrafikaView::DrawArm1(CDC* pDC)
{
	Translate(pDC,64, 169, false);
	Rotate(pDC, arm1angle, false);
	Translate(pDC, -58, -61, false);
	DrawImgTransparent(pDC, arm1);
}

void CBagerGrafikaView::DrawArm2(CDC* pDC)
{
	Translate(pDC, 309, 61, false);
	Rotate(pDC, arm2angle, false);
	Translate(pDC, -36, -40, false);
	DrawImgTransparent(pDC, arm2);
}

void CBagerGrafikaView::DrawFork(CDC* pDC)
{
	Translate(pDC, 272, 40, false);
	Scale(pDC, 2.5, 2.5, false);
	Rotate(pDC, viljuskaangle, false);
	Translate(pDC, -14, -20, false);

	ENHMETAHEADER hdr;
	GetEnhMetaFileHeader(viljuska, sizeof(hdr), &hdr);
	int w = hdr.rclBounds.right - hdr.rclBounds.left;
	int h = hdr.rclBounds.bottom - hdr.rclBounds.top;
	CRect rect(0, 0, w, h);
	PlayEnhMetaFile(pDC->m_hDC, viljuska, rect);
}


// CBagerGrafikaView printing

BOOL CBagerGrafikaView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBagerGrafikaView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBagerGrafikaView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CBagerGrafikaView diagnostics

#ifdef _DEBUG
void CBagerGrafikaView::AssertValid() const
{
	CView::AssertValid();
}

void CBagerGrafikaView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBagerGrafikaDoc* CBagerGrafikaView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBagerGrafikaDoc)));
	return (CBagerGrafikaDoc*)m_pDocument;
}
#endif //_DEBUG


// CBagerGrafikaView message handlers

BOOL CBagerGrafikaView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE;
}

void CBagerGrafikaView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	if (nChar == '1')
		arm1angle += 10;
	if (nChar == '2')
		arm1angle -= 10;

	if (nChar == '3')
		arm2angle += 10;
	if (nChar == '4')
		arm2angle -= 10;

	if (nChar == '5')
		viljuskaangle += 10;
	if (nChar == '6')
		viljuskaangle -= 10;


	if (nChar == VK_LEFT)
		pomeraj -= 10;
	if (nChar == VK_RIGHT)
		pomeraj += 10;

	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
