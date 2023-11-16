#include<bits/stdc++.h>
using namespace std;
const int N=500001,M=26,K=3000001;
int n,m,q,a[K][M],s[N],l[N],s2[N],l2[N],c[K],d1[K],d2[K],f2[K],e[N],tot=1;
char b[K],b2[K];
vector<int> g1[K],g2[K];
map<int,int> f[K];
struct str
{
    int x,t,k;
}h[N];
bool cmp(str a,str b)
{
    return a.x<b.x;
}
void add(char x[],int t)
{
    int k=1;
    for(int i=1;i<=l[t];++i)
    {
        if(a[k][x[i]-'a']==0) a[k][x[i]-'a']=++tot;
        k=a[k][x[i]-'a'];
    }
    g1[k].push_back(t);
}
void add2(char x[],int t)
{
    int k=1;
    for(int i=1;x[i]!='*';++i)
    {
        if(a[k][x[i]-'a']==0) return;
        k=a[k][x[i]-'a'];
    }
    g2[k].push_back(t);
}
void add3(char x[],int t)
{
    int k=1;
    ++f2[1];
    if(!f[1].count(l[t])) f[1][l[t]]=1;
    else ++f[1][l[t]];
    for(int i=l[t];i>=1;--i)
    {
        if(a[k][x[i]-'a']==0)
        {
            a[k][x[i]-'a']=++tot;
            for(int j=0;j<=25;++j) a[tot][j]=0;
        }
        k=a[k][x[i]-'a'];
        if(!f[k].count(l[t])) f[k][l[t]]=1;
        else ++f[k][l[t]];
        ++f2[k];
    }
}
int find(char x[],int t)
{
    int k=1;
    for(int i=l2[t];x[i]!='*';--i)
    {
        if(a[k][x[i]-'a']==0) return 0;
        k=a[k][x[i]-'a'];
    }
    int s=f2[k];
    for(int i=0;i<l2[t]-1;++i)
    {
        if(f[k].count(i)) s-=f[k][i];
    }
    return s;
}
void dfs(int x)
{
    if(x==0) return;
    for(int i=0;i<g2[x].size();++i)
    {
        d1[g2[x][i]]=q;
    }
    for(int i=0;i<g1[x].size();++i)
    {
        c[++q]=g1[x][i];
    }
    g1[x].clear();
    for(int i=0;i<=25;++i)
    {
        dfs(a[x][i]);
    }
    for(int i=0;i<g2[x].size();++i)
    {
        d2[g2[x][i]]=q;
    }
    g2[x].clear();
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        s[i]=s[i-1]+l[i-1]+1;
        scanf("%s",b+s[i]+1);
        l[i]=strlen(b+s[i]+1);
        add(b+s[i],i);
    }
    for(int i=1;i<=m;++i)
    {
        s2[i]=s2[i-1]+l2[i-1]+1;
        scanf("%s",b2+s2[i]+1);
        l2[i]=strlen(b2+s2[i]+1);
        add2(b2+s2[i],i);
    }
    dfs(1);
    for(int i=1;i<=m;++i)
    {
        h[i*2-1]=(str){d1[i],i,-1};
        h[i*2]=(str){d2[i],i,1};
    }
    sort(h+1,h+m*2+1,cmp);
    tot=1;
    for(int i=0;i<=25;++i) a[1][i]=0;
    for(int i=1;i<=m*2;++i)
    {
        for(int j=h[i-1].x+1;j<=h[i].x;++j)
        {
            add3(b+s[c[j]],c[j]);
        }
        e[h[i].t]+=find(b2+s2[h[i].t],h[i].t)*h[i].k;
    }
    for(int i=1;i<=m;++i)
    {
        printf("%d\n",e[i]);
    }
    return 0;
}