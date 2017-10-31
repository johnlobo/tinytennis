.module spriteList

.area _DATA

.area _CODE

.globl _spriteList
.globl _eraseEntity
.globl _drawEntity
.globl _entityUpdate
.globl _print_sprites


;;
;;  print_sprites: Print all the active sprites in the Sprite List.
;;
;;  input:

;;  output:

;;  destroys: A, HL, BC, DE
;;

_print_sprites::
    push ix                 ;;Keep registers
    push hl
    push bc 
                            ;;
                            ;; First Loop erase Sprites
                            ;;
    ld ix, #_spriteList     ;; load sprite list address in IX
    ld a, 0 (ix)            ;; check if the number of sprites is greater than one
    or a    
    jr z, exit_sl_ps
    ld b,a                  ;; if so, load the number of sprites in B
    push bc
loop1_sl_ps:
    ld l, 1 (ix)            ;; check the address of the first sprite in HL
    ld h, 2 (ix)            ;; check the address of the first sprite in HL
    push ix                 ;; saves IX
    push hl                 ;; loads the adress for the first sprite in IX
    pop ix
    ld a, 15 (ix)           ;; check if "draw" value
    or a
    jr z, next1_sl_ps        ;; if draw = 0 skip the sprite
    push bc
    push hl
    call	_eraseEntity
    pop hl
    pop bc
next1_sl_ps:
    pop ix                  ;; restore in ix the position in the spreite list
    inc ix
    inc ix                  ;; jumps to the next item in the list
    djnz loop1_sl_ps        ;; if there are still some sprites to print get back to loop
                            ;;
                            ;; Second Loop draw Sprites
                            ;;
    ld ix, #0               ;; move the value of bc store in teh stack to bc passing by IX
	  add	ix,sp
    ld b, 1 (ix)
     ld ix, #_spriteList     ;; load sprite list address in IX
loop2_sl_ps:
    ld l, 1 (ix)            ;; check the address of the first sprite in HL
    ld h, 2 (ix)            ;; check the address of the first sprite in HL
    push ix                 ;; saves IX
    push hl                 ;; loads the adress for the first sprite in IX
    pop ix
    ld a, 15 (ix)           ;; check if "draw" value
    or a
    jr z, next2_sl_ps        ;; if draw = 0 skip the sprite
    push bc
    push hl
    call	_drawEntity
    pop hl
    pop bc
next2_sl_ps:
    pop ix                  ;; restore in ix the position in the spreite list
    inc ix
    inc ix                  ;; jumps to the next item in the list
    djnz loop2_sl_ps
                            ;;
                            ;; Third Loop update Sprites
                            ;;
    ld ix, #0               ;; move the value of bc store in teh stack to bc passing by IX
	  add	ix,sp
    ld b, 1 (ix)
     ld ix, #_spriteList     ;; load sprite list address in IX
loop3_sl_ps:
    ld l, 1 (ix)            ;; check the address of the first sprite in HL
    ld h, 2 (ix)            ;; check the address of the first sprite in HL
    push ix                 ;; saves IX
    push hl                 ;; loads the adress for the first sprite in IX
    pop ix
    ld a, 15 (ix)           ;; check if "draw" value
    or a
    jr z, next3_sl_ps        ;; if draw = 0 skip the sprite
    push bc
    push hl
    call _entityUpdate
    pop hl
    pop bc
next3_sl_ps:
    pop ix                  ;; restore in ix the position in the spreite list
    inc ix
    inc ix                  ;; jumps to the next item in the list
    djnz loop3_sl_ps
                            ;;
                            ;; End of routine
                            ;;
                            ;;
                            ;; End of routine
                            ;;
    exit_sl_ps:
    pop bc
    pop bc
    pop hl
    pop ix
    ret