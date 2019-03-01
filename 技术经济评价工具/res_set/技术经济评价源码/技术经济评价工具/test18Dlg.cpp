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

	
	GetDlgItem(IDC_COMBO1)->EnableWindow(false);//δѡ��ѡ��ťʱӦ�ò���ѡ��
	GetDlgItem(IDC_COMBO2)->EnableWindow(false);
	GetDlgItem(IDC_DATA1)->EnableWindow(false);
	GetDlgItem(IDC_DATA2)->EnableWindow(false);
	GetDlgItem(IDC_OK1)->EnableWindow(false);
	GetDlgItem(IDC_OK2)->EnableWindow(false);

	//���ز˵���Դ����Ի���
	m_Menu.LoadMenu(IDR_MENU);  //IDR_MENUΪ����Ĳ˵���ID����Resource��ͼ��Menu�ļ����¿����ҵ�
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
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_ROMAN,"����");
		CDC* pDC=GetDC();
		pDC->SetTextColor(RGB(255,0,255));
		CFont* pOleFont=pDC->SelectObject(&m_Font);
		pDC->TextOut(160,30,"�����������۹���");
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

//��ӵĳ���������ʼ
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
	MessageBox("��ѡ��ԭʼ����!");

	CString FilePathNameO="";
    char filefilter[]="txt�ļ�(*.txt)|*.txt|";//�ļ�Ϊtxt��ʽ
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,filefilter);

    if(dlg.DoModal()==IDOK)
    FilePathNameO=dlg.GetPathName();

	filename=(LPSTR)(LPCTSTR)FilePathNameO;	

	if(FilePathNameO=="")
	{
		AfxMessageBox("ѡ��ԭʼ�����ļ�ʧ�ܣ�");
		return;
	}
	
	CString str;
    m_NewCom1.GetWindowText(str);

	if(str=="��ֵ��")
		CWe.entropy_weight(filename);
	else if(str=="��ɫ�����ȷ�")
		CWe.grey_correlation_degree(filename);
	else if(str=="����ϵ����")
		CWe.variance_coefficient(filename);
	else if(str=="��Ŀ���Ż���")
		CWe.multi_objective_optimization(filename);
	else if(str=="�����ϵ����")
		CWe.multiple_correlation_coefficient(filename);
	else if(str=="�˷���Ȩ��Ϸ�")
		CWe.multiple_weight(filename);
	else if(str=="���Լ�Ȩ��Ϸ�")
		CWe.linear_weight(filename);
	else if(str=="�Ľ���Ȩ��")
		CWe.improved_entropy_weight(filename);
	else if(str=="ר�Ҵ�ַ�")
		CWe.expert(filename);
	else if(str=="�Ա�����")
		CWe.contrast_compositor(filename);
	else if(str=="����ͼ��")
		CWe.PC(filename);
	else if(str=="CRITIC��")
		CWe.critic(filename);
	else if(str=="��η�����")
		CWe.AHP(filename);
	else
		AfxMessageBox("����ѡ��Ȩ�ط�����Ȼ�����ԣ�");	
}

void CTest18Dlg::OnData2() 
{
	CString str;
    m_NewCom2.GetWindowText(str);

	MessageBox("��ѡ��ԭʼ����!");
	CString FilePathNameO="";
    //CFileDialog dlg(TRUE);///TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
	char filefilter[]="txt�ļ�(*.txt)|*.txt|";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,filefilter);

    if(dlg.DoModal()==IDOK)
    FilePathNameO=dlg.GetPathName();
	filename=(LPSTR)(LPCTSTR)FilePathNameO;	
	if(FilePathNameO=="")
	{
		AfxMessageBox("ѡ��ԭʼ�����ļ�ʧ�ܣ�");
		return;
	}

	MessageBox("��������ѡ��Ȩ������!");
	CString FilePathNameW="";
    if(dlg.DoModal()==IDOK)
    FilePathNameW=dlg.GetPathName();
	weight_filename=(LPSTR)(LPCTSTR)FilePathNameW;	
	if(FilePathNameW=="")
	{
		AfxMessageBox("ѡ��Ȩ�������ļ�ʧ�ܣ�");
		return;
	}

	
	if(str=="�ۺ�ָ����")
		CEv.comprehensive_index(filename,weight_filename);
	else if(str=="��ɫ�����ۺ����۷�")
		CEv.grey_relational_comprehensive_evaluation(filename,weight_filename);
	else if(str=="��ɫ�ƽ�����ⷨ")
		CEv.topsis(filename,weight_filename);
	else if(str=="����ֵ��")
		CEv.osculating_value(filename,weight_filename);
	else
		AfxMessageBox("����ѡ���ۺ����۷�����Ȼ�����ԣ�");	
}

void CTest18Dlg::OnOk1() 
{
	if(!(IDOK == AfxMessageBox(_T("������������ǰ�Ƿ���<������ݺ�ͼ��>��ť��"), MB_OKCANCEL | MB_ICONQUESTION)))
	{
		AfxMessageBox("���ȵ��<������ݺ�ͼ��>��ť��,�ٵ��<ȷ��>��ť��");
		return;
	}

	CFileFind counter;
	BOOL bWorking = counter.FindFile("weight.txt");
	if(!bWorking)
	{
		AfxMessageBox("weight.txt�ļ����ƻ���δѡ�񷽷���δѡ��ԭʼ����1��");
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
	//*********��ͼ**********
	FILE *fp;
	float **count;
	int i,j;
	int row=0,column=0;
	char ch;
     
	//......����ԭʼ����W......
	if((fp=fopen("weight.txt","r"))==NULL);//���ļ�
    while(!feof(fp)&&(ch=fgetc(fp))!='\n')//ͳ������
		if(ch=='\t')
			column++;
	column++;
	fseek(fp,0L,0);//���ļ��ײ�
	while(!feof(fp))//ͳ������
		if(fgetc(fp)=='\n')
			row++;
		row++;

    count=(float**)malloc(sizeof(float*)*row);//Ϊԭʼ���ݾ��󿪱��ڴ�
	for(i=0;i<row;i++)
		count[i]=(float*)malloc(sizeof(float)*column);

	fseek(fp,0L,0);//���ļ��ײ�
	while(!feof(fp))//��������
	for(i=0;i<row;i++)
		for(j=0;j<column;j++)
			fscanf(fp,"%f,",&count[i][j]);

	int biaoji=0;
	for(i=0;i<column;i++)
		if(count[0][i]<0)
			biaoji++;
	if(biaoji!=0)
	{
		AfxMessageBox("�뿼��ѡ���㷨�Ƿ����ʵ�ʣ�ָ��ֵ���ָ�����");
		return;
	}

	int num=column;

	CClientDC dc(this);  
    //�õ��ؼ��Ĵ�С
	CRect rect;  
    GetDlgItem(IDC_HUATU)->GetWindowRect(&rect);//��ȡ�ؼ��������Ļ��λ��  
    ScreenToClient(rect);//ת��Ϊ�Ի����ϵ����λ��  
    CPen* pPenBlue = new CPen;                                  //�������ʶ���  
    pPenBlue->CreatePen(PS_SOLID, 2, RGB(0,0,225));     //��ɫ����  
    CPen* pPenBlack = new CPen;                                 //�������ʶ���  
    pPenBlack->CreatePen(PS_SOLID, 1, RGB(0,0,0)); //��ɫ����  
    //ѡ�к�ɫ���ʣ������浱ǰ����  
    CGdiObject* pOldPen = dc.SelectObject(pPenBlack);  
    //int i = 0;  ******************
    CString str;  
	int OriX=rect.left+50,OriY=rect.bottom-40;//����ϵԭ��OriX��OriY  
    CPoint OPos(OriX,OriY),NowPos;  //OPos��ԭ������ 
	str.Format("%d",0);  
    dc.TextOut(OPos.x-15,OPos.y+5,str); 

	dc.MoveTo(OPos);  
    NowPos.x = rect.right;  
    NowPos.y = OPos.y;  
    dc.LineTo(NowPos);  
    //���Ƽ�ͷ  
    dc.LineTo(NowPos.x - 5,NowPos.y - 5);  
    dc.MoveTo(NowPos);  
    dc.LineTo(NowPos.x - 5,NowPos.y + 5);  
      
    //Ѱ������������������  
    float MAXx = NowPos.x-OPos.x;  
    //x������ϵ�������ݲ���  
    int Tstepx =(int) (MAXx / (num+0.8));   //��������num  
    //x������ϵ���Ŀ̶Ȳ���
	int Xstep=Tstepx;
    for (i = 1;i <= num;i++)//��ʾnum���̶�  
    {  
        dc.MoveTo(OPos.x + Xstep * i,OPos.y);  
        dc.LineTo(CPoint(OPos.x+Xstep * i,OPos.y-5));  
        
		str.Format("%d",i);  
        dc.TextOut(OPos.x + Xstep * i - 10,rect.bottom-36,str);  
    }  

	//����������
	str.Format("%s","����/ָ��");  
    dc.TextOut(OPos.x + Xstep * (num/2),rect.bottom-20,str);
	//str.Format("%s","��");  
    //dc.TextOut(OPos.x + Xstep * (num/2+1),rect.bottom-20,str);

    //����y������ϵ��  
    dc.MoveTo(OPos);  
    NowPos.x = OPos.x;  
    NowPos.y = rect.top;  
    dc.LineTo(NowPos);  
    //���Ƽ�ͷ  
    dc.LineTo(NowPos.x - 5,NowPos.y + 5);  
    dc.MoveTo(NowPos);  
    dc.LineTo(NowPos.x + 5,NowPos.y + 5);  
      
    //Ѱ������������������  
    float MAXy = 0;  
    for (i = 0;i < num;i++)  
    {  
        if (MAXy < count[0][i])  
        {  
            MAXy = count[0][i];  
        }  
    }  
    //y������ϵ�������ݲ���  
    float Tstepy = MAXy / 10.;   //10������  
    //y������ϵ���Ŀ̶Ȳ���  
    int Ystep = (OriY-rect.top) / 22;//����21��ԭ���ǣ���20����Ϊ��������ݲ�����10������20����2����ʾһ������������һ��1�Ƕ�����ĺÿ�  
    //��ʾy����Ŀ̶Ⱥ�����  
    for (i = 1;i < 23;i++)//��ʾ21���̶�  
    {  
        dc.MoveTo(OPos.x,OPos.y - Ystep * i );  
        dc.LineTo(CPoint(OPos.x + 5,OPos.y - Ystep * i));  
        if (i % 2 == 0)  
        {  
            str.Format("%3.2f",Tstepy * i / 2);  
            dc.TextOut(rect.left+20,OPos.y - Ystep * i-8,str);  
        }  
    }  

	//����������
	str.Format("%s","��");  
    dc.TextOut(rect.left+5,OPos.y - Ystep*15-24,str);
	str.Format("%s","��");  
    dc.TextOut(rect.left+5,OPos.y - Ystep*14-17,str);
	str.Format("%s","\/");  
    dc.TextOut(rect.left+10,OPos.y - Ystep*13-12,str);
	str.Format("%s","ָ");  
    dc.TextOut(rect.left+5,OPos.y - Ystep*12-7,str);
	str.Format("%s","��");  
    dc.TextOut(rect.left+5,OPos.y - Ystep*11,str);
	str.Format("%s","ֵ");  
    dc.TextOut(rect.left+5,OPos.y - Ystep*10+7,str);
      
	//���ƻҶ�ͼ���ֱ��ͼ  
    int RealStep = OPos.y-rect.top-(OriY-rect.top-Ystep*21);  
    dc.SelectObject(pPenBlue); //ѡ����ɫ����  
    for (i = 1;i <= num;i++)  
    {   
        NowPos.x = OPos.x + Tstepx*i;  
		
        NowPos.y = OPos.y;  
        dc.MoveTo(NowPos);  
        NowPos.y = OPos.y - (float)(((float)(RealStep*20))/(21*MAXy))*count[0][i-1];  
        //˵�������������ҿ��ܲ���Ϊʲô����ע��һ�������y������ϵ�������ݲ�����y������ϵ���Ŀ̶Ȳ���  
        //������������ģ�(RealStep/21):(max/10)=X:1,Ȼ��Ҫ��X��X��ʾ1�������ö��ٸ��ʾ</span>  
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
        //�ָ���ǰ�Ļ���  
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
	if(!(IDOK == AfxMessageBox(_T("������������ǰ�Ƿ���<������ݺ�ͼ��>��ť��"), MB_OKCANCEL | MB_ICONQUESTION)))
	{
		AfxMessageBox("���ȵ��<������ݺ�ͼ��>��ť��,�ٵ��<ȷ��>��ť��");
		return;
	}

	CFileFind counter;
	BOOL bWorking = counter.FindFile("evaluation.txt");
	if(!bWorking)
	{
		AfxMessageBox("evaluation.txt�ļ����ƻ���δѡ�񷽷���δѡ��ԭʼ����2��");
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
	//*********��ͼ**********
	FILE *fp;
	float **count;
	int i,j;
	int row=0,column=0;
	char ch;
     
	//......����ԭʼ����W......
	if((fp=fopen("evaluation.txt","r"))==NULL);//���ļ�
    while(!feof(fp)&&(ch=fgetc(fp))!='\n')//ͳ������
		if(ch=='\t')
			column++;
	column++;
	fseek(fp,0L,0);//���ļ��ײ�
	while(!feof(fp))//ͳ������
		if(fgetc(fp)=='\n')
			row++;
		row++;

    count=(float**)malloc(sizeof(float*)*row);//Ϊԭʼ���ݾ��󿪱��ڴ�
	for(i=0;i<row;i++)
		count[i]=(float*)malloc(sizeof(float)*column);

	fseek(fp,0L,0);//���ļ��ײ�
	while(!feof(fp))//��������
	for(i=0;i<row;i++)
		for(j=0;j<column;j++)
			fscanf(fp,"%f,",&count[i][j]);

	int biaoji=0;
	for(i=0;i<column;i++)
		if(count[0][i]<0)
			biaoji++;
	if(biaoji!=0)
	{
		AfxMessageBox("�뿼��ѡ���㷨�Ƿ����ʵ�ʣ��ۺ�����ֵ���ָ�����");
		return;
	}

	int num=column;

	CClientDC dc(this);  
    //�õ��ؼ��Ĵ�С
	CRect rect;  
    GetDlgItem(IDC_HUATU)->GetWindowRect(&rect);//��ȡ�ؼ��������Ļ��λ��  
    ScreenToClient(rect);//ת��Ϊ�Ի����ϵ����λ��  
    CPen* pPenBlue = new CPen;                                  //�������ʶ���  
    pPenBlue->CreatePen(PS_SOLID, 2, RGB(0,0,225));     //��ɫ����  
    CPen* pPenBlack = new CPen;                                 //�������ʶ���  
    pPenBlack->CreatePen(PS_SOLID, 1, RGB(0,0,0)); //��ɫ����  
    //ѡ�к�ɫ���ʣ������浱ǰ����  
    CGdiObject* pOldPen = dc.SelectObject(pPenBlack);  
    //int i = 0;  ******************
    CString str;  
	int OriX=rect.left+50,OriY=rect.bottom-40;//����ϵԭ��OriX��OriY  
    CPoint OPos(OriX,OriY),NowPos;  //OPos��ԭ������ 
	str.Format("%d",0);  
    dc.TextOut(OPos.x-15,OPos.y+5,str); 

	dc.MoveTo(OPos);  
    NowPos.x = rect.right;  
    NowPos.y = OPos.y;  
    dc.LineTo(NowPos);  
    //���Ƽ�ͷ  
    dc.LineTo(NowPos.x - 5,NowPos.y - 5);  
    dc.MoveTo(NowPos);  
    dc.LineTo(NowPos.x - 5,NowPos.y + 5);  
      
    //Ѱ������������������  
    float MAXx = NowPos.x-OPos.x;  
    //x������ϵ�������ݲ���  
    int Tstepx =(int) (MAXx / (num+0.8));   //��������num  
    //x������ϵ���Ŀ̶Ȳ���
	int Xstep=Tstepx;
    for (i = 1;i <= num;i++)//��ʾnum���̶�  
    {  
        dc.MoveTo(OPos.x + Xstep * i,OPos.y);  
        dc.LineTo(CPoint(OPos.x+Xstep * i,OPos.y-5));  
        
		str.Format("%d",i);  
        dc.TextOut(OPos.x + Xstep * i - 10,rect.bottom-36,str);  
    }  

	//����������
	str.Format("%s","����/ָ��");  
    dc.TextOut(OPos.x + Xstep * (num/2),rect.bottom-20,str);
	//str.Format("%s","��");  
    //dc.TextOut(OPos.x + Xstep * (num/2+1),rect.bottom-20,str);

    //����y������ϵ��  
    dc.MoveTo(OPos);  
    NowPos.x = OPos.x;  
    NowPos.y = rect.top;  
    dc.LineTo(NowPos);  
    //���Ƽ�ͷ  
    dc.LineTo(NowPos.x - 5,NowPos.y + 5);  
    dc.MoveTo(NowPos);  
    dc.LineTo(NowPos.x + 5,NowPos.y + 5);  
      
    //Ѱ������������������  
    float MAXy = 0;  
    for (i = 0;i < num;i++)  
    {  
        if (MAXy < count[0][i])  
        {  
            MAXy = count[0][i];  
        }  
    }  
    //y������ϵ�������ݲ���  
    float Tstepy = MAXy / 10.;   //10������  
    //y������ϵ���Ŀ̶Ȳ���  
    int Ystep = (OriY-rect.top) / 22;//����21��ԭ���ǣ���20����Ϊ��������ݲ�����10������20����2����ʾһ������������һ��1�Ƕ�����ĺÿ�  
    //��ʾy����Ŀ̶Ⱥ�����  
    for (i = 1;i < 23;i++)//��ʾ21���̶�  
    {  
        dc.MoveTo(OPos.x,OPos.y - Ystep * i );  
        dc.LineTo(CPoint(OPos.x + 5,OPos.y - Ystep * i));  
        if (i % 2 == 0)  
        {  
            str.Format("%3.2f",Tstepy * i / 2);  
            dc.TextOut(rect.left+20,OPos.y - Ystep * i-8,str);  
        }  
    }  

	//����������
	str.Format("%s","��");  
    dc.TextOut(rect.left+5,OPos.y - Ystep*15-24,str);
	str.Format("%s","��");  
    dc.TextOut(rect.left+5,OPos.y - Ystep*14-17,str);
	str.Format("%s","\/");  
    dc.TextOut(rect.left+10,OPos.y - Ystep*13-12,str);
	str.Format("%s","ָ");  
    dc.TextOut(rect.left+5,OPos.y - Ystep*12-7,str);
	str.Format("%s","��");  
    dc.TextOut(rect.left+5,OPos.y - Ystep*11,str);
	str.Format("%s","ֵ");  
    dc.TextOut(rect.left+5,OPos.y - Ystep*10+7,str);
      
	//���ƻҶ�ͼ���ֱ��ͼ  
    int RealStep = OPos.y-rect.top-(OriY-rect.top-Ystep*21);  
    dc.SelectObject(pPenBlue); //ѡ����ɫ����  
    for (i = 1;i <= num;i++)  
    {   
        NowPos.x = OPos.x + Tstepx*i;  
		
        NowPos.y = OPos.y;  
        dc.MoveTo(NowPos);  
        NowPos.y = OPos.y - (float)(((float)(RealStep*20))/(21*MAXy))*count[0][i-1];  
        //˵�������������ҿ��ܲ���Ϊʲô����ע��һ�������y������ϵ�������ݲ�����y������ϵ���Ŀ̶Ȳ���  
        //������������ģ�(RealStep/21):(max/10)=X:1,Ȼ��Ҫ��X��X��ʾ1�������ö��ٸ��ʾ</span>  
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
        //�ָ���ǰ�Ļ���  
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
	if(!(IDOK == AfxMessageBox(_T("�Ƿ�ɾ���������ļ���"), MB_OKCANCEL | MB_ICONQUESTION)))
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
	strPath="res_set\\ָ���㷨��";
	ShellExecute(NULL,NULL,_T("explorer"),strPath,NULL,SW_SHOW);

}

void CTest18Dlg::OnPjsfk() 
{
	// TODO: Add your command handler code here
	char *strPath;
	strPath="res_set\\�����㷨��";
	ShellExecute(NULL,NULL,_T("explorer"),strPath,NULL,SW_SHOW);

}

void CTest18Dlg::OnQtzsk() 
{
	// TODO: Add your command handler code here
	char *strPath;
	strPath="res_set\\����֪ʶ��";
	ShellExecute(NULL,NULL,_T("explorer"),strPath,NULL,SW_SHOW);

}

void CTest18Dlg::OnYssj() 
{
	// TODO: Add your command handler code here
	char *strPath;
	strPath="res_set\\ԭʼ����";
	ShellExecute(NULL,NULL,_T("explorer"),strPath,NULL,SW_SHOW);
	
}

void CTest18Dlg::OnPjzbsj() 
{
	// TODO: Add your command handler code here
	char *strPath;
	strPath="res_set\\����ָ������";
	ShellExecute(NULL,NULL,_T("explorer"),strPath,NULL,SW_SHOW);
	
}

void CTest18Dlg::OnMcxzy() 
{
	// TODO: Add your command handler code here
	char *strPath;
	strPath="res_set\\Matlab������Դ";
	ShellExecute(NULL,NULL,_T("explorer"),strPath,NULL,SW_SHOW);
	
}

void CTest18Dlg::OnXmcgbg() 
{
	// TODO: Add your command handler code here
	char *strPath;
	strPath="res_set\\��Ŀ�ɹ�����";
	ShellExecute(NULL,NULL,_T("explorer"),strPath,NULL,SW_SHOW);
	
}

void CTest18Dlg::OnTapcg() 
{
	// TODO: Add your command handler code here
	char *strPath;
	strPath="res_set\\����Ӧ�������ĳɹ�";
	ShellExecute(NULL,NULL,_T("explorer"),strPath,NULL,SW_SHOW);
	
}

void CTest18Dlg::OnJspjym() 
{
	// TODO: Add your command handler code here
	char *strPath;
	strPath="res_set\\������������Դ��";
	ShellExecute(NULL,NULL,_T("explorer"),strPath,NULL,SW_SHOW);
	
}