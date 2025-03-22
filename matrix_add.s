.section .note.GNU-stack, "", @progbits

.section .text
.global matrix_add

matrix_add:
    pushq %rbp
    movq %rsp, %rbp
    pushq %r12
    pushq %r13
    pushq %r14
    pushq %r15

    xorq %r9, %r9

    outer_loop:
        cmpq %r9, %rcx
        je outer_loop_end

        movq (%rdi, %r9, 8), %r10
        movq (%rsi, %r9, 8), %r11
        movq (%rdx, %r9, 8), %r12

        xorq %r13, %r13

    inner_loop:
        cmpq %r13, %r8
        je inner_loop_end

        movq (%r10, %r13, 8), %r14
        movq (%r11, %r13, 8), %r15

        addq %r15, %r14
        movq %r14, (%r12, %r13, 8)

        incq %r13
        jmp inner_loop

    inner_loop_end:
        incq %r9
        jmp outer_loop

    outer_loop_end:

    popq %r15
    popq %r14
    popq %r13
    popq %r12
    movq %rbp, %rsp
    popq %rbp
    ret
    