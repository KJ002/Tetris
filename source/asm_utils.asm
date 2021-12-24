section .text

global getCoords

;; RDI - value
;; RSI - divisor
;; RDX (modulo)
;; RAX (floor division)
;;
;; 32bit values for modulo and division are calculated
;; rax register (division) is shifted by 32bits to the left
;; and then is or'ed into the rdx register which holds the
;; modulo
;;
getCoords:
    mov eax, edi
    cdq
    idiv esi
    sal rax, 32
    or rax, rdx
    ret
