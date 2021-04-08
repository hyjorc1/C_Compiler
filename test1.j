
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
    .code stack 1 locals 3
        ;; test1 17 expression
        iload 0 ; load from a
        ineg
        istore 0 ; store to a
        ;; test1 18 expression
        fload 2 ; load from c
        fneg
        fstore 2 ; store to c
        ;; test1 19 expression
        iload 0 ; load from a
        ireturn
    .end code
.end method

.method public static main : ()I
    .code stack 3 locals 0
        ;; test1 23 expression
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
