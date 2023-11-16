#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=1000001;
int n,m,q,s,p=1,t[N],l[N],c[N];
bool h[N];
queue<int> Q;
struct road
{
    int m,q;
}a[N<<1];
struct road2
{
    int x,y;
}b[N];
void road(int x,int y)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
}
void tpsort()
{
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        --s;
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(h[i]) continue;
            h[i]=h[i^1]=true;
            --l[k],--l[a[i].m];
            if(l[a[i].m]==q-1) Q.push(a[i].m);
        }
    }
}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        b[i]=(road2){x,y};
        ++l[x],++l[y];
        road(x,y);
        road(y,x);
    }
    s=n;
    for(int i=1;i<=n;++i)
    {
        if(l[i]<q) Q.push(i);
    }
    tpsort();
    for(int i=m;i>=1;--i)
    {
        c[i]=s;
        if(h[i*2]) continue;
        h[i*2]=h[i*2+1]=true;
        --l[b[i].x],--l[b[i].y];
        if(l[b[i].x]==q-1) Q.push(b[i].x);
        if(l[b[i].y]==q-1) Q.push(b[i].y);
        tpsort();
    }
    for(int i=1;i<=m;++i)
    {
        printf("%d\n",c[i]);
    }
    return 0;
}