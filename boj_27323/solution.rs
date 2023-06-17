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

fn main() {
    let mut ibuf = stdin().lock();

    let mut a = 0i32;
    a.read(&mut ibuf);

    let mut b = 0i32;
    b.read(&mut ibuf);

    println!("{}", a * b);
}

//

