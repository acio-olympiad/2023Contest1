#include <bits/stdc++.h>

using namespace std;

template<typename T>
using min_heap = priority_queue<
    T, vector<T>, greater<T>
>;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<pair<size_t, uint64_t>>> graph(n);
    for(size_t i = 0; i < m; i++) {
        size_t u, v; uint w;
        cin >> u >> v >> w; u--; v--;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    min_heap<pair<uint64_t, size_t>> que;
    vector<uint64_t> dist(2 * n, UINT64_MAX);
    auto maybe = [&](uint64_t d, size_t v) {
        if(d >= dist[v]) return;
        que.emplace(dist[v] = d, v);
    };

    maybe(0, 1);
    while(not que.empty()) {
        auto [d, uu] = que.top(); que.pop();
        if(d > dist[uu]) continue;
        auto b = uu % 2, u = uu / 2;
        for(auto [v, w] : graph[u]) {
            maybe(d + w, 2*v + b);
            if(b) maybe(d, 2*v);
        }
    }

    cout << min(dist[2*(n-1)+0], dist[2*(n-1)+1]) << endl;
}
