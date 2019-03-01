#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"iostream.h"


//�������ۺ�����
class CWeight
{
public:
	//���۸�Ȩ��
	int entropy_weight(char *filename);//��ֵ��
	int grey_correlation_degree(char *filename);//��ɫ�����ȷ�
	int variance_coefficient(char *filename);//����ϵ����
	int multi_objective_optimization(char *filename);//��Ŀ���Ż���
	int multiple_correlation_coefficient(char *filename);//�����ϵ����
	int multiple_weight(char *filename);//�˷���Ȩ��Ϸ�
	int linear_weight(char *filename);//���Լ�Ȩ��Ϸ�
	int critic(char *filename);
	int improved_entropy_weight(char *filename);//�Ľ���Ȩ��
	//�͹۸�Ȩ��
	int expert(char *filename);//ר�Ҵ�ַ�
	int AHP(char *filename);//��η�����
	int contrast_compositor(char *filename);//�Ա�����
	int PC(char *filename);//����ͼ��
};


/*********************************Entropy weight method*****************************
                                  Enter the file's name!
    Input��ԭʼ������X[M][N]��Ԫ��X[i][j]�����i�ַ�����j��ָ���ԭʼ���ݣ�
    Output��ָ���Ȩ����W��
*/
int CWeight::entropy_weight(char *filename)
{
	//......����ԭʼ����......
	FILE *fp;
    float  **W,**x;//�����ά����
    int  i,j;
	int  row=0,column=0;//�У���
    char ch;


	if((fp=fopen(filename,"r"))==NULL)//���ļ�
	{
		printf("open error\n");
		return 1;
	}


    while(!feof(fp)&&(ch=fgetc(fp))!='\n')//ͳ������
		if(ch=='\t')
			column++;
	column++;
	if(column==1)
	{
		printf("no data\n");
		return 1;	
	}
	fseek(fp,0L,0);//���ļ��ײ�
	while(!feof(fp))//ͳ������
		if(fgetc(fp)=='\n')
			row++;
	row++;
	if(row==1)
	{
		printf("no data\n");
		return 1;	
	}


	W=(float**)malloc(sizeof(float*));//ΪȨ�����������ڴ�
	if(W==NULL)
	{
		printf("no memory\n");
		return 1;	
	}
	W[0]=(float*)malloc(sizeof(float)*column);
	if(W[0]==NULL)
	{
		printf("no memory\n");
		return 1;	
	}
    x=(float**)malloc(sizeof(float*)*row);//Ϊԭʼ���ݾ��󿪱��ڴ�
	if(x==NULL)
	{
		printf("no memory\n");
		return 1;	
	}
	for(i=0;i<row;i++)
	{
		x[i]=(float*)malloc(sizeof(float)*column);
		if(x[i]==NULL)
		{
			printf("no memory\n");
			return 1;	
		}
	}


	fseek(fp,0L,0);//���ļ��ײ�
	while(!feof(fp))//��������
	for(i=0;i<row;i++)
		for(j=0;j<column;j++)
			fscanf(fp,"%f,",&x[i][j]);


	//......����ؾ���......
	int m=row,n=column;
	float sum=0,K=(float)(1/log(n));


	for(j=0;j<n;j++)
	{
		for(i=0;i<m;i++)
			sum+=x[i][j];
		for(i=0;i<m;i++)
			x[i][j]=x[i][j]/sum;
		sum=0;
	}


	//......��������->ƫ���->�͹�Ȩ��......
	for(j=0;j<n;j++)//������->ƫ���
	{
		for(i=0;i<m;i++)
			if(x[i][j])
			{
				sum+=K*x[i][j]*(float)log(x[i][j]);
			}
		W[0][j]=1-sum;
		sum=0;
	}
	for(j=0;j<n;j++)//->�͹�Ȩ����
		sum+=W[0][j];
	for(j=0;j<n;j++)
		W[0][j]=W[0][j]/sum;


	//......��ʾ���������......
	if((fp=fopen("weight.txt","w+"))==NULL)//���ļ�
	{
		printf("open error\n");
		return 1;
	}
	for(i=0;i<1;i++)//�����ʾ����Ļ��д���ļ�"weight.txt"
	{
		//fprintf(fp,"��ֵ��:\t");
		for(j=0;j<n;j++)
		{
			if(j==column-1)
				fprintf(fp,"%f",W[i][j]);
			else
				fprintf(fp,"%f\t",W[i][j]);
		}
	}

	//......�ͷ��ڴ�......
	fclose(fp);//�ر��ļ�
	for(i=0;i<row;i++)
		free(x[i]);
	free(x);
	free(W[0]);
	free(W);
	return 0;
}



/************************Grey correlation degree method************************
                            Enter the file's name!
    Input��ԭʼ�������0��Ϊ���������ο�Ȩֵ��
	       ԭʼ������X[N][M]��Ԫ��X[i][j]ָ����i��ר�ҶԵ�j����ָ������֣�
	Output������ָ���Ȩ��ֵW[2][N-1]
	        W[0][j]ָ����Grey correlation degree weight��
			W[1][j]ָ����Grey correlation degree weight��
*/
#define r 0.5
int CWeight::grey_correlation_degree(char *filename)
{
	//......����ԭʼ����......
	FILE *fp;
    float  **W,**x,**d;//�����ά����
    int  i,j;
	int  row=0,column=0;//�У���
    char ch;


	if((fp=fopen(filename,"r"))==NULL)//���ļ�
	{
		printf("open error\n");
		return 1;
	}


    while(!feof(fp)&&(ch=fgetc(fp))!='\n')//ͳ������
		if(ch=='\t')
			column++;
	column++;
	if(column==1)
	{
		printf("no data\n");
		return 1;	
	}
	fseek(fp,0L,0);//���ļ��ײ�
	while(!feof(fp))//ͳ������
		if(fgetc(fp)=='\n')
			row++;
	row++;
	if(row==1)
	{
		printf("no data\n");
		return 1;	
	}


	W=(float**)malloc(sizeof(float*)*2);//ΪȨ�����������ڴ�
	if(W==NULL)
	{
		printf("no memory\n");
		return 1;	
	}
	for(i=0;i<2;i++)
	{
		W[i]=(float*)malloc(sizeof(float)*(column-1));
		if(W[i]==NULL)
		{
			printf("no memory\n");
	 	    return 1;	
		}
	}

    x=(float**)malloc(sizeof(float*)*row);//Ϊԭʼ���ݾ��󿪱��ڴ�
	if(x==NULL)
	{
		printf("no memory\n");
		return 1;	
	}
	for(i=0;i<row;i++)
	{
		x[i]=(float*)malloc(sizeof(float)*column);
		if(x[i]==NULL)
		{
			printf("no memory\n");
			return 1;	
		}
	}
	fseek(fp,0L,0);//���ļ��ײ�
	while(!feof(fp))//��������
	for(i=0;i<row;i++)
		for(j=0;j<column;j++)
			fscanf(fp,"%f,",&x[i][j]);

	d=(float**)malloc(sizeof(float*)*row);//Ϊ������󿪱��ڴ�
	if(x==NULL)
	{
		printf("no memory\n");
		return 1;	
	}
	for(i=0;i<row;i++)
	{
		d[i]=(float*)malloc(sizeof(float)*column);
		if(x[i]==NULL)
		{
			printf("no memory\n");
			return 1;	
		}
	}

	
	//......��ԭʼ�����ֵ��......
	int n=row,m=column;
	float sum=0;


	for(j=0;j<m;j++)
	{
		for(i=0;i<n;i++)
			sum+=x[i][j];
		for(i=0;i<n;i++)
			x[i][j]=m*x[i][j]/sum;
		sum=0;
	}


	//......�������......
	float max,min;


	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			d[i][j]=(float)fabs(x[0][j]-x[i][j]);


	max=d[0][0];
	min=d[0][0];
	for(i=1;i<n;i++)
		for(j=0;j<m;j++)
		{
			if(d[i][j]>max)
				max=d[i][j];
			else if(d[i][j]<min)
				min=d[i][j];
		}


	//......����ϵ���͹�����......
	for(j=1;j<m;j++) //i=1����һ��Ϊ���������ο�Ȩֵ
	{
		for(i=0;i<n;i++)
			sum+=(float)((min+r*max)/(d[i][j]+r*max));
		W[0][j-1]=sum/m;
		sum=0;
	}

	
	//......Ȩ������һ������......
	for(j=0;j<m-1;j++)
			sum+=W[0][j];
	for(j=0;j<m-1;j++)
		W[0][j]=W[0][j]/sum;

	
	//......��ɫ������Ȩ��ȷ���Ľ�����......
	sum=0;
	for(j=1;j<m;j++)
	{
		for(i=1;i<n;i++)
			sum+=(float)pow((x[0][j]-x[i][j]),2);
		W[1][j-1]=1/(sum+1);
		sum=0;
	}


	//......Ȩ���������һ������......
	for(j=0;j<m-1;j++)
			sum+=W[1][j];
	for(j=0;j<m-1;j++)
		W[1][j]=W[1][j]/sum;


	//......��ʾ���������weight.txt......
	if((fp=fopen("weight.txt","w+"))==NULL)//���ļ�
	{
		printf("open error\n");
		return 1;
	}
	for(i=0;i<1/*2*/;i++)//�����ʾ����Ļ��д���ļ�"Grey_correlation_degree_weight.txt"
	{
		for(j=0;j<m-1;j++)
		{
			if(j==m-2)
				fprintf(fp,"%f",W[i][j]);
			else
				fprintf(fp,"%f\t",W[i][j]);
		}
	}


	//......�ͷ��ڴ�......
    fclose(fp);//�ر��ļ�
	for(i=0;i<row;i++)
	{
		free(x[i]);
		free(d[i]);
	}
	free(x);
	free(d);
	for(i=0;i<2;i++)
		free(W[i]);
	free(W);
	return 0;
}



/*********************************Variance_coefficient_method*****************************
                                  Enter the file's name!
    Input��ԭʼ������X[M][N]��Ԫ��X[i][j]�����i�������j�����ָ���ԭʼ���ݣ�
    Output��ָ���Ȩ����W[N]��
*/
int CWeight::variance_coefficient(char *filename)
{
	FILE *fp;
    float  **W,**x,**x0,**s;//�����ά����
    int  i,j;
	int  row=0,column=0;//�У���
    char ch;


	if((fp=fopen(filename,"r"))==NULL)//���ļ�
	{
		printf("open error\n");
		return 1;
	}


    while(!feof(fp)&&(ch=fgetc(fp))!='\n')//ͳ������
		if(ch=='\t')
			column++;
	column++;
	if(column==1)
	{
		printf("no data\n");
		return 1;	
	}
	fseek(fp,0L,0);//���ļ��ײ�
	while(!feof(fp))//ͳ������
		if(fgetc(fp)=='\n')
			row++;
	row++;
	if(row==1)
	{
		printf("no data\n");
		return 1;	
	}

    x=(float**)malloc(sizeof(float*)*row);//Ϊԭʼ���ݾ���x�����ڴ�
	if(x==NULL)
	{
		printf("no memory\n");
		return 1;	
	}
	for(i=0;i<row;i++)
	{
		x[i]=(float*)malloc(sizeof(float)*column);
		if(x[i]==NULL)
		{
			printf("no memory\n");
			return 1;	
		}
	}


	//��filename.txt�ж�ȡ����
	fseek(fp,0L,0);//���ļ��ײ�
	while(!feof(fp))//��������
	for(i=0;i<row;i++)
		for(j=0;j<column;j++)
			fscanf(fp,"%f,",&x[i][j]);

	W=(float **)malloc(sizeof(float *)*1);//ΪȨ�ؿ����ڴ�
	x0=(float **)malloc(sizeof(float *)*1);//Ϊ��ֵ�����ڴ�
	s=(float **)malloc(sizeof(float *)*1);//Ϊ��׼����ڴ�
	if(x0==NULL&&W==NULL&&s==NULL)
	{
		printf("no memory!\n");
		return 1;
	}
	for(i=0;i<1;i++)
	{
		W[i]=(float *)malloc(sizeof(float)*column);
		x0[i]=(float *)malloc(sizeof(float)*column);
		s[i]=(float *)malloc(sizeof(float)*column);
		if(W[i]==NULL&&x0[i]==NULL&&s[i]==NULL&&s[i]==NULL)
		{
			printf("no memory!");
			return 1;
		}
	}


	//���ָ���ֵ�ͱ�׼��
	int n=row,m=column;
	float sum=0;
	for(j=0;j<m;j++)
	{
		for(i=0;i<n;i++)
			sum+=x[i][j];
		x0[0][j]=sum/n;
		sum=0;
	}

	for(j=0;j<m;j++)
	{
		for(i=0;i<n;i++)
			sum+=(float)pow((x[i][j]-x0[0][j]),2);
		s[0][j]=(float)sqrt(sum/(n-1));
		sum=0;
	}


	//�����ָ�����ϵ��������ϵ����ΪȨ�أ������һ������
	for(j=0;j<m;j++)
	{
		W[0][j]=s[0][j]/x0[0][j];
		sum+=W[0][j];
	}
	for(j=0;j<m;j++)
		W[0][j]=W[0][j]/sum;


	//......��ʾ���������......
	if((fp=fopen("weight.txt","w+"))==NULL)//���ļ�
	{
		printf("open error\n");
		return 1;
	}
	for(i=0;i<1;i++)//�����ʾ����Ļ��д���ļ�"weight.txt"
	{
		//fprintf(fp,"����ϵ����:\t");
		for(j=0;j<m;j++)
		{
			if(j==column-1)
				fprintf(fp,"%f",W[i][j]);
			else
				fprintf(fp,"%f\t",W[i][j]);
		}
	}


	//......�ͷ��ڴ�......
	fclose(fp);//�ر��ļ�
	for(i=0;i<row;i++)
		free(x[i]);
	free(x);
	free(W[0]),free(x0[0]),free(s[0]);
	free(W),free(x0),free(s);
	return 0;
}



/*********************************Multi objective optimization method*****************************
                                      Enter the file's name!
    Input��ԭʼ������X[M][N]��Ԫ��X[i][j]�����i�������j�����ָ���ԭʼ���ݣ�
    Output��ָ���Ȩ����W[N]��
*/
int CWeight::multi_objective_optimization(char *filename)
{
	FILE *fp;
	float **x,**W,sum=0;
	int i,j,k;
	int row=0,column=0;
	char ch;

	if((fp=fopen(filename,"r"))==NULL)
	{
		printf("open error\n");
		return 1;
	}
	while(!feof(fp)&&(ch=fgetc(fp))!='\n')
		if(ch=='\t')
			column++;
	column++;
	if(column==1)
	{
		printf("no data\n");
		return 1;
	}
	fseek(fp,0L,0);
	while(!feof(fp))
		if(fgetc(fp)=='\n')
			row++;
	row++;
	if(row==1)
	{
		printf("no data\n");
		return 1;
	}

	x=(float**)malloc(sizeof(float*)*row);//Ϊԭʼ���ݾ���x�����ڴ�
	if(x==NULL)
	{
		printf("no memory\n");
		return 1;
	}
	for(i=0;i<row;i++)
	{
		x[i]=(float*)malloc(sizeof(float)*column);
		if(x[i]==NULL)
		{
			printf("no memory\n");
			return 1;
		}
	}


	//......��filename.txt�ж�ȡ����......
	fseek(fp,0L,0);
	while(!feof(fp))
		for(i=0;i<row;i++)
			for(j=0;j<column;j++)
				fscanf(fp,"%f,",&x[i][j]);


	W=(float**)malloc(sizeof(float*)*1);//ΪȨ�����������ڴ�W
	if(W==NULL)
	{
		printf("no memory\n");
		return 1;
	}
	W[0]=(float*)malloc(sizeof(float)*column);
	if(W[0]==NULL)
	{
		printf("no memory\n");
		return 1;
	}


	//......����߾���A�Ĺ淶������Z......
	int m=row,n=column;

	for(j=0;j<n;j++)
	{
		for(i=0;i<m;i++)
			sum+=x[i][j];
		for(i=0;i<m;i++)
			x[i][j]=x[i][j]/sum;
		sum=0;
	}


	//......�����Ż�Ȩ��......
	float sum0=0;
	for(j=0;j<n;j++)
		for(i=0;i<m;i++)
			for(k=0;k<m;k++)
				sum0+=(float)fabs(x[i][j]-x[k][j]);

	for(j=0;j<n;j++)
	{
		for(i=0;i<m;i++)
			for(k=0;k<m;k++)
				sum+=(float)fabs(x[i][j]-x[k][j]);
		W[0][j]=sum/sum0;
		sum=0;
	}

	
	//......W��׼��......
	for(j=0;j<n;j++)
		sum+=W[0][j];
	for(j=0;j<n;j++)
		W[0][j]=W[0][j]/sum;


	//......��ʾ���W���洢......
	if((fp=fopen("weight.txt","w+"))==NULL)
	{
		printf("open error\n");
		return 1;
	}

	//fprintf(fp,"��Ŀ���Ż���:\t");
	for(j=0;j<n;j++)
	{
		if(j==column-1)
			fprintf(fp,"%f",W[0][j]);
		else
			fprintf(fp,"%f\t",W[0][j]);
	}


	//......�ͷ��ڴ�......
	fclose(fp);
	free(W[0]);
	free(W);
	for(i=0;i<m;i++)
		free(x[i]);
	free(x);
	return 0;
}



/*********************************Multiple correlation coefficient method*****************************
                                         Enter the file's name!
    Input��ԭʼ������X[M][N]��Ԫ��X[i][j]�����i�������j�����ָ���ԭʼ���ݣ�
    Output��ָ���Ȩ����W[N]��
*/
int CWeight::multiple_correlation_coefficient(char *filename)
{
	FILE *fp;
	int i,j,k;
    float **x;
	float **R,**R1;
    float **r1,**W;
	float sum=0;
	int row=0,column=0;
	char ch;


	if((fp=fopen(filename,"r"))==NULL)//���ļ�
	{
		printf("open error\n");
		return 1;
	}
	while(!feof(fp)&&(ch=fgetc(fp))!='\n')
		if(ch=='\t')
			column++;
	column++;
	if(column==1)
	{
		printf("no data\n");
		return 1;
	}
	fseek(fp,0L,0);
	while(!feof(fp))
		if(fgetc(fp)=='\n')
			row++;
	row++;
	if(row==1)
	{
		printf("no data\n");
		return 1;
	}


	//......���ٶ�̬�ڴ�......
	x=(float**)malloc(sizeof(float*)*row);//Ϊԭʼ���ݾ���x�����ڴ�
	if(x==NULL)
	{
		printf("no memory\n");
		return 1;
	}
	for(i=0;i<row;i++)
	{
		x[i]=(float*)malloc(sizeof(float)*column);
		if(x[i]==NULL)
		{
			printf("no memory\n");
			return 1;
		}
	}

	W=(float**)malloc(sizeof(float*)*1);//ΪȨ�����������ڴ�W
	if(W==NULL)
	{
		printf("no memory\n");
		return 1;
	}
	W[0]=(float*)malloc(sizeof(float)*column);
	if(W[0]==NULL)
	{
		printf("no memory\n");
		return 1;
	}

	R=(float**)malloc(sizeof(float*)*column);//Ϊ���ϵ������R�����ڴ�
	if(R==NULL)
	{
		printf("no memory\n");
		return 1;
	}
	for(i=0;i<column;i++)
	{
		R[i]=(float*)malloc(sizeof(float)*column);
		if(R[i]==NULL)
		{
			printf("no memory\n");
			return 1;
		}
	}

	R1=(float**)malloc(sizeof(float*)*(column-1));//Ϊ����R1�����ڴ�
	if(R1==NULL)
	{
		printf("no memory\n");
		return 1;
	}
	for(i=0;i<(column-1);i++)
	{
		R1[i]=(float*)malloc(sizeof(float)*(column-1));
		if(R1[i]==NULL)
		{
			printf("no memory\n");
			return 1;
		}
	}

	r1=(float**)malloc(sizeof(float*)*1);//�����ڴ�
	if(r1==NULL)
	{
		printf("no memory\n");
		return 1;
	}
	r1[0]=(float*)malloc(sizeof(float)*(column-1));
	if(r1[0]==NULL)
	{
		printf("no memory\n");
		return 1;
	}


	//......��filename.txt�ж�ȡ����......
	fseek(fp,0L,0);
	while(!feof(fp))
		for(i=0;i<row;i++)
			for(j=0;j<column;j++)
				fscanf(fp,"%f,",&x[i][j]);


	//......���ָ������ϵ������......
	int m=row,n=column;
	float average,sumsd=0,variance;//sumsdΪsum of squares of deviation(���ƽ���ͣ�

	for(j=0;j<n;j++)
	{
		for(i=0;i<m;i++)
			sum+=x[i][j];
		average=sum/m;
		for(i=0;i<m;i++)
			sumsd+=(x[i][j]-average)*(x[i][j]-average);
		variance=sumsd/(m-1);
		for(i=0;i<m;i++)
	    	x[i][j]=(float)((x[i][j]-average)/sqrt(variance));
		sum=0;
		sumsd=0;
	}

	for(j=0;j<n;j++)
	{
		for(k=0;k<n;k++)
		{
			for(i=0;i<m;i++)
				sum+=x[i][j]*x[i][k];
		    R[j][k]=sum/(m-1);
		    sum=0;
		}
	}


	//......�������ָ��������ָ������ϵ��......
	for(k=0;k<n;k++)
	{
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
			{
				if(i<k&&j<k)
					R1[i][j]=R[i][j];
				else if(i>k&&j<k)
					R1[i-1][j]=R[i][j];
				else if(i<k&&j>k)
					R1[i][j-1]=R[i][j];
				else if(i>k&&j>k)
					R1[i-1][j-1]=R[i][j];
			}

		for(i=0;i<n;i++)
		{
			if(i<k)
				r1[0][i]=R[i][k];
			else if(i>k)
				r1[0][i-1]=R[i][k];
		}

		for(j=0;j<n-1;j++)
			for(i=0;i<n-1;i++)
				sum+=r1[0][i]*R1[i][j]*r1[0][j];
			
		W[0][k]=sum;
		sum=0;
	}


	//......ȨֵW��һ������......
	for(j=0;j<n;j++)
		sum+=(float)1./W[0][j];
	for(j=0;j<n;j++)
		W[0][j]=(float)1./(W[0][j]*sum);


	//......��ʾ���W......
	if((fp=fopen("weight.txt","w+"))==NULL)
	{
		printf("open error\n");
		return 1;
	}

	//fprintf(fp,"�����ϵ����:\t");
	for(j=0;j<n;j++)
	{
		if(j==column-1)
			fprintf(fp,"%f",W[0][j]);
		else
			fprintf(fp,"%f\t",W[0][j]);
	}


	//......�ͷ��ڴ�......
	fclose(fp);

	for(i=0;i<1;i++)
	{
		free(r1[i]);
		free(W[i]);
	}
	free(r1);
	free(W);

	for(i=0;i<m;i++)
		free(x[i]);
	free(x);

	for(i=0;i<n;i++)
		free(R[i]);
	free(R);

	for(i=0;i<n-1;i++)
		free(R1[i]);
	free(R1);
	return 0;
}



/*********************************The multiplicatively weighted combination method*****************************
                                            Enter the file's name!
    Input��ԭʼ������X[M][N]��Ԫ��X[i][j]�����i�ַ�����j��ָ���ԭʼ���ݣ�
    Output��ָ���Ȩ����W[N]��
*/
int CWeight::multiple_weight(char *filename)
{
	FILE *fp;
	float **x,**W;
	int i,j,row=0,column=0;
	float sum=0,multiple=1;
	char ch;

	if((fp=fopen(filename,"r"))==NULL)//���ļ�
	{
		printf("open error\n");
		return 1;
	}
	while(!feof(fp)&&(ch=fgetc(fp))!='\n')
		if(ch=='\t')
			column++;
	column++;
	if(column==1)
	{
		printf("no data\n");
		return 1;
	}
	fseek(fp,0L,0);
	while(!feof(fp))
		if(fgetc(fp)=='\n')
			row++;
	row++;
	if(row==1)
	{
		printf("no data\n");
		return 1;
	}

	//......���ٶ�̬�ڴ�......
	x=(float**)malloc(sizeof(float*)*row);//Ϊԭʼ���ݾ���x�����ڴ�
	if(x==NULL)
	{
		printf("no memory\n");
		return 1;
	}
	for(i=0;i<row;i++)
	{
		x[i]=(float*)malloc(sizeof(float)*column);
		if(x[i]==NULL)
		{
			printf("no memory\n");
			return 1;
		}
	}

	W=(float**)malloc(sizeof(float*)*1);//ΪȨ�����������ڴ�W
	if(W==NULL)
	{
		printf("no memory\n");
		return 1;
	}
	W[0]=(float*)malloc(sizeof(float)*column);
	if(W[0]==NULL)
	{
		printf("no memory\n");
		return 1;
	}


	//......��filename.txt�ж�ȡ����......
	fseek(fp,0L,0);
	while(!feof(fp))
		for(i=0;i<row;i++)
			for(j=0;j<column;j++)
				fscanf(fp,"%f,",&x[i][j]);


	//......�˷���Ȩ�����Ȩֵ......
	int m=row,n=column;
	for(j=0;j<n;j++)
	{
		for(i=0;i<m;i++)
			multiple*=x[i][j];
		sum+=multiple;
		multiple=1;
	}

	for(j=0;j<n;j++)
	{
		for(i=0;i<m;i++)
			multiple*=x[i][j];
		W[0][j]=multiple/sum;
		multiple=1;
	}


	//......ȨֵW��һ������......
	sum=0;
	for(j=0;j<n;j++)
		sum+=W[0][j];
	for(j=0;j<n;j++)
		W[0][j]=W[0][j]/sum;


	//......��ʾ���W......
	if((fp=fopen("weight.txt","w+"))==NULL)
	{
		printf("open error\n");
		return 1;
	}

	//fprintf(fp,"�˷���Ȩ��Ϸ�:\t");
	for(j=0;j<n;j++)
	{
		if(j==column-1)
			fprintf(fp,"%f",W[0][j]);
		else
			fprintf(fp,"%f\t",W[0][j]);
	}


	//......�ͷ��ڴ�......
	fclose(fp);
	free(W);
	for(i=0;i<m;i++)
		free(x[i]);
	free(x);
	return 0;
}



/*********************************The linear weighted assignment method*****************************
                                         Enter the file's name!
    Input��ԭʼ������X[M][N]��Ԫ��X[i][j]�����i�ַ�����j��ָ���ԭʼ���ݣ�
    Output��ָ���Ȩ����W[N]��
*/
int CWeight::linear_weight(char *filename)
{
	FILE *fp;
	float **x,**w,**W1,**W;
	int i,j,k;
	float sum=0,max;
	int row=0,column=0;
	char ch;


	if((fp=fopen(filename,"r"))==NULL)//���ļ�
	{
		printf("open error\n");
		return 1;
	}
	while(!feof(fp)&&(ch=fgetc(fp))!='\n')
		if(ch=='\t')
			column++;
	column++;
	if(column==1)
	{
		printf("no data\n");
		return 1;
	}
	fseek(fp,0L,0);
	while(!feof(fp))
		if(fgetc(fp)=='\n')
			row++;
	row++;
	if(row==1)
	{
		printf("no data\n");
		return 1;
	}

	//......���ٶ�̬�ڴ�......
	x=(float**)malloc(sizeof(float*)*row);//Ϊԭʼ���ݾ���x�����ڴ�
	if(x==NULL)
	{
		printf("no memory\n");
		return 1;
	}
	for(i=0;i<row;i++)
	{
		x[i]=(float*)malloc(sizeof(float)*column);
		if(x[i]==NULL)
		{
			printf("no memory\n");
			return 1;
		}
	}

	w=(float**)malloc(sizeof(float*)*row);//Ϊԭʼ���ݾ���x�����ڴ�
	if(w==NULL)
	{
		printf("no memory\n");
		return 1;
	}
	for(i=0;i<row;i++)
	{
		w[i]=(float*)malloc(sizeof(float)*row);
		if(w[i]==NULL)
		{
			printf("no memory\n");
			return 1;
		}
	}

	W1=(float**)malloc(sizeof(float*)*1);//ΪȨ�����������ڴ�W
	if(W1==NULL)
	{
		printf("no memory\n");
		return 1;
	}
	W1[0]=(float*)malloc(sizeof(float)*row);
	if(W1[0]==NULL)
	{
		printf("no memory\n");
		return 1;
	}

	W=(float**)malloc(sizeof(float*)*1);//ΪȨ�����������ڴ�W
	if(W==NULL)
	{
		printf("no memory\n");
		return 1;
	}
	W[0]=(float*)malloc(sizeof(float)*column);
	if(W[0]==NULL)
	{
		printf("no memory\n");
		return 1;
	}


	//......��filename.txt�ж�ȡ����......
	fseek(fp,0L,0);
	while(!feof(fp))
		for(i=0;i<row;i++)
			for(j=0;j<column;j++)
				fscanf(fp,"%f,",&x[i][j]);


    //......��spearman�ȼ����ϵ������w......
	int m=row,n=column;
	for(i=0;i<m;i++)
		for(k=0;k<m;k++)
		{
			for(j=0;j<n;j++)
				sum+=(float)pow((x[i][j]-x[k][j]),2);
			w[i][k]=1-6*sum/(n*(n-1));
			sum=0;
		}


	//......ȷ��������ϵ��......
	int a1,a2;
	float sum1=0,sum2=0;
	max=w[0][0];
	for(i=0;i<m;i++)
		for(k=0;k<m;k++)
		{
			if(max<w[i][j])
				max=w[i][j];
			a1=i;
			a2=j;
		}


	//......�󷽷�Ȩ���������һ��......
	for(j=0;j<m;j++)//Ѱ��һ������ߵĸ�ֵ����
		sum1+=w[a1][j];
	for(i=0;i<m;i++)
		sum2+=w[i][a2];
	if(sum1>sum2)
	{
		for(j=0;j<m;j++)
			W1[0][j]=w[a1][j];
	}
	else
	{
		for(j=0;j<m;j++)
			W1[0][j]=w[j][a2];
	}

	for(j=0;j<m;j++)//��׼����ֵ������Ȩֵ
		sum+=W1[0][j];
	for(j=0;j<m;j++)
		W1[0][j]=W1[0][j]/sum;


	//......���ۺ�Ȩ��W�����һ��......
	sum=0;
	for(j=0;j<n;j++)
	{
		for(i=0;i<m;i++)
			sum+=W1[0][i]*x[i][j];
		W[0][j]=sum;
		sum=0;
	}

	for(j=0;j<n;j++)//��׼���ۺ�Ȩ��
		sum+=W[0][j];
	for(j=0;j<n;j++)
		W[0][j]=W[0][j]/sum;


	//......��ʾ���W......
	if((fp=fopen("weight.txt","w+"))==NULL)
	{
		printf("open error\n");
		return 1;
	}

	//fprintf(fp,"���Լ�Ȩ��Ϸ�:\t");
	for(j=0;j<n;j++)
	{
		if(j==column-1)
			fprintf(fp,"%f",W[0][j]);
		else
			fprintf(fp,"%f\t",W[0][j]);
	}


	//......�ͷ��ڴ�......
	fclose(fp);
	free(W);
	free(W1);
	for(i=0;i<m;i++)
	{
		free(x[i]);
		free(w[i]);
	}
	free(x);
	free(w);
	return 0;
}



/*********************************CRITIC method*****************************
                             Enter the file's name!
    Input��ԭʼ������X[M][N]��Ԫ��X[i][j]�����i�ַ�����j��ָ���ԭʼ���ݣ�
    Output��ָ���Ȩ����W[N]��
*/
int CWeight::critic(char *filename)
{
	FILE *fp;
	float **x,**R,**B,**W;
	int i,j,k;
	float sum=0;
	int row=0,column=0;
	char ch;


	if((fp=fopen(filename,"r"))==NULL)//���ļ�
	{
		printf("open error\n");
		return 1;
	}
	while(!feof(fp)&&(ch=fgetc(fp))!='\n')
		if(ch=='\t')
			column++;
	column++;
	if(column==1)
	{
		printf("no data\n");
		return 1;
	}
	fseek(fp,0L,0);
	while(!feof(fp))
		if(fgetc(fp)=='\n')
			row++;
	row++;
	if(row==1)
	{
		printf("no data\n");
		return 1;
	}

	//......���ٶ�̬�ڴ�......
	x=(float**)malloc(sizeof(float*)*row);//Ϊԭʼ���ݾ���x�����ڴ�
	if(x==NULL)
	{
		printf("no memory\n");
		return 1;
	}
	for(i=0;i<row;i++)
	{
		x[i]=(float*)malloc(sizeof(float)*column);
		if(x[i]==NULL)
		{
			printf("no memory\n");
			return 1;
		}
	}

	R=(float**)malloc(sizeof(float*)*column);//Ϊ���ϵ������R�����ڴ�
	if(R==NULL)
	{
		printf("no memory\n");
		return 1;
	}
	for(i=0;i<column;i++)
	{
		R[i]=(float*)malloc(sizeof(float)*column);
		if(R[i]==NULL)
		{
			printf("no memory\n");
			return 1;
		}
	}

	B=(float**)malloc(sizeof(float*)*1);//Ϊԭʼ���ݾ���x�����ڴ�
	if(B==NULL)
	{
		printf("no memory\n");
		return 1;
	}
	for(i=0;i<1;i++)
	{
		B[i]=(float*)malloc(sizeof(float)*column);
		if(B[i]==NULL)
		{
			printf("no memory\n");
			return 1;
		}
	}

	W=(float**)malloc(sizeof(float*)*1);
	if(W==NULL)
	{
		printf("no memory\n");
		return 1;
	}
	W[0]=(float*)malloc(sizeof(float)*column);
	if(W[0]==NULL)
	{
		printf("no memory\n");
		return 1;
	}

	//......��filename.txt�ж�ȡ����......
	fseek(fp,0L,0);
	while(!feof(fp))
		for(i=0;i<row;i++)
			for(j=0;j<column;j++)
				fscanf(fp,"%f,",&x[i][j]);


	//......���ָ������ϵ������......
	int m=row,n=column;
	float average,sumsd=0,variance;//sumsdΪsum of squares of deviation(���ƽ���ͣ�

	for(j=0;j<n;j++)
	{
		for(i=0;i<m;i++)
			sum+=x[i][j];
		average=sum/m;
		for(i=0;i<m;i++)
			sumsd+=(x[i][j]-average)*(x[i][j]-average);
		variance=sumsd/(m-1);
		for(i=0;i<m;i++)
	    	x[i][j]=(float)((x[i][j]-average)/sqrt(variance));
		sum=0;
		sumsd=0;
	}

	for(j=0;j<n;j++)
	{
		for(k=0;k<n;k++)
		{
			for(i=0;i<m;i++)
				sum+=x[i][j]*x[i][k];
		    R[j][k]=sum/(m-1);
		    sum=0;
		}
	}



	//......��������ָ��......
	for(j=0;j<n;j++)
	{
		for(i=0;i<n;i++)
			sum+=(1-R[i][j]);
		B[0][j]=sum;
		sum=0;
	}


	//......������Ϣ��......
	for(j=0;j<n;j++)
	{
		for(i=0;i<m;i++)
			sum+=x[i][j];
		average=sum/m;
		for(i=0;i<m;i++)
			sumsd+=(x[i][j]-average)*(x[i][j]-average);
		variance=sumsd/(m-1);
		W[0][j]=(float)sqrt(variance)*B[0][j];
		sum=0;
		sumsd=0;
	}

	//......Ȩ�ع�һ��......
	for(j=0;j<n;j++)
		sum+=W[0][j];
	for(j=0;j<n;j++)
		W[0][j]=W[0][j]/sum;



	//......��ʾ���W......
	if((fp=fopen("weight.txt","w+"))==NULL)
	{
		printf("open error\n");
		return 1;
	}

	//fprintf(fp,"CRITIC:\t");
	for(j=0;j<n;j++)
	{
		if(j==column-1)
			fprintf(fp,"%f",W[0][j]);
		else
			fprintf(fp,"%f\t",W[0][j]);
	}


	//......�ͷ��ڴ�......
	fclose(fp);
	free(W);
	free(B);
	for(i=0;i<m;i++)
	{
		free(x[i]);
	}
	free(x);
	for(i=0;i<n;i++)
	{
		free(R[i]);
	}
	free(R);
	return 0;
}




/*********************************Improved entropy weight method*****************************
                                     Enter the file's name!
    Input��ԭʼ������X[M][N]��Ԫ��X[i][j]�����i�ַ�����j��ָ���ԭʼ���ݣ�
    Output��ָ���Ȩ����W��
*/
int CWeight::improved_entropy_weight(char *filename)
{
	//......����ԭʼ����......
	FILE *fp;
    float  **W,**x;//�����ά����
    int  i,j;
	int  row=0,column=0;//�У���
    char ch;


	if((fp=fopen(filename,"r"))==NULL)//���ļ�
	{
		printf("open error\n");
		return 1;
	}


    while(!feof(fp)&&(ch=fgetc(fp))!='\n')//ͳ������
		if(ch=='\t')
			column++;
	column++;
	if(column==1)
	{
		printf("no data\n");
		return 1;	
	}
	fseek(fp,0L,0);//���ļ��ײ�
	while(!feof(fp))//ͳ������
		if(fgetc(fp)=='\n')
			row++;
	row++;
	if(row==1)
	{
		printf("no data\n");
		return 1;	
	}


	W=(float**)malloc(sizeof(float*));//ΪȨ�����������ڴ�
	if(W==NULL)
	{
		printf("no memory\n");
		return 1;	
	}
	W[0]=(float*)malloc(sizeof(float)*column);
	if(W[0]==NULL)
	{
		printf("no memory\n");
		return 1;	
	}
    x=(float**)malloc(sizeof(float*)*row);//Ϊԭʼ���ݾ��󿪱��ڴ�
	if(x==NULL)
	{
		printf("no memory\n");
		return 1;	
	}
	for(i=0;i<row;i++)
	{
		x[i]=(float*)malloc(sizeof(float)*column);
		if(x[i]==NULL)
		{
			printf("no memory\n");
			return 1;	
		}
	}


	fseek(fp,0L,0);//���ļ��ײ�
	while(!feof(fp))//��������
	for(i=0;i<row;i++)
		for(j=0;j<column;j++)
			fscanf(fp,"%f,",&x[i][j]);


	//......����ؾ���......
	int m=row,n=column;
	float sum=0,K=(float)(1/log(n));


	for(j=0;j<n;j++)
	{
		for(i=0;i<m;i++)
			sum+=x[i][j];
		for(i=0;i<m;i++)
			x[i][j]=x[i][j]/sum;
		sum=0;
	}


	//......��������->ƫ���->�͹�Ȩ��......
	for(j=0;j<n;j++)//������->ƫ���
	{
		for(i=0;i<m;i++)
			if(x[i][j])
			{
				sum+=(-K*x[i][j]*(float)log(x[i][j]));
			}
		W[0][j]=1-sum;
		sum=0;
	}
	for(j=0;j<n;j++)//->�͹�Ȩ����
		sum+=W[0][j];
	for(j=0;j<n;j++)
		W[0][j]=W[0][j]/sum;
	

	//......��Ȩ����......
	int flag=1,Kmax=0;
	sum=0;
	while(flag&&Kmax<10)
	{
		for(j=0;j<n;j++)
		{
			if(W[0][j]>0.3)
			{
				for(i=0;i<n;i++)
				{
					if(i!=j)
						sum+=W[0][i];
				}
				for(i=0;i<n;i++)
				{
					if(i!=j)
						W[0][i]=(float)(W[0][i]+W[0][i]*(W[0][j]-0.3)/sum);
				}
				W[0][j]=0.30;
				sum=0;
			}
		}
		flag=0;
		for(j=0;j<n;j++)
		{
			if(W[0][j]>0.3000001)
				flag++;
		}
		if(flag!=0)
			flag=1;
		Kmax++;
	}
	if(Kmax==10)
	{
		//printf("��Ȩ���������ѳ���%d�Σ�",10);
		AfxMessageBox("��Ȩ���������ѳ���10�Σ�");
		return 1;
	}


	//......��ʾ���������......
	if((fp=fopen("weight.txt","w+"))==NULL)//���ļ�
	{
		printf("open error\n");
		return 1;
	}
	for(i=0;i<1;i++)//�����ʾ����Ļ��д���ļ�"weight.txt"
	{
		//fprintf(fp,"�Ľ���ֵ��:\t");
		for(j=0;j<n;j++)
		{
			if(j==column-1)
				fprintf(fp,"%f",W[i][j]);
			else
				fprintf(fp,"%f\t",W[i][j]);
		}
	}


	//......�ͷ��ڴ�......
	fclose(fp);//�ر��ļ�
	for(i=0;i<row;i++)
		free(x[i]);
	free(x);
	free(W[0]);
	free(W);
	return 0;
}




/*********************************The expert scoring method*****************************
                                    Enter the file's name!
    Input��ԭʼ������A[M][N]��Ԫ��A[i][j]�����i��ר�ҶԵ�j��ָ������֣�
    Output��ָ���Ȩ����W[N]��
*/
int CWeight::expert(char *filename)
{
	FILE *fp;
	float **A,**D,**aver,**v,**ka,sum=0;
	int i,j;
	int row=0,column=0;
	char ch;


	if((fp=fopen(filename,"r"))==NULL)//���ļ�
	{
		printf("open error\n");
		return 1;
	}
	while(!feof(fp)&&(ch=fgetc(fp))!='\n')
		if(ch=='\t')
			column++;
	column++;
	if(column==1)
	{
		printf("no data\n");
		return 1;
	}
	fseek(fp,0L,0);
	while(!feof(fp))
		if(fgetc(fp)=='\n')
			row++;
	row++;
	if(row==1)
	{
		printf("no data\n");
		return 1;
	}

	//......���ٶ�̬�ڴ�......
	A=(float**)malloc(sizeof(float*)*row);//Ϊԭʼ���ݾ���x�����ڴ�
	if(A==NULL)
	{
		printf("no memory\n");
		return 1;
	}
	for(i=0;i<row;i++)
	{
		A[i]=(float*)malloc(sizeof(float)*column);
		if(A[i]==NULL)
		{
			printf("no memory\n");
			return 1;
		}
	}

	D=(float**)malloc(sizeof(float*)*row);//Ϊԭʼ���ݾ���x�����ڴ�
	if(D==NULL)
	{
		printf("no memory\n");
		return 1;
	}
	for(i=0;i<row;i++)
	{
		D[i]=(float*)malloc(sizeof(float)*column);
		if(D[i]==NULL)
		{
			printf("no memory\n");
			return 1;
		}
	}

	aver=(float**)malloc(sizeof(float*)*1);
	v=(float**)malloc(sizeof(float*)*1);
	ka=(float**)malloc(sizeof(float*)*1);
	if(aver==NULL||v==NULL||ka==NULL)
	{
		printf("no memory\n");
		return 1;
	}
	aver[0]=(float*)malloc(sizeof(float)*column);
	v[0]=(float*)malloc(sizeof(float)*column);
	ka[0]=(float*)malloc(sizeof(float)*column);
	if(aver[0]==NULL||v[0]==NULL||ka[0]==NULL)
	{
		printf("no memory\n");
		return 1;
	}


	//......��filename.txt�ж�ȡ����......
	fseek(fp,0L,0);
	while(!feof(fp))
		for(i=0;i<row;i++)
			for(j=0;j<column;j++)
				fscanf(fp,"%f,",&A[i][j]);


	//......��һ������......
	int m=row,n=column;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
			sum+=A[i][j];
		for(j=0;j<n;j++)
			A[i][j]=A[i][j]/sum;
		sum=0;
	}


	//......����ָ��ƽ��ֵ......
	for(j=0;j<n;j++)
	{
		for(i=0;i<m;i++)
			sum+=A[i][j];
		aver[0][j]=sum/m;
		sum=0;
	}


	//......�������......
	for(j=0;j<n;j++)
	{
		for(i=0;i<m;i++)
			D[i][j]=(A[i][j]-aver[0][j]);
	}


	//......�������̶�......
	for(j=0;j<n;j++)
	{
		for(i=0;i<m;i++)
			sum+=(float)pow((D[i][j]),2);
		v[0][j]=(float)sqrt(sum/(m-1));
		sum=0;
	}

	for(j=0;j<n;j++)
		ka[0][j]=v[0][j]/aver[0][j];


	//......�򿪲�д��Ȩ���ļ�......
	if((fp=fopen("weight.txt","w+"))==NULL)
	{
		printf("open error\n");
		return 1;
	}

	//......����̶��ж�......
	int biaoji=0;
	for(j=0;j<n;j++)
	{
		if(ka[0][j]>0.05)
			biaoji++;
	}

	if(biaoji!=0)
	{
    	for(j=0;j<n;j++)
		{
			if(j==n-1)
			{
				if(ka[0][j]>0.05)
    	    		fprintf(fp,"%f",1.);
		    	else
		    		fprintf(fp,"%f",2.);
			}
			else
			{
     	    	if(ka[0][j]>0.05)
    	    		fprintf(fp,"%f\t",1.);
		    	else
		    		fprintf(fp,"%f\t",2.);
			}
		}
		AfxMessageBox("ר����ȷ����Ȩ��ϵ��ֵ��Ϊ��ɢ��ȱ��ͳһ�ԺͿɿ���,�����½���ר�����ۣ�");
		AfxMessageBox("���ϵͳ�����ϵ�ȷ�����˽ⲻһ��ָ��(1����һ��ָ�꣬2����һ����ָ��)��");
	}
	else
	{
    	//fprintf(fp,"expert scoring:\t");
    	for(j=0;j<n;j++)
		{
	    	if(j==column-1)
	    		fprintf(fp,"%f",aver[0][j]);
	    	else
		    	fprintf(fp,"%f\t",aver[0][j]);
		}
	}


	//......�ͷ��ڴ�......
	fclose(fp);
	free(v);
	free(aver);
	free(ka);
	for(i=0;i<m;i++)
	{
		free(A[i]);
		free(D[i]);
	}
	free(A);
	free(D);
	return 0;
}



/*********************************analytic hierarchy process(AHP)*****************************
                                    Enter the file's name!
									   input max lambda!
    Input��ԭʼ������A[M][N]��Ԫ��A[i][j]�����i��ר�ҶԵ�j��ָ������֣�
    Output��ָ���Ȩ����W[N]��
*/
int CWeight::AHP(char *filename)
{
	
	FILE *fp;
	float **A,**W;
	int i,j;
	int row=0,column=0;
	char ch;


	if((fp=fopen(filename,"r"))==NULL)//���ļ�
	{
		printf("open error\n");
		return 1;
	}
	while(!feof(fp)&&(ch=fgetc(fp))!='\n')
		if(ch=='\t')
			column++;
	column++;
	if(column==1)
	{
		printf("no data\n");
		return 1;
	}
	fseek(fp,0L,0);
	while(!feof(fp))
		if(fgetc(fp)=='\n')
			row++;
	row++;
	if(row==1)
	{
		printf("no data\n");
		return 1;
	}

	if(row!=column)
	{
		AfxMessageBox("�жϾ������в���ȣ�\n");
		return 1;
	}

	//......���ٶ�̬�ڴ�......
	A=(float**)malloc(sizeof(float*)*row);//Ϊԭʼ���ݾ���x�����ڴ�
	if(A==NULL)
	{
		printf("no memory\n");
		return 1;
	}
	for(i=0;i<row;i++)
	{
		A[i]=(float*)malloc(sizeof(float)*column);
		if(A[i]==NULL)
		{
			printf("no memory\n");
			return 1;
		}
	}

	W=(float**)malloc(sizeof(float*)*1);//ΪȨ������W�����ڴ�
	if(W==NULL)
	{
		printf("no memory\n");
		return 1;
	}
	for(i=0;i<1;i++)
	{
		W[i]=(float*)malloc(sizeof(float)*column);
		if(W[i]==NULL)
		{
			printf("no memory\n");
			return 1;
		}
	}

	if(row>15)
	{
		AfxMessageBox("�жϾ���ά��һ�����Ϊ15!\n");
		return 1;
	}


	//......��filename.txt�ж�ȡ����......
	fseek(fp,0L,0);
	while(!feof(fp))
	{
		for(i=0;i<row;i++)
			for(j=0;j<column;j++)
				fscanf(fp,"%f,",&A[i][j]);
	}


	//......�����������lambda���������ֵ��Ӧ����������......
	float **U,lambda,sum=0,sumM=1;
	int m=row,n=column;


	//......�����ڴ�......
	U=(float**)malloc(sizeof(float*)*1);//ΪȨ������U�����ڴ�
	if(U==NULL)
	{
		printf("no memory\n");
		return 1;
	}
	for(i=0;i<1;i++)
	{
		U[i]=(float*)malloc(sizeof(float)*column);
		if(U[i]==NULL)
		{
			printf("no memory\n");
			return 1;
		}
	}

	//��������ֵ
	for(i=0;i<m;i++)
	{	
		for(j=0;j<n;j++)
			sumM*=A[i][j];	
		W[0][i]=pow(sumM,1./m);
		sumM=1;
	}
	for(i=0;i<m;i++)
		sum+=W[0][i];
	for(i=0;i<n;i++)
		W[0][i]=W[0][i]/sum;
    sum=0;


	//��������ֵ
	for(i=0;i<m;i++)
	{	
		for(j=0;j<n;j++)
			sumM*=A[i][j];	
		W[0][i]=pow(sumM,1./m);
		sumM=1;
	}
	for(i=0;i<m;i++)
		sum+=W[0][i];
	for(i=0;i<n;i++)
		W[0][i]=W[0][i]/sum;
    sum=0;

	//�����������ֵ
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
			sum+=A[i][j]*W[0][j];
		U[0][i]=sum;
		sum=0;
	}
	
	for(i=0;i<m;i++)
		sum+=U[0][i]/W[0][i];
	lambda=sum/m;
	sum=0;



	//......������RI[15]�洢��ͬά�ȶ�Ӧ��RIֵ......
	float RI[15]={0,0,0.58,0.90,1.12,1.24,1.32,1.41,1.45,1.49,1.52,1.54,1.56,1.58,1.59};


	//......�����������ֵ��һ���Լ���......
	float CI,CR;
	int flag,flag0,l=0;
	CI=(lambda-n)/(n-1);
	CR=CI/RI[n];
	if(CR<0.10)
	{
		//......��ʾ���������......
    	if((fp=fopen("weight.txt","w+"))==NULL)//���ļ�
		{
     		printf("open error\n");
	    	return 1;
		}
		//�����ʾ����Ļ��д���ļ�"weight.txt"
    	for(j=0;j<n;j++)
		{
	 	   	if(j==n-1)
		   		fprintf(fp,"%f",W[0][j]);
		   	else
			  	fprintf(fp,"%f\t",W[0][j]);
		}
	}
	else
	{
		AfxMessageBox("һ���Լ���ʧ�ܣ�");
	}


	//......�ͷ��ڴ�......
	fclose(fp);
	for(i=0;i<m;i++)
	{
		free(A[i]);
	}
	free(A);
	free(U[0]);
	free(W[0]);
	free(U);
	free(W);
	return 0;
}



/*********************************Contrast compositor method*****************************
                                    Enter the file's name!
    Input��ԭʼ������A[M][N]��Ԫ��A[i][j]�����i��ר�ҶԵ�j��ָ������֣�
    Output��ָ���Ȩ����W[N]��
*/
int CWeight::contrast_compositor(char *filename)
{
	AfxMessageBox("��ָ���Ŀ����Ȩ�ؿ��Ի��ڸ����о�����ã������������η����㷨��");

	FILE *fp;
	float **A,**W;
	int i,j;
	int row=0,column=0;
	char ch;


	if((fp=fopen(filename,"r"))==NULL)//���ļ�
	{
		printf("open error\n");
		return 1;
	}
	while(!feof(fp)&&(ch=fgetc(fp))!='\n')
		if(ch=='\t')
			column++;
	column++;
	if(column==1)
	{
		printf("no data\n");
		return 1;
	}
	fseek(fp,0L,0);
	while(!feof(fp))
		if(fgetc(fp)=='\n')
			row++;
	row++;
	if(row==1)
	{
		printf("no data\n");
		return 1;
	}

	//......���ٶ�̬�ڴ�......
	A=(float**)malloc(sizeof(float*)*row);//Ϊԭʼ���ݾ���x�����ڴ�
	if(A==NULL)
	{
		printf("no memory\n");
		return 1;
	}
	for(i=0;i<row;i++)
	{
		A[i]=(float*)malloc(sizeof(float)*column);
		if(A[i]==NULL)
		{
			printf("no memory\n");
			return 1;
		}
	}

	W=(float**)malloc(sizeof(float*)*1);//ΪȨ������W�����ڴ�
	if(W==NULL)
	{
		printf("no memory\n");
		return 1;
	}
	for(i=0;i<1;i++)
	{
		W[i]=(float*)malloc(sizeof(float)*column);
		if(W[i]==NULL)
		{
			printf("no memory\n");
			return 1;
		}
	}


	//......��filename.txt�ж�ȡ����......
	fseek(fp,0L,0);
	while(!feof(fp))
	{
		for(i=0;i<row;i++)
			for(j=0;j<column;j++)
				fscanf(fp,"%f,",&A[i][j]);
	}


	//......�����ָ��Ȩ��......
	int m=row,n=column;
	float sum=0;
	for(j=0;j<n;j++)
	{
		for(i=0;i<m;i++)
			sum+=(float)(log(A[i][j])/log(n));
		W[0][j]=sum/m;
		sum=0;
	}


	//......��һ��......
	for(j=0;j<n;j++)
		sum+=W[0][j];
	for(j=0;j<n;j++)
	    W[0][j]=W[0][j]/sum;



	//......��ʾ���������......
	if((fp=fopen("weight.txt","w+"))==NULL)//���ļ�
	{
		printf("open error\n");
		return 1;
	}
	for(i=0;i<1;i++)//�����ʾ����Ļ��д���ļ�"weight.txt"
	{
		//fprintf(fp,"�Ա�����:\t");
		for(j=0;j<n;j++)
		{
			if(j==n-1)
				fprintf(fp,"%f",W[i][j]);
			else
				fprintf(fp,"%f\t",W[i][j]);
		}
	}


	//......�ͷ��ڴ�......
	fclose(fp);
	for(i=0;i<m;i++)
	{
		free(A[i]);
	}
	free(A);
	free(W[0]);
	free(W);
	return 0;
}



/*********************************precedence Chart(PC)*****************************
                                 Enter the file's name!
    Input��ԭʼ������A[M][N]��Ԫ��A[i][j]�����i��ר�ҶԵ�j��ָ������֣�
    Output��ָ���Ȩ����W[N]��
*/
int CWeight::PC(char *filename)
{
	FILE *fp;
	float **A,**W;
	int i,j;
	int row=0,column=0;
	char ch;


	if((fp=fopen(filename,"r"))==NULL)//���ļ�
	{
		printf("open error\n");
		return 1;
	}
	while(!feof(fp)&&(ch=fgetc(fp))!='\n')
		if(ch=='\t')
			column++;
	column++;
	if(column==1)
	{
		printf("no data\n");
		return 1;
	}
	fseek(fp,0L,0);
	while(!feof(fp))
		if(fgetc(fp)=='\n')
			row++;
	row++;
	if(row==1)
	{
		printf("no data\n");
		return 1;
	}

	//......���ٶ�̬�ڴ�......
	A=(float**)malloc(sizeof(float*)*row);//Ϊԭʼ���ݾ���x�����ڴ�
	if(A==NULL)
	{
		printf("no memory\n");
		return 1;
	}
	for(i=0;i<row;i++)
	{
		A[i]=(float*)malloc(sizeof(float)*column);
		if(A[i]==NULL)
		{
			printf("no memory\n");
			return 1;
		}
	}

	W=(float**)malloc(sizeof(float*)*1);//ΪȨ������W�����ڴ�
	if(W==NULL)
	{
		printf("no memory\n");
		return 1;
	}
	for(i=0;i<1;i++)
	{
		W[i]=(float*)malloc(sizeof(float)*column);
		if(W[i]==NULL)
		{
			printf("no memory\n");
			return 1;
		}
	}


	//......��filename.txt�ж�ȡ����......
	fseek(fp,0L,0);
	while(!feof(fp))
	{
		for(i=0;i<row;i++)
			for(j=0;j<column;j++)
				fscanf(fp,"%f,",&A[i][j]);
	}

	if(row!=column)
	{
		AfxMessageBox("ԭʼ�������в���ȣ�");
		return 1;
	}


	//......��������......
	int m=row,n=column,flag=0;
	for(i=0;i<m;i++)
	{
		for(j=i;j<n;j++)
		{
			if(i!=j)
			{
				if((A[i][j]+A[j][i])==1);
				else
					flag++;
			}
		}
	}

	//......��ʾ���������......
	if((fp=fopen("weight.txt","w+"))==NULL)//���ļ�
	{
		printf("open error\n");
		return 1;
	}


	if(flag==0)
	{
		//fprintf(fp,"��������ɹ���\n")
		AfxMessageBox("��������ɹ���");

		//......�����ָ��Ȩ��......
    	float sum=0,T;
    	T=(float)(n-1)*n/2;
    	for(i=0;i<n;i++)
		{
	    	for(j=0;j<m;j++)
		    	sum+=A[i][j];
    		W[0][i]=sum/T;
    		sum=0;
		}


    	//......��һ��......
    	for(j=0;j<n;j++)
	    	sum+=W[0][j];
    	for(j=0;j<n;j++)
	        W[0][j]=W[0][j]/sum;


    	for(i=0;i<1;i++)//�����ʾ����Ļ��д���ļ�"weight.txt"
		{
    		//fprintf(fp,"�Ա�����:\t");
	    	for(j=0;j<n;j++)
			{
	    		if(j==n-1)
			    	fprintf(fp,"%f",W[i][j]);
		    	else
		 	    	fprintf(fp,"%f\t",W[i][j]);
			}
		}
	}
	else if(flag!=0)
	{
		//fprintf(fp,"��������ʧ�ܣ�\n");
		AfxMessageBox("��������ʧ�ܣ�");
		return 1;
	}


	//......�ͷ��ڴ�......
	fclose(fp);
	for(i=0;i<m;i++)
	{
		free(A[i]);
	}
	free(A);
	free(W[0]);
	free(W);
	return 0;
}