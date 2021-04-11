
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

.method public static main : ()I
    .code stack 1 locals 0
        ;; test1 4 expression
        ldc 0 ; depth 1
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
