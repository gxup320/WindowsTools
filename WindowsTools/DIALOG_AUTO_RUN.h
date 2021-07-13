#pragma once


// DIALOG_AUTO_RUN 对话框

class DIALOG_AUTO_RUN : public CDialogEx
{
	DECLARE_DYNAMIC(DIALOG_AUTO_RUN)

public:
	DIALOG_AUTO_RUN(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DIALOG_AUTO_RUN();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_AUTO_RUN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
