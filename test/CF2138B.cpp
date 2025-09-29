#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,a[N],b[N],f[N],g[N],T[N];
void add(int x,int k)
{
    while(x<=n) T[x]=max(T[x],k),x+=x&-x;
}
int sum(int x)
{
    int s=0;
    while(x>=1) s=max(s,T[x]),x-=x&-x;
    return s;
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
            b[a[i]]=i;
        }
        for(int i=1;i<=n;++i) T[i]=0;
        for(int i=n;i>=1;--i)
        {
            add(b[i],b[i]);
            f[b[i]]=sum(b[i]-1);
        }
        for(int i=1;i<=n;++i) T[i]=0;
        for(int i=n;i>=1;--i)
        {
            add(b[i],f[b[i]]);
            g[b[i]]=sum(b[i]-1);
        }
        for(int i=1;i<=n;++i) g[i]=max(g[i],g[i-1]);
        for(int i=1;i<=m;++i)
        {
            int l,r;
            scanf("%d%d",&l,&r);
            if(l<=g[r]) printf("NO\n");
            else printf("YES\n");
        }
    }
    return 0;
}