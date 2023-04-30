; ModuleID = 'advcalc2ir'
declare i32 @printf(i8*, ...)
@print.str = constant [4 x i8] c"%d\0A\00"

define i32 @main() {
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 3)
%2 = add i32 5, 8
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %2)
%4 = sub i32 9, 5
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %4)
%6 = mul i32 2, 99
%7 = mul i32 %6, 21
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %7)
%9 = and i32 3, 8
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %9)
%11 = and i32 3, 9
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %11)
%13 = or i32 3, 9
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %13)
%15 = or i32 3, 8
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %15)
%17 = mul i32 8, 8
%18 = mul i32 8, %17
%19 = mul i32 3, 5
%20 = sub i32 %18, %19
%21 = add i32 %20, 32
%22 = sub i32 %21, 1
%23 = add i32 %22, 1
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %23)
%25 = and i32 2, 2
%26 = and i32 2, 2
%27 = or i32 %25, %26
%28 = or i32 %27, 2
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %28)
%30 = mul i32 4, 3
%31 = add i32 3, %30
%32 = mul i32 4, 9
%33 = sub i32 %32, 1
%34 = mul i32 4, 0
%35 = sub i32 6, %34
%36 = sub i32 %35, 2
%37 = sub i32 %36, 2
%38 = sub i32 %37, 2
%39 = sub i32 %38, 2
%40 = and i32 %33, %39
%41 = or i32 %31, %40
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %41)
ret i32 0
}