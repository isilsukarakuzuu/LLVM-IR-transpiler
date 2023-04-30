; ModuleID = 'advcalc2ir'
declare i32 @printf(i8*, ...)
@print.str = constant [4 x i8] c"%d\0A\00"

define i32 @main() {
%a = alloca i32
store i32 3, i32* %a
%1 = load i32, i32* %a
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %1)
%3 = add i32 5, 8
%b = alloca i32
store i32 %3, i32* %b
%4 = load i32, i32* %b
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %4)
%6 = sub i32 9, 5
%c = alloca i32
store i32 %6, i32* %c
%7 = load i32, i32* %c
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %7)
%9 = mul i32 2, 33
%10 = load i32, i32* %a
%11 = mul i32 %9, %10
%12 = mul i32 %11, 21
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %12)
%14 = load i32, i32* %b
%15 = sub i32 %14, 5
%16 = load i32, i32* %a
%17 = and i32 %16, %15
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %17)
%19 = load i32, i32* %c
%20 = add i32 %19, 5
%21 = load i32, i32* %a
%22 = and i32 %21, %20
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %22)
%24 = load i32, i32* %a
%25 = load i32, i32* %c
%26 = add i32 %25, 5
%27 = or i32 %24, %26
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %27)
%29 = load i32, i32* %a
%30 = load i32, i32* %c
%31 = add i32 %30, 5
%32 = sub i32 %31, 1
%33 = or i32 %29, %32
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %33)
%35 = load i32, i32* %b
%36 = sub i32 %35, 5
store i32 %36, i32* %b
%37 = load i32, i32* %a
%38 = add i32 %37, 5
store i32 %38, i32* %a
%39 = load i32, i32* %a
%40 = load i32, i32* %b
%41 = add i32 %39, %40
store i32 %41, i32* %c
%42 = load i32, i32* %b
%43 = load i32, i32* %b
%44 = mul i32 %42, %43
%45 = load i32, i32* %c
%46 = sub i32 %45, 13
%47 = load i32, i32* %a
%48 = load i32, i32* %b
%49 = sub i32 %47, %48
%50 = add i32 %49, 5
%51 = load i32, i32* %a
%52 = mul i32 %51, %44
%53 = mul i32 %46, %50
%54 = sub i32 %52, %53
%55 = load i32, i32* %c
%56 = mul i32 2, %55
%57 = add i32 %54, %56
%58 = sub i32 %57, 1
%59 = add i32 %58, 1
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %59)
%iki = alloca i32
store i32 2, i32* %iki
%gercekteniki = alloca i32
store i32 2, i32* %gercekteniki
%uc = alloca i32
store i32 3, i32* %uc
%61 = load i32, i32* %gercekteniki
%62 = load i32, i32* %gercekteniki
%63 = and i32 %61, %62
%64 = load i32, i32* %gercekteniki
%65 = load i32, i32* %gercekteniki
%66 = and i32 %64, %65
%67 = or i32 %63, %66
%68 = load i32, i32* %gercekteniki
%69 = or i32 %67, %68
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %69)
%71 = load i32, i32* %uc
%72 = load i32, i32* %gercekteniki
%73 = sub i32 %71, %72
%74 = load i32, i32* %uc
%75 = load i32, i32* %gercekteniki
%76 = mul i32 %74, %75
%77 = load i32, i32* %gercekteniki
%78 = load i32, i32* %gercekteniki
%79 = mul i32 %77, %78
%80 = load i32, i32* %uc
%81 = load i32, i32* %gercekteniki
%82 = load i32, i32* %gercekteniki
%83 = mul i32 %81, %82
%84 = load i32, i32* %uc
%85 = mul i32 %83, %84
%86 = add i32 %80, %85
%87 = load i32, i32* %gercekteniki
%88 = mul i32 2, %87
%89 = load i32, i32* %uc
%90 = mul i32 %88, %89
%91 = load i32, i32* %uc
%92 = mul i32 %90, %91
%93 = sub i32 %92, %73
%94 = mul i32 %79, 0
%95 = sub i32 %76, %94
%96 = load i32, i32* %gercekteniki
%97 = sub i32 %95, %96
%98 = load i32, i32* %gercekteniki
%99 = sub i32 %97, %98
%100 = load i32, i32* %gercekteniki
%101 = sub i32 %99, %100
%102 = load i32, i32* %gercekteniki
%103 = sub i32 %101, %102
%104 = and i32 %93, %103
%105 = or i32 %86, %104
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %105)
ret i32 0
}