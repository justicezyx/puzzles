from typing import List, Tuple
from collections import defaultdict

def ts(edges: List[Tuple[int, int, int]]):
    """
    [(s, d, length/weight)]
    """
    graph = defaultdict(set)
    reverse_graph = defaultdict(set)
    nodes = set()
    for s, d, _ in edges:
        # print(f"s: {s} d: {d}")
        nodes.add(s)
        nodes.add(d)
        graph[s].add(d)
        reverse_graph[d].add(s)
    res = []
    candidates = set()
    while len(res) < len(nodes):
        if not candidates:
            for n in nodes:
                if not graph[n]:
                    candidates.add(n)
        if not candidates:
            raise ValueError("Have cycle")
        new_candidates = set()
        for c in candidates:
            res.append(c)
            for predecessor in reverse_graph[c]:
                graph[predecessor].remove(c)
                if not graph[predecessor]:
                    new_candidates.add(predecessor)
        candidates = new_candidates
    return res


def longest_path(edges: List[Tuple[int, int, int]]):
    """
    Return the longest path originating from every node in the DAG.
    """
    res = {}
    ts_order = ts(edges)
    graph = defaultdict(set)
    for s, d, w in edges:
        graph[s].add((d,w))
    for n in ts_order:
        if not graph[n]:
            res[n] = 0
            continue
        max_weight = 0
        for neighbor, w in graph[n]:
            max_weight = max(max_weight, res[neighbor]+w)
        res[n] = max_weight
    return res
            

if __name__ == "__main__":
    edges = [(0, 1, 1), (1, 3, 1), (2, 3, 1), (3, 4, 2)]
    print(ts(edges))
    print(longest_path(edges))
