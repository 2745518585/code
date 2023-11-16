#include<cstdio>
using namespace std;
int a[1000001],la;
void div(int a[],int &l,int b)
{
    int x=0,c[l+1];
    for(int i=l;i>=1;--i)
    {
        c[i]=(x*10+a[i])/b;
        x=(x*10+a[i])%b;
    }
    for(int i=1;i<=l;++i) a[i]=c[i];
    while(l>1&&a[l]==0) --l;
}
void times(int a[],int &l,int b)
{
	for(int i=1;i<=l;++i)
	{
		a[i]*=b;
	}
	for(int i=1;i<=l;++i)
	{
		a[i+1]+=a[i]/10;
		a[i]%=10;
	}
	while(a[l+1]!=0)
	{
		++l;
		a[l+1]+=a[l]/10;
		a[l]%=10;
	}
}
int fpow(int x,int k)
{
    int y=1;
    while(k)
    {
        if(k&1) y=y*x%1000;
        x=x*x%1000;
        k>>=1;
    }
    return y;
}
int main()
{
    int x,y;
    scanf("%d%d",&x,&y);
    y=fpow(y%1000,y);
    a[1]=1;
    la=1;
    --x;
    --y;
    for(int i=y-x+1;i<=y;++i)
    {
        times(a,la,i);
    }
    for(int i=1;i<=x;++i)
    {
        div(a,la,i);
    }
    for(int i=la;i>=1;--i)
    {
        printf("%d",a[i]);
    }
    return 0;
}