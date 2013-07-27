
include windows.inc
include kernel32.inc
include user32.inc
include Comctl32.inc
include shell32.inc

includelib kernel32.lib
includelib user32.lib
includelib Comctl32.lib
includelib shell32.lib

DlgProc			PROTO	:HWND,:UINT,:WPARAM,:LPARAM

.const
; Constantes para los dialogs
IDD_DIALOG1			equ 101
; Constantes para los botones
BTN_SALIR			equ 1005
BTN_GENERAR			equ 1003
BTN_ACERCADE		equ 1004
; Constantes para los edits
EDT_NOMBRE 			equ 1001
EDT_HASH			equ 1002

;#########################################################################

.data?

hInstance			dd ?
hIcon				dd ?

.data
mensaje db "***** CracksLatinoS! 2006 *****",10,13,10,13
		db "SHA-1 160 bits HASH Generator",10,13,10,13
		db "Programado por: +NCR/CRC! [ReVeRsEr]",10,13
		db "Fecha: 19/05/06",10,13,10,13
		db "100 % Win32 ASM",10,13,10,13
		db "----------------------------------------------",10,13
		db "Gracias a WhiteG por su trabajo con",10,13
		db "SHA-1 pues gracias a el esta tool",10,13
		db "es posible.",10,13
		db "----------------------------------------------",10,13,10,13
		db "Programado con RadASM + MASM",0
titulo db "CLS! 2006 - SHA-1 HASH Generator",0 
formato	db '%08X',0
; Buffer que contiene la info para el HASH
ptrData dd 255 dup (0),0
; Tamanio del buffer ptrData
nSize dd 4 dup (0),0
; Buffer que almacena el HASH
ptrBuffer dd 255 dup (0),0
tempHash160 dd 255 dup (0),0
;#########################################################################
