use std::env;
use std::fs;
use std::fmt;
use fs::File;
use std::io::prelude::*;


#[derive(Debug)]
enum TokenType {
    Return,
    Semicolon,
    Literal,
    Variable,
}

struct Token {
    pub _type: TokenType,
    pub _value: Option<String>,
}

impl fmt::Debug for Token {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.debug_struct("Token")
            .field("_type", &self._type)
            .field("_value", &self._value)
            .finish()
    }
}

fn main() {
    let argv: Vec<String> = env::args().collect();
    let file_path = &argv[1].to_owned();
    let file_name = &argv[1].to_owned().replace(".phi", ".asm");

    let content = fs::read_to_string(file_path)
        .expect("error reading file");

    let mut tokenized: Vec<Token> = Vec::new();

    let mut i = 0;
    while i < content.len() {
        let mut token: String = Default::default();
        let c = content.chars().nth(i).unwrap();

        if c.is_alphabetic() {
            token.push(c);
            i += 1;

            while content.chars().nth(i).unwrap().is_alphanumeric() {
                token.push(content.chars().nth(i).unwrap());
                i += 1;
            }

            i -= 1;
            
            if token == "return" {
                tokenized.push(Token {
                    _type: TokenType::Return,
                    _value: None
                });
            }
            else {
                tokenized.push(Token {
                    _type: TokenType::Variable,
                    _value: Some(token.clone())
                });
            }
        }
        else if c.is_numeric() {
            token.push(c);
            i += 1;

            while content.chars().nth(i).unwrap().is_numeric() {
                token.push(content.chars().nth(i).unwrap());
                i += 1;
            }

            i -= 1;

            tokenized.push(Token {
                _type: TokenType::Literal,
                _value: Some(token.clone())
            });

        }
        else if c == ';' {
            tokenized.push(Token {
                _type: TokenType::Semicolon,
                _value: None
            });
        }

        i += 1;
    }



    for i in 0..tokenized.len() {
        match tokenized[i]._type {
            TokenType::Return => {
                let fd = File::create(file_name);
                println!("Return!");
                let _ = fd.expect("error writing to file").write_all(b"mov eax 60\n");
            },
            TokenType::Variable => println!("Variable!"),
            TokenType::Literal => println!("Literal!"),
            TokenType::Semicolon => println!("Semicolon!"),
        }
    }
    
    println!("{:?}", tokenized);
}
