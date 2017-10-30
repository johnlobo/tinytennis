.module spriteList

.area _DATA

.area _CODE

.globl _spriteList
.globl _eraseEntity

;;
;;  print_sprites: Print all the active sprites in the Sprite List.
;;
;;  input:

;;  output:

;;  destroys: A, HL, B, DE
;;

.globl _print_sprites
_print_sprites::
    push ix                 ;;Keep registers
    push hl
    push bc
    ld ix, #_spriteList     ;; load sprite list address in IX
    ld a, 0 (ix)            ;; check if the number of sprites is greater than one
    or a    
    jr z, exit_sl_ps
    ld b,a                  ;; if so, load the number of sprites in B
loop_sl_ps:
    ld l, 1 (ix)            ;; check the address of the first sprite in HL
    ld h, 2 (ix)            ;; check the address of the first sprite in HL
    push ix                 ;; saves IX
    push hl                 ;; loads the adress for the first sprite in IX
    pop ix
    ld a, 15 (ix)           ;; check if "draw" value
    or a
    jr z, next_sl_ps        ;; if draw = 0 skip the sprite
    push bc
    call	_eraseEntity
    pop bc
next_sl_ps:
    pop ix                  ;; restore in ix the position in the spreite list
    inc ix
    inc ix                  ;; jumps to the next item in the list
    djnz loop_sl_ps         ;; if there are still some sprites to print get back to loop
exit_sl_ps:
    pop bc
    pop hl
    pop ix
    ret