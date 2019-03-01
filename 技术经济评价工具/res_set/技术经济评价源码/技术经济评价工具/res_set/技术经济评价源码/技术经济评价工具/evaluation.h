#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"iostream.h"


//�������ۺ�����
class CEvaluation
{
public:
	//���۷���
	int comprehensive_index(char *filename,char *weight_filename);//�ۺ�ָ����
	int grey_relational_comprehensive_evaluation(char *filename,char *weight_filename);//��ɫ�����ۺ����۷�
	int topsis(char *filename,char *weight_filename);//��ɫ���ƽ�����ⷨ
	int osculating_value(char *filename,char *weight_filename);//����ֵ��

};



/*********************************Comprehensive index method*****************************
                            Enter the file's and weight file's name!
    Input��ԭʼ������A[N][M+S],W[N],Ԫ��A[i][j]�����i�ַ�����j��ָ���ԭʼ���ݣ�
    Output��F[N]��
*/
int CEvaluation::comprehensive_index(char *filename,char *weight_filename)
{
	FILE *fp,*fq;
	float **A,**W,**F;
	int i,j;
	float sum=0;
	int row=0,column=0;
	char ch;


	//......����ԭʼ����A......
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

    A=(float**)malloc(sizeof(float*)*row);//Ϊԭʼ���ݾ��󿪱��ڴ�
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


	fseek(fp,0L,0);//���ļ��ײ�
	while(!feof(fp))//��������
	for(i=0;i<row;i++)
		for(j=0;j<column;j++)
			fscanf(fp,"%f,",&A[i][j]);

     
	//......����ԭʼ����W......
	int column1=0,row1=0;
	if((fq=fopen(weight_filename,"r"))==NULL)//���ļ�
	{
		printf("open error\n");
		return 1;
	}


    while(!feof(fq)&&(ch=fgetc(fq))!='\n')//ͳ������
		if(ch=='\t')
			column1++;
	column1++;
	if(column1==1)
	{
		printf("no data\n");
		return 1;	
	}
	fseek(fq,0L,0);//���ļ��ײ�
	while(!feof(fq))//ͳ������
		if(fgetc(fq)=='\n')
			row1++;
		row1++;
	if(row1==0)
	{
		printf("no data\n");
		return 1;	
	}

    W=(float**)malloc(sizeof(float*)*row1);//Ϊԭʼ���ݾ��󿪱��ڴ�
	if(W==NULL)
	{
		printf("no memory\n");
		return 1;	
	}
	for(i=0;i<row1;i++)
	{
		W[i]=(float*)malloc(sizeof(float)*column1);
		if(W[i]==NULL)
		{
			printf("no memory\n");
			return 1;	
		}
	}


	fseek(fq,0L,0);//���ļ��ײ�
	while(!feof(fq))//��������
	for(i=0;i<row1;i++)
		for(j=0;j<column1;j++)
			fscanf(fq,"%f,",&W[i][j]);


	if(column!=column1)
	{
		//printf("ָ��Ȩ�������������\n");
		AfxMessageBox("ָ��Ȩ����Ŀ��ԭʼ���ݲ�ƥ�䣡");
		return 1;
	}
	else
	{
		int m=row,n=column;

		F=(float**)malloc(sizeof(float*)*1);//Ϊԭʼ���ݾ��󿪱��ڴ�
    	if(F==NULL)
		{
	    	printf("no memory\n");
     		return 1;	
		}
    	for(i=0;i<1;i++)
		{
	    	F[i]=(float*)malloc(sizeof(float)*n);
	    	if(F[i]==NULL)
			{
	    		printf("no memory\n");
		    	return 1;	
			}
		}


		//......Ҫ�ظ�ָ���Ȩ���۷�......
		for(i=0;i<m;i++)
		{
			for(j=0;j<n;j++)
				sum+=A[i][j]*W[0][j];
			F[0][i]=sum;
			sum=0;
		}


		//......��һ��......
		for(j=0;j<m;j++)
	    	sum+=F[0][j];
	    for(j=0;j<m;j++)
	        F[0][j]=F[0][j]/sum;


		//......��ʾ���������......
    	if((fp=fopen("evaluation.txt","w+"))==NULL)//���ļ�
		{
	    	printf("open error\n");
	     	return 1;
		}
    	for(i=0;i<1;i++)//�����ʾ����Ļ��д���ļ�"weight.txt"
		{
	    	//fprintf(fp,"�ۺ�ָ����:\t");
	    	for(j=0;j<m;j++)
			{
		    	if(j==m-1)
		     		fprintf(fp,"%f",F[i][j]);
		     	else
			    	fprintf(fp,"%f\t",F[i][j]);
			}
		}
	}

	//......�ͷ��ڴ�......
	fclose(fp);
	fclose(fq);
	for(i=0;i<row;i++)
	{
		free(A[i]);
	}
	free(A);
	free(W[0]);
	free(F[0]);
	free(W);
	free(F);
	
	return 0;
}



/*********************************The grey relational comprehensive evaluation method*****************************
                                       Enter the file's and weight file's name!
    Input��ԭʼ������D[M][N],W[N],Ԫ��D[i][j]�����i�ַ�����j��ָ���ԭʼ���ݣ�
    Output��������������ֵ����R[M]��
*/
int CEvaluation::grey_relational_comprehensive_evaluation(char *filename,char *weight_filename)
{

	FILE *fp,*fq;
	float **D,**W,**C,**E,**R;
	float max,min,sum=0;
	int i,j;
	int row=0,column=0;
	char ch;


	//......����ԭʼ����D......
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

    D=(float**)malloc(sizeof(float*)*row);//Ϊԭʼ���ݾ��󿪱��ڴ�
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


	fseek(fp,0L,0);//���ļ��ײ�
	while(!feof(fp))//��������
	for(i=0;i<row;i++)
		for(j=0;j<column;j++)
			fscanf(fp,"%f,",&D[i][j]);


	//......����ԭʼ����W......
	int column1=0,row1=0;
	if((fq=fopen(weight_filename,"r"))==NULL)//���ļ�
	{
		printf("open error\n");
		return 1;
	}


    while(!feof(fq)&&(ch=fgetc(fq))!='\n')//ͳ������
		if(ch=='\t')
			column1++;
	column1++;
	if(column1==1)
	{
		printf("no data\n");
		return 1;	
	}
	fseek(fq,0L,0);//���ļ��ײ�
	while(!feof(fq))//ͳ������
		if(fgetc(fq)=='\n')
			row1++;
		row1++;
	if(row1==0)
	{
		printf("no data\n");
		return 1;	
	}

    W=(float**)malloc(sizeof(float*)*row1);//Ϊԭʼ���ݾ��󿪱��ڴ�
	if(W==NULL)
	{
		printf("no memory\n");
		return 1;	
	}
	for(i=0;i<row1;i++)
	{
		W[i]=(float*)malloc(sizeof(float)*column1);
		if(W[i]==NULL)
		{
			printf("no memory\n");
			return 1;	
		}
	}


	fseek(fq,0L,0);//���ļ��ײ�
	while(!feof(fq))//��������
	for(i=0;i<row1;i++)
		for(j=0;j<column1;j++)
			fscanf(fq,"%f,",&W[i][j]);


	if(column!=column1)
	{
		//printf("ָ��Ȩ�������������\n");
		AfxMessageBox("ָ��Ȩ����Ŀ��ԭʼ���ݲ�ƥ�䣡");
		return 1;
	}
	else
	{
		int m=row,n=column;


		C=(float**)malloc(sizeof(float*)*row);//Ϊ�淶�����󿪱��ڴ�
    	if(C==NULL)
		{
	    	printf("no memory\n");
	    	return 1;	
		}
    	for(i=0;i<row;i++)
		{
	    	C[i]=(float*)malloc(sizeof(float)*column);
	    	if(C[i]==NULL)
			{
		    	printf("no memory\n");
		    	return 1;	
			}
		}

		E=(float**)malloc(sizeof(float*)*(m-1));//Ϊ������󿪱��ڴ�
    	if(E==NULL)
		{
	    	printf("no memory\n");
	    	return 1;	
		}
    	for(i=0;i<m-1;i++)
		{
	    	E[i]=(float*)malloc(sizeof(float)*column);
	    	if(E[i]==NULL)
			{
		    	printf("no memory\n");
		    	return 1;	
			}
		}

		R=(float**)malloc(sizeof(float*)*1);
		if(R==NULL)
		{
			printf("no memory\n");
			return 1;
		}

		for(i=0;i<1;i++)
		{
			R[i]=(float*)malloc(sizeof(float)*column);
			if(R==NULL)
			{
				printf("no memory\n");
				return 1;
			}
		}


		//......��ָ����й淶������......
		for(j=0;j<n;j++)
		{
            min=D[0][j],max=D[0][j];
			for(i=0;i<m;i++)
			{
				if(max<D[i][j])
					max=D[i][j];
				if(min>D[i][j])
					min=D[i][j];
			}
			for(i=0;i<m;i++)
				C[i][j]=(min-D[i][j])/(max-D[i][j]);
		}


		//......�����ɫ����ϵ��......
		float rho=0.5;
		for(j=0;j<n;j++)
		{
			for(i=1;i<m;i++)
				E[i-1][j]=(float)(fabs(D[i][j]-D[0][j]));
		}

		max=E[0][0],min=E[0][0];
		for(i=0;i<m-1;i++)
		{
			for(j=0;j<n;j++)
			{
				if(max<E[i][j])
					max=E[i][j];
				if(min>E[i][j])
					min=E[i][j];
			}
		}

		for(i=0;i<m-1;i++)
		{
			for(j=0;j<n;j++)
				E[i][j]=(min+rho*max)/(E[i][j]+rho*max);
		}


		//......�����ۺ����۽��......
		for(i=0;i<m-1;i++)
		{
			for(j=0;j<n;j++)
				sum+=(W[0][j]*E[i][j]);
			R[0][i]=sum;
			sum=0;
		}


		//......��ʾ���R���洢......
    	if((fp=fopen("evaluation.txt","w+"))==NULL)
		{
     		printf("open error\n");
	    	return 1;
		}

    	//fprintf(fp,"\n*******��ɫ�����ۺ����з�********\n");
		for(i=0;i<1;i++)//�����ʾ����Ļ��д���ļ�"weight.txt"
		{
	    	//fprintf(fp,"�ۺ�ָ����:\t");
	    	for(j=0;j<m-1;j++)
			{
		    	if(j==m-2)
		     		fprintf(fp,"%f",R[i][j]);
		     	else
			    	fprintf(fp,"%f\t",R[i][j]);
			}
		}


     	//......�ͷ��ڴ�......
	    fclose(fp);
		fclose(fq);
		free(R[0]);
		free(W[0]);
		for(i=0;i<m;i++)
		{
			free(D[i]);
			free(C[i]);
		}
		free(D);
		free(C);
		for(i=0;i<m-1;i++)
			free(E[i]);
		free(E);
	}
	return 0;
}




/*********************************TOPSIS*****************************
                  Enter the file's and weight file's name!
    Input��ԭʼ������A[M][N],W[N],Ԫ��A[i][j]�����i�ַ�����j��ָ���ԭʼ���ݣ�
    Output��������������ֵ����C[M]��
*/
int CEvaluation::topsis(char *filename,char *weight_filename)
{
	FILE *fp,*fq;
	float **A,**A1,**A2,**W,**w,**R1,**R2,**d1,**d2,**r1,**r2,**C;
	int i,j;
	float sum=0,sum1=0,sum2=0,max,min;
	int row=0,column=0;
	char ch;


	//......����ԭʼ����A......
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

    A=(float**)malloc(sizeof(float*)*row);//Ϊԭʼ���ݾ��󿪱��ڴ�
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


	fseek(fp,0L,0);//���ļ��ײ�
	while(!feof(fp))//��������
	for(i=0;i<row;i++)
		for(j=0;j<column;j++)
			fscanf(fp,"%f,",&A[i][j]);

     
	//......����ԭʼ����W......
	int column1=0,row1=0;
	if((fq=fopen(weight_filename,"r"))==NULL)//���ļ�
	{
		printf("open error\n");
		return 1;
	}


    while(!feof(fq)&&(ch=fgetc(fq))!='\n')//ͳ������
		if(ch=='\t')
			column1++;
	column1++;
	if(column1==1)
	{
		printf("no data\n");
		return 1;	
	}
	fseek(fq,0L,0);//���ļ��ײ�
	while(!feof(fq))//ͳ������
		if(fgetc(fq)=='\n')
			row1++;
		row1++;
	if(row1==0)
	{
		printf("no data\n");
		return 1;	
	}

    W=(float**)malloc(sizeof(float*)*row1);//Ϊԭʼ���ݾ��󿪱��ڴ�
	if(W==NULL)
	{
		printf("no memory\n");
		return 1;	
	}
	for(i=0;i<row1;i++)
	{
		W[i]=(float*)malloc(sizeof(float)*column1);
		if(W[i]==NULL)
		{
			printf("no memory\n");
			return 1;	
		}
	}


	fseek(fq,0L,0);//���ļ��ײ�
	while(!feof(fq))//��������
	for(i=0;i<row1;i++)
		for(j=0;j<column1;j++)
			fscanf(fq,"%f,",&W[i][j]);


	if(column!=column1)
	{
		//printf("ָ��Ȩ�������������\n");
		AfxMessageBox("ָ��Ȩ����Ŀ��ԭʼ���ݲ�ƥ�䣡");
		return 1;
	}
	else
	{
		int m=row,n=column;

		A1=(float**)malloc(sizeof(float*)*row);//Ϊԭʼ���ݾ��󿪱��ڴ�
    	if(A1==NULL)
		{
	    	printf("no memory\n");
	    	return 1;	
		}
    	for(i=0;i<row;i++)
		{
	    	A1[i]=(float*)malloc(sizeof(float)*column);
	    	if(A1[i]==NULL)
			{
		    	printf("no memory\n");
		    	return 1;	
			}
		}

		A2=(float**)malloc(sizeof(float*)*row);//Ϊԭʼ���ݾ��󿪱��ڴ�
    	if(A2==NULL)
		{
	    	printf("no memory\n");
	    	return 1;	
		}
    	for(i=0;i<row;i++)
		{
	    	A2[i]=(float*)malloc(sizeof(float)*column);
	    	if(A2[i]==NULL)
			{
		    	printf("no memory\n");
		    	return 1;	
			}
		}

    	w=(float**)malloc(sizeof(float*)*n);//ΪȨ�ؾ��󿪱��ڴ�
    	if(w==NULL)
		{
    		printf("no memory\n");
     		return 1;	
		}
    	for(i=0;i<n;i++)
		{
	    	w[i]=(float*)malloc(sizeof(float)*n);
    		if(w[i]==NULL)
			{
	     		printf("no memory\n");
		    	return 1;	
			}
		}

		d1=(float**)malloc(sizeof(float*)*row);//Ϊԭʼ���ݾ��󿪱��ڴ�
    	if(d1==NULL)
		{
	    	printf("no memory\n");
	    	return 1;	
		}
    	for(i=0;i<row;i++)
		{
	    	d1[i]=(float*)malloc(sizeof(float)*column);
	    	if(d1[i]==NULL)
			{
		    	printf("no memory\n");
		    	return 1;	
			}
		}

		d2=(float**)malloc(sizeof(float*)*row);//Ϊԭʼ���ݾ��󿪱��ڴ�
    	if(d2==NULL)
		{
	    	printf("no memory\n");
	    	return 1;	
		}
    	for(i=0;i<row;i++)
		{
	    	d2[i]=(float*)malloc(sizeof(float)*column);
	    	if(d2[i]==NULL)
			{
		    	printf("no memory\n");
		    	return 1;	
			}
		}

	    R1=(float**)malloc(sizeof(float*)*1);//Ϊָ��������������R1,R2�����ڴ�
	    R2=(float**)malloc(sizeof(float*)*1);
	    if(R1==NULL||R2==NULL)
		{
	    	printf("no memory\n");
		    return 1;	
		}

	    R1[0]=(float*)malloc(sizeof(float)*n);
     	R2[0]=(float*)malloc(sizeof(float)*n);
    	if(R1[0]==NULL||R2[0]==NULL)
		{
	    	printf("no memory\n");
	    	return 1;	
		}

	    r1=(float**)malloc(sizeof(float*)*1);//Ϊ�������ӵ������d1,d2����ֵ����C�����ڴ�
    	r2=(float**)malloc(sizeof(float*)*1);
     	C=(float**)malloc(sizeof(float*)*1);
    	if(r1==NULL||r2==NULL||C==NULL)
		{
     		printf("no memory\n");
	    	return 1;	
		}

	    r1[0]=(float*)malloc(sizeof(float)*m);
    	r2[0]=(float*)malloc(sizeof(float)*m);
     	C[0]=(float*)malloc(sizeof(float)*m);
     	if(r1[0]==NULL||r2[0]==NULL||C[0]==NULL)
		{
	    	printf("no memory\n");
	     	return 1;	
		}


		//......��淶���߾��󲢽��������ٻ�����......
    	for(j=0;j<n;j++)
		{
	    	for(i=0;i<m;i++)
	     		sum+=(float)pow(A[i][j],2);
			for(i=0;i<m;i++)
				A[i][j]=(float)(A[i][j]/sqrt(sum));
	    	sum=0;
		}

		/*int flag,k=0;
		printf("���۶�����Ч���ͣ�0�����ǳɱ��ͣ�1��,��ѡ��0��1����");
		scanf("%d",&flag);
		while(flag!=0&&flag!=1)
		{
			printf("ѡ��������������룺");
			scanf("%d",&flag);
			k++;
			if(k>3)
			{
				printf("��������������Σ�");
				return 1;
			}
		}*/
		int flag=0,k=0;
        
		for(j=0;j<n;j++)
		{
			max=A[0][j],min=A[0][j];
			for(i=0;i<m;i++)
			{
				if(max<A[i][j])
					max=A[i][j];
				else if(min>A[i][j])
					min=A[i][j];
			}

			if(flag==0)
			{
				for(i=0;i<m;i++)
			    	A1[i][j]=(A[i][j]-min)/(max-min);
			}
			else if(flag==1)
			{
				for(i=0;i<m;i++)
			    	A1[i][j]=(max-A[i][j])/(max-min);
			}

		}


		//......���Ȩ���߾���......
	    for(i=0;i<n;i++)//Ȩ�ؾ���
		{
	    	for(j=0;j<n;j++)
	     		w[i][j]=0;
	    	w[i][i]=W[0][i];
		}

     	for(i=0;i<m;i++)
		{
	    	for(j=0;j<n;j++)
			{
	     		for(k=0;k<n;k++)
		     		sum+=A1[i][k]*w[k][j];
				A2[i][j]=sum;
				sum=0;
			}
		}


		//......�����뷽���븺���뷽��......
		for(j=0;j<n;j++)
		{
			max=A2[0][j],min=A2[0][j];
			for(i=0;i<m;i++)
			{
				if(max<A2[i][j])
					max=A2[i][j];
				else if(min>A2[i][j])
					min=A2[i][j];
			}
			R1[0][j]=max;
			R2[0][j]=min;
		}


		//......��������������뷽���������뷽���Ļҹ���ϵ�����ҹ�����......
		float rho=0.5;
		for(i=0;i<m;i++)
		{
			for(j=0;j<n;j++)
			{
				d1[i][j]=(float)fabs(R1[0][j]-A2[i][j]);
				d2[i][j]=(float)fabs(R2[0][j]-A2[i][j]);
			}
		}

		max=d1[0][0],min=d1[0][0];
		for(i=0;i<m;i++)
		{
			for(j=0;j<n;j++)
			{
				if(max<A2[i][j])
					max=A2[i][j];
				else if(min>A2[i][j])
					min=A2[i][j];
			}
		}

		for(i=0;i<m;i++)
		{
			for(j=0;j<n;j++)
				d1[i][j]=(min+rho*max)/(d1[i][j]+rho*max);
		}


		max=d2[0][0],min=d2[0][0];
		for(i=0;i<m;i++)
		{
			for(j=0;j<n;j++)
			{
				if(max<A2[i][j])
					max=A2[i][j];
				else if(min>A2[i][j])
					min=A2[i][j];
			}
		}

		for(i=0;i<m;i++)
		{
			for(j=0;j<n;j++)
				d2[i][j]=(min+rho*max)/(d2[i][j]+rho*max);
		}

		for(i=0;i<m;i++)
		{
			for(j=0;j<n;j++)
			{
				sum1+=d1[i][j];
				sum2+=d2[i][j];
			}
			r1[0][i]=sum1/n;
			r2[0][i]=sum2/n;
			sum1=0;
			sum2=0;
		}


		//......�������������......
		for(i=0;i<m;i++)
			C[0][i]=r1[0][i]/(r1[0][i]+r2[0][i]);


		//......��ʾ���C���洢......
    	if((fp=fopen("evaluation.txt","w+"))==NULL)
		{
     		printf("open error\n");
	    	return 1;
		}

    	//fprintf(fp,"��ɫ-�ƽ�����ⷨ:\t");
    	for(i=0;i<1;i++)
		{
			for(j=0;j<m;j++)
			{
				if(j==m-1)
			    	fprintf(fp,"%f",C[i][j]);
		        else
		        	fprintf(fp,"%f\t",C[i][j]);
			}
		}


     	//......�ͷ��ڴ�......
	    fclose(fp);
		fclose(fq);
    	free(W[0]);
    	free(r1[0]);
    	free(r2[0]);
    	free(C[0]);
    	free(W);
    	free(r1);
    	free(r2);
    	free(C);
    	for(i=0;i<m;i++)
		{
	    	free(A[i]);
	    	free(A1[i]);
	    	free(A2[i]);
			free(d1[i]);
			free(d2[i]);
		}
    	free(A);
	    free(A1);
    	free(A2);
		free(d1);
		free(d2);
		for(j=0;j<n;j++)
			free(w[j]);
		free(w);
    	return 0;
	}
	return 0;
}




/*********************************Osculating value method*****************************
                           Enter the file's and weight file's name!
    Input��ԭʼ������A[M][N],W[N],Ԫ��A[i][j]�����i�ַ�����j��ָ���ԭʼ���ݣ�
	                    *******ԭʼ����Ϊ�淶����������ת���������**********
    Output��������������ֵ����C[M]��
*/
int CEvaluation::osculating_value(char *filename,char *weight_filename)
{
	FILE *fp,*fq;
	float **A,**W,**w,**R,**r1,**R1,**R2,**d1,**d2,**C;
	int i,j,k;
	float sum=0,sum1=0,sum2=0,max,min;
	int row=0,column=0;
	char ch;

	
	//......����ԭʼ����A......
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

    A=(float**)malloc(sizeof(float*)*row);//Ϊԭʼ���ݾ��󿪱��ڴ�
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


	fseek(fp,0L,0);//���ļ��ײ�
	while(!feof(fp))//��������
	for(i=0;i<row;i++)
		for(j=0;j<column;j++)
			fscanf(fp,"%f,",&A[i][j]);

     
	//......����ԭʼ����W......
	int column1=0,row1=0;
	if((fq=fopen(weight_filename,"r"))==NULL)//���ļ�
	{
		printf("open error\n");
		return 1;
	}


    while(!feof(fq)&&(ch=fgetc(fq))!='\n')//ͳ������
		if(ch=='\t')
			column1++;
	column1++;
	if(column1==1)
	{
		printf("no data\n");
		return 1;	
	}
	fseek(fq,0L,0);//���ļ��ײ�
	while(!feof(fq))//ͳ������
		if(fgetc(fq)=='\n')
			row1++;
		row1++;
	if(row1==0)
	{
		printf("no data\n");
		return 1;	
	}

    W=(float**)malloc(sizeof(float*)*row1);//Ϊԭʼ���ݾ��󿪱��ڴ�
	if(W==NULL)
	{
		printf("no memory\n");
		return 1;	
	}
	for(i=0;i<row1;i++)
	{
		W[i]=(float*)malloc(sizeof(float)*column1);
		if(W[i]==NULL)
		{
			printf("no memory\n");
			return 1;	
		}
	}


	fseek(fq,0L,0);//���ļ��ײ�
	while(!feof(fq))//��������
	for(i=0;i<row1;i++)
		for(j=0;j<column1;j++)
			fscanf(fq,"%f,",&W[i][j]);


    if(column!=column1)
	{
		//printf("ָ��Ȩ�ظ����������\n");
		AfxMessageBox("ָ��Ȩ����Ŀ��ԭʼ���ݲ�ƥ�䣡");
		return 1;
	}
	else
	{
    	//......Ϊw,R,R1,R2,d1,d2,C���䶯̬�ڴ�......
    	int m=row,n=column;
    	w=(float**)malloc(sizeof(float*)*n);//ΪȨ�ؾ��󿪱��ڴ�
    	if(w==NULL)
		{
    		printf("no memory\n");
     		return 1;	
		}
    	for(i=0;i<n;i++)
		{
	    	w[i]=(float*)malloc(sizeof(float)*n);
    		if(w[i]==NULL)
			{
	     		printf("no memory\n");
		    	return 1;	
			}
		}

    	r1=(float**)malloc(sizeof(float*)*m);//Ϊ�淶�����󿪱��ڴ�
      	if(r1==NULL)
		{
	    	printf("no memory\n");
	    	return 1;	
		}
     	for(i=0;i<m;i++)
		{
	    	r1[i]=(float*)malloc(sizeof(float)*n);
	    	if(r1[i]==NULL)
			{
		    	printf("no memory\n");
		    	return 1;	
			}
		}

	    R=(float**)malloc(sizeof(float*)*m);//Ϊ�淶�����󿪱��ڴ�
	    if(R==NULL)
		{
	    	printf("no memory\n");
	    	return 1;	
		}
	    for(i=0;i<m;i++)
		{
	    	R[i]=(float*)malloc(sizeof(float)*n);
	    	if(R[i]==NULL)
			{
		    	printf("no memory\n");
		    	return 1;	
			}
		}

	    R1=(float**)malloc(sizeof(float*)*1);//Ϊָ��������������R1,R2�����ڴ�
	    R2=(float**)malloc(sizeof(float*)*1);
	    if(R1==NULL||R2==NULL)
		{
	    	printf("no memory\n");
		    return 1;	
		}

	    R1[0]=(float*)malloc(sizeof(float)*n);
     	R2[0]=(float*)malloc(sizeof(float)*n);
    	if(R1[0]==NULL||R2[0]==NULL)
		{
	    	printf("no memory\n");
	    	return 1;	
		}

	    d1=(float**)malloc(sizeof(float*)*1);//Ϊ�������ӵ������d1,d2����ֵ����C�����ڴ�
    	d2=(float**)malloc(sizeof(float*)*1);
     	C=(float**)malloc(sizeof(float*)*1);
    	if(d1==NULL||d2==NULL||C==NULL)
		{
     		printf("no memory\n");
	    	return 1;	
		}

	    d1[0]=(float*)malloc(sizeof(float)*m);
    	d2[0]=(float*)malloc(sizeof(float)*m);
     	C[0]=(float*)malloc(sizeof(float)*m);
     	if(d1[0]==NULL||d2[0]==NULL||C[0]==NULL)
		{
	    	printf("no memory\n");
	     	return 1;	
		}


		for(j=0;j<n;j++)
		{
			for(i=0;i<m;i++)
			{
				sum+=A[i][j];
			}

			for(i=0;i<m;i++)
				A[i][j]=A[i][j]/sum;
			sum=0;
		}
		
        
     	//......Ȩ�ؾ���......
	    for(i=0;i<n;i++)
		{
	    	for(j=0;j<n;j++)
	     		w[i][j]=0;
	    	w[i][i]=W[0][i];
		}

		
	    //......��淶��ָ�����R......
    	for(j=0;j<n;j++)
		{
	    	for(i=0;i<m;i++)
	     		sum+=(float)pow(A[i][j],2);
			for(i=0;i<m;i++)
				r1[i][j]=(float)(A[i][j]/sqrt(sum));
	    	sum=0;
		}
		

     	//......��Ȩ�淶������......
     	for(i=0;i<m;i++)
		{
	    	for(j=0;j<n;j++)
			{
	     		for(k=0;k<n;k++)
		     		sum+=r1[i][k]*w[k][j];
				R[i][j]=sum;
				sum=0;
			}
		}


    	//......��ָ��������������R1,R2......
	    for(j=0;j<n;j++)
		{
		    max=R[0][j],min=R[0][j];
	    	for(i=0;i<m;i++)
			{
		     	if(R[i][j]>max)
			    	max=R[i][j];
		    	else if(R[i][j]<min)
			    	min=R[i][j];
			}
	    	R1[0][j]=max;
		    R2[0][j]=min;
		} 


	    //......���������ӵ��������������ֵ��������������ֵ�Է�����������......
    	float sum1=0,sum2=0;
    	for(i=0;i<m;i++)
		{
	    	for(j=0;j<n;j++)
			{
		    	sum1+=(float)pow((R[i][j]-R1[0][j]),2);
			    sum2+=(float)pow((R[i][j]-R2[0][j]),2);
			}
		    d1[0][i]=(float)sqrt(sum1);
	    	d2[0][i]=(float)sqrt(sum2);
	    	sum1=0.0;
	    	sum2=0.0;
		}

    	min=d1[0][0];
    	max=d2[0][0];
	    for(i=0;i<m;i++)
		{
	    	if(min>d1[0][i])
		    	min=d1[0][i];
	    	if(max<d2[0][i])
		    	max=d2[0][i];
		}

	    for(i=0;i<m;i++)
			C[0][i]=((d1[0][i]/min)-(d2[0][i]/max));


     	//......��ʾ���C���洢......
    	if((fp=fopen("evaluation.txt","w+"))==NULL)
		{
     		printf("open error\n");
	    	return 1;
		}

    	//fprintf(fp,"����ֵ��:\t");
    	for(i=0;i<1;i++)
		{
		    for(j=0;j<m;j++)
			{
				if(j==m-1)
		        	fprintf(fp,"%f",C[i][j]);
		     	else
			     	fprintf(fp,"%f\t",C[i][j]);
			}
		}

     	//......�ͷ��ڴ�......
	    fclose(fp);
		fclose(fq);
    	free(W[0]);
    	free(R1[0]);
     	free(R2[0]);
    	free(d1[0]);
    	free(d2[0]);
    	free(C[0]);
    	free(W);
    	free(R1);
    	free(R2);
    	free(d1);
    	free(d2);
    	free(C);
    	for(i=0;i<m;i++)
		{
	    	free(A[i]);
	    	free(R[i]);
	    	free(r1[i]);
		}
    	free(A);
	    free(R);
    	free(r1);
		for(j=0;j<n;j++)
			free(w[j]);
		free(w);
    	return 0;
	}
	return 0;
}
