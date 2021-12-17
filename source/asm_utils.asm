section .text

global getCoords

;; RDI - value
;; RSI - divisor
;; rdx (modulo)
;; rax (floor division)
getCoords:
    mov eax, edi
    cdq
    idiv esi
    sal rax, 32
    or rax, rdx
    ret
