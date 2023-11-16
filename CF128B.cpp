#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
const int N=1000001;
int n,k;
char a[N];
bool cmp(int x,int y)
{
    return a[x]<a[y];
}
void solve(vector<int> x,int l)
{
    if(l==n) return;
    vector<int> h[26];
    for(auto i:x)
    {
        if(i<=n) h[a[i]-'a'].push_back(i+1);
    }
    for(int i=0;i<=25;++i)
    {
        if(h[i].empty()) continue;
        k-=h[i].size();
        if(k<=0)
        {
            int p=h[i][0];
            for(int j=l+1;j>=1;--j)
            {
                printf("%c",a[p-j]);
            }
            exit(0);
        }
        solve(h[i],l+1);
    }
}
int main()
{
    scanf("%s%d",a+1,&k);
    n=strlen(a+1);
    vector<int> x;
    for(int i=1;i<=n;++i) x.push_back(i);
    solve(x,0);
    printf("No such line.");
    return 0;
}