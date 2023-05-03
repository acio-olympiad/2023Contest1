import networkx as nx
import numpy as np

def get_random_graph(subtask, N, rng):
    assert N % 2 == 0
    halfn = N // 2
    lg = nx.ladder_graph(halfn)
    res = []
    for u, v in lg.edges:
        res.append((u, v, rng.integers(1, 10001) if subtask != 2 else 1))
    return len(lg.nodes), res

CASES = [
    (1, 2),
    (1, 4),
    (1, 6),
    (1, 100),
    (1, 100),
    (1, 100),
    (1, 1000),
    (1, 1000),
    (1, 1000),
    (1, 1000),
    (1, 1000),
    (1, 1000),
    (1, 1000),
    (1, 1000),
    (1, 1000),
    (1, 1000),
    (2, 2),
    (2, 4),
    (2, 42042),
    (2, 69420),
    (2, 100000),
    (3, 100000),
    (3, 100000),
    (3, 100000),
    (3, 100000)
]

if __name__ == "__main__":
    for i, (sub, N) in enumerate(CASES):
        fn = f"sub{sub}-{i}.in"
        N, edges = get_random_graph(sub, N, np.random.default_rng(seed=178*i + 349))
        with open(fn, "w") as f:
            f.write(f"{N} {len(edges)}\n")
            for a, b, c in edges:
                f.write(f"{a+1} {b+1} {c}\n")
        print("Written", fn)

