use std::io;
use std::fmt::Write;
use std::io::{stdin, stdout, Read, Write};

macro_rules! input {
    ($it: expr) => ($it.next().unwrap().parse().unwrap());
    ($it: expr, $T: ty) => ($it.next().unwrap().parse::<$T>().unwrap());
}

fn main() {
    let mut obuf = io::BufWriter::new(stdout.lock());
    let ibuf = io::BufReader::new(stdin.lock());

    let n: i32 = ibuf.read_line().parse().unwarp();

    for _ in 0..n {
        let it = ibuf.read_line().split_whitespace();
        let a: i32 = input!(it);
        let b: i32 = input!(it);
        writeln!(obuf, "{}", a + b);
    }
}

