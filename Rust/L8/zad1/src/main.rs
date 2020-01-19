fn main() {}

fn dna_strand(dna: &str) -> String {
    dna.chars().map(|c|
    match c{
        'A' => return 'T',
        'T' => return 'A',
        'C' => return 'G',
        'G' => return 'C',
        _ => return ' '
    }).collect()
}

#[test]
fn test1() {
    assert_eq!(dna_strand("AAAA"),"TTTT");
}

#[test]
fn test2() {
    assert_eq!(dna_strand("TTAA"),"AATT");
}

#[test]
fn test3() {
    assert_eq!(dna_strand("ATTGC"),"TAACG");
}

#[test]
fn test4() {
    assert_eq!(dna_strand("GTAT"),"CATA");
}

#[test]
fn test5() {
    assert_eq!(dna_strand("CC"),"GG");
}

#[test]
fn test6() {
    assert_eq!(dna_strand("TT"),"AA");
}

#[test]
fn test7() {
    assert_eq!(dna_strand("CG"),"GC");
}

#[test]
fn test8() {
    assert_eq!(dna_strand("TTAT"),"AATA");
}

#[test]
fn test9() {
    assert_eq!(dna_strand("ATA"),"TAT");
}

#[test]
fn test10() {
    assert_eq!(dna_strand("CGG"),"GCC");
}