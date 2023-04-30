; ModuleID = 'advcalc2ir'
declare i32 @printf(i8*, ...)
@print.str = constant [4 x i8] c"%d\0A\00"

define i32 @main() {
%x = alloca i32
store i32 3, i32* %x
%y = alloca i32
store i32 5, i32* %y
%1 = load i32, i32* %y
%2 = add i32 1, %1
%3 = load i32, i32* %x
%4 = mul i32 %3, %2
%5 = add i32 23, %4
%zvalue = alloca i32
store i32 %5, i32* %zvalue
%6 = load i32, i32* %zvalue
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %6)
%8 = load i32, i32* %x
%9 = load i32, i32* %y
%10 = sub i32 %8, %9
%11 = load i32, i32* %zvalue
%12 = sub i32 %10, %11
%k = alloca i32
store i32 %12, i32* %k
%13 = add i32 2, 5
%14 = mul i32 1, %13
%15 = load i32, i32* %x
%16 = load i32, i32* %y
%17 = mul i32 3, %16
%18 = mul i32 %17, %14
%19 = add i32 %15, %18
store i32 %19, i32* %k
%20 = load i32, i32* %k
%21 = add i32 %20, 1
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %21)
ret i32 0
}