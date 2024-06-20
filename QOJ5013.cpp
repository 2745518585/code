#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=1000001;
int n,q,a[N],c[N],f[N],g[N];
bool h[N];
char b[N];
struct
{
    int l,r;
}d[N];
struct str
{
    int x,w;
    str() {}
    str(int x,int w):x(x),w(w) {}
    friend bool operator<(const str &a,const str &b)
    {
        return a.w>b.w;
    }
};
void solve(int n,int *a)
{
    for(int i=1;i<=n;++i)
    {
        d[i].l=i-1,d[i].r=i+1;
    }
    d[0].l=0,d[0].r=1;
    d[n+1].r=n+1,d[n+1].l=n;
    a[0]=a[n+1]=0;
    priority_queue<str> Q;
    for(int i=1;i<=n;++i)
    {
        Q.push(str(i,a[i]));
        h[i]=false;
    }
    g[0]=0;
    int t=0;
    while(!Q.empty())
    {
        int k=Q.top().x;
        Q.pop();
        if(h[k]) continue;
        // printf("%d\n",k);
        // for(int i=1;i<=n;++i) printf("%d ",a[i]);printf("\n");
        // for(int i=1;i<=n;++i) printf("%d ",h[i]);printf("\n");
        ++t;
        g[t]=g[t-1]+a[k];
        if(d[k].l>=1&&d[k].r<=n)
        {
            a[k]=a[d[k].l]+a[d[k].r]-a[k];
            Q.push(str(k,a[k]));
        }
        else a[k]=-1;
        h[d[k].l]=h[d[k].r]=true;
        d[k].l=d[d[k].l].l;
        d[k].r=d[d[k].r].r;
        d[d[k].l].r=k;
        d[d[k].r].l=k;
        if(a[k]==-1)
        {
            h[k]=true;
            d[d[k].l].r=d[k].r;
            d[d[k].r].l=d[k].l;
        }
    }
}
int main()
{
    scanf("%d%s",&n,b+1);
    for(int i=1;i<=n;++i)
    {
        if(b[i]==b[i-1]) ++a[q];
        else a[++q]=1;
    }
    // for(int i=1;i<=q;++i) printf("%d ",a[i]);printf("\n");
    for(int i=1;i<=n;++i) f[i]=-1e9;
    for(auto i:{0,1})
    {
        for(auto j:{0,1})
        {
            int l=2+i,r=q-1-j;
            if(l>r) continue;
            for(int k=l;k<=r;++k) c[k]=a[k];
            for(int k=0;k<=q;++k) g[k]=1e9;
            solve(r-l+1,c+l-1);
            // printf("%d %d:\n",l,r);
            for(int k=0;k<=q;++k)
            {
                int z=q-k*2-i-j;
                if(z>2) --z;
                if(z>0)
                {
                    // printf("%d %d %d %d\n",k,g[k],z,n-g[k]-i*a[1]-j*a[q]);
                    f[z]=max(f[z],n-g[k]-i*a[1]-j*a[q]);
                }
            }
        }
    }
    for(int i=n;i>=1;--i) c[i]=c[i+1]+(b[i]=='1');
    int w=0;
    for(int i=1;i<=n;++i)
    {
        if(b[i]=='0') ++w;
        f[1]=max(f[1],w+c[i]);
    }
    for(int i=1;i<=n;++i) f[i]=max(f[i],f[i-1]);
    for(int i=1;i<=n;++i)
    {
        printf("%d ",f[i]);
    }
    return 0;
}