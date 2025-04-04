.section .note.GNU-stack, "", @progbits

.section .data
minor_buffer: .space 32

.section .text
.global matrix_det

matrix_det:

    pushq %rbp
    movq %rsp, %rbp
    pushq %rbx
    pushq %r12
    pushq %r13
    pushq %r14
    pushq %r15

    cmpq $1, %rsi
    je det_1x1
    cmpq $2, %rsi
    je det_2x2

    movq $0, %r15
    movq $0, %rbx

    det_loop:

        cmpq %rbx, %rsi
        je det_loop_end

        movq %rsi, %r14
        decq %r14

        movq %r14, %rdi
        shlq $3, %rdi
        call mcur
        movq %rax, %r12

        movq $1, %r13

        fill_minor:

            cmpq %r13, %rsi
            je fill_minor_end

            movq %r14, %rdi
            shlq $3, %rdi
            call mcur
            movq %rax, (%r12, %r13, 8)

            movq $0, %r8
            movq $0, %r9

            copy_elements:

                cmpq %r8, %rsi
                je copy_elements_end

                cmpq %rbx, %r8
                je skip_col

                movq (%rdi, %r13, 8), %r10
                movq (%r10, %r8, 8), %r11

                movq (%r12, %r13, 8), %r10
                movq %r11, (%r10, %r9, 8)

                incq %r9

                skip_col:

                    incq %r8
                    jmp copy_elements
            
            copy_elements_end:

            incq %r13
            jmp fill_minor

        fill_minor_end:

        movq %r12, %rdi
        movq %r14, %rsi
        call matrix_det
        movq %rax, %r11

        movq $1, %rax
        testq $1, %rbx
        jz positive
        negq %rax

        positive:

            movq (%rdi), %r10
            movq (%r10, %rbx, 8), %r10
            imulq %r10, %r11
            imulq %r11, %rax
            addq %rax, %r15

        movq $0, %r13 
        
        free_minor:

            cmpq %r13, %r14
            je free_minor_end

            movq (%r12, %r13, 8), %rdi
            call mfree
            incq %r13
            jmp free_minor

        free_minor_end:
        
        movq %r12, %rdi
        call mfree

        incq %rbx
        jmp det_loop

    det_loop_end:

    det_1x1:
        movq (%rdi), %rax
        movq (%rax), %rax
        jmp matrix_det_end

    det_2x2:
    movq (%rdi), %r8
    movq 8(%rdi), %r9
    
    movq (%r8), %r10
    movq 8(%r8), %r11
    movq (%r9), %r12
    movq 8(%r9), %r13
    
    imulq %r13, %r10
    imulq %r12, %r11
    subq %r11, %r10
    movq %r10, %rax

    matrix_det_end:

    popq %r15
    popq %r14
    popq %r13
    popq %r12
    popq %rbx
    popq %rbp
    ret

mcur:
    pushq %rdi
    movq $12, %rax
    xorq %rdi, %rdi
    syscall
    popq %rdi
    ret

mfree:
    pushq %rbx
    movq %rdi, %rbx
    movq $12, %rax
    syscall
    cmpq %rax, %rbx 
    jne error
    popq %rbx
    ret

error:
    movq $0, %rax
    ret
    