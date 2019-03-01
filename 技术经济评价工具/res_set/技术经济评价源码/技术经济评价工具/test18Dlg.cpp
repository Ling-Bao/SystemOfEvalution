// test18Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "test18.h"
#include "test18Dlg.h"

#include "evaluation.h"
#include "weight.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTest18Dlg dialog

CTest18Dlg::CTest18Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTest18Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTest18Dlg)
	m_Radio1 = -1;
	m_Radio2 = -1;
	m_Result = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTest18Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTest18Dlg)
	DDX_Control(pDX, IDC_COMBO2, m_NewCom2);
	DDX_Control(pDX, IDC_COMBO1, m_NewCom1);
	DDX_Radio(pDX, IDC_RADIO1, m_Radio1);
	DDX_Radio(pDX, IDC_RADIO2, m_Radio2);
	DDX_Text(pDX, IDC_EDIT1, m_Result);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTest18Dlg, CDialog)
	//{{AFX_MSG_MAP(CTest18Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_DATA1, OnData1)
	ON_BN_CLICKED(IDC_DATA2, OnData2)
	ON_BN_CLICKED(IDC_OK1, OnOk1)
	ON_BN_CLICKED(IDC_OK2, OnOk2)
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_BN_CLICKED(IDC_BUTTON1, OnClear)
	ON_BN_CLICKED(IDC_CLEARFILE, OnClearfile)
	ON_COMMAND(ID_ZBSFK, OnZbsfk)
	ON_COMMAND(ID_PJSFK, OnPjsfk)
	ON_COMMAND(ID_QTZSK, OnQtzsk)
	ON_COMMAND(ID_YSSJ, OnYssj)
	ON_COMMAND(ID_PJZBSJ, OnPjzbsj)
	ON_COMMAND(ID_MCXZY, OnMcxzy)
	ON_COMMAND(ID_XMCGBG, OnXmcgbg)
	ON_COMMAND(ID_TAPCG, OnTapcg)
	ON_COMMAND(ID_JSPJYM, OnJspjym)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTest18Dlg message handlers

BOOL CTest18Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	
	GetDlgItem(IDC_COMBO1)->EnableWindow(false);//未选择单选按钮时应该不可选的
	GetDlgItem(IDC_COMBO2)->EnableWindow(false);
	GetDlgItem(IDC_DATA1)->EnableWindow(false);
	GetDlgItem(IDC_DATA2)->EnableWindow(false);
	GetDlgItem(IDC_OK1)->EnableWindow(false);
	GetDlgItem(IDC_OK2)->EnableWindow(false);

	//加载菜单资源进入对话框
	m_Menu.LoadMenu(IDR_MENU);  //IDR_MENU为加入的菜单的ID，在Resource视图的Menu文件夹下可以找到
	SetMenu(&m_Menu);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTest18Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTest18Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CFont m_Font;
		m_Font.CreateFont(28,28,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_ROMAN,"黑体");
		CDC* pDC=GetDC();
		pDC->SetTextColor(RGB(255,0,255));
		CFont* pOleFont=pDC->SelectObject(&m_Font);
		pDC->TextOut(160,30,"技术经济评价工具");
		pDC->SelectObject(pOleFont);

		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTest18Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//添加的程序从这儿开始
CEvaluation CEv;
CWeight CWe;
char *filename;
char *weight_filename;

void CTest18Dlg::OnRadio1() 
{
	GetDlgItem(IDC_COMBO1)->EnableWindow(true);
	GetDlgItem(IDC_DATA1)->EnableWindow(true);
	GetDlgItem(IDC_OK1)->EnableWindow(true);

	UpdateData(true);
	m_Radio2=-1;
	GetDlgItem(IDC_COMBO2)->EnableWindow(false);
	GetDlgItem(IDC_DATA2)->EnableWindow(false);
	GetDlgItem(IDC_OK2)->EnableWindow(false);
	UpdateData(false);	
}

void CTest18Dlg::OnRadio2() 
{
	GetDlgItem(IDC_COMBO2)->EnableWindow(true);
	GetDlgItem(IDC_DATA2)->EnableWindow(true);
	GetDlgItem(IDC_OK2)->EnableWindow(true);

	UpdateData(true);
	m_Radio1=-1;
	GetDlgItem(IDC_COMBO1)->EnableWindow(false);
	GetDlgItem(IDC_DATA1)->EnableWindow(false);
	GetDlgItem(IDC_OK1)->EnableWindow(false);
	UpdateData(false);	
}

void CTest18Dlg::OnData1() 
{
	MessageBox("请选择原始数据!");

	CString FilePathNameO="";
    char filefilter[]="txt文件(*.txt)|*.txt|";//文件为txt格式
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,filefilter);

    if(dlg.DoModal()==IDOK)
    FilePathNameO=dlg.GetPathName();

	filename=(LPSTR)(LPCTSTR)FilePathNameO;	

	if(FilePathNameO=="")
	{
		AfxMessageBox("选择原始数据文件失败！");
		return;
	}
	
	CString str;
    m_NewCom1.GetWindowText(str);

	if(str=="熵值法")
		CWe.entropy_weight(filename);
	else if(str=="灰色关联度法")
		CWe.grey_correlation_degree(filename);
	else if(str=="变异系数法")
		CWe.variance_coefficient(filename);
	else if(str=="多目标优化法")
		CWe.multi_objective_optimization(filename);
	else if(str=="复相关系数法")
		CWe.multiple_correlation_coefficient(filename);
	else if(str=="乘法加权组合法")
		CWe.multiple_weight(filename);
	else if(str=="线性加权组合法")
		CWe.linear_weight(filename);
	else if(str=="改进熵权法")
		CWe.improved_entropy_weight(filename);
	else if(str=="专家打分法")
		CWe.expert(filename);
	else if(str=="对比排序法")
		CWe.contrast_compositor(filename);
	else if(str=="优序图法")
		CWe.PC(filename);
	else if(str=="CRITIC法")
		CWe.critic(filename);
	else if(str=="层次分析法")
		CWe.AHP(filename);
	else
		AfxMessageBox("请先选择权重方法，然后重试！");	
}

void CTest18Dlg::OnData2() 
{
	CString str;
    m_NewCom2.GetWindowText(str);

	MessageBox("请选择原始数据!");
	CString FilePathNameO="";
    //CFileDialog dlg(TRUE);///TRUE为OPEN对话框，FALSE为SAVE AS对话框
	char filefilter[]="txt文件(*.txt)|*.txt|";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,filefilter);

    if(dlg.DoModal()==IDOK)
    FilePathNameO=dlg.GetPathName();
	filename=(LPSTR)(LPCTSTR)FilePathNameO;	
	if(FilePathNameO=="")
	{
		AfxMessageBox("选择原始数据文件失败！");
		return;
	}

	MessageBox("接下来请选择权重数据!");
	CString FilePathNameW="";
    if(dlg.DoModal()==IDOK)
    FilePathNameW=dlg.GetPathName();
	weight_filename=(LPSTR)(LPCTSTR)FilePathNameW;	
	if(FilePathNameW=="")
	{
		AfxMessageBox("选择权重数据文件失败！");
		return;
	}

	
	if(str=="综合指数法")
		CEv.comprehensive_index(filename,weight_filename);
	else if(str=="灰色关联综合评价法")
		CEv.grey_relational_comprehensive_evaluation(filename,weight_filename);
	else if(str=="灰色逼近理想解法")
		CEv.topsis(filename,weight_filename);
	else if(str=="密切值法")
		CEv.osculating_value(filename,weight_filename);
	else
		AfxMessageBox("请先选择综合评价方法，然后重试！");	
}

void CTest18Dlg::OnOk1() 
{
	if(!(IDOK == AfxMessageBox(_T("进行数据运算前是否点击<清除数据和图像>按钮！"), MB_OKCANCEL | MB_ICONQUESTION)))
	{
		AfxMessageBox("请先点击<清除数据和图像>按钮后,再点击<确定>按钮！");
		return;
	}

	CFileFind counter;
	BOOL bWorking = counter.FindFile("weight.txt");
	if(!bWorking)
	{
		AfxMessageBox("weight.txt文件被破坏或未选择方法或未选择原始数据1！");
		return;
	}

	char *pszFileName="weight.txt";
    CStdioFile myFile;
    CFileException fileException;
	int tag=0;
    if(myFile.Open(pszFileName,CFile::typeText|CFile::modeReadWrite),&fileException)
	{
		myFile.SeekToBegin();
		CString str1;
		myFile.ReadString(str1);
		CString str2;
		myFile.ReadString(str2);
		m_Result=str1+str2;
		UpdateData(false);
		tag=1;

	}

	myFile.Close();

	if(tag)
	{
	//*********画图**********
	FILE *fp;
	float **count;
	int i,j;
	int row=0,column=0;
	char ch;
     
	//......读入原始数据W......
	if((fp=fopen("weight.txt","r"))==NULL);//打开文件
    while(!feof(fp)&&(ch=fgetc(fp))!='\n')//统计列数
		if(ch=='\t')
			column++;
	column++;
	fseek(fp,0L,0);//置文件首部
	while(!feof(fp))//统计行数
		if(fgetc(fp)=='\n')
			row++;
		row++;

    count=(float**)malloc(sizeof(float*)*row);//为原始数据矩阵开辟内存
	for(i=0;i<row;i++)
		count[i]=(float*)malloc(sizeof(float)*column);

	fseek(fp,0L,0);//置文件首部
	while(!feof(fp))//读入数据
	for(i=0;i<row;i++)
		for(j=0;j<column;j++)
			fscanf(fp,"%f,",&count[i][j]);

	int biaoji=0;
	for(i=0;i<column;i++)
		if(count[0][i]<0)
			biaoji++;
	if(biaoji!=0)
	{
		AfxMessageBox("请考虑选用算法是否符合实际，指标值出现负数！");
		return;
	}

	int num=column;

	CClientDC dc(this);  
    //得到控件的大小
	CRect rect;  
    GetDlgItem(IDC_HUATU)->GetWindowRect(&rect);//获取控件相对于屏幕的位置  
    ScreenToClient(rect);//转化为对话框上的相对位置  
    CPen* pPenBlue = new CPen;                                  //创建画笔对象  
    pPenBlue->CreatePen(PS_SOLID, 2, RGB(0,0,225));     //蓝色画笔  
    CPen* pPenBlack = new CPen;                                 //创建画笔对象  
    pPenBlack->CreatePen(PS_SOLID, 1, RGB(0,0,0)); //黑色画笔  
    //选中黑色画笔，并保存当前画笔  
    CGdiObject* pOldPen = dc.SelectObject(pPenBlack);  
    //int i = 0;  ******************
    CString str;  
	int OriX=rect.left+50,OriY=rect.bottom-40;//坐标系原点OriX，OriY  
    CPoint OPos(OriX,OriY),NowPos;  //OPos是原点坐标 
	str.Format("%d",0);  
    dc.TextOut(OPos.x-15,OPos.y+5,str); 

	dc.MoveTo(OPos);  
    NowPos.x = rect.right;  
    NowPos.y = OPos.y;  
    dc.LineTo(NowPos);  
    //绘制箭头  
    dc.LineTo(NowPos.x - 5,NowPos.y - 5);  
    dc.MoveTo(NowPos);  
    dc.LineTo(NowPos.x - 5,NowPos.y + 5);  
      
    //寻找数据数组最大的数据  
    float MAXx = NowPos.x-OPos.x;  
    //x轴坐标系数的数据步长  
    int Tstepx =(int) (MAXx / (num+0.8));   //方案个数num  
    //x轴坐标系数的刻度步长
	int Xstep=Tstepx;
    for (i = 1;i <= num;i++)//显示num个刻度  
    {  
        dc.MoveTo(OPos.x + Xstep * i,OPos.y);  
        dc.LineTo(CPoint(OPos.x+Xstep * i,OPos.y-5));  
        
		str.Format("%d",i);  
        dc.TextOut(OPos.x + Xstep * i - 10,rect.bottom-36,str);  
    }  

	//横坐标名称
	str.Format("%s","方案/指标");  
    dc.TextOut(OPos.x + Xstep * (num/2),rect.bottom-20,str);
	//str.Format("%s","案");  
    //dc.TextOut(OPos.x + Xstep * (num/2+1),rect.bottom-20,str);

    //绘制y轴坐标系数  
    dc.MoveTo(OPos);  
    NowPos.x = OPos.x;  
    NowPos.y = rect.top;  
    dc.LineTo(NowPos);  
    //绘制箭头  
    dc.LineTo(NowPos.x - 5,NowPos.y + 5);  
    dc.MoveTo(NowPos);  
    dc.LineTo(NowPos.x + 5,NowPos.y + 5);  
      
    //寻找数据数组最大的数据  
    float MAXy = 0;  
    for (i = 0;i < num;i++)  
    {  
        if (MAXy < count[0][i])  
        {  
            MAXy = count[0][i];  
        }  
    }  
    //y轴坐标系数的数据步长  
    float Tstepy = MAXy / 10.;   //10个数据  
    //y轴坐标系数的刻度步长  
    int Ystep = (OriY-rect.top) / 22;//除以21的原因是，有20是因为上面的数据步长是10，现在20就是2格显示一个步长，还有一个1是多出来的好看  
    //显示y坐标的刻度和数据  
    for (i = 1;i < 23;i++)//显示21个刻度  
    {  
        dc.MoveTo(OPos.x,OPos.y - Ystep * i );  
        dc.LineTo(CPoint(OPos.x + 5,OPos.y - Ystep * i));  
        if (i % 2 == 0)  
        {  
            str.Format("%3.2f",Tstepy * i / 2);  
            dc.TextOut(rect.left+20,OPos.y - Ystep * i-8,str);  
        }  
    }  

	//纵坐标名称
	str.Format("%s","方");  
    dc.TextOut(rect.left+5,OPos.y - Ystep*15-24,str);
	str.Format("%s","案");  
    dc.TextOut(rect.left+5,OPos.y - Ystep*14-17,str);
	str.Format("%s","\/");  
    dc.TextOut(rect.left+10,OPos.y - Ystep*13-12,str);
	str.Format("%s","指");  
    dc.TextOut(rect.left+5,OPos.y - Ystep*12-7,str);
	str.Format("%s","标");  
    dc.TextOut(rect.left+5,OPos.y - Ystep*11,str);
	str.Format("%s","值");  
    dc.TextOut(rect.left+5,OPos.y - Ystep*10+7,str);
      
	//绘制灰度图像的直方图  
    int RealStep = OPos.y-rect.top-(OriY-rect.top-Ystep*21);  
    dc.SelectObject(pPenBlue); //选择蓝色画笔  
    for (i = 1;i <= num;i++)  
    {   
        NowPos.x = OPos.x + Tstepx*i;  
		
        NowPos.y = OPos.y;  
        dc.MoveTo(NowPos);  
        NowPos.y = OPos.y - (float)(((float)(RealStep*20))/(21*MAXy))*count[0][i-1];  
        //说明：上面这个大家可能不懂为什么，先注意一下上面的y轴坐标系数的数据步长，y轴坐标系数的刻度步长  
        //比例这样计算的：(RealStep/21):(max/10)=X:1,然后要求X，X表示1个数据用多少格表示</span>  
        dc.LineTo(NowPos);
		
		NowPos.x = OPos.x + Tstepx*i-MAXx/(3*num);
		NowPos.y = OPos.y;  
        dc.MoveTo(NowPos);  
        NowPos.y = OPos.y - (float)(((float)(RealStep*20))/(21*MAXy))*count[0][i-1];  
        dc.LineTo(NowPos);

		NowPos.y = OPos.y - (float)(((float)(RealStep*20))/(21*MAXy))*count[0][i-1];  
		NowPos.x = OPos.x + Tstepx*i;  
        dc.MoveTo(NowPos);
		NowPos.y = OPos.y - (float)(((float)(RealStep*20))/(21*MAXy))*count[0][i-1];  
		NowPos.x = OPos.x + Tstepx*i-MAXx/(3*num);
        dc.LineTo(NowPos);
	}  
        //恢复以前的画笔  
        dc.SelectObject(pOldPen);  
        delete pPenBlue;  
        delete pPenBlack;
		fclose(fp);
    	free(count[0]);
    	free(count);
    }

	//DeleteFile(pszFileName);
}

void CTest18Dlg::OnOk2() 
{
	if(!(IDOK == AfxMessageBox(_T("进行数据运算前是否点击<清除数据和图像>按钮！"), MB_OKCANCEL | MB_ICONQUESTION)))
	{
		AfxMessageBox("请先点击<清除数据和图像>按钮后,再点击<确定>按钮！");
		return;
	}

	CFileFind counter;
	BOOL bWorking = counter.FindFile("evaluation.txt");
	if(!bWorking)
	{
		AfxMessageBox("evaluation.txt文件被破坏或未选择方法或未选择原始数据2！");
		return;
	}

	char*pszFileName="evaluation.txt";
    CStdioFile myFile;
    CFileException fileException;
	int tag=0;

    if(myFile.Open(pszFileName,CFile::typeText|CFile::modeReadWrite),&fileException)
	{
		myFile.SeekToBegin();
		CString str1;
		myFile.ReadString(str1);
		CString str2;
		myFile.ReadString(str2);
		m_Result=str1+str2;
		UpdateData(false);

		tag=1;
	}


	myFile.Close();

	if(tag)
	{
	//*********画图**********
	FILE *fp;
	float **count;
	int i,j;
	int row=0,column=0;
	char ch;
     
	//......读入原始数据W......
	if((fp=fopen("evaluation.txt","r"))==NULL);//打开文件
    while(!feof(fp)&&(ch=fgetc(fp))!='\n')//统计列数
		if(ch=='\t')
			column++;
	column++;
	fseek(fp,0L,0);//置文件首部
	while(!feof(fp))//统计行数
		if(fgetc(fp)=='\n')
			row++;
		row++;

    count=(float**)malloc(sizeof(float*)*row);//为原始数据矩阵开辟内存
	for(i=0;i<row;i++)
		count[i]=(float*)malloc(sizeof(float)*column);

	fseek(fp,0L,0);//置文件首部
	while(!feof(fp))//读入数据
	for(i=0;i<row;i++)
		for(j=0;j<column;j++)
			fscanf(fp,"%f,",&count[i][j]);

	int biaoji=0;
	for(i=0;i<column;i++)
		if(count[0][i]<0)
			biaoji++;
	if(biaoji!=0)
	{
		AfxMessageBox("请考虑选用算法是否符合实际，综合评价值出现负数！");
		return;
	}

	int num=column;

	CClientDC dc(this);  
    //得到控件的大小
	CRect rect;  
    GetDlgItem(IDC_HUATU)->GetWindowRect(&rect);//获取控件相对于屏幕的位置  
    ScreenToClient(rect);//转化为对话框上的相对位置  
    CPen* pPenBlue = new CPen;                                  //创建画笔对象  
    pPenBlue->CreatePen(PS_SOLID, 2, RGB(0,0,225));     //蓝色画笔  
    CPen* pPenBlack = new CPen;                                 //创建画笔对象  
    pPenBlack->CreatePen(PS_SOLID, 1, RGB(0,0,0)); //黑色画笔  
    //选中黑色画笔，并保存当前画笔  
    CGdiObject* pOldPen = dc.SelectObject(pPenBlack);  
    //int i = 0;  ******************
    CString str;  
	int OriX=rect.left+50,OriY=rect.bottom-40;//坐标系原点OriX，OriY  
    CPoint OPos(OriX,OriY),NowPos;  //OPos是原点坐标 
	str.Format("%d",0);  
    dc.TextOut(OPos.x-15,OPos.y+5,str); 

	dc.MoveTo(OPos);  
    NowPos.x = rect.right;  
    NowPos.y = OPos.y;  
    dc.LineTo(NowPos);  
    //绘制箭头  
    dc.LineTo(NowPos.x - 5,NowPos.y - 5);  
    dc.MoveTo(NowPos);  
    dc.LineTo(NowPos.x - 5,NowPos.y + 5);  
      
    //寻找数据数组最大的数据  
    float MAXx = NowPos.x-OPos.x;  
    //x轴坐标系数的数据步长  
    int Tstepx =(int) (MAXx / (num+0.8));   //方案个数num  
    //x轴坐标系数的刻度步长
	int Xstep=Tstepx;
    for (i = 1;i <= num;i++)//显示num个刻度  
    {  
        dc.MoveTo(OPos.x + Xstep * i,OPos.y);  
        dc.LineTo(CPoint(OPos.x+Xstep * i,OPos.y-5));  
        
		str.Format("%d",i);  
        dc.TextOut(OPos.x + Xstep * i - 10,rect.bottom-36,str);  
    }  

	//横坐标名称
	str.Format("%s","方案/指标");  
    dc.TextOut(OPos.x + Xstep * (num/2),rect.bottom-20,str);
	//str.Format("%s","案");  
    //dc.TextOut(OPos.x + Xstep * (num/2+1),rect.bottom-20,str);

    //绘制y轴坐标系数  
    dc.MoveTo(OPos);  
    NowPos.x = OPos.x;  
    NowPos.y = rect.top;  
    dc.LineTo(NowPos);  
    //绘制箭头  
    dc.LineTo(NowPos.x - 5,NowPos.y + 5);  
    dc.MoveTo(NowPos);  
    dc.LineTo(NowPos.x + 5,NowPos.y + 5);  
      
    //寻找数据数组最大的数据  
    float MAXy = 0;  
    for (i = 0;i < num;i++)  
    {  
        if (MAXy < count[0][i])  
        {  
            MAXy = count[0][i];  
        }  
    }  
    //y轴坐标系数的数据步长  
    float Tstepy = MAXy / 10.;   //10个数据  
    //y轴坐标系数的刻度步长  
    int Ystep = (OriY-rect.top) / 22;//除以21的原因是，有20是因为上面的数据步长是10，现在20就是2格显示一个步长，还有一个1是多出来的好看  
    //显示y坐标的刻度和数据  
    for (i = 1;i < 23;i++)//显示21个刻度  
    {  
        dc.MoveTo(OPos.x,OPos.y - Ystep * i );  
        dc.LineTo(CPoint(OPos.x + 5,OPos.y - Ystep * i));  
        if (i % 2 == 0)  
        {  
            str.Format("%3.2f",Tstepy * i / 2);  
            dc.TextOut(rect.left+20,OPos.y - Ystep * i-8,str);  
        }  
    }  

	//纵坐标名称
	str.Format("%s","方");  
    dc.TextOut(rect.left+5,OPos.y - Ystep*15-24,str);
	str.Format("%s","案");  
    dc.TextOut(rect.left+5,OPos.y - Ystep*14-17,str);
	str.Format("%s","\/");  
    dc.TextOut(rect.left+10,OPos.y - Ystep*13-12,str);
	str.Format("%s","指");  
    dc.TextOut(rect.left+5,OPos.y - Ystep*12-7,str);
	str.Format("%s","标");  
    dc.TextOut(rect.left+5,OPos.y - Ystep*11,str);
	str.Format("%s","值");  
    dc.TextOut(rect.left+5,OPos.y - Ystep*10+7,str);
      
	//绘制灰度图像的直方图  
    int RealStep = OPos.y-rect.top-(OriY-rect.top-Ystep*21);  
    dc.SelectObject(pPenBlue); //选择蓝色画笔  
    for (i = 1;i <= num;i++)  
    {   
        NowPos.x = OPos.x + Tstepx*i;  
		
        NowPos.y = OPos.y;  
        dc.MoveTo(NowPos);  
        NowPos.y = OPos.y - (float)(((float)(RealStep*20))/(21*MAXy))*count[0][i-1];  
        //说明：上面这个大家可能不懂为什么，先注意一下上面的y轴坐标系数的数据步长，y轴坐标系数的刻度步长  
        //比例这样计算的：(RealStep/21):(max/10)=X:1,然后要求X，X表示1个数据用多少格表示</span>  
        dc.LineTo(NowPos);
		
		NowPos.x = OPos.x + Tstepx*i-MAXx/(3*num);
		NowPos.y = OPos.y;  
        dc.MoveTo(NowPos);  
        NowPos.y = OPos.y - (float)(((float)(RealStep*20))/(21*MAXy))*count[0][i-1];  
        dc.LineTo(NowPos);

		NowPos.y = OPos.y - (float)(((float)(RealStep*20))/(21*MAXy))*count[0][i-1];  
		NowPos.x = OPos.x + Tstepx*i;  
        dc.MoveTo(NowPos);
		NowPos.y = OPos.y - (float)(((float)(RealStep*20))/(21*MAXy))*count[0][i-1];  
		NowPos.x = OPos.x + Tstepx*i-MAXx/(3*num);
        dc.LineTo(NowPos);
	}  
        //恢复以前的画笔  
        dc.SelectObject(pOldPen);  
        delete pPenBlue;  
        delete pPenBlack;
		fclose(fp);
    	free(count[0]);
    	free(count);
    }

	//DeleteFile(pszFileName);
	
}

void CTest18Dlg::OnAbout() 
{
	CAboutDlg dlg;
	dlg.DoModal();	
}

void CTest18Dlg::OnExit() 
{
	CDialog::OnCancel();	
}

void CTest18Dlg::OnClear() 
{
	CString str;
	str=" ";
	m_Result=str;
	UpdateData(false);

	CRect Rect;
    GetDlgItem(IDC_HUATU)->GetWindowRect(&Rect);
	ScreenToClient(Rect);
    GetDC()-> FillSolidRect(Rect,RGB(255, 255, 255)); 

}

void CTest18Dlg::OnClearfile() 
{
	if(!(IDOK == AfxMessageBox(_T("是否删除计算结果文件！"), MB_OKCANCEL | MB_ICONQUESTION)))
	{
		return;
	}


	char *pszFileNameE="evaluation.txt";
	DeleteFile(pszFileNameE);
	char *pszFileNameW="weight.txt";
	DeleteFile(pszFileNameW);
}

void CTest18Dlg::OnAbout2() 
{
	CAboutDlg dlg;
	dlg.DoModal();
}
void CTest18Dlg::OnZbsfk() 
{
	// TODO: Add your command handler code here
	char *strPath;
	strPath="res_set\\指标算法库";
	ShellExecute(NULL,NULL,_T("explorer"),strPath,NULL,SW_SHOW);

}

void CTest18Dlg::OnPjsfk() 
{
	// TODO: Add your command handler code here
	char *strPath;
	strPath="res_set\\评价算法库";
	ShellExecute(NULL,NULL,_T("explorer"),strPath,NULL,SW_SHOW);

}

void CTest18Dlg::OnQtzsk() 
{
	// TODO: Add your command handler code here
	char *strPath;
	strPath="res_set\\其它知识库";
	ShellExecute(NULL,NULL,_T("explorer"),strPath,NULL,SW_SHOW);

}

void CTest18Dlg::OnYssj() 
{
	// TODO: Add your command handler code here
	char *strPath;
	strPath="res_set\\原始数据";
	ShellExecute(NULL,NULL,_T("explorer"),strPath,NULL,SW_SHOW);
	
}

void CTest18Dlg::OnPjzbsj() 
{
	// TODO: Add your command handler code here
	char *strPath;
	strPath="res_set\\评价指标数据";
	ShellExecute(NULL,NULL,_T("explorer"),strPath,NULL,SW_SHOW);
	
}

void CTest18Dlg::OnMcxzy() 
{
	// TODO: Add your command handler code here
	char *strPath;
	strPath="res_set\\Matlab程序资源";
	ShellExecute(NULL,NULL,_T("explorer"),strPath,NULL,SW_SHOW);
	
}

void CTest18Dlg::OnXmcgbg() 
{
	// TODO: Add your command handler code here
	char *strPath;
	strPath="res_set\\项目成果报告";
	ShellExecute(NULL,NULL,_T("explorer"),strPath,NULL,SW_SHOW);
	
}

void CTest18Dlg::OnTapcg() 
{
	// TODO: Add your command handler code here
	char *strPath;
	strPath="res_set\\理论应用与论文成果";
	ShellExecute(NULL,NULL,_T("explorer"),strPath,NULL,SW_SHOW);
	
}

void CTest18Dlg::OnJspjym() 
{
	// TODO: Add your command handler code here
	char *strPath;
	strPath="res_set\\技术经济评价源码";
	ShellExecute(NULL,NULL,_T("explorer"),strPath,NULL,SW_SHOW);
	
}