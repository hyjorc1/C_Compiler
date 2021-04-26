#ifndef INSTR_H
#define INSTR_H

#include <iostream>
#include <string>
#include <map>

struct attributes;  // in lexer.h

class expr;
class environment;

class instruction {
    int labelid;
  public:
    instruction(int labelid = -1);
    virtual ~instruction();

    virtual void show(std::ostream &s) const = 0;
    virtual void execute(environment &e) const = 0;

    inline bool isLabel() const { return labelid >= 0; }
    inline int getLabel() const { return labelid; }
    inline bool isInvisible() const { return labelid < -1; }
};

inline std::ostream& operator<< (std::ostream &s, const instruction* i)
{
  if (0==i) return s;
  if (i->isInvisible()) return s;
  if (!i->isLabel()) s << "        ";
  i->show(s);
  return s << "\n";
}

/*
  Build an appropriate instruction for the current token.
  May use the lexer to read additional info, as needed.

  @param  tid     Token id of instruction
  @param  A       Token attributes

*/
instruction* buildInstruction(int tid, const attributes &A);



/*
  Runtime environment for analyzing instructions.
*/
class environment {
  private:
    struct node {
      expr* data;
      node* next;
    }; // struct environment::node

    node* head;
    unsigned depth;
    unsigned max_depth;
    std::ostream& sout;

    const char* current_method;
    unsigned stack_req;
  public:
    std::map <std::string, int> versions;

  public:
    environment(std::ostream &s);
    ~environment();

    void startMethod(const char* methname, unsigned maxstack);
    void endMethod();

    void annotate(const char* info);

    inline std::ostream& out() const { return sout; }

    inline bool is_empty() const { 
      return 0==head; 
    }
    inline expr* top() const {
      if (0==head) return 0;
      return head->data;
    }
    expr* pop(const instruction* instr);
    void push(expr* d);
};

template <class T>
inline std::ostream& operator<< (environment &e, const T &x)
{
  return e.out() << x;
}


#endif
