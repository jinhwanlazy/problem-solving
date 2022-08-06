use std::io::{self, Read};

macro_rules! input {
    ($it: expr) => ($it.next().unwrap().parse().unwrap());
    ($it: expr, $T: ty) => ($it.next().unwrap().parse::<$T>().unwrap());
}

fn main() {
    let mut buf = String::new();
    io::stdin().read_to_string(&mut buf).unwrap();

    let mut it = buf.split_whitespace();
    
    let a: i64 = input!(it);
    let b: i64 = input!(it);
    let ans = a + b;
    println!("{}", ans);
}

