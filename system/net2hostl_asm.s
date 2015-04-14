.global net2hostl_asm

net2hostl_asm:
      push %ebp
      mov %esp, %ebp
      mov 8(%ebp), %eax
      xchg %ah,%al
      rol $16, %eax
      xchg %ah, %al
      pop %ebp
ret

