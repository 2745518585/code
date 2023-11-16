#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=1000001;
int m,n,f[N],g[N];
char a[N],b[N];
int main()
{
    int T;
    scanf("%s%d",a+1,&T);
    m=strlen(a+1);
    int s=0;
    while(T--)
    {
        scanf("%s",b+1);
        n=strlen(b+1);
        if(n<=1) continue;
        for(int i=1;i<=m/2;++i) swap(a[i],a[m-i+1]);
        for(int i=1;i<=n/2;++i) swap(b[i],b[n-i+1]);
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
            g[m-i+1]=j;
        }
        for(int i=m-1;i>=1;--i) g[i]=max(g[i],g[i+1]);
        for(int i=1;i<=m/2;++i) swap(a[i],a[m-i+1]);
        for(int i=1;i<=n/2;++i) swap(b[i],b[n-i+1]);
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
            if(j+g[i+1]>=n)
            {
                ++s;
                break;
            }
        }
    }
    printf("%d",s);
    return 0;
}