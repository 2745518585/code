#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=1000001;
int n,b[N][2];
ll a[N];
bool h[N];
struct str
{
    int x;
    ll s;
    friend bool operator <(str a,str b)
    {
        return abs(a.s)>abs(b.s);
    }
};
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%lld",&a[i]);
            if(a[i]==0)
            {
                --n,--i;
                continue;
            }
            if((a[i]>0&&a[i-1]>0)||(a[i]<0&&a[i-1]<0))
            {
                a[i-1]+=a[i];
                --n,--i;
                continue;
            }
        }
        a[0]=a[n+1]=0;
        priority_queue<str> Q;
        for(int i=1;i<=n;++i)
        {
            a[i]=abs(a[i]);
            Q.push((str){i,a[i]});
        }
        for(int i=1;i<=n;++i)
        {
            b[i][0]=i-1,b[i][1]=i+1;
        }
        b[0][1]=1,b[n+1][0]=n;
        b[0][0]=0,b[n+1][1]=n+1;
        for(int i=0;i<=n+1;++i) h[i]=false;
        int s=n;
        while(s>1)
        {
            str k=Q.top();
            Q.pop();
            while(h[k.x]==true) k=Q.top(),Q.pop();
            a[k.x]=0;
            if(b[k.x][0]!=0&&b[k.x][1]!=n+1) a[k.x]=a[b[k.x][0]]+a[b[k.x][1]]-k.s,s-=2;
            else if(b[k.x][0]!=0) a[k.x]=a[b[k.x][0]],--s;
            else if(b[k.x][1]!=n+1) a[k.x]=a[b[k.x][1]],--s;
            h[b[k.x][0]]=h[b[k.x][1]]=true;
            b[k.x][0]=b[b[k.x][0]][0];
            b[k.x][1]=b[b[k.x][1]][1];
            b[b[k.x][0]][1]=b[b[k.x][1]][0]=k.x;
            Q.push((str){k.x,a[k.x]});
        }
        while(!Q.empty()&&h[Q.top().x]==true) Q.pop();
        if(!Q.empty()) printf("%lld\n",Q.top().s);
        else printf("0\n");
    }
    return 0;
}