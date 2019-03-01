clear;
clc;
X=xlsread('original_data.xls',-1);
[m,n]=size(X);

%绘制第一个图形
subplot(121);
boxplot(X,0,'+',1);

%计算样本的标准差
stdr=std(X,0,1);

%计算样本各列的均值
meanc=mean(X);

%标准化原始数据
sr=(X-meanc(ones(m,1),:))./stdr(ones(m,1),:)

%样本相关矩阵
R=sr'*sr/(m-1)

%进行主成分分析
[pcs,newdata,variances,t2]=princomp(sr)
%方差贡献率
percent_explained=100*variances/sum(variances)

%绘制第二个图形
subplot(122);
pareto(percent_explained);%帕累托图
xlabel('主成分');
ylabel('方差占的比重');

%输出到result.xls
xlswrite('result.xls','原始数据标准化矩阵',1,'A1');
xlswrite('result.xls',sr,1,'A2');

k1=m+3;
string_1=['A',num2str(k1)];
xlswrite('result.xls','样本相关矩阵',1,string_1);
string_2=['A',num2str(m+4)];
xlswrite('result.xls',R,1,string_2);

k2=m+n+5;
string_3=['A',num2str(k2)];
xlswrite('result.xls','单位化特征向量',1,string_3);
string_4=['A',num2str(m+n+6)];
xlswrite('result.xls',pcs,1,string_4);

k3=m+n+n+7;
string_5=['A',num2str(k3)];
xlswrite('result.xls','主成分得分',1,string_5);
string_6=['A',num2str(m+n+n+8)];
xlswrite('result.xls',newdata,1,string_6);

k4=m+n+n+m+9;
string_7=['A',num2str(k4)];
xlswrite('result.xls','特征值',1,string_7);
string_8=['A',num2str(m+n+n+m+10)];
xlswrite('result.xls',variances,1,string_8);

k5=m+n+n+m+n+11;
string_9=['A',num2str(k5)];
xlswrite('result.xls','统计量Hotelling T2',1,string_9);
string_10=['A',num2str(m+n+n+m+n+12)];
xlswrite('result.xls',t2,1,string_10);

k6=m+n+n+m+n+m+13;
string_11=['A',num2str(k6)];
xlswrite('result.xls','方差贡献率',1,string_11);
string_12=['A',num2str(m+n+n+m+n+m+14)];
xlswrite('result.xls',percent_explained,1,string_12);