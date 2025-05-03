[global syscallentrypoint]
[extern syscallprobe]
[extern syscall_rax]
[extern syscall_rbx]
[extern syscall_rcx]
[extern syscall_rdx]
[extern syscall_rsi]
[extern syscall_rdi]
[extern syscall_rsp]
[extern syscall_rbp]
[extern syscall_r8]
[extern syscall_r9]
[extern syscall_r10]
[extern syscall_r11]
[extern syscall_r12]
[extern syscall_r13]
[extern syscall_r14]
[extern syscall_r15]
[extern syscall_exstack]

syscallentrypoint:
    mov qword [syscall_rax],rax
    mov qword [syscall_rbx],rbx
    mov qword [syscall_rcx],rcx
    mov qword [syscall_rdx],rdx
    mov qword [syscall_rsi],rsi
    mov qword [syscall_rdi],rdi
    mov qword [syscall_rsp],rsp
    mov qword [syscall_rbp],rbp
    mov qword [syscall_r8],r8
    mov qword [syscall_r9],r9
    mov qword [syscall_r10],r10
    mov qword [syscall_r11],r11
    mov qword [syscall_r12],r12
    mov qword [syscall_r13],r13
    mov qword [syscall_r14],r14
    mov qword [syscall_r15],r15
    ;mov rsp,qword [syscall_exstack]
    call syscallprobe
    mov rax, qword [syscall_rax]
    mov rbx, qword [syscall_rbx]
    mov rcx, qword [syscall_rcx]
    mov rdx, qword [syscall_rdx]
    mov rsi, qword [syscall_rsi]
    mov rdi, qword [syscall_rdi]
    mov r8, qword [syscall_r8]
    mov r9, qword [syscall_r9]
    mov r10, qword [syscall_r10]
    mov r11, qword [syscall_r11]
    mov r12, qword [syscall_r12]
    mov r13, qword [syscall_r13]
    mov r14, qword [syscall_r14]
    mov r15, qword [syscall_r15]
    o64 sysret