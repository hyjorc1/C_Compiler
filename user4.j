
; Java assembly code

.class public user4
.super java/lang/Object

; Global vars

; Default constructor

.method <init> : ()V
    .code stack 1 locals 1
        aload_0
        invokespecial Method java/lang/Object <init> ()V
        return
    .end code
.end method

; Methods

.method public static main : ()I
    .code stack 1 locals 2
        bipush 48 ; instr_line 0 depth 1
        istore 0 ; store to c instr_line 1 depth -1
        ;; user4.c 19 expression
        iload 0 ; load from c instr_line 2 depth 1
        istore 1 ; store to x instr_line 3 depth -1
        ;; user4.c 20 expression
        iload 0 ; load from c instr_line 4 depth 1
        ireturn ; instr_line 5 depth -1
    .end code
.end method

; Java main function

.method public static main : ([Ljava/lang/String;)V
    .code stack 1 locals 1
        invokestatic Method user4 main ()I
        pop
        return
    .end code
.end method
