#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
int n;
vector<pair<int,int>> ans;
int main()
{
    scanf("%d",&n);
    if(n%2==1)
    {
        for(int i=1;i<=n;++i)
        {
            for(int j=1;j<=n/2;++j)
            {
                ans.push_back(make_pair((i-j+n-1)%n+1,(i+j-1)%n+1));
            }
        }
    }
    else
    {
        for(int i=1;i<=n-1;++i)
        {
            ans.push_back(make_pair(i,n));
            for(int j=1;j<=(n-1)/2;++j)
            {
                ans.push_back(make_pair((i-j+(n-1)-1)%(n-1)+1,(i+j-1)%(n-1)+1));
            }
        }
    }
    for(auto i:ans) printf("%d %d\n",min(i.first,i.second),max(i.first,i.second));
    return 0;
}