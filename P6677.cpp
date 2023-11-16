#include<bits/stdc++.h>
using namespace std;
const int N=500001;
int n,sx,sy,f[N][2],g[N][2];
struct str
{
	int x,y,t;
}a[N];
bool cmp(str a,str b)
{
	return a.y-a.x<b.y-b.x;
}
int main()
{
	scanf("%d%d",&n,&n);
	char z[N];
	scanf("%s",z+1);
	for(int i=1;i<=n;++i)
	{
		f[i][0]=i-1;
		f[i][1]=i+1;
		f[i+n][0]=i+n-1;
		f[i+n][1]=i+n+1;
		g[i][0]=g[i+n][0]=z[i-1!=0?i-1:n]-'0';
		g[i][1]=g[i+n][1]=z[i]-'0';
	}
	for(int i=1;i<=n-3;++i)
	{
		scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].t);
		if(a[i].x>a[i].y) swap(a[i].x,a[i].y);
		if(i==1)
		{
			sx=a[i].x;
			sy=a[i].y;
			continue;
		}
		if(a[i].x>=sx&&a[i].x<=sy&&a[i].y>=sx&&a[i].y<=sy);
		else if((a[i].x<=sx||a[i].x>=sy)&&(a[i].y<=sx||a[i].y>=sy))
		{
			if(a[i].x<=sx) a[i].x+=n;
			if(a[i].y<=sx) a[i].y+=n;
			if(a[i].x>a[i].y) swap(a[i].x,a[i].y);
		}
		else
		{
			printf("neispravna triangulacija");
			return 0;
		}
	}
	sort(a+1,a+n-2,cmp);
	bool u=true;
	for(int i=1;i<=n-3;++i)
	{
		if(f[a[i].x][1]!=f[a[i].y][0])
		{
			printf("neispravna triangulacija");
			return 0;
		}
		if(g[a[i].x][1]==g[a[i].y][0]||a[i].t==g[a[i].x][1]||a[i].t==g[a[i].y][0]) u=false;
		f[a[i].x][1]=a[i].y,f[a[i].y][0]=a[i].x;
		g[a[i].x][1]=g[a[i].y][0]=a[i].t;
	}
	if(f[sy][1]!=f[sx+n][0])
	{
		printf("neispravna triangulacija");
		return 0;
	}
	if(g[sy][1]==g[sx+n][0]||g[sx][1]==g[sy][1]||g[sx][1]==g[sx+n][0]) u=false;
	if(u==true) printf("tocno");
	else printf("neispravno bojenje");
	return 0;
}