function varargout = SysOfEval(varargin)
% SYSOFEVAL MATLAB code for SysOfEval.fig
%      SYSOFEVAL, by itself, creates a new SYSOFEVAL or raises the existing
%      singleton*.
%
%      H = SYSOFEVAL returns the handle to a new SYSOFEVAL or the handle to
%      the existing singleton*.
%
%      SYSOFEVAL('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in SYSOFEVAL.M with the given input arguments.
%
%      SYSOFEVAL('Property','Value',...) creates a new SYSOFEVAL or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before SysOfEval_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to SysOfEval_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help SysOfEval

% Last Modified by GUIDE v2.5 31-Oct-2015 18:55:33

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @SysOfEval_OpeningFcn, ...
                   'gui_OutputFcn',  @SysOfEval_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before SysOfEval is made visible.
function SysOfEval_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to SysOfEval (see VARARGIN)

% Choose default command line output for SysOfEval
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes SysOfEval wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = SysOfEval_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --------------------------------------------------------------------
function TSC_Callback(hObject, eventdata, handles)
% hObject    handle to TSC (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function RA_Callback(hObject, eventdata, handles)
% hObject    handle to RA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
button0 = questdlg('�Ƿ��ȡԭʼ���ݲ���������Է�����','������ʾ','Yes','No','Yes'); %������ť
if strcmp(button0,'No')
    return;
end
dir = get(handles.pathfile,'String');
A = xlsread(dir,-1);
R = corrcoef(A);
set(handles.table,'data',R);
notes = '    ͨ���趨�����ϵ����ֵ�Լ����ϵ��������ԶԸ�ָ���������Է������Ӷ����Ե�ͳ�Ƴ�ָ��������ԡ�';
set(handles.text_notes,'string',notes)


% --------------------------------------------------------------------
function PCA_Callback(hObject, eventdata, handles)
% hObject    handle to PCA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
button0 = questdlg('�Ƿ��ȡԭʼ���ݲ��������ɷַ���������','������ʾ','Yes','No','Yes'); %������ť
if strcmp(button0,'No')
    return;
end
dir = get(handles.pathfile,'String');
X = xlsread(dir,-1);%��ȡ����
[m,n] = size(X);

%���������ı�׼��;�ֵ����
stdr = std(X,0,1);
meanc = mean(X);
sr = (X-meanc(ones(m,1),:))./stdr(ones(m,1),:);

%�������ɷַ������󷽲����
[pcs,newdata,variances,t2] = princomp(sr);
%����pcsΪ����������newdata���ɷֵ÷֣�variancesΪ����ֵ��t2Ϊͳ����Hotelling
%����ֻ�õ�newdata��variances
percent_explained = 100*variances/sum(variances);

%����Է�������EW
a = X'*newdata;
b1 = sum(X.*X);
b2 = sum(newdata.*newdata);
b1 = b1.^(0.5);
b2 = b2.^(0.5);
b = b1*b2';
EW = a./b;
Result = sum(EW,2);

%��������table�ؼ������ñ�ע
set(handles.table,'data',Result);
notes = '        �������ɷַ����㷨�󣬿����ڷ���������еõ���ָ����������ɷ�Ӱ���ܺ͵�����ֵ���������ֵ����50%����˵����ָ������ɷ�Ӱ��ϴ�ͬʱ�����򻹻��ڻ�ͼ�����л�������ֵ�����ʵı�״ͼ��';
set(handles.text_notes,'string',notes)

%������ֵ��ռ�������ɱ�ͼ��ʾ��axes�ؼ�
axes(handles.draw_axes)
colormap(cool); %ͨ��colormapת����ɫ
len = length(percent_explained);
pie3(percent_explained);

% --------------------------------------------------------------------
function FA_Callback(hObject, eventdata, handles)
% hObject    handle to FA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
button0 = questdlg('�Ƿ��ȡԭʼ���ݲ��������ӷ�����','������ʾ','Yes','No','Yes'); %������ť
if strcmp(button0,'No')
    return;
end
dir = get(handles.pathfile,'String');
X = xlsread(dir,-1);%��ȡ����
[m,n]=size(X);

%���ó�ʼ����
thelong=0.000001;
Max=inf;
delta=inf;

%���ϵ������
sr = zscore(X);
R = sr'*sr/(m-1);

%�������ɷַ���
[pcs,newdata,variances,t2] = princomp(sr);

%����ֵռ����ٷ���
percent_explained = 100*variances/sum(variances);

%����ֵ���ۼưٷ���
leiji = percent_explained./sum(percent_explained);
for i = 1:n
    lj_percentage(i) = sum(leiji(1:i));
end
leiji_percentage = lj_percentage';

%������ֵ��ռ�������ɱ�ͼ��ʾ��axes�ؼ�
axes(handles.draw_axes)
colormap(cool); %ͨ��colormapת����ɫ
len = length(percent_explained);
pie3(percent_explained);

%���濪ʼ�������غɾ���
for j = 1:n
    AA(:,j) = sqrt(variances(j,1))*pcs(:,j);
end
for i = 1:n
    if(lj_percentage(i) >= 0.85)
        k = i;
        break;
    end
end
A = AA(:,1:k); %�����غɾ���

%��h��ƽ������ͬ�ȣ���d��ƽ����ʣ�෽���g��ƽ��������ף�
BB = power(A,2);
for j = 1:n
    hhh(j) = sum(BB(j,:));
end
hh = hhh';
h = sqrt(hh);
dd = 1-h;
gg = sum(BB);

%���濪ʼ�󷽲����������ת����
%��ֵ��theta
M = 0;
B = A;
TTT = eye(k,k);
while(delta>thelong)
    M = M+1;
    for r = 1:k-1
        if r == 1
            T1 = eye(k,k);
        end
        for g = r+1:k
            x = B(:,r)./h;
            y = B(:,g)./h;
            v = power(x,2)-power(y,2);
            w = 2*x.*y;
            a = sum(v);
            b = sum(w);
            c = sum(power(v,2)-power(w,2));
            d = 2*sum(v.*w);
            e = d-2*a*b/n;
            f = c-(power(a,2)-power(b,2))/n;
            if e == 0
                break;
            else
                theta = acot(f/e);
                theta = theta/4;
            end
            if and(e>0,theta<0)
                theta = theta+pi/4;
            elseif and(e<0,theta>0)
                theta = theta-pi/4;
            end
            TT = eye(k,k);
            TT(r,r) = cos(theta);
            TT(r,g) = -sin(theta);
            TT(g,r) = sin(theta);
            TT(g,g) = cos(theta);
            TTT = TT*TTT;
            T1 = TT*T1;
        end
    end
    B = B*T1;
    BB = power(B,2);
    ddd = BB./hh(:,ones(k,1));
    aver = mean(ddd);
    VV = sum(power(ddd-aver(ones(n,1),:),2)/n);
    V(M) = sum(VV);
    if M == 1
        delta = Max;
    else
        delta = abs(V(M)-V(M-1));
    end
end
%{
V
N = M
B
TTT
%}

%���濪ʼ���������ӵ÷־���
for i = 1:m
    XX = zscore(X);
    XX = XX(i,:);
    F = B'*inv(R);
    FF(i,:) = (F*XX')';
end
%��������table�ؼ������ñ�ע
set(handles.table,'data',FF);
notes = '        �������ӷ����㷨�󣬿����ڷ���������еõ��������ӵ÷־���һ����˵��ÿ������ֻ����������ָ��������غɽϴ���ˣ����Ը��ݴ˵÷־���ָ�갴���غɽ��з��ಢ���רҵ֪ʶ�Ը�����������ͬʱ�����򻹻��ڻ�ͼ�����л�������ֵ�����ʵı�״ͼ��';
set(handles.text_notes,'string',notes)


% --------------------------------------------------------------------
function ZBQZL_Callback(hObject, eventdata, handles)
% hObject    handle to ZBQZL (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function ZJPP_Callback(hObject, eventdata, handles)
% hObject    handle to ZJPP (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
button = questdlg('�Ƿ��ָ�����ר�����۲���ԭʼ���ݱ�','������ʾ','Yes','No','Yes'); %������ť
if button == 'Yes'
    dir = get(handles.pathfile,'String');
    X = xlsread(dir,-1);%��ȡ����
end
[a0,b0] = size(X);
if a0 > 1 && b0 > 1
    msgbox('ָ�������ѳ���һά����ע�����ݵ�ѡȡ��');
    return;
end

sumX = sum(X);% ��һ��
oneX = X./sumX;
set(handles.table,'data',oneX');
notes = '        ר�����۹���Ϊר���ṩһ������ԭʼ���ݲ��Ը�ָ��������ֵĽ������棻����ʱ�뽫��ָ�갴�հٷ��ƽ��д�֣���ɴ�ֺ�ѡ�и�ָ���������ֽ�������ȷ����֮�󽫷����û����档';
set(handles.text_notes,'string',notes)
axes(handles.draw_axes);
plot(oneX,'--rs',...
    'LineWidth',2,...
    'MarkerEdgeColor','k',...
    'MarkerFaceColor','g',...
    'MarkerSize',10);
if 5 <= length(oneX)
    ylim([min(oneX)+0.05*min(oneX) max(oneX)+0.05*max(oneX)]);   % ����y�᷶Χ
end
xlabel('ָ�����','FontSize',10);

% --------------------------------------------------------------------
function TCP_Callback(hObject, eventdata, handles)
% hObject    handle to TCP (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function ABOUT_Callback(hObject, eventdata, handles)
% hObject    handle to ABOUT (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%web help\����ƽ̨.txt
winopen('help\����ƽ̨.txt')


% --------------------------------------------------------------------
function FCE_Callback(hObject, eventdata, handles)
% hObject    handle to FCE (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
button0 = questdlg('�Ƿ��ȡԭʼ���ݲ�����ģ���ۺ����У�','������ʾ','Yes','No','Yes'); %������ť
if strcmp(button0,'No')
    return;
end
 %�������ݡ�
dir = get(handles.pathfile,'String');
data=xlsread(dir,-1);
[n,m]=size(data);%n����������mָ�����

button1 = questdlg('��ѡ��ָ��Ȩ��������ѡ��No���˳�������','������ʾ','Yes','No','Yes'); %������ť
if strcmp(button1,'No')
    return;
end
weight=xlsread(dir,-1);
if m ~= length(weight)
    warndlg('ָ��Ȩ����Ŀ��ԭʼ����ָ����Ŀ����ȣ�');
    return;
end

button1 = questdlg('��ѡ��ָ�ȼ��������ݣ��˴���ط�Ϊ�����ȼ��㣬��3*N���󣩣�ѡ��No���˳�������','������ʾ','Yes','No','Yes'); %������ť
if strcmp(button1,'No')
    return;
end
dengji=xlsread(dir,-1);
[n0,m0] = size(dengji);
if 3 ~= n0 && m0 ~= m
    warndlg('������ȼ����־����ָ����Ŀ��ԭʼ����ָ����Ŀ���ȣ�');
    return;
end

%���ݱ�׼��
mean_d=mean(data);
for j=1:m
    data(:,j)=data(:,j)/mean_d(j);
end

%����������������0,1/3,2/3��1Ϊ�ĸ��ȼ���������
for j=1:m
    a=dengji(3,j);b=dengji(2,j);c=dengji(1,j);
    for i=1:n
        x=data(i,j);
        if x>c
            lsd(i,j)=1;
        elseif x>b
            A=[c*c,c,1;(b+c)^2/4,(b+c)/2,1;b*b,b,1];
            B=[1,2/3,1/2]';
            C=inv(A)*B;
            lsd(i,j)=[x*x,x,1]*C;
        elseif x>a
            A=[b*b,b,1;(b+a)^2/4,(b+a)/2,1;a*a,a,1];
            B=[1/2,1/3,0]';
            C=inv(A)*B;
            lsd(i,j)=[x*x,x,1]*C;
        else
            lsd(i,j)=0;
        end
    end
end
%�ۺ�����
zp=lsd*weight';
result = [lsd zp];
set(handles.table,'data',result);
notes = '        ģ���ۺ�������Ҫ�ṩԭʼ���ݣ�ָ��Ȩ�������Լ��ȼ����������ģ���ۺ������㷨����0,1/3,2/3��1Ϊ�ĸ��ȼ��������Ĳ���ϵȼ��������������Ⱥ�����������Լ�����������ۺϵ÷֣������������Ⱦ������һ��Ϊ�������÷��������������÷�����ͼ��';
set(handles.text_notes,'string',notes)
axes(handles.draw_axes);
plot(zp,'--rs',...
    'LineWidth',2,...
    'MarkerEdgeColor','k',...
    'MarkerFaceColor','g',...
    'MarkerSize',10);
if 5 <= length(zp)
    ylim([min(zp)+0.05*min(zp) max(zp)+0.05*max(zp)]);   % ����y�᷶Χ
end
xlabel('�������','FontSize',10);



% --------------------------------------------------------------------
function HFCE_Callback(hObject, eventdata, handles)
% hObject    handle to HFCE (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

button = questdlg('���ȡ���㾫��e������������Max���Ƿ�������У�','������ʾ','Yes','No','Yes'); %������ť
if strcmp(button,'No')
    return;
end
dir = get(handles.pathfile,'String');
EMax = xlsread(dir,-1);%��ȡ����
[a0,a1] = size(EMax);
if (a0 == 1 && a1 == 2) || (a0 == 2 && a1 == 1)
    
else
    msgbox('��ѡȡ�ľ��Ⱥ͵����������ݲ�����2Ԫ�ص�һά���飬������ѡ��');
    return;
end
E = EMax(1);
Max = EMax(2);
%�������ȹ�ϵ���� 
F = xlsread(dir,-1);
[b0,b1] = size(F)
if b0 ~= b1
    msgbox('��ѡȡ�����ݲ��������ȹ�ϵ���󣨷��󣩣�������ѡ��');
    return;
end

%����ģ��һ�¾��� 
N=size(F); 
r=sum(F'); 
for i=1:N(1) 
    for j=1:N(2) 
        R(i,j)=(r(i)-r(j))/(2*N(1))+0.5; 
    end 
end 
E=R./R'; 
% �����ʼ���� ---------- 
% W=sum(R')./sum(sum(R)); % ���й�һ�� 
%--------------------------------------------------------- 
for i=1:N(1) 
    S(i)=R(i,1); 
    for j=2:N(2) 
        S(i)=S(i)*R(i,j); 
    end 
end 
S=S.^(1/N(1)); 
W = S./sum(S)%������
% a=input('����a=?'); 
%W=sum(R')/(N(1)*a)-1/(2*a)+1/N(1); %����
V(:,1)=W'/max(abs(W));% �����ݷ�������������
for i=1:Max 
    V(:,i+1)=E*V(:,i); 
    V(:,i+1)=V(:,i+1)/max(abs(V(:,i+1))); 
    if max(abs(V(:,i+1)-V(:,i)))k=i; 
        A=V(:,i+1)./sum(V(:,i+1)); 
        break
    else
    end
end
weights = [W;A'];

set(handles.table,'data',weights');
notes = '        �豣֤���㾫������������������������ѡȡ�����ȹ�ϵ�����Ƿ����벢����Գ����ݺ�Ϊ1�����Ǳ��룩�����в��ģ���㷨�󣬽��õ��ò�ָ���Ȩ�أ���һ���ַ��������ã��ڶ������ݷ��������ã�������֮�⽫��ʾ���������ָ��Ȩ�ص�ͼ�����ø��㷨��������Ȩֵȷ�������տ���ȷ������ָ���Ȩ��ֵ!';
set(handles.text_notes,'string',notes)
axes(handles.draw_axes);
plot(W,'--rs',...
    'LineWidth',2,...
    'MarkerEdgeColor','k',...
    'MarkerFaceColor','g',...
    'MarkerSize',10);
if 5 <= length(W)
    ylim([min(W)+0.05*min(W) max(W)+0.05*max(W)]);   % ����y�᷶Χ
end
xlabel('ָ�����--������','FontSize',10);


% --------------------------------------------------------------------
function DEA_Callback(hObject, eventdata, handles)
% hObject    handle to DEA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function HE_Callback(hObject, eventdata, handles)
% hObject    handle to HE (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%web help\���۰���.txt
winopen('help\���۰���.txt')


% --------------------------------------------------------------------
function AHP_Callback(hObject, eventdata, handles)
% hObject    handle to AHP (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
button0 = questdlg('�Ƿ��ȡԭʼ���ݲ����в�η�����','������ʾ','Yes','No','Yes'); %������ť
if strcmp(button0,'No')
    return;
end
dir = get(handles.pathfile,'String');
X = xlsread(dir,-1);%��ȡ����

[b0,b1] = size(X);
if b0 ~= b1
    msgbox('��ѡȡ�����ݲ��������ȹ�ϵ���󣨷��󣩣�������ѡ��');
    return;
end
                                     %���ضԱȾ���X��ֻ��Ҫ�ı����X
[m,n] = size(X);                     %��ȡָ�����
if n >15
    msgbox('ָ�����������ܳ���15��');
    return;
end
                                     %��ͬά�ȶ�Ӧ��RIֵ
RI = [0 0 0.58 0.90 1.12 1.24 1.32 1.41 1.45 1.49 1.51 1.54 1.56 1.58 1.59];
R = rank(X);                         %���жϾ������
[V,D] = eig(X);                      %���жϾ��������ֵ������������V����ֵ��D����������
tz = max(D);
B = max(tz);                         %�������ֵ
[row, col] = find(D == B);           %�������ֵ����λ��
C = V(:,col);                        %��Ӧ��������
CI = (B-n)/(n-1);                    %����һ���Լ���ָ��CI
CR = CI/RI(1,n);   
if CR < 0.10
    stringCI = num2str(CI);
    stringCR = num2str(CR);
    str = strcat('  �жϾ���Xͨ��һ���Լ��飬','CR=',stringCI,'��CI=',stringCR,'  ');
    msgbox(str);
    Q = zeros(n,1);
    for i = 1:n
        Q(i,1) = C(i,1)/sum(C(:,1)); %����������׼��
    end
    %Q                               %���Ȩ������
    %��������table�ؼ������ñ�ע
    set(handles.table,'data',Q);
    notes = '        �������ݾ���Ϊ�жϾ������в�η����㷨�󣬿����ڷ���������еõ���ָ���Ȩ�أ�ֵ��ע����Ǹ����ָ����Ŀ��Ҫ����15��ԭ���ǲ�ͬά�ȶ�Ӧ��RIֵ���Ϊ15��';
    set(handles.text_notes,'string',notes)
    axes(handles.draw_axes);
    plot(Q,'--rs',...
        'LineWidth',2,...
        'MarkerEdgeColor','k',...
        'MarkerFaceColor','g',...
        'MarkerSize',10);
    if 5 <= length(Q)
        ylim([min(Q)+0.05*min(Q) max(Q)+0.05*max(Q)]);   % ����y�᷶Χ
    end
    xlabel('ָ�����','FontSize',10);
else
    msgbox('�ԱȾ���Aδͨ��һ���Լ��飬��ԶԱȾ���A���¹���');
    return;
end


% --------------------------------------------------------------------
function BYXS_Callback(hObject, eventdata, handles)
% hObject    handle to BYXS (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function HSGL_Callback(hObject, eventdata, handles)
% hObject    handle to HSGL (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%����ԭʼ����ȫΪ����ָ�꣬������ȫ��ָ��ֵԽ��Խ��
bData = questdlg('ԭʼ�����Ƿ�����������ָ�ꣿ','������ʾ','Yes','No','Yes');
if bData == 'Yes'
    dir = get(handles.pathfile,'String');
    X = xlsread(dir,-1);        %��ȡԭʼ����X
else
    return;
end
[r,c] = size(X);

%Ȩ����������
bWeights = questdlg('�Ƿ���ָ��Ȩ�����ݣ�','������ʾ','Yes','No','Yes');
if strcmp(bWeights,'Yes')
    dir = get(handles.pathfile,'String');
    weights = xlsread(dir,-1);  %��ȡָ��Ȩ������weights
    [a0,b0] = size(weights);%�ж�ѡȡ��Ȩ�������Ƿ���ȷ
    if (a0 > 1 && a0 ~= r) || (b0 > 1 && b0 ~= c) || (a0 > 1 && b0 > 1)
        msgbox('�ѳ���һά�򲻵���ָ��������ע������ѡȡ��');
        return;
    end
end

%�ο����е�����
bOptArray = questdlg('�Ƿ����òο����У�','������ʾ','Yes','No','Yes'); %������ť
if strcmp(bOptArray,'Yes')
    dir = get(handles.pathfile,'String');
    optArray = xlsread(dir,-1); %��ȡ�ο���������optArray
    [a1,b1] = size(optArray);%�ж�ѡȡ�Ĳο������Ƿ���ȷ
    if (a1 > 1 && a1 ~= r) || (b1 > 1 && b1 ~= c) || (a1 > 1 && b1 > 1)
        msgbox('�ѳ���һά�򲻵���ָ��������ע������ѡȡ��');
        return;
    end
else
    %��������ָ��ǰ���£���ָ������ֵ����ɲο�����
    optArray = max(X,[],1); 
end
 
% ���ݹ淶����������ָ��������ο�����һ��淶����0-1֮��
stdMatrix = zeros(r+1,c);  % ����Ϊ�ο����б�׼��ֵ������Ϊԭʼ���۾����׼��ֵ
optArryAndStat = [optArray;X];
maxOfCols = max(optArryAndStat);    % �����ο��������ڵĸ��е����ֵ
minOfCols = min(optArryAndStat);    % �����ο��������ڵĸ��е���Сֵ
for j=1:c
    for i = 1:r+1
        stdMatrix(i,j) = (optArryAndStat(i,j)-minOfCols(j))./(maxOfCols(j)-minOfCols(j));  % �����׼��ָ��ֵ
    end
end
 
% �������ϵ��
absValue = zeros(r,c);   % �����Բ�ֵ���з���ռ�
R_0 = stdMatrix(1,:);  % ��׼�������Ĳο�����
for i=2:r+1
    absValue(i-1,:) = abs(stdMatrix(i,:)-R_0);  % ���Բ�ֵ���м���
end
minAbsValueOfCols = min(absValue,[],1);         % absValueÿһ�е���Сֵ
maxAbsValueOfCols = max(absValue,[],1);         % absValueÿһ�е����ֵ
minAbsValue = min(minAbsValueOfCols);           % absValue����Сֵ
maxAbsValue = max(maxAbsValueOfCols);           % absValue�����ֵ
defCoeff=0.5;                                 % ���÷ֱ�ϵ��Ϊ0.5
relCoeff = (minAbsValue+defCoeff*maxAbsValue)./(absValue+defCoeff*maxAbsValue);  % ����ϵ������
 
% ���û�и���ָ��Ȩ�أ���������Ȩ����͹�Ȩ��
if strcmp(bWeights,'No')
    R = stdMatrix(2:r,:);    % Ȩ��
    [rows,cols] = size(R);  
    k = 1/log(rows);         % ��k
    f = zeros(rows,cols);    % ��ʼ��fij
    sumBycols = sum(R,1);    % ��������ÿһ��֮��(���Ϊһ��1*cols��������)
    % ����fij
    for i = 1:rows
        for j = 1:cols
            f(i,j) = R(i,j)./sumBycols(1,j);
        end
    end
    lnfij=zeros(rows,cols);  % ��ʼ��lnfij
    % ����lnfij
    for i = 1:rows
        for j = 1:cols
            if f(i,j) == 0
                lnfij(i,j) = 0;
            else
                lnfij(i,j) = log(f(i,j));
            end
        end
    end
    Hj = -k*(sum(f.*lnfij,1)); % ������ֵHj
    weights = (1-Hj)/(cols-sum(Hj));
end

% ���������
P = zeros(r,1);    % �����������з���ռ�
for i = 1:r
    for j = 1:c
        P(i,1) = relCoeff(i,j)*weights(j);  % �����ȼ���
    end
end
%{ 
[sortW,IXW]=sort(weights,'descend');        %Ȩ�ؽ�������IXWȷ����Ӧ��ָ������һ��
indexes={};
for i=1:c
    indexes(i)={strcat('ָ��',num2str(i))}; %����Ϊָ��1��ָ��2��
end
sortIndex=indexes(IXW);                     % �������Ȩ�ض�Ӧ��ָ������
%}
 
%��������table�ؼ������ñ�ע
set(handles.table,'data',P);
notes = '        ����ԭʼ��������������ָ�꣬�������������Ҫ���й淶�������л�ɫ���������㷨�󣬿���ѡ��ָ��Ȩ�غͲο����У����û��ѡ��������ֵ������͹�ָ��Ȩ���Լ�ѡȡ����ָ������ֵ�����Ϊ�ο����С�';
set(handles.text_notes,'string',notes);
axes(handles.draw_axes);
plot(P,'--rs',...
    'LineWidth',2,...
    'MarkerEdgeColor','k',...
    'MarkerFaceColor','g',...
    'MarkerSize',10);
xlim([1 r]);   % ����x�᷶Χ
xlabel('�������','FontSize',10);


% --------------------------------------------------------------------
function ZHFQ_Callback(hObject, eventdata, handles)
% hObject    handle to ZHFQ (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function OIW_Callback(hObject, eventdata, handles)
% hObject    handle to OIW (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%���ñ�ע
notes = '        ���ü����������۹������ڸ���������';
set(handles.text_notes,'string',notes)
system('�����������۹���/�����������۹���.exe')%���ü����������۹���


% --------------------------------------------------------------------
function HW_Callback(hObject, eventdata, handles)
% hObject    handle to HW (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%web help\Ȩ����������.txt
winopen('help\Ȩ����������.txt')


% --------------------------------------------------------------------
function HI_Callback(hObject, eventdata, handles)
% hObject    handle to HI (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%web help\ָ����ϵ��������.txt
winopen('help\ָ����ϵ��������.txt')


% --------------------------------------------------------------------
function HE_ButtonDownFcn(hObject, eventdata, handles)
% hObject    handle to HE (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)



function pathfile_Callback(hObject, eventdata, handles)
% hObject    handle to pathfile (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of pathfile as text
%        str2double(get(hObject,'String')) returns contents of pathfile as a double


% --- Executes during object creation, after setting all properties.
function pathfile_CreateFcn(hObject, eventdata, handles)
% hObject    handle to pathfile (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in edit2.
function edit2_Callback(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of edit2


% --- Executes during object creation, after setting all properties.
function edit2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called


% --- Executes on button press in row.
function row_Callback(hObject, eventdata, handles)
% hObject    handle to row (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hint: get(hObject,'Value') returns toggle state of row
set(handles.row,'value',1);
set(handles.column,'value',0);


% --- Executes on button press in column.
function column_Callback(hObject, eventdata, handles)
% hObject    handle to column (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Hint: get(hObject,'Value') returns toggle state of column
set(handles.row,'value',0);
set(handles.column,'value',1);



function choice_Callback(hObject, eventdata, handles)
% hObject    handle to choice (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of choice as text
%        str2double(get(hObject,'String')) returns contents of choice as a double


% --- Executes during object creation, after setting all properties.
function choice_CreateFcn(hObject, eventdata, handles)
% hObject    handle to choice (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in drawbutton.
function drawbutton_Callback(hObject, eventdata, handles)
% hObject    handle to drawbutton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%�ж����ݱ�״̬
table_data = get(handles.table,'data');
MaxNum = length(table_data);
if 4 == length(class(table_data))
    helpdlg('���ݱ�Ϊ�գ�������ѡ���ʵ��������з�����');
    return;
end

%��ȡ��ť״̬
if get(handles.row,'value')
    option = 1;
elseif get(handles.column,'value')
    option = 2;
else
    helpdlg('��δѡ���');
    return;
end
choice_string = get(handles.choice,'String');
choince_num = str2num(choice_string);
if choince_num > MaxNum
    MaxString = num2str(MaxNum);
    msgbox(strcat('����������ִ�����󳤶�',MaxString));
    return;
end

%������ݻ�ͼ
if 1 == option
    data = table_data(choince_num,:);
else
    data = table_data(:,choince_num);
end
axes(handles.draw_axes)
bar(data,'g','EdgeColor',[0 0 1]);


% --- Executes on button press in cleardrawbutton.
function cleardrawbutton_Callback(hObject, eventdata, handles)
% hObject    handle to cleardrawbutton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
button0 = questdlg('ȷ��Ҫ�����ͼ���������','������ʾ','Yes','No','Yes'); %������ť
if strcmp(button0,'No')
    return;
end
cla reset;


% --- Executes on button press in cleardatabutton.
function cleardatabutton_Callback(hObject, eventdata, handles)
% hObject    handle to cleardatabutton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
button0 = questdlg('ȷ��Ҫ�������������ݣ�','������ʾ','Yes','No','Yes'); %������ť
if strcmp(button0,'No')
    return;
end
cleardata = cell(4,2);
set(handles.table,'data',cleardata);


% --------------------------------------------------------------------
function OEM_Callback(hObject, eventdata, handles)
% hObject    handle to OEM (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%���ñ�ע
notes = '        ���ü����������۹������ڸ���������';
set(handles.text_notes,'string',notes)
system('�����������۹���/�����������۹���.exe')%���ü����������۹���


% --------------------------------------------------------------------
function C2R_Callback(hObject, eventdata, handles)
% hObject    handle to C2R (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
button0 = questdlg('�Ƿ��ȡ������ָ��ԭʼ���ݲ�����CCR��ƷЧ�ʷ�����','������ʾ','Yes','No','Yes'); %������ť
if strcmp(button0,'No')
    return;
end
dir = get(handles.pathfile,'String');
temp_input=xlsread(dir,-1);

button1 = questdlg('�Ƿ��ȡ�����ָ��ԭʼ���ݣ�ѡ��No���˳�������','������ʾ','Yes','No','Yes'); %������ť
if strcmp(button1,'No')
    return;
end
temp_output=xlsread(dir,-1);
[m,n0]=size(temp_input);
[s,n1]=size(temp_output);
if n0 ~= n1 %�ж�ѡȡ���������������ָ�������Ƿ���ȷ
    msgbox('����ȡ���������������ָ��ԭʼ���ݵ�����������Ʒ��������ȣ���ע������ѡȡ��');
	return;
end
n = n0;

mA=m+s;
nA=n+mA+1;
mb=mA;

A=zeros(mA,nA);

A(1:m,1:n)=temp_input;
A(m+1:mA,1:n)=temp_output;
A(1:m,n+1:n+m)=eye(m);
A(m+1:mA,n+1+m:nA-1)=-eye(s);

F=[zeros(n,1);-(1e-6)*ones(mA,1);1];

lb=zeros(nA,1);
b=zeros(mb,1);

outputx=zeros(nA,n);
outputfval=zeros(1,n);

for i=1:n
    A(1:m,nA)=-A(1:m,i);
    b(m+1:mb,1)=A(m+1:mA,i);
    [x,fval]=linprog(F,[],[],A,b,lb);
    outputx(1:nA,i)=x;
    outputfval(1,i)=fval;
end

%����������
%{
outputx(1:n,:) %'lamdaֵ'
outputx(n+1:n+m,:) %'�ɳڱ���ֵ'
outputx(n+m+1:nA-1,:) %'ʣ�����'
outputx(nA,:) %'thetaֵ'
outputfval %'Ŀ�꺯��ֵ'
%}

%��������table�ؼ������ñ�ע
theta = outputx(nA,:);
result = [theta' outputfval'];

set(handles.table,'data',result);
notes = '        �����������ָ��ԭʼ����Ҫ����ͬ��������Ϊָ�꣬��DMU������,C2R��Ҫ��������DMU�����ߵ�Ԫ���Ĺ�ģ�뼼��Ч�ʣ�����C2R�㷨�󣬿��Ը�����������DMU����Ч�ʷ�������һ����������thetaֵ���ڶ�����Ŀ�꺯��ֵ����thetaֵΪ1���ǿ���1����˵������Ч�ʣ�Ŀ�꺯��ֵΪDMUЧ��ָ��ֵ��';
set(handles.text_notes,'string',notes);
axes(handles.draw_axes);
plot(outputfval,'--rs',...
    'LineWidth',2,...
    'MarkerEdgeColor','k',...
    'MarkerFaceColor','g',...
    'MarkerSize',10);
xlabel('�������','FontSize',10);


% --------------------------------------------------------------------
function C2GS2_Callback(hObject, eventdata, handles)
% hObject    handle to C2GS2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
button0 = questdlg('�Ƿ��ȡ������ָ��ԭʼ���ݲ�����CCR��ƷЧ�ʷ�����','������ʾ','Yes','No','Yes'); %������ť
if strcmp(button0,'No')
    return;
end
dir = get(handles.pathfile,'String');
temp_input=xlsread(dir,-1);

button1 = questdlg('�Ƿ��ȡ�����ָ��ԭʼ���ݣ�ѡ��No���˳�������','������ʾ','Yes','No','Yes'); %������ť
if strcmp(button1,'No')
    return;
end
temp_output=xlsread(dir,-1);
[m,n0]=size(temp_input);
[s,n1]=size(temp_output);
if n0 ~= n1 %�ж�ѡȡ���������������ָ�������Ƿ���ȷ
    msgbox('����ȡ���������������ָ��ԭʼ���ݵ�����������Ʒ��������ȣ���ע������ѡȡ��');
	return;
end
n = n0;

mA=m+s;
nA=n+mA+1;
mb=mA;

A=zeros(mA,nA);

A(1:m,1:n)=temp_input;
A(m+1:mA,1:n)=temp_output;
A(1:m,n+1:n+m)=eye(m);
A(m+1:mA,n+1+m:nA-1)=-eye(s);

F=[zeros(n,1);-(1e-6)*ones(mA,1);1];

lb=zeros(nA,1);
b=zeros(mb,1);

outputx=zeros(nA,n);
outputfval=zeros(1,n);

for i=1:n
    A(1:m,nA)=-A(1:m,i);
    A(mA+1,:)=[ones(1,n),zeros(1,mA+1)];
    b(m+1:mb,1)=A(m+1:mA,i);
    b(mA+1,1)=1;
    [x,fval]=linprog(F,[],[],A,b,lb);
    outputx(1:nA,i)=x;
    outputfval(1,i)=fval;
end

%����������
%{
outputx(1:n,:) %'lamdaֵ'
outputx(n+1:n+m,:) %'�ɳڱ���ֵ'
outputx(n+m+1:nA-1,:) %'ʣ�����'
outputx(nA,:) %'thetaֵ'
outputfval %'Ŀ�꺯��ֵ'
%}

%��������table�ؼ������ñ�ע
theta = outputx(nA,:);
result = [theta' outputfval'];

set(handles.table,'data',result);
notes = '        �����������ָ��ԭʼ����Ҫ����ͬ��������Ϊָ�꣬��Ϊ������,C2RS2��Ҫ��������DMU�ļ�����Ч�ԣ�����C2GS2�㷨�󣬿�����������DMU���м�����Ч�Է�������һ����������thetaֵ���ڶ�����Ŀ�꺯��ֵ����thetaֵΪ1���ǿ���1����˵�����м�����Ч�ԣ��꺯��ֵΪ��DMU������Ч��ֵ��';
set(handles.text_notes,'string',notes);
axes(handles.draw_axes);
plot(outputfval,'--rs',...
    'LineWidth',2,...
    'MarkerEdgeColor','k',...
    'MarkerFaceColor','g',...
    'MarkerSize',10);
xlabel('�������','FontSize',10);

% --------------------------------------------------------------------
function Reform_C2R_Callback(hObject, eventdata, handles)
% hObject    handle to Reform_C2R (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
button0 = questdlg('�Ƿ��ȡ������ָ��ԭʼ���ݲ�����CCR��ƷЧ�ʷ�����','������ʾ','Yes','No','Yes'); %������ť
if strcmp(button0,'No')
    return;
end
dir = get(handles.pathfile,'String');
temp_input=xlsread(dir,-1);

button1 = questdlg('�Ƿ��ȡ�����ָ��ԭʼ���ݣ�ѡ��No���˳�������','������ʾ','Yes','No','Yes'); %������ť
if strcmp(button1,'No')
    return;
end
temp_output=xlsread(dir,-1);
[m,n0]=size(temp_input);
[s,n1]=size(temp_output);
if n0 ~= n1 %�ж�ѡȡ���������������ָ�������Ƿ���ȷ
    msgbox('����ȡ���������������ָ��ԭʼ���ݵ�����������Ʒ��������ȣ���ע������ѡȡ��');
	return;
end
n = n0;

mA=m+s;
nA=n+mA+1;
mb=mA;

A=zeros(mA,nA);

A(1:m,1:n)=temp_input;
A(m+1:mA,1:n)=temp_output;
A(1:m,n+1:n+m)=eye(m);
A(m+1:mA,n+1+m:nA-1)=-eye(s);

F=[zeros(n,1);-(1e-6)*ones(mA,1);1];

lb=zeros(nA-1,1);
b=zeros(mb,1);

outputx=zeros(nA-1,n);
outputfval=zeros(1,n);

for i=1:n
    A(1:m,nA)=-A(1:m,i);
    b(m+1:mb,1)=A(m+1:mA,i);
    AA=A;
    AA(:,i)=[];
    FF=F;
    FF(i)=[];
    [x,fval]=linprog(FF,[],[],AA,b,lb);
    outputx(1:nA-1,i)=x;
    outputfval(1,i)=fval;
end
%����������
%{
outputx(1:n,:) %'lamdaֵ'
outputx(n+1:n+m,:) %'�ɳڱ���ֵ'
outputx(n+m+1:nA-1,:) %'ʣ�����'
outputxoutputx(nA-1,:) %'thetaֵ'
outputfval %'Ŀ�꺯��ֵ'
%}

%��������table�ؼ������ñ�ע
theta = outputx(nA-1,:);
result = [theta' outputfval'];

set(handles.table,'data',result);
notes = '        �����������ָ��ԭʼ����Ҫ����ͬ��������Ϊָ�꣬��Ϊ������,�Ľ�C2R�ܶ�����DMUЧ�ʽ��г���������������иĽ�C2R�㷨�󣬿�����������DMUЧ�ʽ��з�������һ����������thetaֵ���ڶ�����Ŀ�꺯��ֵ����theta����1������Ч������ֵ���������Ŀ�꺯��ֵΪDMUЧ��ָ��ֵ��';
set(handles.text_notes,'string',notes);
axes(handles.draw_axes);
plot(outputfval,'--rs',...
    'LineWidth',2,...
    'MarkerEdgeColor','k',...
    'MarkerFaceColor','g',...
    'MarkerSize',10);
xlabel('�������','FontSize',10);


% --- Executes on button press in datafile.
function datafile_Callback(hObject, eventdata, handles)
% hObject    handle to datafile (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[name path] = uigetfile({'*.xls;*.xlsx','Excel File(*.xls;*.xlsx)'},'File Selector');
pathname = strcat(path,name);
set(handles.pathfile,'string',pathname);
