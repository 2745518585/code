#include<bits/stdc++.h>
using namespace std;
const int N=1000001,M=11;
int n,m,k,s1,s2,p=1,t[N],f[N];
bool h[N];
struct road
{
    int m,q,w;
}a[N<<1];
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
int sum(int x,int y)
{
    return (x-1)*(k+1)+y+1;
}
int main()
{
    scanf("%d%d%d%d",&n,&s1,&s2,&k);
    int x,y,w;
    while(~scanf("%d%d%d",&x,&y,&w))
    {
        for(int i=0;i<=k;++i)
        {
            road(sum(x,i),sum(y,i),w);
            road(sum(y,i),sum(x,i),w);
            if(i<=k-1)
            {
                road(sum(x,i),sum(y,i+1),0);
                road(sum(y,i),sum(x,i+1),0);
            }
        }
    }
    queue<int> Q;
    for(int i=1;i<=sum(n,k);++i) f[i]=1e9;
    f[sum(s1,0)]=0;
    h[sum(s1,0)]=true;
    Q.push(sum(s1,0));
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        if(h[k]==false) continue;
        h[k]=false;
        for(int i=t[k];i!=0;i=a[i].q)
        {
            if(f[k]+a[i].w<f[a[i].m])
            {
                f[a[i].m]=f[k]+a[i].w;
                h[a[i].m]=true;
                Q.push(a[i].m);
            }
        }
    }
    int s=1e9;
    for(int i=0;i<=k;++i) s=min(s,f[sum(s2,i)]);
    printf("%d",s==1e9?-1:s);
    return 0;
}