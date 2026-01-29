; ModuleID = 'TestAlgebraic.c'
source_filename = "TestAlgebraic.c"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"
target triple = "arm64-apple-macosx15.0.0"

; Function Attrs: noinline nounwind optnone ssp uwtable(sync)
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  store i32 5, ptr %2, align 4
  %8 = load i32, ptr %2, align 4
  %9 = add nsw i32 %8, 0
  store i32 %9, ptr %3, align 4
  %10 = load i32, ptr %3, align 4
  %11 = mul nsw i32 %10, 9
  store i32 %11, ptr %4, align 4
  %12 = load i32, ptr %3, align 4
  %13 = mul nsw i32 %12, 7
  store i32 %13, ptr %5, align 4
  %14 = load i32, ptr %3, align 4
  %15 = mul nsw i32 %14, 8
  store i32 %15, ptr %6, align 4
  %16 = load i32, ptr %3, align 4
  %17 = sdiv i32 %16, 3
  store i32 %17, ptr %7, align 4
  ret i32 0
}

attributes #0 = { noinline nounwind optnone ssp uwtable(sync) "frame-pointer"="non-leaf" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-m1" "target-features"="+aes,+crc,+dotprod,+fp-armv8,+fp16fml,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+sha3,+v8.1a,+v8.2a,+v8.3a,+v8.4a,+v8.5a,+v8a,+zcm,+zcz" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 15, i32 2]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{i32 7, !"frame-pointer", i32 1}
!5 = !{!"Apple clang version 16.0.0 (clang-1600.0.26.6)"}
