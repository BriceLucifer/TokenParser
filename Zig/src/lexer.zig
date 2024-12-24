//! lexer.zig
const std = @import("std");
const token = @import("token.zig");


// Lexer 结构体
pub const Lexer = struct {
    input: []const u8,         // 输入源码
    position: usize,           // 当前索引
    read_position: usize,      // 下一个字符的索引
    ch: u8,                    // 当前字符

    // 初始化 Lexer
    pub fn init(input: []const u8) Lexer {
        var l = Lexer{
            .input = input,
            .position = 0,
            .read_position = 0,
            .ch = 0,
        };
        l.read_char();
        return l;
    }

    // 读取下一个字符
    pub fn read_char(self: *Lexer) void {
        if (self.read_position >= self.input.len) {
            self.ch = 0; // EOF
        } else {
            self.ch = self.input[self.read_position];
        }
        self.position = self.read_position;
        self.read_position += 1;
    }

    pub fn peek_char(self: *Lexer) u8 {
        if (self.read_position >= self.input.len) {
            return 0;
        }else {
            return self.input[self.read_position];
        }
    }

    // 读取标识符
    pub fn read_identifier(self: *Lexer) []const u8 {
        const start = self.position;
        while (is_letter(self.ch)) {
            self.read_char();
        }
        return self.input[start..self.position];
    }

    // 读取数字
    pub fn read_number(self: *Lexer) []const u8 {
        const start = self.position;
        while (is_digit(self.ch)) {
            self.read_char();
        }
        return self.input[start..self.position];
    }

    // 跳过空白字符
    fn skip_whitespace(self: *Lexer) void {
        while (self.ch == ' ' or self.ch == '\t' or self.ch == '\n' or self.ch == '\r') {
            self.read_char();
        }
    }

    // 获取下一个 Token
    pub fn next_token(self: *Lexer) token.Token {
        var tok: token.Token = undefined;
        self.skip_whitespace();

        switch (self.ch) {
            '=' => { 
                if (self.peek_char() == '=') {
                    // const ch = self.ch;
                    self.read_char();
                    tok.Type = token.TokenType.EQ;
                    tok.Literal = "==";
                } else {
                    tok.Type = token.TokenType.ASSIGN;
                    tok.Literal = self.ch;
                }
            },
            '!' => {
                if (self.peek_char() == '=') {
                    // const ch = self.ch;
                    self.read_char();
                    tok.Type = token.TokenType.NOT_EQ;
                    tok.Literal = "!=";
                } else {
                    tok.Type = token.TokenType.BANG;
                    tok.Literal = "!";
                }
            },
            '/' => {
                tok = token.Token.init(token.TokenType.SLASH, []u8{self.ch});
            },
            '*' => {
                tok = token.Token.init(token.TokenType.ASTERISK, "*");
            },
            '<' => {
                tok = token.Token.init(token.TokenType.LT, "<");
            },
            '>' => {
                tok = token.Token.init(token.TokenType.GT, ">");
            },
            ';' => {
                tok = token.Token.init(token.TokenType.SEMICOLON, ";");
            },
            '(' => {
                tok = token.Token.init(token.TokenType.LPAREN, "(");
            },
            ')' => {
                tok = token.Token.init(token.TokenType.RPAREN, ")");
            },
            ',' => {
                tok = token.Token.init(token.TokenType.COMMA, ",");
            },
            '+' => {
                tok = token.Token.init(token.TokenType.PLUS, "+");
            },
            '-' => {
                tok = token.Token.init(token.TokenType.MINUS, "-");
            },
            '{' => {
                tok = token.Token.init(token.TokenType.LBRACE, "{");
            },
            '}' => {
                tok = token.Token.init(token.TokenType.RBRACE, "}");
            },
            '[' => {
                tok = token.Token.init(token.TokenType.LBRACKET, "[");
            },
            ']' => {
                tok = token.Token.init(token.TokenType.RBRACKET, "]");
            },
            ':' => {
                tok = token.Token.init(token.TokenType.COLON, ":");
            },
            0 => {
                tok = token.Token.init(token.TokenType.EOF, "0");
            },
            else  => {
                if (is_letter(self.ch)) {
                    const literal = self.read_identifier();
                    // lookup keywords
                    const token_type = token.Look_up(literal);
                    return token.Token.init(token_type, literal);
                } else if (is_digit(self.ch)) {
                    const literal = self.read_number();
                    return token.Token.init(token.TokenType.INT, literal);
                } else {
                    tok = token.Token.init(token.TokenType.ILLEGAL, "illegal_token",);
                }
            }
        }
        self.read_char();
        return tok;
    }

    // 判断是否是字母
    fn is_letter(ch: u8) bool {
        return (ch >= 'a' and ch <= 'z') or (ch >= 'A' and ch <= 'Z') or (ch == '_');
    }
    // 判断是否是数字
    fn is_digit(ch: u8) bool {
        return ch >= '0' and ch <= '9';
    }
  
};
