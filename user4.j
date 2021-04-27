
; Java assembly code

.class public user4
.super java/lang/Object

; Global vars

.field static x [I

.method static <clinit> : ()V
    .code stack 1 locals 0
        ; Initializing x
        ldc 10 ; depth 1
        newarray int
        putstatic Field user4 x [I ; depth -1
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
        ;; user4.c 8 expression
        getstatic Field user4 x [I ; depth 1
        ldc 0 ; depth 1
        ldc 0 ; depth 1
        iastore ; depth -3
        ;; user4.c 9 expression
        getstatic Field user4 x [I ; depth 1
        ldc 1 ; depth 1
        ldc 1 ; depth 1
        iastore ; depth -3
        ;; user4.c 10 expression
        getstatic Field user4 x [I ; depth 1
        ldc 0 ; depth 1
        getstatic Field user4 x [I ; depth 1
        ldc 1 ; depth 1
        dup2 ; depth 2
        iaload ; depth -1
        iconst_1 ; depth 1
        iadd ; depth -1
        dup_x2 ; depth 1
        iastore ; depth -3
        iastore ; depth -3
        ;; user4.c 11 expression
        getstatic Field user4 x [I ; depth 1
        ldc 0 ; depth 1
        iaload ; depth -1
        getstatic Field user4 x [I ; depth 1
        ldc 1 ; depth 1
        iaload ; depth -1
        iadd ; depth -1
        ldc 48 ; depth 1
        iadd ; depth -1
        invokestatic Method libc putchar (I)I ; depth 0
        pop ; depth -1
        ;; user4.c 12 expression
        ldc 10 ; depth 1
        invokestatic Method libc putchar (I)I ; depth 0
        pop ; depth -1
        ;; user4.c 13 expression
        getstatic Field user4 x [I ; depth 1
        ldc 0 ; depth 1
        iaload ; depth -1
        getstatic Field user4 x [I ; depth 1
        ldc 1 ; depth 1
        iaload ; depth -1
        iadd ; depth -1
        ireturn ; depth -1
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
