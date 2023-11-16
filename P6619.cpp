#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=5000001;
int m,q,c[N];
ll T1[N],T2[N];
struct str
{
    int z,t,x,y;
}b[N];
void add(ll *T,int x,ll k)
{
    while(x<=q) T[x]+=k,x+=(x&-x);
}
ll sum(ll *T,int x)
{
    ll s=0;
    while(x>=1) s+=T[x],x-=(x&-x);
    return s;
}
int main()
{
    scanf("%d",&m);
    for(int i=1;i<=m;++i)
    {
        scanf("%d",&b[i].z);
        if(b[i].z==1)
        {
            scanf("%d%d%d",&b[i].t,&b[i].x,&b[i].y);
            if(b[i].t==1) ++b[i].x;
            c[++q]=b[i].x;
        }
        else
        {
            scanf("%d",&b[i].x);
        }
    }
    sort(c+1,c+q+1);
    q=unique(c+1,c+q+1)-c-1;
    for(int i=1;i<=m;++i)
    {
        if(b[i].z==1) b[i].x=lower_bound(c+1,c+q+1,b[i].x)-c;
    }
    for(int i=1;i<=m;++i)
    {
        int z=b[i].z;
        if(z==1)
        {
            int t=b[i].t,x=b[i].x,y=b[i].y;
            if(t==0) add(T1,x,y);
            else add(T2,x,y);
        }
        else
        {
            int x=b[i].x;
            if(b[x].t==0) add(T1,b[x].x,-b[x].y);
            else add(T2,b[x].x,-b[x].y);
        }
        int x=0;
        ll w1=0,w2=sum(T2,q);
        for(int t=(1<<20);t>=1;t>>=1)
        {
            if(x+t<=q&&w1+T1[x+t]<w2-T2[x+t])
            {
                w1+=T1[x+t];
                w2-=T2[x+t];
                x+=t;
            }
        }
        int y=0;
        ll w4=sum(T2,q),p=w4-sum(T2,x+1);
        for(int t=(1<<20);t>=1;t>>=1)
        {
            if(y+t<=q&&w4-T2[y+t]>=p)
            {
                w4-=T2[y+t];
                y+=t;
                t<<=1;
            }
        }
        ll w3=sum(T1,y);
        if(min(w1,w2)==0&&min(w3,w4)==0)
        {
            printf("Peace\n");
            continue;
        }
        if(min(w1,w2)>min(w3,w4))
        {
            printf("%d %lld\n",c[x+1]-1,min(w1,w2)*2);
        }
        else
        {
            printf("%d %lld\n",c[y+1]-1,min(w3,w4)*2);
        }
    }
    return 0;
}