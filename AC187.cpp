#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,h[101],a1[101],a2[101];
bool dfs(int d,int x,int m1,int m2)
{
    if(m1+m2>d) return false;
    if(x==n) return true;
    bool u=false;
    for(int i=1;i<=m1;++i)
    {
        if(a1[i]<h[x])
        {
            int t=a1[i];
            a1[i]=h[x];
            if(dfs(d,x+1,m1,m2)) return true;
            a1[i]=t;
            u=true;
            break;
        }
    }  
    if(u==false)
    {
        a1[m1+1]=h[x];
        if(dfs(d,x+1,m1+1,m2)) return true;
    }
    u=false;
    for(int i=1;i<=m2;++i)
    {
        if(a2[i]>h[x])
        {
            int t=a2[i];
            a2[i]=h[x];
            if(dfs(d,x+1,m1,m2)) return true;
            a2[i]=t;
            u=true;
            break;
        }
    }
    if(u==false)
    {
        a2[m2+1]=h[x];
        if(dfs(d,x+1,m1,m2+1)) return true;
    }
    return false;
}
int main()
{
    while(1)
    {
        scanf("%d",&n);
        if(n==0) break;
        for(int i=0;i<n;++i) scanf("%d",&h[i]);
        int d=0;
        while(!dfs(d,0,0,0)) ++d;
        printf("%d\n",d);
    }
    return 0;
}