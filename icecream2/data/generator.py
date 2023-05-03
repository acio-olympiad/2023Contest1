import networkx as nx
import numpy as np

def get_random_graph(subtask, N, nextra, seed):
    rng = np.random.default_rng(seed=seed)
    if subtask == 2:
        assert nextra == 0
    elif subtask == 3:
        assert 0 <= nextra <= 1
    else:
        assert 0 <= nextra <= 11
    lg = nx.random_tree(N, seed=seed+1)
    while len(lg.edges) < N + nextra - 1:
        u = rng.integers(1, N)
        v = rng.integers(u, N+1)
        if not lg.has_edge(u, v):
            lg.add_edge(u, v)

    assert len(lg.edges) == N + nextra - 1

    res = []
    q = []
    for u, v in lg.edges:
        res.append((u, v, rng.integers(1, 10001)))
    for i in range(N):
        q.append(rng.integers(1, N+1))
    return len(lg.nodes), res, q

CASES = [
    (1, 2, 0),
    (1, 4, 0),
    (1, 6, 2),
    (1, 100, 0),
    (1, 100, 1),
    (1, 100, 2),
    (1, 1000, 11),
    (1, 1000, 11),
    (1, 1000, 11),
    (1, 1000, 11),
    (1, 1000, 11),
    (1, 1000, 11),
    (1, 1000, 11),
    (1, 1000, 11),
    (1, 1000, 11),
    (1, 1000, 11),
    (2, 100000, 0),
    (2, 100000, 0),
    (2, 100000, 0),
    (2, 100000, 0),
    (3, 100000, 1),
    (3, 100000, 1),
    (3, 100000, 1),
    (3, 100000, 1),
    (3, 100000, 1),
    (3, 100000, 1),
    (3, 100000, 1),
    (4, 100000, 11),
    (4, 100000, 11),
    (4, 100000, 11),
    (4, 100000, 11),
    (4, 100000, 11)
]

if __name__ == "__main__":
    for i, (sub, N, maxextra) in enumerate(CASES):
        fn = f"sub{sub}-{i}.in"
        N, edges, queries = get_random_graph(sub, N, maxextra, 178*i + 349)
        with open(fn, "w") as f:
            f.write(f"{N} {len(edges)} {len(queries)}\n")
            for a, b, c in edges:
                f.write(f"{a+1} {b+1} {c}\n")
            f.write(" ".join([str(x) for x in queries]) + "\n")
        print("Written", fn)

