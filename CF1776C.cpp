#include<bits/stdc++.h>
using namespace std;
const int N=100001;
int n,m,t,a[N];
bool h[N];
int solve()
{
    sort(a+1,a+m+1);
    for(int i=1;i<=m;++i)
    {
        if(n/a[i]<=m-i)
        {
            t=a[i];
            return 1;
        }
    }
    return 0;
}
pair<int,int> solve1(int p)
{
    h[p]=true;
    int x=0,y=1e9,z=0;
    for(int i=1;i<=n;++i)
    {
        if(h[i])
        {
            if(z>=a[m]&&z<y) x=i-z,y=z;
            z=0;
        }
        else ++z;
    }
    if(z>=a[m]&&z<y-x+1) x=n-z+1,y=z;
    --m;
    return make_pair(x,x+a[m+1]-1);
}
int solve2(pair<int,int> z)
{
    --m;
    int x=z.first,y=z.second;
    if(y-x+1<t) return x;
    for(int i=x;i<=y;++i)
    {
        if(i%t==0) return i;
    }
    return x;
}
int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;++i)
    {
        scanf("%d",&a[i]);
    }
    if(solve()==0)
    {
        printf("Alessia\n");
        fflush(stdout);
        pair<int,int> z=solve1(0);
        printf("%d %d\n",z.second-z.first+1,z.first);
        fflush(stdout);
        while(m)
        {
            int x;
            scanf("%d",&x);
            pair<int,int> z=solve1(x);
            printf("%d %d\n",z.second-z.first+1,z.first);
            fflush(stdout);
        }
    }
    else
    {
        printf("Bernardo\n");
        fflush(stdout);
        while(m)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            printf("%d\n",solve2(make_pair(y,y+x-1)));
            fflush(stdout);
        }
    }
    return 0;
}