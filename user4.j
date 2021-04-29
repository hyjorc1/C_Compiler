
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
    .code stack 2 locals 1
        ldc 0 ; instr_line 0 depth 1
        istore 0 ; store to i instr_line 1 depth -1
        iload 0 ; load from i instr_line 2 depth 1
        ifne L0 ; instr_line 3 depth -1
        goto L3 ; instr_line 4 depth 0
L0:
        iload 0 ; load from i instr_line 5 depth 1
        ldc 1 ; instr_line 6 depth 1
        isub ; instr_line 7 depth -1
        ifne L1 ; instr_line 8 depth -1
        goto L2 ; instr_line 9 depth 0
L1:
        ;; user4.c 7 expression
        ldc 2 ; instr_line 10 depth 1
        istore 0 ; store to i instr_line 11 depth -1
        goto L3 ; instr_line 12 depth 0
L2:
        ;; user4.c 9 expression
        ldc 4 ; instr_line 13 depth 1
        istore 0 ; store to i instr_line 14 depth -1
L3:
        ;; user4.c 12 expression
        iload 0 ; load from i instr_line 15 depth 1
        ldc 48 ; instr_line 16 depth 1
        iadd ; instr_line 17 depth -1
        invokestatic Method libc putchar (I)I ; instr_line 18 depth 0
        pop ; instr_line 19 depth -1
L4:
        ;; user4.c 13 expression
        ldc 10 ; instr_line 20 depth 1
        invokestatic Method libc putchar (I)I ; instr_line 21 depth 0
        pop ; instr_line 22 depth -1
L5:
        ;; user4.c 14 expression
        iload 0 ; load from i instr_line 23 depth 1
        ireturn ; instr_line 24 depth -1
    .end code
.end method

.method public static if_stmt : ()V
    .code stack 2 locals 1
        ldc 1 ; instr_line 0 depth 1
        istore 0 ; store to i instr_line 1 depth -1
        iload 0 ; load from i instr_line 2 depth 1
        ifne L0 ; instr_line 3 depth -1
        goto L1 ; instr_line 4 depth 0
L0:
        ;; user4.c 20 expression
        ldc 2 ; instr_line 5 depth 1
        istore 0 ; store to i instr_line 6 depth -1
L1:
        ;; user4.c 22 expression
        iload 0 ; load from i instr_line 7 depth 1
        ldc 48 ; instr_line 8 depth 1
        iadd ; instr_line 9 depth -1
        invokestatic Method libc putchar (I)I ; instr_line 10 depth 0
        pop ; instr_line 11 depth -1
L2:
        ;; user4.c 23 expression
        ldc 10 ; instr_line 12 depth 1
        invokestatic Method libc putchar (I)I ; instr_line 13 depth 0
        pop ; instr_line 14 depth -1
        return
    .end code
.end method

.method public static if_else_stmt : ()V
    .code stack 2 locals 1
        ldc 1 ; instr_line 0 depth 1
        istore 0 ; store to i instr_line 1 depth -1
        iload 0 ; load from i instr_line 2 depth 1
        ifne L0 ; instr_line 3 depth -1
        goto L3 ; instr_line 4 depth 0
L0:
        iload 0 ; load from i instr_line 5 depth 1
        ldc 1 ; instr_line 6 depth 1
        isub ; instr_line 7 depth -1
        ifne L1 ; instr_line 8 depth -1
        goto L2 ; instr_line 9 depth 0
L1:
        ;; user4.c 30 expression
        ldc 2 ; instr_line 10 depth 1
        istore 0 ; store to i instr_line 11 depth -1
        goto L4 ; instr_line 12 depth 0
L2:
        ;; user4.c 32 expression
        ldc 4 ; instr_line 13 depth 1
        istore 0 ; store to i instr_line 14 depth -1
        goto L4 ; instr_line 15 depth 0
L3:
        ;; user4.c 35 expression
        ldc 3 ; instr_line 16 depth 1
        istore 0 ; store to i instr_line 17 depth -1
L4:
        ;; user4.c 37 expression
        iload 0 ; load from i instr_line 18 depth 1
        ldc 48 ; instr_line 19 depth 1
        iadd ; instr_line 20 depth -1
        invokestatic Method libc putchar (I)I ; instr_line 21 depth 0
        pop ; instr_line 22 depth -1
L5:
        ;; user4.c 38 expression
        ldc 10 ; instr_line 23 depth 1
        invokestatic Method libc putchar (I)I ; instr_line 24 depth 0
        pop ; instr_line 25 depth -1
        return
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
