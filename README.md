> dont care about the HellsGate that i wrote for that (i am sorry for that) 
 -> I wrote this for educational purposes only 

### also replace this :
```in .asm file
SetValue PROC
    mov rdi,rcx
    ret
SetValue ENDP


NtCreateSection PROC
    mov         r10,rcx
    mov         rax,rdi
    syscall
    ret
NtCreateSection ENDP
```
 
# Direct syscall in other way 
- Calculating SSN in run time and syscall
- direct syscall with Hardcoded syscall number
- GetProc and GetModuleHandle replacement function
- Encryption with Xor for shellcode

i also wrote Hash function for API hashing but i didnt complete that


