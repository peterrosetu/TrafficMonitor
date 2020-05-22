#pragma once
#include "Common.h"
#include "afxwin.h"
//#include "StaticEx.h"
#include "DrawCommon.h"
#include "IniHelper.h"
#include "CommonData.h"

// CTaskBarDlg �Ի���
#define TASKBAR_WND_HEIGHT theApp.DPI(32)				//���������ڵĸ߶�
#define WM_TASKBAR_MENU_POPED_UP (WM_USER + 1004)		//���������������Ҽ��˵�����ʱ��������Ϣ
#define TASKBAR_GRAPH_MAX_LEN 500						//��ʷ���ݴ洢��󳤶�
#define TASKBAR_GRAPH_STEP 5							//�����ӻ�һ����

class CTaskBarDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTaskBarDlg)

public:
	CTaskBarDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTaskBarDlg();

	CToolTipCtrl m_tool_tips;
	CMenu m_menu;	//�Ҽ��˵�

	void ShowInfo(CDC* pDC); 	//����Ϣ���Ƶ��ؼ���
	void TryDrawStatusBar(CDrawCommon& drawer, const CRect& rect_bar, int usage_percent); //����CPU/�ڴ�״̬��

	void TryDrawGraph(CDrawCommon& drawer, const CRect &value_rect, CList<int,int> &list);		// ����CPU/�ڴ涯̬ͼ

	bool AdjustWindowPos();	//���ô������������е�λ��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TASK_BAR_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	HWND m_hTaskbar;	//���������ھ��
	HWND m_hBar;		//���������ڶ��������ľ��
	HWND m_hMin;		//��С�����ڵľ��
	CRect m_rcBar;		//��ʼ״̬ʱ���������ڵľ�������
	CRect m_rcMin;		//��ʼ״̬ʱ��С�����ڵľ�������
	CRect m_rect;		//��ǰ���ڵľ�������
	int m_window_width;		//���ڿ��
	int m_window_width_s;	//����ʾCPU���ڴ�������ʱ�Ĵ��ڿ��
	int m_window_height;
	int m_up_lable_width;	//�ϴ���ǩ�Ŀ��
	int m_down_lable_width;	//���ر�ǩ�Ŀ��
	int m_cpu_lable_width;		//CPU��ǩ�Ŀ��
	int m_memory_lable_width;	//�ڴ��ǩ�Ŀ��
	int m_ud_value_width;		//�ϴ���������ֵ�Ŀ��
	int m_cm_value_width;		//CPU���ڴ���ֵ�Ŀ��

	int m_min_bar_width;	//��С��������С��Ⱥ�Ŀ��
	int m_min_bar_height;	//��С��������С�߶Ⱥ�ĸ߶ȣ���������������Ļ�����Ҳ�ʱ��

	CList<int, int> m_cpu_his;		//����cpuʹ������ʷ���ݵ����������水��ʱ��˳��Խ����ͷ������Խ��
	CList<int, int> m_memory_his;	//�����ڴ�ռ������ʷ���ݵ����������水��ʱ��˳��Խ����ͷ������Խ��

	int m_left_space{};			//��С�����ںͶ������ڴ������ı߾�
	int m_top_space{};			//��С�����ںͶ������ڴ��ڶ����ı߾ࣨ��������������Ļ�����Ҳ�ʱ��

	bool m_connot_insert_to_task_bar{ false };	//��������޷�Ƕ������������Ϊtrue
	bool m_taskbar_on_top_or_bottom{ true };		//�������������Ļ������ײ�����Ϊture
	int m_error_code{};

	CFont m_font;			//����

	CDC* m_pDC{};		//���ڵ�DC���������㴰�ڵĿ��

	bool IsTaskbarOnTopOrBottom();		//�ж��������Ƿ�����Ļ�Ķ�����ײ���������򷵻�false���������������Ļ���࣬�򷵻�false
	CString GetMouseTipsInfo();		//��ȡ�����ʾ

	void AddHisToList(CList<int,int> &list, int current_usage_percent);		//����ǰ��������ֵ��ӽ�����

public:
	void SetTextFont();
	void ApplySettings();
	void CalculateWindowWidth();		//���㴰����Ҫ�Ŀ��

	void SetToolTipsTopMost();			//���������ʾ�ö�
	void UpdateToolTips();

	bool GetCannotInsertToTaskBar() const { return m_connot_insert_to_task_bar; }
	int GetErrorCode() const { return m_error_code; }

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnSetBackgroundColor();
	//afx_msg void OnSetTextColor();
	afx_msg void OnInitMenu(CMenu* pMenu);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//afx_msg void OnSetFont();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnPaint();
};
