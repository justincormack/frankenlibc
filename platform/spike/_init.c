// See LICENSE for license details.

#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <limits.h>

#include "util.h"
#include "syscall.h"

// initialized in crt.S
int have_vec;

static long handle_frontend_syscall(long which, long arg0, long arg1, long arg2)
{
  volatile uint64_t magic_mem[8] __attribute__((aligned(64)));
  magic_mem[0] = which;
  magic_mem[1] = arg0;
  magic_mem[2] = arg1;
  magic_mem[3] = arg2;
  __sync_synchronize();
  write_csr(tohost, (long)magic_mem);
  while (swap_csr(fromhost, 0) == 0);
  return magic_mem[0];
}

// In setStats, we might trap reading uarch-specific counters.
// The trap handler will skip over the instruction and write 0,
// but only if a0 is the destination register.
#define read_csr_safe(reg) ({ register long __tmp asm("a0"); \
  asm volatile ("csrr %0, " #reg : "=r"(__tmp)); \
  __tmp; })

#define NUM_COUNTERS 18
static long counters[NUM_COUNTERS];
static char* counter_names[NUM_COUNTERS];
static int handle_stats(int enable)
{
  //use csrs to set stats register
  if (enable)
    asm volatile ("csrrs a0, stats, 1" ::: "a0");
  int i = 0;
#define READ_CTR(name) do { \
    while (i >= NUM_COUNTERS) ; \
    long csr = read_csr_safe(name); \
    if (!enable) { csr -= counters[i]; counter_names[i] = #name; } \
    counters[i++] = csr; \
  } while (0)
  READ_CTR(cycle);   READ_CTR(instret);
  READ_CTR(uarch0);  READ_CTR(uarch1);  READ_CTR(uarch2);  READ_CTR(uarch3);
  READ_CTR(uarch4);  READ_CTR(uarch5);  READ_CTR(uarch6);  READ_CTR(uarch7);
  READ_CTR(uarch8);  READ_CTR(uarch9);  READ_CTR(uarch10); READ_CTR(uarch11);
  READ_CTR(uarch12); READ_CTR(uarch13); READ_CTR(uarch14); READ_CTR(uarch15);
#undef READ_CTR
  if (!enable)
    asm volatile ("csrrc a0, stats, 1" ::: "a0");
  return 0;
}

static void tohost_exit(int code)
{
  write_csr(tohost, (code << 1) | 1);
  while (1);
}

long handle_trap(long cause, long epc, long regs[32])
{
  int* csr_insn;
  asm ("jal %0, 1f; csrr a0, stats; 1:" : "=r"(csr_insn));
  long sys_ret = 0;

  if (cause == CAUSE_ILLEGAL_INSTRUCTION &&
      (*(int*)epc & *csr_insn) == *csr_insn)
    ;
  else if (cause != CAUSE_SYSCALL)
    tohost_exit(1337);
  else if (regs[17] == SYS_exit)
    tohost_exit(regs[10]);
  else if (regs[17] == SYS_stats)
    sys_ret = handle_stats(regs[10]);
  else
    sys_ret = handle_frontend_syscall(regs[17], regs[10], regs[11], regs[12]);

  regs[10] = sys_ret;
  return epc+4;
}

long _syscall(long num, long arg0, long arg1, long arg2)
{
  register long a7 asm("a7") = num;
  register long a0 asm("a0") = arg0;
  register long a1 asm("a1") = arg1;
  register long a2 asm("a2") = arg2;
  asm volatile ("scall" : "+r"(a0) : "r"(a1), "r"(a2), "r"(a7));
  return a0;
}

void setStats(int enable)
{
  _syscall(SYS_stats, enable, 0, 0);
}

void __attribute__((weak)) thread_entry(int cid, int nc)
{
  // multi-threaded programs override this function.
  // for the case of single-threaded programs, only let core 0 proceed.
  while (cid != 0);
}

int __attribute__((weak)) main(int argc, char** argv)
{
  // single-threaded programs override this function.
  //printstr("Implement main(), foo!\n");
  return -1;
}

static void init_tls()
{
  register void* thread_pointer asm("tp");
  extern char _tls_data;
  extern __thread char _tdata_begin, _tdata_end, _tbss_end;
  size_t tdata_size = &_tdata_end - &_tdata_begin;
  memcpy(thread_pointer, &_tls_data, tdata_size);
  size_t tbss_size = &_tbss_end - &_tdata_end;
  memset(thread_pointer + tdata_size, 0, tbss_size);
}

int argc = 1;
char *argv[2] = {"spike", "\0"};
char *envp[2] = {"RUMP_VERBOSE=1", "\0"};

void _init(int cid, int nc)
{
  init_tls();
  thread_entry(cid, nc);

  // only single-threaded programs should ever get here.
  int ret = __franken_start_main(main, argc, argv, envp);

/*
  char buf[NUM_COUNTERS * 32] __attribute__((aligned(64)));
  char* pbuf = buf;
  for (int i = 0; i < NUM_COUNTERS; i++)
    if (counters[i])
      pbuf += sprintf(pbuf, "%s = %d\n", counter_names[i], counters[i]);
  if (pbuf != buf)
    printstr(buf);
*/

  exit(ret);
}
