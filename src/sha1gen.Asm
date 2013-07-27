.386
.model flat, stdcall  ;32 bit memory model
option casemap :none  ;case sensitive

include sha1gen.inc
include sha1.inc

.code

start:

	invoke GetModuleHandle,NULL
	mov		hInstance,eax

    invoke InitCommonControls
	invoke DialogBoxParam,hInstance,IDD_DIALOG1,NULL,addr DlgProc,NULL
	invoke ExitProcess,0

;########################################################################

DlgProc proc hWin:HWND,uMsg:UINT,wParam:WPARAM,lParam:LPARAM

	mov		eax,uMsg
	.if eax==WM_INITDIALOG
		invoke LoadIcon,hInstance,500
		mov hIcon,eax
		;-----------------------
		;MODIFICACION 6: cambiamos el anteultimo parametro.
		;Originalmente tenia valor NULL. Le coloque valor 1
		;para que el icono del programa se muestre tambien en la lista de programas
		;que aparece al presionar Alt+Tab.		
		;-----------------------
		invoke SendMessage,hWin,WM_SETICON,1,hIcon
		;-----------------------
		;MODIFICACION 4: limitamos el Edit de Nombre, de modo que tenga
		;un maximo de 30 caracteres
		;-----------------------		
		invoke GetDlgItem,hWin,EDT_NOMBRE
		invoke SendMessage,eax,EM_LIMITTEXT,30,NULL
		
	.elseif eax==WM_COMMAND
		mov eax,wParam
		mov edx,eax
		shr edx,16
		.if ax==EDT_NOMBRE
			;-----------------------
			;MODIFICACION 5: para leer 30 caracteres, se debe pasar como ultimo parametro
			;el numero 31 (ya que son 30 caracteres + 1 caracter para el byte nulo final).
			;-----------------------			
			invoke GetDlgItemText,hWin,EDT_NOMBRE,addr ptrData,31
			mov nSize,eax
			push	offset ptrData			
			push	nSize 			
			push	offset ptrBuffer
			call	SHA1
			;convertimos el HASH de 160 bits a cadena
			mov esi,offset ptrBuffer
			;-----------------------
			;MODIFICACION 1: un hash de 160 bits son 5 dwords, por eso
			;reemplace el MOV ECX, 8 por un MOV ECX, 5
			;-----------------------			
			mov ecx,5
			invierte_hash160:
			mov eax,dword ptr ds:[esi]
			xchg ah,al
			ror eax,10h
			xchg ah,al
			mov dword ptr ds:[esi],eax
			add esi,4
			loopd invierte_hash160
			mov esi,offset tempHash160
			mov edi,offset ptrBuffer
			xor ecx,ecx
			;-----------------------
			;MODIFICACION 2: igual que la modificacion anterior. Un hash de 160 bits son 5 dwords, por eso
			;reemplace el WHILE ECX<6  por un WHILE ECX<5
			;-----------------------						
			.while ecx<5
				push ecx
				;-----------------------
				;MODIFICACION 3: cambie el formato a utilizar con wsprintf.
				;Anteriormente estaba definido como formato db '%X',0.
				;Lo redefini como formato db '%08X',0
				;de modo que el string generado por wsprintf tenga siempre 8 digitos
				;(se completa con 0's a izquierda para rellenar). Ejemplo de aplicacion:
				;convertir el numero 212121 a hexa utilizando wsprintf.
				;con el formato anterior, genera el string '212121'. Con el formato nuevo
				;genera el string '00212121'. De esta forma el string correspondiente al Hash
				;estara formado siempre por 40 caracteres.
				;-----------------------
				invoke wsprintf,esi,addr formato,dword ptr ds:[edi]
				add esi,8
				add edi,4
				pop ecx
				inc ecx
			.endw
			invoke SetDlgItemText,hWin,EDT_HASH,addr tempHash160
		.elseif eax==BTN_ACERCADE
			invoke MessageBox,hWin,offset mensaje,offset titulo,MB_OK+MB_ICONINFORMATION
		.elseif eax==BTN_SALIR
			invoke EndDialog,hWin,0
		.endif
	.elseif eax==WM_CLOSE
		invoke EndDialog,hWin,0
	.else
		mov		eax,FALSE
		ret
	.endif
	mov		eax,TRUE
	ret

DlgProc endp

end start
