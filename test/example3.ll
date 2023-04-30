; ModuleID = 'advcalc2ir'
declare i32 @printf(i8*, ...)
@print.str = constant [4 x i8] c"%d\0A\00"

define i32 @main() {
%a = alloca i32
store i32 8, i32* %a
%1 = load i32, i32* %a
%2 = sub i32 %1, 6
%3 = mul i32 8, %2
%b = alloca i32
store i32 %3, i32* %b
%4 = load i32, i32* %b
%5 = add i32 %4, 6
%c = alloca i32
store i32 %5, i32* %c
%6 = load i32, i32* %a
%7 = shl i32 %6, 2
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %7)
%9 = load i32, i32* %b
%10 = load i32, i32* %a
%11 = sub i32 %9, %10
%12 = add i32 %11, 1
%13 = xor i32 %12, 17
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %13)
%15 = load i32, i32* %b
%16 = mul i32 2, %15
%17 = load i32, i32* %c
%18 = sub i32 %16, %17
%y = alloca i32
store i32 %18, i32* %y
%19 = load i32, i32* %y
%20 = ashr i32 %19, 2
%21 = load i32, i32* %c
%22 = xor i32 %21, -1
%23 = xor i32 %20, %22
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %23)
ret i32 0
}