#ifndef TOKEN_H
#define TOKEN_H

enum yytokentype
{
    /* Type name: void, char, int, or float */
    TYPE = 260,

    /* keywords */
    CONST = 261,
    STRUCT = 262,
    FOR = 263,
    WHILE = 264,
    DO = 265,
    IF = 266,
    ELSE = 267,
    BREAK = 268,
    CONTINUE = 269,
    RETURN = 270,

    /* Identifier: sequence of letters, underscores, 
    or digits that does not start with a digit, and 
    is not a keyword */
    IDENT = 271,

    /* Integer constant: one or more digits */
    INTCONST = 272,

    /*  Real constant: one or more digits, optional 
    decimal part, optional exponent part, not an integer 
    constant; OR decimal part and optional exponent part */
    REALCONST = 273,

    /* String constant: double quoted string, can have ‘\"’ inside */
    STRCONST = 274,

    /* Character constant: single quote, character other 
    than \ and ’, single quote; OR single quote, \, 
    character, single quote for escape sequences: 
    ’\a’, ’\b’, ’\n’, ’\r’, ’\t’, ’\\’, ’\’’ */
    CHARCONST = 275,

    LPAR = 276,     // "("
    RPAR = 277,     // ")"
    LBRACKET = 278, // "["
    RBRACKET = 279, // "]"
    LBRACE = 280,   // "{"
    RBRACE = 281,   // "}"

    DOT = 282,   // "."
    COMMA = 283, // ","
    SEMI = 284,  // ";"
    QUEST = 285, // "?"
    COLON = 286, // ":"

    PLUS = 287,  // "+"
    MINUS = 288, // "-"
    STAR = 289,  // "*"
    SLASH = 290, // "/"
    MOD = 291,   // "%"
    TILDE = 292, // "~"

    PIPE = 293,  // "|"
    AMP = 294,   // "&"
    BANG = 295,  // "!"
    DPIPE = 296, // "||"
    DAMP = 297,  // "&&"

    ASSIGN = 298,      // "="
    PLUSASSIGN = 299,  // "+="
    MINUSASSIGN = 300, // "-="
    STARASSIGN = 301,  // "*="
    SLASHASSIGN = 302, // "/="
    INCR = 303,        // "++"
    DECR = 304,        // "--"

    EQUALS = 305, // "=="
    NEQUAL = 306, // "!="
    GT = 307,     // ">"
    GE = 308,     // ">="
    LT = 309,     // "<"
    LE = 310,     // "<="

    ERR = 1000, // error

    END = 2000
};

#endif
