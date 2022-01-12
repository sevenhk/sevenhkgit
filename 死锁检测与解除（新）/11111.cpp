#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
 
#define False 0
#define True 1

int s,c,tmp;
int *Request,*Available,*Work,*Finish,*Security;
int **Max,**Allocation,**Need;
char *NAME;
void Truesafe();
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
/********��ʼ�����ݣ����������������Դ���ࡢ������Դ������������
�����̶���Դ����������������̵���Դ�ѷ��������ȡ�********/
void init()
{
	/* cΪ���̸�����������������sΪ��Դ���࣬������������*/
    int i,j,S,C;
	int number,flag;
	char name;//������Դ����
	//����ϵͳ��Դ��Ŀ������Դ���Ը��� 
    printf("������ϵͳ�ɷ������Դ���ࣺ");
	scanf("%d",&S);
	s=S;
	FormatR();	
	//����������������̵����������� 
    printf("ϵͳ���м���������Ҫ������Դ:");	
	scanf("%d",&C);
	c=C;
    FromatC();
	  for(i=0;i<s;i++)
	{
		printf("��Դ%d������:",i+1);
		fflush(stdin);  //������������������ַ���ע���������#include<stdlib.h>ͷ�ļ�
		scanf("%c",&name);
		NAME[i]=name;
		printf("��Դ%c�ĳ�ʼ�ɷ�������Ϊ:",name);	
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
				        printf("����%d��%c������Դ����Ϊ��",i+1,NAME[j]);//N=s��M=c��
			        	scanf("%d",&Max[i][j]);
						Need[i][j]=Max[i][j];
				        if(Max[i][j]>Available[j])
						{
							flag = True;
                            printf("��������Դ����ϵͳ�����Դ�޶�%d�����������ý���������Դ����",Available[j]);
						}
				}while(flag);
			}
			printf("----------------------------------------\n");
		}								

			
	//����������Ѿ��������Դ��������û���Ҫ����Դ�� 
		for(i=0;i<c;i++)
		{
						printf("----------------------------------------\n");
			for(j=0;j<s;j++)
		  	{
			  do{
		            flag=False;
				    printf("����������Ϊ����%d�����%c��Դ���ͷ������Դ����",i+1,NAME[j]);
				    scanf("%d",&Allocation[i][j]);
				    if(Allocation[i][j]>Need[i][j]&&Allocation[i][j]>Available[j])  
					{
						flag=True;				
						printf("���õ���Դ��������Դ������������ֵ�����������ý�");
						printf("\n");
						printf("����%d��%c����Դ����Ҫ%d����ϵͳ�Ը���Դ���ͻ��ɷ������Դ��Ϊ%d��",i+1,NAME[j],Need[i][j],Available[j]);
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
 
/********��ʾ��Դ�������********/
void showdata()
{
	int i,j;
	printf("*************************************************************\n");
	printf("ϵͳĿǰ�ɷ������Դ��:\n");
	for(i=0;i<s;i++)
        printf("    %c    ",NAME[i]);
	printf("\n");
	for(j=0;j<s;j++)
        printf("    %d    ",Available[j]);
	printf("\n");
	printf("ϵͳ��ǰ����Դ����������£�\n");
	printf("                  ����������Դ��   	          ���ѷ�����Դ��            ���̻���Ҫ��Դ��\n");
	printf("��������:          ");
	//����������ͬ�е���Դ����Max��Allocation��Need�·ֱ��Ӧ 
	for(j=0;j<3;j++){
		for(i=0;i<s;i++)
			printf("%c        ",NAME[i]);
		printf("     ");
	}
	printf("\n");
	//���ÿ�����̵�Max��Allocation��Need 
	for(i=0;i<c;i++)
	{
		printf(" ����%d��           ",i+1);
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
 
/********���Է�����Դ********/
int test() //��̽�ԵĽ���Դ�������i������ 
{ 
	for(int j=0;j<s;j++)
	{
		Available[j]=Available[j]-Request[j];
		Allocation[tmp][j]=Allocation[tmp][j]+Request[j];
		Need[tmp][j]=Need[tmp][j]-Request[j];
	}
	return True;
}
 
/********��̽�Է�����Դ����********/
int Retest() //��test�����෴ 
{ 
	for(int j=0; j<s; j++)
	{
		Available[j] = Available[j] + Request[j];
		Allocation[tmp][j] = Allocation[tmp][j] - Request[j];
		Need[tmp][j] = Need[tmp][j] + Request[j];
	}
	return True;
}
/********��ȫ���㷨********/
int safe()
{
	int i,j,k=0,m,apply;
	//��ʼ��work 
	for(j=0;j<s;j++)
        Work[j] = Available[j];
    //��ʼ��Finish 
    for(i=0;i<c;i++) 
    	Finish[i] = False;
	//��ȫ���� 
	for(i=0;i<c;i++){ 
		apply=0;
		for(j=0;j<s;j++){
			if(Finish[i]==False && Need[i][j]<=Work[j])
			{   
				apply++;
				//ֱ��ÿ����Դ��������С��ϵͳ��������Դ���ſɷ���
				if(apply==s)
				{  
					for(m=0;m<s;m++)
				        Work[m]=Work[m]+Allocation[i][m];//���ĵ�ǰ�ɷ�����Դ
					Finish[i]=True;
					Security[k++]=i;
					i=-1; //��֤ÿ�β�ѯ���ӵ�һ�����̿�ʼ		
				}
			}
		}
	}
	
	for(i=0;i<c;i++){
		if(Finish[i]==False){
			printf("ϵͳ����ȫ\n");//���ɹ�ϵͳ����ȫ
			return False;
		}
	}
    printf("ϵͳ�ǰ�ȫ��!\n");//�����ȫ������ɹ�
    printf("����һ����ȫ����:");
	for(i=0;i<c;i++){//������н�������
		printf("P%d",Security[i]);
		if(i<c-1) 
			printf("->");
	}
	printf("\n");
	return True;
}
/********�����㷨��������Դ�����Է�********/
void Assignment()
{
	int flag = True;//��־�������ж��ܷ�������м��㷨����һ�� 
	int i,j;
 
	printf("��ѡ������Ҫ����Ľ���(1-%d):",c); 
    scanf("%d",&i);//������������Դ�Ľ��̺�
	tmp=i;
	printf("��ϵͳ���ɷ������Դ����");
	for(j=0;j<s;j++)
		printf("%c:%3d",NAME[j],Available[j]);
	printf("\n");
	printf("����������Ϊ����%d�������Դ����\n",i);
	i-=1;
	for(j=0;j<s;j++)
	{
		printf("%c:",NAME[j]);
		scanf("%d",&Request[j]);//������Ҫ�������Դ
	}
    for (j=0;j<s;j++)
	{
		if(Request[j]>Need[i][j])//�ж������Ƿ�������������������
		{
			printf("%d\n",i);
			printf("����%d�������Դ��������Ҫ����Դ\n",i+1);
			printf("���䲻����������䣡\n");
			flag = False;
			break;
		}
		else 
		{
            if(Request[j]>Available[j])//�ж������Ƿ���ڵ�ǰ�ɷ�����Դ�������������
			{                         
				printf("����%d�������Դ����ϵͳ���ڿ����õ���Դ",i+1);
				printf("\n");
				printf("ϵͳ�����㹻��Դ���������!\n");
				flag = False;
				break;
			}
		}
    }
    //ǰ���������������Է�����Դ��Ѱ�Ұ�ȫ���� 
    if(flag) {
		test(); //���ݽ���������,�Է�����Դ 
		showdata(); //���ݽ�������������ʾ�Է�������Դ�� 
		if(!safe()) //Ѱ�Ұ�ȫ����
		{
			Retest();
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
 
int main()//������
{	
	int m=1;
	char choice;
	while(m)
	{
	printf("\t---------------------------------------------------\n");
	printf("\t||                                               ||\n");
	printf("\t||               �����ļ������                ||\n");
	printf("\t||                                               ||\n");
	printf("\t---------------------------------------------------\n");
	init();//��ʼ������
    //�����м��㷨�ж�ϵͳ��ǰʱ���Ƿ�ȫ������ȫ�Ͳ��ټ���������Դ 
	if(!safe())
	{
		m=1;
		freeMem();
	}
	else
		m=-1;
	    showdata();//��ʾ������Դ
	}
	do{
		printf("*************************************************************\n");
		printf("\n");
		printf("\n");
		printf("\t-------------------����������ʾ--------------------\n");
		printf("                     R(r):�����������   \n");	
		printf("                     E(e):�˳�       \n");
		printf("\t---------------------------------------------------\n");
		printf("��ѡ��");
		fflush(stdin);  //������������������ַ���ע���������#include<stdlib.h>ͷ�ļ�
		scanf("%c",&choice);
		switch(choice)
		{
			case 'r':
			case 'R':
				Assignment();break;			
			case 'e':
			case 'E':
				exit(0);
			default: printf("����ȷѡ��!\n");break;
		}
	} while(choice);
	freeMem();
	return 0;
}
 
 