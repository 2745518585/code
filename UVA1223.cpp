#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=100001;
int n,h[N],x1[N],x2[N],sa[N],rk[N],he[N];
char a[N];
void init(char a[])
{
    int n=strlen(a+1),m=26;
    for(int i=1;i<=m;++i) h[i]=0;
    for(int i=1;i<=n;++i) x1[i]=x2[i]=sa[i]=rk[i]=he[i]=0;
    for(int i=1;i<=n;++i)
    {
        ++h[a[i]-'a'+1];
        x1[i]=a[i]-'a'+1;
    }
    for(int i=1;i<=m;++i) h[i]+=h[i-1];
    for(int i=n;i>=1;--i) sa[h[x1[i]]--]=i;
    for(int r=1;r<=n;r<<=1)
    {
        int p=0;
        for(int i=n-r+1;i<=n;++i) x2[++p]=i;
        for(int i=1;i<=n;++i) if(sa[i]>r) x2[++p]=sa[i]-r;
        for(int i=1;i<=m;++i) h[i]=0;
        for(int i=1;i<=n;++i) ++h[x1[i]];
        for(int i=1;i<=m;++i) h[i]+=h[i-1];
        for(int i=n;i>=1;--i) sa[h[x1[x2[i]]]--]=x2[i],x2[i]=0;
        swap(x1,x2);
        p=0;
        x1[sa[1]]=++p;
        for(int i=2;i<=n;++i)
        {
            if(x2[sa[i]]==x2[sa[i-1]]&&x2[sa[i]+r]==x2[sa[i-1]+r]) x1[sa[i]]=p;
            else x1[sa[i]]=++p;
        }
        if(p==n) break;
        m=p;
    }
    for(int i=1;i<=n;++i) rk[sa[i]]=i;
    int p=0;
    for(int i=1;i<=n;++i)
    {
        if(rk[i]==1) continue;
        if(p>=1) --p;
        int j=sa[rk[i]-1];
        while(i+p<=n&&j+p<=n&&a[i+p]==a[j+p]) ++p;
        he[rk[i]]=p;
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",a+1);
        init(a);
        n=strlen(a+1);
        int s=0;
        for(int i=2;i<=n;++i) s=max(s,he[i]);
        printf("%d\n",s);
    }
    return 0;
}