#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1000001;
int n,m,q,b[N],c[N],T[N];
struct str
{
    int k,x,y,z,t;
    str(){}
    str(int k,int x,int y,int z,int t):k(k),x(x),y(y),z(z),t(t){}
}a[N],p[N];
void add(int x,int k)
{
    T[x]+=k;
    while(x<=n)
    {
        x+=(x&-x);
        T[x]+=k;
    }
}
int sum(int x)
{
    int s=T[x];
    while(x>=1)
    {
        x-=(x&-x);
        s+=T[x];
    }
    return s;
}
void solve(int l,int r,int ml,int mr)
{
    if(l>r||ml>mr) return;
    if(ml==mr)
    {
        for(int i=l;i<=r;++i) if(a[i].k==1) c[a[i].t]=ml;
        return;
    }
    int z=ml+mr>>1,p1=l-1,p2=r+1;
    for(int i=l;i<=r;++i)
    {
        if(a[i].k==1)
        {
            int k=sum(a[i].y)-sum(a[i].x-1);
            if(a[i].z<=k) p[++p1]=a[i];
            else a[i].z-=k,p[--p2]=a[i];
        }
        else if(a[i].k==2)
        {
            if(a[i].y<=z)
            {
                add(a[i].x,a[i].z);
                p[++p1]=a[i];
            }
            else p[--p2]=a[i];
        }
    }
    for(int i=l;i<=p1;++i)
    {
        a[i]=p[i];
        if(a[i].k==2&&a[i].y<=z) add(a[i].x,-a[i].z);
    }
    for(int i=p2;i<=r;++i)
    {
        a[i]=p[p2+r-i];
        if(a[i].k==2&&a[i].y<=z) add(a[i].x,-a[i].z);
    }
    solve(l,p1,ml,z);
    solve(p2,r,z+1,mr);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
        a[++q]=str(2,i,b[i],1,0);
    }
    for(int i=1;i<=m;++i) c[i]=-1;
    for(int i=1;i<=m;++i)
    {
        char z[10];
        scanf("%s",z);
        if(z[0]=='Q')
        {
            int x,y,k;
            scanf("%d%d%d",&x,&y,&k);
            a[++q]=str(1,x,y,k,i);
        }
        else if(z[0]=='C')
        {
            int x,k;
            scanf("%d%d",&x,&k);
            a[++q]=str(2,x,b[x],-1,0);
            a[++q]=str(2,x,k,1,0);
            b[x]=k;
        }
    }
    solve(1,q,0,1e9);
    for(int i=1;i<=m;++i)
    {
        if(c[i]!=-1) printf("%d\n",c[i]);
    }
    return 0;
}