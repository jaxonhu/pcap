
// MFCpacpDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"


// CMFCpacpDlg 对话框
class CMFCpacpDlg : public CDialogEx
{
// 构造
public:
	CMFCpacpDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCPACP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpenButton();
	afx_msg void OnBnClickedSaveButton();
	afx_msg void OnBnClickedOk();
	// pcap地址
	CString m_pfile;
//	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedWuButton();
	// 保存路径
	CString m_path;

	afx_msg void OnEnChangeOpenEdit();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();

	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton5();
	// jindu
	CString m_jindu;
};
