#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,m,a[N],f1[N],f2[N],f3[N];
bool h[N];
vector<int> b[N];
struct str1
{
    int l,r,k;
    str1() {}
    str1(int l,int r,int k):l(l),r(r),k(k) {}
};
vector<str1> b1[N];
struct str2
{
    int x,t;
    str2() {}
    str2(int x,int t):x(x),t(t) {}
};
vector<str2> b2[N];
namespace sgt1
{
    int T[N];
    void add(int x,int k)
    {
        while(x<=n) T[x]=max(T[x],k),x+=x&-x;
    }
    int sum(int x)
    {
        int s=0;
        while(x>=1) s=max(s,T[x]),x-=x&-x;
        return s;
    }
}
namespace sgt2
{
    int T[N];
    void add(int x,int k)
    {
        while(x<=n) T[x]+=k,x+=x&-x;
    }
    int sum(int x)
    {
        int s=0;
        while(x>=1) s+=T[x],x-=x&-x;
        return s;
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;++i) sgt1::T[i]=0;
    for(int i=1;i<=n;++i)
    {
        f1[i]=sgt1::sum(n-a[i]);
        sgt1::add(n-a[i]+1,i);
    }
    for(int i=1;i<=n;++i) sgt1::T[i]=0;
    for(int i=n;i>=1;--i)
    {
        f2[i]=n-sgt1::sum(n-a[i])+1;
        b[f2[i]].push_back(i);
        sgt1::add(n-a[i]+1,n-i+1);
    }
    for(int i=1;i<=n;++i) sgt1::T[i]=0,f3[i]=n+1;
    for(int i=n;i>=1;--i)
    {
        for(auto j:b[i])
        {
            f3[j]=n-sgt1::sum(a[j]-1)+1;
        }
        sgt1::add(a[i],n-i+1);
    }
    // for(int i=1;i<=n;++i) printf("%d ",f1[i]);printf("\n");
    // for(int i=1;i<=n;++i) printf("%d ",f2[i]);printf("\n");
    // for(int i=1;i<=n;++i) printf("%d ",f3[i]);printf("\n");
    for(int i=1;i<=n;++i)
    {
        b1[f1[i]+1].push_back(str1(f2[i],f3[i]-1,1));
        b1[i+1].push_back(str1(f2[i],f3[i]-1,-1));
        // printf("%d %d %d %d\n",f1[i]+1,i,f2[i],f3[i]-1);
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        b2[x].push_back(str2(y,i));
    }
    for(int i=1;i<=n;++i)
    {
        for(auto j:b1[i])
        {
            sgt2::add(j.l,j.k);
            sgt2::add(j.r+1,-j.k);
        }
        for(auto j:b2[i])
        {
            h[j.t]=sgt2::sum(j.x)!=0;
        }
    }
    for(int i=1;i<=m;++i)
    {
        if(h[i]) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}