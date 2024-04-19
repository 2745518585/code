#include<cstdio>
#include<algorithm>
using namespace std;
typedef unsigned long long ull;
typedef __int128_t lll;
const int N=101;
int n,m,k;
ull a[N],b[N];
lll qpow(lll a,int b)
{
    lll x=1,y=a;
    while(b)
    {
        if(b&1) x=x*y;
        y=y*y;
        b>>=1;
    }
    return x;
}
void add(ull x)
{
    for(int i=63;i>=0;--i)
    {
        if((x&(1ull<<i))==0) continue;
        if(a[i]==0)
        {
            a[i]=x;
            break;
        }
        x^=a[i];
    }
}
int main()
{
    scanf("%d%d",&m,&k);
    for(int i=1;i<=m;++i)
    {
        ull x;
        scanf("%llu",&x);
        add(x);
    }
    if(k>=3)
    {
        for(int i=0;i<=63;++i)
        {
            if(a[i]) b[++n]=a[i];
        }
        lll s=0;
        for(int i=0;i<=(1<<n)-1;++i)
        {
            ull w=0;
            for(int j=1;j<=n;++j)
            {
                if(i&(1<<(j-1))) w^=b[j];
            }
            s+=qpow(w,k);
        }
        printf("%llu",(ull)(s/(1<<n)));
        if(s%(1<<n)!=0) printf(".5");
        return 0;
    }
    if(k==1)
    {
        ull s=0;
        for(int i=0;i<=63;++i)
        {
            bool u=false;
            for(int j=0;j<=63;++j)
            {
                if(a[j]&(1ull<<i)) u=true;
            }
            if(u) s+=(1ull<<i);
        }
        printf("%llu",s/2);
        if(s%2) printf(".5");
        return 0;
    }
    ull s=0,t=0;
    for(int i=0;i<=63;++i)
    {
        for(int j=0;j<=63;++j)
        {
            int w1=0,w2=0;
            bool u1=false,u2=false;
            for(int k=0;k<=63;++k)
            {
                if(a[k]&(1ull<<i)) u1=true;
                if(a[k]&(1ull<<j)) u2=true;
                if((a[k]&(1ull<<i))&&(a[k]&(1ull<<j))) ++w1;
                if((a[k]&(1ull<<i))||(a[k]&(1ull<<j))) ++w2;
            }
            if(!u1||!u2) continue;
            if(w1==w2)
            {
                if(i+j-1>=0) s+=(1ull<<(i+j-1));
                else ++t;
            }
            else
            {
                if(i+j-2>=0) s+=(1ull<<(i+j-2));
                else ++t;
            }
        }
    }
    s+=t/2;
    printf("%llu",s);
    if(t%2) printf(".5");
    return 0;
}