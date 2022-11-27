#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

/*
 * Author : jinhan814
 * Date : 2022-04-16
 * Description : Non-recursive implementation of Segment Tree with Lazy Propagation
 */

template<typename NodeType,
         typename LazyType,
         typename F_Merge,
         typename F_Update,
         typename F_Composition>
struct LazySegTree { // 1-indexed
public:
    using A = NodeType;
    using B = LazyType;
    LazySegTree() : LazySegTree(0, A(), B()) {}
    explicit LazySegTree(int n, const A& e, const B& id)
        : n(n), e(e), id(id), lg(Log2(n)), sz(1 << lg), tree(sz << 1, e), lazy(sz, id) {
          cout << "n: " << n << "\n";
          cout << "e: " << e.val << ", " << e.sz << "\n";
          cout << "id: " << id << "\n";
          cout << "lg: " << lg << "\n";
          cout << "sz: " << sz << "\n";
        }
    void Set(int i, const A& val) { tree[--i | sz] = val; }
    void Init() { for (int i = sz - 1; i; i--) tree[i] = M(tree[i << 1], tree[i << 1 | 1]); }
    void Update(int i, const B& f) {
        --i |= sz;
        for (int j = lg; j; j--) Push(i >> j);
        Apply(i, f);
        for (int j = 1; j <= lg; j++) Pull(i >> j);
    }
    void Update(int l, int r, const B& f) {
        --l |= sz, --r |= sz;
        for (int i = lg; i; i--) {
            if (l >> i << i != l) Push(l >> i);
            if (r + 1 >> i << i != r + 1) Push(r >> i);
        }
        for (int L = l, R = r; L <= R; L >>= 1, R >>= 1) {
            if (L & 1) Apply(L++, f);
            if (~R & 1) Apply(R--, f);
        }
        for (int i = 1; i <= lg; i++) {
            if (l >> i << i != l) Pull(l >> i);
            if (r + 1 >> i << i != r + 1) Pull(r >> i);
        }
    }
    A Query(int i) {
        --i |= sz;
        for (int j = lg; j; j--) Push(i >> j);
        return tree[i];
    }
    A Query(int l, int r) {
        A L = e, R = e; --l |= sz, --r |= sz;
        for (int i = lg; i; i--) {
            if (l >> i << i != l) Push(l >> i);
            if (r + 1 >> i << i != r + 1) Push(r >> i);
        }
        for (; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) L = M(L, tree[l++]);
            if (~r & 1) R = M(tree[r--], R);
        }
        return M(L, R);
    }
private:
    const int n, lg, sz; const A e; const B id;
    vector<A> tree; vector<B> lazy;
    F_Merge M; F_Update U; F_Composition C;
    static int Log2(int n) {
        int ret = 0;
        while (n > 1 << ret) ret++;
        return ret;
    }
    void Apply(int i, const B& f) {
        tree[i] = U(f, tree[i]);
        if (i < sz) lazy[i] = C(f, lazy[i]);
    }
    void Push(int i) {
        Apply(i << 1, lazy[i]);
        Apply(i << 1 | 1, lazy[i]);
        lazy[i] = id;
    }
    void Pull(int i) {
        tree[i] = M(tree[i << 1], tree[i << 1 | 1]);
    }
};

struct NodeType {
	long long val; int sz;
	constexpr NodeType(long long val, int sz) : val(val), sz(sz) {}
};

constexpr NodeType e(0, 0);

using LazyType = long long;

constexpr LazyType id = 0;

struct F_Merge {
	NodeType operator() (const NodeType& a, const NodeType& b) const {
		return NodeType(a.val + b.val, a.sz + b.sz);
	}
};

struct F_Update {
	NodeType operator() (const LazyType& a, const NodeType& b) const {
		return NodeType(b.val + a * b.sz, b.sz);
	}
};

struct F_Composition {
	LazyType operator() (const LazyType& a, const LazyType& b) const {
		return a + b;
	}
};

int main() {
	fastio;
	int n, m, k; cin >> n >> m >> k;
	LazySegTree<NodeType, LazyType, F_Merge, F_Update, F_Composition> ST(n, e, id);
	for (int i = 1; i <= n; i++) {
		long long t; cin >> t;
		ST.Set(i, NodeType(t, 1));
	}
	ST.Init();
	while (m + k--) {
		int t, l, r; LazyType f; cin >> t >> l >> r;
		if (t & 1) cin >> f, ST.Update(l, r, f);
		else cout << ST.Query(l, r).val << '\n';
	}
}
