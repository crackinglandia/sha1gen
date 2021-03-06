comment ~

SHA1

message digest size : 160 bits

	push	offset ptrData			;The address of the data to be hashed 
	push	nSize 				;The number of bytes of data to be hashed
	push	offset ptrBuffer		;The pointer to the buffer to receive message digest (20 bytes)
	call	SHA1

WiteG//xtreeme

~
.486

Trans_0	MACRO	argument_1 , argument_2, argument_3, argument_4, argument_5, memory_ptr

	mov	esp, argument_1
	mov	edi, dword ptr [esi]
	rol	esp , 5
	bswap	edi
	add	argument_5, esp
	mov	memory_ptr, edi
	mov	esp, argument_3
	add	esi, 4
	xor	esp, argument_4
	add	argument_5, edi
	and	esp, argument_2
	xor	esp, argument_4
	ror	argument_2, 2
	lea	argument_5, [argument_5 + esp + 05A827999h]

ENDM

Trans_1	MACRO	argument_1 , argument_2, argument_3, argument_4, argument_5, memory_ptr_1, memory_ptr_2, memory_ptr_3, memory_ptr_4
	mov	esp, argument_1
	mov	edi, memory_ptr_1
	rol	esp , 5
	xor	edi, memory_ptr_2
	add	argument_5, esp
	xor	edi, memory_ptr_3
	mov	esp, argument_3
	xor	edi, memory_ptr_4
	xor	esp, argument_4
	rol	edi, 1
	and	esp, argument_2
	mov	memory_ptr_4, edi
	xor	esp, argument_4
	add	argument_5, edi
	ror	argument_2, 2
	lea	argument_5, [argument_5 + esp + 05A827999h]

ENDM

Trans_2	MACRO	argument_1 , argument_2, argument_3, argument_4, argument_5, memory_ptr_1, memory_ptr_2, memory_ptr_3, memory_ptr_4

	mov	esp, argument_1
	mov	edi, memory_ptr_1
	rol	esp , 5
	xor	edi, memory_ptr_2
	add	argument_5, esp
	xor	edi, memory_ptr_3
	mov	esp, argument_2
	xor	edi, memory_ptr_4
	xor	esp, argument_3
	rol	edi, 1
	xor	esp, argument_4
	mov	memory_ptr_4, edi
	add	argument_5, esp
	ror	argument_2, 2
	lea	argument_5, [argument_5 + edi + 06ED9EBA1h]

ENDM

Trans_3	MACRO	argument_1 , argument_2, argument_3, argument_4, argument_5, memory_ptr_1, memory_ptr_2, memory_ptr_3, memory_ptr_4

	mov	esp, argument_1
	mov	edi, memory_ptr_1
	rol	esp , 5
	xor	edi, memory_ptr_2
	add	argument_5, esp
	xor	edi, memory_ptr_3
	mov	esp, argument_2
	xor	edi, memory_ptr_4
	or	esp, argument_3
	rol	edi, 1
	and	esp, argument_4
	mov	memory_ptr_4, edi
	add	argument_5  , edi
	mov	edi, argument_2
	and	edi, argument_3
	or	edi, esp
	ror	argument_2, 2
	lea	argument_5, [argument_5 + edi + 08F1BBCDCh]

ENDM

Trans_4	MACRO	argument_1 , argument_2, argument_3, argument_4, argument_5, memory_ptr_1, memory_ptr_2, memory_ptr_3, memory_ptr_4

	mov	esp, argument_1
	mov	edi, memory_ptr_1
	rol	esp , 5
	xor	edi, memory_ptr_2
	add	argument_5, esp
	xor	edi, memory_ptr_3
	mov	esp, argument_2
	xor	edi, memory_ptr_4
	xor	esp, argument_3
	rol	edi, 1
	xor	esp, argument_4
	mov	memory_ptr_4, edi
	add	argument_5  , esp
	ror	argument_2, 2
	lea	argument_5, [argument_5 + edi + 0CA62C1D6h]

ENDM

.data?
_temp_buffer 	db 128 dup(?)
old_esp		dd ?
_hash_0		dd ?
_hash_1 	dd ?
_hash_2 	dd ?
_hash_3 	dd ?
_hash_4		dd ?
_hash_5		dd ?
_hash_6		dd ?
_hash_7		dd ?
_hash_8		dd ?
_hash_9		dd ?
_hash_0_temp	dd ?
_hash_1_temp	dd ?
_hash_2_temp	dd ?
_hash_3_temp	dd ?
_hash_4_temp	dd ?
_hash_5_temp	dd ?
_hash_6_temp	dd ?
_hash_7_temp	dd ?
_hash_8_temp	dd ?
_hash_9_temp	dd ?
_size		dd ?
_count		dd ?
_flag		dd ?

.code
SHA1	PROC
	pushad
	mov	old_esp, esp
	cld
	mov	ecx, [esp+ 28h]	; dlugosc danych do hashowania w bajtach	_size
	mov	esi, [esp+ 2Ch]	; offset danych do hashowania			_addr_INPUT
	mov	dword ptr [_size] , ecx
	or	dword ptr [_flag] , -1		; umowna flaga...
	mov	dword ptr [_count], ecx

	mov	dword ptr [_hash_0] , 067452301h
	mov	dword ptr [_hash_1] , 0EFCDAB89h
	mov	dword ptr [_hash_2] , 098BADCFEh
	mov	dword ptr [_hash_3] , 010325476h
	mov	dword ptr [_hash_4] , 0C3D2E1F0h

@@SHA1_Loop:
	cmp	dword ptr [_count] , 64
	jb	@@SHA1_LIPOF

	mov	eax, dword ptr [_hash_0]
	mov	ebx, dword ptr [_hash_1]
	mov	ecx, dword ptr [_hash_2]
	mov	edx, dword ptr [_hash_3]
	mov	ebp, dword ptr [_hash_4]

	Trans_0 eax,ebx,ecx,edx,ebp,dword ptr [_temp_buffer+4*0]
	Trans_0 ebp,eax,ebx,ecx,edx,dword ptr [_temp_buffer+4*1]
	Trans_0 edx,ebp,eax,ebx,ecx,dword ptr [_temp_buffer+4*2]
	Trans_0 ecx,edx,ebp,eax,ebx,dword ptr [_temp_buffer+4*3]
	Trans_0 ebx,ecx,edx,ebp,eax,dword ptr [_temp_buffer+4*4]
	Trans_0 eax,ebx,ecx,edx,ebp,dword ptr [_temp_buffer+4*5]
	Trans_0 ebp,eax,ebx,ecx,edx,dword ptr [_temp_buffer+4*6]
	Trans_0 edx,ebp,eax,ebx,ecx,dword ptr [_temp_buffer+4*7]
	Trans_0 ecx,edx,ebp,eax,ebx,dword ptr [_temp_buffer+4*8]
	Trans_0 ebx,ecx,edx,ebp,eax,dword ptr [_temp_buffer+4*9]
	Trans_0 eax,ebx,ecx,edx,ebp,dword ptr [_temp_buffer+4*10]
	Trans_0 ebp,eax,ebx,ecx,edx,dword ptr [_temp_buffer+4*11]
	Trans_0 edx,ebp,eax,ebx,ecx,dword ptr [_temp_buffer+4*12]
	Trans_0 ecx,edx,ebp,eax,ebx,dword ptr [_temp_buffer+4*13]
	Trans_0 ebx,ecx,edx,ebp,eax,dword ptr [_temp_buffer+4*14]
	Trans_0 eax,ebx,ecx,edx,ebp,dword ptr [_temp_buffer+4*15]
	Trans_1 ebp,eax,ebx,ecx,edx,dword ptr [_temp_buffer+4*13],dword ptr [_temp_buffer+4*8] ,dword ptr [_temp_buffer+4*2] ,dword ptr [_temp_buffer+4*0]
	Trans_1 edx,ebp,eax,ebx,ecx,dword ptr [_temp_buffer+4*14],dword ptr [_temp_buffer+4*9] ,dword ptr [_temp_buffer+4*3] ,dword ptr [_temp_buffer+4*1]
	Trans_1 ecx,edx,ebp,eax,ebx,dword ptr [_temp_buffer+4*15],dword ptr [_temp_buffer+4*10],dword ptr [_temp_buffer+4*4] ,dword ptr [_temp_buffer+4*2]
	Trans_1 ebx,ecx,edx,ebp,eax,dword ptr [_temp_buffer+4*0] ,dword ptr [_temp_buffer+4*11],dword ptr [_temp_buffer+4*5] ,dword ptr [_temp_buffer+4*3]
	Trans_2 eax,ebx,ecx,edx,ebp,dword ptr [_temp_buffer+4*1] ,dword ptr [_temp_buffer+4*12],dword ptr [_temp_buffer+4*6] ,dword ptr [_temp_buffer+4*4]
	Trans_2 ebp,eax,ebx,ecx,edx,dword ptr [_temp_buffer+4*2] ,dword ptr [_temp_buffer+4*13],dword ptr [_temp_buffer+4*7] ,dword ptr [_temp_buffer+4*5]
	Trans_2 edx,ebp,eax,ebx,ecx,dword ptr [_temp_buffer+4*3] ,dword ptr [_temp_buffer+4*14],dword ptr [_temp_buffer+4*8] ,dword ptr [_temp_buffer+4*6]
	Trans_2 ecx,edx,ebp,eax,ebx,dword ptr [_temp_buffer+4*4] ,dword ptr [_temp_buffer+4*15],dword ptr [_temp_buffer+4*9] ,dword ptr [_temp_buffer+4*7]
	Trans_2 ebx,ecx,edx,ebp,eax,dword ptr [_temp_buffer+4*5] ,dword ptr [_temp_buffer+4*0] ,dword ptr [_temp_buffer+4*10],dword ptr [_temp_buffer+4*8]
	Trans_2 eax,ebx,ecx,edx,ebp,dword ptr [_temp_buffer+4*6] ,dword ptr [_temp_buffer+4*1] ,dword ptr [_temp_buffer+4*11],dword ptr [_temp_buffer+4*9]
	Trans_2 ebp,eax,ebx,ecx,edx,dword ptr [_temp_buffer+4*7] ,dword ptr [_temp_buffer+4*2] ,dword ptr [_temp_buffer+4*12],dword ptr [_temp_buffer+4*10]
	Trans_2 edx,ebp,eax,ebx,ecx,dword ptr [_temp_buffer+4*8] ,dword ptr [_temp_buffer+4*3] ,dword ptr [_temp_buffer+4*13],dword ptr [_temp_buffer+4*11]
	Trans_2 ecx,edx,ebp,eax,ebx,dword ptr [_temp_buffer+4*9] ,dword ptr [_temp_buffer+4*4] ,dword ptr [_temp_buffer+4*14],dword ptr [_temp_buffer+4*12]
	Trans_2 ebx,ecx,edx,ebp,eax,dword ptr [_temp_buffer+4*10],dword ptr [_temp_buffer+4*5] ,dword ptr [_temp_buffer+4*15],dword ptr [_temp_buffer+4*13]
	Trans_2 eax,ebx,ecx,edx,ebp,dword ptr [_temp_buffer+4*11],dword ptr [_temp_buffer+4*6] ,dword ptr [_temp_buffer+4*0] ,dword ptr [_temp_buffer+4*14]
	Trans_2 ebp,eax,ebx,ecx,edx,dword ptr [_temp_buffer+4*12],dword ptr [_temp_buffer+4*7] ,dword ptr [_temp_buffer+4*1] ,dword ptr [_temp_buffer+4*15]
	Trans_2 edx,ebp,eax,ebx,ecx,dword ptr [_temp_buffer+4*13],dword ptr [_temp_buffer+4*8] ,dword ptr [_temp_buffer+4*2] ,dword ptr [_temp_buffer+4*0]
	Trans_2 ecx,edx,ebp,eax,ebx,dword ptr [_temp_buffer+4*14],dword ptr [_temp_buffer+4*9] ,dword ptr [_temp_buffer+4*3] ,dword ptr [_temp_buffer+4*1]
	Trans_2 ebx,ecx,edx,ebp,eax,dword ptr [_temp_buffer+4*15],dword ptr [_temp_buffer+4*10],dword ptr [_temp_buffer+4*4] ,dword ptr [_temp_buffer+4*2]
	Trans_2 eax,ebx,ecx,edx,ebp,dword ptr [_temp_buffer+4*0] ,dword ptr [_temp_buffer+4*11],dword ptr [_temp_buffer+4*5] ,dword ptr [_temp_buffer+4*3]
	Trans_2 ebp,eax,ebx,ecx,edx,dword ptr [_temp_buffer+4*1] ,dword ptr [_temp_buffer+4*12],dword ptr [_temp_buffer+4*6] ,dword ptr [_temp_buffer+4*4]
	Trans_2 edx,ebp,eax,ebx,ecx,dword ptr [_temp_buffer+4*2] ,dword ptr [_temp_buffer+4*13],dword ptr [_temp_buffer+4*7] ,dword ptr [_temp_buffer+4*5]
	Trans_2 ecx,edx,ebp,eax,ebx,dword ptr [_temp_buffer+4*3] ,dword ptr [_temp_buffer+4*14],dword ptr [_temp_buffer+4*8] ,dword ptr [_temp_buffer+4*6]
	Trans_2 ebx,ecx,edx,ebp,eax,dword ptr [_temp_buffer+4*4] ,dword ptr [_temp_buffer+4*15],dword ptr [_temp_buffer+4*9] ,dword ptr [_temp_buffer+4*7]
	Trans_3 eax,ebx,ecx,edx,ebp,dword ptr [_temp_buffer+4*5] ,dword ptr [_temp_buffer+4*0] ,dword ptr [_temp_buffer+4*10],dword ptr [_temp_buffer+4*8]
	Trans_3 ebp,eax,ebx,ecx,edx,dword ptr [_temp_buffer+4*6] ,dword ptr [_temp_buffer+4*1] ,dword ptr [_temp_buffer+4*11],dword ptr [_temp_buffer+4*9]
	Trans_3 edx,ebp,eax,ebx,ecx,dword ptr [_temp_buffer+4*7] ,dword ptr [_temp_buffer+4*2] ,dword ptr [_temp_buffer+4*12],dword ptr [_temp_buffer+4*10]
	Trans_3 ecx,edx,ebp,eax,ebx,dword ptr [_temp_buffer+4*8] ,dword ptr [_temp_buffer+4*3] ,dword ptr [_temp_buffer+4*13],dword ptr [_temp_buffer+4*11]
	Trans_3 ebx,ecx,edx,ebp,eax,dword ptr [_temp_buffer+4*9] ,dword ptr [_temp_buffer+4*4] ,dword ptr [_temp_buffer+4*14],dword ptr [_temp_buffer+4*12]
	Trans_3 eax,ebx,ecx,edx,ebp,dword ptr [_temp_buffer+4*10],dword ptr [_temp_buffer+4*5] ,dword ptr [_temp_buffer+4*15],dword ptr [_temp_buffer+4*13]
	Trans_3 ebp,eax,ebx,ecx,edx,dword ptr [_temp_buffer+4*11],dword ptr [_temp_buffer+4*6] ,dword ptr [_temp_buffer+4*0] ,dword ptr [_temp_buffer+4*14]
	Trans_3 edx,ebp,eax,ebx,ecx,dword ptr [_temp_buffer+4*12],dword ptr [_temp_buffer+4*7] ,dword ptr [_temp_buffer+4*1] ,dword ptr [_temp_buffer+4*15]
	Trans_3 ecx,edx,ebp,eax,ebx,dword ptr [_temp_buffer+4*13],dword ptr [_temp_buffer+4*8] ,dword ptr [_temp_buffer+4*2] ,dword ptr [_temp_buffer+4*0]
	Trans_3 ebx,ecx,edx,ebp,eax,dword ptr [_temp_buffer+4*14],dword ptr [_temp_buffer+4*9] ,dword ptr [_temp_buffer+4*3] ,dword ptr [_temp_buffer+4*1]
	Trans_3 eax,ebx,ecx,edx,ebp,dword ptr [_temp_buffer+4*15],dword ptr [_temp_buffer+4*10],dword ptr [_temp_buffer+4*4] ,dword ptr [_temp_buffer+4*2]
	Trans_3 ebp,eax,ebx,ecx,edx,dword ptr [_temp_buffer+4*0] ,dword ptr [_temp_buffer+4*11],dword ptr [_temp_buffer+4*5] ,dword ptr [_temp_buffer+4*3]
	Trans_3 edx,ebp,eax,ebx,ecx,dword ptr [_temp_buffer+4*1] ,dword ptr [_temp_buffer+4*12],dword ptr [_temp_buffer+4*6] ,dword ptr [_temp_buffer+4*4]
	Trans_3 ecx,edx,ebp,eax,ebx,dword ptr [_temp_buffer+4*2] ,dword ptr [_temp_buffer+4*13],dword ptr [_temp_buffer+4*7] ,dword ptr [_temp_buffer+4*5]
	Trans_3 ebx,ecx,edx,ebp,eax,dword ptr [_temp_buffer+4*3] ,dword ptr [_temp_buffer+4*14],dword ptr [_temp_buffer+4*8] ,dword ptr [_temp_buffer+4*6]
	Trans_3 eax,ebx,ecx,edx,ebp,dword ptr [_temp_buffer+4*4] ,dword ptr [_temp_buffer+4*15],dword ptr [_temp_buffer+4*9] ,dword ptr [_temp_buffer+4*7]
	Trans_3 ebp,eax,ebx,ecx,edx,dword ptr [_temp_buffer+4*5] ,dword ptr [_temp_buffer+4*0] ,dword ptr [_temp_buffer+4*10],dword ptr [_temp_buffer+4*8]
	Trans_3 edx,ebp,eax,ebx,ecx,dword ptr [_temp_buffer+4*6] ,dword ptr [_temp_buffer+4*1] ,dword ptr [_temp_buffer+4*11],dword ptr [_temp_buffer+4*9]
	Trans_3 ecx,edx,ebp,eax,ebx,dword ptr [_temp_buffer+4*7] ,dword ptr [_temp_buffer+4*2] ,dword ptr [_temp_buffer+4*12],dword ptr [_temp_buffer+4*10]
	Trans_3 ebx,ecx,edx,ebp,eax,dword ptr [_temp_buffer+4*8] ,dword ptr [_temp_buffer+4*3] ,dword ptr [_temp_buffer+4*13],dword ptr [_temp_buffer+4*11]
	Trans_4 eax,ebx,ecx,edx,ebp,dword ptr [_temp_buffer+4*9] ,dword ptr [_temp_buffer+4*4] ,dword ptr [_temp_buffer+4*14],dword ptr [_temp_buffer+4*12]
	Trans_4 ebp,eax,ebx,ecx,edx,dword ptr [_temp_buffer+4*10],dword ptr [_temp_buffer+4*5] ,dword ptr [_temp_buffer+4*15],dword ptr [_temp_buffer+4*13]
	Trans_4 edx,ebp,eax,ebx,ecx,dword ptr [_temp_buffer+4*11],dword ptr [_temp_buffer+4*6] ,dword ptr [_temp_buffer+4*0] ,dword ptr [_temp_buffer+4*14]
	Trans_4 ecx,edx,ebp,eax,ebx,dword ptr [_temp_buffer+4*12],dword ptr [_temp_buffer+4*7] ,dword ptr [_temp_buffer+4*1] ,dword ptr [_temp_buffer+4*15]
	Trans_4 ebx,ecx,edx,ebp,eax,dword ptr [_temp_buffer+4*13],dword ptr [_temp_buffer+4*8] ,dword ptr [_temp_buffer+4*2] ,dword ptr [_temp_buffer+4*0]
	Trans_4 eax,ebx,ecx,edx,ebp,dword ptr [_temp_buffer+4*14],dword ptr [_temp_buffer+4*9] ,dword ptr [_temp_buffer+4*3] ,dword ptr [_temp_buffer+4*1]
	Trans_4 ebp,eax,ebx,ecx,edx,dword ptr [_temp_buffer+4*15],dword ptr [_temp_buffer+4*10],dword ptr [_temp_buffer+4*4] ,dword ptr [_temp_buffer+4*2]
	Trans_4 edx,ebp,eax,ebx,ecx,dword ptr [_temp_buffer+4*0] ,dword ptr [_temp_buffer+4*11],dword ptr [_temp_buffer+4*5] ,dword ptr [_temp_buffer+4*3]
	Trans_4 ecx,edx,ebp,eax,ebx,dword ptr [_temp_buffer+4*1] ,dword ptr [_temp_buffer+4*12],dword ptr [_temp_buffer+4*6] ,dword ptr [_temp_buffer+4*4]
	Trans_4 ebx,ecx,edx,ebp,eax,dword ptr [_temp_buffer+4*2] ,dword ptr [_temp_buffer+4*13],dword ptr [_temp_buffer+4*7] ,dword ptr [_temp_buffer+4*5]
	Trans_4 eax,ebx,ecx,edx,ebp,dword ptr [_temp_buffer+4*3] ,dword ptr [_temp_buffer+4*14],dword ptr [_temp_buffer+4*8] ,dword ptr [_temp_buffer+4*6]
	Trans_4 ebp,eax,ebx,ecx,edx,dword ptr [_temp_buffer+4*4] ,dword ptr [_temp_buffer+4*15],dword ptr [_temp_buffer+4*9] ,dword ptr [_temp_buffer+4*7]
	Trans_4 edx,ebp,eax,ebx,ecx,dword ptr [_temp_buffer+4*5] ,dword ptr [_temp_buffer+4*0] ,dword ptr [_temp_buffer+4*10],dword ptr [_temp_buffer+4*8]
	Trans_4 ecx,edx,ebp,eax,ebx,dword ptr [_temp_buffer+4*6] ,dword ptr [_temp_buffer+4*1] ,dword ptr [_temp_buffer+4*11],dword ptr [_temp_buffer+4*9]
	Trans_4 ebx,ecx,edx,ebp,eax,dword ptr [_temp_buffer+4*7] ,dword ptr [_temp_buffer+4*2] ,dword ptr [_temp_buffer+4*12],dword ptr [_temp_buffer+4*10]
	Trans_4 eax,ebx,ecx,edx,ebp,dword ptr [_temp_buffer+4*8] ,dword ptr [_temp_buffer+4*3] ,dword ptr [_temp_buffer+4*13],dword ptr [_temp_buffer+4*11]
	Trans_4 ebp,eax,ebx,ecx,edx,dword ptr [_temp_buffer+4*9] ,dword ptr [_temp_buffer+4*4] ,dword ptr [_temp_buffer+4*14],dword ptr [_temp_buffer+4*12]
	Trans_4 edx,ebp,eax,ebx,ecx,dword ptr [_temp_buffer+4*10],dword ptr [_temp_buffer+4*5] ,dword ptr [_temp_buffer+4*15],dword ptr [_temp_buffer+4*13]
	Trans_4 ecx,edx,ebp,eax,ebx,dword ptr [_temp_buffer+4*11],dword ptr [_temp_buffer+4*6] ,dword ptr [_temp_buffer+4*0] ,dword ptr [_temp_buffer+4*14]
	Trans_4 ebx,ecx,edx,ebp,eax,dword ptr [_temp_buffer+4*12],dword ptr [_temp_buffer+4*7] ,dword ptr [_temp_buffer+4*1] ,dword ptr [_temp_buffer+4*15]

	add	dword ptr [_hash_0], eax
	add	dword ptr [_hash_1], ebx
	add	dword ptr [_hash_2], ecx
	add	dword ptr [_hash_3], edx
	add	dword ptr [_hash_4], ebp

	sub	dword ptr [_count], 64
	jmp	@@SHA1_Loop

@@SHA1_LIPOF:
	cmp	dword ptr [_flag], 0
	jz	@@SHA1_Finishing
	mov	esp, old_esp
	call	BI_Padding
	jmp	@@SHA1_Loop

@@SHA1_Finishing:
	mov	esp, old_esp
	mov	edi, [esp+ 24h]		; offset bufora dla wyniku _addr_OUTPUT
	mov	esi, offset _hash_0

	mov	ecx, 5
@@:
	mov	eax, dword ptr [esi+4*ecx-4]
	bswap	eax
	mov	dword ptr [edi+4*ecx-4], eax
	dec	ecx
	jnz	@B

	mov	ecx, 56
	xor	eax, eax
	mov	edi, offset _temp_buffer
	rep	stosd

	popad
	ret	0Ch
SHA1	ENDP

BI_Padding	PROC

	mov	ecx, dword ptr [_count]
	mov	dword ptr [_flag] , 0
	mov	dword ptr [_count], 64
	mov	eax, ecx
	mov	edi, offset _temp_buffer

	test	eax, eax
	jz	@@only_null
	
	rep	movsb

@@only_null:
	mov	ecx, eax
	mov	byte ptr [edi], 80h
	sub	ecx, 55
	inc	edi
	neg	ecx
	jz	@@save_size_in_pad
	jns	@@zero_mem

	add	dword ptr [_count], 64
	add	ecx, 64		;padding rozciagnij tez na nastepne 64 bajty !

@@zero_mem:
	xor	al, al
	rep	stosb

@@save_size_in_pad:
	xor	edx, edx
	mov	eax, dword ptr [_size]
	mul	dword ptr [const_8]
	bswap	eax
	bswap	edx
	mov	dword ptr [edi], edx
	mov	dword ptr [edi+4], eax
	mov	esi, offset _temp_buffer
	ret
	
const_8	dd	8
BI_Padding	ENDP