#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100001;
int n,m,s,h[N];
bool u=false;
struct roads
{
    int p=1,t[N];
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
}a;
void dfs(int x,int k)
{
    h[x]=k;
    for(int i=a.t[x];i!=0;i=a.a[i].q)
    {
    	if(h[a.a[i].m]==-1) dfs(a.a[i].m,k^a.a[i].w);
        else if(((h[a.a[i].m]!=k)^a.a[i].w)==1)
		{
			u=true;
			return;
		}
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        char z[10];
        int x,y;
        scanf("%s%d%d",z,&x,&y);
        a.road(x,y,z[0]=='D');
        a.road(y,x,z[0]=='D');
    }
    for(int i=1;i<=n;++i) h[i]=-1;
    for(int i=1;i<=n;++i)
    {
        if(h[i]==-1)
        {
            dfs(i,0);
            ++s;
            if(u==true)
            {
                printf("0");
                return 0;
            }
        }
    }
    printf("1");
    for(int i=1;i<=s;++i) printf("0");
    return 0;
}