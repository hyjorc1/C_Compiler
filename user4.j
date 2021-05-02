
; Java assembly code

.class public user4
.super java/lang/Object

; Global vars

.field static N I

; Default constructor

.method <init> : ()V
    .code stack 1 locals 1
        aload_0
        invokespecial Method java/lang/Object <init> ()V
        return
    .end code
.end method

; Methods

.method public static print : (I)V
    .code stack 3 locals 1
        ;; user4.c 8 if statement
        iload 0 ; load from x instr_line 0 depth 1
        ldc 0 ; instr_line 1 depth 1
        if_icmplt L0 ; instr_line 2 depth -2
        goto L2 ; instr_line 3 depth 0
L0:
        ;; user4.c 9 expression
        bipush 45 ; instr_line 4 depth 1
        invokestatic Method libc putchar (I)I ; instr_line 5 depth 0
        pop ; instr_line 6 depth -1
L1:
        ;; user4.c 10 return
        return ; instr_line 7 depth 0
L2:
        ;; user4.c 12 if statement
        iload 0 ; load from x instr_line 8 depth 1
        ldc 9 ; instr_line 9 depth 1
        if_icmpgt L3 ; instr_line 10 depth -2
        goto L4 ; instr_line 11 depth 0
L3:
        ;; user4.c 13 expression
        iload 0 ; load from x instr_line 12 depth 1
        ldc 10 ; instr_line 13 depth 1
        idiv ; instr_line 14 depth -1
        invokestatic Method user4 print (I)V ; instr_line 15 depth -1
L4:
        ;; user4.c 15 expression
        ldc 48 ; instr_line 16 depth 1
        iload 0 ; load from x instr_line 17 depth 1
        ldc 10 ; instr_line 18 depth 1
        irem ; instr_line 19 depth -1
        iadd ; instr_line 20 depth -1
        invokestatic Method libc putchar (I)I ; instr_line 21 depth 0
        pop ; instr_line 22 depth -1
L5:
        return
    .end code
.end method

.method public static print_row : ([II)V
    .code stack 2 locals 3
        ;; user4.c 21 for statement
        ldc 0 ; instr_line 0 depth 1
        istore 2 ; store to i instr_line 1 depth -1
L0:
        iload 2 ; load from i instr_line 2 depth 1
        iload 1 ; load from n instr_line 3 depth 1
        if_icmplt L2 ; instr_line 4 depth -2
        goto L4 ; instr_line 5 depth 0
L1:
        iload 2 ; load from i instr_line 6 depth 1
        iconst_1 ; instr_line 7 depth 1
        iadd ; instr_line 8 depth -1
        istore 2 ; store to i instr_line 9 depth -1
        goto L0 ; instr_line 10 depth 0
L2:
        ;; user4.c 22 expression
        aload 0 ; load from A instr_line 11 depth 1
        iload 2 ; load from i instr_line 12 depth 1
        iaload ; instr_line 13 depth -1
        invokestatic Method user4 print (I)V ; instr_line 14 depth -1
L3:
        ;; user4.c 23 expression
        ldc 32 ; instr_line 15 depth 1
        invokestatic Method libc putchar (I)I ; instr_line 16 depth 0
        pop ; instr_line 17 depth -1
        goto L1 ; instr_line 18 depth 0
L4:
        ;; user4.c 25 expression
        ldc 10 ; instr_line 19 depth 1
        invokestatic Method libc putchar (I)I ; instr_line 20 depth 0
        pop ; instr_line 21 depth -1
L5:
        return
    .end code
.end method

.method public static main : ()I
    .code stack 3 locals 5
        ldc 10 ; instr_line 0 depth 1
        newarray int ; instr_line 1 depth 0
        astore 4 ; store to A instr_line 2 depth -1
        ;; user4.c 32 expression
        ldc 9 ; instr_line 3 depth 1
        putstatic Field user4 N I ; instr_line 4 depth -1
L0:
        ;; user4.c 34 expression
        aload 4 ; load from A instr_line 5 depth 1
        ldc 0 ; instr_line 6 depth 1
        ldc 1 ; instr_line 7 depth 1
        iastore ; instr_line 8 depth -3
L1:
        ;; user4.c 35 for statement
        ldc 1 ; instr_line 9 depth 1
        istore 0 ; store to i instr_line 10 depth -1
L2:
        iload 0 ; load from i instr_line 11 depth 1
        getstatic Field user4 N I ; instr_line 12 depth 1
        if_icmple L4 ; instr_line 13 depth -2
        goto L5 ; instr_line 14 depth 0
L3:
        iload 0 ; load from i instr_line 15 depth 1
        iconst_1 ; instr_line 16 depth 1
        iadd ; instr_line 17 depth -1
        istore 0 ; store to i instr_line 18 depth -1
        goto L2 ; instr_line 19 depth 0
L4:
        ;; user4.c 36 expression
        aload 4 ; load from A instr_line 20 depth 1
        iload 0 ; load from i instr_line 21 depth 1
        ldc 0 ; instr_line 22 depth 1
        iastore ; instr_line 23 depth -3
        goto L3 ; instr_line 24 depth 0
L5:
        ;; user4.c 38 expression
        aload 4 ; load from A instr_line 25 depth 1
        ldc 1 ; instr_line 26 depth 1
        invokestatic Method user4 print_row ([II)V ; instr_line 27 depth -2
L6:
        ;; user4.c 39 for statement
        ldc 1 ; instr_line 28 depth 1
        istore 0 ; store to i instr_line 29 depth -1
L7:
        iload 0 ; load from i instr_line 30 depth 1
        getstatic Field user4 N I ; instr_line 31 depth 1
        if_icmplt L9 ; instr_line 32 depth -2
        goto L17 ; instr_line 33 depth 0
L8:
        iload 0 ; load from i instr_line 34 depth 1
        iconst_1 ; instr_line 35 depth 1
        iadd ; instr_line 36 depth -1
        istore 0 ; store to i instr_line 37 depth -1
        goto L7 ; instr_line 38 depth 0
L9:
        ;; user4.c 40 expression
        ldc 0 ; instr_line 39 depth 1
        istore 2 ; store to prev instr_line 40 depth -1
L10:
        ;; user4.c 41 for statement
        ldc 0 ; instr_line 41 depth 1
        istore 1 ; store to j instr_line 42 depth -1
L11:
        iload 1 ; load from j instr_line 43 depth 1
        iload 0 ; load from i instr_line 44 depth 1
        if_icmple L13 ; instr_line 45 depth -2
        goto L16 ; instr_line 46 depth 0
L12:
        iload 1 ; load from j instr_line 47 depth 1
        iconst_1 ; instr_line 48 depth 1
        iadd ; instr_line 49 depth -1
        istore 1 ; store to j instr_line 50 depth -1
        goto L11 ; instr_line 51 depth 0
L13:
        ;; user4.c 42 expression
        aload 4 ; load from A instr_line 52 depth 1
        iload 1 ; load from j instr_line 53 depth 1
        iaload ; instr_line 54 depth -1
        iload 2 ; load from prev instr_line 55 depth 1
        iadd ; instr_line 56 depth -1
        istore 3 ; store to next instr_line 57 depth -1
L14:
        ;; user4.c 43 expression
        aload 4 ; load from A instr_line 58 depth 1
        iload 1 ; load from j instr_line 59 depth 1
        iaload ; instr_line 60 depth -1
        istore 2 ; store to prev instr_line 61 depth -1
L15:
        ;; user4.c 44 expression
        aload 4 ; load from A instr_line 62 depth 1
        iload 1 ; load from j instr_line 63 depth 1
        iload 3 ; load from next instr_line 64 depth 1
        iastore ; instr_line 65 depth -3
        goto L12 ; instr_line 66 depth 0
L16:
        ;; user4.c 46 expression
        aload 4 ; load from A instr_line 67 depth 1
        iload 0 ; load from i instr_line 68 depth 1
        ldc 1 ; instr_line 69 depth 1
        iadd ; instr_line 70 depth -1
        invokestatic Method user4 print_row ([II)V ; instr_line 71 depth -2
        goto L8 ; instr_line 72 depth 0
L17:
        ;; user4.c 49 return
        ldc 0 ; instr_line 73 depth 1
        ireturn ; instr_line 74 depth -1
L18:
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
