#include<cstdio>
#include<iostream>
const int N=21,K=100000,pow10[10]={1,10,100,1000,10000,100000};
int m,k,a[N][N],b[N],c[N],d[K+1];
bool g[6][K+1],g0[6][K+1],h[K+1],u=false;
char buf[1<<21],*p1=buf,*p2=buf;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
inline void init()
{
    register int t=0;
    for(register int i=2;i<=99999;++i)
    {
        if(h[i]==false) d[++t]=i;
        for(register int j=1;j<=t&&i*d[j]<=99999;++j)
        {
            h[i*d[j]]=true;
            if(i%d[j]==0) break;
        }
    }
    for(register int i=1;i<=t;++i)
    {
        if(d[i]<10000) continue;
        register int x=d[i],s=0;
        while(x!=0)
        {
            s+=x%10;
            x/=10;
        }
        if(s!=m) continue;
        g[1][d[i]/10000*10000]=true;
        g[2][d[i]/1000*1000]=true;
        g[3][d[i]/100*100]=true;
        g[4][d[i]/10*10]=true;
        g[5][d[i]]=true;
        g0[1][d[i]%10]=true;
        g0[2][d[i]%100]=true;
        g0[3][d[i]%1000]=true;
        g0[4][d[i]%10000]=true;
        g0[5][d[i]]=true;
    }
}
inline void dfs(register int x,register int y)
{
    if(y>5) ++x,y=1;
    if(x==6)
    {
        for(register int i=1;i<=5;++i)
        {
            for(register int j=1;j<=5;++j) putchar(a[i][j]+'0');
            putchar('\n');
        }
        putchar('\n');
        u=true;
        return;
    }
    register int r=-1;
    if(x==5||y==5)
    {
        if(x==5)
        {
            r=m-c[y+5];
            if(y==5)
            {
                if(r!=-1&&r!=m-c[11]) return;
                r=m-c[11];
            }
            else if(y==1)
            {
                if(r!=-1&&r!=m-c[12]) return;
                r=m-c[12];
            }
        }
        if(y==5)
        {
            if(r!=-1&&r!=m-c[x]) return;
            r=m-c[x];
        }
    }
    if(x==4&&y==2)
    {
        if(y==2)
        {
            if(r!=-1&&r!=c[6]-c[12]) return;
            r=c[6]-c[12];
        }
        else if(y==4)
        {
            if(r!=-1&&r!=((m+c[10]-c[4]-c[11])>>1)) return;
            r=((m+c[10]-c[4]-c[11])>>1);
        }
    }
    if(r!=-1)
    {
        register int p1=r*pow10[5-y],p2=r*pow10[5-x];
        if(((x==1||y==1)&&r==0)||!(g[y][b[x]+p1]&&g[x][b[y+5]+p2]&&(x==y?g[y][b[11]+p1]:1)&&(x+y==6?g0[x][b[12]+p1]:1))) return;
        b[x]+=p1,c[x]+=r,b[y+5]+=p2,c[y+5]+=r;
        if(x==y) b[11]+=p1,c[11]+=r;
        if(x+y==6) b[12]+=p1,c[12]+=r;
        a[x][y]=r;
        dfs(x,y+1);
        b[x]-=p1,c[x]-=r,b[y+5]-=p2,c[y+5]-=r;
        if(x==y) b[11]-=p1,c[11]-=r;
        if(x+y==6) b[12]-=p1,c[12]-=r;
    }
    else for(register int i=0;i<=9;++i)
    {
        register int p1=i*pow10[5-y],p2=i*pow10[5-x];
        if(((x==1||y==1)&&i==0)||!(g[y][b[x]+p1]&&g[x][b[y+5]+p2]&&(x!=y||g[y][b[11]+p1])&&(x+y!=6||g0[x][b[12]+p1]))) continue;
        b[x]+=p1,c[x]+=i,b[y+5]+=p2,c[y+5]+=i;
        if(x==y) b[11]+=p1,c[11]+=i;
        if(x+y==6) b[12]+=p1,c[12]+=i;
        a[x][y]=i;
        dfs(x,y+1);
        b[x]-=p1,c[x]-=i,b[y+5]-=p2,c[y+5]-=i;
        if(x==y) b[11]-=p1,c[11]-=i;
        if(x+y==6) b[12]-=p1,c[12]-=i;
    }
}
int main()
{
    m=read(),k=read();
    if(!m%3)
    {
        printf("NONE");
        return 0;
    }
    init();
    a[1][1]=k;
    b[1]=b[6]=b[11]=k*10000;
    c[1]=c[6]=c[11]=k;
    dfs(1,2);
    if(!u) printf("NONE");
    return 0;
}