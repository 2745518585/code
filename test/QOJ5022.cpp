#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001,M=500;
int n,m,q,t,d[N],f[N],f2[N],g[N],g2[N],h[N];
vector<pair<int,int>> b[N],c[N];
struct
{
    int l,r;
}a[N];

void solve(int l,int r)
{
    t=0;
    for(int i=l;i<=r;++i)
    {
        d[++t]=a[i].l,d[++t]=a[i].r;
        for(auto j:b[i]) d[++t]=j.first;
    }
    d[++t]=n;
    sort(d+1,d+t+1);
    t=unique(d+1,d+t+1)-d-1;
    for(int i=1;i<=t;++i) c[i].clear();
    for(int i=l;i<=r;++i)
    {
        for(auto j:b[i])
        {
            c[lower_bound(d+1,d+t+1,j.first)-d].push_back(make_pair(i,j.second));
        }
    }
    for(int i=l-1;i<=r;++i) g[i]=0;
    for(int i=1;i<=t;++i)
    {
        for(int j=l;j<=r;++j) g[j]^=g[j+1];
        {
            for(int j=0;j<=max(d[i]-d[i-1],r-l);++j) h[j]=0;
            for(int j=d[i-1]+1;j<=d[i];++j) h[j-d[i-1]]+=f[j];
            for(int j=1;j<=d[i]-d[i-1];j*=2)
            {
                for(int k=0;k<=d[i]-d[i-1];++k)
                {
                    if(k&j) h[k]+=h[k^j];
                }
            }
            for(int j=0;j<=r-l;++j) g2[j]+=h[j];
        }
        {
            for(int j=0;j<=d[i]-d[i-1];++j) h[j]=0;
            for(int j=d[i-1]+1;j<=d[i];++j) h[j-d[i-1]]+=f[j];
            for(int j=1;j<=(r-l);j*=2)
            {
                if(((r-l)&j)==0) continue;
                for(int k=d[i]-d[i-1];k>=j;--k) h[k]+=h[k-j];
            }
            for(int j=d[i-1]+1;j<=d[i];++j) f2[j]=h[j-d[i-1]];
        }
        {
            for(int j=0;j<=max(d[i]-d[i-1],r-l);++j) h[j]=0;
            for(int j=0;j<=r-l;++j) h[j]+=g[j];
            for(int j=1;j<=r-l;j*=2)
            {
                for(int k=0;k<=r-l;++k)
                {
                    if(k&j) h[k]+=h[k^j];
                }
            }
            for(int j=0;j<=r-l;++j) g2[j]+=h[j];
        }
    }
}
int main()
{
    scanf("%*d%d%d",&n,&q);
    for(int i=1;i<=q;++i)
    {
        int z;
        scanf("%d",&z);
        if(z==1)
        {
            ++m;
            scanf("%d%d",&a[m].l,&a[m].r);
            --q,--i;
        }
        else if(z==2)
        {
            int x;
            scanf("%d",&x);
            b[m].push_back(make_pair(x,i));
        }
    }

}