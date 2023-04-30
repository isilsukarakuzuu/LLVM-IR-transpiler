; ModuleID = 'advcalc2ir'
declare i32 @printf(i8*, ...)
@print.str = constant [4 x i8] c"%d\0A\00"

define i32 @main() {
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 8)
%2 = mul i32 8, 2
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %2)
%4 = mul i32 8, 2
%5 = add i32 %4, 6
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %5)
%7 = shl i32 8, 2
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %7)
%9 = xor i32 9, 17
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %9)
%11 = xor i32 10, -1
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %11)
%13 = sub i32 32, 2
%14 = shl i32 10, 2
%15 = lshr i32 10, %13
%16 = or i32 %14, %15
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %16)
%18 = sub i32 32, 1
%19 = lshr i32 16, 1
%20 = shl i32 16, %18
%21 = or i32 %19, %20
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %21)
%23 = shl i32 8, 2
%24 = xor i32 10, -1
%25 = xor i32 %23, %24
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %25)
%27 = sub i32 32, 2
%28 = shl i32 10, 2
%29 = lshr i32 10, %27
%30 = or i32 %28, %29
%31 = sub i32 32, 1
%32 = lshr i32 16, 1
%33 = shl i32 16, %31
%34 = or i32 %32, %33
%35 = xor i32 %30, %34
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %35)
%37 = sub i32 32, 2
%38 = shl i32 10, 2
%39 = lshr i32 10, %37
%40 = or i32 %38, %39
%41 = sub i32 32, 1
%42 = lshr i32 16, 1
%43 = shl i32 16, %41
%44 = or i32 %42, %43
%45 = xor i32 %40, %44
%46 = xor i32 %45, -1
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %46)
ret i32 0
}