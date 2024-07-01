#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int N=5000001;
int n,q,a[N],d[N],dl[N],dr[N];
vector<int> b[N];
int main()
{
    scanf("%d",&n);
    for(int i=(1<<n);i<=(1<<(n+1))-1;++i) d[i]=1,dl[i]=dr[i]=i;
    for(int i=(1<<n)-1;i>=1;--i) d[i]=d[i*2]+1,dl[i]=dl[i*2],dr[i]=dr[i*2+1];
    queue<int> Q;
    a[dl[1]]=a[dr[1]]=1;
    if(d[1]>1)
    {
        a[1]=a[dl[1]/2]=a[dr[1]/2]=2;
        Q.push(1);
        if(d[1]>2)
        {
            Q.push(dl[1]/2);
            Q.push(dr[1]/2);
        }
    }
    q=d[1]/2+1;
    while(!Q.empty())
    {
        int k=Q.front();
        Q.pop();
        if(k>1&&!a[k/2])
        {
            a[k/2]=a[k]+1;
            Q.push(k/2);
        }
        if(k<(1<<n)) for(int i:{k*2,k*2+1})
        {
            if(a[i]) continue;
            if(a[dl[i]]||a[dr[i]])
            {
                a[i]=a[k]+1;
                Q.push(i);
            }
            else
            {
                a[dl[i]]=a[dr[i]]=a[k];
                if(d[i]>1)
                {
                    a[i]=a[dl[i]/2]=a[dr[i]/2]=q+1;
                    Q.push(i);
                    if(d[i]>2)
                    {
                        Q.push(dl[i]/2);
                        Q.push(dr[i]/2);
                    }
                }
                q+=d[i]/2;
            }
        }
    }
    for(int i=1;i<=(1<<(n+1))-1;++i) b[a[i]].push_back(i);
    int s=0;
    for(int i=1;i<=q;++i)
    {
        if(b[i].size()) ++s;
    }
    printf("%d\n",s);
    for(int i=1;i<=q;++i)
    {
        if(b[i].size()==0) continue;
        printf("%d ",b[i].size());
        for(auto j:b[i]) printf("%d ",j);
        printf("\n");
    }
    return 0;
}