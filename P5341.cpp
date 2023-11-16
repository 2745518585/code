#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=1000001;
int n,k,sa[N],rk[N],he[N],b[N],Q[N],T,R,f[N];
char a[N];
namespace SA
{
    int h[N],x1[N],x2[N];
    void init(char a[])
    {
        int n=strlen(a+1),m=128;
        for(int i=1;i<=n*2;++i) sa[i]=rk[i]=he[i]=x1[i]=x2[i]=0;
        for(int i=0;i<=m*2;++i) h[i]=0;
        for(int i=1;i<=n;++i)
        {
            ++h[a[i]];
            x1[i]=a[i];
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
}
int main()
{
    int F;
    scanf("%d",&F);
    while(F--)
    {
        scanf("%s%d",a+1,&k);
        SA::init(a);
        n=strlen(a+1);
        T=0,R=-1;
        for(int i=2;i<=n;++i)
        {
            while(T<=R&&Q[T]<=i-k+1) ++T;
            while(T<=R&&he[Q[R]]>=he[i]) --R;
            Q[++R]=i;
            if(i>=k) b[i-k+1]=he[Q[T]];
        }
        for(int i=0;i<=n+1;++i) f[i]=0;
        for(int i=1;i<=n-k+1;++i)
        {
            if((k!=1?b[i]:n-sa[i]+1)>max(he[i],he[i+k]))
            {
                ++f[max(he[i],he[i+k])+1];
                --f[(k!=1?b[i]:n-sa[i]+1)+1];
            }
        }
        for(int i=1;i<=n;++i) f[i]+=f[i-1];
        int q=0;
        for(int i=1;i<=n;++i)
        {
            if(f[i]>=f[q]) q=i;
        }
        printf("%d\n",f[q]==0?-1:q);
    }
    return 0;
}