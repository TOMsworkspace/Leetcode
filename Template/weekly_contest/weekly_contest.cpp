#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define rrep(i, a, b) for(int i = a; i >= (b); --i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define subnb true
#define Lnb true
#define PB push_back
#define PF push_front
#define LB lower_bound
#define UB upper_bound
#define fr(x) freopen(x,"r",stdin)
#define fw(x) freopen(x,"w",stdout)
#define complete_unique(a) a.erase(unique(begin(a),end(a)),end(a))
#define mst(x, a) memset(x,a,sizeof(x))
#define all(a) begin(a),end(a)
#define rall(a) rbegin(a),rend(a)
#define MP make_pair
#define lowbit(x) ((x)&(-(x)))
#define bitcnt(x) (__builtin_popcountll(x))
#define lson (ind<<1)
#define rson (ind<<1|1)
#define se second
#define fi first
#define EX0 exit(0);

using ll = long long;
using ull = unsigned long long;
using db = double;
using ld = long double;
using VLL = std::vector<ll>;
using VI = std::vector<int>;
using PII = std::pair<int, int>;
using PLL = std::pair<ll, ll>;

using namespace __gnu_pbds; //required
using namespace std;
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
const ll mod = 1e9 + 7;

template<typename T, typename S>
inline bool upmin(T &a, const S &b) { return a > b ? a = b, 1 : 0; }

template<typename T, typename S>
inline bool upmax(T &a, const S &b) { return a < b ? a = b, 1 : 0; }

ull twop(ll x) { return 1ULL << x; }

ll MOD(ll a, ll m) {
    a %= m;
    if(a < 0)a += m;
    return a;
}

ll inverse(ll a, ll m) {
    a = MOD(a, m);
    if(a <= 1)return a;
    return MOD((1 - inverse(m, a) * m) / a, m);
}

template<typename T>
T sqr(T x) { return x * x; }

template<typename T>
ll sz(const T &x) { return x.size(); }

ll fast(ll a, ll b, ll mod) {
    a %= mod;
    if(b < 0)a = inverse(a, mod), b = -b;
    ll ans = 1;
    while(b) {
        if(b & 1)ans = ans * a % mod;
        a = a * a % mod;
        b /= 2;
    }
    return ans % mod;
}

string to_string(string s) { return '"' + s + '"'; }

string to_string(const char *s) { return to_string((string) s); }

string to_string(bool b) { return (b ? "true" : "false"); }

template<typename A, typename B>
string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }

template<typename A>
string to_string(A v) {
    bool first = true;
    string res = "{";
    for(const auto &x: v) {
        if(!first) { res += ", "; }
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}

void debug_out() { cerr << endl; }

template<typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    cerr << " " << to_string(H);
    debug_out(T...);
}

#ifdef LOCAL
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define dbg(...) do {} while(0)
#endif

struct SegTree {
    static const int maxn = 100010;
    
    struct node {
        int l, r;
        int ans, pre, suf;
        
        int full() {
            return r - l + 1 == pre;
        }
    };
    
    node no[maxn * 4];
    
    void push_up(int ind) {
        no[ind].ans = 0;
        upmax(no[ind].ans, no[lson].ans);
        upmax(no[ind].ans, no[rson].ans);
        upmax(no[ind].ans, no[lson].suf + no[rson].pre);
        if(no[lson].full()) {
            no[ind].pre = no[lson].pre + no[rson].pre;
        } else {
            no[ind].pre = no[lson].pre;
        }
        if(no[rson].full()) {
            no[ind].suf = no[lson].suf + no[rson].suf;
        } else {
            no[ind].suf = no[rson].suf;
        }
    }
    
    void push_down(int ind) {
    }
    
    void build(int l, int r, int ind) {
        no[ind].l = l;
        no[ind].r = r;
        no[ind].ans = no[ind].suf = no[ind].pre = 0;
        if(l == r) {
        
        } else {
            int mid = (l + r) / 2;
            build(l, mid, lson);
            build(mid + 1, r, rson);
            push_up(ind);
        }
    }
    
    void update(int l, int r, int ind, int val) {
        if(l > no[ind].r || r < no[ind].l)return;
        if(l <= no[ind].l && no[ind].r <= r) {
            no[ind].ans = no[ind].suf = no[ind].pre = val;
        } else {
            push_down(ind);
            update(l, r, lson, val);
            update(l, r, rson, val);
            push_up(ind);
        }
    }
    
    void query(int l, int r, int ind, int &ans) {
        if(l > no[ind].r || r < no[ind].l)return;
        if(l <= no[ind].l && no[ind].r <= r) {
            upmax(ans, no[ind].ans);
        } else {
            push_down(ind);
            query(l, r, lson, ans);
            query(l, r, rson, ans);
            push_up(ind);
            
        }
    }
};

SegTree tr[26];

class Solution {
public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int> &queryIndices) {
        REP(i, 0, 26) {
            tr[i].build(0, sz(s), 1);
        }
        REP(i, 0, sz(s)) {
            tr[s[i] - 'a'].update(i, i, 1, 1);
        }
        VI ans(sz(queryCharacters));
        REP(i, 0, sz(queryCharacters)) {
            int pos = queryIndices[i];
            int nch = queryCharacters[i];
            tr[s[pos] - 'a'].update(pos, pos, 1, 0);
            s[pos] = nch;
            tr[s[pos] - 'a'].update(pos, pos, 1, 1);
            REP(j, 0, 26) {
                tr[j].query(0, sz(s), 1, ans[i]);
            }
        }
        return ans;
    }
};

#define LOCAL
#ifdef LOCAL

namespace SOLVE {
    void main() {
    }
}

//find /var/log -name 'secure*' -type f | while read line;do awk '/Failed/{print $(NF-3)}' $line;done | awk '{a[$0]++}END{for (j in a) if(a[j] > 20) print j"="a[j]}' | sort -n -t'=' -k 2


#ifdef __WIN32__
#define INPUT_FILE "./input.txt"
#define OUTPUT_FILE "./output.txt"
#else
#define INPUT_FILE ""
#define OUTPUT_FILE ""
#endif

signed main() {
    fr(INPUT_FILE);
    fw(OUTPUT_FILE);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int t = 1;
//    cin >> t;
    for(int i = 1; i <= t; i++) {
//        cout<<"Case #"<<i<<": ";
        SOLVE::main();
        
    }

//    clock_t st = clock();
//    while(clock() - st < 3.0 * CLOCKS_PER_SEC){
//
//    }
    
    return 0;
}

#endif


