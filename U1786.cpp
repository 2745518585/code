#include<bits/stdc++.h>
#define max(x,y) x>y?x:y
const int N=10001,M=1000001;
int n,m,q,a[N],b[M],f[M],g[M];
bool h[N];
bool cmp(int a,int b)
{
    return a>b;
}
void dfs(register int x,register int t)
{
    if(b[x]>m/q) return;
    if(b[x]==m/q) ++x,t=0;
    if(x==q+1)
    {
        printf("%d",m/q);
        exit(0);
    }
    int p=0;
    for(register int i=max(g[m/q-b[x]],t+1);i<=n;++i)
    {
        if(h[i]==true||b[x]+a[i]>m/q||a[i]==p||f[m/q-b[x]-a[i]]==false) continue;
        b[x]+=a[i];
        h[i]=true;
        p=a[i];
        dfs(x,i);
        b[x]-=a[i];
        h[i]=false;
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        m+=a[i];
    }
    std::sort(a+1,a+n+1,cmp);
    f[0]=true;
    for(int i=1;i<=n;++i)
    {
        for(int j=m;j>=a[i];--j)
        {
            f[j]|=f[j-a[i]];
        }
    }
    int x=0;
    for(int i=m;i>=1;--i)
    {
        while(x+1<=n&&a[x+1]>i) ++x;
        g[i]=x+1;
    }
    for(q=m;q>=2;--q)
    {
        if(m%q!=0||m/q<a[1]||f[m/q]==false) continue;
        for(int j=1;j<=q;++j) b[j]=0;
        dfs(1,0);
    }
    printf("%d",m);
    return 0;
}