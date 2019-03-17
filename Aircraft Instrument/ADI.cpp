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

	Graphics graphics(pDc->m_hDC);		//GDI����
	CRect rect;
	GetClientRect(&m_Rect);
	Point center(m_Rect.CenterPoint().x,m_Rect.CenterPoint().y);
	
	m_centerX = center.X;
	m_centerY = center.Y;

	//���ڿͻ�����������
	Bitmap CatchImage(m_Rect.Width(),m_Rect.Height());
	//�����ڴ滭��
	Graphics buffer(&CatchImage);
	//�������ڴ滭��һ�µĻ�����
	OnDrawADI(center.X,center.Y,buffer);
	//����ADI���ƺ����������ͻ������������ͼ�ζ�����Ϊ���� 
	buffer.SetSmoothingMode(SmoothingModeAntiAlias);	
	//����ͼ�κ��ı�������ģʽ 
	buffer.SetTextRenderingHint(TextRenderingHintAntiAlias);
	graphics.DrawImage(&CatchImage,0,0);
	//��������λͼ������ǰ̨ 

	// Do not call CStatic::OnPaint() for painting messages
}

void CADI::OnDrawADI(int x, int y, Graphics &buffer)
{
	int Wm = 0,Hm = 0,PitchScaleWidth = 120,PitchScaleHeight = 200;
	double PitchRange = 60;
	double PitchTicksCount =15;	//�����Ƿ�Χ�������ǿ̶���
	double pitchAngle = 0;	//������
 	int TicksDistance = m_Rect.Height()/(4* PitchTicksCount);	//�̶�֮��ľ���
	
	//�ϰ벿����ɫ 
	x += m_Pitch / 40 * ( TicksDistance ) * sin(-m_RollAngle * PI / 180);
	y += m_Pitch / 40 * ( TicksDistance ) * cos(m_RollAngle * PI / 180);
	//ƽ�Ʊ任��������ԭ��ƽ�����ͻ�������
	buffer.TranslateTransform(x,y);	//x,yΪ�µ�����
	buffer.RotateTransform(m_RollAngle);

 

 	Pen pen(Color::Black,2);
	SolidBrush brush(Color::Black);
	FontFamily fontFamily(L"Arial");
	Font font(&fontFamily,m_Rect.Height()/24,FontStyleRegular,UnitPixel);
	
	//���Ʊ���ɫ,�������󣬷����޷�����ԭ�����ϵ�ͼ��
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
	
	//���ݼ���ĵ�һ���̶���λ�úͿ̶�ֵ����ѭ���д���������ɿ̶ȴ��Ļ���
	for (int L = 0;L<=PitchTicksCount;L++)
	{

		//���̶��߼�����
		if (L % 5 ==0)
		{

			PointF L1pointF((m_centerX-m_Rect.right)/4 ,L*TicksDistance - 5),L2pointF((m_centerX- m_Rect.right )/4, -L*TicksDistance -5);
			PointF R1pointF((m_Rect.right-m_centerX)/4 -15 ,L*TicksDistance - 5),R2pointF((m_Rect.right -m_centerX )/4-15, -L*TicksDistance -5);

			buffer.FillRectangle(&SolidBrush(Color::Black),Rect((m_centerX-m_Rect.right)/8 , L*TicksDistance, (m_Rect.right - m_centerX)/4 ,2 ));
			buffer.FillRectangle(&SolidBrush(Color::Black),Rect((m_centerX-m_Rect.right)/8 , -L*TicksDistance, (m_Rect.right - m_centerX)/4 ,2 ));
			switch (L)
			{
			case 0:	
				buffer.DrawString(L"0",-1,&font,L1pointF,&SolidBrush(Color::Black));	//���ַ�������	Pen		lineRadio(Color::Silver,2);
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
		//���ƶ̶̿���
		buffer.FillRectangle(&SolidBrush(Color::Black),Rect((m_centerX-m_Rect.right)/16 , L*TicksDistance, (m_Rect.right - m_centerX)/8 ,2 ));
		buffer.FillRectangle(&SolidBrush(Color::Black),Rect((m_centerX-m_Rect.right)/16 , -L*TicksDistance, (m_Rect.right - m_centerX)/8 ,2 ));
	}

//////////////////////////////////////////////////////////////////////////
//����ǣ��̶ȴ��̶����������òü�����������
	buffer.ResetClip(); 
	buffer.ResetTransform(); 
	buffer.TranslateTransform(m_centerX, m_centerY);
	//���Ʋ�����ָ��
	GraphicsPath path1;
	Point point11(0,(m_centerX-m_Rect.right)*45/70);
	Point point22(5,(m_centerX-m_Rect.right)*50/70);
	Point point33(-5,(m_centerX-m_Rect.right)*50/70);
	
	path1.AddLine(point11,point22);
	path1.AddLine(point22,point33);
	path1.AddLine(point33,point11);
	
	buffer.DrawPath(&pen,&path1);
	buffer.FillPath(&SolidBrush(Color::Yellow),&path1);

	//��������Բ��

	buffer.FillEllipse(&SolidBrush(Color::Yellow),0 - m_Rect.Height() / 60,0 - m_Rect.Height()/60,m_Rect.Height()/30,m_Rect.Height()/30);

	//�������ĺ�ֱ��
	Pen      linepen(Color::Yellow,4); 
	buffer.DrawLine(&linepen, (m_centerX-m_Rect.right)*3/7, 0, (m_centerX-m_Rect.right)/7, 0);
	buffer.DrawLine(&linepen, (m_Rect.right - m_centerX )/7, 0, (m_Rect.right -m_centerX )*3/7, 0);

	buffer.DrawLine(&linepen, (m_centerX-m_Rect.right)*3/7, 0, (m_centerX-m_Rect.right)*3/7, 10);
	buffer.DrawLine(&linepen, (m_Rect.right - m_centerX ) *3/7, 0, (m_Rect.right -m_centerX )*3/7, 10);

	//�Զ̶̿���Ϊ������ѭ������ɿ̶ȴ��Ļ��� 
	int RollArcRadius = (m_Rect.right - x) *5/7;	//�뾶
	int RollShortTickLengh ; //�̶̿ȳ���
	
	//���ƹ�ת�̶Ȱ�Բ	
	Rect rect((m_centerX-m_Rect.right)*45/70,(m_centerX-m_Rect.right)*45/70,(m_Rect.right -m_centerX )*90/70,(m_Rect.right -m_centerX )*90/70);
	buffer.DrawArc(&Pen(Color::White,2),rect,180.0f,180.0f);
	
	//��ǰ��������ת��ֵ
	Font        Wordfont(&fontFamily, m_Rect.Height()/20, FontStyleRegular, UnitPixel);
	PointF      PitchpointF(m_centerX-m_Rect.Width(), m_centerY - m_Rect.Height() /7);
	PointF      RollpointF(m_centerX-m_Rect.Width(), m_centerY - m_Rect.Height() /12);
	SolidBrush  solidBrush(Color::White);	
	CString strShowPitch,strShowRoll;
	strShowPitch.Format("���� %0.2f",-m_Pitch/20);
	
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
	strShowRoll.Format("��ת %0.2f",showRoll);

	wchar_t * p=strShowPitch.AllocSysString();
	buffer.DrawString(p,-1,&Wordfont,PitchpointF,&solidBrush);
	p = strShowRoll.AllocSysString();
	buffer.DrawString(p,-1,&Wordfont,RollpointF,&solidBrush);


	//���ƿ̶�
	for(int r = 0; r < 7; r++) 
	{ 
		
		buffer.FillRectangle(&SolidBrush(Color::White),Rect(( m_centerX - m_Rect.right ) *5/7 , -2, (m_Rect.right - m_centerX) *5/70, (m_Rect.right - m_centerX) *5/350));
		
		buffer.RotateTransform(180/6);	//��ת
	}
	
	buffer.RotateTransform(-180 * 10 /6 );

	//���ƿ̶�����
	PointF RadRpointF(-10 ,( m_centerX - m_Rect.right) *5/7 - 15);	//
	PointF Rad0pointf(-5,( m_centerX - m_Rect.right) *5/7 - 15);
	for(r = 0; r < 7; r++) 
	{ 	
		switch (r)	//��������
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
		
		buffer.RotateTransform(180/6);	//��ת
	}


	//����ָ��,��ָ��Ƕ�
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
