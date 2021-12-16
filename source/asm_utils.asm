section .text
    global getStack
    global getCoords

;; Pops and returns the stack
getStack:
    pop rax
    ret

;; RDI - grid width (modulo)
;; RSI - grid height (floor division)
getCoords:
    mov rdx, 0
    mov rax, rdi
    mov rcx, rsi
    div rcx

    push rax
    push rdx

    ret
