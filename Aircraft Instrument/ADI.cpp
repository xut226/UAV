// ADI.cpp : implementation file
//

#include "stdafx.h"
#include "Demo.h"
#include "ADI.h"
#include <math.h>
#include <string>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define PI 3.1415926
/////////////////////////////////////////////////////////////////////////////
// CADI

CADI::CADI()
{
	m_RollAngle = 0.0f;
	m_Pitch = 0.0f;
}

CADI::~CADI()
{
}


BEGIN_MESSAGE_MAP(CADI, CStatic)
	//{{AFX_MSG_MAP(CADI)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CADI message handlers

void CADI::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here
	CDC* pDc = GetDC();

	Graphics graphics(pDc->m_hDC);		//GDI对象
	CRect rect;
	GetClientRect(&m_Rect);
	Point center(m_Rect.CenterPoint().x,m_Rect.CenterPoint().y);
	
	m_centerX = center.X;
	m_centerY = center.Y;

	//窗口客户区中心坐标
	Bitmap CatchImage(m_Rect.Width(),m_Rect.Height());
	//声明内存画布
	Graphics buffer(&CatchImage);
	//声明与内存画布一致的缓冲区
	OnDrawADI(center.X,center.Y,buffer);
	//调用ADI绘制函数，并将客户区中心坐标和图形对象作为参数 
	buffer.SetSmoothingMode(SmoothingModeAntiAlias);	
	//设置图形和文本反走样模式 
	buffer.SetTextRenderingHint(TextRenderingHintAntiAlias);
	graphics.DrawImage(&CatchImage,0,0);
	//将缓冲区位图拷贝到前台 

	// Do not call CStatic::OnPaint() for painting messages
}

void CADI::OnDrawADI(int x, int y, Graphics &buffer)
{
	int Wm = 0,Hm = 0,PitchScaleWidth = 120,PitchScaleHeight = 200;
	double PitchRange = 60;
	double PitchTicksCount =15;	//俯仰角范围，俯仰角刻度数
	double pitchAngle = 0;	//俯仰角
 	int TicksDistance = m_Rect.Height()/(4* PitchTicksCount);	//刻度之间的距离
	
	//上半部分颜色 
	x += m_Pitch / 40 * ( TicksDistance ) * sin(-m_RollAngle * PI / 180);
	y += m_Pitch / 40 * ( TicksDistance ) * cos(m_RollAngle * PI / 180);
	//平移变换，将坐标原点平移至客户区中心
	buffer.TranslateTransform(x,y);	//x,y为新的中心
	buffer.RotateTransform(m_RollAngle);

 

 	Pen pen(Color::Black,2);
	SolidBrush brush(Color::Black);
	FontFamily fontFamily(L"Arial");
	Font font(&fontFamily,m_Rect.Height()/24,FontStyleRegular,UnitPixel);
	
	//绘制背景色,区域尽量大，否则将无法覆盖原背景上的图像
	LinearGradientBrush linBlBrush(
		Point(4*(m_centerX-m_Rect.right), 0),
		Point(4*(m_centerX-m_Rect.right), m_Rect.Height() * 3 / 2),
		Color(255, 10, 50, 100),   // opaque 
		Color(255, 10, 50, 238));  // opaque green
	
	LinearGradientBrush linGrBrush(
		Point(4*(m_centerX-m_Rect.right), 0),
		Point(4*(m_centerX-m_Rect.right), m_Rect.Height() * 3 / 2 ),
		Color(255, 101, 238, 110),   // opaque 
		Color(255, 101, 100, 110));  // opaque green
	buffer.FillRectangle(&linBlBrush,Rect( 4*(m_centerX-m_Rect.right),4*(m_centerY - m_Rect.bottom), m_Rect.Width() * 8 , m_Rect.Height()*20) );
	buffer.FillRectangle(&linGrBrush,Rect( 4*(m_centerX-m_Rect.right),0,  m_Rect.Width() * 8 , m_Rect.Height()*20) );
	
	//根据计算的第一个刻度线位置和刻度值，在循环中从下至上完成刻度带的绘制
	for (int L = 0;L<=PitchTicksCount;L++)
	{

		//长刻度线及文字
		if (L % 5 ==0)
		{

			PointF L1pointF((m_centerX-m_Rect.right)/4 ,L*TicksDistance - 5),L2pointF((m_centerX- m_Rect.right )/4, -L*TicksDistance -5);
			PointF R1pointF((m_Rect.right-m_centerX)/4 -15 ,L*TicksDistance - 5),R2pointF((m_Rect.right -m_centerX )/4-15, -L*TicksDistance -5);

			buffer.FillRectangle(&SolidBrush(Color::Black),Rect((m_centerX-m_Rect.right)/8 , L*TicksDistance, (m_Rect.right - m_centerX)/4 ,2 ));
			buffer.FillRectangle(&SolidBrush(Color::Black),Rect((m_centerX-m_Rect.right)/8 , -L*TicksDistance, (m_Rect.right - m_centerX)/4 ,2 ));
			switch (L)
			{
			case 0:	
				buffer.DrawString(L"0",-1,&font,L1pointF,&SolidBrush(Color::Black));	//宽字符。。。	Pen		lineRadio(Color::Silver,2);
				buffer.DrawString(L"0",-1,&font,R1pointF,&SolidBrush(Color::Black));
				break;
			case 5:
				buffer.DrawString(L"10",-1,&font,L1pointF,&SolidBrush(Color::Black));
				buffer.DrawString(L"-10",-1,&font,L2pointF,&SolidBrush(Color::Black));
				buffer.DrawString(L"10",-1,&font,R1pointF,&SolidBrush(Color::Black));
				buffer.DrawString(L"-10",-1,&font,R2pointF,&SolidBrush(Color::Black));
				break;
			case 10:
				buffer.DrawString(L"20",-1,&font,L1pointF,&SolidBrush(Color::Black));
				buffer.DrawString(L"-20",-1,&font,L2pointF,&SolidBrush(Color::Black));
				buffer.DrawString(L"20",-1,&font,R1pointF,&SolidBrush(Color::Black));
				buffer.DrawString(L"-20",-1,&font,R2pointF,&SolidBrush(Color::Black));
				break;
			case 15:
				buffer.DrawString(L"30",-1,&font,L1pointF,&SolidBrush(Color::Black));
				buffer.DrawString(L"-30",-1,&font,L2pointF,&SolidBrush(Color::Black));
				buffer.DrawString(L"30",-1,&font,R1pointF,&SolidBrush(Color::Black));
				buffer.DrawString(L"-30",-1,&font,R2pointF,&SolidBrush(Color::Black));
				break;
			default:
				break;
			}
		}
		//绘制短刻度线
		buffer.FillRectangle(&SolidBrush(Color::Black),Rect((m_centerX-m_Rect.right)/16 , L*TicksDistance, (m_Rect.right - m_centerX)/8 ,2 ));
		buffer.FillRectangle(&SolidBrush(Color::Black),Rect((m_centerX-m_Rect.right)/16 , -L*TicksDistance, (m_Rect.right - m_centerX)/8 ,2 ));
	}

//////////////////////////////////////////////////////////////////////////
//横滚角，刻度带固定不动，重置裁剪区和坐标面
	buffer.ResetClip(); 
	buffer.ResetTransform(); 
	buffer.TranslateTransform(m_centerX, m_centerY);
	//绘制不动的指针
	GraphicsPath path1;
	Point point11(0,(m_centerX-m_Rect.right)*45/70);
	Point point22(5,(m_centerX-m_Rect.right)*50/70);
	Point point33(-5,(m_centerX-m_Rect.right)*50/70);
	
	path1.AddLine(point11,point22);
	path1.AddLine(point22,point33);
	path1.AddLine(point33,point11);
	
	buffer.DrawPath(&pen,&path1);
	buffer.FillPath(&SolidBrush(Color::Yellow),&path1);

	//绘制中心圆点

	buffer.FillEllipse(&SolidBrush(Color::Yellow),0 - m_Rect.Height() / 60,0 - m_Rect.Height()/60,m_Rect.Height()/30,m_Rect.Height()/30);

	//绘制中心横直线
	Pen      linepen(Color::Yellow,4); 
	buffer.DrawLine(&linepen, (m_centerX-m_Rect.right)*3/7, 0, (m_centerX-m_Rect.right)/7, 0);
	buffer.DrawLine(&linepen, (m_Rect.right - m_centerX )/7, 0, (m_Rect.right -m_centerX )*3/7, 0);

	buffer.DrawLine(&linepen, (m_centerX-m_Rect.right)*3/7, 0, (m_centerX-m_Rect.right)*3/7, 10);
	buffer.DrawLine(&linepen, (m_Rect.right - m_centerX ) *3/7, 0, (m_Rect.right -m_centerX )*3/7, 10);

	//以短刻度线为例，在循环中完成刻度带的绘制 
	int RollArcRadius = (m_Rect.right - x) *5/7;	//半径
	int RollShortTickLengh ; //短刻度长度
	
	//绘制滚转刻度半圆	
	Rect rect((m_centerX-m_Rect.right)*45/70,(m_centerX-m_Rect.right)*45/70,(m_Rect.right -m_centerX )*90/70,(m_Rect.right -m_centerX )*90/70);
	buffer.DrawArc(&Pen(Color::White,2),rect,180.0f,180.0f);
	
	//当前俯仰、滚转数值
	Font        Wordfont(&fontFamily, m_Rect.Height()/20, FontStyleRegular, UnitPixel);
	PointF      PitchpointF(m_centerX-m_Rect.Width(), m_centerY - m_Rect.Height() /7);
	PointF      RollpointF(m_centerX-m_Rect.Width(), m_centerY - m_Rect.Height() /12);
	SolidBrush  solidBrush(Color::White);	
	CString strShowPitch,strShowRoll;
	strShowPitch.Format("俯仰 %0.2f",-m_Pitch/20);
	
	float showRoll = 0.0f;
	if (m_RollAngle > 180)
	{
		showRoll = m_RollAngle -360;
		
	}
	else if (m_RollAngle < -180)
	{
		showRoll = m_RollAngle + 360;
	}
	else
	{
		showRoll = m_RollAngle;
	}
	strShowRoll.Format("滚转 %0.2f",showRoll);

	wchar_t * p=strShowPitch.AllocSysString();
	buffer.DrawString(p,-1,&Wordfont,PitchpointF,&solidBrush);
	p = strShowRoll.AllocSysString();
	buffer.DrawString(p,-1,&Wordfont,RollpointF,&solidBrush);


	//绘制刻度
	for(int r = 0; r < 7; r++) 
	{ 
		
		buffer.FillRectangle(&SolidBrush(Color::White),Rect(( m_centerX - m_Rect.right ) *5/7 , -2, (m_Rect.right - m_centerX) *5/70, (m_Rect.right - m_centerX) *5/350));
		
		buffer.RotateTransform(180/6);	//旋转
	}
	
	buffer.RotateTransform(-180 * 10 /6 );

	//绘制刻度数字
	PointF RadRpointF(-10 ,( m_centerX - m_Rect.right) *5/7 - 15);	//
	PointF Rad0pointf(-5,( m_centerX - m_Rect.right) *5/7 - 15);
	for(r = 0; r < 7; r++) 
	{ 	
		switch (r)	//绘制文字
		{
		case 0:
			buffer.DrawString(L"-90",-1,&font,RadRpointF,&SolidBrush(Color::White));
			break;
		case 1:
			buffer.DrawString(L"-60",-1,&font,RadRpointF,&SolidBrush(Color::White));
			break;
		case 2:
			buffer.DrawString(L"-30",-1,&font,RadRpointF,&SolidBrush(Color::White));
			break;
		case 3:
			buffer.DrawString(L"0",-1,&font,Rad0pointf,&SolidBrush(Color::White));
			break;
		case 4:
			buffer.DrawString(L"30",-1,&font,RadRpointF,&SolidBrush(Color::White));
			break;
		case 5:
			buffer.DrawString(L"60",-1,&font,RadRpointF,&SolidBrush(Color::White));
			break;
		case 6:
			buffer.DrawString(L"90",-1,&font,RadRpointF,&SolidBrush(Color::White));
			break;
			
		default:
			break;
		}
		
		buffer.RotateTransform(180/6);	//旋转
	}


	//绘制指针,及指针角度
	buffer.RotateTransform(-180 * 4 /6  + m_RollAngle);
	GraphicsPath path;
	Point point1(0,(m_centerX-m_Rect.right)*45/70);
	Point point2(5,(m_centerX-m_Rect.right)*40/70);
	Point point3(-5,(m_centerX-m_Rect.right)*40/70);
	
	path.AddLine(point1,point2);
	path.AddLine(point2,point3);
	path.AddLine(point3,point1);
		
	buffer.DrawPath(&pen,&path);
	buffer.FillPath(&SolidBrush(Color::Yellow),&path);


	
}

void CADI::SetRollAngle(float RollAngle)
{
	m_RollAngle = RollAngle;

	Invalidate();
}

void CADI::SetPitch(float fPitch)
{
	m_Pitch = -fPitch *20;
	
	Invalidate();
}
