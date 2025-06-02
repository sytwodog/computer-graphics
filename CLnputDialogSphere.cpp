// CLnputDialogSphere.cpp: 实现文件
//

#include "pch.h"
#include "CG2022116169李思怡.h"
#include "afxdialogex.h"
#include "CLnputDialogSphere.h"


// CLnputDialogSphere 对话框

IMPLEMENT_DYNAMIC(CLnputDialogSphere, CDialogEx)

CLnputDialogSphere::CLnputDialogSphere(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SPH, pParent)
	, mRadius(0)
	, mLongitude(0)
	, mLatitude(0)
{

}

CLnputDialogSphere::~CLnputDialogSphere()
{
}

void CLnputDialogSphere::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RADIUS, mRadius);
	DDX_Text(pDX, IDC_LONGITUDE, mLongitude);
	DDX_Text(pDX, IDC_LATITUDE, mLatitude);
}


BEGIN_MESSAGE_MAP(CLnputDialogSphere, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLnputDialogSphere::OnBnClickedOk)
END_MESSAGE_MAP()


// CLnputDialogSphere 消息处理程序


void CLnputDialogSphere::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);//取回数据到成员变量
	CDialogEx::OnOK();
}


BOOL CLnputDialogSphere::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
