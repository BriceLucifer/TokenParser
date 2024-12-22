// main.zig
const std = @import("std");
const lexer = @import("lexer.zig");
const token = @import("token.zig");

pub fn lex_input(input: []const u8) !void {
    var lex = lexer.Lexer.init(input);
    var tok: token.Token = token.Token.init(token.TokenType.ILLEGAL, "");

    var allocator = std.heap.page_allocator;
    try token.initMap(&allocator);

    while (true) {
        tok = lex.next_token();
        if (tok.Type == token.TokenType.EOF) break;
        std.debug.print("({s} \"{s}\")\n", .{ token.format(tok.Type), tok.Literal });
    }
    defer token.map.?.deinit();
}

pub fn main() !void {
    const hello: []const u8 = "let add:fn = fn (a,b) { return a + b ;} - / [] {} (); == != !! // #";
    try lex_input(hello);
}


