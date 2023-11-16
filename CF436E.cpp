#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=10000001;
int n,m,a[N],b[N],h[N];
struct str
{
    int x;
    ll s;
    str(){}
    str(int x0,int s0){x=x0,s=s0;}
    friend bool operator <(str a,str b)
    {
        return a.s>b.s;
    }
};
priority_queue<str> Q1,Q2,Q3,Q4,Q5;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
    {
        scanf("%d%d",&a[i],&b[i]);
        Q1.push(str(i,a[i]));
        Q2.push(str(i,b[i]));
    }
    Q1.push(str(n+1,1e18));
    Q2.push(str(n+1,1e18));
    Q3.push(str(n+2,1e18));
    Q4.push(str(n+2,1e18));
    Q5.push(str(n+3,1e18));
    h[n+1]=0,h[n+2]=1,h[n+3]=2;
    ll s=0;
    for(int i=1;i<=m;++i)
    {
        while(Q1.size()>1&&h[Q1.top().x]!=0) Q1.pop();
        while(Q2.size()>1&&h[Q2.top().x]!=0) Q2.pop();
        while(Q3.size()>1&&h[Q3.top().x]!=1) Q3.pop();
        while(Q4.size()>1&&h[Q4.top().x]!=1) Q4.pop();
        while(Q5.size()>1&&h[Q5.top().x]!=2) Q5.pop();
        ll p1=Q1.top().s,p2=Q3.top().s,p3=Q2.top().s+Q4.top().s,p4=Q2.top().s+Q5.top().s;
        if(p1<=p2&&p1<=p3&&p1<=p4)
        {
            s+=p1;
            int z=Q1.top().x;
            Q1.pop();
            h[z]=1;
            Q3.push(str(z,b[z]-a[z]));
            Q4.push(str(z,-a[z]));
        }
        else if(p2<=p3&&p2<=p4)
        {
            s+=p2;
            int z=Q3.top().x;
            Q3.pop();
            h[z]=2;
            Q5.push(str(z,a[z]-b[z]));
        }
        else if(p3<=p4)
        {
            s+=p3;
            int z1=Q2.top().x,z2=Q4.top().x;
            Q2.pop(),Q4.pop();
            h[z1]=2,h[z2]=0;
            Q5.push(str(z1,a[z1]-b[z1]));
            Q1.push(str(z2,a[z2]));
            Q2.push(str(z2,b[z2]));
        }
        else
        {
            s+=p4;
            int z1=Q2.top().x,z2=Q5.top().x;
            Q2.pop(),Q5.pop();
            h[z1]=2,h[z2]=1;
            Q5.push(str(z1,a[z1]-b[z1]));
            Q3.push(str(z2,b[z2]-a[z2]));
            Q4.push(str(z2,-a[z2]));
        }
    }
    printf("%lld\n",s);
    for(int i=1;i<=n;++i)
    {
        printf("%d",h[i]);
    }
    return 0;
}