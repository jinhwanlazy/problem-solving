use std::io::{BufRead, stdin, StdinLock};

trait ReadFromStdin {
    fn read(&mut self, ibuf: &mut StdinLock);
}

impl ReadFromStdin for String {
    fn read(&mut self, ibuf: &mut StdinLock) {
        let mut buf = String::new();
        ibuf.read_line(&mut buf).unwrap();
        *self = buf.trim().to_string();
    }
}

impl<T: std::str::FromStr> ReadFromStdin for Vec<T> {
    fn read(&mut self, ibuf: &mut StdinLock) {
        let mut line = String::new();
        ibuf.read_line(&mut line).unwrap();
        *self = line
            .split_whitespace()
            .filter_map(|s| s.parse().ok())
            .collect();
    }
}

macro_rules! impl_read_for_numbers {
    ( $( $t:ty ),* ) => {
        $(
            impl ReadFromStdin for $t {
                fn read(&mut self, ibuf: &mut StdinLock) {
                    let mut buf = String::new();
                    ibuf.read_line(&mut buf).unwrap();
                    *self = buf.trim().parse().unwrap();
                }
            }
        )*
    };
}

impl_read_for_numbers!(f32, f64,
    i8, i16, i32, i64, i128, isize, 
    u8, u16, u32, u64, u128, usize);


impl<T, U> ReadFromStdin for (T, U)
where T: ReadFromStdin, U: ReadFromStdin,
{
    fn read(&mut self, ibuf: &mut StdinLock) {
        self.0.read(ibuf);
        self.1.read(ibuf);
    }
}

fn main() {
    let mut ibuf = stdin().lock();

    let mut nm : Vec<usize> = Vec::new();
    nm.read(&mut ibuf);
    let n = nm[0];
    let m = nm[1];

    let mut v = vec![0usize; n + 1];
    for _ in 0..m {
        let mut ijk : Vec<usize> = Vec::new();
        ijk.read(&mut ibuf);
        let i = ijk[0];
        let j = ijk[1];
        let k = ijk[2];
        for l in i..j+1 {
            v[l] = k;
        }
    }
    
    for i in 1..n+1 {
        print!("{} ", v[i]);
    }
}
