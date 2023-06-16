# uint64_t asm_func(uint64_t arg0, uint64_t arg1)
.globl asm_func

asm_func:
    # Write your asm here
    # Make sure to check out RISC-V calling convention
    # in order to get argument from call
    
    # Get two arguments from a0 and a1
    # Then save to a0 to return
    addw a0, a0, a1
    ret
    
    
