#include<cstdio>
#include<algorithm>
using namespace std;
#define X x1,y1,x2,y2,x3,y3
const int N=11,M=3000001;
const short dx[4]={-1,0,0,1},dy[4]={0,-1,1,0};
int m,n,p=1,t[M],x1,y1,x2,y2,x3,y3,f[M],g[M],l[M],Q[M],T,R;
bool h[N][N],d[M];
struct road
{
    int m,q;
}a[M<<2];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
int sum(int x1,int y1,int x2,int y2,int x3,int y3)
{
    return (x1-1)*m*m*n*n*n+(y1-1)*m*m*n*n+(x2-1)*m*n*n+(y2-1)*m*n+(x3-1)*n+y3;
}
int num(int dx1,int dy1,int dx2,int dy2,int dx3,int dy3)
{
    return (((x1-dx1)+(y1-dy1)+(x2-dx2)+(y2-dy2)+(x3-dx3)+(y3-dy3))%2+2)%2;
}
bool check(int x,int y)
{
    return x>=1&&x<=m&&y>=1&&y<=n&&!h[x][y];
}
void solve(int x1,int y1,int x2,int y2,int x3,int y3)
{
    int t=sum(X);
    if(d[t]) return;
    d[t]=true;
    if(x1==1)
    {
        if(num(X)==0) g[t]=-1;
        else g[t]=1;
        return;
    }
    if((x1==x2&&y1==y2)||(x1==x3&&y1==y3))
    {
        g[t]=-1;
        return;
    }
    if(num(X)==0)
    {
        for(int i=0;i<=3;++i)
        {
            if(!check(x2+dx[i],y2+dy[i])||(x2+dx[i]==x3&&y2+dy[i]==y3)) continue;
            road(sum(x1,y1,x2+dx[i],y2+dy[i],x3,y3),t);
            ++l[t];
            solve(x1,y1,x2+dx[i],y2+dy[i],x3,y3);
        }
        for(int i=0;i<=3;++i)
        {
            if(!check(x3+dx[i],y3+dy[i])||(x2==x3+dx[i]&&y2==y3+dy[i])) continue;
            road(sum(x1,y1,x2,y2,x3+dx[i],y3+dy[i]),t);
            ++l[t];
            solve(x1,y1,x2,y2,x3+dx[i],y3+dy[i]);
        }
    }
    else
    {
        for(int i=0;i<=2;++i)
        {
            if(!check(x1+dx[i],y1+dy[i])) continue;
            road(sum(x1+dx[i],y1+dy[i],x2,y2,x3,y3),t);
            ++l[t];
            solve(x1+dx[i],y1+dy[i],x2,y2,x3,y3);
        }
    }
}
void abc()
{
    scanf("%d%d",&m,&n);
    x1=y1=x2=y2=x3=y3=0;
    for(int i=1;i<=m;++i)
    {
        char z[N];
        scanf("%s",z+1);
        for(int j=1;j<=n;++j)
        {
            if(z[j]=='X') x1=i,y1=j;
            else if(z[j]=='O')
            {
                if(x2==0) x2=i,y2=j;
                else x3=i,y3=j;
            }
            if(z[j]=='#') h[i][j]=true;
            else h[i][j]=false;
        }
    }
    p=1;
    for(int i=1;i<=m*m*m*n*n*n;++i) t[i]=l[i]=g[i]=f[i]=d[i]=0;
    solve(X);
    T=R=0;
    for(int i=1;i<=m*m*m*n*n*n;++i)
    {
        if(l[i]==0)
        {
            if(g[i]==0) g[i]=-1;
            f[i]=0;
            Q[++R]=i;
        }
    }
    while(T<R)
    {
        int k=Q[++T];
        if(g[k]==0) g[k]=-1;
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(g[a[i].m]==1)
            {
                if(g[k]==-1) f[a[i].m]=min(f[a[i].m],f[k]+1);
                continue;
            }
            if(g[k]==1)
            {
                f[a[i].m]=max(f[a[i].m],f[k]+1);
                --l[a[i].m];
                if(l[a[i].m]==0) Q[++R]=a[i].m;
            }
            else
            {
                g[a[i].m]=1;
                f[a[i].m]=f[k]+1;
                Q[++R]=a[i].m;
            }
        }
    }
    if(g[sum(X)]==1) printf("Red %d\n",f[sum(X)]);
    else if(g[sum(X)]==-1) printf("Black %d\n",f[sum(X)]);
    else printf("Tie\n");
}
int main()
{
    int TOT;
    scanf("%*d%d",&TOT);
    while(TOT--) abc();
    return 0;
}