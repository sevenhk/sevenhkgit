#include<stdio.h>
int main()
{
int n,i,j,min,a[100];
while(scanf("%d",&n)!=EOF)
{ 
	for(i=0;i<=n-1;i++)
		scanf("%d",&a[i]);
    for(j=1;j<n;j++)
	 {
		for(i=0;i<n-1;i++)
		{

				 if(a[i]>a[j])                                    
				 {
					min=a[j];
					a[j]=a[i];
					a[i]=min;
				 }
			 }
		}	
		for(i=0;i<=n-1;i++)
		printf(" %d ",a[i]);
}

return 0;

}

