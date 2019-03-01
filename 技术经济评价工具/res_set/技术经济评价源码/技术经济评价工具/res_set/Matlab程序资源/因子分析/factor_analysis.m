clear;
clc;
thelong=0.000001;
Max=inf;
delta=inf;
X=xlsread('original_data.xls',-1);
[m,n]=size(X);

%第一个图形
subplot(121);
boxplot(X,0,'+',0);
xlabel('变量值的范围');
ylabel('指标（变量）');

%相关系数矩阵
sr=zscore(X)
R=sr'*sr/(m-1)

%进行主成分分析
[pcs,newdata,variances,t2]=princomp(sr)

%特征值占总体百分数
percent_explained=100*variances/sum(variances)

%特征值的累计百分数
leiji=percent_explained./sum(percent_explained);
for i=1:n
    lj_percentage(i)=sum(leiji(1:i));
end
leiji_percentage=lj_percentage'

%第二个图形
subplot(122);
pareto(percent_explained);
xlabel('主成分');
ylabel('方差占的比重（%）');

%下面开始求因子载荷矩阵
for j=1:n
    AA(:,j)=sqrt(variances(j,1))*pcs(:,j);
end
for i=1:n
    if(lj_percentage(i)>=0.85)
        k=i;
        break;
    end
end

%因子载荷矩阵
A=AA(:,1:k)

%求h的平方（共同度）、d的平方（剩余方差）和g的平方（方差贡献）
BB=power(A,2);
for j=1:n
    hhh(j)=sum(BB(j,:));
end
hh=hhh'
h=sqrt(hh);
dd=1-h
gg=sum(BB)

%下面开始求方差最大正交旋转矩阵
%赋值给theta
M=0;
B=A;
TTT=eye(k,k);
while(delta>thelong)
    M=M+1;
    for r=1:k-1
        if r==1
            T1=eye(k,k);
        end
        for g=r+1:k
            x=B(:,r)./h;
            y=B(:,g)./h;
            v=power(x,2)-power(y,2);
            w=2*x.*y;
            a=sum(v);
            b=sum(w);
            c=sum(power(v,2)-power(w,2));
            d=2*sum(v.*w);
            e=d-2*a*b/n;
            f=c-(power(a,2)-power(b,2))/n;
            if e==0
                break;
            else
                theta=acot(f/e);
                theta=theta/4;
            end
            if and(e>0,theta<0)
                theta=theta+pi/4;
            elseif and(e<0,theta>0)
                theta=theta-pi/4;
            end
            TT=eye(k,k);
            TT(r,r)=cos(theta);
            TT(r,g)=-sin(theta);
            TT(g,r)=sin(theta);
            TT(g,g)=cos(theta);
            TTT=TT*TTT;
            T1=TT*T1;
        end
    end
    B=B*T1;
    BB=power(B,2);
    ddd=BB./hh(:,ones(k,1));
    aver=mean(ddd);
    VV=sum(power(ddd-aver(ones(n,1),:),2)/n);
    V(M)=sum(VV);
    if M==1
        delta=Max;
    else
        delta=abs(V(M)-V(M-1));
    end
end
V
N=M
B
TTT

%下面开始求正交因子得分矩阵
for i=1:m
    XX=zscore(X);
    XX=XX(i,:);
    F=B'*inv(R);
    FF(i,:)=(F*XX')';
end
FF