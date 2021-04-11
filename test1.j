
; Java assembly code

.class public test1
.super java/lang/Object

; Global vars

.field static x [I

.method static <clinit> : ()V
    .code stack 1 locals 0
        ; Initializing x
        ldc 5 ; depth 0
        newarray int
        putstatic Field test1 x [I ; depth 0
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
    .code stack 6 locals 0
        ;; test1 8 expression
        getstatic Field test1 x [I ; depth 1
        ldc 3 ; depth 1
        getstatic Field test1 x [I ; depth 1
        ldc 2 ; depth 1
        ldc 10 ; depth 1
        dup_x2 ; depth 1
        iastore ; depth -3
        dup_x2 ; depth 1
        iastore ; depth -3
        pop ; depth -1
        ;; test1 9 expression
        getstatic Field test1 x [I ; depth 1
        ldc 2 ; depth 1
        iaload ; depth -1
        getstatic Field test1 x [I ; depth 1
        ldc 3 ; depth 1
        iaload ; depth -1
        iadd
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
