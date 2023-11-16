#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n;
bool f[N][3],g[N][3];
vector<int> a[N];
vector<pair<int,int>> ans;
void dfs(int x,int fa)
{
    f[x][0]=f[x][1]=f[x][2]=false;
    int v0=0,v1=0,v2=0;
    for(auto i:a[x])
    {
        if(i==fa) continue;
        dfs(i,x);
        if(f[i][0]&&f[i][1]) ++v2;
        else if(f[i][0]) ++v0;
        else if(f[i][1]) ++v1;
        else return;
    }
    if(v0<=v1+1&&v0+v2>=v1) f[x][2]=true;
    if((v0+1)<=v1+v2+1&&(v0+1)+v2>=v1) f[x][0]=true;
    if(v0<=(v1+1)+v2+1&&v0+v2>=(v1+1)) f[x][1]=true;
    // printf("%d | %d %d %d | %d %d %d\n",x,v0,v1,v2,f[x][0],f[x][1],f[x][2]);
}
void dfs2(int x,int fa,int t)
{
    std::vector<int> u0,u1;
    if(t==0) u0.push_back(x);
    else if(t==1) u1.push_back(x);
    for(auto i:a[x])
    {
        if(i==fa) continue;
        if(f[i][0]&&!f[i][1]) u0.push_back(i);
        else if(f[i][1]&&!f[i][0]) u1.push_back(i);
    }
    for(auto i:a[x])
    {
        if(i==fa) continue;
        if(f[i][0]&&f[i][1])
        {
            if(u0.size()<u1.size()) u0.push_back(i);
            else u1.push_back(i);
        }
    }
    while(!u0.empty())
    {
        if(u0.back()==x) ans.push_back(make_pair(x,fa));
        else dfs2(u0.back(),x,0);
        u0.pop_back();
        if(!u1.empty())
        {
            if(u1.back()==x) ans.push_back(make_pair(x,fa));
            else dfs2(u1.back(),x,1);
            u1.pop_back();
        }
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i) a[i].clear();
        for(int i=1;i<=n-1;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            a[x].push_back(y);
            a[y].push_back(x);
        }
        ans.clear();
        dfs(1,0);
        if(f[1][2])
        {
            printf("YES\n");
            dfs2(1,0,2);
            reverse(ans.begin(),ans.end());
            for(auto i:ans) printf("%d %d\n",i.first,i.second);
        }
        else printf("NO\n");
    }
    return 0;
}