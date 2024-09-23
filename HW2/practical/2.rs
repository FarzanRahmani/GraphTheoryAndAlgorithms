use std::collections::{HashMap, HashSet};

struct HopcroftKarp<'a> {
    graph: &'a HashMap<char, HashSet<char>>,
    pair_u: HashMap<char, Option<char>>,
    pair_v: HashMap<char, Option<char>>,
    dist: HashMap<Option<char>, usize>,
    max_matching: usize,
}

impl<'a> HopcroftKarp<'a> {
    fn new(graph: &'a HashMap<char, HashSet<char>>) -> Self {
        let mut pair_u = HashMap::new();
        let mut pair_v = HashMap::new();
        for (u, _) in graph.iter() {
            pair_u.insert(*u, None);
        }
        for (v, _) in graph.values().flatten() {
            pair_v.insert(*v, None);
        }
        let mut dist = HashMap::new();
        dist.insert(None, usize::MAX);
        for u in graph.keys() {
            if pair_u[u].is_none() {
                dist.insert(Some(*u), 0);
            } else {
                dist.insert(Some(*u), usize::MAX);
            }
        }
        HopcroftKarp {
            graph,
            pair_u,
            pair_v,
            dist,
            max_matching: 0,
        }
    }

    fn bfs(&mut self) -> bool {
        let mut queue = Vec::new();
        for u in self.graph.keys() {
            if self.pair_u[u].is_none() {
                self.dist.insert(Some(*u), 0);
                queue.push(*u);
            } else {
                self.dist.insert(Some(*u), usize::MAX);
            }
        }
        self.dist.insert(None, usize::MAX);

        while let Some(u) = queue.pop() {
            if let Some(d) = self.dist.get(&Some(u)) {
                for &v in self.graph[&u].iter() {
                    if *self.dist.get(&self.pair_v[&v]).unwrap() == usize::MAX {
                        *self.dist.get_mut(&self.pair_v[&v]).unwrap() = *d + 1;
                        queue.push(self.pair_v[&v].unwrap());
                    }
                }
            }
        }
        *self.dist.get(&None).unwrap() != usize::MAX
    }

    fn dfs(&mut self, u: char) -> bool {
        if let Some(d) = self.dist.get(&Some(u)) {
            for &v in self.graph[&u].iter() {
                if *self.dist.get(&self.pair_v[&v]).unwrap() == *d + 1 {
                    if self.pair_v[&v].is_none() || self.dfs(self.pair_v[&v].unwrap()) {
                        self.pair_v.insert(v, Some(u));
                        self.pair_u.insert(u, Some(v));
                        return true;
                    }
                }
            }
            self.dist.insert(Some(u), usize::MAX);
            return false;
        }
        true
    }

    fn max_matching_size(&mut self) -> usize {
        while self.bfs() {
            for &u in self.graph.keys() {
                if self.pair_u[&u].is_none() && self.dfs(u) {
                    self.max_matching += 1;
                }
            }
        }
        self.max_matching / 2
    }
}

fn parse_input(input_str: &str) -> (HashMap<char, HashSet<char>>, HashSet<char>, HashSet<String>) {
    let mut graph = HashMap::new();
    let mut vertices = HashSet::new();
    let mut edges = HashSet::new();

    let mut i = 0;
    let sequence = input_str.chars().collect::<Vec<char>>();
    while i < sequence.len() {
        if sequence[i] == ' ' {
            i += 1;
            continue;
        } else if i == sequence.len() - 1 || sequence[i + 1] == ' ' {
            let isolated_vertex = sequence[i];
            vertices.insert(isolated_vertex);
            graph.entry(isolated_vertex).or_insert(HashSet::new());
            i += 1;
            continue;
        }
        let vertex1 = sequence[i];
        let vertex2 = sequence[i + 1];
        let mut edge_chars = vec![vertex1, vertex2];
        edge_chars.sort();
        let edge = edge_chars.into_iter().collect::<String>();
        vertices.insert(vertex1);
        vertices.insert(vertex2);
        edges.insert(edge.clone());
        graph.entry(vertex1).or_insert(HashSet::new()).insert(vertex2);
        graph.entry(vertex2).or_insert(HashSet::new()).insert(vertex1);
        i += 2;
    }
    (graph, vertices, edges)
}

fn maximum_matching(input_string: &str) -> usize {
    let (graph, _, _) = parse_input(input_string);
    let mut hk = HopcroftKarp::new(&graph);
    hk.max_matching_size()
}

fn main() {
    let input_str = {
        let mut input = String::new();
        std::io::stdin().read_line(&mut input).expect("Failed to read line");
        input.trim().to_string()
    };
    println!("{}", maximum_matching(&input_str));
}
