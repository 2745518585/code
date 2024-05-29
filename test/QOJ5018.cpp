#include<cstdio>
#include<algorithm>
#include"nth.h"
#include"grader.cpp"
namespace Alice
{
    using namespace std;
    int n,m,k,l,r,t=20,w,a[M];
    void initA(bitset<M> _a,unsigned _m,unsigned _k)
    {
        m=_m,k=_k;
        for(int i=0;i<=M-1;++i) if(_a[i]) a[++n]=i;
        m-=n;
        if(k<=min(n,m)) l=1,r=k,k=0;
        else if(k<=max(n,m))
        {
            if(n<=m) l=0,r=n;
            else l=k-m,r=k;
            k=1;
        }
        else
        {
            l=k-m,r=n;
            k=1;
        }
        sendA((a[(l+r)/2]&(1<<t))!=0);
    }
    void receiveA(bool x)
    {
        if(l==r)
        {
            int p=(a[l]&(1<<t))!=0;
            // printf("A: %d %d %d %d: %d %d\n",l,r,t,w,p,x);for(int i=l;i<=r;++i) printf("%d ",a[i]);printf("\n");
            if(p==x) w|=(p<<t),--t;
            else if((p<x)^k) report(a[l]);
        }
        else if(r-l<=1)
        {
            int p=(a[l+k]&(1<<t))!=0;
            // printf("A: %d %d %d %d: %d %d\n",l,r,t,w,p,x);for(int i=l;i<=r;++i) printf("%d ",a[i]);printf("\n");
            if(p<x) l=r;
            else if(p>x) r=l;
            else
            {
                w|=(p<<t);
                if(p==1&&(a[l]&(1<<t))==0) a[l]=w;
                if(p==0&&(a[r]&(1<<t))!=0) a[r]=w|((1<<t)-1);
                --t;
            }
        }
        else
        {
            int p=(a[(l+r)/2]&(1<<t))!=0;
            // printf("A: %d %d %d %d: %d %d\n",l,r,t,w,p,x);for(int i=l;i<=r;++i) printf("%d ",a[i]);printf("\n");
            if(p^x)
            {
                if(p<x) l=(l+r)/2;
                else r=(l+r)/2;
            }
            else
            {
                w|=(p<<t);
                for(int i=l;i<=r;++i)
                {
                    if(p==1&&(a[i]&(1<<t))==0) a[i]=w;
                    if(p==0&&(a[i]&(1<<t))!=0) a[i]=w|((1<<t)-1);
                }
                --t;
            }
        }
        if(t==-1) report(w);
        if(l==r) sendA((a[l]&(1<<t))!=0);
        else if(r-l==1) sendA((a[l+k]&(1<<t))!=0);
        else sendA((a[(l+r)/2]&(1<<t))!=0);
    }
}
namespace Bob
{
    using namespace std;
    int n,m,k,l,r,t=20,w,a[M];
    void initB(bitset<M> _a,unsigned _m,unsigned _k)
    {
        m=_m,k=_k;
        for(int i=0;i<=M-1;++i) if(_a[i]) a[++n]=i;
        m-=n;
        if(k<=min(n,m)) l=1,r=k,k=0;
        else if(k<=max(n,m))
        {
            if(n<=m) l=0,r=n;
            else l=k-m,r=k;
            k=1;
        }
        else
        {
            l=k-m,r=n;
            k=1;
        }
        sendB((a[(l+r+1)/2]&(1<<t))!=0);
    }
    void receiveB(bool x)
    {
        if(l==r)
        {
            int p=(a[l]&(1<<t))!=0;
            // printf("B: %d %d %d %d: %d %d\n",l,r,t,w,p,x);for(int i=l;i<=r;++i) printf("%d ",a[i]);printf("\n");
            if(p==x) w|=(p<<t),--t;
            else if((p<x)^k) report(a[l]);
        }
        else if(r-l<=1)
        {
            int p=(a[l+k]&(1<<t))!=0;
            // printf("B: %d %d %d %d: %d %d\n",l,r,t,w,p,x);for(int i=l;i<=r;++i) printf("%d ",a[i]);printf("\n");
            if(p<x) l=r;
            else if(p>x) r=l;
            else
            {
                w|=(p<<t);
                if(p==1&&(a[l]&(1<<t))==0) a[l]=w;
                if(p==0&&(a[r]&(1<<t))!=0) a[r]=w|((1<<t)-1);
                --t;
            }
        }
        else
        {
            int p=(a[(l+r+1)/2]&(1<<t))!=0;
            // printf("B: %d %d %d %d: %d %d\n",l,r,t,w,p,x);for(int i=l;i<=r;++i) printf("%d ",a[i]);printf("\n");
            if(p^x)
            {
                if(p<x) l=(l+r+1)/2;
                else r=(l+r+1)/2;
            }
            else
            {
                w|=(p<<t);
                for(int i=l;i<=r;++i)
                {
                    if(p==1&&(a[i]&(1<<t))==0) a[i]=w;
                    if(p==0&&(a[i]&(1<<t))!=0) a[i]=w|((1<<t)-1);
                }
                --t;
            }
        }
        if(t==-1) report(w);
        if(l==r) sendB((a[l]&(1<<t))!=0);
        else if(r-l==1) sendB((a[l+k]&(1<<t))!=0);
        else sendB((a[(l+r+1)/2]&(1<<t))!=0);
    }
}