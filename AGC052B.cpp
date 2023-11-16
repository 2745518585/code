#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,f1[N],f2[N];
struct str
{
    int x,w1,w2;
    str() {}
    str(int x,int w1,int w2):x(x),w1(w1),w2(w2) {}
};
vector<str> a[N];
void dfs(int x,int fa)
{
    for(auto i:a[x])
    {
        if(i.x==fa) continue;
        f1[i.x]=f1[x]^i.w1;
        f2[i.x]=f2[x]^i.w2;
        dfs(i.x,x);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n-1;++i)
    {
        int x,y,w1,w2;
        scanf("%d%d%d%d",&x,&y,&w1,&w2);
        a[x].push_back(str(y,w1,w2));
        a[y].push_back(str(x,w1,w2));
    }
    dfs(1,0);
    int w=0;
    for(int i=0;i<=30;++i)
    {
        int w1=0,w2=0;
        for(int j=1;j<=n;++j)
        {
            if(f1[j]&(1<<i)) ++w1;
            if(f2[j]&(1<<i)) ++w2;
        }
        if(w1!=w2) w^=(1<<i);
    }
    for(int i=1;i<=n;++i) f2[i]^=w;
    sort(f1+1,f1+n+1);
    sort(f2+1,f2+n+1);
    for(int i=1;i<=n;++i)
    {
        if(f1[i]!=f2[i])
        {
            printf("NO");
            return 0;
        }
    }
    printf("YES");
    return 0;
}