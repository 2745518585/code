#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=6001;
int n,a[N][N],b[N];
bool h[N];
vector<pair<int,int>> ans;
void NO()
{
    printf("NO");
    exit(0);
}
void solve(vector<int> p)
{
    if(p.size()==1) return;
    int x=0;
    for(auto i:p)
    {
        if(a[i][i]==1&&b[i]<p.size()&&!h[i])
        {
            x=i;
            break;
        }
    }
    if(x==0)
    {
        vector<int> p1,p2,p3;
        for(auto i:p)
        {
            if(h[i]) p3.push_back(i);
            else if(a[i][i]==0) p1.push_back(i);
            else p2.push_back(i);
        }
        if(p3.size()==p.size())
        {
            for(int i=1;i<p3.size();++i) ans.push_back(make_pair(p3[i],p3[0]));
            return;
        }
        if(p2.size()==0||p1.size()<p2.size()+1) NO();
        for(int i=0;i<p2.size();++i)
        {
            ans.push_back(make_pair(p1[i],p2[i]));
            ans.push_back(make_pair(p2[i],p1[i+1]));
        }
        for(int i=p2.size()+1;i<p1.size();++i)
        {
            ans.push_back(make_pair(p1[i],p2[0]));
        }
        for(auto i:p3) ans.push_back(make_pair(i,p2[0]));
        return;
    }
    vector<int> p1,p2;
    for(auto i:p)
    {
        if(a[i][x]) p1.push_back(i);
        else p2.push_back(i);
    }
    for(auto i:p1)
    {
        for(auto j:p2)
        {
            if(a[i][j]) --b[j];
            if(a[j][i]) --b[i];
        }
    }
    int y=0;
    for(auto i:p2)
    {
        if(a[x][i]==0&&b[i]==p2.size())
        {
            if(y) NO();
            y=i;
        }
    }
    if(y==0) NO();
    for(auto i:p1)
    {
        for(auto j:p2)
        {
            if(j==y) continue;
            if(a[i][j]!=a[y][j]) NO();
        }
    }
    for(auto i:p2)
    {
        for(auto j:p1)
        {
            if(j==x) continue;
            if(a[i][j]!=a[x][j]) NO();
        }
    }
    h[x]=h[y]=true;
    ans.push_back(make_pair(x,y));
    solve(p1);
    solve(p2);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        static char z[N];
        scanf("%s",z+1);
        for(int j=1;j<=n;++j)
        {
            a[i][j]=z[j]-'0';
            b[j]+=a[i][j];
        }
    }
    if(n==1)
    {
        if(a[1][1]) printf("NO");
        else printf("YES");
        return 0;
    }
	for(int i=1;i<=n;i++) if(!a[i][i]&&b[i]!=0) NO();
    vector<int> p;
    for(int i=1;i<=n;++i) p.push_back(i);
    solve(p);
    printf("YES\n");
    for(auto i:ans)
    {
        printf("%d %d\n",i.first,i.second);
    }
    return 0;
}