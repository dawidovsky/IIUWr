use std::collections::HashMap;

fn main() {
    let decoder = MorseDecoder::new();
   decoder.decode_morse(".... . -.--   .--- ..- -.. .");
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

    fn decode_morse(&self, encoded: &str) -> String {
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
fn test1(){
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(".... . -.--   .--- ..- -.. ."), "HEY JUDE");
}

#[test]
fn test2(){
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse("-.-.--"), "!");
}

#[test]
fn test3(){
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse("-...-"), "=");
}

#[test]
fn test4(){
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse("--."), "G");
}

#[test]
fn test5(){
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse("....-"), "4");
}

#[test]
fn test6(){
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse("-..."), "B");
}

#[test]
fn test7(){
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse("-.-"), "K");
}

#[test]
fn test8(){
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse("...--"), "3");
}

#[test]
fn test9(){
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse("."), "E");
}

#[test]
fn test10(){
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse("..."), "S");
}