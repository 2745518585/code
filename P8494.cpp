#include<bits/stdc++.h>
using namespace std;
const int N=100001;
int m,s,a[N];
bool g[N],h[N];
void move_inside(int i);
void move_outside(int i);
int press_button();
void add(int x)
{
    if(h[x]==false) move_inside(x-1),++s;
    h[x]=true;
}
void del(int x)
{
    if(h[x]==true) move_outside(x-1),--s;
    h[x]=false;
}
int sum()
{
    return press_button();
}
int min_cardinality(int n)
{
    for(int i=1;i<=n;++i)
    {
        add(i);
        if(sum()>1) del(i);
        else ++m,g[i]=true;
    }
    int l=2,r=n/m;
    while(l<=r)
    {
        int z=l+r>>1;
        for(int i=1;i<=n;++i) a[i]=i;
        random_shuffle(a+1,a+n+1);
        for(int i=1;i<=n;++i)
        {
            if(g[a[i]]) continue;
            if(s>=m*z) break;
            add(a[i]);
            if(sum()>z) del(a[i]);
        }
        if(s>=m*z)
        {
            l=z+1;
            for(int i=1;i<=n;++i)
            {
                if(g[i]) continue;
                if(h[i]) g[i]=true;
            }
        }
        else
        {
            r=s/m;
            for(int i=1;i<=n;++i)
            {
                if(g[i]) continue;
                if(h[i]) del(i);
                else g[i]=true;
            }
        }
    }
    return r;
}