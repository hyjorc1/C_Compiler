#ifndef TOKEN_MAP_H
#define TOKEN_MAP_H

#include <stdio.h>
#include <string.h>

char *map(int token) { 
    switch (token) { 
        case 260: return "TYPE";

        case 261: return "CONST";
        case 262: return "STRUCT";
        case 263: return "FOR";
        case 264: return "WHILE";

        case 265: return "DO";
        case 266: return "IF";
        case 267: return "ELSE";
        case 268: return "BREAK";
        case 269: return "CONTINUE";
        case 270: return "RETURN";

        case 271: return "IDENT";
        case 272: return "INTCONST";
        case 273: return "REALCONST";
        case 274: return "STRCONST";
        case 275: return "CHARCONST";

        case 276: return "LPAR";
        case 277: return "RPAR";
        case 278: return "LBRACKET";
        case 279: return "RBRACKET";
        case 280: return "LBRACE";
        case 281: return "RBRACE";

        case 282: return "DOT";
        case 283: return "COMMA";
        case 284: return "SEMI";
        case 285: return "QUEST";
        case 286: return "COLON";

        case 287: return "PLUS";
        case 288: return "MINUS";
        case 289: return "STAR";
        case 290: return "SLASH";
        case 291: return "MOD";
        case 292: return "TILDE";

        case 293: return "PIPE";
        case 294: return "AMP";
        case 295: return "BANG";
        case 296: return "DPIPE";
        case 297: return "DAMP";

        case 298: return "ASSIGN";
        case 299: return "PLUSASSIGN";
        case 300: return "MINUSASSIGN";
        case 301: return "STARASSIGN";
        case 302: return "SLASHASSIGN";
        case 303: return "INCR";
        case 304: return "DECR";

        case 305: return "EQUALS";
        case 306: return "NEQUAL";
        case 307: return "GT";
        case 308: return "GE";
        case 309: return "LT";
        case 310: return "LE";

        default:
            return "UNKOWN";
    }
}

#endif