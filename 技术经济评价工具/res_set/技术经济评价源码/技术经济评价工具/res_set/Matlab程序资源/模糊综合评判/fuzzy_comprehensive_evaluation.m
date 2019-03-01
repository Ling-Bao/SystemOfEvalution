 clear
 clc
 clear data
 
 %读入数据
data=xlsread('original_data.xls',-1);
[n,m]=size(data);%n数据条数，m指标个数

%数据标准化
mean_d=mean(data);
for j=1:m
    data(:,j)=data(:,j)/mean_d(j);
end

weight=xlsread('original_data.xls',-1);

dengji=xlsread('original_data.xls',-1);

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
%输出
xlswrite('result.xls',zp);