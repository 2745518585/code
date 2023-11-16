#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2000001;
int n,m,q,b[N],c[N],T[N],f[N],g[N],h[N];
bool d[N],e[N];
struct str
{
    int a,b,c;
    str(){}
    str(int a,int b,int c):a(a),b(b),c(c){}
}a[N];
bool cmp(str a,str b)
{
    if(a.a!=b.a) return a.a<b.a;
    if(a.b!=b.b) return a.b<b.b;
    return a.c<b.c;
}
bool cmp2(str a,str b)
{
    if(a.b!=b.b) return a.b<b.b;
    if(a.a!=b.a) return a.a<b.a;
    return a.c<b.c;
}
void add(int x,int k)
{
    while(x<=n)
    {
        T[x]+=k;
        x+=(x&-x);
    }
}
int sum(int x)
{
    int s=0;
    while(x>=1)
    {
        s+=T[x];
        x-=(x&-x);
    }
    return s;
}
void cdq(int b[],int n)
{
    if(n==1) return;
    int m=n>>1;
    cdq(b,m);
    cdq(b+m,n-m);
    for(int i=1;i<=n;++i) c[i]=b[i];
    int x=1,y=m+1;
    for(int i=1;i<=n;++i)
    {
        if(x<=m&&(y>n||a[c[x]].b<=a[c[y]].b))
        {
            b[i]=c[x];
            add(a[c[x]].c,h[c[x]]);
            ++x;
        }
        else
        {
            b[i]=c[y];
            g[c[y]]+=sum(a[c[y]].c);
            ++y;
        }
    }
    for(int i=1;i<=m;++i) add(a[c[i]].c,-h[c[i]]);
}
int find_f(int x)
{
    int z=x,t=1,w=sum(x-1);
    while(t>=1)
    {
        if(z-t>=1&&w-sum(z-t-1)==(x-(z-t))) z-=t,t<<=1;
        else t>>=1;
    }
    return z;
}
int find_b(int x)
{
    int z=x,t=1,w=sum(x-1);
    while(t>=1)
    {
        if(z+t<=n&&sum(z+t-1)-w==((z+t)-x)) z+=t,t<<=1;
        else t>>=1;
    }
    return z;
}
int main()
{
    scanf("%d %d\n",&n,&m);
    ++n;
    for(int i=1;i<=n-1;++i)
    {
        if(getchar()=='1')
        {
            add(i,1),d[i]=true;
            int z1=find_f(i),z2=find_b(i+1);
            a[++q]=str(-i,z1,i+1),h[q]=m;
            a[++q]=str(-i,z1,z2+1),h[q]=-m;
            a[++q]=str(-i,i+1,i+1),h[q]=-m;
            a[++q]=str(-i,i+1,z2+1),h[q]=m;
        }
    }
    for(int i=1;i<=m;++i)
    {
        char z[10];
        scanf("%s",z);
        if(z[0]=='t')
        {
            int x;
            scanf("%d",&x);
            int u;
            if(d[x]==false) add(x,1),d[x]=true,u=1;
            else add(x,-1),d[x]=false,u=-1;
            int z1=find_f(x),z2=find_b(x+1);
            a[++q]=str(i,z1,x+1),h[q]=u*(m-i);
            a[++q]=str(i,z1,z2+1),h[q]=-u*(m-i);
            a[++q]=str(i,x+1,x+1),h[q]=-u*(m-i);
            a[++q]=str(i,x+1,z2+1),h[q]=u*(m-i);
        }
        else if(z[0]=='q')
        {
            int x,y;
            scanf("%d%d",&x,&y);
            a[++q]=str(i,x,y);
            if(sum(y-1)-sum(x-1)==y-x) g[q]=-(m-i);
            e[q]=true;
        }
    }
    sort(a+1,a+q+1,cmp);
    for(int i=1;i<=q;++i) b[i]=i;
    for(int i=1;i<=n;++i) T[i]=0;
    cdq(b,q);
    for(int i=1;i<=q;++i)
    {
        if(e[i]==true) printf("%d\n",g[i]);
    }
    return 0;
}