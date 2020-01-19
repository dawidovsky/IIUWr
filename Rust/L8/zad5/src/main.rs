use std::collections::HashMap;

fn main() {
    let decoder = MorseDecoder::new();
    decoder.decode_bits("0001110001");
}

struct MorseDecoder {
    morse_code: HashMap<String, String>,
}

impl MorseDecoder {

    fn new() -> MorseDecoder {
        MorseDecoder{ morse_code :
        [("....-", "4"),("--..--", ","),(".--", "W"),(".-.-.-", "."),("..---", "2"),(".", "E"),("--..", "Z"),(".----", "1"),(".-..", "L"),
        (".--.", "P"),(".-.", "R"),("...", "S"),("-.--", "Y"),("...--", "3"),(".....", "5"),("--.", "G"),("-.--.", "("),("-....", "6"),
        (".-.-.", "+"),("...-..-", "$"),(".--.-.", "@"),("...---...", "SOS"),("..--.-", "_"),("-.", "N"),("-..-", "X"),("-----", "0"),
        ("....", "H"),("-...", "B"),(".---", "J"),("---...", ","),("-", "T"),("---..", "8"),("-..-.", "/"),("--.-", "Q"),("...-", "V"),
        ("----.", "9"),("--", "M"),("-.-.-.", ";"),("-.-.--", "!"),("..-.", "F"),("..--..", "?"),("-...-", "="),("..-", "U"),(".----.", "'"),
        ("---", "O"),("-.--.-", ")"),("..", "I"),("-....-", "-"),(".-..-.", "\""),(".-", "A"),("-.-.", "C"),("-..", "D"),(".-...", "&"),
        ("--...", "7"),("-.-", "K")].iter().map(|(k, v)| (k.to_string(), v.to_string())).collect()}
        }

    fn find_transmission(&self, code: &str) -> u32 {
        let mut res = code.len();
        let mut count = 0;
        let mut was_zero: bool = false;
        for c in code.chars() {
            if c == '1' {
                if was_zero && count <= res {res = count; count = 0;}
                count += 1;
                was_zero = false;
            }
            else{
                if !was_zero && count <= res {res = count; count = 0;}
                count += 1;
                was_zero = true;
            }
        }
        if count < res {count as u32} else {res as u32}
    }

    pub fn decode_bits(&self, encoded: &str) -> String {
        let trimmed = encoded.trim_matches('0');
        let transmission = self.find_transmission(trimmed);
        let mut res = "".to_string();
        let mut zero_count = 0;
        let mut one_count = 0;
        for c in trimmed.chars() {
            if c == '1' {
                one_count += 1;
                if zero_count > 0 {
                    if zero_count == 3 * transmission {res.push(' ');}
                    if zero_count == 7 * transmission {res.push_str("   ");}
                }
                zero_count = 0;
            }
            else {
                zero_count += 1;
                if one_count > 0 {
                    if one_count == transmission {res.push('.');}
                    if one_count == 3 * transmission {res.push('-');}
                }
                one_count = 0;
            }
        }
        if one_count > 0 {
            if one_count == transmission {res.push('.');}
            if one_count == 3 * transmission {res.push('-');}
        }
        res
    }

    pub fn decode_morse(&self, encoded: &str) -> String {
        let s = encoded.trim();
        let mut vec_string: Vec<&str> = s.split("  ").collect();
        vec_string.retain(|s| !s.is_empty());
        let mut res: String = self.decode(vec_string);
        res.truncate(res.len().saturating_sub(1));
        res
    }

    fn decode(&self, enc: Vec<&str>) -> String {
        let mut res: String = "".to_string();
        for s in enc.iter() {
            let mut vec_string: Vec<&str> = s.split(" ").collect();
            vec_string.retain(|s| !s.is_empty());
            for val in vec_string.iter() {
                res.push_str(self.morse_code.get(&val.to_string()).unwrap());
            }
            res.push(' ');
        }
        res
    }

}

#[test]
fn test1() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(&decoder.decode_bits("1100110011001100000011000000111111001100111111001111110000000000000011001111110011111100111111000000110011001111110000001111110011001100000011")), "HEY JUDE".to_string());
}

#[test]
fn test2() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(&decoder.decode_bits("1110111")), "M".to_string());
}

#[test]
fn test3() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(&decoder.decode_bits("11111100111111")), "M".to_string());
}

#[test]
fn test4() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(&decoder.decode_bits("01110")), "E".to_string());
}

#[test]
fn test5() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(&decoder.decode_bits("111")), "E".to_string());
}

#[test]
fn test6() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(&decoder.decode_bits("00011100010101010001000000011101110101110001010111000101000111010111010001110101110000000111010101000101110100011101110111000101110111000111010000000101011101000111011101110001110101011100000001011101110111000101011100011101110001011101110100010101000000011101110111000101010111000100010111010000000111000101010100010000000101110101000101110001110111010100011101011101110000000111010100011101110111000111011101000101110101110101110")), "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG.".to_string());
}

#[test]
fn test7() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(&decoder.decode_bits("0001110001")), "TE".to_string());
}

#[test]
fn test8() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(&decoder.decode_bits("1")), "E".to_string());
}

#[test]
fn test9() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(&decoder.decode_bits("0000000000000000000111000000000000")), "E".to_string());
}

#[test]
fn test10() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(&decoder.decode_bits("10101011101110111010101")), "SOS".to_string());
}