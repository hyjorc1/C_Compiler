
; Java assembly code

.class public test1
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

.method public static fn : ()V
    .code stack 0 locals 0
        return
    .end code
.end method

.method public static zero : ()I
    .code stack 1 locals 0
        ;; test1 3 expression
        ldc 0 ; depth 1
        ireturn ; depth -1
    .end code
.end method

.method public static main : ()I
    .code stack 2 locals 1
        ;; test1 7 expression
        invokestatic Method test1 zero ()I ; depth 1
        istore 0 ; store to x and depth -1
        ;; test1 8 expression
        invokestatic Method test1 zero ()I ; depth 1
        invokestatic Method test1 zero ()I ; depth 1
        iadd ; depth -1
        ldc 1 ; depth 1
        iadd ; depth -1
        ireturn ; depth -1
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
