#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=5001;
int n,fa[N];
char a[N][N];
vector<pair<int,int>> ans;
int find(int x)
{
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%s",a[i]+i);
        }
        ans.clear();
        for(int i=1;i<=n+1;++i) fa[i]=i;
        bool v=false;
        for(int i=n;i>=1;--i)
        {
            for(int j=i;j<=n;++j)
            {
                if(a[i][j]=='0'||find(i)==find(j)) continue;
                int x=find(find(i)+1),p=find(j);
                fa[find(i)]=p;
                ans.push_back(make_pair(i,j));
                int u=0;
                while(x!=p)
                {
                    fa[x]=p;
                    ++u;
                    if(u==1) ans.push_back(make_pair(x,j));
                    else ans.push_back(make_pair(x,i));
                    x=find(x+1);
                }
            }
        }
        for(auto i:ans)
        {
            printf("%d %d\n",i.first,i.second);
        }
    }
    return 0;
}