#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
 
#define False 0
#define True 1

int s,c;
int *Request,*Available,*Work,*Finish,*Security;
int **Max,**Allocation,**Need;
char *NAME;
 
void FormatR()
{
  Request=(int *)malloc(s * sizeof(int));
  Available=(int *)malloc(s * sizeof(int));
  Work=(int *)malloc(s * sizeof(int));
}
void FromatC()
{
    int i;
    Max=(int **)malloc(sizeof(int *) * c);
    for(i=0;i<c;i++)
    {
        Max[i]=(int *)malloc(sizeof(int) * s);
    }
    Allocation=(int **)malloc(sizeof(int *) * c);
    for(i=0;i<c;i++)
    {
        Allocation[i]=(int *)malloc(sizeof(int) * s);
    }
    Need=(int **)malloc(sizeof(int *) * c);
    for(i=0;i<c;i++)
    {
        Need[i]=(int *)malloc(sizeof(int) * s);
    }
    NAME=(char *)malloc(s * sizeof(char));
    Finish=(int *)malloc(s * sizeof(int));
    Security=(int *)malloc(s * sizeof(int));
}
/********初始化数据：输入进程数量、资源种类、各种资源可利用数量、
各进程对资源最大需求量、各进程的资源已分配数量等。********/
void init()
{
	/* c为进程个数，即矩阵行数，s为资源种类，即矩阵列数。*/
    int i,j,S,C;
	int number,flag;
	char name;//输入资源名称
	//输入系统资源数目及各资源初试个数 
    printf("银行可贷款项目数：");
	scanf("%d",&S);
	s=S;
	FormatR();	
	//输入进程数及各进程的最大需求矩阵 
    printf("将有几家企业需要贷款:");	
	scanf("%d",&C);
	c=C;
    FromatC();
	  for(i=0;i<s;i++)
	{
		printf("资源%d的名称:",i+1);
		fflush(stdin);  //清空输入流缓冲区的字符，注意必须引入#include<stdlib.h>头文件
		scanf("%c",&name);
		NAME[i]=name;
		printf("资源%c的初始个数为:",name);	
		scanf("%d",&number);
		Available[i]=number;
	}
		for(i=0;i<c;i++)
		{
			printf("----------------------------------------\n");
			for(j=0;j<s;j++)
			{
				do{
					    flag = False;
				        printf("企业%d的%c类型贷款所需贷款金额：",i+1,NAME[j]);//N=s；M=c；
			        	scanf("%d",&Max[i][j]);
						Need[i][j]=Max[i][j];
				        if(Max[i][j]>Available[j])
						{
							flag = True;
                            printf("所设金额超过银行最大贷款限度%d，请重新设置贷款金额：",Available[j]);
						}
				}while(flag);
			}
			printf("----------------------------------------\n");
		}								

			
	//输入各进程已经分配的资源量，并求得还需要的资源量 
		for(i=0;i<c;i++)
		{
						printf("----------------------------------------\n");
			for(j=0;j<s;j++)
		  	{
			  do{
		            flag=False;
				    printf("请输入您将为企业%d的第%c种贷款类型分配的资金：",i+1,NAME[j]);
				    scanf("%d",&Allocation[i][j]);
				    if(Allocation[i][j]>Need[i][j]&&Allocation[i][j]>Available[j])  
					{
						flag=True;				
						printf("设置的金额超出金额分配最大数值，请重新设置金额。");
						printf("\n");
						printf("企业%d的%c类贷款金额还需要%d，现银行对该贷款类型还可分配的金额为%d。",i+1,NAME[j],Need[i][j],Available[j]);
						printf("\n");
					}
					else
					{
						Need[i][j]=Need[i][j]-Allocation[i][j];
						Available[j]=Available[j]-Allocation[i][j];
					}
			  }while(flag);
		  	}
						printf("----------------------------------------\n");
		}
}
 
/********显示资源分配矩阵********/
void showdata()
{
	int i,j;
	printf("*************************************************************\n");
	printf("银行目前可分配的资源:\n");
	for(i=0;i<s;i++)
        printf("    %c    ",NAME[i]);
	printf("\n");
	for(j=0;j<s;j++)
        printf("    %d    ",Available[j]);
	printf("\n");
	printf("银行当前的资源分配情况如下：\n");
	printf("                  企业总贷款   	          现已分配贷款            企业还需要贷款数\n");
	printf("贷款类型:          ");
	//输出与进程名同行的资源名，Max、Allocation、Need下分别对应 
	for(j=0;j<3;j++){
		for(i=0;i<s;i++)
			printf("%c        ",NAME[i]);
		printf("     ");
	}
	printf("\n");
	//输出每个进程的Max、Allocation、Need 
	for(i=0;i<c;i++)
	{
		printf(" 企业%d：           ",i+1);
        for(j=0;j<s;j++)
			printf("%d        ",Max[i][j]);
		printf("     "); 
		for(j=0;j<s;j++)
			printf("%d        ",Allocation[i][j]);
		printf("     "); 
		for(j=0;j<s;j++)
			printf("%d        ",Need[i][j]);
		printf("\n");
	}
}
 
/********尝试分配资源********/
int test(int i) //试探性的将资源分配给第i个进程 
{ 
	for(int j=0;j<s;j++)
	{
		Available[j]=Available[j]-Request[j];
		Allocation[i][j]=Allocation[i][j]+Request[j];
		Need[i][j]=Need[i][j]-Request[j];
	}
	return True;
}
 
/********试探性分配资源作废********/
int Retest(int i) //与test操作相反 
{ 
	for(int j=0; j<s; j++)
	{
		Available[j] = Available[j] + Request[j];
		Allocation[i][j] = Allocation[i][j] - Request[j];
		Need[i][j] = Need[i][j] + Request[j];
	}
	return True;
}
 
/********安全性算法********/
int safe()
{
	int i,j,k=0,m,apply;
	//初始化work 
	for(j=0;j<s;j++)
        Work[j] = Available[j];
    //初始化Finish 
    for(i=0;i<c;i++) 
    	Finish[i] = False;
	//求安全序列 
	for(i=0;i<c;i++){ 
		apply=0;
		for(j=0;j<s;j++){
			if(Finish[i]==False && Need[i][j]<=Work[j])
			{   
				apply++;
				//直到每类资源尚需数都小于系统可利用资源数才可分配
				if(apply==s)
				{  
					for(m=0;m<s;m++)
				        Work[m]=Work[m]+Allocation[i][m];//更改当前可分配资源
					Finish[i]=True;
					Security[k++]=i;
					i=-1; //保证每次查询均从第一个进程开始		
				}
			}
		}
	}
	
	for(i=0;i<c;i++){
		if(Finish[i]==False){
			printf("系统不安全\n");//不成功系统不安全
			return False;
		}
	}
    printf("系统是安全的!\n");//如果安全，输出成功
    printf("存在一个安全序列:");
	for(i=0;i<c;i++){//输出运行进程数组
		printf("P%d",Security[i]);
		if(i<c-1) 
			printf("->");
	}
	printf("\n");
	return True;
}
 
/********利用银行家算法对申请资源进行试分********/
void bank()
{
	int flag = True;//标志变量，判断能否进入银行家算法的下一步 
	int i,j;
 
	printf("请选择你想要分配的企业(1-%d):",c); 
    scanf("%d",&i);//输入须申请资源的进程号
	printf("现银行还可分配的资金：");
	for(j=0;j<s;j++)
		printf("%c:%3d",NAME[j],Available[j]);
	printf("\n");
	printf("请输入您将为企业%d分配的资金：\n",i);
	i-=1;
	for(j=0;j<s;j++)
	{
		printf("%c:",NAME[j]);
		scanf("%d",&Request[j]);//输入需要申请的资源
	}
	
	//判断银行家算法的前两条件是否成立 
    for (j=0;j<s;j++)
	{
		if(Request[j]>Need[i][j])//判断申请是否大于需求，若大于则出错
		{
			printf("%d\n",i);
			printf("企业%d分配的资金大于它需要的贷款\n",i+1);
			printf("分配不合理，不予分配！\n");
			flag = False;
			break;
		}
		else 
		{
            if(Request[j]>Available[j])//判断申请是否大于当前可分配资源，若大于则出错
			{                         
				printf("企业%d分配的资金大于银行现在可利用的资源",i+1);
				printf("\n");
				printf("银行尚无足够资金，不予分配!\n");
				flag = False;
				break;
			}
		}
    }
    //前两个条件成立，试分配资源，寻找安全序列 
    if(flag) {
		test(i); //根据进程需求量,试分配资源 
		showdata(); //根据进程需求量，显示试分配后的资源量 
		if(!safe()) //寻找安全序列
		{
			Retest(i);
			showdata();
		}
    }
}
void freeMem()
{
	int i;
	for(i=0;i<c;++i)
	{
		free(Max[i]);
	}
	free(Max);
	for(i=0;i<c;++i)
	{
		free(Allocation[i]);
	}
	free(Allocation);
	for(i=0;i<c;++i)
	{
		free(Need[i]);
	}
	free(Need);
	free(Request);
	free(Available);
	free(Work);
	free(Finish);
	free(Security);
	free(NAME);

}
 
int main()//主函数
{	
	char choice;
	printf("\t---------------------------------------------------\n");
	printf("\t||                                               ||\n");
	printf("\t||               银行家算法的实现                ||\n");
	printf("\t||                                               ||\n");
	printf("\t---------------------------------------------------\n");
	init();//初始化数据
    showdata();//显示各种资源
    //用银行家算法判定系统当前时刻是否安全，不安全就不再继续分配资源 
	if(!safe()) exit(0);
	
	do{
		printf("*************************************************************\n");
		printf("\n");
		printf("\n");
		printf("\t-------------------银行家算法演示------------------\n");
		printf("                     R(r):请求分配   \n");	
		printf("                     E(e):退出       \n");
		printf("\t---------------------------------------------------\n");
		printf("请选择：");
		fflush(stdin);  //清空输入流缓冲区的字符，注意必须引入#include<stdlib.h>头文件
		scanf("%c",&choice);
		switch(choice)
		{
			case 'r':
			case 'R':
				bank();break;			
			case 'e':
			case 'E':
				freeMem();
				exit(0);
			default: printf("请正确选择!\n");break;
		}
	} while(choice);
	return 0;
}
 
 