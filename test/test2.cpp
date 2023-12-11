#pragma GCC optimize("O2")
#include<bits/stdc++.h>
#define db double
#define seg(x,y) (line){x,y}
#define mk(x,y) (point){x,y}
using namespace std;
const int N=2e6+50;
const db eps=1e-6,pi=acos(-1),inf=1e32;

void write(db x,char t='\n'){if(fabs(x)<eps)x=0;printf("%.2lf%c",x,t);}
template<class T, class... Args> inline void write(T x, Args... args) { write(x, ' '), write(args...); }


struct point
{
	db x,y,k;
	friend point operator+(point a,point b){return mk(a.x+b.x,a.y+b.y);}
	friend point operator-(point a,point b){return mk(a.x-b.x,a.y-b.y);}
	friend point operator*(point a,db b){return mk(a.x*b,a.y*b);}
	db Atan2(){return atan2(y,x);}
	friend bool operator<(point a,point b){return a.k==b.k?a.x<b.x:a.k<b.k;}
	db len(){return sqrt(x*x+y*y);}
	void pre(point o){k=atan2(y-o.y,x-o.x);}
	friend bool operator==(point a,point b){a=a-b;return (fabs(a.x)<=eps)&(fabs(a.y)<=eps);}
	friend db dis(point a,point b){return (a-b).len();}
	friend point tolen(point a,db t){return a*(t/a.len());}
	void input(){scanf("%lf%lf",&x,&y);}
	void print(){printf("%.2lf %.2lf\n",x,y);}
	db angle(){return (y<0)*pi+atan(y/x);}
	point rotate(db t){return mk(x*cos(t)-y*sin(t),y*cos(t)+x*sin(t));}
}z,O;

bool equiv(db x,db y){return fabs(x-y)<=eps;}
db dot(point a,point b){return a.x*b.x+a.y*b.y;}
db cross(point a,point b){return a.x*b.y-a.y*b.x;}
db angle(point a,point b){if(a==z||b==z)return 0;return acos(dot(a,b)/a.len()/b.len());}
point mirror(point a,point b){return b+(b-a);}
bool zcmp(db x){return fabs(x)<=eps;}

struct line
{
	point a,b;
	
	point vec(){return b-a;}
	
	bool include(point x,int f=1)
	{
		if(f)return zcmp(cross(a-x,b-x));
		if(!zcmp(cross(a-x,b-x)))return 0;
		return (min(a.x,b.x)<=x.x+eps)&(max(a.x,b.x)+eps>=x.x)&(min(a.y,b.y)<=x.y+eps)&(max(a.y,b.y)+eps>=x.y);
	}
};

bool onright(line a,point s){return cross(a.a-s,a.b-s)<=0;}

int relation(line a,line b)
{
	if(a.include(b.a)&&a.include(b.b))return -1;
	if(zcmp(cross(a.vec(),b.vec())))return 0;
	return 1;
}

point intersect(line a,line b)
{
	db s1=cross(b.a-a.a,b.b-a.a),s2=cross(b.b-a.b,b.a-a.b);
	return a.a+(a.b-a.a)*(s1/(s1+s2));
}

point perpend(line a,point b)
{
	point d=b+(a.vec()).rotate(pi/2);
	return intersect(a,(line){b,d});
}

db dis(line a,point b,int f=1)
{
	if((a.a-a.b)==z)return -1;
	point p=perpend(a,b);
	if(a.include(p,0)||f)return dis(b,p);
	return min(dis(a.a,b),dis(a.b,b));
}

int n,m,cs,cc;
point to,p[N];

struct circle
{
	point o;db r;
	
	bool in(point x)
	{
		return r>dis(x,o)+eps;
	}
	
	bool in(line x)
	{
		return dis(x,o,0)+eps<r;
	}
}c[N],o;
	
int intersectnum(line a,line b)
{
	if(relation(a,b)!=1)return 0;
	point x=intersect(a,b);
	return (a.include(x,0)&&b.include(x,0));
}

struct square
{
	point a,dx,dy;
	
	bool in(point x)
	{
		if(x.x>a.x+eps&&eps+x.x<(a+dx+dy).x&&x.y>a.y+eps&&eps+x.y<(a+dx+dy).y)return 1;
		return 0;
	}
	
	bool in(line x)
	{
		if(in(x.a)||in(x.b))return 1;
		if(relation(seg(a,a+dx),x)==-1||relation(seg(a,a+dy),x)==-1||relation(seg(a+dx,a+dx+dy),x)==-1||relation(seg(a+dy,a+dx+dy),x)==-1)return 0;
		if(x.include(a)||x.include(a+dx)||x.include(a+dy)||x.include(a+dx+dy))return 0;
		int val=intersectnum(seg(a,a+dx),x)+intersectnum(seg(a,a+dy),x)+intersectnum(seg(a+dy,a+dy+dx),x)+intersectnum(seg(a+dx,a+dx+dy),x);
		return val==2;
	}
	
	bool chk(circle x)
	{
		return x.in(seg(a,a+dx))|x.in(seg(a,a+dy))|x.in(seg(a+dx,a+dx+dy))|x.in(seg(a+dy,a+dx+dy));
	}
}s[N];

bool chk(point x)
{
	for(int i=1;i<=cc;i++)if(c[i].in(x))return 1;
	for(int i=1;i<=cs;i++)if(s[i].in(x))return 1;
	return 0;
}

bool chk(line x)
{
	for(int i=1;i<=cc;i++)if(c[i].in(x))return 1;
	for(int i=1;i<=cs;i++)if(s[i].in(x))return 1;
	return 0;
}

bool chk(point o,point l,point r,point x)
{
	return onright(seg(o,r),x)&&!onright(seg(o,l),x);
}

bool chk(circle o,point l,point r,circle x,int f=0)
{
	if(f)swap(l,r);
	if(dis(o.o,x.o)>=o.r+x.r)return 0;
	if(x.in(l)||x.in(r))return 1;
	return chk(o.o,l,r,x.o);
}

bool chk(circle o,point l,point r,square x,int f=0)
{
	if(f)swap(l,r);
	if(x.in(l)||x.in(r))return 1;
	point a=x.a,b=a+x.dx,c=a+x.dy,d=a+x.dx+x.dy,t[6],q[6];int m=0,k=0;
	if(x.in(o.o))
	{
		if(dis(a,o.o)>o.r&&chk(o.o,l,r,a))return 1;
		if(dis(b,o.o)>o.r&&chk(o.o,l,r,b))return 1;
		if(dis(c,o.o)>o.r&&chk(o.o,l,r,c))return 1;
		if(dis(d,o.o)>o.r&&chk(o.o,l,r,d))return 1;
		return 0;
	}
	if(o.in(a))t[++m]=a;else q[++k]=a;
	if(o.in(b))t[++m]=b;else q[++k]=b;
	if(o.in(c))t[++m]=c;else q[++k]=c;
	if(o.in(d))t[++m]=d;else q[++k]=d;
	if(m==4)return 0;
	if(m==1)return chk(o.o,l,r,t[1]);
	if(m==2)return chk(o.o,l,r,q[1])|chk(o.o,l,r,q[2]);
	if(m==3)return chk(o.o,l,r,q[1]);
	if(!x.chk(o))return 0;
	return chk(o.o,l,r,a)+chk(o.o,l,r,b)+chk(o.o,l,r,c)+chk(o.o,l,r,d)>1;
}

bool chk(circle o,point l,point r)
{
	for(int i=1;i<=cc;i++)if(chk(o,l,r,c[i]))return 1;
	for(int i=1;i<=cs;i++)if(chk(o,l,r,s[i]))return 1;
	return 0;
}

db dis(circle o,point l,point r)
{
	r=r-o.o,l=l-o.o;
	return o.r*angle(l,r);
}

struct edge
{
	int u,v;db w;int nxt,f;
}e[N];

struct node
{
	int x;db w;
	
	friend bool operator<(node a,node b)
	{
		return a.w>b.w;
	}
};

int head[N],cnt;
int cl[N],sl[N],cr[N],sr[N];
db d[N],exval;

void add(int u,int v,db w,int f=0)
{
	e[++cnt]=(edge){u,v,w,head[u],f};head[u]=cnt;
	e[++cnt]=(edge){v,u,w,head[v],f};head[v]=cnt;
}

int popc(int x)
{
	int s=0;
	while(x) x^=x&-x,++s;
	return s;
}

void dij()
{
	double w=1e9;
	static double val0[N];
	for(int z=1;z<=cnt;z++) val0[z]=e[z].w;
	for(int x=0;x<=(1<<n)-1;++x)
	{
		for(int z=1;z<=cnt;z++)
		{
			e[z].w=val0[z];
			point u=p[e[z].u],v=p[e[z].v];
			for(int j=1;j<=n;j++)
			{
				if(x&(1<<(j-1))) continue;
				int F=0,G=0;
				for(int k=cl[j];k<=cr[j];k++)
				{
					if(c[k].in(u))F|=1;
					if(e[z].f)G|=chk(c[e[z].f],u,v,c[k],((z&1)^1));
					else G|=c[k].in(seg(u,v));
				}
				for(int k=sl[j];k<=sr[j];k++)
				{
					if(s[k].in(u))F|=1;
					if(e[z].f)G|=chk(c[e[z].f],u,v,s[k],((z&1)^1));
					else G|=s[k].in(seg(u,v));
				}
				if(!F&&G) e[z].w=1e9;
			}
		}
		priority_queue<node>q;
		for(int i=1;i<=m;i++)d[i]=inf;d[1]=0;
		q.push((node){1,0});
		while(!q.empty())
		{
			int x=q.top().x;db w=q.top().w;q.pop();
			if(!equiv(w,d[x]))continue;
			for(int i=head[x];i;i=e[i].nxt)
			{
				int v=e[i].v;
				if(d[v]>d[x]+e[i].w)
				{
					d[v]=d[x]+e[i].w;
					q.push((node){v,d[v]});
				}
			}
		}
		w=min(w,d[2]+exval*popc(x));
	}
	if(equiv(w,inf))w=0;
	write(w);
}

point dx=mk(1,0),dy=mk(0,1);

int find(circle o,point&a,point&b,point x)
{
	if(o.in(x))return 0;
	x=x-o.o;point rx=x;
	db angle=acos(o.r/x.len());
	x=tolen(x.rotate(angle),o.r);
	a=x+o.o;
	x=mirror(x,perpend(seg(O,rx),x));
	b=x+o.o;
	return 1;
}

int h[N];

bool cmp(int a,int b)
{
	return p[a]<p[b];
}

vector<int>in[N];

main()
{
	// freopen("in.txt","r",stdin);
	// freopen("out.txt","w",stdout);
	o.o.input(),scanf("%lf",&o.r);to.input();scanf("%lf",&exval);scanf("%d",&n);
	p[++m]=o.o,p[++m]=to;
	for(int i=1;i<=n;i++)
	{
		point x;db r;x.input();scanf("%lf",&r);
		cl[i]=cc+1;cr[i]=cc+4;sl[i]=cs+1;sr[i]=cs+2;
		p[++m]=x-dx*o.r;p[++m]=x-dy*o.r;c[++cc]=(circle){x,o.r};in[cc].push_back(m),in[cc].push_back(m-1);x=x+dx*r;
		p[++m]=x+dx*o.r;p[++m]=x-dy*o.r;c[++cc]=(circle){x,o.r};in[cc].push_back(m),in[cc].push_back(m-1);x=x+dy*r;
		p[++m]=x+dx*o.r;p[++m]=x+dy*o.r;c[++cc]=(circle){x,o.r};in[cc].push_back(m),in[cc].push_back(m-1);x=x-dx*r;
		p[++m]=x-dx*o.r;p[++m]=x+dy*o.r;c[++cc]=(circle){x,o.r};in[cc].push_back(m),in[cc].push_back(m-1);x=x-dy*r;
		s[++cs]=(square){x-dx*o.r,dx*(2*o.r+r),dy*r};
		s[++cs]=(square){x-dy*o.r,dx*r,dy*(2*o.r+r)};
	}
	for(int i=1;i<=cc;i++)if(equiv(dis(p[1],c[i].o),c[i].r))in[i].push_back(1);
	for(int i=1;i<=cc;i++)if(equiv(dis(p[2],c[i].o),c[i].r))in[i].push_back(2);
	if(zcmp(o.r))cc=0;int mm=m;
	for(int i=1;i<=cc;i++)
	for(int j=i+1;j<=cc;j++)
	{
		if(seg(O,dx).include(c[j].o-c[i].o))continue;
		if(seg(O,dy).include(c[j].o-c[i].o))continue;
		point x=c[j].o-c[i].o;x=x.rotate(pi/2);x=tolen(x,c[i].r);
		point A,B,C,D;
		A=c[i].o+x,B=c[i].o-x;C=c[j].o+x,D=c[j].o-x;
		p[++m]=A,p[++m]=C,add(m-1,m,dis(A,C)),in[i].push_back(m-1),in[j].push_back(m);
		p[++m]=B,p[++m]=D,add(m-1,m,dis(B,D)),in[i].push_back(m-1),in[j].push_back(m);
	}
	for(int i=1;i<=cc;i++)
	for(int j=i+1;j<=cc;j++)
	{
		point x=c[j].o-c[i].o;
		x=c[i].o+tolen(x,x.len()*c[i].r/(c[i].r+c[j].r));
		point A,B,C,D;
		if(!find(c[i],A,B,x))continue;
		if(!find(c[j],C,D,x))continue;
		if(!zcmp(cross(A-x,C-x)))swap(A,B);
		p[++m]=A,p[++m]=C,add(m-1,m,dis(A,C)),in[i].push_back(m-1),in[j].push_back(m);
		p[++m]=B,p[++m]=D,add(m-1,m,dis(B,D)),in[i].push_back(m-1),in[j].push_back(m);
	}
	for(int i=1;i<=mm;i++)
	for(int j=1;j<=cc;j++)if(dis(p[i],c[j].o)>c[j].r)
	{
		point x,y;if(!find(c[j],x,y,p[i]))continue;
		if(!seg(O,dx).include(p[i]-x)&&!seg(O,dy).include(p[i]-x))p[++m]=x,add(i,m,dis(p[i],x)),in[j].push_back(m);
		if(!seg(O,dx).include(p[i]-y)&&!seg(O,dy).include(p[i]-y))p[++m]=y,add(i,m,dis(p[i],y)),in[j].push_back(m);
	}
	for(int i=1;i<=cc;i++)
	{
		int top=0;
		for(auto j:in[i])h[++top]=j,p[j].pre(c[i].o);
		sort(h+1,h+1+top,cmp);h[top+1]=h[1];
		for(int j=1;j<=top;j++)add(h[j],h[j+1],dis(c[i],p[h[j]],p[h[j+1]]),i);
	}
	for(int i=1;i<=mm;i++)for(int j=i+1;j<=mm;j++)
	add(i,j,dis(p[i],p[j]));
	dij();
}
