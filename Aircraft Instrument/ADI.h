#if !defined(AFX_ADI_H__0494E238_FB29_48EE_A8DD_2FC462332706__INCLUDED_)
#define AFX_ADI_H__0494E238_FB29_48EE_A8DD_2FC462332706__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ADI.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CADI window

class CADI : public CStatic
{
// Construction
public:
	CADI();

// Attributes
public:
	float m_RollAngle;
	float m_Pitch;
	CRect m_Rect;
	int m_centerX;
	int m_centerY;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CADI)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetPitch(float fPitch);
	void SetRollAngle(float RollAngle);
	void OnDrawADI(int x,int y,Graphics& buffer);
	virtual ~CADI();

	// Generated message map functions
protected:
	//{{AFX_MSG(CADI)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADI_H__0494E238_FB29_48EE_A8DD_2FC462332706__INCLUDED_)
