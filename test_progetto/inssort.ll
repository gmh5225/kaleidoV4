declare double @randinit(double)

declare double @randk()

declare double @timek()

declare double @printval(double, double)

@A = global [10 x double] zeroinitializer
define double @inssort() {
entry:
  %j = alloca double, align 8
  %step = alloca double, align 8
  %pivot = alloca double, align 8
  %i = alloca double, align 8
  br label %init

init:                                             ; preds = %entry
  store double 1.000000e+00, ptr %i, align 8
  br label %cond

cond:                                             ; preds = %mergeblock27, %init
  %i1 = load double, ptr %i, align 8
  %ltres = fcmp ult double %i1, 1.000000e+01
  br i1 %ltres, label %loop, label %afterLoop

loop:                                             ; preds = %cond
  %i2 = load double, ptr %i, align 8
  %0 = fptrunc double %i2 to float
  %1 = fptosi float %0 to i32
  %2 = getelementptr inbounds [10 x double], ptr @A, i32 %1
  %A = load double, ptr %2, align 8
  store double %A, ptr %pivot, align 8
  store double 1.000000e+00, ptr %step, align 8
  br label %init3

afterLoop:                                        ; preds = %cond
  %3 = phi double [ 0.000000e+00, %cond ]
  ret double %3

init3:                                            ; preds = %loop
  %i7 = load double, ptr %i, align 8
  %subres = fsub double %i7, 1.000000e+00
  store double %subres, ptr %j, align 8
  br label %cond4

cond4:                                            ; preds = %mergeblock, %init3
  %j8 = load double, ptr %j, align 8
  %ltres9 = fcmp ult double -1.000000e+00, %j8
  br i1 %ltres9, label %loop5, label %afterLoop6

loop5:                                            ; preds = %cond4
  %pivot10 = load double, ptr %pivot, align 8
  %j11 = load double, ptr %j, align 8
  %4 = fptrunc double %j11 to float
  %5 = fptosi float %4 to i32
  %6 = getelementptr inbounds [10 x double], ptr @A, i32 %5
  %A12 = load double, ptr %6, align 8
  %ltres13 = fcmp ult double %pivot10, %A12
  br i1 %ltres13, label %trueBlock, label %falseBlock

afterLoop6:                                       ; preds = %cond4
  %7 = phi double [ 0.000000e+00, %cond4 ]
  %step23 = load double, ptr %step, align 8
  %eqres = fcmp ueq double %step23, 1.000000e+00
  br i1 %eqres, label %trueBlock24, label %falseBlock26

trueBlock:                                        ; preds = %loop5
  %j14 = load double, ptr %j, align 8
  %8 = fptrunc double %j14 to float
  %9 = fptosi float %8 to i32
  %10 = getelementptr inbounds [10 x double], ptr @A, i32 %9
  %A15 = load double, ptr %10, align 8
  %j16 = load double, ptr %j, align 8
  %addres = fadd double %j16, 1.000000e+00
  %11 = fptrunc double %addres to float
  %12 = fptosi float %11 to i32
  %13 = getelementptr inbounds [10 x double], ptr @A, i32 %12
  store double %A15, ptr %13, align 8
  br label %mergeblock

falseBlock:                                       ; preds = %loop5
  %pivot17 = load double, ptr %pivot, align 8
  %j18 = load double, ptr %j, align 8
  %addres19 = fadd double %j18, 1.000000e+00
  %14 = fptrunc double %addres19 to float
  %15 = fptosi float %14 to i32
  %16 = getelementptr inbounds [10 x double], ptr @A, i32 %15
  store double %pivot17, ptr %16, align 8
  store double 1.000000e+01, ptr %step, align 8
  br label %mergeblock

mergeblock:                                       ; preds = %falseBlock, %trueBlock
  %17 = phi double [ 0.000000e+00, %trueBlock ], [ 0.000000e+00, %falseBlock ]
  %j20 = load double, ptr %j, align 8
  %step21 = load double, ptr %step, align 8
  %subres22 = fsub double %j20, %step21
  store double %subres22, ptr %j, align 8
  br label %cond4

trueBlock24:                                      ; preds = %afterLoop6
  %pivot25 = load double, ptr %pivot, align 8
  store double %pivot25, ptr @A, align 8
  br label %mergeblock27

falseBlock26:                                     ; preds = %afterLoop6
  br label %mergeblock27

mergeblock27:                                     ; preds = %falseBlock26, %trueBlock24
  %18 = phi double [ 0.000000e+00, %trueBlock24 ], [ 0.000000e+00, %falseBlock26 ]
  %i28 = load double, ptr %i, align 8
  %addres29 = fadd double %i28, 1.000000e+00
  store double %addres29, ptr %i, align 8
  br label %cond
}

define double @main() {
entry:
  %i15 = alloca double, align 8
  %i = alloca double, align 8
  %seed = alloca double, align 8
  %calltmp = call double @timek()
  store double %calltmp, ptr %seed, align 8
  %seed1 = load double, ptr %seed, align 8
  %calltmp2 = call double @randinit(double %seed1)
  br label %init

init:                                             ; preds = %entry
  store double 0.000000e+00, ptr %i, align 8
  br label %cond

cond:                                             ; preds = %loop, %init
  %i3 = load double, ptr %i, align 8
  %ltres = fcmp ult double %i3, 1.000000e+01
  br i1 %ltres, label %loop, label %afterLoop

loop:                                             ; preds = %cond
  %calltmp4 = call double @randk()
  %i5 = load double, ptr %i, align 8
  %0 = fptrunc double %i5 to float
  %1 = fptosi float %0 to i32
  %2 = getelementptr inbounds [10 x double], ptr @A, i32 %1
  store double %calltmp4, ptr %2, align 8
  %i6 = load double, ptr %i, align 8
  %3 = fptrunc double %i6 to float
  %4 = fptosi float %3 to i32
  %5 = getelementptr inbounds [10 x double], ptr @A, i32 %4
  %A = load double, ptr %5, align 8
  %calltmp7 = call double @printval(double %A, double 0.000000e+00)
  %i8 = load double, ptr %i, align 8
  %addres = fadd double %i8, 1.000000e+00
  store double %addres, ptr %i, align 8
  br label %cond

afterLoop:                                        ; preds = %cond
  %6 = phi double [ 0.000000e+00, %cond ]
  %calltmp9 = call double @printval(double 0.000000e+00, double 1.000000e+00)
  %calltmp10 = call double @inssort()
  br label %init11

init11:                                           ; preds = %afterLoop
  store double 0.000000e+00, ptr %i15, align 8
  br label %cond12

cond12:                                           ; preds = %loop13, %init11
  %i16 = load double, ptr %i15, align 8
  %ltres17 = fcmp ult double %i16, 1.000000e+01
  br i1 %ltres17, label %loop13, label %afterLoop14

loop13:                                           ; preds = %cond12
  %i18 = load double, ptr %i15, align 8
  %7 = fptrunc double %i18 to float
  %8 = fptosi float %7 to i32
  %9 = getelementptr inbounds [10 x double], ptr @A, i32 %8
  %A19 = load double, ptr %9, align 8
  %calltmp20 = call double @printval(double %A19, double 0.000000e+00)
  %i21 = load double, ptr %i15, align 8
  %addres22 = fadd double %i21, 1.000000e+00
  store double %addres22, ptr %i15, align 8
  br label %cond12

afterLoop14:                                      ; preds = %cond12
  %10 = phi double [ 0.000000e+00, %cond12 ]
  ret double %10
}

