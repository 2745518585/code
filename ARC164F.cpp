#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,f[N];
vector<int> a[N],b;
void dfs(int x,int w)
{
    if(w%2==0)
    {
        for(auto i:a[x])
        {
            dfs(i,w^1);
            f[x]+=f[i];
        }
        ++f[x];
    }
    else
    {
        if(a[x].size()==0) b.push_back(0);
        int p=0;
        for(auto i:a[x])
        {
            dfs(i,w^1);
            if(f[i]>f[x]) f[x]=f[i],p=i;
        }
        for(auto i:a[x])
        {
            if(i!=p) b.push_back(f[i]);
        }
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=2;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        a[x].push_back(i);
    }
    dfs(1,1);
    b.push_back(f[1]);
    sort(b.begin(),b.end());
    int s=0;
    for(int i=0;i<b.size();++i)
    {
        if(i%2==0) s-=b[i];
        else s+=b[i];
    }
    printf("%d\n",(n+1)/2+s);
    return 0;
}