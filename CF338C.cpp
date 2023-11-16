#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1001;
int n,a[N][N],b[N],c[N];
bool cmp(int x,int y)
{
    return a[x][b[x]/2+1]>a[y][b[y]/2+1];
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&b[i]);
        for(int j=1;j<=b[i];++j)
        {
            scanf("%d",&a[i][j]);
        }
        c[i]=i;
    }
    sort(c+1,c+n+1,cmp);
    int s1=0,s2=0,t=0;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=b[c[i]]/2;++j) s1+=a[c[i]][j],s2+=a[c[i]][b[c[i]]-j+1];
        if(b[c[i]]%2==1)
        {
            ++t;
            if(t%2==1) s1+=a[c[i]][b[c[i]]/2+1];
            else s2+=a[c[i]][b[c[i]]/2+1];
        }
    }
    printf("%d %d",s1,s2);
    return 0;
}