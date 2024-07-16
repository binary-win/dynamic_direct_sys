;EXTERN pNtCreateSection:DWORD



.code
;public SetValue


SetValue PROC
    mov rdi,rcx
    ret
SetValue ENDP


NtCreateSection PROC
    mov         r10,rcx
    mov         rax,4Ah
    syscall
    ret
NtCreateSection ENDP




NtCreateThreadEx PROC
    mov         r10,rcx
    mov         eax,0C7h
    syscall
    ret
NtCreateThreadEx ENDP


NtWaitForSingleObject PROC
    mov         r10,rcx
    mov         eax,4
    syscall
    ret
NtWaitForSingleObject ENDP




END