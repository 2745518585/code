#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001,M=500;
int n,m,q,t,d[N],e[N],f[N],f2[N],g[N],g2[N],h[N];
vector<pair<int,int>> b[N],c[N];
struct
{
    int l,r;
}a[N];
void solve(int l,int r)
{
    t=0;
    for(int i=l+1;i<=r;++i)
    {
        d[++t]=a[i].l,d[++t]=a[i].r;
        for(auto j:b[i]) d[++t]=j.first;
    }
    d[++t]=n;
    sort(d+1,d+t+1);
    t=unique(d+1,d+t+1)-d-1;
    for(int i=1;i<=t;++i) c[i].clear();
    for(int i=l+1;i<=r;++i)
    {
        for(auto j:b[i])
        {
            c[lower_bound(d+1,d+t+1,j.first)-d].push_back(make_pair(i,j.second));
        }
    }
    for(int i=l;i<=r;++i) g[i]=0;
    for(int i=1;i<=n;++i) f2[i]=0;
    // printf("%d %d:\n",l,r);
    for(int i=1;i<=t;++i)
    {
        for(int j=r;j>=l+1;--j) g[j]^=g[j-1];
        int v=0;
        g[0]=g[l];
        for(int j=l+1;j<=r;++j)
        {
            if(a[j].l<d[i]&&a[j].r>=d[i]) g[++v]=g[j];
            else g[v]^=g[j];
        }
        for(int j=0;j<=v;++j) g2[j]=0;
        {
            for(int j=0;j<=max(d[i]-d[i-1],v);++j) h[j]=0;
            for(int j=d[i-1]+1;j<=d[i];++j) h[d[i]-j]^=f[j];
            for(int j=1;j<=max(d[i]-d[i-1],v);j*=2)
            {
                for(int k=0;k<=max(d[i]-d[i-1],v);++k)
                {
                    if(k&j) h[k]^=h[k^j];
                }
            }
            for(int j=0;j<=v;++j) g2[j]^=h[j];
        }
        {
            for(int j=0;j<=d[i]-d[i-1];++j) h[j]=0;
            for(int j=d[i-1]+1;j<=d[i];++j) h[j-d[i-1]]^=f[j];
            for(int j=1;j<=d[i]-d[i-1];j*=2)
            {
                if((v&j)==0) continue;
                for(int k=d[i]-d[i-1];k>=j;--k) h[k]^=h[k-j];
            }
            for(int j=d[i-1]+1;j<=d[i];++j) f2[j]^=h[j-d[i-1]];
        }
        {
            for(int j=0;j<=max(d[i]-d[i-1],v);++j) h[j]=0;
            for(int j=0;j<=v;++j) h[v-j]^=g[j];
            for(int j=1;j<=max(d[i]-d[i-1],v);j*=2)
            {
                for(int k=0;k<=max(d[i]-d[i-1],v);++k)
                {
                    if(k&j) h[k^j]^=h[k];
                }
            }
            for(int j=d[i-1]+1;j<=d[i];++j) f2[j]^=h[j-d[i-1]];
        }
        {
            for(int j=0;j<=v;++j) h[j]=0;
            for(int j=0;j<=v;++j) h[j+(d[i]-d[i-1])]^=g[j];
            for(int j=1;j<=v;j*=2)
            {
                if(((d[i]-d[i-1])&j)!=0) continue;
                for(int k=v;k>=j;--k) h[k]^=h[k-j];
            }
            for(int j=0;j<=v;++j) g2[j]^=h[j];
        }
        v=0;
        g[l]=g2[0];
        for(int j=l+1;j<=r;++j)
        {
            if(a[j].l<d[i]&&a[j].r>=d[i]) g[j]=g2[++v];
            else g[j]=g2[v];
        }
        for(auto j:c[i])
        {
            e[j.second]=g[j.first];
        }
        // printf("%d: ",d[i]);
        // for(int i=l;i<=r;++i) printf("%d ",g[i]);printf("\n");
    }
    swap(f,f2);
}
int main()
{
    scanf("%*d%d%d",&n,&q);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&f[i]);
    }
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
    for(auto i:b[0])
    {
        e[i.second]=f[i.first];
    }
    for(int i=0;i<=(m-1)/M;++i)
    {
        solve(i*M,min((i+1)*M,m));
    }
    for(int i=1;i<=q;++i)
    {
        printf("%d\n",e[i]);
    }
    for(int i=1;i<=n;++i)
    {
        printf("%d\n",f[i]);
    }
    return 0;
}