.section .note.GNU-stack, "", @progbits

.section .text
.global matrix_mul

matrix_mul:

    pushq %rbp
    movq %rsp, %rbp
    pushq %r12
    pushq %r13
    pushq %r14
    pushq %r15
    pushq %rbx

    xorq %r10, %r10

outer_loop_i:
    cmpq %r10, %rcx
    je outer_loop_i_end

    xorq %r11, %r11

outer_loop_j:
    cmpq %r11, %r9
    je outer_loop_j_end

    movq $0, %r12

    xorq %r13, %r13

inner_loop_k:
    cmpq %r13, %r8
    je inner_loop_k_end

    movq (%rdi, %r10, 8), %r14
    movq (%r14, %r13, 8), %r14

    movq (%rsi, %r13, 8), %r15 
    movq (%r15, %r11, 8), %r15

    imulq %r15, %r14
    addq %r14, %r12

    incq %r13
    jmp inner_loop_k

inner_loop_k_end:
    movq (%rdx, %r10, 8), %r14
    movq %r12, (%r14, %r11, 8)

    incq %r11
    jmp outer_loop_j

outer_loop_j_end:
    incq %r10
    jmp outer_loop_i

outer_loop_i_end:

    popq %rbx
    popq %r15
    popq %r14
    popq %r13
    popq %r12
    movq %rbp, %rsp
    popq %rbp
    ret
