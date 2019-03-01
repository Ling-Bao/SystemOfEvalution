clear;
clc;
X=xlsread('original_data.xls',-1);
[m,n]=size(X);

%���Ƶ�һ��ͼ��
subplot(121);
boxplot(X,0,'+',1);

%���������ı�׼��
stdr=std(X,0,1);

%�����������еľ�ֵ
meanc=mean(X);

%��׼��ԭʼ����
sr=(X-meanc(ones(m,1),:))./stdr(ones(m,1),:)

%������ؾ���
R=sr'*sr/(m-1)

%�������ɷַ���
[pcs,newdata,variances,t2]=princomp(sr)
%�������
percent_explained=100*variances/sum(variances)

%���Ƶڶ���ͼ��
subplot(122);
pareto(percent_explained);%������ͼ
xlabel('���ɷ�');
ylabel('����ռ�ı���');

%�����result.xls
xlswrite('result.xls','ԭʼ���ݱ�׼������',1,'A1');
xlswrite('result.xls',sr,1,'A2');

k1=m+3;
string_1=['A',num2str(k1)];
xlswrite('result.xls','������ؾ���',1,string_1);
string_2=['A',num2str(m+4)];
xlswrite('result.xls',R,1,string_2);

k2=m+n+5;
string_3=['A',num2str(k2)];
xlswrite('result.xls','��λ����������',1,string_3);
string_4=['A',num2str(m+n+6)];
xlswrite('result.xls',pcs,1,string_4);

k3=m+n+n+7;
string_5=['A',num2str(k3)];
xlswrite('result.xls','���ɷֵ÷�',1,string_5);
string_6=['A',num2str(m+n+n+8)];
xlswrite('result.xls',newdata,1,string_6);

k4=m+n+n+m+9;
string_7=['A',num2str(k4)];
xlswrite('result.xls','����ֵ',1,string_7);
string_8=['A',num2str(m+n+n+m+10)];
xlswrite('result.xls',variances,1,string_8);

k5=m+n+n+m+n+11;
string_9=['A',num2str(k5)];
xlswrite('result.xls','ͳ����Hotelling T2',1,string_9);
string_10=['A',num2str(m+n+n+m+n+12)];
xlswrite('result.xls',t2,1,string_10);

k6=m+n+n+m+n+m+13;
string_11=['A',num2str(k6)];
xlswrite('result.xls','�������',1,string_11);
string_12=['A',num2str(m+n+n+m+n+m+14)];
xlswrite('result.xls',percent_explained,1,string_12);