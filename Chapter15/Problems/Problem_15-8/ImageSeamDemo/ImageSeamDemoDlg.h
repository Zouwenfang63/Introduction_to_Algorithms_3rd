
// ImageSeamDemoDlg.h: 头文件
//

#pragma once

#include "CImageSeamView.h"
#include "ImageSeam.h"


// CImageSeamDemoDlg 对话框
class CImageSeamDemoDlg : public CDialogEx
{
// 构造
public:
	CImageSeamDemoDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGESEAMDEMO_DIALOG };
#endif

	const ImageSeam& GetImageSeam() const { return m_ImageSeam; }

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int m_ImageWidth;
	int m_ImageHeight;
	ImageSeam m_ImageSeam;
	CImageSeamView m_ImageSeamFigure;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	int m_TotalDisruption;
	afx_msg void OnSetImageSize();
	afx_msg void OnRandomDisruption();
	afx_msg void OnGetSeam();
};
