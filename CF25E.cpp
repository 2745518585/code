#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=2000001,M=5;
int f[N],s;
char a[M][N];
int KMP(char a[],char b[])
{
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
        if(j==n) return j;
        if(i==m) return j;
    }
}
int main()
{
    for(int i=1;i<=3;++i)
    {
        scanf("%s",a[i]+1);
    }
    for(int i=1;i<=3;++i)
    {
        for(int j=1;j<=3;++j)
        {
            if(i==j) continue;
            for(int k=1;k<=3;++k)
            {
                if(i==k||j==k) continue;
                int z=KMP(a[i],a[j]);
                if(z==strlen(a[j]+1)) s=max(s,KMP(a[i],a[j])+KMP(a[i],a[k]));
                else s=max(s,KMP(a[i],a[j])+KMP(a[j],a[k]));
            }
        }
    }
    s=-s;
    for(int i=1;i<=3;++i)
    {
        s+=strlen(a[i]+1);
    }
    printf("%d",s);
    return 0;
}