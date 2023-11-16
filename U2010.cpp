#include<cstdio>
using namespace std;
typedef long long ll;
const int N=10001;
int q,q2=0,u=1,v=1,b[N];
ll n,m;
struct road
{
    int x,y;
    road(){}
    road(int x,int y):x(x),y(y){}
}a[N];
int main()
{
    scanf("%lld",&n);
    if(n<0) n=-n,v=-v;
    while((1ll<<(m+1))<=n) ++m;
    b[++q]=1;
    ++q;
    b[q]=b[q-1]+1;
    a[++q2]=road(1,2);
    for(ll i=m;i>=0;--i)
    {
        if(i<m)
        {
            ++q;
            b[q]=b[q-1]+3;
            for(int j=b[q-1]+1;j<=b[q];++j)
            {
                for(int k=b[q-2]+1;k<=b[q-1];++k)
                {
                    a[++q2]=road(k,j);
                }
            }
            u=-u;
        }
        if((n&(1ll<<i))!=0)
        {
            if(u==1)
            {
                ++q;
                b[q]=b[q-1]+2;
                for(int j=b[q-1]+1;j<=b[q];++j)
                {
                    for(int k=b[q-2]+1;k<=b[q-1];++k)
                    {
                        a[++q2]=road(k,j);
                    }
                }
                u=-u;
            }
            ++b[q];
            a[++q2]=road(1,b[q]);
        }
    }
    if(u==v)
    {
        ++q;
        b[q]=b[q-1]+2;
        for(int i=b[q-1]+1;i<=b[q];++i)
        {
            for(int j=b[q-2]+1;j<=b[q-1];++j)
            {
                a[++q2]=road(j,i);
            }
        }
        u=-u;
    }
    ++q;
    b[q]=b[q-1]+1;
    for(int i=b[q-2]+1;i<=b[q-1];++i)
    {
        a[++q2]=road(i,b[q]);
    }
    printf("%d %d\n",b[q],q2);
    for(int i=1;i<=q2;++i)
    {
        printf("%d %d\n",a[i].x,a[i].y);
    }
    return 0;
}