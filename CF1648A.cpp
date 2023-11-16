#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000001;
int m,n;
ll T1[N],T2[N],T3[N];
void add(ll *T,int x,ll k)
{
    while(x<=n) T[x]+=k,x+=x&-x;
}
ll sum(ll *T,int x)
{
    ll s=0;
    while(x>=1) s+=T[x],x-=x&-x;
    return s;
}
struct str
{
    int x,y;
    str(){}
    str(int x,int y):x(x),y(y){}
};
vector<str> a[N];
int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            int x;
            scanf("%d",&x);
            a[x].push_back(str(i,j));
        }
    }
    ll s=0;
    for(int i=1;i<=100000;++i)
    {
        for(auto j:a[i])
        {
            s+=sum(T1,j.y)*(j.x+j.y)-sum(T2,j.y);
            s+=(sum(T3,n)-sum(T3,j.y))-(sum(T1,n)-sum(T1,j.y))*(j.y-j.x);
            add(T1,j.y,1);
            add(T2,j.y,j.y+j.x);
            add(T3,j.y,j.y-j.x);
        }
        for(auto j:a[i])
        {
            add(T1,j.y,-1);
            add(T2,j.y,-(j.y+j.x));
            add(T3,j.y,-(j.y-j.x));
        }
    }
    printf("%lld",s);
    return 0;
}