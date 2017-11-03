.module spriteList

.area _DATA

.area _CODE

.globl _spriteList
.globl _eraseEntity
.globl _drawEntity
.globl _entityUpdate
.globl _print_sprites
.globl cpct_waitVSYNC_asm


;;
;;  print_sprites: Print all the active sprites in the Sprite List.
;;
;;  input:

;;  output:

;;  destroys: A, HL, BC, DE
;;

_print_sprites::
                            ;;
                            ;; First Loop erase Sprites
							;;
	ld hl, #_spriteList
    ld a, (hl)
	or a, a
	ret	Z        			;;
    ld b,a                  ;; if so, load the number of sprites in B
    push bc
loop1_sl_ps:
	inc hl
    ld e, (hl)            ;; check the address of the first sprite in HL
	inc hl
	ld d, (hl)            ;; check the address of the first sprite in HL
	push hl
	ex de, hl
	push bc
	ld bc, #15
	add hl, bc
	ld a, (hl)           ;; check if "draw" value
	or a
	jr z, next1_sl_ps        ;; if draw = 0 skip the sprite
	sbc hl, bc
	push hl
	call _eraseEntity
	pop hl
next1_sl_ps:
	pop bc
	pop hl
	djnz loop1_sl_ps        ;; if there are still some sprites to print get back to loop
                            ;;
                            ;; Second Loop draw Sprites
                            ;;
    ld hl, #0               ;; move the value of bc store in teh stack to bc passing by HL
	add	hl,sp
	inc hl
    ld b, (hl)
	ld hl, #_spriteList
loop2_sl_ps:
	inc hl
    ld e, (hl)            ;; check the address of the first sprite in HL
	inc hl
	ld d, (hl)            ;; check the address of the first sprite in HL
	push hl
	ex de, hl
	push bc
	ld bc, #15
	add hl, bc
	ld a, (hl)           ;; check if "draw" value
	or a
	jr z, next2_s1_ps        ;; if draw = 0 skip the sprite
	sbc hl, bc
	push hl
	call _drawEntity
	pop hl
next2_s1_ps:
	pop bc
	pop hl
	djnz loop2_sl_ps        ;; if there are still some sprites to print get back to loop
                            ;;
                            ;; Third Loop update Sprites
                            ;;
    ld hl, #0               ;; move the value of bc store in teh stack to bc passing by HL
	add	hl,sp
	inc hl
    ld b, (hl)
	ld hl, #_spriteList
loop3_sl_ps:
	inc hl
    ld e, (hl)            ;; check the address of the first sprite in HL
	inc hl
	ld d, (hl)            ;; check the address of the first sprite in HL
	push hl
	ex de, hl
	push bc
	ld bc, #15
	add hl, bc
	ld a, (hl)           ;; check if "draw" value
	or a
	jr z, next3_sl_ps        ;; if draw = 0 skip the sprite
	sbc hl, bc
	push hl
	call _entityUpdate
	pop hl
next3_sl_ps:
	pop bc
	pop hl
	djnz loop3_sl_ps        ;; if there are still some sprites to print get back to loop
                            ;;
                            ;; End of routine
                            ;;
exit_sl_ps:
    pop bc
    ret