#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;
int n,q=1,a[10000001][26],g[10000001],f[10000001];
bool h[1000001];
void build(char *x)
{
    int k=1;
    for(int i=1;x[i];++i)
    {
        if(a[k][x[i]-'a']==0) a[k][x[i]-'a']=++q;
        k=a[k][x[i]-'a'];
    }
    ++g[k];
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
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        char x[1000001];
        cin>>x+1;
        build(x);
    }
    bfs();
    char c[1000001];
    cin>>c+1;
    int m=strlen(c+1);
    int s=0,x=1;
    for(int i=1;i<=m;++i)
    {
        x=a[x][c[i]-'a'];
        int k=x;
        while(k!=0&&h[k]==false)
        {
            s+=g[k];
            h[k]=true;
            k=f[k];
        }
    }
    printf("%d",s);
}