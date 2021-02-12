#ifndef TOKEN_MAP_H
#define TOKEN_MAP_H

#include <map>
#include <string>

using namespace std;

map<int, string> enum_map = {
    {260, "TYPE"},

    {261, "CONST"},
    {262, "STRUCT"},
    {263, "FOR"},
    {264, "WHILE"},
    {265, "DO"},
    {266, "IF"},
    {267, "ELSE"},
    {268, "BREAK"},
    {269, "CONTINUE"},
    {270, "RETURN"},

    {271, "IDENT"},
    {272, "INTCONST"},
    {273, "REALCONST"},
    {274, "STRCONST"},
    {275, "CHARCONST"},

    {276, "LPAR"},
    {277, "RPAR"},
    {278, "LBRACKET"},
    {279, "RBRACKET"},
    {280, "LBRACE"},
    {281, "RBRACE"},

    {282, "DOT"},
    {283, "COMMA"},
    {284, "SEMI"},
    {285, "QUEST"},
    {286, "COLON"},

    {287, "PLUS"},
    {288, "MINUS"},
    {289, "STAR"},
    {290, "SLASH"},
    {291, "MOD"},
    {292, "TILDE"},

    {293, "PIPE"},
    {294, "AMP"},
    {295, "BANG"},
    {296, "DPIPE"},
    {297, "DAMP"},

    {298, "ASSIGN"},
    {299, "PLUSASSIGN"},
    {300, "MINUSASSIGN"},
    {301, "STARASSIGN"},
    {302, "SLASHASSIGN"},
    {303, "INCR"},
    {304, "DECR"},

    {305, "EQUALS"},
    {306, "NEQUAL"},
    {307, "GT"},
    {308, "GE"},
    {309, "LT"},
    {310, "LE"},
    
};

#endif