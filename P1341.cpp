#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=150;
int m,q=1e9,w,b[N],c[N];
bool a[N][N];
bool dfs(int x,int t)
{
    if(t==m+1) return true;
    for(int i=1;i<=128;++i)
    {
        if(a[x][i]==true)
        {
            a[x][i]=a[i][x]=false;
            if(dfs(i,t+1))
            {
                c[t]=i;
                return true;
            }
            a[x][i]=a[i][x]=true;
        }
    }
    return false;
}
int main()
{
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        char x,y;
        cin>>x>>y;
        a[x][y]=a[y][x]=true;
        ++b[x];
        ++b[y];
    }
    for(int i=1;i<=128;++i)
    {
        if(b[i]&1)
        {
            q=min(q,i);
            ++w;
        }
    }
    if(w==1||w>=3)
    {
        printf("No Solution");
        return 0;
    }
    if(w==0)
    {
        for(int i=1;i<=128;++i)
        {
            if(b[i]>0)
            {
                q=i;
                break;
            }
        }
    }
    dfs(q,1);
    printf("%c",q);
    for(int i=1;i<=m;++i)
    {
        printf("%c",c[i]);
    }
    return 0;
}