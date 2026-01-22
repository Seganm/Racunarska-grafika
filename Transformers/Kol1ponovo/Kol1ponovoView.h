
// Kol1ponovoView.h : interface of the CKol1ponovoView class
//

#pragma once
#include"DImage.h"

class CKol1ponovoView : public CView
{
protected: // create from serialization only
	CKol1ponovoView() noexcept;
	DECLARE_DYNCREATE(CKol1ponovoView)

// Attributes
public:
	CKol1ponovoDoc* GetDocument() const;
	DImage* img1 = new DImage();
	DImage* img2 = new DImage();
	DImage* img3 = new DImage();
	DImage* img4 = new DImage();
	DImage* img5 = new DImage();
	DImage* img6 = new DImage();

	int body1angle = 0;
	int arm1angle = 0;
	int arm2angle = 0;
	int leg1angle = 0;
	int leg2angle = 0;

// Operations
public:




// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	void DrawBackground(CDC* pDC, CRect rc);
	void DrawImgTransparent(CDC* pDC, DImage* pImage);
	void Translate(CDC* pDC, float dX, float dY, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);
	void DrawArm1(CDC* pDC);
	void DrawArm2(CDC* pDC);
	void DrawLeg1(CDC* pDC);
	void DrawLeg2(CDC* pDC);
	void DrawBody1(CDC* pDC);
	void DrawTransformer(CDC* pDC);

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CKol1ponovoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in Kol1ponovoView.cpp
inline CKol1ponovoDoc* CKol1ponovoView::GetDocument() const
   { return reinterpret_cast<CKol1ponovoDoc*>(m_pDocument); }
#endif

