
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

.method public static main1 : (ICC)I
    .code stack 1 locals 5
        ldc 10
        istore 3 ; store to d
        ldc 1
        istore 4 ; store to e
        ;; test1 16 expression
        iload 3 ; load from d
        istore 0 ; store to a
        ;; test1 17 expression
        iload 0 ; load from a
        ireturn
    .end code
.end method

.method public static main : ()I
    .code stack 3 locals 0
        ;; test1 21 expression
        ldc 10
        bipush 97
        bipush 98
        invokestatic Method test1 main1 (ICC)I
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
