
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

.method public static main2 : ([C)I
    .code stack 4 locals 2
        aload 0 ; load from a
        ldc 0
        caload
        ldc 1
        iadd
        istore 1 ; store to x
        ;; test1 11 expression
        iload 1 ; load from x
        ireturn
    .end code
.end method

.method public static main : ()I
    .code stack 1 locals 0
        ;; test1 29 expression
        ldc 'hi'
        invokevirtual Method java/lang/String toCharArray ()[C
        invokestatic Method test1 main2 ([C)I
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
