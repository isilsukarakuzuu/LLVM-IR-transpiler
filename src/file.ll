; ModuleID = 'advcalc2ir'
declare i32 @printf(i8*, ...)
@print.str = constant [4 x i8] c"%d\0A\00"

define i32 @main() {
%x = alloca i32
store i32 3, i32* %x
%y = alloca i32
store i32 5, i32* %y
%10000 = load i32, i32* %y
%10001 = add i32 1, %10000
%10002 = load i32, i32* %x
%10003 = mul i32 %10002, %10001
%10004 = add i32 23, %10003
%zvalue = alloca i32
store i32 %10004, i32* %zvalue
%10005 = load i32, i32* %zvalue
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %10005)
%10006 = load i32, i32* %x
%10007 = load i32, i32* %y
%10008 = load i32, i32* %zvalue
%10009 = sub i32 %10007, %10008
%10010 = sub i32 %10006, %10009
%k = alloca i32
store i32 %10010, i32* %k
%10011 = add i32 2, 5
%10012 = mul i32 1, %10011
%10013 = load i32, i32* %x
%10014 = load i32, i32* %y
%10015 = mul i32 %10014, %10012
%10016 = mul i32 3, %10015
%10017 = add i32 %10013, %10016
store i32 %10017, i32* %k
%10018 = load i32, i32* %k
%10019 = add i32 %10018, 1
call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @print.str, i32 0, i32 0), i32 %10019)
}