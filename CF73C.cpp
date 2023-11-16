#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=200001,M=21;
int m,n,q,f[N],g[M][N],h[M];
char a[N],b[M][N];
void KMP(char a[],char b[],int t)
{
    int m=strlen(a+1),n=strlen(b+1);
    f[1]=0;
    for(int i=2,j=0;i<=n;++i)
    {
        while(j!=0&&b[i]!=b[j+1]) j=f[j];
        if(b[i]==b[j+1]) ++j;
        f[i]=j;
    }
    for(int i=1,j=0;i<=m;++i)
    {
        while(j!=0&&a[i]!=b[j+1]) j=f[j];
        if(a[i]==b[j+1]) ++j;
        if(j==n) g[t][i]=i-n+1;
    }
}
int main()
{
    scanf("%s%d",a+1,&n);
    m=strlen(a+1);
    for(int i=1;i<=n;++i)
    {
        scanf("%s",b[i]+1);
        KMP(a,b[i],i);
    }
    int s=0,k=1;
    for(int i=1;i<=m;++i)
    {
        int x=0;
        for(int j=1;j<=n;++j)
        {
            h[j]=max(h[j],g[j][i]);
            x=max(x,h[j]+1);
        }
        if(i-x+1>s) s=i-x+1,k=x;
    }
    printf("%d %d\n",s,k-1);
    return 0;
}