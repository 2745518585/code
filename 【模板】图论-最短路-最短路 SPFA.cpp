#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=1000001,M=10000001;
int n,m,p=1,t[N],f[N];
bool h[N];
struct road
{
    int m,q,w;
}a[M];
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        road(x,y,w);
    }
    for(int i=1;i<=n;++i) f[i]=1e9;
    f[1]=0;
    h[1]=true;
    queue<int> Q;
    Q.push(1);
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
    printf("%d",f[n]==1e9?-1:f[n]);
    return 0;
}