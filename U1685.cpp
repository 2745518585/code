#include<bits/stdc++.h>
using namespace std;
const int N=2000001;
int n,m,tot=1,a[N][27],g[N],f[N],h[N],l[N];
char b[N],c[N];
void add(char x[],int t)
{
    int k=1;
    for(int i=1;x[i];++i)
    {
        if(a[k][x[i]-'a']==0) a[k][x[i]-'a']=++tot;
        k=a[k][x[i]-'a'];
    }
    g[t]=k;
}
void bfs()
{
    queue<int> Q;
    for(int i=0;i<=26;++i) a[0][i]=1;
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
                f[a[k][i]]=a[f[k]][i];
                ++l[a[f[k]][i]];
                Q.push(a[k][i]);
            }
            else a[k][i]=a[f[k]][i];
        }
    }
}
void tpsort()
{
    queue<int> Q;
    for(int i=1;i<=tot;++i)
    {
        if(l[i]==0) Q.push(i);
    }
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        h[f[k]]+=h[k];
        --l[f[k]];
        if(l[f[k]]==0) Q.push(f[k]);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%s",b+m+1);
        add(b+m,i);
        m+=strlen(b+m+1);
        b[++m]='z'+1;
    }
    bfs();
    int x=1;
    for(int i=1;i<=m;++i)
    {
        x=a[x][b[i]-'a'];
        ++h[x];
    }
    tpsort();
    for(int i=1;i<=n;++i)
    {
        printf("%d\n",h[g[i]]);
    }
    return 0;
}