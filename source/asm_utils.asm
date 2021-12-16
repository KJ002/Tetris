section .text
    global getStack
    global getCoords

;; Pops and returns the stack
getStack:
    pop rax
    ret

;; RDI - value
;; RSI - divisor
;; Values are pushed onto stack
;; rdx (modulo) is pushed first then
;; rax (floor division) is pushed second
getCoords:
    mov rdx, 0
    mov rax, rdi
    mov rcx, rsi
    div rcx

    push rdx
    push rax

    ret
