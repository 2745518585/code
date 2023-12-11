#include<bits/stdc++.h>
using namespace std;
typedef long double ld;
std::mt19937 rd(std::random_device{}());
void register_rnd(int argc,char **argv)
{
    if(argc>=2) rd.seed(std::stoul(argv[1]));
}
int rnd(const int &llim,const int &ulim)
{
    return (std::uniform_int_distribution<int>(llim,ulim))(rd);
}
const int N=1000001;
const short dx[4]={-1,-1,1,1},dy[4]={-1,1,-1,1};
struct pt
{
    ld x=0,y=0;
    pt() {};
    pt(const ld &_x,const ld &_y):x(_x),y(_y) {};
};
ld dis(const pt &a,const pt &b)
{
    return sqrtl((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
ld dis(const pt &a,const pt &b,const ld &ta,const ld &tb)
{
    ld s=1e18;
    for(int i=0;i<=3;++i) for(int j=0;j<=3;++j) s=min(s,dis(pt(a.x+dx[i]*ta,a.y+dy[i]*ta),pt(b.x+dx[j]*tb,b.y+dy[j]*tb)));
    if(a.x+ta>b.x-tb&&b.x+tb>a.x-ta) s=min(s,abs(a.y-b.y)-ta-tb);
    if(a.y+ta>b.y-tb&&b.y+tb>a.y-ta) s=min(s,abs(a.x-b.x)-ta-tb);
    return s;
}
int n;
pt a[N];
ld b[N],R;
bool check(int x,const ld &t)
{
    for(int i=0;i<=n+1;++i)
    {
        if(x!=i&&dis(a[x],a[i],t,b[i])<R*2) return false;
    }
    return true;
}
int main(int argc,char **argv)
{
    register_rnd(argc,argv);
    ld x1=rnd(0,100000)/100.0,y1=rnd(0,100000)/100.0,x2=rnd(0,100000)/100.0,y2=rnd(0,100000)/100.0;
    n=rnd(0,20);
    a[0]=pt(x1,y1);
    a[n+1]=pt(x2,y2);
    ld w=1e18;
    for(int i=1;i<=n;++i)
    {
        a[i].x=rnd(0,100000)/100.0;
        a[i].y=rnd(0,100000)/100.0;
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=n+1;++j)
        {
            if(i!=j) w=min(w,dis(a[i],a[j]));
        }
    }
    R=rnd(0,w/2*100)/100.0;
    printf("%.2Lf %.2Lf %.2Lf\n%.2Lf %.2Lf\n%.2Lf\n",x1,y1,R,x2,y2,(ld)rnd(0,100000)/100.0);
    printf("%d\n",n);
    for(int i=1;i<=n;++i)
    {
        ld l=0,r=min(min(a[i].x,a[i].y),(ld)1000);
        while(r-l>1e-3)
        {
            ld z=(l+r)/2;
            if(check(i,z)) l=z;
            else r=z;
        }
        b[i]=rnd(0,l*100)/100.0;
    }
    for(int i=1;i<=n;++i)
    {
        printf("%.2Lf %.2Lf %.2Lf\n",a[i].x-b[i],a[i].y-b[i],b[i]*2);
    }
    return 0;
}