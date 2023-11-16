#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;
int n,q=1,a[10000001][26],f[10000001],g[10000001],h[1000001];
void build(char *x,int t)
{
    int k=1;
    for(int i=1;x[i];++i)
    {
        if(a[k][x[i]-'a']==0)
        {
            a[k][x[i]-'a']=++q;
            g[q]=0;
            for(int i=0;i<=25;++i)
            {
                a[q][i]=0;
            }
        }
        k=a[k][x[i]-'a'];
    }
    g[k]=t;
}
void bfs()
{
    queue<int> Q;
    for(int i=0;i<=25;++i)
    {
        a[0][i]=1;
    }
    f[1]=0;
    Q.push(1);
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        for(int i=0;i<=25;++i)
        {
            if(a[k][i]!=0)
            {
                Q.push(a[k][i]);
                f[a[k][i]]=a[f[k]][i];
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
    char z[200][100];
    g[1]=0;
    for(int i=0;i<=25;++i)
    {
        a[1][i]=0;
    }
    for(int i=1;i<=n;++i)
    {
        cin>>z[i]+1;
        build(z[i],i);
    }
    bfs();
    char c[1000001];
    cin>>c+1;
    int m=strlen(c+1);
    int x=1;
    for(int i=1;i<=n;++i) h[i]=0;
    for(int i=1;i<=m;++i)
    {
        x=a[x][c[i]-'a'];
        int k=x;
        while(k!=0)
        {
            if(g[k]!=0) ++h[g[k]];
            k=f[k];
        }
    }
    int s=0;
    for(int i=1;i<=n;++i)
    {
        s=max(s,h[i]);
    }
    printf("%d\n",s);
    for(int i=1;i<=n;++i)
    {
        if(h[i]==s) cout<<z[i]+1<<endl;
    }
}
int main()
{
    scanf("%d",&n);
    while(n!=0)
    {
        abc();
        scanf("%d",&n);
    }
    return 0;
}