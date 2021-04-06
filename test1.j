
; Java assembly code

.class public test1
.super java/lang/Object

; Global vars

.field static x [I
.field static y1 I
.field static y2 C
.field static y3 F

.method static <clinit> : ()V
    .code stack 1 locals 0
        iconst_0
        putstatic Field test1 y1 I
        bipush 97
        putstatic Field test1 y2 C
        ldc +1.1f
        putstatic Field test1 y3 F
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

.method public static main : ()I
    .code stack 2 locals 0
        iconst_0
        ireturn
    .end code
.end method

.method public static main2 : ([ICF)V
    .code stack 2 locals 3
        return
    .end code
.end method

.method public static main3 : ()V
    .code stack 2 locals 0
        return
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
