#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int N=101,M=18;
int n,m,q,t,w1,w2,r[N],f[1<<M][N];
bool h[N];
vector<pair<int,int>> a[N];
vector<int> p;
void dfs(int x)
{
    if(h[x]) return;
    p.push_back(x);
    h[x]=true;
    for(auto i:a[x])
    {
        if(i.second==w2) continue;
        dfs(i.first);
    }
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&w1,&w2);
    for(int i=1;i<=m;++i)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        a[x].push_back(make_pair(y,w));
        a[y].push_back(make_pair(x,w));
    }
    for(int i=1;i<=n;++i)
    {
        if(r[i]==0)
        {
            p.clear();
            dfs(i);
            if(p.size()>3)
            {
                ++q;
                for(auto i:p) r[i]=q;
            }
            else
            {
                --t;
                for(auto i:p) r[i]=t;
            }
        }
    }
    for(int i=0;i<=(1<<q)-1;++i)
    {
        for(int j=1;j<=n;++j) f[i][j]=1e9;
    }
    f[0][1]=0;
    queue<pair<int,int>> Q1,Q2;
    Q1.push(make_pair(0,1));
    while(!Q1.empty()||!Q2.empty())
    {
        int k,x;
        if(!Q1.empty()&&(Q2.empty()||f[Q1.front().first][Q1.front().second]<=f[Q2.front().first][Q2.front().second])) k=Q1.front().first,x=Q1.front().second,Q1.pop();
        else k=Q2.front().first,x=Q2.front().second,Q2.pop();
        for(auto i:a[x])
        {
            if(r[i.first]>0&&((k&(1<<(r[i.first]-1))))) continue;
            if(r[x]==r[i.first]&&i.second==w2) continue;
            int t=k;
            if(r[i.first]!=r[x]&&r[x]>0) t|=(1<<(r[x]-1));
            if(f[k][x]+i.second<f[t][i.first])
            {
                f[t][i.first]=f[k][x]+i.second;
                if(i.second==w1) Q1.push(make_pair(t,i.first));
                else Q2.push(make_pair(t,i.first));
            }
        }
    }
    for(int i=1;i<=n;++i)
    {
        int s=1e9;
        for(int j=0;j<=(1<<q)-1;++j) s=min(s,f[j][i]);
        printf("%d ",s);
    }
    return 0;
}