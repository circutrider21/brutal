#pragma once

#include <brutal/io.h>
#include <handover/handover.h>
#include "kernel/tasking.h"

IoWriter *arch_debug(void);

void arch_entry_main(struct handover *handover);

void arch_entry_other(void);

void arch_boot_other(void);

void arch_idle(void);

void arch_stop(void);

void arch_enable_interrupt(void);