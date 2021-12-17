section .text

global getCoords

;; RDI - value
;; RSI - divisor
;; Values are pushed onto stack
;; rdx (modulo) is pushed first then
;; rax (floor division) is pushed second
getCoords:
    mov eax, edi
    cdq
    idiv esi
    sal rax, 32
    or rax, rdx
    ret
