#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <fstream>
#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

using namespace std;

// https://stackoverflow.com/questions/40663527/how-to-inherit-from-yyflexlexer
class Scanner : public yyFlexLexer
{
public:
    // Scanner(istream *in) : yyFlexLexer(in){};
    virtual ~Scanner(){};
    Scanner(){};

    // get rid of override virtual function warning
    using FlexLexer::yylex;
    virtual int yylex();

    const char *curfilename;

    struct bufstack
    {
        struct bufstack *prev{nullptr};
        yy_buffer_state *bs{nullptr};
        int lineno;
        const char *filename{nullptr};
        filebuf *fb{nullptr};
    } *curbs {nullptr};

    int newfile(istream *in, const char *fn, filebuf *fb);

    int newfile(const char *fn);

    int popfile(void);
};

#endif
