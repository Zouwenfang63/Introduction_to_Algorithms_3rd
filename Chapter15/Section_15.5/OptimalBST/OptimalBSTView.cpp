// OptimalBSTView.cpp: 实现文件
//

#include "stdafx.h"
#include "OptimalBST.h"
#include "OptimalBSTView.h"
#include "OptimalBSTDlg.h"


// COptimalBSTView

IMPLEMENT_DYNAMIC(COptimalBSTView, CWnd)

COptimalBSTView::COptimalBSTView()
{

}

COptimalBSTView::~COptimalBSTView()
{
}


BEGIN_MESSAGE_MAP(COptimalBSTView, CWnd)
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
END_MESSAGE_MAP()


BOOL COptimalBSTView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message == WM_LBUTTONDOWN || pMsg->message == WM_LBUTTONDBLCLK
		|| pMsg->message == WM_RBUTTONDOWN || pMsg->message == WM_RBUTTONDBLCLK)
	{
		return TRUE;
	}

	return CWnd::PreTranslateMessage(pMsg);
}


void COptimalBSTView::ResetScrollRange()
{
	CSize tree_paint_size = GetPaintSize(((COptimalBSTDlg*)GetParent())->GetOptimalBST());
	int sx = tree_paint_size.cx;
	int sy = tree_paint_size.cy;

	SCROLLINFO scroll_info;
	scroll_info.cbSize = sizeof(SCROLLINFO);

	CRect client;
	GetClientRect(client);
	scroll_info.fMask = SIF_RANGE | SIF_PAGE;
	scroll_info.nMin = 0;
	scroll_info.nMax = sx;
	scroll_info.nPage = client.Width();
	SetScrollInfo(SB_HORZ, &scroll_info);

	GetClientRect(client);
	scroll_info.fMask = SIF_RANGE | SIF_PAGE | SIF_DISABLENOSCROLL;
	scroll_info.nMin = 0;
	scroll_info.nMax = sy;
	scroll_info.nPage = client.Height();
	SetScrollInfo(SB_VERT, &scroll_info);
}


// COptimalBSTView 消息处理程序
void COptimalBSTView::OnPaint()
{
	static bool first_paint = 1;

	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CWnd::OnPaint()

	if(first_paint == 1)
	{
		first_paint = 0;
		ShowScrollBar(SB_BOTH);
		SCROLLINFO scroll_info;
		scroll_info.fMask = SIF_DISABLENOSCROLL;
		SetScrollInfo(SB_HORZ, &scroll_info);
		SetScrollInfo(SB_VERT, &scroll_info);
		//EnableScrollBarCtrl(SB_HORZ);
		//EnableScrollBarCtrl(SB_VERT);

		//ResetScrollRange();
	}

	Paint(((COptimalBSTDlg*)GetParent())->GetOptimalBST());
}


void COptimalBSTView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int x = GetScrollPos(SB_HORZ);

	switch(nSBCode)
	{
	case SB_LEFT:
		x = 0;
		break;

	case SB_RIGHT:
		x = GetScrollLimit(SB_HORZ) - 1;
		break;

	case SB_LINELEFT:
		x -= 1;
		break;

	case SB_LINERIGHT:
		x += 1;
		break;

	case SB_PAGELEFT:
		x -= 10;
		break;

	case SB_PAGERIGHT:
		x += 10;
		break;

	case SB_THUMBTRACK:
		x = nPos;
		break;

	default:
		break;
	}

	int x_max = GetScrollLimit(SB_HORZ);
	if(x > x_max) x = x_max - 1;
	if(x < 0) x = 0;

	SetScrollPos(SB_HORZ, x);
	Invalidate();

	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}


void COptimalBSTView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int y = GetScrollPos(SB_VERT);

	switch(nSBCode)
	{
	case SB_TOP:
		y = 0;
		break;

	case SB_BOTTOM:
		y = GetScrollLimit(SB_VERT) - 1;
		break;

	case SB_LINEUP:
		y-= 1;
		break;

	case SB_LINEDOWN:
		y+= 1;
		break;

	case SB_PAGEUP:
		y-= 10;
		break;

	case SB_PAGEDOWN:
		y += 10;
		break;

	case SB_THUMBTRACK:
		y = nPos;
		break;

	default:
		break;
	}

	int y_max = GetScrollLimit(SB_VERT);
	if(y > y_max) y = y_max - 1;
	if(y < 0) y = 0;

	SetScrollPos(SB_VERT, y);
	Invalidate();

	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}


void COptimalBSTView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	ResetScrollRange();
}
