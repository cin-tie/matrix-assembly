.section .note.GNU-stack, "", @progbits

.section .text
.globl matrix_add

matrix_add:
    pushq %rbp
    movq %rsp, %rbp
    pushq %rbx
    pushq %r12
    pushq %r13
    pushq %r14

    xorq %r9, %r9
    xorq %r10, %r10

    outer_loop:

        cmpq %r9, %rcx
        je outer_loop_end

        movq (%rdi, %r9, 8), %r11
        movq (%rsi, %r9, 8), %r12
        movq (%rdx, %r9, 8), %r13

        xorq %r10, %r10

        inner_loop:

            cmpq %r10, %r8
            je inner_loop_end

            movq (%r11, %r10, 8), %r14
            addq (%r12, %r10, 8), %r14
            movq %r14, (%r13, %r10, 8)

            incq %r10
            jmp inner_loop

        inner_loop_end:

        incq %r9
        jmp outer_loop

    outer_loop_end:

    popq %r14
    popq %r13
    popq %r12
    popq %r11
    popq %rbx
    movq %rbp, %rsp
    popq %rbp
