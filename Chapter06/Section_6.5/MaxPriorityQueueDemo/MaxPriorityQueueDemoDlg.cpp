
// MaxPriorityQueueDemoDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MaxPriorityQueueDemo.h"
#include "MaxPriorityQueueDemoDlg.h"
#include "afxdialogex.h"

#include <sstream>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMaxPriorityQueueDemoDlg 对话框



CMaxPriorityQueueDemoDlg::CMaxPriorityQueueDemoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAXPRIORITYQUEUEDEMO_DIALOG, pParent)
	, m_InsertElements(_T(""))
	, m_IncreaseElemIndex(0)
	, m_IncreaseToElem(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMaxPriorityQueueDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_INSERT_ELEM_EDIT, m_InsertElements);
	DDX_Text(pDX, IDC_INCREASE_ELEM_INDEX_EDIT, m_IncreaseElemIndex);
	DDV_MinMaxInt(pDX, m_IncreaseElemIndex, 0, INT_MAX);
	DDX_Text(pDX, IDC_INCREASE_TO_ELEM_EDIT, m_IncreaseToElem);
}

BEGIN_MESSAGE_MAP(CMaxPriorityQueueDemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_INSERT, &CMaxPriorityQueueDemoDlg::OnInsert)
	ON_BN_CLICKED(IDC_EXTRACT_MAX, &CMaxPriorityQueueDemoDlg::OnExtractMax)
	ON_BN_CLICKED(IDC_INCREASE_KEY, &CMaxPriorityQueueDemoDlg::OnIncreaseKey)
	ON_BN_CLICKED(IDC_CLEAR, &CMaxPriorityQueueDemoDlg::OnClear)
END_MESSAGE_MAP()


// CMaxPriorityQueueDemoDlg 消息处理程序

BOOL CMaxPriorityQueueDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_MaxPriorityQueueFigure.SubclassDlgItem(IDC_MAX_PRIORITY_QUEUE_FIGURE, this);

	int initQueueData[] = { 16, 14, 10, 8, 7, 9, 3, 2, 4, 1 };
	//int initQueueData[] = { 15, 13, 9, 5, 12, 8, 7, 4, 0, 6, 2, 1 };
	for(int i = 0; i < sizeof(initQueueData)/sizeof(int); ++i)
		m_MaxPriorityQueue.insert(initQueueData[i]);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMaxPriorityQueueDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMaxPriorityQueueDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CMaxPriorityQueueDemoDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
			return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CMaxPriorityQueueDemoDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rect;

	if (m_MaxPriorityQueueFigure.m_hWnd)
	{
		m_MaxPriorityQueueFigure.GetWindowRect(rect);
		ScreenToClient(rect);
		rect.bottom = cy-12;
		rect.right = cx-13;
		m_MaxPriorityQueueFigure.MoveWindow(rect);
	}
}

void CMaxPriorityQueueDemoDlg::OnInsert()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();

	istringstream is(m_InsertElements.GetBuffer());
	m_InsertElements.ReleaseBuffer();
	
	int elem;
	while (is >> elem)
		m_MaxPriorityQueue.insert(elem);

	m_MaxPriorityQueueFigure.ResetScrollRange();
	Invalidate();
}

void CMaxPriorityQueueDemoDlg::OnExtractMax()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{
		m_MaxPriorityQueue.extract_max();
	}
	catch (runtime_error)
	{
		MessageBox("Empty Queue Error!");
	}

	m_MaxPriorityQueueFigure.ResetScrollRange();
	Invalidate();
}

void CMaxPriorityQueueDemoDlg::OnIncreaseKey()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_MaxPriorityQueue.increase_key(m_IncreaseElemIndex, m_IncreaseToElem);
	m_MaxPriorityQueueFigure.ResetScrollRange();
	Invalidate();
}

void CMaxPriorityQueueDemoDlg::OnClear()
{
	// TODO: 在此添加控件通知处理程序代码
	m_MaxPriorityQueue.clear();
	m_MaxPriorityQueueFigure.ResetScrollRange();
	Invalidate();
}
