#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;
const int N=5001;
int n,m,a[N],c1[N],c2[N],c3[N],c4[N];
ll f[N][N];
struct str
{
    int x,l,r;
    ll w;
}b[N];
struct str2
{
    int x;
    ll w;
    str2() {}
    str2(int x,ll w):x(x),w(w) {}
    friend bool operator<(str2 a,str2 b)
    {
        return a.w>b.w;
    }
};
vector<int> b1,b2;
priority_queue<str2> Q1[N],Q2[N];
bool cmp1(int x,int y)
{
    return b[x].l<b[y].l;
}
bool cmp2(int x,int y)
{
    return b[x].r>b[y].r;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=m;++i)
    {
        scanf("%d%lld%d%d",&b[i].x,&b[i].w,&b[i].l,&b[i].r);
        b1.push_back(i),b2.push_back(i);
        c1[i]=c2[i]=c3[i]=c4[i]=b[i].x;
        while(c1[i]>=1&&a[c1[i]-1]>=b[i].l) --c1[i];
        while(c2[i]>=1&&a[c2[i]-1]<=b[i].r) --c2[i];
        while(c3[i]<=n&&a[c3[i]+1]>=b[i].l) ++c3[i];
        while(c4[i]<=n&&a[c4[i]+1]<=b[i].r) ++c4[i];
    }
    sort(b1.begin(),b1.end(),cmp1);
    sort(b2.begin(),b2.end(),cmp2);
    for(int i:b1)
    {
        for(int j:b2)
        {
            f[i][j]=1e18;
            int l=max(c1[i],c2[j]),r=min(c3[i],c4[j]);
            if(l>r||b[i].x<l||b[i].x>r||b[j].x<l||b[j].x>r||(b[i].l>b[j].l&&b[i].r>b[j].r)) continue;
            if(b[i].l==1&&b[j].r==n) f[i][j]=0;
            else if(b[i].l>b[j].l) f[i][j]=f[j][j];
            else if(b[i].r>b[j].r) f[i][j]=f[i][i];
            else
            {
                while(!Q1[i].empty())
                {
                    str2 x=Q1[i].top();
                    if(b[x.x].x>=l&&b[x.x].x<=r&&b[x.x].l<=b[j].r&&b[x.x].r>=b[i].l)
                    {
                        f[i][j]=min(f[i][j],x.w);
                        break;
                    }
                    Q1[i].pop();
                }
                while(!Q2[j].empty())
                {
                    str2 x=Q2[j].top();
                    if(b[x.x].x>=l&&b[x.x].x<=r&&b[x.x].l<=b[j].r&&b[x.x].r>=b[i].l)
                    {
                        f[i][j]=min(f[i][j],x.w);
                        break;
                    }
                    Q2[j].pop();
                }
            }
            Q1[i].push(str2(j,f[i][j]+b[j].w));
            Q2[j].push(str2(i,f[i][j]+b[i].w));
        }
    }
    for(int i=1;i<=m;++i)
    {
        if(f[i][i]>=1e18||a[b[i].x]<b[i].l||a[b[i].x]>b[i].r) printf("-1\n");
        else printf("%lld\n",f[i][i]+b[i].w);
    }
    return 0;
}