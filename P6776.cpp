#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=10000001;
int n,m;
struct tree
{
    int l,r;
}T[N];
bool solve(vector<int> a)
{
    if(a.size()==0) return false;
    for(auto i:a)
    {
        if(T[i].l==0&&T[i].r==0) return true;
    }
    vector<int> a1,a2,a3,a4;
    for(auto i:a)
    {
        if(T[i].l==0) a1.push_back(T[i].r);
        if(T[i].r==0) a2.push_back(T[i].l);
        if(T[i].l&&T[i].r&&(T[T[i].l].l==0&&T[T[i].l].r==0)) a3.push_back(T[i].r);
        if(T[i].l&&T[i].r&&(T[T[i].r].l==0&&T[T[i].r].r==0)) a4.push_back(T[i].l);
    }
    return solve(a1)&&solve(a2)&&solve(a3)&&solve(a4);
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        n=0;
        scanf("%d",&m);
        vector<int> a;
        for(int i=1;i<=m;++i)
        {
            int k;
            scanf("%d",&k);
            bool u=true;
            for(int j=n+1;j<=n+k;++j)
            {
                scanf("%d%d",&T[j].l,&T[j].r);
                if(T[j].l!=0) T[j].l+=n;
                if(T[j].r!=0) T[j].r+=n;
            }
            for(int j=n+1;j<=n+k;++j)
            {
                if(T[j].l&&T[j].r&&(T[T[j].l].l||T[T[j].l].r)&&(T[T[j].r].l||T[T[j].r].r)) u=false;
            }
            if(u) a.push_back(n+1);
            n+=k;
        }
        if(solve(a)) printf("Almost Complete\n");
        else printf("No\n");
    }
    return 0;
}