#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=18,M=200001;
const ll P=1e9+7;
int m,n,R,R2,pow2[N],c[N][N],h[M<<4];
ll d[N][N];
bool a[N][N];
struct str
{
    int x;
    ll s;
    str(){}
    str(int x,ll s):x(x),s(s){}
}Q[M],Q2[M],b[N][N][M];
void add(int x,ll s)
{
    if(h[x]!=0) Q2[h[x]].s+=s;
    else
    {
        Q2[++R2]=str(x,s);
        h[x]=R2;
    }
}
void solve1(int x,int y,int t,ll w)
{
    int t1=(t>>(y-1))%2,t2=(t>>y)%2;
    if(!a[x][y])
    {
        if(t1==0&&t2==0) add(t,w);
    }
    else if(t1==0&&t2==0)
    {
        add(t,w);
        if(a[x+1][y]) add(t+pow2[y-1],w);
        if(a[x][y+1]) add(t+pow2[y],w);
    }
    else if(t1==0&&t2!=0) add(t-pow2[y],w);
    else if(t1!=0&&t2==0) add(t-pow2[y-1],w);
}
void solve2(int x,int y,int t,ll w)
{
    int t1=(t>>(y-1))%2,t2=(t>>y)%2;
    if(!a[x][y])
    {
        if(t1==0&&t2==0) add(t,w);
    }
    else if(t1==0&&t2==0)
    {
        add(t,w);
        if(a[x-1][y]) add(t+pow2[y],w);
        if(a[x][y-1]) add(t+pow2[y-1],w);
    }
    else if(t1==0&&t2!=0) add(t-pow2[y],w);
    else if(t1!=0&&t2==0) add(t-pow2[y-1],w);
}
int main()
{
    pow2[0]=1;
    for(int i=1;i<=17;++i) pow2[i]=pow2[i-1]*2;
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            int x;
            scanf("%d",&x);
            if(x==0) a[i][j]=true;
        }
    }
    Q[++R]=str(0,1);
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=R;++j) Q[j].x<<=1;
        for(int j=1;j<=n;++j)
        {
            for(int k=0;k<=500000;++k) h[k]=0;
            for(int k=1;k<=R;++k)
            {
                b[i][j][++c[i][j]]=Q[k];
                solve1(i,j,Q[k].x,Q[k].s);
            }
            for(int k=1;k<=R2;++k) Q[k]=Q2[k],Q[k].s%=P;
            R=R2;
            R2=0;
        }
    }
    R=R2=0;
    Q[++R]=str(0,1);
    for(int i=m;i>=1;--i)
    {
        for(int j=1;j<=R;++j) Q[j].x>>=1;
        for(int j=n;j>=1;--j)
        {
            for(int k=0;k<=500000;++k) h[k]=0;
            for(int k=1;k<=R;++k)
            {
                solve2(i,j,Q[k].x,Q[k].s);
            }
            if(a[i][j]==false) d[i][j]=0;
            else
            {
                for(int k=0;k<=500000;++k) h[k]=0;
                for(int k=1;k<=c[i][j];++k)
                {
                    if((b[i][j][k].x>>(j-1))%2!=0||(b[i][j][k].x>>j)%2!=0) continue;
                    h[b[i][j][k].x]+=b[i][j][k].s;
                }
                ll s=0;
                for(int k=1;k<=R;++k)
                {
                    if((Q[k].x>>(j-1))%2!=0||(Q[k].x>>j)%2!=0) continue;
                    s=(s+h[Q[k].x]*Q[k].s%P)%P;
                }
                d[i][j]=s;
            }
            for(int k=1;k<=R2;++k) Q[k]=Q2[k],Q[k].s%=P;
            R=R2;
            R2=0;
        }
    }
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            printf("%d ",d[i][j]);
        }
        printf("\n");
    }
    return 0;
}