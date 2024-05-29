#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,m,b[N],f1[N],f2[N],s1,s2;
vector<int> a[N];
void dfs(int x,int fa,int *f)
{
    for(auto i:a[x])
    {
        if(i==fa) continue;
        f[i]=f[x]+1;
        dfs(i,x,f);
    }
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d%d%d",&n,&s1,&s2);
        for(int i=1;i<=n;++i) a[i].clear();
        for(int i=1;i<=n-1;++i)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            a[x].push_back(y);
            a[y].push_back(x);
        }
        f1[s1]=0;
        dfs(s1,0,f1);
        f2[s2]=0;
        dfs(s2,0,f2);
        int x=0;
        for(int i=1;i<=n;++i)
        {
            if(f1[i]==f2[i]||f1[i]==f2[i]-1)
            {
                if(x==0||f2[i]<f2[x]) x=i;
            }
        }
        f1[x]=0;
        dfs(x,0,f1);
        int s=0;
        for(int i=1;i<=n;++i) s=max(s,f1[i]);
        printf("%d\n",(n-1)*2-s+f2[x]);
    }
    return 0;
}