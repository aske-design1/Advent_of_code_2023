
fn find_adjacencies(city: &mut Vec<Vec<Vertex>>, coordinates: (usize, usize)) -> Vec<(usize, usize, u32)> {
	let (x, y) = coordinates; 
	let cur_vertex: Vertex = city[y][x];
	let combinations: Vec<(usize, usize, u32)> = Vec::new(); 
	
    let (x, y) = (x,y) as u32;

    if let some(x) = checkPoint(city, (x,y-1), &cur_vertex) { combinations.push(x) }
    if let some(x) = checkPoint(city, (x+1,y), &cur_vertex) { combinations.push(x) }
    if let some(x) = checkPoint(city, (x,y+1), &cur_vertex) { combinations.push(x) }
    if let some(x) = checkPoint(city, (x-1,y), &cur_vertex) { combinations.push(x) }

    (*cur_vertex).used = true; 

    combinations
}

fn checkPoint(city: &mut Vec<Vec<Vertex>>, point: (u32, u32), cur_vertex: &Vertex) -> Option<(usize, usize, u32)> {
   let (x,y) = point; 
    if x >= city[0].len() || y >= city.len() || cur_vertex.parent.1 == y && cur_vertex.parent.0 == x  {
        return None; 
    }

    let next_vertex: Vertex = city[y][x]; 
    (*next_vertex).dist = (*cur_vertex).dist + (*next_vertex).value;
    (*next_vertex).parent = ((*cur_vertex).point.0, (*cur_vertex).point.1); 

    Some((x, y, (*next_vertex).dist))
}

fn insert_in_heap(queue: &mut VecDeque<(usize, usize, u32)>, points: Vec<(usize, usize, u32)>) -> () {
    while let some(point) = points.iter() {
        queue.push_front(point);
        sort_queue(queue, 0); 
    } 

}

fn sort_queue(queue: &mut VecDeque<(usize, usize, u32)>, i: usize) {
    let l = left(i); 
    let r = right(i); 
    
    let mut smallest;
    if r < queue.len() && queue[r].2 < queue[i].2 {
       //println!("dist right to i: {}",queue[r].dist);

        smallest = r; 
    } else { smallest = i }
    
    if l < queue.len() && queue[l].2 < queue[smallest].2 {
        //println!("dist left to i: {}", queue[l].dist);

        smallest = l; 
    }
    if i != smallest {
        (*queue).swap(i, smallest); 
        sort_queue(queue, smallest); 
    }
}


fn left(i: usize) -> usize {
    (i+1) * 2 - 1
}
fn right(i: usize) -> usize {
    (i+1)*2 
}
