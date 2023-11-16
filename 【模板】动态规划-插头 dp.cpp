#include<cstdio>
#include<algorithm>
#include<unordered_map>
using namespace std;
typedef long long ll;
const int N=21,M=5000001;
int m,n,R,R2,ex,ey,pow4[N];
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
    int t1=(t>>((y-1)*2))%4,t2=(t>>(y*2))%4;
    if(!a[x][y])
    {
        if(t1==0&&t2==0) add(t,w);
    }
    else if(t1==0&&t2==0)
    {
        if(a[x+1][y]&&a[x][y+1]) add(t+pow4[y-1]+pow4[y]*2,w);
    }
    else if(t1==0&&t2!=0)
    {
        if(a[x+1][y]) add(t-pow4[y]*t2+pow4[y-1]*t2,w);
        if(a[x][y+1]) add(t,w);
    }
    else if(t1!=0&&t2==0)
    {
        if(a[x+1][y]) add(t,w);
        if(a[x][y+1]) add(t-pow4[y-1]*t1+pow4[y]*t1,w);
    }
    else if(t1==1&&t2==1)
    {
        int z=1;
        for(int i=y+1;i<=n;++i)
        {
            if((t>>(i*2))%4==1) ++z;
            if((t>>(i*2))%4==2) --z;
            if(z==0)
            {
                add(t-pow4[y-1]-pow4[y]-pow4[i],w);
                break;
            }
        }
    }
    else if(t1==2&&t2==2)
    {
        int z=1;
        for(int i=y-2;i>=0;--i)
        {
            if((t>>(i*2))%4==1) --z;
            if((t>>(i*2))%4==2) ++z;
            if(z==0)
            {
                add(t-pow4[y-1]*2-pow4[y]*2+pow4[i],w);
                break;
            }
        }
    }
    else if(t1==2&&t2==1)
    {
        add(t-pow4[y-1]*2-pow4[y],w);
    }
    else if(x==ex&&y==ey) s+=w;
}
int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;++i)
    {
        char z[N+1];
        scanf("%s",z+1);
        for(int j=1;j<=n;++j)
        {
            if(z[j]=='.')
            {
                a[i][j]=true;
                ex=i,ey=j;
            }
        }
    }
    pow4[0]=1;
    for(int i=1;i<=13;++i) pow4[i]=pow4[i-1]*4;
    Q[++R]=str(0,1);
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=R;++j) Q[j].x<<=2;
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
    printf("%lld",s);
    return 0;
}