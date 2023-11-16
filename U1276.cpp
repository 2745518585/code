#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=151,M=11,K=59049;
int n,m,k,t1,t2,a[K+100],b1[K+100],b2[K+100],g[N],h[K+100],f[K+100],f2[K+100],pow3[N];
bool check1(int x)
{
    while(x!=0)
    {
        if(x%3==1&&x/3%3!=1) return false;
        while(x%3==1) x/=3;
        if(x%3==2)
        {
            if(x/3%3==2) x/=3;
            else return false;
        }
        x/=3;
    }
    return true;
}
int check2(int x)
{
    int s=0;
    while(x!=0)
    {
        if(x%3==1)
        {
            if(x/3%3==1&&x/9%3==1) ++s,x/=9;
            else return -1;
        }
        else if(x%3==2)
        {
            if(x/3%3==2) ++s,x/=3;
            else return -1;
        }
        x/=3;
    }
    return s;
}
bool check(int x,int y)
{
    while(x!=0||y!=0)
    {
        if(x%3!=0&&y%3!=0) return true;
        x/=3,y/=3;
    }
    return false;
}
void print(int x)
{
    for(int i=1;i<=m;++i)
    {
        printf("%d",x%3);
        x/=3;
    }
}
void abc()
{
    pow3[0]=1;
    for(int i=1;i<=M+1;++i) pow3[i]=pow3[i-1]*3;
    t1=t2=0;
    for(int i=0;i<=K-1;++i) a[i]=h[i]=0;
    for(int i=1;i<=n;++i) g[i]=0;
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=k;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        g[x]+=pow3[y-1];
    }
    for(int i=0;i<=pow3[m]-1;++i)
    {
        if(check1(i)) b1[++t1]=i;
        h[i]=check2(i);
        if(h[i]!=-1) b2[++t2]=i;
    }
    for(int i=0;i<=pow3[m]-1;++i)
    {
        int x=i,s=0;
        for(int j=1;j<=m;++j)
        {
            s+=max(x%3-1,0)*pow3[j-1];
            x/=3;
        }
        a[i]=s;
    }
    for(int i=0;i<=K-1;++i) f[i]=-1e9;
    f[0]=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=pow3[m]-1;++j) f2[j]=f[j],f[j]=-1e9;
        for(int j=1;j<=t1;++j)
        {
            if(check(b1[j],g[i])||f2[b1[j]]<=-1e8) continue;
            for(int k=1;k<=t2;++k)
            {
                if(check(b1[j],b2[k])||check(b2[k],g[i])||h[b2[k]]==-1) continue;
                f[a[b1[j]]+b2[k]]=max(f[a[b1[j]]+b2[k]],f2[b1[j]]+h[b2[k]]);
            }
        }
    }
    printf("%d\n",f[0]);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) abc();
    return 0;
}