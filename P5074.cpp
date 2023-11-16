#include<cstdio>
#include<algorithm>
#include<unordered_map>
using namespace std;
typedef long long ll;
const int N=21,M=10000001;
int m,n,R,R2,ex,ey,pow2[N];
ll s;
bool a[N][N];
struct str
{
    int x;
    ll s;
    str(){}
    str(int x,ll s):x(x),s(s){}
}Q[M],Q2[M];
unordered_map<int,int> Map;
void add(int x,ll s)
{
    if(Map.count(x)) Q2[Map[x]].s+=s;
    else
    {
        Q2[++R2]=str(x,s);
        Map[x]=R2;
    }
}
void solve(int x,int y,int t,ll w)
{
    int t1=(t>>(y-1))%2,t2=(t>>y)%2;
    if(!a[x][y])
    {
        if(t1==0&&t2==0) add(t,w);
    }
    else if(t1==0&&t2==0)
    {
        if(a[x+1][y]&&a[x][y+1]) add(t+pow2[y-1]+pow2[y],w);
    }
    else if(t1==0&&t2!=0)
    {
        if(a[x+1][y]) add(t-pow2[y]+pow2[y-1],w);
        if(a[x][y+1]) add(t,w);
    }
    else if(t1!=0&&t2==0)
    {
        if(a[x+1][y]) add(t,w);
        if(a[x][y+1]) add(t-pow2[y-1]+pow2[y],w);
    }
    else if(t1!=0&&t2!=0)
    {
        add(t-pow2[y-1]-pow2[y],w);
        if(x==ex&&y==ey) s+=w;
    }
    
}
void abc()
{
    scanf("%d%d",&m,&n);
    for(int i=0;i<=m+1;++i)
    {
        for(int j=0;j<=n+1;++j) a[i][j]=false;
    }
    ex=ey=0;
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            int x;
            scanf("%d",&x);
            if(x==1)
            {
                a[i][j]=true;
                ex=i,ey=j;
            }
        }
    }
    if(ex==0&&ey==0)
    {
        printf("1\n");
        return;
    }
    s=R=R2=0;
    Q[++R]=str(0,1);
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=R;++j) Q[j].x<<=1;
        for(int j=1;j<=n;++j)
        {
            Map.clear();
            for(int k=1;k<=R;++k)
            {
                solve(i,j,Q[k].x,Q[k].s);
            }
            for(int k=1;k<=R2;++k) Q[k]=Q2[k];
            R=R2;
            R2=0;
        }
    }
    printf("%lld\n",s);
}
int main()
{
    pow2[0]=1;
    for(int i=1;i<=13;++i) pow2[i]=pow2[i-1]*2;
    int T;
    scanf("%d",&T);
    while(T--) abc();
    return 0;
}