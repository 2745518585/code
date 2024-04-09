#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
typedef long long ll;
const int N=2000001;
int n,m,b[N],d[N];
char a[N],c[N];
vector<pair<int,int>> ans;
void print()
{
    printf("YES\n");
    printf("%d\n",ans.size());
    for(auto i:ans)
    {
        for(int j=i.first;j<=i.second;++j) printf("%c",a[j]);
        printf(" ");
    }
    printf("\n");
}
void solve()
{
    ans.clear();
    bool u=false;
    for(int i=1;i<=n;++i)
    {
        if(a[i]!=a[n-i+1])
        {
            u=true;
            break;
        }
    }
    if(u)
    {
        ans.push_back(make_pair(1,n));
        print();
        return;
    }
    m=0;
    for(int i=1;i<=n;++i)
    {
        if(a[i-1]!=a[i])
        {
            b[++m]=1;
            c[m]=a[i];
            d[m]=i;
        }
        else ++b[m],d[m]=i;
    }
    if(m%2==0)
    {
        for(int i=1;i<=m;i+=2)
        {
            ans.push_back(make_pair(d[i-1]+1,d[i+1]));
        }
        print();
        return;
    }
    for(int i=1;i<=m;i+=2)
    {
        if(b[1]!=b[i]||c[1]!=c[i])
        {
            ans.push_back(make_pair(1,d[i]));
            for(int j=i+1;j<=m;j+=2)
            {
                ans.push_back(make_pair(d[j-1]+1,d[j+1]));
            }
            print();
            return;
        }
    }
    for(int i=2;i<=m-1;++i)
    {
        if(b[i]!=1)
        {
            ans.push_back(make_pair(1,d[i]-1));
            ans.push_back(make_pair(d[i],n));
            print();
            return;
        }
    }
    for(int i=4;i<=m;i+=2)
    {
        if(c[i]!=c[i-2])
        {
            ans.push_back(make_pair(1,d[i-3]));
            ans.push_back(make_pair(d[i-3]+1,d[i]));
            ans.push_back(make_pair(d[i]+1,n));
            print();
            return;
        }
    }
    printf("NO\n");
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",a+1);
        n=strlen(a+1);
        solve();
    }
    return 0;
}