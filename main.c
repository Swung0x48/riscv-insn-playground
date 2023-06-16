#include <stdio.h>
#include <math.h>
#include <string.h>
#include <signal.h>
#include <stdint.h>

uint64_t asm_func(uint64_t arg0, uint64_t arg1);

static volatile sig_atomic_t got_sigill;

static void sigill_handler(int signo, siginfo_t *si, void* data) {
  ucontext_t* uc = (ucontext_t*)data;
  uc->uc_mcontext.__gregs[REG_PC] += 4;
  got_sigill = 1;
}

int check_presence() {
  struct sigaction sa_old, sa_new;
  memset(&sa_new, 0, sizeof(sa_new));
  sa_new.sa_flags = SA_SIGINFO;
  sa_new.sa_sigaction = sigill_handler;
  sigaction(SIGILL, &sa_new, &sa_old);

  /* Write insn that may not be present here 
   * In the case that it's not present, a SIGILL
   * will be raised, and handled by sigill_handler()
   */
  asm("csrrs t0, vlenb, x0");

  sigaction(SIGILL, &sa_old, NULL);
  if (got_sigill) return 0;
  return 1;
}


int main() {
  if (check_presence())
    printf("V extension present!\n");
  else
    printf("V extension not present\n");
    
  printf("%ld\n", asm_func(1ul, 2ul));
  
  return 0;
}
