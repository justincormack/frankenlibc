struct __ucontext_stack_t {
    void *ss_sp;
    int ss_flags;
    size_t ss_size;
};
typedef struct ucontext_t {
    unsigned long uc_regs[40];
    unsigned long uc_flags;
    void *uc_link;
    struct __ucontext_stack_t uc_stack;
} ucontext_t;
