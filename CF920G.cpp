#include<cstdio>
#include<algorithm>
using namespace std;
const int N=10000001;
int mu[N],pri[N],spri,ipri[N];
int sum(int x,int p)
{
    int s=0;
    for(int i=1;i*i<=p;++i)
    {
        if(p%i==0)
        {
            s+=mu[i]*(x/i);
            if(p/i!=i) s+=mu[p/i]*(x/(p/i));
        }
    }
    return s;
}
int main()
{
    mu[1]=1;
    for(int i=2;i<=10000000;++i)
    {
        if(ipri[i]==false) pri[++spri]=i,mu[i]=-1;
        for(int j=1;j<=spri&&i*pri[j]<=10000000;++j)
        {
            ipri[i*pri[j]]=true;
            if(i%pri[j]==0) break;
            mu[i*pri[j]]=-mu[i];
        }
    }
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int x,p,k;
        scanf("%d%d%d",&x,&p,&k);
        k+=sum(x,p);
        int l=x+1,r=1e7;
        while(l<r)
        {
            int z=l+r>>1;
            if(sum(z,p)>=k) r=z;
            else l=z+1;
        }
        printf("%d\n",l);
    }
    return 0;
}