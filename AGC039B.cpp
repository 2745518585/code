#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=1001;
int n,f[N];
char a[N][N];
int bfs(int x)
{
    for(int i=1;i<=n;++i) f[i]=0;
    f[x]=1;
    queue<int> Q;
    Q.push(x);
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        for(int i=1;i<=n;++i)
        {
            if(a[k][i]=='1')
            {
                if(f[i]==0)
                {
                    f[i]=f[k]+1;
                    Q.push(i);
                }
                else if(abs(f[k]-f[i])!=1) return -1;
            }
        }
    }
    int s=0;
    for(int i=1;i<=n;++i) s=max(s,f[i]);
    return s;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%s",a[i]+1);
    }
    int s=-1;
    for(int i=1;i<=n;++i) s=max(s,bfs(i));
    printf("%d",s);
    return 0;
}