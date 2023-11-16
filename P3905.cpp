#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
int n,m,s,t,a[101][101],f[101];
bool h[101];
struct str
{
    int x,s;
    bool operator <(const str& x)const
    {
        return x.s<s;
    }
};
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        a[x][y]=-w;
        a[y][x]=-w;
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        a[x][y]=-a[x][y];
        a[y][x]=-a[y][x];
    }
    scanf("%d%d",&s,&t);
    priority_queue<str> q;
    q.push((str){s,0});
    for(int i=1;i<=n;++i) f[i]=1e9;
    f[s]=0;
    while(!q.empty())
    {
        int k=q.top().x;
        q.pop();
        for(int i=1;i<=n;++i)
        {
            if(a[k][i]!=0&&f[k]+max(0,a[k][i])<f[i])
            {
                f[i]=f[k]+max(0,a[k][i]);
                q.push((str){i,f[i]});
            }
        }
    }
    printf("%d",f[t]);
    return 0;
}