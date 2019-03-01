clear;
clc;
thelong=0.000001;
Max=inf;
delta=inf;
X=xlsread('original_data.xls',-1);
[m,n]=size(X);

%��һ��ͼ��
subplot(121);
boxplot(X,0,'+',0);
xlabel('����ֵ�ķ�Χ');
ylabel('ָ�꣨������');

%���ϵ������
sr=zscore(X)
R=sr'*sr/(m-1)

%�������ɷַ���
[pcs,newdata,variances,t2]=princomp(sr)

%����ֵռ����ٷ���
percent_explained=100*variances/sum(variances)

%����ֵ���ۼưٷ���
leiji=percent_explained./sum(percent_explained);
for i=1:n
    lj_percentage(i)=sum(leiji(1:i));
end
leiji_percentage=lj_percentage'

%�ڶ���ͼ��
subplot(122);
pareto(percent_explained);
xlabel('���ɷ�');
ylabel('����ռ�ı��أ�%��');

%���濪ʼ�������غɾ���
for j=1:n
    AA(:,j)=sqrt(variances(j,1))*pcs(:,j);
end
for i=1:n
    if(lj_percentage(i)>=0.85)
        k=i;
        break;
    end
end

%�����غɾ���
A=AA(:,1:k)

%��h��ƽ������ͬ�ȣ���d��ƽ����ʣ�෽���g��ƽ��������ף�
BB=power(A,2);
for j=1:n
    hhh(j)=sum(BB(j,:));
end
hh=hhh'
h=sqrt(hh);
dd=1-h
gg=sum(BB)

%���濪ʼ�󷽲����������ת����
%��ֵ��theta
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

%���濪ʼ���������ӵ÷־���
for i=1:m
    XX=zscore(X);
    XX=XX(i,:);
    F=B'*inv(R);
    FF(i,:)=(F*XX')';
end
FF