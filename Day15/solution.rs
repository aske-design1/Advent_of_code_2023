use std::fs;
use std::collections::HashMap;

#[allow(non_snake_case)]
fn main() {
    let fileString = fileFunc(&"path");
    let sequence: Vec<&str> = fileString.split(",").collect();

    let sum: i64 = calculateSumFromSeq(&sequence); 

    println!("Part 1's sum of the algorithm is: {}", sum); 

    let focusPower = part2(&sequence);
    println!("Part 2's focus power is: {}", focusPower); 
}

#[allow(non_snake_case)]
fn fileFunc(filePath: &str) -> String {
    let contents: String = fs::read_to_string(filePath).unwrap();
    contents
}

#[allow(non_snake_case)]
fn calculateSumFromSeq(sequence: &Vec<&str>) -> i64 {
    let sum: i64 = sequence.iter().map(|el| calculateSumFromElement(*el)).sum();
    sum
}

#[allow(non_snake_case)]
fn calculateSumFromElement(str: &str) -> i64 {
    let chars = str.chars();
    let mut sum: i64 = 0; 
    
    for char in chars {
        if char == '\n' {
            continue;
        }
        let val:u8 = char as u8; 
        sum = ((val as i64 + sum)*17) % 256;
    }
    sum
}

#[allow(non_snake_case)]
fn part2(seq: &Vec<&str>) -> i64 {
    let mut sum: i64 = 0; 
    let mut hash: HashMap<u8, Vec<(String, i32)>> = HashMap::new(); 

    for str in seq {
        if (*str).contains("=") {
            insertIntoBox(str, &mut hash);
        } else {
            deleteEntry(str, &mut hash);
        }
    }  
    println!("hash map {:?}", hash);


    sum
}

#[allow(non_snake_case)]
fn insertIntoBox(string: &str, map: &mut HashMap<u8, Vec<(String, i32)>>) -> () {
    let splitStr: Vec<&str> = string.split("=").collect();
    let key = calculateSumFromElement(splitStr[0]) % 10;
    let val = splitStr[1].parse::<i32>().unwrap();
    let label = splitStr[0];

    map.entry(key as u8).and_modify(|vec| {
        if let Some(index) = checkIfLabelAlreadyIn(&label, &vec) {
            vec[index] = (String::from(label), val)
        } else{
            (*vec).push((String::from(label),val)) 
        }
    }).or_insert(vec![(String::from(label), val)]);
}

#[allow(non_snake_case)]
fn deleteEntry(string: &str, map: &mut HashMap<u8, Vec<(String, i32)>>) -> () { 
    let slice = &string[0..(string.len()-1)];
    let key = calculateSumFromElement(slice) as u8;

    if let Some(el) = map.remove(&key) {
        map.insert(key, el.into_iter().filter(| (label,_) | slice != *label).collect());   
    }
}

#[allow(non_snake_case)]
fn checkIfLabelAlreadyIn(label: &str, vec: &Vec<(String, i32)>) -> Option<usize> {
    for (index, (labelInVec,_)) in vec.iter().enumerate() {
        if labelInVec == label {
            return Some(index)        
        }
    }
    None
}
