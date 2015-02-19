#ifndef _UCONTEXT_H
#define _UCONTEXT_H

struct __ucontext_stack_t {
    void *ss_sp;
    int ss_flags;
    size_t ss_size;
};
typedef struct ucontext_t {
    unsigned long uc_regs[9];
    unsigned long uc_flags;
    void *uc_link;
    struct __ucontext_stack_t uc_stack;
} ucontext_t;

/* Note the type of makecontext is not the standard, as this is
   not valid C. We only allow a single void* argument but define
   as if it takes no arguments as that is normal.
*/
int  getcontext(ucontext_t *);
void makecontext(ucontext_t *, void (*)(void), int, void *);
int  swapcontext(ucontext_t *, ucontext_t *);

#endif
