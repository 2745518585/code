#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
int n,q=1,m=0,a[1500001][27],g[1500001],r[1500001],f[1500001],h[1500001];
char z[201][1500001],c[1500001];
void build(char *x,int t)
{
    int k=1;
    for(int i=1;x[i];++i)
    {
        if(a[k][x[i]-'a']==0)
        {
            a[k][x[i]-'a']=++q;
        }
        k=a[k][x[i]-'a'];
    }
    g[t]=k;
}
void bfs()
{
    queue<int> Q;
    for(int i=0;i<=26;++i)
    {
        a[0][i]=1;
    }
    f[1]=0;
    Q.push(1);
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        for(int i=0;i<=26;++i)
        {
            if(a[k][i]!=0)
            {
                Q.push(a[k][i]);
                f[a[k][i]]=a[f[k]][i];
                ++r[a[f[k]][i]];
            }
            else
            {
                a[k][i]=a[f[k]][i];
            }
        }
    }
}
void abc()
{
    queue<int> Q;
    for(int i=1;i<=q;++i)
    {
        if(r[i]==0) Q.push(i);
    }
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        h[f[k]]+=h[k];
        --r[f[k]];
        if(r[f[k]]==0) Q.push(f[k]);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        cin>>z[i]+1;
        build(z[i],i);
        for(int j=1;z[i][j];++j)
        {
            c[++m]=z[i][j];
        }
        c[++m]='z'+1;
    }
    bfs();
    int x=1;
    for(int i=1;i<=m;++i)
    {
        x=a[x][c[i]-'a'];
        ++h[x];
    }
    abc();
    for(int i=1;i<=n;++i)
    {
        printf("%d\n",h[g[i]]);
    }
    return 0;
}