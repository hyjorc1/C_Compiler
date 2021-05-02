
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
    .code stack 3 locals 2
        ldc 0 ; instr_line 0 depth 1
        istore 0 ; store to i instr_line 1 depth -1
        ldc 1 ; instr_line 2 depth 1
        dup ; instr_line 3 depth 1
        istore 0 ; store to i instr_line 4 depth -1
        istore 1 ; store to j instr_line 5 depth -1
        ;; user4.c 4 expression
        iload 0 ; load from i instr_line 6 depth 1
        dup ; instr_line 7 depth 1
        iconst_1 ; instr_line 8 depth 1
        iadd ; instr_line 9 depth -1
        istore 0 ; store to i instr_line 10 depth -1
        istore 0 ; store to i instr_line 11 depth -1
L0:
        ldc 0 ; instr_line 12 depth 1
        ireturn ; instr_line 13 depth -1
L1:
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
