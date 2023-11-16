#include<cstdio>
#include<algorithm>
using namespace std;
const int N=101;
int a[N][N],d[N],s,q;
bool b1[N][N],b2[N][N],b3[N][N];
struct str
{
    int x,s;
}c[N];
bool cmp(str a,str b)
{
    return a.s<b.s;
}
int sum(int x,int y)
{
    return (x-1)/3*3+(y-1)/3;
}
int num(int x,int y)
{
    return min(min(x,10-x),min(y,10-y))+5;
}
void dfs(int x,int y,int w)
{
    if(x==0)
    {
        s=max(s,w);
        return;
    }
    if(a[x][y]!=0)
    {
        if(y<9) dfs(x,y+1,w);
        else dfs(d[x],1,w);
    }
    for(int i=1;i<=9;++i)
    {
        if(b1[x][i]||b2[y][i]||b3[sum(x,y)][i]) continue;
        b1[x][i]=b2[y][i]=b3[sum(x,y)][i]=true;
        if(y<9) dfs(x,y+1,w+num(x,y)*i);
        else dfs(d[x],1,w+num(x,y)*i);
        b1[x][i]=b2[y][i]=b3[sum(x,y)][i]=false;
    }
}
int main()
{
    for(int i=1;i<=9;++i)
    {
        for(int j=1;j<=9;++j)
        {
            scanf("%d",&a[i][j]);
            if(a[i][j]==0) ++c[i].s;
            else
            {
                q+=a[i][j]*num(i,j);
                if(b1[i][a[i][j]]||b2[j][a[i][j]]||b3[sum(i,j)][a[i][j]])
                {
                    printf("-1");
                    return 0;
                }
                b1[i][a[i][j]]=b2[j][a[i][j]]=b3[sum(i,j)][a[i][j]]=true;
            }
        }
    }
    for(int i=1;i<=9;++i) c[i].x=i;
    sort(c+1,c+9+1,cmp);
    for(int i=1;i<=9;++i)
    {
        d[c[i-1].x]=c[i].x;
    }
    dfs(d[0],1,q);
    printf("%d",s==0?-1:s);
    return 0;
}