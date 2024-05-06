#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,q,fa[N];
ll a[N];
bool h[N];
vector<int> d[N];
struct
{
    int l,r;
}b[N];
struct str
{
    int x;
    ll w;
    str() {}
    str(int x,ll w):x(x),w(w) {}
    friend bool operator<(str a,str b)
    {
        return a.w>b.w;
    }
};
ll query(int l,int r)
{
    printf("? %d %d\n",l,r);
    fflush(stdout);
    ll x;
    scanf("%lld",&x);
    return x;
}
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
void dfs(int x)
{
    // printf("  %d %d %lld\n",b[x].l,b[x].r,a[x]);
    ll s=0;
    int p=0;
    for(auto i:d[x])
    {
        s+=a[i];
        if(a[i]<=0) p=i;
    }
    if(s>a[x]) a[p]-=s-a[x];
    for(auto i:d[x]) dfs(i);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            a[i]=query(i,i);
            b[i].l=b[i].r=i;
        }
        for(int i=1;i<=n*2+1;++i) fa[i]=i,d[i].clear();
        fa[0]=fa[n+1]=0;
        b[0].l=1,b[0].r=-1;
        q=n+1;
        for(int i=1;i<=n-1;++i)
        {
            if(!((a[i]>0)^(a[i+1]>0)))
            {
                int x1=find(i),x2=find(i+1);
                ++q;
                a[q]=a[x1]+a[x2];
                b[q].l=b[x1].l,b[q].r=b[x2].r;
                d[q]={x1,x2};
                fa[x1]=fa[x2]=q;
            }
        }
        priority_queue<str> Q;
        for(int i=1;i<=q;++i)
        {
            if(find(i)==i&&a[i]>0) Q.push(str(i,a[i]));
        }
        while(!Q.empty())
        {
            // for(int i=1;i<=q;++i)
            // {
            //     if(find(i)==i) printf("%d %d %d\n",b[i].l,b[i].r,a[i]);
            // }
            // printf("\n");
            int x=Q.top().x;
            Q.pop();
            if(x!=find(x)) continue;
            // printf(" %d %d %lld\n",b[x].l,b[x].r,a[x]);
            auto check=[&](int x1,int x2,int x3)
            {
                ll z=query(b[x1].l,b[x3].r);
                if(z!=max(a[x1],a[x3]))
                {
                    a[x2]=z-a[x1]-a[x3];
                    ++q;
                    a[q]=z;
                    b[q].l=b[x1].l,b[q].r=b[x3].r;
                    fa[x1]=fa[x2]=fa[x3]=q;
                    d[q]={x1,x2,x3};
                    Q.push(str(q,a[q]));
                    return true;
                }
                a[x2]=min(a[x2],-min(a[x1],a[x3]));
                return false;
            };
            int x2=find(b[x].l-1),x1=find(b[x2].l-1),x3=find(b[x].r+1),x4=find(b[x3].r+1);
            if(x1)
            {
                if(check(x1,x2,x)) continue;
            }
            if(x4)
            {
                if(check(x,x3,x4)) continue;
            }
            ++q;
            a[q]=a[x],b[q]=b[x];
            fa[x]=q,d[q]={x};
            if(x2) a[q]+=a[x2],b[q].l=b[x2].l,fa[x2]=q,d[q].push_back(x2);
            if(x3) a[q]+=a[x3],b[q].r=b[x3].r,fa[x3]=q,d[q].push_back(x3);
        }
        for(int i=1;i<=q;++i)
        {
            if(find(i)==i) dfs(i);
        }
        printf("! ");
        for(int i=1;i<=n;++i)
        {
            printf("%lld ",a[i]);
        }
        printf("\n");
        fflush(stdout);
    }
    return 0;
}