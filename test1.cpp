#pragma GCC optimize("Ofast","inline")
#include<bits/stdc++.h>
#define mk(x,y) (point){x,y}
#define seg(x,y) (line){x,y}
#define db double
using namespace std;
const int N=2e5+50,M=1e7;
const db eps=1e-4,reps=1e-5,pi=acos(-1);

struct point
{
	db x,y;
	
	friend bool operator==(point a,point b){return fabs(a.x-b.x)<=reps&&fabs(a.y-b.y)<=reps;}
	friend bool operator!=(point a,point b){return fabs(a.x-b.x)>reps||fabs(a.y-b.y)>reps;}
	friend point operator+(point a,point b){return mk(a.x+b.x,a.y+b.y);}
	friend point operator-(point a,point b){return mk(a.x-b.x,a.y-b.y);}
	friend point operator*(point a,db b){return mk(a.x*b,a.y*b);}
	db dis(){return sqrt(x*x+y*y);}
	friend db dis(point a,point b){return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}
	point rotate(db t){return mk(x*cos(t)-y*sin(t),y*cos(t)+x*sin(t));};
	friend point tolen(point a,db x){return a*(x/a.dis());}
}pos;

db dot(point a,point b){return a.x*b.x+a.y*b.y;}
db cross(point a,point b){return a.x*b.y-a.y*b.x;}

struct line
{
	point a,b;
	
	point vec(){return b-a;}
}a[N];

point intersect(line a,line b)
{
	db s1=cross(b.a-a.a,b.b-a.a),s2=cross(b.b-a.b,b.a-a.b);
	return a.a+a.vec()*(s1/(s1+s2));
}

point perpend(line a,point b)
{
	return intersect(a,seg(b,b+a.vec().rotate(pi/2)));
}

int inter(db r,line a,point&A,point&B)
{
	point p=perpend(a,pos);db d=dis(p,pos);
	if(d>r)return 0;
	A=p+tolen(a.vec(),sqrt(r*r-d*d))-pos;
	B=p-tolen(a.vec(),sqrt(r*r-d*d))-pos;
	return 1;
}

int intersect(db r,line a,db&L,db&R)
{
	point A,B;
	if(!inter(r,a,A,B))return 0;
	L=atan2(A.x,A.y);R=atan2(B.x,B.y);
	if(L>R)swap(L,R);if(R-L>=pi)L+=pi*2,swap(L,R);
	L*=M,R*=M;
	return 1;
}

int n,k,id;

struct node
{
	int l,r;
	
	int chk(node x)
	{
		return max(x.l,l)<=min(x.r,r);
	}
}s[N];

db l[N],r[N],t[N];
int tmp[N],val[N];
vector<int>in[N];

void insert(int x,int d,int n)
{
	for(int i=x;i<=n;i+=(i&(-i)))val[i]+=d;
}

int find(int x)
{
	int ans=0;
	for(int i=x;i;i-=(i&(-i)))ans+=val[i];
	return ans;
}

struct ga
{
	point x;int id;
	
	friend bool operator<(ga a,ga b)
	{
		return atan2(a.x.x-pos.x,a.x.y-pos.y)<=atan2(b.x.x-pos.x,b.x.y-pos.y);
	}
}p[N];

int check(db l1,db r1,db l2,db r2)
{
	if(l1>=pi*M&&l2>=pi*M)return 0;
	
	if(l1==l2||r1==r2)return 1;
	if(l1>l2)swap(l1,l2),swap(r1,r2);
	if(r2>=r1&&l2<=r1)return 1;
//	if(r1>pi*M)return 0;
//	l1+=pi*2*M,r1+=pi*2*M;
//	if(l1==l2||r1==r2)return 1;
//	if(l1>l2)swap(l1,l2),swap(r1,r2);
//	if(r2>=r1&&l2<=r1)return 1;
	return 0;
}

int chk(db x)
{
	int cnt=0,cc=0,c=0;
	for(int i=1;i<=n;i++)
	{
		if(!intersect(x,a[i],l[cc+1],r[cc+1]))continue;
		cc++;t[++c]=l[cc];t[++c]=r[cc];
		if(r[cc]<=pi*M)
		{
			t[++c]=l[cc]+pi*2*M;t[++c]=r[cc]+pi*2*M;
			l[cc+1]=l[cc]+pi*2*M;r[cc+1]=r[cc]+pi*2*M;
			cc++;
		}
	}
	sort(t+1,t+1+c);
	for(int i=1;i<=cc;i++)
	{
		s[i]=(node){(int)(lower_bound(t+1,t+1+c,l[i])-t),(int)(lower_bound(t+1,t+1+c,r[i])-t)};
		in[s[i].l].push_back(s[i].r);
	}
//	for(int i=1;i<=cc;i++)
//	for(int j=i+1;j<=cc;j++)
//	cnt+=check(l[i],r[i],l[j],r[j]);
//	return cnt>=k;
	for(int i=1;i<=c;i++)
	{
		sort(in[i].begin(),in[i].end());
		for(auto x:in[i])
		{
			cnt+=find(c-i+1)-find(c-x);
			if(t[i]<pi*M)insert(c-x+1,1,c);
		}
		in[i].clear();
	}
	for(int i=1;i<=c;i++)val[i]=0;
	return cnt>=k;
}

main()
{
//	freopen("memory15.in","r",stdin);
//	freopen("out.txt","w",stdout);
	cerr<<fixed<<setprecision(10);
	cin>>n>>k>>pos.x>>pos.y>>id;
	for(int i=1;i<=n;i++)
	{
		int k,b;cin>>k>>b;
		a[i]=seg(mk(.0,b*1.0),mk(100.0,100*k+b*1.0));
//		if(k*pos.x+b==pos.y)cout<<"f21\n";
	}
	db l=0,r=1e15,ans=r;
	while(r-l>eps)
	{
		cerr<<l<<' '<<r<<'\n';
		db mid=(l+r)/2;
		if(chk(mid))ans=mid,r=mid-eps;
		else l=mid+eps;
	}
	cerr<<ans<<'\n'<<87990940.315648913383<<'\n'<<dis(pos,intersect(a[259],a[879]))<<'\n';
	int tot=0;
	for(int i=1;i<=n;i++)
	{
		point A,B;if(!inter(ans,a[i],A,B))continue;
		p[++tot]=(ga){A,i};if(A!=B)p[++tot]=(ga){B,i};
	}
	sort(p+1,p+1+tot);
	for(int i=1;i<=tot;i++)
	{
		ga la=p[(i-1+tot-1)%tot+1];
		if(fabs(ans-dis(intersect(a[la.id],a[p[i].id]),pos))<=ans*1e-6)
		{
			cerr<<dis(intersect(a[la.id],a[p[i].id]),pos)<<'\n';
			cout<<la.id<<' '<<p[i].id;
			return 0;
		}
	}
}
