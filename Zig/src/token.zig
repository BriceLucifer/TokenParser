//! token.zig
const std = @import("std");

// Token 类型枚举
pub const TokenType = enum {
    ILLEGAL,
    EOF,
    IDENT,
    ASSIGN,
    PLUS,
    MINUS,
    BNAG,
    ASTERISK,
    SLASH,
    COMMA,
    BANG,
    SEMICOLON,
    LT,
    GT,
    LPAREN,
    RPAREN,
    LBRACKET,
    RBRACKET,
    LBRACE,
    RBRACE,
    INT,
    FUNCTION,
    LET,
    TRUE,
    FALSE,
    IF,
    ELSE,
    RETURN,
    EQ,
    NOT_EQ,
};

// Custom Format Implementation for TokenType
pub fn format(self: TokenType) []const u8 {
    return switch (self) {
        TokenType.ILLEGAL => "ILLEGAL",
        TokenType.EOF => "EOF",
        TokenType.IDENT => "IDENT",
        TokenType.ASSIGN => "ASSIGN",
        TokenType.PLUS => "PLUS",
        TokenType.MINUS => "MINUS",
        TokenType.BNAG => "BNAG",
        TokenType.ASTERISK => "ASTERISK",
        TokenType.SLASH => "SLASH",
        TokenType.COMMA => "COMMA",
        TokenType.BANG => "BANG",
        TokenType.SEMICOLON => "SEMICOLON",
        TokenType.LT => "LT",
        TokenType.GT => "GT",
        TokenType.LPAREN => "LPAREN",
        TokenType.RPAREN => "RPAREN",
        TokenType.LBRACKET => "LBRACKET",
        TokenType.RBRACKET => "RBRACKET",
        TokenType.LBRACE => "LBRACE",
        TokenType.RBRACE => "RBRACE",
        TokenType.INT => "INT",
        TokenType.FUNCTION => "FUNCTION",
        TokenType.LET => "LET",
        TokenType.TRUE => "TRUE",
        TokenType.FALSE => "FALSE",
        TokenType.IF => "IF",
        TokenType.ELSE => "ELSE",
        TokenType.RETURN => "RETURN",
        TokenType.EQ => "EQ",
        TokenType.NOT_EQ => "NOT_EQ",
    };
}

// HashMap 定义
pub const Hashmap = std.StringHashMap(TokenType);
pub var map: ?Hashmap = null;

// 初始化关键字 HashMap
pub fn initMap(allocator: *std.mem.Allocator) !void {
    if (map == null) {
        map = Hashmap.init(allocator.*);
        // 这里确保 map 不为 null
    }

    // 在 map 被初始化之后可以直接操作
    _ = try map.?.put("fn", TokenType.FUNCTION);
    _ = try map.?.put("let", TokenType.LET);
    _ = try map.?.put("true", TokenType.TRUE);
    _ = try map.?.put("false", TokenType.FALSE);
    _ = try map.?.put("if", TokenType.IF);
    _ = try map.?.put("else", TokenType.ELSE);
    _ = try map.?.put("return", TokenType.RETURN);
}


// Token 结构体定义
pub const Token = struct {
    Type: TokenType,
    Literal: []const u8,

    // Token 初始化函数
    pub fn init(token_type: TokenType, literal: []const u8) Token {
        return Token{
            .Type = token_type,
            .Literal = literal,
        };
    }
};

// 查找关键字对应的 TokenType
pub fn Look_up(keyword: []const u8) TokenType {
    if (map) |m| {
        if (m.get(keyword)) |token_type| {
            return token_type;
        }
    }
    return TokenType.IDENT;
}