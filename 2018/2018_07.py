"""
for sort dictionary by value
{k: v for k, v in sorted(x.items(), key=lambda item: item[1])}
"""

# INPUT = '''Step C must be finished before step A can begin.
# Step C must be finished before step F can begin.
# Step A must be finished before step B can begin.
# Step A must be finished before step D can begin.
# Step B must be finished before step E can begin.
# Step D must be finished before step E can begin.
# Step F must be finished before step E can begin.'''

INPUT = '''Step W must be finished before step G can begin.
Step N must be finished before step X can begin.
Step M must be finished before step O can begin.
Step S must be finished before step I can begin.
Step F must be finished before step Y can begin.
Step Q must be finished before step K can begin.
Step K must be finished before step Y can begin.
Step Z must be finished before step J can begin.
Step G must be finished before step L can begin.
Step J must be finished before step C can begin.
Step R must be finished before step E can begin.
Step X must be finished before step I can begin.
Step P must be finished before step E can begin.
Step V must be finished before step Y can begin.
Step C must be finished before step I can begin.
Step O must be finished before step H can begin.
Step T must be finished before step B can begin.
Step Y must be finished before step A can begin.
Step E must be finished before step L can begin.
Step B must be finished before step D can begin.
Step L must be finished before step U can begin.
Step A must be finished before step I can begin.
Step I must be finished before step D can begin.
Step H must be finished before step D can begin.
Step U must be finished before step D can begin.
Step B must be finished before step I can begin.
Step S must be finished before step F can begin.
Step M must be finished before step R can begin.
Step A must be finished before step H can begin.
Step Z must be finished before step O can begin.
Step K must be finished before step I can begin.
Step K must be finished before step D can begin.
Step B must be finished before step A can begin.
Step G must be finished before step I can begin.
Step Z must be finished before step B can begin.
Step R must be finished before step P can begin.
Step J must be finished before step E can begin.
Step R must be finished before step I can begin.
Step Q must be finished before step U can begin.
Step S must be finished before step Z can begin.
Step E must be finished before step I can begin.
Step F must be finished before step E can begin.
Step F must be finished before step I can begin.
Step S must be finished before step J can begin.
Step O must be finished before step I can begin.
Step V must be finished before step B can begin.
Step A must be finished before step U can begin.
Step M must be finished before step T can begin.
Step K must be finished before step A can begin.
Step L must be finished before step I can begin.
Step I must be finished before step U can begin.
Step G must be finished before step U can begin.
Step B must be finished before step U can begin.
Step E must be finished before step D can begin.
Step J must be finished before step T can begin.
Step M must be finished before step Y can begin.
Step P must be finished before step B can begin.
Step M must be finished before step S can begin.
Step E must be finished before step U can begin.
Step R must be finished before step Y can begin.
Step J must be finished before step I can begin.
Step J must be finished before step D can begin.
Step Y must be finished before step E can begin.
Step A must be finished before step D can begin.
Step X must be finished before step H can begin.
Step O must be finished before step E can begin.
Step E must be finished before step B can begin.
Step E must be finished before step A can begin.
Step F must be finished before step U can begin.
Step G must be finished before step J can begin.
Step M must be finished before step Z can begin.
Step Y must be finished before step U can begin.
Step Y must be finished before step D can begin.
Step S must be finished before step D can begin.
Step G must be finished before step H can begin.
Step C must be finished before step Y can begin.
Step B must be finished before step H can begin.
Step P must be finished before step V can begin.
Step M must be finished before step K can begin.
Step L must be finished before step A can begin.
Step G must be finished before step A can begin.
Step Q must be finished before step P can begin.
Step P must be finished before step I can begin.
Step H must be finished before step U can begin.
Step G must be finished before step X can begin.
Step L must be finished before step H can begin.
Step X must be finished before step P can begin.
Step Z must be finished before step Y can begin.
Step N must be finished before step K can begin.
Step Q must be finished before step X can begin.
Step X must be finished before step L can begin.
Step T must be finished before step Y can begin.
Step P must be finished before step A can begin.
Step C must be finished before step T can begin.
Step J must be finished before step V can begin.
Step X must be finished before step O can begin.
Step S must be finished before step C can begin.
Step R must be finished before step C can begin.
Step E must be finished before step H can begin.
Step V must be finished before step H can begin.
Step L must be finished before step D can begin.'''


from collections import defaultdict

def parse(filename):
    res = []
    for line in filename.split('\n'):
        line = line.strip()
        splitted = line.split()
        predecessor = splitted[1]
        successor = splitted[-3]
        res.append( (predecessor, successor))
    return res

def create_graph(data):
    graph = defaultdict(list)
    for p, s in data:
        graph[p].append(s)
    return graph

def find_predecessors(graph, node):
    res = []
    for n in graph:
        sucessor = graph[n]
        if node in sucessor:
            res.append(n)
    return res

def find_nodes_with_no_predecessor(graph):
    nodes = []
    for node in graph:
        predecessors = find_predecessors(graph, node)
        if not predecessors:
            nodes.append(node)
    return nodes


def topological_sort(graph):
    S = sorted(find_nodes_with_no_predecessor(graph))
    L = []
    while S:
        n = S[0]
        del S[0]
        L.append(n)
        next_nodes = graph[n]
        del graph[n]
        for m in next_nodes[:]:
            nodes = find_predecessors(graph, m)
            if not nodes:
                S.append(m)
        S = sorted(S)
    return L


def main():
    data = parse(INPUT)
    graph = create_graph(data)
    print(''.join(topological_sort(graph)))

if __name__ == "__main__":
    main()
