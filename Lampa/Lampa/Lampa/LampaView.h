
// LampaView.h : interface of the CLampaView class
//

#pragma once
#include "DImage.h"

class CLampaView : public CView
{
protected: // create from serialization only
	CLampaView() noexcept;
	DECLARE_DYNCREATE(CLampaView)

// Attributes
public:
	CLampaDoc* GetDocument() const;
	DImage* base = new DImage();
	DImage* arm1 = new DImage();
	DImage* arm2 = new DImage();
	DImage* head = new DImage();
	DImage* pozadina = new DImage();
	DImage* base_shadow = new DImage();
	DImage* arm1_shadow = new DImage();
	DImage* arm2_shadow = new DImage();
	DImage* head_shadow = new DImage();

	int arm1_angle = -45;
	int arm2_angle = -90;
	int head_angle = 180;


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
	void DrawLampBase(CDC* pDC, bool bIsShadow);
	void DrawLampArm1(CDC* pDC, bool bIsShadow);
	void DrawLampArm2(CDC* pDC, bool bIsShadow);
	void DrawLampHead(CDC* pDC, bool bIsShadow);
	void DrawLamp(CDC* pDC, bool bIsShadow);
	void DrawLampShadow(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CLampaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in LampaView.cpp
inline CLampaDoc* CLampaView::GetDocument() const
   { return reinterpret_cast<CLampaDoc*>(m_pDocument); }
#endif

