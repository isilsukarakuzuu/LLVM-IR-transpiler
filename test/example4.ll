; ModuleID = 'advcalc2ir'
declare i32 @printf(i8*, ...)
@print.str = constant [4 x i8] c"%d\0A\00"

define i32 @main() {
%x = alloca i32
store i32 1, i32* %x
%1 = load i32, i32* %x
%2 = add i32 %1, 3
%y = alloca i32
store i32 %2, i32* %y
%3 = load i32, i32* %x
%4 = load i32, i32* %y
%5 = mul i32 %3, %4
%6 = load i32, i32* %y
%7 = mul i32 %5, %6
%8 = load i32, i32* %y
%9 = mul i32 %7, %8
%z = alloca i32
store i32 %9, i32* %z
%10 = load i32, i32* %z
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %10)
%12 = load i32, i32* %x
%13 = load i32, i32* %x
%14 = xor i32 %12, %13
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %14)
%16 = load i32, i32* %x
%17 = load i32, i32* %x
%18 = xor i32 %16, %17
%19 = load i32, i32* %z
%20 = load i32, i32* %y
%21 = add i32 %19, %20
%22 = or i32 %18, %21
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %22)
%24 = load i32, i32* %x
%25 = load i32, i32* %x
%26 = xor i32 %24, %25
%27 = load i32, i32* %z
%28 = load i32, i32* %y
%29 = add i32 %27, %28
%30 = or i32 %26, %29
%31 = ashr i32 %30, 1
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %31)
%33 = load i32, i32* %x
%34 = load i32, i32* %x
%35 = xor i32 %33, %34
%36 = load i32, i32* %z
%37 = load i32, i32* %y
%38 = add i32 %36, %37
%39 = or i32 %35, %38
%40 = ashr i32 %39, 1
%41 = shl i32 %40, 1
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %41)
ret i32 0
}