#include <kernel.h>
#include <t_syslog.h>
#include <t_stdlib.h>

uint32_t us_ticker_read() {
    SYSTIM systim;
    ER ercd = get_tim(&systim);
    assert(ercd == E_OK);
#if TKERNEL_PRVER == UINT_C(0x2021)
    return systim * 1000UL;
#else
#error "Only HRP2 kernel is supported."
    return systim;
#endif

}
