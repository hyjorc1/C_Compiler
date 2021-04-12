
; Java assembly code

.class public test1
.super java/lang/Object

; Global vars

.field static i1 I
.field static i2 I
.field static c1 C
.field static c2 C
.field static f1 F
.field static f2 F

.method static <clinit> : ()V
    .code stack 1 locals 0
        ; Initializing i1
        ldc 1 ; depth 1
        putstatic Field test1 i1 I ; depth -1
        ; Initializing i2
        ldc 2 ; depth 1
        putstatic Field test1 i2 I ; depth -1
        ; Initializing c1
        bipush 97 ; depth 1
        putstatic Field test1 c1 C ; depth -1
        ; Initializing c2
        bipush 98 ; depth 1
        putstatic Field test1 c2 C ; depth -1
        ; Initializing f1
        ldc +2.1f ; depth 1
        putstatic Field test1 f1 F ; depth -1
        ; Initializing f2
        ldc +2.2f ; depth 1
        putstatic Field test1 f2 F ; depth -1
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
    .code stack 2 locals 9
        ldc 1 ; depth 1
        istore 0 ; store to li1 and depth -1
        ldc 2 ; depth 1
        istore 1 ; store to li2 and depth -1
        bipush 97 ; depth 1
        istore 2 ; store to lc1 and depth -1
        bipush 98 ; depth 1
        istore 3 ; store to lc2 and depth -1
        ldc +2.1f ; depth 1
        fstore 4 ; store to lf1 and depth -1
        ldc +2.2f ; depth 1
        fstore 5 ; store to lf2 and depth -1
        getstatic Field test1 i1 I ; depth 1
        getstatic Field test1 c1 C ; depth 1
        iadd ; depth -1
        getstatic Field test1 f1 F ; depth 1
        f2i
        iadd ; depth -1
        istore 6 ; store to s1 and depth -1
        iload 0 ; load from li1 and depth 1
        iload 2 ; load from lc1 and depth 1
        iadd ; depth -1
        fload 4 ; load from lf1 and depth 1
        f2i
        iadd ; depth -1
        istore 7 ; store to s2 and depth -1
        iload 0 ; load from li1 and depth 1
        getstatic Field test1 c1 C ; depth 1
        iadd ; depth -1
        fload 4 ; load from lf1 and depth 1
        f2i
        iadd ; depth -1
        istore 8 ; store to s3 and depth -1
        ;; test1 14 expression
        iload 6 ; load from s1 and depth 1
        iload 7 ; load from s2 and depth 1
        iadd ; depth -1
        iload 8 ; load from s3 and depth 1
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
