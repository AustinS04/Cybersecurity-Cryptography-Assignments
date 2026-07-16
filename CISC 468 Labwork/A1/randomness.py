from bcc import BPF

bpf_interrupt_text = """#include <uapi/linux/ptrace.h>

int trace_add_interrupt_randomness(struct pt_regs *ctx, int irq)
{

bpf_trace_printk("add_interrupt_randomness: irq=%d\\n",irq);
return 0;

}"""


bpf_input_text = """#include <uapi/linux/ptrace.h>

int trace_add_input_randomness(struct pt_regs *ctx, int type, int code, int value)
{

bpf_trace_printk("add_input_randomness: type=%d, code=%d, value=%d\\n",type,code,value);
return 0;

}"""



b = BPF(text=bpf_input_text)
#b.attach_kprobe(event="add_interrupt_randomness", fn_name="trace_add_interrupt_randomness")
b.attach_kprobe(event="add_input_randomness", fn_name="trace_add_input_randomness")
print("Tracing all main entropy sources... Ctrl-C to stop.")
b.trace_print()
