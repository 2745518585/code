#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=1000001;
int n,a[N],b[N][2],T[N];
vector<int> d;
int gcd(int a,int b)
{
    if(b==0) return a;
    return gcd(b,a%b);
}
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
int find(int x)
{
    int l=x,r=n+1,w=sum(x-1);
    while(l<r)
    {
        int z=l+r>>1;
        if(sum(z)>w) r=z;
        else l=z+1;
    }
    return l;
}
int main()
{
    int TOT;
    scanf("%d",&TOT);
    while(TOT--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i) T[i]=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i]);
            b[i][0]=i-1,b[i][1]=i+1;
        }
        b[1][0]=n,b[n][1]=1;
        for(int i=1;i<=n;++i)
        {
            if(gcd(a[i],a[b[i][1]])==1) add(i,1);
        }
        d.clear();
        int x=1;
        while(true)
        {
            int z=find(x);
            if(z==n+1)
            {
                z=find(1);
                if(z==n+1) break;
            }
            z=b[z][1];
            d.push_back(z);
            if(gcd(a[b[z][0]],a[z])==1) add(b[z][0],-1);
            if(gcd(a[z],a[b[z][1]])==1) add(z,-1);
            if(gcd(a[b[z][0]],a[b[z][1]])==1) add(b[z][0],1);
            b[b[z][0]][1]=b[z][1];
            b[b[z][1]][0]=b[z][0];
            x=b[z][1];
        }
        printf("%d ",d.size());
        for(auto i:d) printf("%d ",i);
        printf("\n");
    }
    return 0;
}