#include<cstdio>
#include<algorithm>
#include<vector>
#define DEBUG
#include"currency.h"
#include"grader.cpp"
namespace Solve
{
    using namespace std;
    typedef long long ll;
    const int N=1001;
    int id,q,ans[N];
    bool ipk[N],h[N];
    ll gcd(ll a,ll b)
    {
        if(b==0) return a;
        return gcd(b,a%b);
    }
    ll lcm(ll a,ll b)
    {
        if(a/gcd(a,b)>((ll)1e18)/b) return 2e18;
        else return a/gcd(a,b)*b;
    }
    ll solve1(ll lim=1e18)
    {
        for(int i=1;i<=1000;++i) h[i]=false;
        vector<ll> p;
        for(int i=200;i>=1;--i)
        {
            ll v=1;
            for(int j=1000/i;j>=1;--j)
            {
                if(h[i*j]==false)
                {
                    for(int k=1;k<=i*j;++k) if((i*j)%k==0) h[k]=true;
                    if(lcm(v,i*j)>lim) p.push_back(v),v=1;
                    v=lcm(v,i*j);
                }
            }
            sort(p.begin(),p.end(),greater<ll>());
            bool u=false;
            for(auto &i:p)
            {
                if(lcm(i,v)<=lim)
                {
                    i=lcm(i,v);
                    u=true;
                    break;
                }
            }
            if(!u) p.push_back(v);
        }
        p.pop_back();
        for(int i=1;i<=1000;++i) h[i]=true;
        for(auto i:p)
        {
            if(query(i))
            {
                for(int j=1;j<=1000;++j)
                {
                    if(i%j!=0) h[j]=false;
                }
            }
            else
            {
                for(int j=1;j<=1000;++j)
                {
                    if(i%j==0) h[j]=false;
                }
            }
        }
        vector<int> x;
        for(int i=1;i<=1000;++i) if(h[i]) x.push_back(i);
        while(x.size()>1)
        {
            int n=x.size(),p=0,w=n;
            for(int i=1;i<=1000;++i)
            {
                if(!ipk[i]) continue;
                int z=0;
                for(auto j:x)
                {
                    if(j%i==0) ++z;
                }
                if(abs(z*2-n)<w) w=abs(z*2-n),p=i;
            }
            ll v=1;
            for(auto i:x)
            {
                if(i%p!=0) v=lcm(v,i);
            }
            for(auto i:x)
            {
                if((i%p!=0)^(v%i==0)) exit(1);
            }
            vector<int> y;
            if(query(v))
            {
                for(auto i:x)
                {
                    if(i%p!=0) y.push_back(i);
                }
            }
            else
            {
                for(auto i:x)
                {
                    if(i%p==0) y.push_back(i);
                }
            }
            swap(x,y);
        }
        return x[0];
    }
    void main(int _id)
    {
        id=_id;
        for(int i=2;i<=1000;++i)
        {
            if([&](){
                for(int j=2;j*j<=i;++j) if(i%j==0) return false;
                return true;
            }())
            {
                for(int j=i;j<=1000;j*=i) ipk[j]=true;
            }
        }
        if(id<=2)
        {
            ans[++q]=solve1();
            answer(1,ans+1);
        }
        else if(id==3)
        {
            int x=solve1(1000);
            ans[++q]=x;
            int t;
            for(t=x-1;t>=1;--t)
            {
                if(x%t==0&&query(x*((ll)1e9)+t)) break;
            }
            if(t==0)
            {
                answer(1,ans+1);
                return;
            }
            int p1=t,p2=t*2;
            ll l=1,r=1e9;
            while(l<r)
            {
                ll z=l+r>>1;
                if(query(x*z+p1)) r=z;
                else l=z+1;
            }
            if(t==x/2)
            {
                ans[++q]=x*l+t;
                answer(2,ans+1);
                return;
            }
            ll q1=l;
            l=1,r=1e9;
            while(l<r)
            {
                ll z=l+r>>1;
                if(query(x*z+p2)) r=z;
                else l=z+1;
            }
            ll q2=l;
            printf("%d %lld %d %lld\n",p1,q1,p2,q2);
            if(q1>q2) swap(q1,q2),swap(p1,p2);
            int p=p2-p1,q=q2-q1;
            int v=p1,w=0;
            while(w!=1) v=(v+p)%x,w=(w+q)%(x/t);
            l=1,r=1e9;
            while(l<r)
            {
                ll z=l+r>>1;
                if(query(x*z+v)) r=z;
                else l=z+1;
            }
            ans[++q]=x*l+v;
            answer(q,ans+1);
        }
        else if(id==4)
        {
            for(int i=0;i<=1000;++i) h[i]=false;
            h[0]=true;
            for(int i=1;i<=1000;++i)
            {
                if(query(i)&&!h[i])
                {
                    ans[++q]=i;
                    for(int j=0;j<=1000-i;++j) h[j+i]|=h[j];
                }
            }
            answer(q,ans+1);
        }
    }
}
void solve(int id)
{
    Solve::main(id);
}