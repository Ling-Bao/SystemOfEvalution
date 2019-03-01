#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"iostream.h"


//定义评价函数类
class CWeight
{
public:
	//主观赋权法
	int entropy_weight(char *filename);//熵值法
	int grey_correlation_degree(char *filename);//灰色关联度法
	int variance_coefficient(char *filename);//变异系数法
	int multi_objective_optimization(char *filename);//多目标优化法
	int multiple_correlation_coefficient(char *filename);//复相关系数法
	int multiple_weight(char *filename);//乘法加权组合法
	int linear_weight(char *filename);//线性加权组合法
	int critic(char *filename);
	int improved_entropy_weight(char *filename);//改进熵权法
	//客观赋权法
	int expert(char *filename);//专家打分法
	int AHP(char *filename);//层次分析法
	int contrast_compositor(char *filename);//对比排序法
	int PC(char *filename);//优序图法
};


/*********************************Entropy weight method*****************************
                                  Enter the file's name!
    Input：原始数据阵X[M][N]，元素X[i][j]代表第i种方案第j项指标的原始数据！
    Output：指标的权向量W！
*/
int CWeight::entropy_weight(char *filename)
{
	//......读入原始数据......
	FILE *fp;
    float  **W,**x;//定义二维数组
    int  i,j;
	int  row=0,column=0;//行，列
    char ch;


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


	W=(float**)malloc(sizeof(float*));//为权重向量开辟内存
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
    x=(float**)malloc(sizeof(float*)*row);//为原始数据矩阵开辟内存
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


	fseek(fp,0L,0);//置文件首部
	while(!feof(fp))//读入数据
	for(i=0;i<row;i++)
		for(j=0;j<column;j++)
			fscanf(fp,"%f,",&x[i][j]);


	//......求比重矩阵......
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


	//......求熵向量->偏差度->客观权重......
	for(j=0;j<n;j++)//熵向量->偏差度
	{
		for(i=0;i<m;i++)
			if(x[i][j])
			{
				sum+=K*x[i][j]*(float)log(x[i][j]);
			}
		W[0][j]=1-sum;
		sum=0;
	}
	for(j=0;j<n;j++)//->客观权向量
		sum+=W[0][j];
	for(j=0;j<n;j++)
		W[0][j]=W[0][j]/sum;


	//......显示并存入磁盘......
	if((fp=fopen("weight.txt","w+"))==NULL)//打开文件
	{
		printf("open error\n");
		return 1;
	}
	for(i=0;i<1;i++)//输出显示到屏幕并写入文件"weight.txt"
	{
		//fprintf(fp,"熵值法:\t");
		for(j=0;j<n;j++)
		{
			if(j==column-1)
				fprintf(fp,"%f",W[i][j]);
			else
				fprintf(fp,"%f\t",W[i][j]);
		}
	}

	//......释放内存......
	fclose(fp);//关闭文件
	for(i=0;i<row;i++)
		free(x[i]);
	free(x);
	free(W[0]);
	free(W);
	return 0;
}



/************************Grey correlation degree method************************
                            Enter the file's name!
    Input：原始数据阵第0行为“公共”参考权值；
	       原始数据阵X[N][M]，元素X[i][j]指，第i个专家对第j评价指标的评分！
	Output：决策指标的权重值W[2][N-1]
	        W[0][j]指理论Grey correlation degree weight；
			W[1][j]指修正Grey correlation degree weight！
*/
#define r 0.5
int CWeight::grey_correlation_degree(char *filename)
{
	//......读入原始数据......
	FILE *fp;
    float  **W,**x,**d;//定义二维数组
    int  i,j;
	int  row=0,column=0;//行，列
    char ch;


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


	W=(float**)malloc(sizeof(float*)*2);//为权重向量开辟内存
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

    x=(float**)malloc(sizeof(float*)*row);//为原始数据矩阵开辟内存
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
	fseek(fp,0L,0);//置文件首部
	while(!feof(fp))//读入数据
	for(i=0;i<row;i++)
		for(j=0;j<column;j++)
			fscanf(fp,"%f,",&x[i][j]);

	d=(float**)malloc(sizeof(float*)*row);//为距离矩阵开辟内存
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

	
	//......将原始矩阵均值化......
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


	//......求差序列......
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


	//......关联系数和关联度......
	for(j=1;j<m;j++) //i=1，第一列为“公共”参考权值
	{
		for(i=0;i<n;i++)
			sum+=(float)((min+r*max)/(d[i][j]+r*max));
		W[0][j-1]=sum/m;
		sum=0;
	}

	
	//......权向量归一化处理......
	for(j=0;j<m-1;j++)
			sum+=W[0][j];
	for(j=0;j<m-1;j++)
		W[0][j]=W[0][j]/sum;

	
	//......灰色关联度权重确定改进方法......
	sum=0;
	for(j=1;j<m;j++)
	{
		for(i=1;i<n;i++)
			sum+=(float)pow((x[0][j]-x[i][j]),2);
		W[1][j-1]=1/(sum+1);
		sum=0;
	}


	//......权向量及其归一化处理......
	for(j=0;j<m-1;j++)
			sum+=W[1][j];
	for(j=0;j<m-1;j++)
		W[1][j]=W[1][j]/sum;


	//......显示并存入磁盘weight.txt......
	if((fp=fopen("weight.txt","w+"))==NULL)//打开文件
	{
		printf("open error\n");
		return 1;
	}
	for(i=0;i<1/*2*/;i++)//输出显示到屏幕并写如文件"Grey_correlation_degree_weight.txt"
	{
		for(j=0;j<m-1;j++)
		{
			if(j==m-2)
				fprintf(fp,"%f",W[i][j]);
			else
				fprintf(fp,"%f\t",W[i][j]);
		}
	}


	//......释放内存......
    fclose(fp);//关闭文件
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
    Input：原始数据阵X[M][N]，元素X[i][j]代表第i个对象第j项分类指标的原始数据！
    Output：指标的权向量W[N]！
*/
int CWeight::variance_coefficient(char *filename)
{
	FILE *fp;
    float  **W,**x,**x0,**s;//定义二维数组
    int  i,j;
	int  row=0,column=0;//行，列
    char ch;


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

    x=(float**)malloc(sizeof(float*)*row);//为原始数据矩阵x开辟内存
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


	//从filename.txt中读取数据
	fseek(fp,0L,0);//置文件首部
	while(!feof(fp))//读入数据
	for(i=0;i<row;i++)
		for(j=0;j<column;j++)
			fscanf(fp,"%f,",&x[i][j]);

	W=(float **)malloc(sizeof(float *)*1);//为权重开辟内存
	x0=(float **)malloc(sizeof(float *)*1);//为均值开辟内存
	s=(float **)malloc(sizeof(float *)*1);//为标准差开辟内存
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


	//求各指标均值和标准差
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


	//计算各指标变异系数（变异系数作为权重）及其归一化处理
	for(j=0;j<m;j++)
	{
		W[0][j]=s[0][j]/x0[0][j];
		sum+=W[0][j];
	}
	for(j=0;j<m;j++)
		W[0][j]=W[0][j]/sum;


	//......显示并存入磁盘......
	if((fp=fopen("weight.txt","w+"))==NULL)//打开文件
	{
		printf("open error\n");
		return 1;
	}
	for(i=0;i<1;i++)//输出显示到屏幕并写入文件"weight.txt"
	{
		//fprintf(fp,"变异系数法:\t");
		for(j=0;j<m;j++)
		{
			if(j==column-1)
				fprintf(fp,"%f",W[i][j]);
			else
				fprintf(fp,"%f\t",W[i][j]);
		}
	}


	//......释放内存......
	fclose(fp);//关闭文件
	for(i=0;i<row;i++)
		free(x[i]);
	free(x);
	free(W[0]),free(x0[0]),free(s[0]);
	free(W),free(x0),free(s);
	return 0;
}



/*********************************Multi objective optimization method*****************************
                                      Enter the file's name!
    Input：原始数据阵X[M][N]，元素X[i][j]代表第i个对象第j项分类指标的原始数据！
    Output：指标的权向量W[N]！
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

	x=(float**)malloc(sizeof(float*)*row);//为原始数据矩阵x开辟内存
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


	//......从filename.txt中读取数据......
	fseek(fp,0L,0);
	while(!feof(fp))
		for(i=0;i<row;i++)
			for(j=0;j<column;j++)
				fscanf(fp,"%f,",&x[i][j]);


	W=(float**)malloc(sizeof(float*)*1);//为权重向量分配内存W
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


	//......求决策矩阵A的规范化矩阵Z......
	int m=row,n=column;

	for(j=0;j<n;j++)
	{
		for(i=0;i<m;i++)
			sum+=x[i][j];
		for(i=0;i<m;i++)
			x[i][j]=x[i][j]/sum;
		sum=0;
	}


	//......求最优化权重......
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

	
	//......W标准化......
	for(j=0;j<n;j++)
		sum+=W[0][j];
	for(j=0;j<n;j++)
		W[0][j]=W[0][j]/sum;


	//......显示输出W并存储......
	if((fp=fopen("weight.txt","w+"))==NULL)
	{
		printf("open error\n");
		return 1;
	}

	//fprintf(fp,"多目标优化法:\t");
	for(j=0;j<n;j++)
	{
		if(j==column-1)
			fprintf(fp,"%f",W[0][j]);
		else
			fprintf(fp,"%f\t",W[0][j]);
	}


	//......释放内存......
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
    Input：原始数据阵X[M][N]，元素X[i][j]代表第i个对象第j项分类指标的原始数据！
    Output：指标的权向量W[N]！
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


	if((fp=fopen(filename,"r"))==NULL)//打开文件
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


	//......开辟动态内存......
	x=(float**)malloc(sizeof(float*)*row);//为原始数据矩阵x开辟内存
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

	W=(float**)malloc(sizeof(float*)*1);//为权重向量分配内存W
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

	R=(float**)malloc(sizeof(float*)*column);//为相关系数矩阵R开辟内存
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

	R1=(float**)malloc(sizeof(float*)*(column-1));//为矩阵R1开辟内存
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

	r1=(float**)malloc(sizeof(float*)*1);//开辟内存
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


	//......从filename.txt中读取数据......
	fseek(fp,0L,0);
	while(!feof(fp))
		for(i=0;i<row;i++)
			for(j=0;j<column;j++)
				fscanf(fp,"%f,",&x[i][j]);


	//......求各指标的相关系数矩阵......
	int m=row,n=column;
	float average,sumsd=0,variance;//sumsd为sum of squares of deviation(离差平方和）

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


	//......计算各个指标与其他指标的相关系数......
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


	//......权值W归一化处理......
	for(j=0;j<n;j++)
		sum+=(float)1./W[0][j];
	for(j=0;j<n;j++)
		W[0][j]=(float)1./(W[0][j]*sum);


	//......显示输出W......
	if((fp=fopen("weight.txt","w+"))==NULL)
	{
		printf("open error\n");
		return 1;
	}

	//fprintf(fp,"复相关系数法:\t");
	for(j=0;j<n;j++)
	{
		if(j==column-1)
			fprintf(fp,"%f",W[0][j]);
		else
			fprintf(fp,"%f\t",W[0][j]);
	}


	//......释放内存......
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
    Input：原始数据阵X[M][N]，元素X[i][j]代表第i种方法第j项指标的原始数据！
    Output：指标的权向量W[N]！
*/
int CWeight::multiple_weight(char *filename)
{
	FILE *fp;
	float **x,**W;
	int i,j,row=0,column=0;
	float sum=0,multiple=1;
	char ch;

	if((fp=fopen(filename,"r"))==NULL)//打开文件
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

	//......开辟动态内存......
	x=(float**)malloc(sizeof(float*)*row);//为原始数据矩阵x开辟内存
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

	W=(float**)malloc(sizeof(float*)*1);//为权重向量分配内存W
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


	//......从filename.txt中读取数据......
	fseek(fp,0L,0);
	while(!feof(fp))
		for(i=0;i<row;i++)
			for(j=0;j<column;j++)
				fscanf(fp,"%f,",&x[i][j]);


	//......乘法加权组合求权值......
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


	//......权值W归一化处理......
	sum=0;
	for(j=0;j<n;j++)
		sum+=W[0][j];
	for(j=0;j<n;j++)
		W[0][j]=W[0][j]/sum;


	//......显示输出W......
	if((fp=fopen("weight.txt","w+"))==NULL)
	{
		printf("open error\n");
		return 1;
	}

	//fprintf(fp,"乘法加权组合法:\t");
	for(j=0;j<n;j++)
	{
		if(j==column-1)
			fprintf(fp,"%f",W[0][j]);
		else
			fprintf(fp,"%f\t",W[0][j]);
	}


	//......释放内存......
	fclose(fp);
	free(W);
	for(i=0;i<m;i++)
		free(x[i]);
	free(x);
	return 0;
}



/*********************************The linear weighted assignment method*****************************
                                         Enter the file's name!
    Input：原始数据阵X[M][N]，元素X[i][j]代表第i种方法第j项指标的原始数据！
    Output：指标的权向量W[N]！
*/
int CWeight::linear_weight(char *filename)
{
	FILE *fp;
	float **x,**w,**W1,**W;
	int i,j,k;
	float sum=0,max;
	int row=0,column=0;
	char ch;


	if((fp=fopen(filename,"r"))==NULL)//打开文件
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

	//......开辟动态内存......
	x=(float**)malloc(sizeof(float*)*row);//为原始数据矩阵x开辟内存
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

	w=(float**)malloc(sizeof(float*)*row);//为原始数据矩阵x开辟内存
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

	W1=(float**)malloc(sizeof(float*)*1);//为权重向量分配内存W
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

	W=(float**)malloc(sizeof(float*)*1);//为权重向量分配内存W
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


	//......从filename.txt中读取数据......
	fseek(fp,0L,0);
	while(!feof(fp))
		for(i=0;i<row;i++)
			for(j=0;j<column;j++)
				fscanf(fp,"%f,",&x[i][j]);


    //......求spearman等级相关系数矩阵w......
	int m=row,n=column;
	for(i=0;i<m;i++)
		for(k=0;k<m;k++)
		{
			for(j=0;j<n;j++)
				sum+=(float)pow((x[i][j]-x[k][j]),2);
			w[i][k]=1-6*sum/(n*(n-1));
			sum=0;
		}


	//......确定最大关联系数......
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


	//......求方法权向量及其归一化......
	for(j=0;j<m;j++)//寻找一致性最高的赋值方法
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

	for(j=0;j<m;j++)//标准化赋值方法的权值
		sum+=W1[0][j];
	for(j=0;j<m;j++)
		W1[0][j]=W1[0][j]/sum;


	//......求综合权重W及其归一化......
	sum=0;
	for(j=0;j<n;j++)
	{
		for(i=0;i<m;i++)
			sum+=W1[0][i]*x[i][j];
		W[0][j]=sum;
		sum=0;
	}

	for(j=0;j<n;j++)//标准化综合权重
		sum+=W[0][j];
	for(j=0;j<n;j++)
		W[0][j]=W[0][j]/sum;


	//......显示输出W......
	if((fp=fopen("weight.txt","w+"))==NULL)
	{
		printf("open error\n");
		return 1;
	}

	//fprintf(fp,"线性加权组合法:\t");
	for(j=0;j<n;j++)
	{
		if(j==column-1)
			fprintf(fp,"%f",W[0][j]);
		else
			fprintf(fp,"%f\t",W[0][j]);
	}


	//......释放内存......
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
    Input：原始数据阵X[M][N]，元素X[i][j]代表第i种方法第j项指标的原始数据！
    Output：指标的权向量W[N]！
*/
int CWeight::critic(char *filename)
{
	FILE *fp;
	float **x,**R,**B,**W;
	int i,j,k;
	float sum=0;
	int row=0,column=0;
	char ch;


	if((fp=fopen(filename,"r"))==NULL)//打开文件
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

	//......开辟动态内存......
	x=(float**)malloc(sizeof(float*)*row);//为原始数据矩阵x开辟内存
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

	R=(float**)malloc(sizeof(float*)*column);//为相关系数矩阵R开辟内存
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

	B=(float**)malloc(sizeof(float*)*1);//为原始数据矩阵x开辟内存
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

	//......从filename.txt中读取数据......
	fseek(fp,0L,0);
	while(!feof(fp))
		for(i=0;i<row;i++)
			for(j=0;j<column;j++)
				fscanf(fp,"%f,",&x[i][j]);


	//......求各指标的相关系数矩阵......
	int m=row,n=column;
	float average,sumsd=0,variance;//sumsd为sum of squares of deviation(离差平方和）

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



	//......计算量化指标......
	for(j=0;j<n;j++)
	{
		for(i=0;i<n;i++)
			sum+=(1-R[i][j]);
		B[0][j]=sum;
		sum=0;
	}


	//......计算信息量......
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

	//......权重归一化......
	for(j=0;j<n;j++)
		sum+=W[0][j];
	for(j=0;j<n;j++)
		W[0][j]=W[0][j]/sum;



	//......显示输出W......
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


	//......释放内存......
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
    Input：原始数据阵X[M][N]，元素X[i][j]代表第i种方案第j项指标的原始数据！
    Output：指标的权向量W！
*/
int CWeight::improved_entropy_weight(char *filename)
{
	//......读入原始数据......
	FILE *fp;
    float  **W,**x;//定义二维数组
    int  i,j;
	int  row=0,column=0;//行，列
    char ch;


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


	W=(float**)malloc(sizeof(float*));//为权重向量开辟内存
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
    x=(float**)malloc(sizeof(float*)*row);//为原始数据矩阵开辟内存
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


	fseek(fp,0L,0);//置文件首部
	while(!feof(fp))//读入数据
	for(i=0;i<row;i++)
		for(j=0;j<column;j++)
			fscanf(fp,"%f,",&x[i][j]);


	//......求比重矩阵......
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


	//......求熵向量->偏差度->客观权重......
	for(j=0;j<n;j++)//熵向量->偏差度
	{
		for(i=0;i<m;i++)
			if(x[i][j])
			{
				sum+=(-K*x[i][j]*(float)log(x[i][j]));
			}
		W[0][j]=1-sum;
		sum=0;
	}
	for(j=0;j<n;j++)//->客观权向量
		sum+=W[0][j];
	for(j=0;j<n;j++)
		W[0][j]=W[0][j]/sum;
	

	//......熵权修正......
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
		//printf("熵权修正次数已超过%d次！",10);
		AfxMessageBox("熵权修正次数已超过10次！");
		return 1;
	}


	//......显示并存入磁盘......
	if((fp=fopen("weight.txt","w+"))==NULL)//打开文件
	{
		printf("open error\n");
		return 1;
	}
	for(i=0;i<1;i++)//输出显示到屏幕并写入文件"weight.txt"
	{
		//fprintf(fp,"改进熵值法:\t");
		for(j=0;j<n;j++)
		{
			if(j==column-1)
				fprintf(fp,"%f",W[i][j]);
			else
				fprintf(fp,"%f\t",W[i][j]);
		}
	}


	//......释放内存......
	fclose(fp);//关闭文件
	for(i=0;i<row;i++)
		free(x[i]);
	free(x);
	free(W[0]);
	free(W);
	return 0;
}




/*********************************The expert scoring method*****************************
                                    Enter the file's name!
    Input：原始数据阵A[M][N]，元素A[i][j]代表第i个专家对第j个指标的评分！
    Output：指标的权向量W[N]！
*/
int CWeight::expert(char *filename)
{
	FILE *fp;
	float **A,**D,**aver,**v,**ka,sum=0;
	int i,j;
	int row=0,column=0;
	char ch;


	if((fp=fopen(filename,"r"))==NULL)//打开文件
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

	//......开辟动态内存......
	A=(float**)malloc(sizeof(float*)*row);//为原始数据矩阵x开辟内存
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

	D=(float**)malloc(sizeof(float*)*row);//为原始数据矩阵x开辟内存
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


	//......从filename.txt中读取数据......
	fseek(fp,0L,0);
	while(!feof(fp))
		for(i=0;i<row;i++)
			for(j=0;j<column;j++)
				fscanf(fp,"%f,",&A[i][j]);


	//......归一化处理......
	int m=row,n=column;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
			sum+=A[i][j];
		for(j=0;j<n;j++)
			A[i][j]=A[i][j]/sum;
		sum=0;
	}


	//......计算指标平均值......
	for(j=0;j<n;j++)
	{
		for(i=0;i<m;i++)
			sum+=A[i][j];
		aver[0][j]=sum/m;
		sum=0;
	}


	//......计算离差......
	for(j=0;j<n;j++)
	{
		for(i=0;i<m;i++)
			D[i][j]=(A[i][j]-aver[0][j]);
	}


	//......计算分歧程度......
	for(j=0;j<n;j++)
	{
		for(i=0;i<m;i++)
			sum+=(float)pow((D[i][j]),2);
		v[0][j]=(float)sqrt(sum/(m-1));
		sum=0;
	}

	for(j=0;j<n;j++)
		ka[0][j]=v[0][j]/aver[0][j];


	//......打开并写入权重文件......
	if((fp=fopen("weight.txt","w+"))==NULL)
	{
		printf("open error\n");
		return 1;
	}

	//......分歧程度判断......
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
		AfxMessageBox("专家们确定的权重系数值较为离散，缺乏统一性和可靠性,请重新进行专家评价！");
		AfxMessageBox("点击系统界面上的确定以了解不一致指标(1代表不一致指标，2代表一致性指标)！");
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


	//......释放内存......
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
    Input：原始数据阵A[M][N]，元素A[i][j]代表第i个专家对第j个指标的评分！
    Output：指标的权向量W[N]！
*/
int CWeight::AHP(char *filename)
{
	
	FILE *fp;
	float **A,**W;
	int i,j;
	int row=0,column=0;
	char ch;


	if((fp=fopen(filename,"r"))==NULL)//打开文件
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
		AfxMessageBox("判断矩阵行列不相等！\n");
		return 1;
	}

	//......开辟动态内存......
	A=(float**)malloc(sizeof(float*)*row);//为原始数据矩阵x开辟内存
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

	W=(float**)malloc(sizeof(float*)*1);//为权重向量W开辟内存
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
		AfxMessageBox("判断矩阵维数一般最大为15!\n");
		return 1;
	}


	//......从filename.txt中读取数据......
	fseek(fp,0L,0);
	while(!feof(fp))
	{
		for(i=0;i<row;i++)
			for(j=0;j<column;j++)
				fscanf(fp,"%f,",&A[i][j]);
	}


	//......输入最大特征lambda和最大特征值对应的特征向量......
	float **U,lambda,sum=0,sumM=1;
	int m=row,n=column;


	//......分配内存......
	U=(float**)malloc(sizeof(float*)*1);//为权重向量U开辟内存
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

	//计算特征值
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


	//计算特征值
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

	//计算最大特征值
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



	//......用数组RI[15]存储不同维度对应的RI值......
	float RI[15]={0,0,0.58,0.90,1.12,1.24,1.32,1.41,1.45,1.49,1.52,1.54,1.56,1.58,1.59};


	//......计算最大特征值及一致性检验......
	float CI,CR;
	int flag,flag0,l=0;
	CI=(lambda-n)/(n-1);
	CR=CI/RI[n];
	if(CR<0.10)
	{
		//......显示并存入磁盘......
    	if((fp=fopen("weight.txt","w+"))==NULL)//打开文件
		{
     		printf("open error\n");
	    	return 1;
		}
		//输出显示到屏幕并写入文件"weight.txt"
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
		AfxMessageBox("一致性检验失败！");
	}


	//......释放内存......
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
    Input：原始数据阵A[M][N]，元素A[i][j]代表第i个专家对第j个指标的评分！
    Output：指标的权向量W[N]！
*/
int CWeight::contrast_compositor(char *filename)
{
	AfxMessageBox("各指标对目标层的权重可以基于各评判矩阵求得，具体请详见层次分析算法！");

	FILE *fp;
	float **A,**W;
	int i,j;
	int row=0,column=0;
	char ch;


	if((fp=fopen(filename,"r"))==NULL)//打开文件
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

	//......开辟动态内存......
	A=(float**)malloc(sizeof(float*)*row);//为原始数据矩阵x开辟内存
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

	W=(float**)malloc(sizeof(float*)*1);//为权重向量W开辟内存
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


	//......从filename.txt中读取数据......
	fseek(fp,0L,0);
	while(!feof(fp))
	{
		for(i=0;i<row;i++)
			for(j=0;j<column;j++)
				fscanf(fp,"%f,",&A[i][j]);
	}


	//......计算各指标权重......
	int m=row,n=column;
	float sum=0;
	for(j=0;j<n;j++)
	{
		for(i=0;i<m;i++)
			sum+=(float)(log(A[i][j])/log(n));
		W[0][j]=sum/m;
		sum=0;
	}


	//......归一化......
	for(j=0;j<n;j++)
		sum+=W[0][j];
	for(j=0;j<n;j++)
	    W[0][j]=W[0][j]/sum;



	//......显示并存入磁盘......
	if((fp=fopen("weight.txt","w+"))==NULL)//打开文件
	{
		printf("open error\n");
		return 1;
	}
	for(i=0;i<1;i++)//输出显示到屏幕并写入文件"weight.txt"
	{
		//fprintf(fp,"对比排序法:\t");
		for(j=0;j<n;j++)
		{
			if(j==n-1)
				fprintf(fp,"%f",W[i][j]);
			else
				fprintf(fp,"%f\t",W[i][j]);
		}
	}


	//......释放内存......
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
    Input：原始数据阵A[M][N]，元素A[i][j]代表第i个专家对第j个指标的评分！
    Output：指标的权向量W[N]！
*/
int CWeight::PC(char *filename)
{
	FILE *fp;
	float **A,**W;
	int i,j;
	int row=0,column=0;
	char ch;


	if((fp=fopen(filename,"r"))==NULL)//打开文件
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

	//......开辟动态内存......
	A=(float**)malloc(sizeof(float*)*row);//为原始数据矩阵x开辟内存
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

	W=(float**)malloc(sizeof(float*)*1);//为权重向量W开辟内存
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


	//......从filename.txt中读取数据......
	fseek(fp,0L,0);
	while(!feof(fp))
	{
		for(i=0;i<row;i++)
			for(j=0;j<column;j++)
				fscanf(fp,"%f,",&A[i][j]);
	}

	if(row!=column)
	{
		AfxMessageBox("原始数据行列不相等！");
		return 1;
	}


	//......互补检验......
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

	//......显示并存入磁盘......
	if((fp=fopen("weight.txt","w+"))==NULL)//打开文件
	{
		printf("open error\n");
		return 1;
	}


	if(flag==0)
	{
		//fprintf(fp,"互补检验成功！\n")
		AfxMessageBox("互补检验成功！");

		//......计算各指标权重......
    	float sum=0,T;
    	T=(float)(n-1)*n/2;
    	for(i=0;i<n;i++)
		{
	    	for(j=0;j<m;j++)
		    	sum+=A[i][j];
    		W[0][i]=sum/T;
    		sum=0;
		}


    	//......归一化......
    	for(j=0;j<n;j++)
	    	sum+=W[0][j];
    	for(j=0;j<n;j++)
	        W[0][j]=W[0][j]/sum;


    	for(i=0;i<1;i++)//输出显示到屏幕并写入文件"weight.txt"
		{
    		//fprintf(fp,"对比排序法:\t");
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
		//fprintf(fp,"互补检验失败！\n");
		AfxMessageBox("互补检验失败！");
		return 1;
	}


	//......释放内存......
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