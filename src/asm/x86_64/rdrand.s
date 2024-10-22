.global _rdrnd16_step
.global _rdrnd32_step
.global _rdrnd64_step


.text

// extern bool rdrnd16_step(u16 *data)
_rdrnd16_step:
    // Is rdrand supported?
    mov $1, %eax
    cpuid
    bt $30, %ecx

    // If not supported, return false
    jnc .fail
    
    // Try rdrand
    rdrand %ax
    jnc .fail
    
    // Write to data
    mov %ax, (%rdi)

    mov $1, %rax
    ret

.fail:
    mov $0, %rax
    ret

// extern bool rdrnd32_step(u32 *data)
_rdrnd32_step:
    // Is rdrand supported?
    mov $1, %eax
    cpuid
    bt $30, %ecx

    // If not supported, return false
    jnc .fail
    
    // Try rdrand
    rdrand %eax
    jnc .fail
    
    // Write to data
    mov %eax, (%rdi)

    mov $1, %rax
    ret


// extern bool rdrnd64_step(u64 *data)
_rdrnd64_step:
    // Is rdrand supported?
    mov $1, %eax
    cpuid
    bt $30, %ecx

    // If not supported, return false
    jnc .fail
    
    // Try rdrand
    rdrand %rax
    jnc .fail
    
    // Write to data
    mov %rax, (%rdi)

    mov $1, %rax
    ret
