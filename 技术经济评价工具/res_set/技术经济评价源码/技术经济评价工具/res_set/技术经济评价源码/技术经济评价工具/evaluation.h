#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"iostream.h"


//定义评价函数类
class CEvaluation
{
public:
	//评价方法
	int comprehensive_index(char *filename,char *weight_filename);//综合指数法
	int grey_relational_comprehensive_evaluation(char *filename,char *weight_filename);//灰色关联综合评价法
	int topsis(char *filename,char *weight_filename);//灰色—逼近理想解法
	int osculating_value(char *filename,char *weight_filename);//密切值法

};



/*********************************Comprehensive index method*****************************
                            Enter the file's and weight file's name!
    Input：原始数据阵A[N][M+S],W[N],元素A[i][j]代表第i种方案第j项指标的原始数据！
    Output：F[N]！
*/
int CEvaluation::comprehensive_index(char *filename,char *weight_filename)
{
	FILE *fp,*fq;
	float **A,**W,**F;
	int i,j;
	float sum=0;
	int row=0,column=0;
	char ch;


	//......读入原始数据A......
	if((fp=fopen(filename,"r"))==NULL)//打开文件
	{
		printf("open error\n");
		return 1;
	}


    while(!feof(fp)&&(ch=fgetc(fp))!='\n')//统计列数
		if(ch=='\t')
			column++;
	column++;
	if(column==1)
	{
		printf("no data\n");
		return 1;	
	}
	fseek(fp,0L,0);//置文件首部
	while(!feof(fp))//统计行数
		if(fgetc(fp)=='\n')
			row++;
	row++;
	if(row==1)
	{
		printf("no data\n");
		return 1;	
	}

    A=(float**)malloc(sizeof(float*)*row);//为原始数据矩阵开辟内存
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


	fseek(fp,0L,0);//置文件首部
	while(!feof(fp))//读入数据
	for(i=0;i<row;i++)
		for(j=0;j<column;j++)
			fscanf(fp,"%f,",&A[i][j]);

     
	//......读入原始数据W......
	int column1=0,row1=0;
	if((fq=fopen(weight_filename,"r"))==NULL)//打开文件
	{
		printf("open error\n");
		return 1;
	}


    while(!feof(fq)&&(ch=fgetc(fq))!='\n')//统计列数
		if(ch=='\t')
			column1++;
	column1++;
	if(column1==1)
	{
		printf("no data\n");
		return 1;	
	}
	fseek(fq,0L,0);//置文件首部
	while(!feof(fq))//统计行数
		if(fgetc(fq)=='\n')
			row1++;
		row1++;
	if(row1==0)
	{
		printf("no data\n");
		return 1;	
	}

    W=(float**)malloc(sizeof(float*)*row1);//为原始数据矩阵开辟内存
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


	fseek(fq,0L,0);//置文件首部
	while(!feof(fq))//读入数据
	for(i=0;i<row1;i++)
		for(j=0;j<column1;j++)
			fscanf(fq,"%f,",&W[i][j]);


	if(column!=column1)
	{
		//printf("指标权重输入个数错误！\n");
		AfxMessageBox("指标权重数目与原始数据不匹配！");
		return 1;
	}
	else
	{
		int m=row,n=column;

		F=(float**)malloc(sizeof(float*)*1);//为原始数据矩阵开辟内存
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


		//......要素各指标加权评价法......
		for(i=0;i<m;i++)
		{
			for(j=0;j<n;j++)
				sum+=A[i][j]*W[0][j];
			F[0][i]=sum;
			sum=0;
		}


		//......归一化......
		for(j=0;j<m;j++)
	    	sum+=F[0][j];
	    for(j=0;j<m;j++)
	        F[0][j]=F[0][j]/sum;


		//......显示并存入磁盘......
    	if((fp=fopen("evaluation.txt","w+"))==NULL)//打开文件
		{
	    	printf("open error\n");
	     	return 1;
		}
    	for(i=0;i<1;i++)//输出显示到屏幕并写入文件"weight.txt"
		{
	    	//fprintf(fp,"综合指数法:\t");
	    	for(j=0;j<m;j++)
			{
		    	if(j==m-1)
		     		fprintf(fp,"%f",F[i][j]);
		     	else
			    	fprintf(fp,"%f\t",F[i][j]);
			}
		}
	}

	//......释放内存......
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
    Input：原始数据阵D[M][N],W[N],元素D[i][j]代表第i种方案第j项指标的原始数据！
    Output：各个方案密切值排序R[M]！
*/
int CEvaluation::grey_relational_comprehensive_evaluation(char *filename,char *weight_filename)
{

	FILE *fp,*fq;
	float **D,**W,**C,**E,**R;
	float max,min,sum=0;
	int i,j;
	int row=0,column=0;
	char ch;


	//......读入原始数据D......
	if((fp=fopen(filename,"r"))==NULL)//打开文件
	{
		printf("open error\n");
		return 1;
	}


    while(!feof(fp)&&(ch=fgetc(fp))!='\n')//统计列数
		if(ch=='\t')
			column++;
	column++;
	if(column==1)
	{
		printf("no data\n");
		return 1;	
	}
	fseek(fp,0L,0);//置文件首部
	while(!feof(fp))//统计行数
		if(fgetc(fp)=='\n')
			row++;
	row++;
	if(row==1)
	{
		printf("no data\n");
		return 1;	
	}

    D=(float**)malloc(sizeof(float*)*row);//为原始数据矩阵开辟内存
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


	fseek(fp,0L,0);//置文件首部
	while(!feof(fp))//读入数据
	for(i=0;i<row;i++)
		for(j=0;j<column;j++)
			fscanf(fp,"%f,",&D[i][j]);


	//......读入原始数据W......
	int column1=0,row1=0;
	if((fq=fopen(weight_filename,"r"))==NULL)//打开文件
	{
		printf("open error\n");
		return 1;
	}


    while(!feof(fq)&&(ch=fgetc(fq))!='\n')//统计列数
		if(ch=='\t')
			column1++;
	column1++;
	if(column1==1)
	{
		printf("no data\n");
		return 1;	
	}
	fseek(fq,0L,0);//置文件首部
	while(!feof(fq))//统计行数
		if(fgetc(fq)=='\n')
			row1++;
		row1++;
	if(row1==0)
	{
		printf("no data\n");
		return 1;	
	}

    W=(float**)malloc(sizeof(float*)*row1);//为原始数据矩阵开辟内存
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


	fseek(fq,0L,0);//置文件首部
	while(!feof(fq))//读入数据
	for(i=0;i<row1;i++)
		for(j=0;j<column1;j++)
			fscanf(fq,"%f,",&W[i][j]);


	if(column!=column1)
	{
		//printf("指标权重输入个数错误！\n");
		AfxMessageBox("指标权重数目与原始数据不匹配！");
		return 1;
	}
	else
	{
		int m=row,n=column;


		C=(float**)malloc(sizeof(float*)*row);//为规范化矩阵开辟内存
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

		E=(float**)malloc(sizeof(float*)*(m-1));//为距离矩阵开辟内存
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


		//......按指标进行规范化处理......
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


		//......计算灰色关联系数......
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


		//......计算综合评价结果......
		for(i=0;i<m-1;i++)
		{
			for(j=0;j<n;j++)
				sum+=(W[0][j]*E[i][j]);
			R[0][i]=sum;
			sum=0;
		}


		//......显示输出R并存储......
    	if((fp=fopen("evaluation.txt","w+"))==NULL)
		{
     		printf("open error\n");
	    	return 1;
		}

    	//fprintf(fp,"\n*******灰色关联综合评判法********\n");
		for(i=0;i<1;i++)//输出显示到屏幕并写入文件"weight.txt"
		{
	    	//fprintf(fp,"综合指数法:\t");
	    	for(j=0;j<m-1;j++)
			{
		    	if(j==m-2)
		     		fprintf(fp,"%f",R[i][j]);
		     	else
			    	fprintf(fp,"%f\t",R[i][j]);
			}
		}


     	//......释放内存......
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
    Input：原始数据阵A[M][N],W[N],元素A[i][j]代表第i种方案第j项指标的原始数据！
    Output：各个方案密切值排序C[M]！
*/
int CEvaluation::topsis(char *filename,char *weight_filename)
{
	FILE *fp,*fq;
	float **A,**A1,**A2,**W,**w,**R1,**R2,**d1,**d2,**r1,**r2,**C;
	int i,j;
	float sum=0,sum1=0,sum2=0,max,min;
	int row=0,column=0;
	char ch;


	//......读入原始数据A......
	if((fp=fopen(filename,"r"))==NULL)//打开文件
	{
		printf("open error\n");
		return 1;
	}


    while(!feof(fp)&&(ch=fgetc(fp))!='\n')//统计列数
		if(ch=='\t')
			column++;
	column++;
	if(column==1)
	{
		printf("no data\n");
		return 1;	
	}
	fseek(fp,0L,0);//置文件首部
	while(!feof(fp))//统计行数
		if(fgetc(fp)=='\n')
			row++;
	row++;
	if(row==1)
	{
		printf("no data\n");
		return 1;	
	}

    A=(float**)malloc(sizeof(float*)*row);//为原始数据矩阵开辟内存
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


	fseek(fp,0L,0);//置文件首部
	while(!feof(fp))//读入数据
	for(i=0;i<row;i++)
		for(j=0;j<column;j++)
			fscanf(fp,"%f,",&A[i][j]);

     
	//......读入原始数据W......
	int column1=0,row1=0;
	if((fq=fopen(weight_filename,"r"))==NULL)//打开文件
	{
		printf("open error\n");
		return 1;
	}


    while(!feof(fq)&&(ch=fgetc(fq))!='\n')//统计列数
		if(ch=='\t')
			column1++;
	column1++;
	if(column1==1)
	{
		printf("no data\n");
		return 1;	
	}
	fseek(fq,0L,0);//置文件首部
	while(!feof(fq))//统计行数
		if(fgetc(fq)=='\n')
			row1++;
		row1++;
	if(row1==0)
	{
		printf("no data\n");
		return 1;	
	}

    W=(float**)malloc(sizeof(float*)*row1);//为原始数据矩阵开辟内存
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


	fseek(fq,0L,0);//置文件首部
	while(!feof(fq))//读入数据
	for(i=0;i<row1;i++)
		for(j=0;j<column1;j++)
			fscanf(fq,"%f,",&W[i][j]);


	if(column!=column1)
	{
		//printf("指标权重输入个数错误！\n");
		AfxMessageBox("指标权重数目与原始数据不匹配！");
		return 1;
	}
	else
	{
		int m=row,n=column;

		A1=(float**)malloc(sizeof(float*)*row);//为原始数据矩阵开辟内存
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

		A2=(float**)malloc(sizeof(float*)*row);//为原始数据矩阵开辟内存
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

    	w=(float**)malloc(sizeof(float*)*n);//为权重矩阵开辟内存
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

		d1=(float**)malloc(sizeof(float*)*row);//为原始数据矩阵开辟内存
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

		d2=(float**)malloc(sizeof(float*)*row);//为原始数据矩阵开辟内存
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

	    R1=(float**)malloc(sizeof(float*)*1);//为指标最优最劣向量R1,R2开辟内存
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

	    r1=(float**)malloc(sizeof(float*)*1);//为最优最劣点距向量d1,d2密切值向量C开辟内存
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


		//......求规范决策矩阵并进行无量纲化处理......
    	for(j=0;j<n;j++)
		{
	    	for(i=0;i<m;i++)
	     		sum+=(float)pow(A[i][j],2);
			for(i=0;i<m;i++)
				A[i][j]=(float)(A[i][j]/sqrt(sum));
	    	sum=0;
		}

		/*int flag,k=0;
		printf("评价对象是效益型（0）还是成本型（1）,请选择（0或1）：");
		scanf("%d",&flag);
		while(flag!=0&&flag!=1)
		{
			printf("选择错误，请重新输入：");
			scanf("%d",&flag);
			k++;
			if(k>3)
			{
				printf("输入次数超过三次！");
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


		//......求加权决策矩阵......
	    for(i=0;i<n;i++)//权重矩阵
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


		//......求理想方案与负理想方案......
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


		//......计算各方案与理想方案及负理想方案的灰关联系数及灰关联度......
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


		//......计算相对贴近度......
		for(i=0;i<m;i++)
			C[0][i]=r1[0][i]/(r1[0][i]+r2[0][i]);


		//......显示输出C并存储......
    	if((fp=fopen("evaluation.txt","w+"))==NULL)
		{
     		printf("open error\n");
	    	return 1;
		}

    	//fprintf(fp,"灰色-逼近理想解法:\t");
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


     	//......释放内存......
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
    Input：原始数据阵A[M][N],W[N],元素A[i][j]代表第i种方案第j项指标的原始数据！
	                    *******原始数据为规范化和无量纲转化后的数据**********
    Output：各个方案密切值排序C[M]！
*/
int CEvaluation::osculating_value(char *filename,char *weight_filename)
{
	FILE *fp,*fq;
	float **A,**W,**w,**R,**r1,**R1,**R2,**d1,**d2,**C;
	int i,j,k;
	float sum=0,sum1=0,sum2=0,max,min;
	int row=0,column=0;
	char ch;

	
	//......读入原始数据A......
	if((fp=fopen(filename,"r"))==NULL)//打开文件
	{
		printf("open error\n");
		return 1;
	}


    while(!feof(fp)&&(ch=fgetc(fp))!='\n')//统计列数
		if(ch=='\t')
			column++;
	column++;
	if(column==1)
	{
		printf("no data\n");
		return 1;	
	}
	fseek(fp,0L,0);//置文件首部
	while(!feof(fp))//统计行数
		if(fgetc(fp)=='\n')
			row++;
	row++;
	if(row==1)
	{
		printf("no data\n");
		return 1;	
	}

    A=(float**)malloc(sizeof(float*)*row);//为原始数据矩阵开辟内存
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


	fseek(fp,0L,0);//置文件首部
	while(!feof(fp))//读入数据
	for(i=0;i<row;i++)
		for(j=0;j<column;j++)
			fscanf(fp,"%f,",&A[i][j]);

     
	//......读入原始数据W......
	int column1=0,row1=0;
	if((fq=fopen(weight_filename,"r"))==NULL)//打开文件
	{
		printf("open error\n");
		return 1;
	}


    while(!feof(fq)&&(ch=fgetc(fq))!='\n')//统计列数
		if(ch=='\t')
			column1++;
	column1++;
	if(column1==1)
	{
		printf("no data\n");
		return 1;	
	}
	fseek(fq,0L,0);//置文件首部
	while(!feof(fq))//统计行数
		if(fgetc(fq)=='\n')
			row1++;
		row1++;
	if(row1==0)
	{
		printf("no data\n");
		return 1;	
	}

    W=(float**)malloc(sizeof(float*)*row1);//为原始数据矩阵开辟内存
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


	fseek(fq,0L,0);//置文件首部
	while(!feof(fq))//读入数据
	for(i=0;i<row1;i++)
		for(j=0;j<column1;j++)
			fscanf(fq,"%f,",&W[i][j]);


    if(column!=column1)
	{
		//printf("指标权重个数输入错误！\n");
		AfxMessageBox("指标权重数目与原始数据不匹配！");
		return 1;
	}
	else
	{
    	//......为w,R,R1,R2,d1,d2,C分配动态内存......
    	int m=row,n=column;
    	w=(float**)malloc(sizeof(float*)*n);//为权重矩阵开辟内存
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

    	r1=(float**)malloc(sizeof(float*)*m);//为规范化矩阵开辟内存
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

	    R=(float**)malloc(sizeof(float*)*m);//为规范化矩阵开辟内存
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

	    R1=(float**)malloc(sizeof(float*)*1);//为指标最优最劣向量R1,R2开辟内存
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

	    d1=(float**)malloc(sizeof(float*)*1);//为最优最劣点距向量d1,d2密切值向量C开辟内存
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
		
        
     	//......权重矩阵......
	    for(i=0;i<n;i++)
		{
	    	for(j=0;j<n;j++)
	     		w[i][j]=0;
	    	w[i][i]=W[0][i];
		}

		
	    //......求规范化指标矩阵R......
    	for(j=0;j<n;j++)
		{
	    	for(i=0;i<m;i++)
	     		sum+=(float)pow(A[i][j],2);
			for(i=0;i<m;i++)
				r1[i][j]=(float)(A[i][j]/sqrt(sum));
	    	sum=0;
		}
		

     	//......求权规范化矩阵......
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


    	//......求指标最优最劣向量R1,R2......
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


	    //......求最优最劣点距离向量及密切值向量并根据密切值对方案进行排序......
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


     	//......显示输出C并存储......
    	if((fp=fopen("evaluation.txt","w+"))==NULL)
		{
     		printf("open error\n");
	    	return 1;
		}

    	//fprintf(fp,"密切值法:\t");
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

     	//......释放内存......
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
