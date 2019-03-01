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
button0 = questdlg('是否获取原始数据并进行相关性分析？','操作提示','Yes','No','Yes'); %两个按钮
if strcmp(button0,'No')
    return;
end
dir = get(handles.pathfile,'String');
A = xlsread(dir,-1);
R = corrcoef(A);
set(handles.table,'data',R);
notes = '    通过设定的相关系数阈值以及相关系数矩阵可以对各指标进行相关性分析，从而粗略地统计出指标间的相关性。';
set(handles.text_notes,'string',notes)


% --------------------------------------------------------------------
function PCA_Callback(hObject, eventdata, handles)
% hObject    handle to PCA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
button0 = questdlg('是否获取原始数据并进行主成分分析分析？','操作提示','Yes','No','Yes'); %两个按钮
if strcmp(button0,'No')
    return;
end
dir = get(handles.pathfile,'String');
X = xlsread(dir,-1);%获取数据
[m,n] = size(X);

%计算样本的标准差和均值并求
stdr = std(X,0,1);
meanc = mean(X);
sr = (X-meanc(ones(m,1),:))./stdr(ones(m,1),:);

%进行主成分分析并求方差贡献率
[pcs,newdata,variances,t2] = princomp(sr);
%其中pcs为特征向量，newdata主成分得分，variances为特征值，t2为统计量Hotelling
%这里只用到newdata和variances
percent_explained = 100*variances/sum(variances);

%求策略分析矩阵EW
a = X'*newdata;
b1 = sum(X.*X);
b2 = sum(newdata.*newdata);
b1 = b1.^(0.5);
b2 = b2.^(0.5);
b = b1*b2';
EW = a./b;
Result = sum(EW,2);

%输出结果到table控件并设置备注
set(handles.table,'data',Result);
notes = '        运行主成分分析算法后，可以在分析结果表中得到各指标对所有主成分影响总和的评判值，如果评判值大于50%，则说明该指标对主成分影响较大；同时，程序还会在绘图分析中画出特征值贡献率的饼状图。';
set(handles.text_notes,'string',notes)

%将特征值所占比例画成饼图显示到axes控件
axes(handles.draw_axes)
colormap(cool); %通过colormap转换颜色
len = length(percent_explained);
pie3(percent_explained);

% --------------------------------------------------------------------
function FA_Callback(hObject, eventdata, handles)
% hObject    handle to FA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
button0 = questdlg('是否获取原始数据并进行因子分析？','操作提示','Yes','No','Yes'); %两个按钮
if strcmp(button0,'No')
    return;
end
dir = get(handles.pathfile,'String');
X = xlsread(dir,-1);%获取数据
[m,n]=size(X);

%设置初始参数
thelong=0.000001;
Max=inf;
delta=inf;

%相关系数矩阵
sr = zscore(X);
R = sr'*sr/(m-1);

%进行主成分分析
[pcs,newdata,variances,t2] = princomp(sr);

%特征值占总体百分数
percent_explained = 100*variances/sum(variances);

%特征值的累计百分数
leiji = percent_explained./sum(percent_explained);
for i = 1:n
    lj_percentage(i) = sum(leiji(1:i));
end
leiji_percentage = lj_percentage';

%将特征值所占比例画成饼图显示到axes控件
axes(handles.draw_axes)
colormap(cool); %通过colormap转换颜色
len = length(percent_explained);
pie3(percent_explained);

%下面开始求因子载荷矩阵
for j = 1:n
    AA(:,j) = sqrt(variances(j,1))*pcs(:,j);
end
for i = 1:n
    if(lj_percentage(i) >= 0.85)
        k = i;
        break;
    end
end
A = AA(:,1:k); %因子载荷矩阵

%求h的平方（共同度）、d的平方（剩余方差）和g的平方（方差贡献）
BB = power(A,2);
for j = 1:n
    hhh(j) = sum(BB(j,:));
end
hh = hhh';
h = sqrt(hh);
dd = 1-h;
gg = sum(BB);

%下面开始求方差最大正交旋转矩阵
%赋值给theta
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

%下面开始求正交因子得分矩阵
for i = 1:m
    XX = zscore(X);
    XX = XX(i,:);
    F = B'*inv(R);
    FF(i,:) = (F*XX')';
end
%输出结果到table控件并设置备注
set(handles.table,'data',FF);
notes = '        运行因子分析算法后，可以在分析结果表中得到正交因子得分矩阵，一般来说，每个因子只有少数几个指标的因子载荷较大，因此，可以根据此得分矩阵将指标按高载荷进行分类并结合专业知识对各因子命名；同时，程序还会在绘图分析中画出特征值贡献率的饼状图。';
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
button = questdlg('是否对指标进行专家评价并打开原始数据表？','操作提示','Yes','No','Yes'); %两个按钮
if button == 'Yes'
    dir = get(handles.pathfile,'String');
    X = xlsread(dir,-1);%获取数据
end
[a0,b0] = size(X);
if a0 > 1 && b0 > 1
    msgbox('指标数据已超过一维，请注意数据的选取！');
    return;
end

sumX = sum(X);% 归一化
oneX = X./sumX;
set(handles.table,'data',oneX');
notes = '        专家评价功能为专家提供一个调用原始数据并对各指标进行评分的交互界面；操作时请将各指标按照百分制进行打分，完成打分后，选中各指标最终评分结果并点击确定，之后将返回用户界面。';
set(handles.text_notes,'string',notes)
axes(handles.draw_axes);
plot(oneX,'--rs',...
    'LineWidth',2,...
    'MarkerEdgeColor','k',...
    'MarkerFaceColor','g',...
    'MarkerSize',10);
if 5 <= length(oneX)
    ylim([min(oneX)+0.05*min(oneX) max(oneX)+0.05*max(oneX)]);   % 设置y轴范围
end
xlabel('指标序号','FontSize',10);

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
%web help\关于平台.txt
winopen('help\关于平台.txt')


% --------------------------------------------------------------------
function FCE_Callback(hObject, eventdata, handles)
% hObject    handle to FCE (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
button0 = questdlg('是否获取原始数据并进行模糊综合评判？','操作提示','Yes','No','Yes'); %两个按钮
if strcmp(button0,'No')
    return;
end
 %读入数据、
dir = get(handles.pathfile,'String');
data=xlsread(dir,-1);
[n,m]=size(data);%n数据条数，m指标个数

button1 = questdlg('请选择指标权重向量，选择No则退出操作！','操作提示','Yes','No','Yes'); %两个按钮
if strcmp(button1,'No')
    return;
end
weight=xlsread(dir,-1);
if m ~= length(weight)
    warndlg('指标权重数目与原始数据指标数目不相等！');
    return;
end

button1 = questdlg('请选择指等级划分数据（此处务必分为三个等级点，即3*N矩阵），选择No则退出操作！','操作提示','Yes','No','Yes'); %两个按钮
if strcmp(button1,'No')
    return;
end
dengji=xlsread(dir,-1);
[n0,m0] = size(dengji);
if 3 ~= n0 && m0 ~= m
    warndlg('不满足等级划分矩阵或指标数目与原始数据指标数目不等！');
    return;
end

%数据标准化
mean_d=mean(data);
for j=1:m
    data(:,j)=data(:,j)/mean_d(j);
end

%计算隶属函数，以0,1/3,2/3和1为四个等级凝聚中心
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
%综合评分
zp=lsd*weight';
result = [lsd zp];
set(handles.table,'data',result);
notes = '        模糊综合评判需要提供原始数据，指标权重向量以及等级点矩阵；运行模糊综合评判算法后，以0,1/3,2/3和1为四个等级凝聚中心并结合等级点矩阵计算隶属度函数，最后便可以计算出各样本综合得分；最后，输出隶属度矩阵（最后一列为各样本得分向量）及样本得分向量图像。';
set(handles.text_notes,'string',notes)
axes(handles.draw_axes);
plot(zp,'--rs',...
    'LineWidth',2,...
    'MarkerEdgeColor','k',...
    'MarkerFaceColor','g',...
    'MarkerSize',10);
if 5 <= length(zp)
    ylim([min(zp)+0.05*min(zp) max(zp)+0.05*max(zp)]);   % 设置y轴范围
end
xlabel('样本序号','FontSize',10);



% --------------------------------------------------------------------
function HFCE_Callback(hObject, eventdata, handles)
% hObject    handle to HFCE (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

button = questdlg('请获取计算精度e与最大迭代次数Max，是否继续进行？','操作提示','Yes','No','Yes'); %两个按钮
if strcmp(button,'No')
    return;
end
dir = get(handles.pathfile,'String');
EMax = xlsread(dir,-1);%获取数据
[a0,a1] = size(EMax);
if (a0 == 1 && a1 == 2) || (a0 == 2 && a1 == 1)
    
else
    msgbox('所选取的精度和迭代次数数据不满足2元素的一维数组，请重新选择！');
    return;
end
E = EMax(1);
Max = EMax(2);
%输入优先关系矩阵 
F = xlsread(dir,-1);
[b0,b1] = size(F)
if b0 ~= b1
    msgbox('所选取的数据不满足优先关系矩阵（方阵），请重新选择！');
    return;
end

%计算模糊一致矩阵 
N=size(F); 
r=sum(F'); 
for i=1:N(1) 
    for j=1:N(2) 
        R(i,j)=(r(i)-r(j))/(2*N(1))+0.5; 
    end 
end 
E=R./R'; 
% 计算初始向量 ---------- 
% W=sum(R')./sum(sum(R)); % 和行归一法 
%--------------------------------------------------------- 
for i=1:N(1) 
    S(i)=R(i,1); 
    for j=2:N(2) 
        S(i)=S(i)*R(i,j); 
    end 
end 
S=S.^(1/N(1)); 
W = S./sum(S)%方根法
% a=input('参数a=?'); 
%W=sum(R')/(N(1)*a)-1/(2*a)+1/N(1); %排序法
V(:,1)=W'/max(abs(W));% 利用幂法计算排序向量
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
notes = '        需保证计算精度与最大迭代次数按次序连接选取、优先关系矩阵是方阵与并满足对称数据和为1（不是必须），运行层次模糊算法后，将得到该层指标的权重（第一列又方根法所得，第二列由幂法迭代而得），除此之外将显示方根法求得指标权重的图像。利用该算法并逐层进行权值确定，最终可以确定所有指标的权重值!';
set(handles.text_notes,'string',notes)
axes(handles.draw_axes);
plot(W,'--rs',...
    'LineWidth',2,...
    'MarkerEdgeColor','k',...
    'MarkerFaceColor','g',...
    'MarkerSize',10);
if 5 <= length(W)
    ylim([min(W)+0.05*min(W) max(W)+0.05*max(W)]);   % 设置y轴范围
end
xlabel('指标序号--方根法','FontSize',10);


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
%web help\评价帮助.txt
winopen('help\评价帮助.txt')


% --------------------------------------------------------------------
function AHP_Callback(hObject, eventdata, handles)
% hObject    handle to AHP (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
button0 = questdlg('是否获取原始数据并进行层次分析？','操作提示','Yes','No','Yes'); %两个按钮
if strcmp(button0,'No')
    return;
end
dir = get(handles.pathfile,'String');
X = xlsread(dir,-1);%获取数据

[b0,b1] = size(X);
if b0 ~= b1
    msgbox('所选取的数据不满足优先关系矩阵（方阵），请重新选择！');
    return;
end
                                     %因素对比矩阵X，只需要改变矩阵X
[m,n] = size(X);                     %获取指标个数
if n >15
    msgbox('指标最大个数不能超过15！');
    return;
end
                                     %不同维度对应的RI值
RI = [0 0 0.58 0.90 1.12 1.24 1.32 1.41 1.45 1.49 1.51 1.54 1.56 1.58 1.59];
R = rank(X);                         %求判断矩阵的秩
[V,D] = eig(X);                      %求判断矩阵的特征值和特征向量，V特征值，D特征向量；
tz = max(D);
B = max(tz);                         %最大特征值
[row, col] = find(D == B);           %最大特征值所在位置
C = V(:,col);                        %对应特征向量
CI = (B-n)/(n-1);                    %计算一致性检验指标CI
CR = CI/RI(1,n);   
if CR < 0.10
    stringCI = num2str(CI);
    stringCR = num2str(CR);
    str = strcat('  判断矩阵X通过一致性检验，','CR=',stringCI,'，CI=',stringCR,'  ');
    msgbox(str);
    Q = zeros(n,1);
    for i = 1:n
        Q(i,1) = C(i,1)/sum(C(:,1)); %特征向量标准化
    end
    %Q                               %输出权重向量
    %输出结果到table控件并设置备注
    set(handles.table,'data',Q);
    notes = '        输入数据矩阵为判断矩阵；运行层次分析算法后，可以在分析结果表中得到各指标的权重；值得注意的是各层的指标数目不要超过15，原因是不同维度对应的RI值最大为15。';
    set(handles.text_notes,'string',notes)
    axes(handles.draw_axes);
    plot(Q,'--rs',...
        'LineWidth',2,...
        'MarkerEdgeColor','k',...
        'MarkerFaceColor','g',...
        'MarkerSize',10);
    if 5 <= length(Q)
        ylim([min(Q)+0.05*min(Q) max(Q)+0.05*max(Q)]);   % 设置y轴范围
    end
    xlabel('指标序号','FontSize',10);
else
    msgbox('对比矩阵A未通过一致性检验，需对对比矩阵A重新构造');
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
%假设原始数据全为正向指标，即假设全部指标值越大越好
bData = questdlg('原始数据是否满足正向型指标？','操作提示','Yes','No','Yes');
if bData == 'Yes'
    dir = get(handles.pathfile,'String');
    X = xlsread(dir,-1);        %获取原始数据X
else
    return;
end
[r,c] = size(X);

%权重数据设置
bWeights = questdlg('是否赋予指标权重数据？','操作提示','Yes','No','Yes');
if strcmp(bWeights,'Yes')
    dir = get(handles.pathfile,'String');
    weights = xlsread(dir,-1);  %获取指标权重数据weights
    [a0,b0] = size(weights);%判断选取的权重数据是否正确
    if (a0 > 1 && a0 ~= r) || (b0 > 1 && b0 ~= c) || (a0 > 1 && b0 > 1)
        msgbox('已超过一维或不等于指标数，请注意数据选取！');
        return;
    end
end

%参考序列的设置
bOptArray = questdlg('是否设置参考序列？','操作提示','Yes','No','Yes'); %两个按钮
if strcmp(bOptArray,'Yes')
    dir = get(handles.pathfile,'String');
    optArray = xlsread(dir,-1); %获取参考数列数据optArray
    [a1,b1] = size(optArray);%判断选取的参考序列是否正确
    if (a1 > 1 && a1 ~= r) || (b1 > 1 && b1 ~= c) || (a1 > 1 && b1 > 1)
        msgbox('已超过一维或不等于指标数，请注意数据选取！');
        return;
    end
else
    %在正向型指标前提下，各指标的最大值可组成参考数列
    optArray = max(X,[],1); 
end
 
% 数据规范化处理，将各指标数据与参考数列一起规范化到0-1之间
stdMatrix = zeros(r+1,c);  % 首行为参考数列标准化值，其它为原始评价矩阵标准化值
optArryAndStat = [optArray;X];
maxOfCols = max(optArryAndStat);    % 包括参考数列在内的各列的最大值
minOfCols = min(optArryAndStat);    % 包括参考数列在内的各列的最小值
for j=1:c
    for i = 1:r+1
        stdMatrix(i,j) = (optArryAndStat(i,j)-minOfCols(j))./(maxOfCols(j)-minOfCols(j));  % 计算标准化指标值
    end
end
 
% 计算关联系数
absValue = zeros(r,c);   % 给绝对差值序列分配空间
R_0 = stdMatrix(1,:);  % 标准化处理后的参考数列
for i=2:r+1
    absValue(i-1,:) = abs(stdMatrix(i,:)-R_0);  % 绝对差值序列计算
end
minAbsValueOfCols = min(absValue,[],1);         % absValue每一列的最小值
maxAbsValueOfCols = max(absValue,[],1);         % absValue每一列的最大值
minAbsValue = min(minAbsValueOfCols);           % absValue的最小值
maxAbsValue = max(maxAbsValueOfCols);           % absValue的最大值
defCoeff=0.5;                                 % 设置分辨系数为0.5
relCoeff = (minAbsValue+defCoeff*maxAbsValue)./(absValue+defCoeff*maxAbsValue);  % 关联系数计算
 
% 如果没有给定指标权重，则利用熵权法求客观权重
if strcmp(bWeights,'No')
    R = stdMatrix(2:r,:);    % 权重
    [rows,cols] = size(R);  
    k = 1/log(rows);         % 求k
    f = zeros(rows,cols);    % 初始化fij
    sumBycols = sum(R,1);    % 输入矩阵的每一列之和(结果为一个1*cols的行向量)
    % 计算fij
    for i = 1:rows
        for j = 1:cols
            f(i,j) = R(i,j)./sumBycols(1,j);
        end
    end
    lnfij=zeros(rows,cols);  % 初始化lnfij
    % 计算lnfij
    for i = 1:rows
        for j = 1:cols
            if f(i,j) == 0
                lnfij(i,j) = 0;
            else
                lnfij(i,j) = log(f(i,j));
            end
        end
    end
    Hj = -k*(sum(f.*lnfij,1)); % 计算熵值Hj
    weights = (1-Hj)/(cols-sum(Hj));
end

% 计算关联度
P = zeros(r,1);    % 给关联度序列分配空间
for i = 1:r
    for j = 1:c
        P(i,1) = relCoeff(i,j)*weights(j);  % 关联度计算
    end
end
%{ 
[sortW,IXW]=sort(weights,'descend');        %权重降序排序，IXW确保对应的指标名称一致
indexes={};
for i=1:c
    indexes(i)={strcat('指标',num2str(i))}; %名称为指标1、指标2…
end
sortIndex=indexes(IXW);                     % 排序后与权重对应的指标名称
%}
 
%输出结果到table控件并设置备注
set(handles.table,'data',P);
notes = '        假设原始数据满足正向型指标，如果不满足则需要进行规范化；运行灰色关联分析算法后，可以选择指标权重和参考序列，如果没有选择将利用熵值法计算客观指标权重以及选取各个指标的最大值组合作为参考序列。';
set(handles.text_notes,'string',notes);
axes(handles.draw_axes);
plot(P,'--rs',...
    'LineWidth',2,...
    'MarkerEdgeColor','k',...
    'MarkerFaceColor','g',...
    'MarkerSize',10);
xlim([1 r]);   % 设置x轴范围
xlabel('样本序号','FontSize',10);


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
%设置备注
notes = '        调用技术经济评价工具用于辅助分析。';
set(handles.text_notes,'string',notes)
system('技术经济评价工具/技术经济评价工具.exe')%调用技术经济评价工具


% --------------------------------------------------------------------
function HW_Callback(hObject, eventdata, handles)
% hObject    handle to HW (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%web help\权重量化帮助.txt
winopen('help\权重量化帮助.txt')


% --------------------------------------------------------------------
function HI_Callback(hObject, eventdata, handles)
% hObject    handle to HI (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%web help\指标体系构建帮助.txt
winopen('help\指标体系构建帮助.txt')


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

%判断数据表状态
table_data = get(handles.table,'data');
MaxNum = length(table_data);
if 4 == length(class(table_data))
    helpdlg('数据表为空，请您先选择适当方法进行分析！');
    return;
end

%获取按钮状态
if get(handles.row,'value')
    option = 1;
elseif get(handles.column,'value')
    option = 2;
else
    helpdlg('您未选择项！');
    return;
end
choice_string = get(handles.choice,'String');
choince_num = str2num(choice_string);
if choince_num > MaxNum
    MaxString = num2str(MaxNum);
    msgbox(strcat('您输入的数字大于最大长度',MaxString));
    return;
end

%结果数据绘图
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
button0 = questdlg('确定要清除绘图分析结果？','操作提示','Yes','No','Yes'); %两个按钮
if strcmp(button0,'No')
    return;
end
cla reset;


% --- Executes on button press in cleardatabutton.
function cleardatabutton_Callback(hObject, eventdata, handles)
% hObject    handle to cleardatabutton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
button0 = questdlg('确定要清除分析结果数据？','操作提示','Yes','No','Yes'); %两个按钮
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
%设置备注
notes = '        调用技术经济评价工具用于辅助分析。';
set(handles.text_notes,'string',notes)
system('技术经济评价工具/技术经济评价工具.exe')%调用技术经济评价工具


% --------------------------------------------------------------------
function C2R_Callback(hObject, eventdata, handles)
% hObject    handle to C2R (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
button0 = questdlg('是否获取输入型指标原始数据并进行CCR样品效率分析？','操作提示','Yes','No','Yes'); %两个按钮
if strcmp(button0,'No')
    return;
end
dir = get(handles.pathfile,'String');
temp_input=xlsread(dir,-1);

button1 = questdlg('是否获取输出型指标原始数据，选择No将退出操作？','操作提示','Yes','No','Yes'); %两个按钮
if strcmp(button1,'No')
    return;
end
temp_output=xlsread(dir,-1);
[m,n0]=size(temp_input);
[s,n1]=size(temp_output);
if n0 ~= n1 %判断选取的输入型与输出型指标数据是否正确
    msgbox('所获取的输入型与输出型指标原始数据的列数（或样品数）不相等，请注意数据选取！');
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

%输出结果剖析
%{
outputx(1:n,:) %'lamda值'
outputx(n+1:n+m,:) %'松弛变量值'
outputx(n+m+1:nA-1,:) %'剩余变量'
outputx(nA,:) %'theta值'
outputfval %'目标函数值'
%}

%输出结果到table控件并设置备注
theta = outputx(nA,:);
result = [theta' outputfval'];

set(handles.table,'data',result);
notes = '        输入与输出型指标原始数据要有相同列数（行为指标，列DMU样本）,C2R主要用于评价DMU（决策单元）的规模与技术效率；运行C2R算法后，可以根据输出结果对DMU进行效率分析；第一列输出结果是theta值，第二列是目标函数值；若theta值为1或是靠近1，则说具有明效率；目标函数值为DMU效率指标值。';
set(handles.text_notes,'string',notes);
axes(handles.draw_axes);
plot(outputfval,'--rs',...
    'LineWidth',2,...
    'MarkerEdgeColor','k',...
    'MarkerFaceColor','g',...
    'MarkerSize',10);
xlabel('样本序号','FontSize',10);


% --------------------------------------------------------------------
function C2GS2_Callback(hObject, eventdata, handles)
% hObject    handle to C2GS2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
button0 = questdlg('是否获取输入型指标原始数据并进行CCR样品效率分析？','操作提示','Yes','No','Yes'); %两个按钮
if strcmp(button0,'No')
    return;
end
dir = get(handles.pathfile,'String');
temp_input=xlsread(dir,-1);

button1 = questdlg('是否获取输出型指标原始数据，选择No将退出操作？','操作提示','Yes','No','Yes'); %两个按钮
if strcmp(button1,'No')
    return;
end
temp_output=xlsread(dir,-1);
[m,n0]=size(temp_input);
[s,n1]=size(temp_output);
if n0 ~= n1 %判断选取的输入型与输出型指标数据是否正确
    msgbox('所获取的输入型与输出型指标原始数据的列数（或样品数）不相等，请注意数据选取！');
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

%输出结果剖析
%{
outputx(1:n,:) %'lamda值'
outputx(n+1:n+m,:) %'松弛变量值'
outputx(n+m+1:nA-1,:) %'剩余变量'
outputx(nA,:) %'theta值'
outputfval %'目标函数值'
%}

%输出结果到table控件并设置备注
theta = outputx(nA,:);
result = [theta' outputfval'];

set(handles.table,'data',result);
notes = '        输入与输出型指标原始数据要有相同列数（行为指标，列为样本）,C2RS2主要用于评价DMU的技术有效性；运行C2GS2算法后，可由输出结果对DMU进行技术有效性分析；第一列输出结果是theta值，第二列是目标函数值；若theta值为1或是靠近1，则说明具有技术有效性；标函数值为样DMU技术有效性值。';
set(handles.text_notes,'string',notes);
axes(handles.draw_axes);
plot(outputfval,'--rs',...
    'LineWidth',2,...
    'MarkerEdgeColor','k',...
    'MarkerFaceColor','g',...
    'MarkerSize',10);
xlabel('样本序号','FontSize',10);

% --------------------------------------------------------------------
function Reform_C2R_Callback(hObject, eventdata, handles)
% hObject    handle to Reform_C2R (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
button0 = questdlg('是否获取输入型指标原始数据并进行CCR样品效率分析？','操作提示','Yes','No','Yes'); %两个按钮
if strcmp(button0,'No')
    return;
end
dir = get(handles.pathfile,'String');
temp_input=xlsread(dir,-1);

button1 = questdlg('是否获取输出型指标原始数据，选择No将退出操作？','操作提示','Yes','No','Yes'); %两个按钮
if strcmp(button1,'No')
    return;
end
temp_output=xlsread(dir,-1);
[m,n0]=size(temp_input);
[s,n1]=size(temp_output);
if n0 ~= n1 %判断选取的输入型与输出型指标数据是否正确
    msgbox('所获取的输入型与输出型指标原始数据的列数（或样品数）不相等，请注意数据选取！');
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
%输出结果剖析
%{
outputx(1:n,:) %'lamda值'
outputx(n+1:n+m,:) %'松弛变量值'
outputx(n+m+1:nA-1,:) %'剩余变量'
outputxoutputx(nA-1,:) %'theta值'
outputfval %'目标函数值'
%}

%输出结果到table控件并设置备注
theta = outputx(nA-1,:);
result = [theta' outputfval'];

set(handles.table,'data',result);
notes = '        输入与输出型指标原始数据要有相同列数（行为指标，列为样本）,改进C2R能对所有DMU效率进行充分评价与排序；运行改进C2R算法后，可由输出结果对DMU效率进行分析；第一列输出结果是theta值，第二列是目标函数值；若theta大于1，则有效率且随值增大而增大；目标函数值为DMU效率指标值。';
set(handles.text_notes,'string',notes);
axes(handles.draw_axes);
plot(outputfval,'--rs',...
    'LineWidth',2,...
    'MarkerEdgeColor','k',...
    'MarkerFaceColor','g',...
    'MarkerSize',10);
xlabel('样本序号','FontSize',10);


% --- Executes on button press in datafile.
function datafile_Callback(hObject, eventdata, handles)
% hObject    handle to datafile (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
[name path] = uigetfile({'*.xls;*.xlsx','Excel File(*.xls;*.xlsx)'},'File Selector');
pathname = strcat(path,name);
set(handles.pathfile,'string',pathname);
