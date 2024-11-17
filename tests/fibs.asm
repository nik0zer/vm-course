                        ; n in v1
mv.i64 v0, 0            ; F(0) = 0
mv.i64 v2, 1            ; F(1) = 1
mv.i64 v3, 1            ; i = 1

loop_start:
cmpgt.i64 v1, v3        ; i < n ?
cjmpf end_loop          ; if(!acc) pc = address(end_loop)

add.i64 v0, v0, v2      ; F(i) = F(i-1) + F(i-2)
mv.i64 v2, v0
add.i64 v3, v3, 1       ; i++
jmp loop_start          ; pc = address(loop_start)

end_loop:
; result in v0