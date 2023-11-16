#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=1000001,M=10000001;
int n,m,p=1,t[N],f[N];
bool h[N];
struct str
{
    int m,q,w;
}a[M];
int sum(int x,int y)
{
    return (x-1)*n+y;
}
void road(int x,int y,int w)
{
    a[++p].m=y;
    a[p].q=t[x];
    t[x]=p;
    a[p].w=w;
}
void abc()
{
    scanf("%d%d",&m,&n);
    ++m;
    ++n;
    p=1;
    for(int i=1;i<=m*n;++i) t[i]=0;
    for(int i=1;i<=m-1;++i)
    {
        char c[1001];
        scanf("%s",c+1);
        for(int j=1;j<=n-1;++j)
        {
            if(c[j]==92)
            {
                road(sum(i,j),sum(i+1,j+1),0);
                road(sum(i+1,j+1),sum(i,j),0);
                road(sum(i,j+1),sum(i+1,j),1);
                road(sum(i+1,j),sum(i,j+1),1);
            }
            else
            {
                road(sum(i,j),sum(i+1,j+1),1);
                road(sum(i+1,j+1),sum(i,j),1);
                road(sum(i,j+1),sum(i+1,j),0);
                road(sum(i+1,j),sum(i,j+1),0);
            }
        }
    }
    for(int i=1;i<=m*n;++i) f[i]=1e9,h[i]=false;
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
    if(f[m*n]==1e9) printf("NO SOLUTION\n");
    else printf("%d\n",f[m*n]);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) abc();
    return 0;
}