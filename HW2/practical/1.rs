use std::collections::{HashMap, HashSet};

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
        } else if (i == sequence.len() - 1) || sequence[i + 1] == ' ' {
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

fn is_bipartite(graph: &HashMap<char, HashSet<char>>, vertices: &HashSet<char>) -> bool {
    let mut colors = HashMap::new();
    let mut queue = Vec::new();

    for &vertex in vertices {
        if !colors.contains_key(&vertex) {
            queue.push(vertex);
            colors.insert(vertex, 0);

            while !queue.is_empty() {
                let current = queue.remove(0);
                for &neighbor in graph[&current].iter() {
                    if !colors.contains_key(&neighbor) {
                        colors.insert(neighbor, 1 - *colors.get(&current).unwrap());
                        queue.push(neighbor);
                    } else if colors[&neighbor] == colors[&current] {
                        return false;
                    }
                }
            }
        }
    }
    true
}

fn calculate_complement_edges(vertices: &HashSet<char>, edges: &HashSet<String>) -> usize {
    let num_vertices = vertices.len();
    let num_edges = edges.len();
    (num_vertices * (num_vertices - 1)) / 2 - num_edges
}

fn remove_edges_to_bipartite(graph: &mut HashMap<char, HashSet<char>>, vertices: &HashSet<char>, edges: &mut HashSet<String>) -> usize {
    let mut num_removed_edges = 0;

    for &vertex in vertices.iter() {
        let mut queue = vec![vertex];
        let mut colors = HashMap::new();
        colors.insert(vertex, 0);

        while let Some(current) = queue.pop() {
            let neighbors = graph[&current].clone();
            for &neighbor in neighbors.iter() {
                if !colors.contains_key(&neighbor) {
                    colors.insert(neighbor, 1 - *colors.get(&current).unwrap());
                    queue.push(neighbor);
                } else if colors[&neighbor] == colors[&current] {
                    let mut edge_chars = vec![current, neighbor];
                    edge_chars.sort();
                    let edge = edge_chars.into_iter().collect::<String>();
                    if edges.contains(&edge) {
                        edges.remove(&edge);
                        graph.get_mut(&current).unwrap().remove(&neighbor);
                        if current != neighbor {
                            graph.get_mut(&neighbor).unwrap().remove(&current);
                        }
                        num_removed_edges += 1;
                        queue.insert(0, current);
                        break;
                    }
                }
            }
        }
    }
    num_removed_edges
}

fn main() {
    let input_str = {
        let mut input = String::new();
        std::io::stdin().read_line(&mut input).expect("Failed to read line");
        input.trim().to_string()
    };
    
    let (mut graph, vertices, mut edges) = parse_input(&input_str);

    if is_bipartite(&graph, &vertices) {
        let complement_edges = calculate_complement_edges(&vertices, &edges);
        println!("{}", complement_edges);
    } else {
        let num_total_edges = edges.len();
        let num_removed_edges = remove_edges_to_bipartite(&mut graph, &vertices, &mut edges);
        println!("{}", num_total_edges - num_removed_edges);
    }
}

// Example usage:
// fn main() {
//     let input_str1 = "abacdedfsopwkslskc".to_string();
//     main_helper(input_str1); // Output: 57
// 
//     let input_str2 = "kjhgfyfhjklkohufyykpjhgyfhjkphitdyjkpjogyfjkjhgfdfghkljhhgfg".to_string();
//     main_helper(input_str2); // Output: 14
// 
//     let input_str3 = "abc d".to_string();
//     main_helper(input_str3); // Output: 5
// }
