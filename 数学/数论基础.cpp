'目录： 
'1. 欧几里得                  卡常欧几里得 
'2. EX-GCD
'3. 筛                        线性筛 欧拉筛 莫比乌斯筛 
'4. 快速幂 
'5. 快速乘                    O(1)快速乘  卡常快速乘 
'6. 牛顿法迭代求根  
'7. 质因数分解 / 全因数分解 
'8. 原根 





'1. 欧几里得    
//有负数时会以绝对值较大的数的符号  作为gcd的符号 
inline ll gcd(ll a,ll b)
{
    return b?gcd(b,a%b):a;
} 
//卡常欧几里得  负数无效
inline int ctz(ll x) { return __builtin_ctzll(x); }
ll gcd(ll a, ll b) {
    if (!a) return b; if (!b) return a;
    int t = ctz(a | b);
    a >>= ctz(a);
    do {
        b >>= ctz(b);
        if (a > b) swap(a, b);
        b -= a;
    } while (b);
    return a << t;
} 







'2. 扩展欧几里得 
//若a 和 b 互素，那么 x 是 a 在模 b 下的逆元
ll ex_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll ret = ex_gcd(b, a % b, y, x);
    y -= a / b * x;
    return ret;
}






'3. 素数筛 
//素数筛 
const int MAXSIZE; 
int Mark[MAXSIZE];     //prime[0]起 
int prime[MAXSIZE];    //判断是否是一个素数  Mark 标记数组 index 素数个数  
int Prime(){	
	int index=0;
    for (int i = 2; i < MAXSIZE; i++){
        if(Mark[i]) continue;//如标记则跳过  
        prime[index++] = i;//否则得到一个素数
        for (int j = i + i; j < MAXSIZE; j += i) Mark[j] = 1;//标记目前得到的素数的i倍为非素数
    }
    return index;
}
//线性筛+欧拉函数
const LL p_max = 1E5 + 100;
LL phi[p_max];
void get_phi() {
    phi[1] = 1;
    static bool vis[p_max];
    static LL prime[p_max], p_sz, d;
    FOR (i, 2, p_max) {
        if (!vis[i]) {
            prime[p_sz++] = i;
            phi[i] = i - 1;
        }
        for (LL j = 0; j < p_sz && (d = i * prime[j]) < p_max; ++j) {
            vis[d] = 1;
            if (i % prime[j] == 0) {
                phi[d] = phi[i] * prime[j];
                break;
            }
            else phi[d] = phi[i] * (prime[j] - 1);
        }
    }
}
//线性筛+莫比乌斯函数
const LL p_max = 1E5 + 100;
LL mu[p_max];
void get_mu() {
    mu[1] = 1;
    static bool vis[p_max];
    static LL prime[p_max], p_sz, d;
    mu[1] = 1;
    FOR (i, 2, p_max) {
        if (!vis[i]) {
            prime[p_sz++] = i;
            mu[i] = -1;
        }
        for (LL j = 0; j < p_sz && (d = i * prime[j]) < p_max; ++j) {
            vis[d] = 1;
            if (i % prime[j] == 0) {
                mu[d] = 0;
                break;
            }
            else mu[d] = -mu[i];
        }
    }
} 









'4. 快速幂
//当相乘会爆long long 时需要配合快速乘使用  将乘法替换为快速乘 
ll bin(ll x, ll n, ll mod) {
    ll ret = mod != 1;
    for (x %= mod; n; n >>= 1, x = x * x % mod)
        if (n & 1) ret = ret * x % mod;
    return ret;
}








'5. 快速乘 
//基于快速幂O(logn)   相乘爆ll时需要使用 
ll mul(ll a, ll b, ll m) {
    ll ret = 0;
    while (b) {
        if (b & 1) {
            ret += a;
            if (ret >= m) ret -= m;
        }
        a += a;
        if (a >= m) a -= m;
        b >>= 1;
    }
    return ret;
}
//O(1)快速乘 
ll mul(ll u, ll v, ll p) {
    return (u * v - ll((long double) u * v / p) * p + p) % p;
}
ll mul(ll u, ll v, ll p) { // 卡常
    ll t = u * v - ll((long double) u * v / p) * p;
    return t < 0 ? t + p : t;
}





'6. 牛顿迭代法求根
ll sqrt(ll x) {
    if (x == 0) return 0;
    double last = 0;
    double res = 1;
    while (res != last)
    {
        last = res;
        res = (res + x / res) / 2;
    }
    return ll(res);
} 







'7. 质因数分解 /全因数分解 
//前置模板：素数筛
//带指数 
ll factor[30], f_sz, factor_exp[30];
void get_factor(ll x) {
    f_sz = 0;
    ll t = sqrt(x + 0.5);
    for (ll i = 0; pr[i] <= t; ++i)
        if (x % pr[i] == 0) {
            factor_exp[f_sz] = 0;
            while (x % pr[i] == 0) {
                x /= pr[i];
                ++factor_exp[f_sz];
            }
            factor[f_sz++] = pr[i];
        }
    if (x > 1) {
        factor_exp[f_sz] = 1;
        factor[f_sz++] = x;
    }
}
//不带指数
ll factor[30], f_sz;
void get_factor(ll x) {
    f_sz = 0;
    ll t = sqrt(x + 0.5);
    for (ll i = 0; pr[i] <= t; ++i)
        if (x % pr[i] == 0) {
            factor[f_sz++] = pr[i];
            while (x % pr[i] == 0) x /= pr[i];
        }
    if (x > 1) factor[f_sz++] = x;
} 

//全因数分解 O(sqrt(n))
vector<int> v;   //v中储存因数
v.clear();
for(int j=1;j<=sqrt(x);j++){
    if(x%j==0){
        v[i].push_back(j);
        if(x!=j*j)v[i].push_back(x/j);
    }
}
//sort(v.begin(),v.end());  //若需要对因数排序 





'8. 原根
//前置模板：素数筛，快速幂，分解质因数
//要求 p 为质数 
ll find_smallest_primitive_root(ll p) {
    get_factor(p - 1);
    FOR (i, 2, p) {
        bool flag = true;
        FOR (j, 0, f_sz)
            if (bin(i, (p - 1) / factor[j], p) == 1) {
                flag = false;
                break;
            }
        if (flag) return i;
    }
    assert(0); return -1;
}



//一类输出要求： 
//将答案化为X/Y的形式   求使   MY同余X（modP） 的M，保证M存在且唯一
//在P为质数时     MY 同余 X   这个式子做以下操作完全不影响结果，等价       
//				1.同余式左右两边同时乘以与P互质的m ——》 因此可一开始就通分，给特定Y，从而保证X是整数
//     			2.随时在其中一边对P取模   ——》 因此可以在运算中就对X取模 
//				3. a的n次幂的逆元==a逆元的n次幂取模 
