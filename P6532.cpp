#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=300001;
int n,m,tot,rt1,rt2;
ll q1,q2,q,k,a1[N],a2[N],a[N],b1[N<<1],b2[N<<1],b[N<<1];
struct str
{
	ll x,y,w;
}d1[N];
struct str2
{
	ll x1,y1,x2,y2;
}d2[N];
ll sum(int x,int y)
{
	return (x-1)*q2+y;
}
struct tree
{
	ll k;
    int l,r,s,h,t;
}T[N<<2];
void pushup(int x)
{
    T[x].s=T[T[x].l].s+T[T[x].r].s+T[x].t;
}
void rotate_l(int &x)
{
    int p=T[x].r;
    T[x].r=T[p].l;
    T[p].l=x;
    T[p].s=T[x].s;
    x=p;
    pushup(x);
    pushup(T[x].l);
}
void rotate_r(int &x)
{
    int p=T[x].l;
    T[x].l=T[p].r;
    T[p].r=x;
    T[p].s=T[x].s;
    x=p;
    pushup(x);
    pushup(T[x].r);
}
void add(int &x,ll k)
{
    if(x==0)
    {
        x=++tot;
        T[x].l=T[x].r=0;
        T[x].s=T[x].t=1;
        T[x].k=k;
        T[x].h=rand()*rand()%1000000+1;
        return;
    }
    if(k==T[x].k) ++T[x].t;
    else if(k<T[x].k) add(T[x].l,k);
    else if(k>T[x].k) add(T[x].r,k);
    if(T[x].l!=0&&T[x].h>T[T[x].l].h) rotate_r(x);
    if(T[x].r!=0&&T[x].h>T[T[x].r].h) rotate_l(x);
    pushup(x);
}
void remove(int &x,ll k)
{
    if(x==0) return;
    if(k==T[x].k)
    {
        if(T[x].t>1)
        {
            --T[x].t;
            pushup(x);
            return;
        }
        if(T[x].l==0&&T[x].r==0)
        {
            x=0;
            return;
        }
        if(T[x].l!=0&&(T[x].r==0||T[T[x].l].h<T[T[x].r].h))
        {
            rotate_r(x);
            remove(T[x].r,k);
        }
        else
        {   
            rotate_l(x);
            remove(T[x].l,k);
        }
        pushup(x);
        return;
    }
    if(k<T[x].k) remove(T[x].l,k);
    else remove(T[x].r,k);
    pushup(x);
}
ll num(int x,ll k)
{
	if(x==0) return 0;
	if(T[x].k==k) return T[x].t;
	if(k<T[x].k) return num(T[x].l,k);
	else return num(T[x].r,k);
}
int main()
{
//	freopen("topovi.in","r",stdin);
//	freopen("topovi.out","w",stdout);
	scanf("%lld%d%d",&k,&n,&m);
	for(int i=1;i<=n;++i)
	{
		scanf("%lld%lld%lld",&d1[i].x,&d1[i].y,&d1[i].w);
		b1[++q1]=d1[i].x;
		b2[++q2]=d1[i].y;
	}
	for(int i=1;i<=m;++i)
	{
		scanf("%lld%lld%lld%lld",&d2[i].x1,&d2[i].y1,&d2[i].x2,&d2[i].y2);
		b1[++q1]=d2[i].x1,b1[++q1]=d2[i].x2;
		b2[++q2]=d2[i].y1,b2[++q2]=d2[i].y2;
	}
	sort(b1+1,b1+q1+1);
	sort(b2+1,b2+q2+1);
	q1=unique(b1,b1+q1+1)-b1-1;
	q2=unique(b2,b2+q2+1)-b2-1;
	for(int i=1;i<=n;++i)
	{
		d1[i].x=lower_bound(b1+1,b1+q1+1,d1[i].x)-b1;
		d1[i].y=lower_bound(b2+1,b2+q2+1,d1[i].y)-b2;
		b[++q]=sum(d1[i].x,d1[i].y);
	}
	for(int i=1;i<=m;++i)
	{
		d2[i].x1=lower_bound(b1+1,b1+q1+1,d2[i].x1)-b1;
		d2[i].y1=lower_bound(b2+1,b2+q2+1,d2[i].y1)-b2;
		d2[i].x2=lower_bound(b1+1,b1+q1+1,d2[i].x2)-b1;
		d2[i].y2=lower_bound(b2+1,b2+q2+1,d2[i].y2)-b2;
		b[++q]=sum(d2[i].x1,d2[i].y1);
		b[++q]=sum(d2[i].x2,d2[i].y2);
	}
	sort(b+1,b+q+1);
	q=unique(b,b+q+1)-b-1;
	for(int i=1;i<=n;++i)
	{
		int k=lower_bound(b+1,b+q+1,sum(d1[i].x,d1[i].y))-b;
		a[k]=d1[i].w;
		a1[d1[i].x]^=d1[i].w;
		a2[d1[i].y]^=d1[i].w;
	}
	ll s=0;
	for(int i=1;i<=q1;++i)
	{
		add(rt1,a1[i]);
	}
	for(int i=1;i<=q2;++i)
	{
		s+=num(rt1,a2[i]);
		add(rt2,a2[i]);
	}
	for(int i=1;i<=m;++i)
	{
		int k1=lower_bound(b+1,b+q+1,sum(d2[i].x1,d2[i].y1))-b,k2=lower_bound(b+1,b+q+1,sum(d2[i].x2,d2[i].y2))-b;
		remove(rt1,a1[d2[i].x1]);
		remove(rt2,a2[d2[i].y1]);
		s-=num(rt1,a2[d2[i].y1])+num(rt2,a1[d2[i].x1]);
		a1[d2[i].x1]^=a[k1];
		a2[d2[i].y1]^=a[k1];
		s+=num(rt1,a2[d2[i].y1])+num(rt2,a1[d2[i].x1]);
		add(rt1,a1[d2[i].x1]);
		add(rt2,a2[d2[i].y1]);
		a[k2]=a[k1],a[k1]=0;
		remove(rt1,a1[d2[i].x2]);
		remove(rt2,a2[d2[i].y2]);
		s-=num(rt1,a2[d2[i].y2])+num(rt2,a1[d2[i].x2]);
		a1[d2[i].x2]^=a[k2];
		a2[d2[i].y2]^=a[k2];
		s+=num(rt1,a2[d2[i].y2])+num(rt2,a1[d2[i].x2]);
		add(rt1,a1[d2[i].x2]);
		add(rt2,a2[d2[i].y2]);
		ll t1=num(rt1,0),t2=num(rt2,0);
		printf("%lld\n",(q1-t1)*(k-q2)+(q2-t2)*(k-q1)+(q1*q2-s));
	}
	return 0;
}