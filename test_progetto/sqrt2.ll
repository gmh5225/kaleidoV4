define double @iterate(double %y, double %x) {
entry:
  %z = alloca double, align 8
  %eps = alloca double, align 8
  %x2 = alloca double, align 8
  %y1 = alloca double, align 8
  store double %y, ptr %y1, align 8
  store double %x, ptr %x2, align 8
  store double 1.000000e-04, ptr %eps, align 8
  br label %init

init:                                             ; preds = %entry
  %x3 = load double, ptr %x2, align 8
  %x4 = load double, ptr %x2, align 8
  %mulres = fmul double %x3, %x4
  store double %mulres, ptr %z, align 8
  br label %cond

cond:                                             ; preds = %loop, %init
  %eps5 = load double, ptr %eps, align 8
  %z6 = load double, ptr %z, align 8
  %y7 = load double, ptr %y1, align 8
  %subres = fsub double %z6, %y7
  %ltres = fcmp ult double %eps5, %subres
  %eps8 = load double, ptr %eps, align 8
  %y9 = load double, ptr %y1, align 8
  %z10 = load double, ptr %z, align 8
  %subres11 = fsub double %y9, %z10
  %ltres12 = fcmp ult double %eps8, %subres11
  %orres = or i1 %ltres, %ltres12
  br i1 %orres, label %loop, label %afterLoop

loop:                                             ; preds = %cond
  %x13 = load double, ptr %x2, align 8
  %x14 = load double, ptr %x2, align 8
  %mulres15 = fmul double %x13, %x14
  store double %mulres15, ptr %z, align 8
  %x16 = load double, ptr %x2, align 8
  %y17 = load double, ptr %y1, align 8
  %x18 = load double, ptr %x2, align 8
  %addres = fdiv double %y17, %x18
  %addres19 = fadd double %x16, %addres
  %addres20 = fdiv double %addres19, 2.000000e+00
  store double %addres20, ptr %x2, align 8
  br label %cond

afterLoop:                                        ; preds = %cond
  %0 = phi double [ 0.000000e+00, %cond ]
  %x21 = load double, ptr %x2, align 8
  ret double %x21
}

define double @sqrt(double %y) {
entry:
  %y1 = alloca double, align 8
  store double %y, ptr %y1, align 8
  %y2 = load double, ptr %y1, align 8
  %eqres = fcmp ueq double %y2, 1.000000e+00
  br i1 %eqres, label %trueBlock, label %falseBlock

trueBlock:                                        ; preds = %entry
  br label %mergeblock11

falseBlock:                                       ; preds = %entry
  %y3 = load double, ptr %y1, align 8
  %ltres = fcmp ult double %y3, 1.000000e+00
  br i1 %ltres, label %trueBlock4, label %falseBlock7

trueBlock4:                                       ; preds = %falseBlock
  %y5 = load double, ptr %y1, align 8
  %y6 = load double, ptr %y1, align 8
  %subres = fsub double 1.000000e+00, %y6
  %calltmp = call double @iterate(double %y5, double %subres)
  br label %mergeblock

falseBlock7:                                      ; preds = %falseBlock
  %y8 = load double, ptr %y1, align 8
  %y9 = load double, ptr %y1, align 8
  %addres = fdiv double %y9, 2.000000e+00
  %calltmp10 = call double @iterate(double %y8, double %addres)
  br label %mergeblock

mergeblock:                                       ; preds = %falseBlock7, %trueBlock4
  %0 = phi double [ %calltmp, %trueBlock4 ], [ %calltmp10, %falseBlock7 ]
  br label %mergeblock11

mergeblock11:                                     ; preds = %mergeblock, %trueBlock
  %1 = phi double [ 1.000000e+00, %trueBlock ], [ %0, %mergeblock ]
  ret double %1
}

