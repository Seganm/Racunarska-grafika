
// BagerGrafikaView.h : interface of the CBagerGrafikaView class
//

#pragma once
#include "DImage.h"

class CBagerGrafikaView : public CView
{
protected: // create from serialization only
	CBagerGrafikaView() noexcept;
	DECLARE_DYNCREATE(CBagerGrafikaView)

// Attributes
public:
	CBagerGrafikaDoc* GetDocument() const;
	DImage* bager = new DImage();
	DImage* arm1 = new DImage();
	DImage* arm2 = new DImage();
	DImage* pozadina = new DImage();
	HENHMETAFILE viljuska;

	int arm1angle = -90;
	int arm2angle = -90;
	int viljuskaangle = 0;

	int pomeraj = 0;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	void Translate(CDC* pDC, float dX, float dY, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);
	void Scale(CDC* pDC, float sX, float sY, bool rightMultiply);
	void DrawBackground(CDC* pDC);
	void DrawImgTransparent(CDC* pDC, DImage* pImage);
	void DrawBody(CDC* pDC);
	void DrawArm1(CDC* pDC);
	void DrawArm2(CDC* pDC);
	void DrawFork(CDC* pDC);
	void DrawExcavator(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CBagerGrafikaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in BagerGrafikaView.cpp
inline CBagerGrafikaDoc* CBagerGrafikaView::GetDocument() const
   { return reinterpret_cast<CBagerGrafikaDoc*>(m_pDocument); }
#endif

