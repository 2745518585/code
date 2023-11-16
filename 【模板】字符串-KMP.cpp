#include<cstdio>
#include<cstring>
using namespace std;
const int N=1000001;
int f[N];
char a[N],b[N];
int main()
{
    scanf("%s%s",a+1,b+1);
    f[1]=0;
    int m=strlen(a+1),n=strlen(b+1);
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
        if(j==n) printf("%d\n",i-n+1);
    }
    for(int i=1;i<=n;++i)
    {
        printf("%d ",f[i]);
    }
    return 0;
}