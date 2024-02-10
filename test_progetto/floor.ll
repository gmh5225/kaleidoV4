define double @pow2(double %x, double %i) {
entry:
  %i2 = alloca double, align 8
  %x1 = alloca double, align 8
  store double %x, ptr %x1, align 8
  store double %i, ptr %i2, align 8
  %x3 = load double, ptr %x1, align 8
  %i4 = load double, ptr %i2, align 8
  %mulres = fmul double 2.000000e+00, %i4
  %ltres = fcmp ult double %x3, %mulres
  br i1 %ltres, label %trueBlock, label %falseBlock

trueBlock:                                        ; preds = %entry
  %i5 = load double, ptr %i2, align 8
  br label %mergeblock

falseBlock:                                       ; preds = %entry
  %x6 = load double, ptr %x1, align 8
  %i7 = load double, ptr %i2, align 8
  %mulres8 = fmul double 2.000000e+00, %i7
  %calltmp = call double @pow2(double %x6, double %mulres8)
  br label %mergeblock

mergeblock:                                       ; preds = %falseBlock, %trueBlock
  %0 = phi double [ %i5, %trueBlock ], [ %calltmp, %falseBlock ]
  ret double %0
}

define double @intpart(double %x, double %acc) {
entry:
  %y = alloca double, align 8
  %acc2 = alloca double, align 8
  %x1 = alloca double, align 8
  store double %x, ptr %x1, align 8
  store double %acc, ptr %acc2, align 8
  %x3 = load double, ptr %x1, align 8
  %ltres = fcmp ult double %x3, 1.000000e+00
  br i1 %ltres, label %trueBlock, label %falseBlock

trueBlock:                                        ; preds = %entry
  br label %mergeblock

falseBlock:                                       ; preds = %entry
  %x4 = load double, ptr %x1, align 8
  %calltmp = call double @pow2(double %x4, double 1.000000e+00)
  br label %mergeblock

mergeblock:                                       ; preds = %falseBlock, %trueBlock
  %0 = phi double [ 0.000000e+00, %trueBlock ], [ %calltmp, %falseBlock ]
  store double %0, ptr %y, align 8
  %y5 = load double, ptr %y, align 8
  %eqres = fcmp ueq double %y5, 0.000000e+00
  br i1 %eqres, label %trueBlock6, label %falseBlock8

trueBlock6:                                       ; preds = %mergeblock
  %acc7 = load double, ptr %acc2, align 8
  br label %mergeblock14

falseBlock8:                                      ; preds = %mergeblock
  %x9 = load double, ptr %x1, align 8
  %y10 = load double, ptr %y, align 8
  %subres = fsub double %x9, %y10
  %acc11 = load double, ptr %acc2, align 8
  %y12 = load double, ptr %y, align 8
  %addres = fadd double %acc11, %y12
  %calltmp13 = call double @intpart(double %subres, double %addres)
  br label %mergeblock14

mergeblock14:                                     ; preds = %falseBlock8, %trueBlock6
  %1 = phi double [ %acc7, %trueBlock6 ], [ %calltmp13, %falseBlock8 ]
  ret double %1
}

define double @floor(double %x) {
entry:
  %x1 = alloca double, align 8
  store double %x, ptr %x1, align 8
  %x2 = load double, ptr %x1, align 8
  %calltmp = call double @intpart(double %x2, double 0.000000e+00)
  ret double %calltmp
}

