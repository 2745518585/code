#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,k,p=1,tot,t[N],b[N],c[N],d[N],T[N],t1,h[N];
ll f[N][2];
bool g[N];
struct road
{
    int m,q;
}a[N<<1];
struct str
{
    int x;
    ll s;
    str(){}
    str(int x0,ll s0){x=x0,s=s0;}
    friend bool operator <(str a,str b)
    {
        return a.s<b.s;
    }
};
priority_queue<str> Q1,Q2,Q3,Q4,Q5;
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
bool cmp(int a,int b)
{
    return a>b;
}
void dfs0(int x,int fa)
{
    T[x]=1;
    b[x]=c[x]=++tot;
    for(int i=t[x];i!=0;i=a[i].q)
    {
        if(a[i].m==fa) continue;
        if(b[a[i].m]==0)
        {
            dfs0(a[i].m,x);
            T[x]+=T[a[i].m];
            c[x]=min(c[x],c[a[i].m]);
            if(c[a[i].m]<=b[x])
            {
                if(g[x]==false) d[++k]=x;
                if(g[a[i].m]==false) d[++k]=a[i].m;
                g[x]=g[a[i].m]=true;
            }
        }
        else
        {
            if(g[x]==false) d[++k]=x;
            if(g[a[i].m]==false) d[++k]=a[i].m;
            g[x]=g[a[i].m]=true;
        }
        c[x]=min(c[x],b[a[i].m]);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        road(x,y);
        road(y,x);
    }
    for(int i=1;i<=n;++i)
    {
        if(b[i]==0)
        {
            k=0;
            dfs0(i,0);
            if(g[i]==false)
            {
                for(int j=t[i];j!=0;j=a[j].q)
                {
                    f[++t1][0]=T[a[i].m];
                    f[t1][1]=-1e18;
                }
            }
            else
            {
                for(int j=t[i];j!=0;j=a[j].q)
                {
                    if(g[a[j].m]==false)
                    {
                        f[++t1][0]=T[a[j].m];
                        f[t1][1]=-1e18;
                    }
                }
                int s=0,w=0;
                for(int j=1;j<=k;++j)
                {
                    if(d[j]==i) continue;
                    for(int l=t[d[j]];l!=0;l=a[l].q)
                    {
                        if(g[a[l].m]==false)
                        {
                            w=max(w,T[a[l].m]);
                            s+=T[a[l].m];
                        }
                    }
                    ++s;
                }
                f[++t1][0]=w;
                f[t1][1]=s;
            }
        }
    }
    for(int i=1;i<=t1;++i)
    {
        Q1.push(str(i,f[i][0]));
        Q2.push(str(i,f[i][1]));
    }
    Q1.push(str(t1+1,-1e18));
    Q2.push(str(t1+1,-1e18));
    Q3.push(str(t1+2,-1e18));
    Q4.push(str(t1+2,-1e18));
    Q5.push(str(t1+3,-1e18));
    h[t1+1]=0,h[t1+2]=1,h[t1+3]=2;
    ll s=0,k=0;
    while(s<m)
    {
        ++k;
        while(Q1.size()>1&&h[Q1.top().x]!=0) Q1.pop();
        while(Q2.size()>1&&h[Q2.top().x]!=0) Q2.pop();
        while(Q3.size()>1&&h[Q3.top().x]!=1) Q3.pop();
        while(Q4.size()>1&&h[Q4.top().x]!=1) Q4.pop();
        while(Q5.size()>1&&h[Q5.top().x]!=2) Q5.pop();
        ll p1=Q1.top().s,p2=Q3.top().s,p3=Q2.top().s+Q4.top().s,p4=Q2.top().s+Q5.top().s;
        if(p1>=p2&&p1>=p3&&p1>=p4)
        {
            s+=p1;
            int z=Q1.top().x;
            Q1.pop();
            h[z]=1;
            Q3.push(str(z,f[z][1]-f[z][0]));
            Q4.push(str(z,-f[z][0]));
        }
        else if(p2>=p3&&p2>=p4)
        {
            s+=p2;
            int z=Q3.top().x;
            Q3.pop();
            h[z]=2;
            Q5.push(str(z,f[z][0]-f[z][1]));
        }
        else if(p3>=p4)
        {
            s+=p3;
            int z1=Q2.top().x,z2=Q4.top().x;
            Q2.pop(),Q4.pop();
            h[z1]=2,h[z2]=0;
            Q5.push(str(z1,f[z1][0]-f[z1][1]));
            Q1.push(str(z2,f[z2][0]));
            Q2.push(str(z2,f[z2][1]));
        }
        else
        {
            s+=p4;
            int z1=Q2.top().x,z2=Q5.top().x;
            Q2.pop(),Q5.pop();
            h[z1]=2,h[z2]=1;
            Q5.push(str(z1,f[z1][0]-f[z1][1]));
            Q3.push(str(z2,f[z2][1]-f[z2][0]));
            Q4.push(str(z2,-f[z2][0]));
        }
    }
    printf("%lld",k);
    return 0;
}