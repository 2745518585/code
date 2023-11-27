#include<bits/stdc++.h>
using namespace std;
const int N=100010;
const double eps=1e-10;
int n;
inline bool same(double x,double y) { return fabs(x-y)<eps;}
struct Point {
    double x,y;
    inline bool operator<(const Point &t)const {
        if(!same(x,t.x)) return x<t.x;
        return y<t.y;
    }
    inline Point operator+(const Point &t)const {return {x+t.x,y+t.y};}
    inline Point operator-(const Point &t)const {return {x-t.x,y-t.y};} 
    inline Point operator*(const double &t)const {return {x*t,y*t};}//数乘
    inline double operator*(const Point &t)const {return x*t.y-y*t.x;} //叉积 
    inline double operator^(const Point &t)const {return x*t.x+y*t.y;} //点积  
}p[N],tmp[N];
struct Line {  Point s,v;};//点向式结构体
inline Point inter(Line l1,Line l2) {
    Point t1=l1.s+l1.v;
    double s1=l2.v*(l1.s-l2.s);
    double s2=(t1-l2.s)*l2.v;
    double t=s1/(s1+s2);
    return l1.s+l1.v*t;
} //求直线交点
double ans=1e18;
Point a[4]; //答案矩形4个顶点
inline Point get(Point p) {
    p.x=(fabs(p.x)<eps)?0:p.x;
    p.y=(fabs(p.y)<eps)?0:p.y;
    return p;
} //=0可能会输出0/-0 所以要判
inline void update(Line l1,Line l2,Line l3,Line l4) {
    Point b[4]={inter(l1,l2),inter(l2,l3),inter(l3,l4),inter(l4,l1)};
    double now=fabs(b[0]*b[1]+b[1]*b[2]+b[2]*b[3]+b[3]*b[0])/2;
    if(ans>now) {
        ans=now;
        for(int i=0;i<4;i++) a[i]=get(b[i]);
    }
} // 求4条直线围成的4边形面积 更新答案 注意直线顺序
inline Point rotate(Point p) { return {-p.y,p.x};} // 把p旋转90度
inline void getline(Line l1,Point p2,Point p3,Point p4) {
    Point _v=rotate(l1.v);
    Line l2={p2,_v},l3={p3,l1.v},l4={p4,_v};
    update(l1,l2,l3,l4);
} //确定一条直线和另外3个点 求出围成矩形的4条直线并更新答案
int stk[N],top;
void tb() {
    sort(p+1,p+n+1);
    for(int i=1;i<=n;i++) {
        while(top>1&&((p[i]-p[stk[top-1]])*(p[stk[top]]-p[stk[top-1]]))<eps) top--;
        stk[++top]=i;
    }
    int limit=top;
    for(int i=n;i>=1;i--) {
        while(top>limit&&((p[i]-p[stk[top-1]])*(p[stk[top]]-p[stk[top-1]]))<eps) top--;
        stk[++top]=i;
    }
    for(int i=1;i<=top;i++) tmp[i]=p[stk[i]];
    for(int i=1;i<=top;i++) p[i]=tmp[i];
    n=top-1;
}
inline double val(Point a,Point b,Point c) {
    return fabs((a-b)*(a-c));
} //三角形面积
void work() {
    for(int i=1,j=2,x=2,y=2;i<=n;i++) { //i x j y
        while(val(p[i],p[i+1],p[j])<val(p[i],p[i+1],p[j%n+1])) j=j%n+1;
        y=max(y,j);
        while(x!=j&&((p[i+1]-p[i])^(p[x+1]-p[x]))>-eps) x=x%n+1; //>=0 (锐角/直角) <=> >-eps
        while(y!=i&&((p[i+1]-p[i])^(p[y+1]-p[y]))<eps) y=y%n+1;
        printf("%d %d %d %d\n",i,x,j,y);
        getline(Line{p[i],p[i+1]-p[i]},p[x],p[j],p[y]);
    }
}
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lf%lf",&p[i].x,&p[i].y);
    tb();
    for(int i=1;i<=n+1;++i) printf("%.2lf %.2lf\n",p[i].x,p[i].y);
    work();
    printf("%.5lf\n",ans);
    reverse(a,a+4);// a 本身是顺时针的
    int pos=0;
    for(int i=1;i<4;i++)
        if(a[pos].y>a[i].y)
            pos=i;
    for(int i=pos;i<4;i++) printf("%.5lf %.5lf\n",a[i].x,a[i].y);
    for(int i=0;i<pos;i++) printf("%.5lf %.5lf\n",a[i].x,a[i].y);
    return 0;
}
