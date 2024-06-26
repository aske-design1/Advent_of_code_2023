use std::fs;

#[allow(non_snake_case)]
fn main() {
    let fileString = fileFunc(&"C:/Users/askel/OneDrive/Skrivebord/AAU/Rust/AOC/Day15/input.txt");
    let sequence: Vec<&str> = fileString.split(",").collect();

    let sum: i64 = calculateSumFromSeq(sequence); 

    println!("The sum of the algorithm is: {}", sum); 
}

#[allow(non_snake_case)]
fn fileFunc(filePath: &str) -> String {
    let contents: String = fs::read_to_string(filePath).unwrap();
    contents
}

#[allow(non_snake_case)]
fn calculateSumFromSeq(sequence: Vec<&str>) -> i64 {
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

        //println!("The val is: {} and sum is {}",char,sum);
    }

    //println!("The sum of {} is: {}", str, sum);
    sum
}
