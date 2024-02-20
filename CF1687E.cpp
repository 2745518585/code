#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=2000001;
int n,q,a[N],c[N],f[N];
bool g[N],h[N];
vector<int> b[N];
int gcd(int a,int b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
void solve(int *f)
{
    for(int i=1;i<=n;++i) g[i]=false;
    for(int i=1;i<=1000000;++i) h[i]=false;
    q=0;
    for(int i=1;i<=n;++i)
    {
        if(h[a[i]]) continue;
        c[++q]=a[i];
        for(int j=1;a[i]*j<=1000000;++j) h[a[i]*j]=true;
    }
    int w=0;
    for(int i=1;i<=n;++i) w=gcd(w,a[i]);
    while(true)
    {
        int p=0;
        for(int i=1;i<=7;++i)
        {
            f[i]=c[rand()%q+1];
            p=gcd(p,f[i]);
        }
        if(p==w) break;
    }
    sort(g+1,g+7+1);
    // for(int i=1;i<=7;++i) printf("%d ",f[i]);printf("\n");
    for(int i=1;i<=7;++i) g[f[i]]=true;
    for(int i=1;i<=7;++i) f[i]=b[f[i]].back();
    int m=n;
    n=0;
    for(int i=1;i<=m;++i)
    {
        if(!g[a[i]]) a[++n]=a[i];
        else b[a[i]].pop_back(),g[a[i]]=false;
    }
}
int main()
{
    scanf("%d",&n);
    srand(n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
        b[a[i]].push_back(i);
    }
    sort(a+1,a+n+1);
    for(int i=1;i<=14;++i) f[i]=1;
    if(n) solve(f);
    if(n) solve(f+7);
    sort(f+1,f+14+1);
    int q=unique(f+1,f+14+1)-f-1;
    // for(int i=1;i<=q;++i) printf("%d ",f[i]);printf("\n");
    // return 0;
    int s=0;
    for(int i=0;i<=(1<<q)-1;++i)
    {
        int w=0;
        for(int j=1;j<=q;++j)
        {
            if(i&(1<<(j-1))) ++w;
        }
        if(w==0) continue;
        s+=abs(w-2);
    }
    printf("%d\n",s);
    for(int i=0;i<=(1<<q)-1;++i)
    {
        int w=0;
        for(int j=1;j<=q;++j)
        {
            if(i&(1<<(j-1))) ++w;
        }
        if(w==0) continue;
        int t=(w%2?-1:1)*(w-2);
        for(int j=1;j<=abs(t);++j)
        {
            printf("%d %d ",t<0,w);
            for(int k=1;k<=q;++k)
            {
                if(i&(1<<(k-1))) printf("%d ",f[k]);
            }
            printf("\n");
        }
    }
    return 0;
}