#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=10000001;
int n,a[N],S[N];
struct str
{
    int w,s;
    str() {}
    str(int w,int s):w(w),s(s) {}
    friend bool operator<(str a,str b)
    {
        return a.w>b.w;
    }
};
priority_queue<str> Q;
struct tree
{
    int l,r;
}T[N];
void dfs(int x,int l,int r)
{
    if(x==0) return;
    Q.push(str(r-l+1,min(a[l-1],a[r+1])-a[x]));
    dfs(T[x].l,l,x-1);
    dfs(T[x].r,x+1,r);
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i) T[i].l=T[i].r=0;
        int t=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
            S[t+1]=0;
            while(t>0&&a[S[t]]<a[i]) --t;
            if(t>0) T[S[t]].r=i;
            T[i].l=S[t+1];
            S[++t]=i;
        }
        a[0]=a[n+1]=2e9;
        while(!Q.empty()) Q.pop();
        dfs(S[1],1,n);
        ll s=0,w=0;
        for(int i=1;i<=n-1;++i) s+=abs(a[i]-a[i+1]);
        s-=a[1]+a[n];
        for(int i=1;i<=n;++i) w+=a[i];
        while(s>0)
        {
            str x=Q.top();
            Q.pop();
            if(s-x.s*2>0) s-=x.s*2,w+=(ll)x.s*x.w;
            else
            {
                w+=(ll)((s+1)/2)*x.w;
                break;
            }
        }
        printf("%lld\n",w);
    }
    return 0;
}