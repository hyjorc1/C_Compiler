
; Java assembly code

.class public test1
.super java/lang/Object

; Global vars

.field static x I
.field static y I

.method static <clinit> : ()V
    .code stack 1 locals 0
        ; Initializing x
        ldc 1
        putstatic Field test1 x I
        return
    .end code
.end method

; Default constructor

.method <init> : ()V
    .code stack 1 locals 1
        aload_0
        invokespecial Method java/lang/Object <init> ()V
        return
    .end code
.end method

; Methods

.method public static main1 : (ICF)I
    .code stack 6 locals 3
        ;; test1 18 expression
        iload 0 ; load from a
        iload 0 ; load from a
        iadd
        istore 0 ; store to a
        ;; test1 20 expression
        iload 0 ; load from a
        iload 0 ; load from a
        irem
        istore 0 ; store to a
        ;; test1 22 expression
        iload 1 ; load from b
        iload 1 ; load from b
        isub
        i2c
        istore 1 ; store to b
        ;; test1 24 expression
        fload 2 ; load from c
        fload 2 ; load from c
        fmul
        fstore 2 ; store to c
        ;; test1 26 expression
        fload 2 ; load from c
        fload 2 ; load from c
        fdiv
        fstore 2 ; store to c
        ;; test1 27 expression
        iload 0 ; load from a
        ireturn
    .end code
.end method

.method public static main : ()I
    .code stack 3 locals 0
        ;; test1 31 expression
        ldc 10
        bipush 97
        ldc +1.0f
        invokestatic Method test1 main1 (ICF)I
        ireturn
    .end code
.end method

; Java main function

.method public static main : ([Ljava/lang/String;)V
    .code stack 2 locals 2
        invokestatic Method test1 main ()I
        istore_1
        getstatic Field java/lang/System out Ljava/io/PrintStream;
        ldc 'Return code: '
        invokevirtual Method java/io/PrintStream print (Ljava/lang/String;)V
        getstatic Field java/lang/System out Ljava/io/PrintStream;
        iload_1
        invokevirtual Method java/io/PrintStream println (I)V
        return
    .end code
.end method
