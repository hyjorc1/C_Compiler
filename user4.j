
; Java assembly code

.class public user4
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
        ;; user4.c 5 expression
        ldc 0 ; instr_line 0 depth 1
        ireturn ; instr_line 1 depth -1
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
