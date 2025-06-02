#pragma once
#include "afxdialogex.h"


// CLnputDialogSphere 对话框

class CLnputDialogSphere : public CDialogEx
{
	DECLARE_DYNAMIC(CLnputDialogSphere)

public:
	CLnputDialogSphere(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CLnputDialogSphere();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SPH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	double mRadius;
	int mLongitude;
	int mLatitude;
	virtual BOOL OnInitDialog();
};
