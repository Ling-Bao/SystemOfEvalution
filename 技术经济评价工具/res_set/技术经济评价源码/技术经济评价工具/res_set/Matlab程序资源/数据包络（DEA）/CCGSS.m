clear;
clc;
format long;
temp_input=xlsread('original_data.xls',-1);
temp_output=xlsread('original_data.xls',-1);
[m,n]=size(temp_input);
[s,n]=size(temp_output);

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

%输出
xlswrite('output.xls','lamda值',1,'A1');
xlswrite('output.xls',outputx(1:n,:),1,'A2');

k1=n+3;

string_1=['A',num2str(k1)];
xlswrite('output.xls','松弛变量值',1,string_1);
string_2=['A',num2str(n+4)];
xlswrite('output.xls',outputx(n+1:n+m,:),1,string_2);

string_3=['A',num2str(n+m+5)];
xlswrite('output.xls','剩余变量',1,string_3);
string_4=['A',num2str(n+m+6)];
xlswrite('output.xls',outputx(n+m+1:nA-1,:),1,string_4);

string_5=['A',num2str(n+m+s+7)];
xlswrite('output.xls','theta值',1,string_5);
string_6=['A',num2str(n+m+s+8)];
xlswrite('output.xls',outputx(nA,:),1,string_6);

string_7=['A',num2str(n+m+s+10)];
xlswrite('output.xls','目标函数值',1,string_7);
string_8=['A',num2str(n+m+s+11)];
xlswrite('output.xls',outputfval,1,string_8);