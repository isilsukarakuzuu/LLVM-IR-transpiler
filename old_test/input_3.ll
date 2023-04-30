; ModuleID = 'advcalc2ir'
declare i32 @printf(i8*, ...)
@print.str = constant [4 x i8] c"%d\0A\00"

define i32 @main() {
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 8)
%2 = mul i32 8, 2
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %2)
%4 = mul i32 88, 2
%5 = add i32 %4, 6
%6 = shl i32 %5, 2
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %6)
%8 = sub i32 9, 3
%9 = sub i32 17, 6
%10 = xor i32 %8, %9
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %10)
%12 = sub i32 23, 0
%13 = mul i32 10, %12
%14 = mul i32 %13, 0
%15 = sub i32 %14, 1
%16 = xor i32 %15, -1
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %16)
%18 = or i32 2, 4
%19 = sub i32 32, %18
%20 = shl i32 10, %18
%21 = lshr i32 10, %19
%22 = or i32 %20, %21
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %22)
%24 = and i32 1, 3
%25 = sub i32 32, %24
%26 = lshr i32 17, %24
%27 = shl i32 17, %25
%28 = or i32 %26, %27
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %28)
%30 = add i32 12, 3
%31 = shl i32 8, %30
%32 = sub i32 3, 10
%33 = xor i32 %32, -1
%34 = xor i32 %31, %33
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %34)
%36 = sub i32 32, 2
%37 = shl i32 10, 2
%38 = lshr i32 10, %36
%39 = or i32 %37, %38
%40 = sub i32 32, 1
%41 = lshr i32 17, 1
%42 = shl i32 17, %40
%43 = or i32 %41, %42
%44 = xor i32 %39, %43
%45 = xor i32 %44, 0
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %45)
%47 = sub i32 32, 2
%48 = shl i32 10, 2
%49 = lshr i32 10, %47
%50 = or i32 %48, %49
%51 = sub i32 32, 1
%52 = lshr i32 17, 1
%53 = shl i32 17, %51
%54 = or i32 %52, %53
%55 = xor i32 %50, %54
%56 = xor i32 %55, -1
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %56)
ret i32 0
}