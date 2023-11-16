#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1001;
int m,n,q,p,w,a[N],b[N],c[N];
bool dfs(int x,int k)
{
    if(q-w<p) return false;
    if(x==0) return true;
    for(int i=k;i<=n;++i)
    {
        if(a[i]==a[i-1]&&i>k) continue;
        if(a[i]>=b[x])
        {
            bool u;
            a[i]-=b[x];
            if(a[i]<b[1]) w+=a[i];
            if(b[x-1]==b[x]) u=dfs(x-1,i);
            else u=dfs(x-1,1);
            if(a[i]<b[1]) w-=a[i];
            a[i]+=b[x];
            if(u==true) return true;
        }
    }
    return false;
}
int main()
{
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        scanf("%d",&a[i]);
        q+=a[i];
    }
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
    }
    sort(b+1,b+n+1);
    for(int i=1;i<=n;++i) c[i]=c[i-1]+b[i];
    int l=0,r=n;
    while(l<r)
    {
        int z=l+r+1>>1;
        p=c[z];
        if(dfs(z,1)) l=z;
        else r=z-1;
    }
    printf("%d",l);
    return 0;
}