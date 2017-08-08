/* cfg1_out.c */
#define TOPPERS_CFG1_OUT  1
#include "kernel/kernel_int.h"
#include "app.h"
#include "csl.h"
#include "chip_timer.h"
#include "syssvc/syslog.h"
#include "syssvc/banner.h"
#include "target_serial.h"
#include "target_serial_dbsio.h"
#include "syssvc/serial.h"
#include "syssvc/logtask.h"
#include "dmloader.h"


#ifdef INT64_MAX
  typedef int64_t signed_t;
  typedef uint64_t unsigned_t;
#else
  typedef int32_t signed_t;
  typedef uint32_t unsigned_t;
#endif

#include "target_cfg1_out.h"

const uint32_t TOPPERS_cfg_magic_number = 0x12345678;
const uint32_t TOPPERS_cfg_sizeof_signed_t = sizeof(signed_t);
const uint32_t TOPPERS_cfg_sizeof_pointer = sizeof(const volatile void*);
const unsigned_t TOPPERS_cfg_CHAR_BIT = ((unsigned char)~0u == 0xff ? 8 : 16);
const unsigned_t TOPPERS_cfg_CHAR_MAX = ((char)-1 < 0 ? (char)((unsigned char)~0u >> 1) : (unsigned char)~0u);
const unsigned_t TOPPERS_cfg_CHAR_MIN = (unsigned_t)((char)-1 < 0 ? -((unsigned char)~0u >> 1) - 1 : 0);
const unsigned_t TOPPERS_cfg_SCHAR_MAX = (signed char)((unsigned char)~0u >> 1);
const unsigned_t TOPPERS_cfg_SHRT_MAX = (short)((unsigned short)~0u >> 1);
const unsigned_t TOPPERS_cfg_INT_MAX = (int)(~0u >> 1);
const unsigned_t TOPPERS_cfg_LONG_MAX = (long)(~0ul >> 1);

const unsigned_t TOPPERS_cfg_TOPPERS_SUPPORT_OVRHDR = 
#if defined(TOPPERS_SUPPORT_OVRHDR)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TOPPERS_SUPPORT_PROTECT = 
#if defined(TOPPERS_SUPPORT_PROTECT)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TOPPERS_SUPPORT_ATT_MOD = 
#if defined(TOPPERS_SUPPORT_ATT_MOD)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TOPPERS_SUPPORT_ATT_PMA = 
#if defined(TOPPERS_SUPPORT_ATT_PMA)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_SIL_ENDIAN_BIG = 
#if defined(SIL_ENDIAN_BIG)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_SIL_ENDIAN_LITTLE = 
#if defined(SIL_ENDIAN_LITTLE)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TA_NULL = ( unsigned_t )TA_NULL;
const unsigned_t TOPPERS_cfg_TA_ACT = ( unsigned_t )TA_ACT;
const unsigned_t TOPPERS_cfg_TA_TPRI = ( unsigned_t )TA_TPRI;
const unsigned_t TOPPERS_cfg_TA_WMUL = ( unsigned_t )TA_WMUL;
const unsigned_t TOPPERS_cfg_TA_CLR = ( unsigned_t )TA_CLR;
const unsigned_t TOPPERS_cfg_TA_CEILING = ( unsigned_t )TA_CEILING;
const unsigned_t TOPPERS_cfg_TA_STA = ( unsigned_t )TA_STA;
const unsigned_t TOPPERS_cfg_TA_NOWRITE = ( unsigned_t )TA_NOWRITE;
const unsigned_t TOPPERS_cfg_TA_NOREAD = ( unsigned_t )TA_NOREAD;
const unsigned_t TOPPERS_cfg_TA_EXEC = ( unsigned_t )TA_EXEC;
const unsigned_t TOPPERS_cfg_TA_MEMINI = ( unsigned_t )TA_MEMINI;
const unsigned_t TOPPERS_cfg_TA_MEMPRSV = ( unsigned_t )TA_MEMPRSV;
const unsigned_t TOPPERS_cfg_TA_SDATA = ( unsigned_t )TA_SDATA;
const unsigned_t TOPPERS_cfg_TA_UNCACHE = ( unsigned_t )TA_UNCACHE;
const unsigned_t TOPPERS_cfg_TA_IODEV = ( unsigned_t )TA_IODEV;
const unsigned_t TOPPERS_cfg_TA_NONKERNEL = ( unsigned_t )TA_NONKERNEL;
const unsigned_t TOPPERS_cfg_TA_ENAINT = ( unsigned_t )TA_ENAINT;
const unsigned_t TOPPERS_cfg_TA_EDGE = ( unsigned_t )TA_EDGE;
const unsigned_t TOPPERS_cfg_TDOM_KERNEL = ( unsigned_t )TDOM_KERNEL;
const unsigned_t TOPPERS_cfg_TDOM_NONE = ( unsigned_t )TDOM_NONE;
const unsigned_t TOPPERS_cfg_TACP_KERNEL = ( unsigned_t )TACP_KERNEL;
const unsigned_t TOPPERS_cfg_TACP_SHARED = ( unsigned_t )TACP_SHARED;
const signed_t TOPPERS_cfg_TMIN_TPRI = ( signed_t )TMIN_TPRI;
const signed_t TOPPERS_cfg_TMAX_TPRI = ( signed_t )TMAX_TPRI;
const signed_t TOPPERS_cfg_TMIN_DPRI = ( signed_t )TMIN_DPRI;
const signed_t TOPPERS_cfg_TMAX_DPRI = ( signed_t )TMAX_DPRI;
const signed_t TOPPERS_cfg_TMIN_ISRPRI = ( signed_t )TMIN_ISRPRI;
const signed_t TOPPERS_cfg_TMAX_ISRPRI = ( signed_t )TMAX_ISRPRI;
const unsigned_t TOPPERS_cfg_TBIT_TEXPTN = ( unsigned_t )TBIT_TEXPTN;
const unsigned_t TOPPERS_cfg_TBIT_FLGPTN = ( unsigned_t )TBIT_FLGPTN;
const unsigned_t TOPPERS_cfg_TMAX_MAXSEM = ( unsigned_t )TMAX_MAXSEM;
const unsigned_t TOPPERS_cfg_TMAX_RELTIM = ( unsigned_t )TMAX_RELTIM;
const signed_t TOPPERS_cfg_TMIN_INTPRI = ( signed_t )TMIN_INTPRI;
const unsigned_t TOPPERS_cfg_TOPPERS_ATTSEC = ( unsigned_t )TOPPERS_ATTSEC;
const unsigned_t TOPPERS_cfg_TOPPERS_ATTMEM = ( unsigned_t )TOPPERS_ATTMEM;
const unsigned_t TOPPERS_cfg_TOPPERS_USTACK = ( unsigned_t )TOPPERS_USTACK;
const unsigned_t TOPPERS_cfg_OMIT_STANDARD_MEMINIB = 
#if defined(OMIT_STANDARD_MEMINIB)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_OMIT_INITIALIZE_INTERRUPT = 
#if defined(OMIT_INITIALIZE_INTERRUPT)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_OMIT_INITIALIZE_EXCEPTION = 
#if defined(OMIT_INITIALIZE_EXCEPTION)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_OMIT_IDATA = 
#if defined(OMIT_IDATA)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_OMIT_CHECK_USTACK_OVERLAP = 
#if defined(OMIT_CHECK_USTACK_OVERLAP)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_OMIT_STANDARD_DATASECINIB = 
#if defined(OMIT_STANDARD_DATASECINIB)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_OMIT_STANDARD_BSSSECINIB = 
#if defined(OMIT_STANDARD_BSSSECINIB)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_USE_CFG_PASS3 = 
#if defined(USE_CFG_PASS3)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_USE_LATERPASS_DOMINIB = 
#if defined(USE_LATERPASS_DOMINIB)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_USE_DOMINICTXB = 
#if defined(USE_DOMINICTXB)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_USE_TSKINICTXB = 
#if defined(USE_TSKINICTXB)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_USE_REDZONE = 
#if defined(USE_REDZONE)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TARGET_TSKATR = 
#if defined(TARGET_TSKATR)
(TARGET_TSKATR);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TARGET_REGATR = 
#if defined(TARGET_REGATR)
(TARGET_REGATR);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TARGET_MEMATR = 
#if defined(TARGET_MEMATR)
(TARGET_MEMATR);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TARGET_INTATR = 
#if defined(TARGET_INTATR)
(TARGET_INTATR);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TARGET_INHATR = 
#if defined(TARGET_INHATR)
(TARGET_INHATR);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TARGET_ISRATR = 
#if defined(TARGET_ISRATR)
(TARGET_ISRATR);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TARGET_EXCATR = 
#if defined(TARGET_EXCATR)
(TARGET_EXCATR);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TARGET_SVCATR = 
#if defined(TARGET_SVCATR)
(TARGET_SVCATR);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TARGET_MIN_SSTKSZ = 
#if defined(TARGET_MIN_SSTKSZ)
(TARGET_MIN_SSTKSZ);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TARGET_MIN_USTKSZ = 
#if defined(TARGET_MIN_USTKSZ)
(TARGET_MIN_USTKSZ);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TARGET_MIN_ISTKSZ = 
#if defined(TARGET_MIN_ISTKSZ)
(TARGET_MIN_ISTKSZ);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TARGET_DUMMY_STKSZ = 
#if defined(TARGET_DUMMY_STKSZ)
(TARGET_DUMMY_STKSZ);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_CHECK_STKSZ_ALIGN = 
#if defined(CHECK_STKSZ_ALIGN)
(CHECK_STKSZ_ALIGN);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_CHECK_USTKSZ_ALIGN = 
#if defined(CHECK_USTKSZ_ALIGN)
(CHECK_USTKSZ_ALIGN);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_CHECK_FUNC_ALIGN = 
#if defined(CHECK_FUNC_ALIGN)
(CHECK_FUNC_ALIGN);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_CHECK_FUNC_NONNULL = 
#if defined(CHECK_FUNC_NONNULL)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_CHECK_STACK_ALIGN = 
#if defined(CHECK_STACK_ALIGN)
(CHECK_STACK_ALIGN);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_CHECK_STACK_NONNULL = 
#if defined(CHECK_STACK_NONNULL)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_CHECK_USTACK_ALIGN = 
#if defined(CHECK_USTACK_ALIGN)
(CHECK_USTACK_ALIGN);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_CHECK_USTACK_NONNULL = 
#if defined(CHECK_USTACK_NONNULL)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_CHECK_MPF_ALIGN = 
#if defined(CHECK_MPF_ALIGN)
(CHECK_MPF_ALIGN);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_CHECK_MPF_NONNULL = 
#if defined(CHECK_MPF_NONNULL)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_CHECK_MB_ALIGN = 
#if defined(CHECK_MB_ALIGN)
(CHECK_MB_ALIGN);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TOPPERS_LABEL_ASM = 
#if defined(TOPPERS_LABEL_ASM)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_sizeof_ID = ( unsigned_t )sizeof(ID);
const unsigned_t TOPPERS_cfg_sizeof_uint_t = ( unsigned_t )sizeof(uint_t);
const unsigned_t TOPPERS_cfg_sizeof_SIZE = ( unsigned_t )sizeof(SIZE);
const unsigned_t TOPPERS_cfg_sizeof_ATR = ( unsigned_t )sizeof(ATR);
const unsigned_t TOPPERS_cfg_sizeof_PRI = ( unsigned_t )sizeof(PRI);
const unsigned_t TOPPERS_cfg_sizeof_void_ptr = ( unsigned_t )sizeof(void*);
const unsigned_t TOPPERS_cfg_sizeof_VP = ( unsigned_t )sizeof(void*);
const unsigned_t TOPPERS_cfg_sizeof_intptr_t = ( unsigned_t )sizeof(intptr_t);
const unsigned_t TOPPERS_cfg_sizeof_FP = ( unsigned_t )sizeof(FP);
const unsigned_t TOPPERS_cfg_sizeof_ACPTN = ( unsigned_t )sizeof(ACPTN);
const unsigned_t TOPPERS_cfg_sizeof_ACVCT = ( unsigned_t )sizeof(ACVCT);
const unsigned_t TOPPERS_cfg_offsetof_ACVCT_acptn1 = ( unsigned_t )offsetof(ACVCT,acptn1);
const unsigned_t TOPPERS_cfg_offsetof_ACVCT_acptn2 = ( unsigned_t )offsetof(ACVCT,acptn2);
const unsigned_t TOPPERS_cfg_offsetof_ACVCT_acptn3 = ( unsigned_t )offsetof(ACVCT,acptn3);
const unsigned_t TOPPERS_cfg_offsetof_ACVCT_acptn4 = ( unsigned_t )offsetof(ACVCT,acptn4);
const unsigned_t TOPPERS_cfg_sizeof_INHNO = ( unsigned_t )sizeof(INHNO);
const unsigned_t TOPPERS_cfg_sizeof_INTNO = ( unsigned_t )sizeof(INTNO);
const unsigned_t TOPPERS_cfg_sizeof_EXCNO = ( unsigned_t )sizeof(EXCNO);
const unsigned_t TOPPERS_cfg_sizeof_DOMINIB = ( unsigned_t )sizeof(DOMINIB);
const unsigned_t TOPPERS_cfg_offsetof_DOMINIB_domptn = ( unsigned_t )offsetof(DOMINIB,domptn);
const unsigned_t TOPPERS_cfg_sizeof_MEMINIB = ( unsigned_t )sizeof(MEMINIB);
const unsigned_t TOPPERS_cfg_offsetof_MEMINIB_mematr = 
#if !defined(OMIT_STANDARD_MEMINIB)
(offsetof(MEMINIB,mematr));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offsetof_MEMINIB_acptn4 = 
#if !defined(OMIT_STANDARD_MEMINIB)
(offsetof(MEMINIB,acptn4));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offsetof_MEMINIB_acptn1 = 
#if !defined(OMIT_STANDARD_MEMINIB)
(offsetof(MEMINIB,acptn1));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offsetof_MEMINIB_acptn2 = 
#if !defined(OMIT_STANDARD_MEMINIB)
(offsetof(MEMINIB,acptn2));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_sizeof_TINIB = ( unsigned_t )sizeof(TINIB);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_p_dominib = ( unsigned_t )offsetof(TINIB,p_dominib);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_tskatr = ( unsigned_t )offsetof(TINIB,tskatr);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_exinf = ( unsigned_t )offsetof(TINIB,exinf);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_task = ( unsigned_t )offsetof(TINIB,task);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_ipriority = ( unsigned_t )offsetof(TINIB,ipriority);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_sstksz = 
#if !defined(USE_TSKINICTXB)
(offsetof(TINIB,sstksz));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offsetof_TINIB_sstk = 
#if !defined(USE_TSKINICTXB)
(offsetof(TINIB,sstk));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offsetof_TINIB_ustksz = 
#if !defined(USE_TSKINICTXB)
(offsetof(TINIB,ustksz));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offsetof_TINIB_ustk = 
#if !defined(USE_TSKINICTXB)
(offsetof(TINIB,ustk));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offsetof_TINIB_texatr = ( unsigned_t )offsetof(TINIB,texatr);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_texrtn = ( unsigned_t )offsetof(TINIB,texrtn);
const unsigned_t TOPPERS_cfg_sizeof_SEMINIB = ( unsigned_t )sizeof(SEMINIB);
const unsigned_t TOPPERS_cfg_offsetof_SEMINIB_sematr = ( unsigned_t )offsetof(SEMINIB,sematr);
const unsigned_t TOPPERS_cfg_offsetof_SEMINIB_isemcnt = ( unsigned_t )offsetof(SEMINIB,isemcnt);
const unsigned_t TOPPERS_cfg_offsetof_SEMINIB_maxsem = ( unsigned_t )offsetof(SEMINIB,maxsem);
const unsigned_t TOPPERS_cfg_sizeof_FLGPTN = ( unsigned_t )sizeof(FLGPTN);
const unsigned_t TOPPERS_cfg_sizeof_FLGINIB = ( unsigned_t )sizeof(FLGINIB);
const unsigned_t TOPPERS_cfg_offsetof_FLGINIB_flgatr = ( unsigned_t )offsetof(FLGINIB,flgatr);
const unsigned_t TOPPERS_cfg_offsetof_FLGINIB_iflgptn = ( unsigned_t )offsetof(FLGINIB,iflgptn);
const unsigned_t TOPPERS_cfg_sizeof_DTQINIB = ( unsigned_t )sizeof(DTQINIB);
const unsigned_t TOPPERS_cfg_offsetof_DTQINIB_dtqatr = ( unsigned_t )offsetof(DTQINIB,dtqatr);
const unsigned_t TOPPERS_cfg_offsetof_DTQINIB_dtqcnt = ( unsigned_t )offsetof(DTQINIB,dtqcnt);
const unsigned_t TOPPERS_cfg_offsetof_DTQINIB_p_dtqmb = ( unsigned_t )offsetof(DTQINIB,p_dtqmb);
const unsigned_t TOPPERS_cfg_sizeof_PDQINIB = ( unsigned_t )sizeof(PDQINIB);
const unsigned_t TOPPERS_cfg_offsetof_PDQINIB_pdqatr = ( unsigned_t )offsetof(PDQINIB,pdqatr);
const unsigned_t TOPPERS_cfg_offsetof_PDQINIB_pdqcnt = ( unsigned_t )offsetof(PDQINIB,pdqcnt);
const unsigned_t TOPPERS_cfg_offsetof_PDQINIB_maxdpri = ( unsigned_t )offsetof(PDQINIB,maxdpri);
const unsigned_t TOPPERS_cfg_offsetof_PDQINIB_p_pdqmb = ( unsigned_t )offsetof(PDQINIB,p_pdqmb);
const unsigned_t TOPPERS_cfg_sizeof_MTXINIB = ( unsigned_t )sizeof(MTXINIB);
const unsigned_t TOPPERS_cfg_offsetof_MTXINIB_mtxatr = ( unsigned_t )offsetof(MTXINIB,mtxatr);
const unsigned_t TOPPERS_cfg_offsetof_MTXINIB_ceilpri = ( unsigned_t )offsetof(MTXINIB,ceilpri);
const unsigned_t TOPPERS_cfg_sizeof_MPFINIB = ( unsigned_t )sizeof(MPFINIB);
const unsigned_t TOPPERS_cfg_offsetof_MPFINIB_mpfatr = ( unsigned_t )offsetof(MPFINIB,mpfatr);
const unsigned_t TOPPERS_cfg_offsetof_MPFINIB_blkcnt = ( unsigned_t )offsetof(MPFINIB,blkcnt);
const unsigned_t TOPPERS_cfg_offsetof_MPFINIB_blksz = ( unsigned_t )offsetof(MPFINIB,blksz);
const unsigned_t TOPPERS_cfg_offsetof_MPFINIB_mpf = ( unsigned_t )offsetof(MPFINIB,mpf);
const unsigned_t TOPPERS_cfg_offsetof_MPFINIB_p_mpfmb = ( unsigned_t )offsetof(MPFINIB,p_mpfmb);
const unsigned_t TOPPERS_cfg_sizeof_CYCINIB = ( unsigned_t )sizeof(CYCINIB);
const unsigned_t TOPPERS_cfg_offsetof_CYCINIB_cycatr = ( unsigned_t )offsetof(CYCINIB,cycatr);
const unsigned_t TOPPERS_cfg_offsetof_CYCINIB_exinf = ( unsigned_t )offsetof(CYCINIB,exinf);
const unsigned_t TOPPERS_cfg_offsetof_CYCINIB_cychdr = ( unsigned_t )offsetof(CYCINIB,cychdr);
const unsigned_t TOPPERS_cfg_offsetof_CYCINIB_cyctim = ( unsigned_t )offsetof(CYCINIB,cyctim);
const unsigned_t TOPPERS_cfg_offsetof_CYCINIB_cycphs = ( unsigned_t )offsetof(CYCINIB,cycphs);
const unsigned_t TOPPERS_cfg_sizeof_ALMINIB = ( unsigned_t )sizeof(ALMINIB);
const unsigned_t TOPPERS_cfg_offsetof_ALMINIB_almatr = ( unsigned_t )offsetof(ALMINIB,almatr);
const unsigned_t TOPPERS_cfg_offsetof_ALMINIB_exinf = ( unsigned_t )offsetof(ALMINIB,exinf);
const unsigned_t TOPPERS_cfg_offsetof_ALMINIB_almhdr = ( unsigned_t )offsetof(ALMINIB,almhdr);
const unsigned_t TOPPERS_cfg_sizeof_OVRINIB = 
#if defined(TOPPERS_SUPPORT_OVRHDR)
(sizeof(OVRINIB));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offsetof_OVRINIB_ovratr = 
#if defined(TOPPERS_SUPPORT_OVRHDR)
(offsetof(OVRINIB,ovratr));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offsetof_OVRINIB_ovrhdr = 
#if defined(TOPPERS_SUPPORT_OVRHDR)
(offsetof(OVRINIB,ovrhdr));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_sizeof_ISRINIB = ( unsigned_t )sizeof(ISRINIB);
const unsigned_t TOPPERS_cfg_offsetof_ISRINIB_isratr = ( unsigned_t )offsetof(ISRINIB,isratr);
const unsigned_t TOPPERS_cfg_offsetof_ISRINIB_exinf = ( unsigned_t )offsetof(ISRINIB,exinf);
const unsigned_t TOPPERS_cfg_offsetof_ISRINIB_intno = ( unsigned_t )offsetof(ISRINIB,intno);
const unsigned_t TOPPERS_cfg_offsetof_ISRINIB_p_isr_queue = ( unsigned_t )offsetof(ISRINIB,p_isr_queue);
const unsigned_t TOPPERS_cfg_offsetof_ISRINIB_isr = ( unsigned_t )offsetof(ISRINIB,isr);
const unsigned_t TOPPERS_cfg_offsetof_ISRINIB_isrpri = ( unsigned_t )offsetof(ISRINIB,isrpri);
const unsigned_t TOPPERS_cfg_sizeof_INHINIB = 
#if !defined(OMIT_INITIALIZE_INTERRUPT)
(sizeof(INHINIB));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offset_INHINIB_inhno = 
#if !defined(OMIT_INITIALIZE_INTERRUPT)
(offsetof(INHINIB,inhno));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offset_INHINIB_inhatr = 
#if !defined(OMIT_INITIALIZE_INTERRUPT)
(offsetof(INHINIB,inhatr));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offset_INHINIB_int_entry = 
#if !defined(OMIT_INITIALIZE_INTERRUPT)
(offsetof(INHINIB,int_entry));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_sizeof_INTINIB = 
#if !defined(OMIT_INITIALIZE_INTERRUPT)
(sizeof(INTINIB));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offset_INTINIB_intno = 
#if !defined(OMIT_INITIALIZE_INTERRUPT)
(offsetof(INTINIB,intno));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offset_INTINIB_intatr = 
#if !defined(OMIT_INITIALIZE_INTERRUPT)
(offsetof(INTINIB,intatr));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offset_INTINIB_intpri = 
#if !defined(OMIT_INITIALIZE_INTERRUPT)
(offsetof(INTINIB,intpri));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_sizeof_EXCINIB = 
#if !defined(OMIT_INITIALIZE_EXCEPTION)
(sizeof(EXCINIB));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offset_EXCINIB_excno = 
#if !defined(OMIT_INITIALIZE_EXCEPTION)
(offsetof(EXCINIB,excno));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offset_EXCINIB_excatr = 
#if !defined(OMIT_INITIALIZE_EXCEPTION)
(offsetof(EXCINIB,excatr));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offset_EXCINIB_exc_entry = 
#if !defined(OMIT_INITIALIZE_EXCEPTION)
(offsetof(EXCINIB,exc_entry));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_sizeof_SVCINIB = ( unsigned_t )sizeof(SVCINIB);
const unsigned_t TOPPERS_cfg_offsetof_SVCINIB_svcrtn = ( unsigned_t )offsetof(SVCINIB,svcrtn);
const unsigned_t TOPPERS_cfg_offsetof_SVCINIB_stksz = ( unsigned_t )offsetof(SVCINIB,stksz);
const unsigned_t TOPPERS_cfg_TMAX_INTNO = ( unsigned_t )TMAX_INTNO;
const unsigned_t TOPPERS_cfg_TMIN_INTNO = ( unsigned_t )TMIN_INTNO;
const unsigned_t TOPPERS_cfg_TMAX_INTPRI = ( unsigned_t )TMAX_INTPRI;
const unsigned_t TOPPERS_cfg_TA_SORDER = ( unsigned_t )TA_SORDER;
const unsigned_t TOPPERS_cfg_TA_WTHROUGH = ( unsigned_t )TA_WTHROUGH;
const unsigned_t TOPPERS_cfg_TA_NONSHARED = ( unsigned_t )TA_NONSHARED;
const unsigned_t TOPPERS_cfg_ARM_SSECTION_SIZE = ( unsigned_t )ARM_SSECTION_SIZE;
const unsigned_t TOPPERS_cfg_ARM_SECTION_SIZE = ( unsigned_t )ARM_SECTION_SIZE;
const unsigned_t TOPPERS_cfg_ARM_LPAGE_SIZE = ( unsigned_t )ARM_LPAGE_SIZE;
const unsigned_t TOPPERS_cfg_ARM_PAGE_SIZE = ( unsigned_t )ARM_PAGE_SIZE;
const unsigned_t TOPPERS_cfg_ARM_SECTION_TABLE_SIZE = ( unsigned_t )ARM_SECTION_TABLE_SIZE;
const unsigned_t TOPPERS_cfg_ARM_SECTION_TABLE_ALIGN = ( unsigned_t )ARM_SECTION_TABLE_ALIGN;
const unsigned_t TOPPERS_cfg_ARM_SECTION_TABLE_ENTRY = ( unsigned_t )ARM_SECTION_TABLE_ENTRY;
const unsigned_t TOPPERS_cfg_ARM_PAGE_TABLE_SIZE = ( unsigned_t )ARM_PAGE_TABLE_SIZE;
const unsigned_t TOPPERS_cfg_ARM_PAGE_TABLE_ALIGN = ( unsigned_t )ARM_PAGE_TABLE_ALIGN;
const unsigned_t TOPPERS_cfg_ARM_PAGE_TABLE_ENTRY = ( unsigned_t )ARM_PAGE_TABLE_ENTRY;
const unsigned_t TOPPERS_cfg_TOPPERS_MPCORE = 
#if defined(TOPPERS_MPCORE)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_sizeof_TCB = ( unsigned_t )sizeof(TCB);
const unsigned_t TOPPERS_cfg_offsetof_TCB_p_tinib = ( unsigned_t )offsetof(TCB,p_tinib);
const unsigned_t TOPPERS_cfg_offsetof_TCB_svclevel = ( unsigned_t )offsetof(TCB,svclevel);
const unsigned_t TOPPERS_cfg_offsetof_TCB_texptn = ( unsigned_t )offsetof(TCB,texptn);
const unsigned_t TOPPERS_cfg_offsetof_TCB_sp = ( unsigned_t )offsetof(TCB,tskctxb.sp);
const unsigned_t TOPPERS_cfg_offsetof_TCB_pc = ( unsigned_t )offsetof(TCB,tskctxb.pc);
const unsigned_t TOPPERS_cfg_offsetof_TCB_priv = ( unsigned_t )offsetof(TCB,tskctxb.priv);
const unsigned_t TOPPERS_cfg_offsetof_DOMINIB_domid = ( unsigned_t )offsetof(DOMINIB,domctxb.domid);
const unsigned_t TOPPERS_cfg_offsetof_DOMINIB_p_section_table = ( unsigned_t )offsetof(DOMINIB,domctxb.p_section_table);

#define TDOM_APP	1

/* #include "app.h" */
/* #include "csl.h" */

#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 3 "../../target/ev3_gcc/ev3.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL

#if TOPPERS_ENABLE_TRACE
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_0 = ( unsigned_t ) ( TDOM_KERNEL );
#line 6 "../../target/ev3_gcc/ev3.cfg"
const unsigned_t TOPPERS_cfg_static_api_0 = 0;
const unsigned_t TOPPERS_cfg_valueof_iniatr_0 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_1 = ( unsigned_t ) ( TDOM_KERNEL );
#line 7 "../../target/ev3_gcc/ev3.cfg"
const unsigned_t TOPPERS_cfg_static_api_1 = 1;
const unsigned_t TOPPERS_cfg_valueof_teratr_1 = ( unsigned_t )( TA_NULL ); 
#endif
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_2 = ( unsigned_t ) ( TDOM_KERNEL );
#line 13 "../../target/ev3_gcc/ev3.cfg"
const unsigned_t TOPPERS_cfg_static_api_2 = 2;
const unsigned_t TOPPERS_cfg_valueof_iniatr_2 = ( unsigned_t )( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 15 "../../target/ev3_gcc/ev3.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#line 6 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_3 = 3;
const char TOPPERS_cfg_valueof_region_3[] = "ROM"; const unsigned_t TOPPERS_cfg_valueof_regatr_3 = ( unsigned_t )( TA_NOWRITE ); const unsigned_t TOPPERS_cfg_valueof_base_3 = ( unsigned_t )( 0xC0008000 ); const unsigned_t TOPPERS_cfg_valueof_size_3 = ( unsigned_t )( 0x00100000 ); 
#line 7 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_4 = 4;
const char TOPPERS_cfg_valueof_region_4[] = "RAM"; const unsigned_t TOPPERS_cfg_valueof_regatr_4 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_base_4 = ( unsigned_t )( 0xC0108000 ); const unsigned_t TOPPERS_cfg_valueof_size_4 = ( unsigned_t )( 0x03EF8000 ); 
#line 8 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_5 = 5;
const char TOPPERS_cfg_valueof_stdrom_5[] = "ROM"; const char TOPPERS_cfg_valueof_stdram_5[] = "RAM"; 
#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 10 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL

#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 15 "../../target/ev3_gcc/target_mem.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 20 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_6 = ( unsigned_t ) ( TDOM_KERNEL );
#line 21 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_6 = 6;
const unsigned_t TOPPERS_cfg_valueof_mematr_6 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_6 = ( unsigned_t )( 0x00009000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_7 = ( unsigned_t ) ( TDOM_KERNEL );
#line 22 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_7 = 7;
const unsigned_t TOPPERS_cfg_valueof_mematr_7 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_7 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_8 = ( unsigned_t ) ( TDOM_KERNEL );
#line 23 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_8 = 8;
const unsigned_t TOPPERS_cfg_valueof_mematr_8 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_8 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_9 = ( unsigned_t ) ( TDOM_KERNEL );
#line 24 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_9 = 9;
const unsigned_t TOPPERS_cfg_valueof_mematr_9 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_9 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_10 = ( unsigned_t ) ( TDOM_KERNEL );
#line 25 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_10 = 10;
const unsigned_t TOPPERS_cfg_valueof_mematr_10 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_10 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_11 = ( unsigned_t ) ( TDOM_KERNEL );
#line 26 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_11 = 11;
const unsigned_t TOPPERS_cfg_valueof_mematr_11 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_11 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_12 = ( unsigned_t ) ( TDOM_KERNEL );
#line 27 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_12 = 12;
const unsigned_t TOPPERS_cfg_valueof_mematr_12 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_12 = ( unsigned_t )( 0x00010000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_13 = ( unsigned_t ) ( TDOM_KERNEL );
#line 28 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_13 = 13;
const unsigned_t TOPPERS_cfg_valueof_mematr_13 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_13 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_14 = ( unsigned_t ) ( TDOM_KERNEL );
#line 29 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_14 = 14;
const unsigned_t TOPPERS_cfg_valueof_mematr_14 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_14 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_15 = ( unsigned_t ) ( TDOM_KERNEL );
#line 30 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_15 = 15;
const unsigned_t TOPPERS_cfg_valueof_mematr_15 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_15 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_16 = ( unsigned_t ) ( TDOM_KERNEL );
#line 31 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_16 = 16;
const unsigned_t TOPPERS_cfg_valueof_mematr_16 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_16 = ( unsigned_t )( 0x00003000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_17 = ( unsigned_t ) ( TDOM_KERNEL );
#line 32 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_17 = 17;
const unsigned_t TOPPERS_cfg_valueof_mematr_17 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_17 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_18 = ( unsigned_t ) ( TDOM_KERNEL );
#line 33 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_18 = 18;
const unsigned_t TOPPERS_cfg_valueof_mematr_18 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_18 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_19 = ( unsigned_t ) ( TDOM_KERNEL );
#line 34 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_19 = 19;
const unsigned_t TOPPERS_cfg_valueof_mematr_19 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_19 = ( unsigned_t )( 0x00010000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_20 = ( unsigned_t ) ( TDOM_KERNEL );
#line 35 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_20 = 20;
const unsigned_t TOPPERS_cfg_valueof_mematr_20 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_20 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_21 = ( unsigned_t ) ( TDOM_KERNEL );
#line 36 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_21 = 21;
const unsigned_t TOPPERS_cfg_valueof_mematr_21 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_21 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_22 = ( unsigned_t ) ( TDOM_KERNEL );
#line 37 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_22 = 22;
const unsigned_t TOPPERS_cfg_valueof_mematr_22 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_22 = ( unsigned_t )( 0x00009000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_23 = ( unsigned_t ) ( TDOM_KERNEL );
#line 38 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_23 = 23;
const unsigned_t TOPPERS_cfg_valueof_mematr_23 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_23 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_24 = ( unsigned_t ) ( TDOM_KERNEL );
#line 39 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_24 = 24;
const unsigned_t TOPPERS_cfg_valueof_mematr_24 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_24 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_25 = ( unsigned_t ) ( TDOM_KERNEL );
#line 40 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_25 = 25;
const unsigned_t TOPPERS_cfg_valueof_mematr_25 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_25 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_26 = ( unsigned_t ) ( TDOM_KERNEL );
#line 41 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_26 = 26;
const unsigned_t TOPPERS_cfg_valueof_mematr_26 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_26 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_27 = ( unsigned_t ) ( TDOM_KERNEL );
#line 42 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_27 = 27;
const unsigned_t TOPPERS_cfg_valueof_mematr_27 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_27 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_28 = ( unsigned_t ) ( TDOM_KERNEL );
#line 43 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_28 = 28;
const unsigned_t TOPPERS_cfg_valueof_mematr_28 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_28 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_29 = ( unsigned_t ) ( TDOM_KERNEL );
#line 44 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_29 = 29;
const unsigned_t TOPPERS_cfg_valueof_mematr_29 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_29 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_30 = ( unsigned_t ) ( TDOM_KERNEL );
#line 45 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_30 = 30;
const unsigned_t TOPPERS_cfg_valueof_mematr_30 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_30 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_31 = ( unsigned_t ) ( TDOM_KERNEL );
#line 46 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_31 = 31;
const unsigned_t TOPPERS_cfg_valueof_mematr_31 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_31 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_32 = ( unsigned_t ) ( TDOM_KERNEL );
#line 47 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_32 = 32;
const unsigned_t TOPPERS_cfg_valueof_mematr_32 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_32 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_33 = ( unsigned_t ) ( TDOM_KERNEL );
#line 48 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_33 = 33;
const unsigned_t TOPPERS_cfg_valueof_mematr_33 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_33 = ( unsigned_t )( 0x00001000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_34 = ( unsigned_t ) ( TDOM_KERNEL );
#line 50 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_34 = 34;
const unsigned_t TOPPERS_cfg_valueof_mematr_34 = ( unsigned_t )( TA_NOWRITE|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_34 = ( unsigned_t )( 0x0000C000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_35 = ( unsigned_t ) ( TDOM_KERNEL );
#line 52 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_35 = 35;
const unsigned_t TOPPERS_cfg_valueof_mematr_35 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_35 = ( unsigned_t )( 0x00020000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_36 = ( unsigned_t ) ( TDOM_KERNEL );
#line 54 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_36 = 36;
const unsigned_t TOPPERS_cfg_valueof_mematr_36 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_36 = ( unsigned_t )( 0x00002000 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_37 = ( unsigned_t ) ( TDOM_KERNEL );
#line 56 "../../target/ev3_gcc/target_mem.cfg"
const unsigned_t TOPPERS_cfg_static_api_37 = 37;
const unsigned_t TOPPERS_cfg_valueof_mematr_37 = ( unsigned_t )( TA_IODEV|TA_MEMPRSV ); const unsigned_t TOPPERS_cfg_valueof_size_37 = ( unsigned_t )( 0x00002000 ); 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 58 "../../target/ev3_gcc/target_mem.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#if 0 

#endif
/* #include "chip_timer.h" */

#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 8 "../../arch/arm_gcc/am1808/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_38 = ( unsigned_t ) ( TDOM_KERNEL );
#line 11 "../../arch/arm_gcc/am1808/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_38 = 38;
const unsigned_t TOPPERS_cfg_valueof_iniatr_38 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_39 = ( unsigned_t ) ( TDOM_KERNEL );
#line 12 "../../arch/arm_gcc/am1808/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_39 = 39;
const unsigned_t TOPPERS_cfg_valueof_teratr_39 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_40 = ( unsigned_t ) ( TDOM_KERNEL );
#line 13 "../../arch/arm_gcc/am1808/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_40 = 40;
const unsigned_t TOPPERS_cfg_valueof_intno_40 = ( unsigned_t )( INTNO_TIMER ); const unsigned_t TOPPERS_cfg_valueof_intatr_40 = ( unsigned_t )( TA_ENAINT|INTATR_TIMER ); const signed_t TOPPERS_cfg_valueof_intpri_40 = ( signed_t )( INTPRI_TIMER ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_41 = ( unsigned_t ) ( TDOM_KERNEL );
#line 14 "../../arch/arm_gcc/am1808/chip_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_41 = 41;
const unsigned_t TOPPERS_cfg_valueof_isratr_41 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_intno_41 = ( unsigned_t )( INTNO_TIMER ); const signed_t TOPPERS_cfg_valueof_isrpri_41 = ( signed_t )( TMIN_ISRPRI ); 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 25 "../../arch/arm_gcc/am1808/chip_timer.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL

/* #include "syssvc/syslog.h" */

#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 11 "../../syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_42 = ( unsigned_t ) ( TDOM_KERNEL );
#line 12 "../../syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_static_api_42 = 42;
const unsigned_t TOPPERS_cfg_valueof_iniatr_42 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_43 = ( unsigned_t ) ( TDOM_KERNEL );
#line 13 "../../syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_static_api_43 = 43;
const char TOPPERS_cfg_valueof_module_43[] = "syslog.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_44 = ( unsigned_t ) ( TDOM_KERNEL );
#line 15 "../../syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_static_api_44 = 44;
const unsigned_t TOPPERS_cfg_valueof_fncd_44 = ( unsigned_t )( TFN_SYSLOG_WRI_LOG ); const unsigned_t TOPPERS_cfg_valueof_svcatr_44 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_44 = ( unsigned_t )( SSZ_SYSLOG_WRI_LOG ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_45 = ( unsigned_t ) ( TDOM_KERNEL );
#line 17 "../../syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_static_api_45 = 45;
const unsigned_t TOPPERS_cfg_valueof_fncd_45 = ( unsigned_t )( TFN_SYSLOG_FWRI_LOG ); const unsigned_t TOPPERS_cfg_valueof_svcatr_45 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_45 = ( unsigned_t )( 0 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_46 = ( unsigned_t ) ( TDOM_KERNEL );
#line 18 "../../syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_static_api_46 = 46;
const unsigned_t TOPPERS_cfg_valueof_fncd_46 = ( unsigned_t )( TFN_SYSLOG_REA_LOG ); const unsigned_t TOPPERS_cfg_valueof_svcatr_46 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_46 = ( unsigned_t )( SSZ_SYSLOG_REA_LOG ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_47 = ( unsigned_t ) ( TDOM_KERNEL );
#line 20 "../../syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_static_api_47 = 47;
const unsigned_t TOPPERS_cfg_valueof_fncd_47 = ( unsigned_t )( TFN_SYSLOG_MSK_LOG ); const unsigned_t TOPPERS_cfg_valueof_svcatr_47 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_47 = ( unsigned_t )( SSZ_SYSLOG_MSK_LOG ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_48 = ( unsigned_t ) ( TDOM_KERNEL );
#line 22 "../../syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_static_api_48 = 48;
const unsigned_t TOPPERS_cfg_valueof_fncd_48 = ( unsigned_t )( TFN_SYSLOG_REF_LOG ); const unsigned_t TOPPERS_cfg_valueof_svcatr_48 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_48 = ( unsigned_t )( SSZ_SYSLOG_REF_LOG ); 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 24 "../../syssvc/syslog.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL

/* #include "syssvc/banner.h" */

#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 11 "../../syssvc/banner.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_49 = ( unsigned_t ) ( TDOM_KERNEL );
#line 12 "../../syssvc/banner.cfg"
const unsigned_t TOPPERS_cfg_static_api_49 = 49;
const unsigned_t TOPPERS_cfg_valueof_iniatr_49 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_50 = ( unsigned_t ) ( TDOM_KERNEL );
#line 13 "../../syssvc/banner.cfg"
const unsigned_t TOPPERS_cfg_static_api_50 = 50;
const char TOPPERS_cfg_valueof_module_50[] = "banner.o"; 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 14 "../../syssvc/banner.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL

/* #include "target_serial.h" */
/* #include "target_serial_dbsio.h" */

#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 8 "../../target/ev3_gcc/target_serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL

#if defined(BUILD_EV3_PLATFORM)
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_51 = ( unsigned_t ) ( TDOM_KERNEL );
#line 11 "../../target/ev3_gcc/target_serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_51 = 51;
#define BT_SIO_CYC	(<>)

#line 11 "../../target/ev3_gcc/target_serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_cycatr_51 = ( unsigned_t )( TA_STA ); const unsigned_t TOPPERS_cfg_valueof_cyctim_51 = ( unsigned_t )( 5 ); const unsigned_t TOPPERS_cfg_valueof_cycphs_51 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_52 = ( unsigned_t ) ( TDOM_KERNEL );
#line 12 "../../target/ev3_gcc/target_serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_52 = 52;
#define DBSIO_TEST_SPP_MASTER_SIO_CYC	(<>)

#line 12 "../../target/ev3_gcc/target_serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_cycatr_52 = ( unsigned_t )( TA_STA ); const unsigned_t TOPPERS_cfg_valueof_cyctim_52 = ( unsigned_t )( 5 ); const unsigned_t TOPPERS_cfg_valueof_cycphs_52 = ( unsigned_t )( 1 ); 
#endif

#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 15 "../../target/ev3_gcc/target_serial.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL

/* #include "syssvc/serial.h" */

#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 13 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_53 = ( unsigned_t ) ( TDOM_KERNEL );
#line 14 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_53 = 53;
const unsigned_t TOPPERS_cfg_valueof_iniatr_53 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_54 = ( unsigned_t ) ( TDOM_KERNEL );
#line 15 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_54 = 54;
const char TOPPERS_cfg_valueof_module_54[] = "serial.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_55 = ( unsigned_t ) ( TDOM_KERNEL );
#line 17 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_55 = 55;
const unsigned_t TOPPERS_cfg_valueof_fncd_55 = ( unsigned_t )( TFN_SERIAL_OPN_POR ); const unsigned_t TOPPERS_cfg_valueof_svcatr_55 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_55 = ( unsigned_t )( SSZ_SERIAL_OPN_POR ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_56 = ( unsigned_t ) ( TDOM_KERNEL );
#line 19 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_56 = 56;
const unsigned_t TOPPERS_cfg_valueof_fncd_56 = ( unsigned_t )( TFN_SERIAL_CLS_POR ); const unsigned_t TOPPERS_cfg_valueof_svcatr_56 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_56 = ( unsigned_t )( SSZ_SERIAL_CLS_POR ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_57 = ( unsigned_t ) ( TDOM_KERNEL );
#line 21 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_57 = 57;
const unsigned_t TOPPERS_cfg_valueof_fncd_57 = ( unsigned_t )( TFN_SERIAL_REA_DAT ); const unsigned_t TOPPERS_cfg_valueof_svcatr_57 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_57 = ( unsigned_t )( SSZ_SERIAL_REA_DAT ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_58 = ( unsigned_t ) ( TDOM_KERNEL );
#line 23 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_58 = 58;
const unsigned_t TOPPERS_cfg_valueof_fncd_58 = ( unsigned_t )( TFN_SERIAL_WRI_DAT ); const unsigned_t TOPPERS_cfg_valueof_svcatr_58 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_58 = ( unsigned_t )( SSZ_SERIAL_WRI_DAT ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_59 = ( unsigned_t ) ( TDOM_KERNEL );
#line 25 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_59 = 59;
const unsigned_t TOPPERS_cfg_valueof_fncd_59 = ( unsigned_t )( TFN_SERIAL_CTL_POR ); const unsigned_t TOPPERS_cfg_valueof_svcatr_59 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_59 = ( unsigned_t )( SSZ_SERIAL_CTL_POR ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_60 = ( unsigned_t ) ( TDOM_KERNEL );
#line 27 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_60 = 60;
const unsigned_t TOPPERS_cfg_valueof_fncd_60 = ( unsigned_t )( TFN_SERIAL_REF_POR ); const unsigned_t TOPPERS_cfg_valueof_svcatr_60 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_60 = ( unsigned_t )( SSZ_SERIAL_REF_POR ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_61 = ( unsigned_t ) ( TDOM_KERNEL );
#line 30 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_61 = 61;
#define SERIAL_RCV_SEM1	(<>)

#line 30 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_61 = ( unsigned_t )( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_61 = ( unsigned_t )( 0 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_61 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_62 = ( unsigned_t ) ( TDOM_KERNEL );
#line 31 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_62 = 62;
#define SERIAL_SND_SEM1	(<>)

#line 31 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_62 = ( unsigned_t )( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_62 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_62 = ( unsigned_t )( 1 ); 
#if TNUM_PORT >= 2
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_63 = ( unsigned_t ) ( TDOM_KERNEL );
#line 33 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_63 = 63;
#define SERIAL_RCV_SEM2	(<>)

#line 33 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_63 = ( unsigned_t )( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_63 = ( unsigned_t )( 0 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_63 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_64 = ( unsigned_t ) ( TDOM_KERNEL );
#line 34 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_64 = 64;
#define SERIAL_SND_SEM2	(<>)

#line 34 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_64 = ( unsigned_t )( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_64 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_64 = ( unsigned_t )( 1 ); 
#endif 

#if TNUM_PORT >= 3
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_65 = ( unsigned_t ) ( TDOM_KERNEL );
#line 37 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_65 = 65;
#define SERIAL_RCV_SEM3	(<>)

#line 37 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_65 = ( unsigned_t )( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_65 = ( unsigned_t )( 0 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_65 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_66 = ( unsigned_t ) ( TDOM_KERNEL );
#line 38 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_66 = 66;
#define SERIAL_SND_SEM3	(<>)

#line 38 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_66 = ( unsigned_t )( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_66 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_66 = ( unsigned_t )( 1 ); 
#endif 

#if TNUM_PORT >= 4
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_67 = ( unsigned_t ) ( TDOM_KERNEL );
#line 41 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_67 = 67;
#define SERIAL_RCV_SEM4	(<>)

#line 41 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_67 = ( unsigned_t )( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_67 = ( unsigned_t )( 0 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_67 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_68 = ( unsigned_t ) ( TDOM_KERNEL );
#line 42 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_68 = 68;
#define SERIAL_SND_SEM4	(<>)

#line 42 "../../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_68 = ( unsigned_t )( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_68 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_68 = ( unsigned_t )( 1 ); 
#endif 

#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 44 "../../syssvc/serial.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL

/* #include "syssvc/logtask.h" */

#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 11 "../../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_69 = ( unsigned_t ) ( TDOM_KERNEL );
#line 12 "../../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_static_api_69 = 69;
#define LOGTASK	(<>)

#line 12 "../../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_69 = ( unsigned_t )( TA_ACT ); const signed_t TOPPERS_cfg_valueof_itskpri_69 = ( signed_t )( LOGTASK_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_69 = ( unsigned_t )( LOGTASK_STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_70 = ( unsigned_t ) ( TDOM_KERNEL );
#line 14 "../../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_static_api_70 = 70;
const unsigned_t TOPPERS_cfg_valueof_teratr_70 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_71 = ( unsigned_t ) ( TDOM_KERNEL );
#line 15 "../../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_static_api_71 = 71;
const char TOPPERS_cfg_valueof_module_71[] = "logtask.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_72 = ( unsigned_t ) ( TDOM_KERNEL );
#line 17 "../../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_static_api_72 = 72;
const unsigned_t TOPPERS_cfg_valueof_fncd_72 = ( unsigned_t )( TFN_LOGTASK_FLUSH ); const unsigned_t TOPPERS_cfg_valueof_svcatr_72 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_72 = ( unsigned_t )( SSZ_LOGTASK_FLUSH ); 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 19 "../../syssvc/logtask.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 5 "../../target/ev3_gcc/drivers/common/driver_common.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_73 = ( unsigned_t ) ( TDOM_KERNEL );
#line 10 "../../target/ev3_gcc/drivers/common/driver_common.cfg"
const unsigned_t TOPPERS_cfg_static_api_73 = 73;
const unsigned_t TOPPERS_cfg_valueof_isratr_73 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_intno_73 = ( unsigned_t )( INTNO_TIMER ); const signed_t TOPPERS_cfg_valueof_isrpri_73 = ( signed_t )( TMIN_ISRPRI ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_74 = ( unsigned_t ) ( TDOM_KERNEL );
#line 11 "../../target/ev3_gcc/drivers/common/driver_common.cfg"
const unsigned_t TOPPERS_cfg_static_api_74 = 74;
const unsigned_t TOPPERS_cfg_valueof_isratr_74 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_intno_74 = ( unsigned_t )( INTNO_TIMER ); const signed_t TOPPERS_cfg_valueof_isrpri_74 = ( signed_t )( TMIN_ISRPRI ); 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 13 "../../target/ev3_gcc/drivers/common/driver_common.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#if 0 

#line 16 "../../target/ev3_gcc/drivers/common/driver_common.cfg"
const unsigned_t TOPPERS_cfg_static_api_75 = 75;
const unsigned_t TOPPERS_cfg_valueof_fncd_75 = ( unsigned_t )( TFN_DRIVER_DATA_POINTER ); const unsigned_t TOPPERS_cfg_valueof_svcatr_75 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_75 = ( unsigned_t )( 1024 ); 
#line 17 "../../target/ev3_gcc/drivers/common/driver_common.cfg"
const unsigned_t TOPPERS_cfg_static_api_76 = 76;
const unsigned_t TOPPERS_cfg_valueof_fncd_76 = ( unsigned_t )( TFN_HEAP_FOR_DOMAIN ); const unsigned_t TOPPERS_cfg_valueof_svcatr_76 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_76 = ( unsigned_t )( 1024 ); 
#line 19 "../../target/ev3_gcc/drivers/common/driver_common.cfg"
const unsigned_t TOPPERS_cfg_static_api_77 = 77;
const unsigned_t TOPPERS_cfg_valueof_iniatr_77 = ( unsigned_t )( TA_NULL ); 
#line 21 "../../target/ev3_gcc/drivers/common/driver_common.cfg"
const unsigned_t TOPPERS_cfg_static_api_78 = 78;
const char TOPPERS_cfg_valueof_module_78[] = "driver_common.o"; const unsigned_t TOPPERS_cfg_valueof_acptn1_78 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn2_78 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn3_78 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn4_78 = ( unsigned_t )( TACP_KERNEL ); 
#line 23 "../../target/ev3_gcc/drivers/common/driver_common.cfg"
const unsigned_t TOPPERS_cfg_static_api_79 = 79;
const char TOPPERS_cfg_valueof_section_79[] = ".appheap"; const unsigned_t TOPPERS_cfg_valueof_mematr_79 = ( unsigned_t )( TA_NULL ); const char TOPPERS_cfg_valueof_memreg_79[] = "RAM"; const unsigned_t TOPPERS_cfg_valueof_acptn1_79 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn2_79 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn3_79 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn4_79 = ( unsigned_t )( TACP_SHARED ); 
#endif

#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 4 "../../target/ev3_gcc/drivers/brick/brick_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_80 = ( unsigned_t ) ( TDOM_KERNEL );
#line 6 "../../target/ev3_gcc/drivers/brick/brick_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_80 = 80;
const unsigned_t TOPPERS_cfg_valueof_iniatr_80 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_81 = ( unsigned_t ) ( TDOM_KERNEL );
#line 8 "../../target/ev3_gcc/drivers/brick/brick_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_81 = 81;
const char TOPPERS_cfg_valueof_module_81[] = "brick_dri.o"; const unsigned_t TOPPERS_cfg_valueof_acptn1_81 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn2_81 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn3_81 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn4_81 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_82 = ( unsigned_t ) ( TDOM_KERNEL );
#line 10 "../../target/ev3_gcc/drivers/brick/brick_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_82 = 82;
const char TOPPERS_cfg_valueof_section_82[] = ".appheap"; const unsigned_t TOPPERS_cfg_valueof_mematr_82 = ( unsigned_t )( TA_NULL ); const char TOPPERS_cfg_valueof_memreg_82[] = "RAM"; const unsigned_t TOPPERS_cfg_valueof_acptn1_82 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn2_82 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn3_82 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn4_82 = ( unsigned_t )( TACP_SHARED ); 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 12 "../../target/ev3_gcc/drivers/brick/brick_dri.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#line 17 "../../target/ev3_gcc/drivers/brick/brick_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_83 = 83;
#define BTN_CLICK_FLG	(<>)

#line 17 "../../target/ev3_gcc/drivers/brick/brick_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_flgatr_83 = ( unsigned_t )( TA_CLR ); const unsigned_t TOPPERS_cfg_valueof_iflgptn_83 = ( unsigned_t )( 0 ); 
#line 18 "../../target/ev3_gcc/drivers/brick/brick_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_84 = 84;
const unsigned_t TOPPERS_cfg_valueof_acptn1_84 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn2_84 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn3_84 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn4_84 = ( unsigned_t )( TACP_KERNEL ); 
#ifndef TOPPERS_cfg_valueof_TDOM_APP_DEFINED
#define TOPPERS_cfg_valueof_TDOM_APP_DEFINED 1

#line 19 "../../target/ev3_gcc/drivers/brick/brick_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_APP = TDOM_APP;

#endif
#define TOPPERS_cfg_inside_of_TDOM_APP
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_85 = ( unsigned_t ) ( TDOM_APP );
#line 20 "../../target/ev3_gcc/drivers/brick/brick_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_85 = 85;
#define BRICK_BTN_TSK	(<>)

#line 20 "../../target/ev3_gcc/drivers/brick/brick_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_85 = ( unsigned_t )( TA_NULL ); const signed_t TOPPERS_cfg_valueof_itskpri_85 = ( signed_t )( TMIN_APP_TPRI ); const unsigned_t TOPPERS_cfg_valueof_stksz_85 = ( unsigned_t )( STACK_SIZE ); 
#ifndef TOPPERS_cfg_inside_of_TDOM_APP

#line 21 "../../target/ev3_gcc/drivers/brick/brick_dri.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_APP


#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 22 "../../target/ev3_gcc/drivers/brick/brick_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_86 = ( unsigned_t ) ( TDOM_KERNEL );
#line 23 "../../target/ev3_gcc/drivers/brick/brick_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_86 = 86;
#define BRICK_BTN_CYC	(<>)

#line 23 "../../target/ev3_gcc/drivers/brick/brick_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_cycatr_86 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_cyctim_86 = ( unsigned_t )( 10 ); const unsigned_t TOPPERS_cfg_valueof_cycphs_86 = ( unsigned_t )( 0 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_87 = ( unsigned_t ) ( TDOM_KERNEL );
#line 24 "../../target/ev3_gcc/drivers/brick/brick_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_87 = 87;
#define CONSOLE_BTN_CLICK_FLG	(<>)

#line 24 "../../target/ev3_gcc/drivers/brick/brick_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_flgatr_87 = ( unsigned_t )( TA_CLR ); const unsigned_t TOPPERS_cfg_valueof_iflgptn_87 = ( unsigned_t )( 0 ); 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 25 "../../target/ev3_gcc/drivers/brick/brick_dri.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#if 0 

#line 28 "../../target/ev3_gcc/drivers/brick/brick_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_88 = 88;
const unsigned_t TOPPERS_cfg_valueof_fncd_88 = ( unsigned_t )( TFN_DRIVER_DATA_POINTER ); const unsigned_t TOPPERS_cfg_valueof_svcatr_88 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_88 = ( unsigned_t )( 1024 ); 
#line 29 "../../target/ev3_gcc/drivers/brick/brick_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_89 = 89;
const unsigned_t TOPPERS_cfg_valueof_fncd_89 = ( unsigned_t )( TFN_HEAP_FOR_DOMAIN ); const unsigned_t TOPPERS_cfg_valueof_svcatr_89 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_89 = ( unsigned_t )( 1024 ); 
#endif

#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 4 "../../target/ev3_gcc/drivers/fatfs/fatfs.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_90 = ( unsigned_t ) ( TDOM_KERNEL );
#line 11 "../../target/ev3_gcc/drivers/fatfs/fatfs.cfg"
const unsigned_t TOPPERS_cfg_static_api_90 = 90;
#define MMCSD_MOD_SEM	(<>)

#line 11 "../../target/ev3_gcc/drivers/fatfs/fatfs.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_90 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_90 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_90 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_91 = ( unsigned_t ) ( TDOM_KERNEL );
#line 16 "../../target/ev3_gcc/drivers/fatfs/fatfs.cfg"
const unsigned_t TOPPERS_cfg_static_api_91 = 91;
#define FATFS_SEM	(<>)

#line 16 "../../target/ev3_gcc/drivers/fatfs/fatfs.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_91 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_91 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_91 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_92 = ( unsigned_t ) ( TDOM_KERNEL );
#line 17 "../../target/ev3_gcc/drivers/fatfs/fatfs.cfg"
const unsigned_t TOPPERS_cfg_static_api_92 = 92;
#define DISKIO_MTX	(<>)

#line 17 "../../target/ev3_gcc/drivers/fatfs/fatfs.cfg"
const unsigned_t TOPPERS_cfg_valueof_mtxatr_92 = ( unsigned_t )( TA_NULL ); const signed_t TOPPERS_cfg_valueof_ceilpri_92 = ( signed_t )( 0 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_93 = ( unsigned_t ) ( TDOM_KERNEL );
#line 22 "../../target/ev3_gcc/drivers/fatfs/fatfs.cfg"
const unsigned_t TOPPERS_cfg_static_api_93 = 93;
const char TOPPERS_cfg_valueof_module_93[] = "fatfs_dri.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_94 = ( unsigned_t ) ( TDOM_KERNEL );
#line 23 "../../target/ev3_gcc/drivers/fatfs/fatfs.cfg"
const unsigned_t TOPPERS_cfg_static_api_94 = 94;
const char TOPPERS_cfg_valueof_module_94[] = "fatfs_syscall.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_95 = ( unsigned_t ) ( TDOM_KERNEL );
#line 24 "../../target/ev3_gcc/drivers/fatfs/fatfs.cfg"
const unsigned_t TOPPERS_cfg_static_api_95 = 95;
const char TOPPERS_cfg_valueof_module_95[] = "diskio.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_96 = ( unsigned_t ) ( TDOM_KERNEL );
#line 25 "../../target/ev3_gcc/drivers/fatfs/fatfs.cfg"
const unsigned_t TOPPERS_cfg_static_api_96 = 96;
const char TOPPERS_cfg_valueof_module_96[] = "ff.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_97 = ( unsigned_t ) ( TDOM_KERNEL );
#line 26 "../../target/ev3_gcc/drivers/fatfs/fatfs.cfg"
const unsigned_t TOPPERS_cfg_static_api_97 = 97;
const char TOPPERS_cfg_valueof_module_97[] = "mmcsd.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_98 = ( unsigned_t ) ( TDOM_KERNEL );
#line 27 "../../target/ev3_gcc/drivers/fatfs/fatfs.cfg"
const unsigned_t TOPPERS_cfg_static_api_98 = 98;
const char TOPPERS_cfg_valueof_module_98[] = "mmcsdlib.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_99 = ( unsigned_t ) ( TDOM_KERNEL );
#line 28 "../../target/ev3_gcc/drivers/fatfs/fatfs.cfg"
const unsigned_t TOPPERS_cfg_static_api_99 = 99;
const char TOPPERS_cfg_valueof_module_99[] = "mmcsd_dri.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_100 = ( unsigned_t ) ( TDOM_KERNEL );
#line 29 "../../target/ev3_gcc/drivers/fatfs/fatfs.cfg"
const unsigned_t TOPPERS_cfg_static_api_100 = 100;
const char TOPPERS_cfg_valueof_module_100[] = "mmcsd_proto.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_101 = ( unsigned_t ) ( TDOM_KERNEL );
#line 30 "../../target/ev3_gcc/drivers/fatfs/fatfs.cfg"
const unsigned_t TOPPERS_cfg_static_api_101 = 101;
const char TOPPERS_cfg_valueof_module_101[] = "mmcsd_rw.o"; 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 32 "../../target/ev3_gcc/drivers/fatfs/fatfs.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 5 "../../target/ev3_gcc/drivers/gpio/gpio_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_102 = ( unsigned_t ) ( TDOM_KERNEL );
#line 8 "../../target/ev3_gcc/drivers/gpio/gpio_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_102 = 102;
const unsigned_t TOPPERS_cfg_valueof_intno_102 = ( unsigned_t )( GPIO_B0INT ); const unsigned_t TOPPERS_cfg_valueof_intatr_102 = ( unsigned_t )( TA_ENAINT ); const signed_t TOPPERS_cfg_valueof_intpri_102 = ( signed_t )( TMIN_INTPRI ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_103 = ( unsigned_t ) ( TDOM_KERNEL );
#line 9 "../../target/ev3_gcc/drivers/gpio/gpio_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_103 = 103;
const unsigned_t TOPPERS_cfg_valueof_intno_103 = ( unsigned_t )( GPIO_B1INT ); const unsigned_t TOPPERS_cfg_valueof_intatr_103 = ( unsigned_t )( TA_ENAINT ); const signed_t TOPPERS_cfg_valueof_intpri_103 = ( signed_t )( TMIN_INTPRI ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_104 = ( unsigned_t ) ( TDOM_KERNEL );
#line 10 "../../target/ev3_gcc/drivers/gpio/gpio_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_104 = 104;
const unsigned_t TOPPERS_cfg_valueof_intno_104 = ( unsigned_t )( GPIO_B2INT ); const unsigned_t TOPPERS_cfg_valueof_intatr_104 = ( unsigned_t )( TA_ENAINT ); const signed_t TOPPERS_cfg_valueof_intpri_104 = ( signed_t )( TMIN_INTPRI ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_105 = ( unsigned_t ) ( TDOM_KERNEL );
#line 11 "../../target/ev3_gcc/drivers/gpio/gpio_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_105 = 105;
const unsigned_t TOPPERS_cfg_valueof_intno_105 = ( unsigned_t )( GPIO_B3INT ); const unsigned_t TOPPERS_cfg_valueof_intatr_105 = ( unsigned_t )( TA_ENAINT ); const signed_t TOPPERS_cfg_valueof_intpri_105 = ( signed_t )( TMIN_INTPRI ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_106 = ( unsigned_t ) ( TDOM_KERNEL );
#line 12 "../../target/ev3_gcc/drivers/gpio/gpio_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_106 = 106;
const unsigned_t TOPPERS_cfg_valueof_intno_106 = ( unsigned_t )( GPIO_B4INT ); const unsigned_t TOPPERS_cfg_valueof_intatr_106 = ( unsigned_t )( TA_ENAINT ); const signed_t TOPPERS_cfg_valueof_intpri_106 = ( signed_t )( TMIN_INTPRI ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_107 = ( unsigned_t ) ( TDOM_KERNEL );
#line 13 "../../target/ev3_gcc/drivers/gpio/gpio_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_107 = 107;
const unsigned_t TOPPERS_cfg_valueof_intno_107 = ( unsigned_t )( GPIO_B5INT ); const unsigned_t TOPPERS_cfg_valueof_intatr_107 = ( unsigned_t )( TA_ENAINT ); const signed_t TOPPERS_cfg_valueof_intpri_107 = ( signed_t )( TMIN_INTPRI ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_108 = ( unsigned_t ) ( TDOM_KERNEL );
#line 14 "../../target/ev3_gcc/drivers/gpio/gpio_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_108 = 108;
const unsigned_t TOPPERS_cfg_valueof_intno_108 = ( unsigned_t )( GPIO_B6INT ); const unsigned_t TOPPERS_cfg_valueof_intatr_108 = ( unsigned_t )( TA_ENAINT ); const signed_t TOPPERS_cfg_valueof_intpri_108 = ( signed_t )( TMIN_INTPRI ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_109 = ( unsigned_t ) ( TDOM_KERNEL );
#line 15 "../../target/ev3_gcc/drivers/gpio/gpio_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_109 = 109;
const unsigned_t TOPPERS_cfg_valueof_intno_109 = ( unsigned_t )( GPIO_B7INT ); const unsigned_t TOPPERS_cfg_valueof_intatr_109 = ( unsigned_t )( TA_ENAINT ); const signed_t TOPPERS_cfg_valueof_intpri_109 = ( signed_t )( TMIN_INTPRI ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_110 = ( unsigned_t ) ( TDOM_KERNEL );
#line 16 "../../target/ev3_gcc/drivers/gpio/gpio_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_110 = 110;
const unsigned_t TOPPERS_cfg_valueof_intno_110 = ( unsigned_t )( GPIO_B8INT ); const unsigned_t TOPPERS_cfg_valueof_intatr_110 = ( unsigned_t )( TA_ENAINT ); const signed_t TOPPERS_cfg_valueof_intpri_110 = ( signed_t )( TMIN_INTPRI ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_111 = ( unsigned_t ) ( TDOM_KERNEL );
#line 17 "../../target/ev3_gcc/drivers/gpio/gpio_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_111 = 111;
const unsigned_t TOPPERS_cfg_valueof_isratr_111 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_intno_111 = ( unsigned_t )( GPIO_B0INT ); const signed_t TOPPERS_cfg_valueof_isrpri_111 = ( signed_t )( TMAX_ISRPRI ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_112 = ( unsigned_t ) ( TDOM_KERNEL );
#line 18 "../../target/ev3_gcc/drivers/gpio/gpio_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_112 = 112;
const unsigned_t TOPPERS_cfg_valueof_isratr_112 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_intno_112 = ( unsigned_t )( GPIO_B1INT ); const signed_t TOPPERS_cfg_valueof_isrpri_112 = ( signed_t )( TMAX_ISRPRI ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_113 = ( unsigned_t ) ( TDOM_KERNEL );
#line 19 "../../target/ev3_gcc/drivers/gpio/gpio_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_113 = 113;
const unsigned_t TOPPERS_cfg_valueof_isratr_113 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_intno_113 = ( unsigned_t )( GPIO_B2INT ); const signed_t TOPPERS_cfg_valueof_isrpri_113 = ( signed_t )( TMAX_ISRPRI ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_114 = ( unsigned_t ) ( TDOM_KERNEL );
#line 20 "../../target/ev3_gcc/drivers/gpio/gpio_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_114 = 114;
const unsigned_t TOPPERS_cfg_valueof_isratr_114 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_intno_114 = ( unsigned_t )( GPIO_B3INT ); const signed_t TOPPERS_cfg_valueof_isrpri_114 = ( signed_t )( TMAX_ISRPRI ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_115 = ( unsigned_t ) ( TDOM_KERNEL );
#line 21 "../../target/ev3_gcc/drivers/gpio/gpio_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_115 = 115;
const unsigned_t TOPPERS_cfg_valueof_isratr_115 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_intno_115 = ( unsigned_t )( GPIO_B4INT ); const signed_t TOPPERS_cfg_valueof_isrpri_115 = ( signed_t )( TMAX_ISRPRI ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_116 = ( unsigned_t ) ( TDOM_KERNEL );
#line 22 "../../target/ev3_gcc/drivers/gpio/gpio_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_116 = 116;
const unsigned_t TOPPERS_cfg_valueof_isratr_116 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_intno_116 = ( unsigned_t )( GPIO_B5INT ); const signed_t TOPPERS_cfg_valueof_isrpri_116 = ( signed_t )( TMAX_ISRPRI ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_117 = ( unsigned_t ) ( TDOM_KERNEL );
#line 23 "../../target/ev3_gcc/drivers/gpio/gpio_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_117 = 117;
const unsigned_t TOPPERS_cfg_valueof_isratr_117 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_intno_117 = ( unsigned_t )( GPIO_B6INT ); const signed_t TOPPERS_cfg_valueof_isrpri_117 = ( signed_t )( TMAX_ISRPRI ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_118 = ( unsigned_t ) ( TDOM_KERNEL );
#line 24 "../../target/ev3_gcc/drivers/gpio/gpio_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_118 = 118;
const unsigned_t TOPPERS_cfg_valueof_isratr_118 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_intno_118 = ( unsigned_t )( GPIO_B7INT ); const signed_t TOPPERS_cfg_valueof_isrpri_118 = ( signed_t )( TMAX_ISRPRI ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_119 = ( unsigned_t ) ( TDOM_KERNEL );
#line 25 "../../target/ev3_gcc/drivers/gpio/gpio_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_119 = 119;
const unsigned_t TOPPERS_cfg_valueof_isratr_119 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_intno_119 = ( unsigned_t )( GPIO_B8INT ); const signed_t TOPPERS_cfg_valueof_isrpri_119 = ( signed_t )( TMAX_ISRPRI ); 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 28 "../../target/ev3_gcc/drivers/gpio/gpio_dri.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 4 "../../target/ev3_gcc/drivers/sensor/analog/analog_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_120 = ( unsigned_t ) ( TDOM_KERNEL );
#line 5 "../../target/ev3_gcc/drivers/sensor/analog/analog_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_120 = 120;
const unsigned_t TOPPERS_cfg_valueof_iniatr_120 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_121 = ( unsigned_t ) ( TDOM_KERNEL );
#line 6 "../../target/ev3_gcc/drivers/sensor/analog/analog_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_121 = 121;
const char TOPPERS_cfg_valueof_module_121[] = "analog_dri.o"; const unsigned_t TOPPERS_cfg_valueof_acptn1_121 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn2_121 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn3_121 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn4_121 = ( unsigned_t )( TACP_KERNEL ); 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 7 "../../target/ev3_gcc/drivers/sensor/analog/analog_dri.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 4 "../../target/ev3_gcc/drivers/lcd/lcd_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL

#if 0 
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_122 = ( unsigned_t ) ( TDOM_KERNEL );
#line 9 "../../target/ev3_gcc/drivers/lcd/lcd_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_122 = 122;
const unsigned_t TOPPERS_cfg_valueof_intno_122 = ( unsigned_t )( LCD_SPI_INT ); const unsigned_t TOPPERS_cfg_valueof_intatr_122 = ( unsigned_t )( TA_ENAINT ); const signed_t TOPPERS_cfg_valueof_intpri_122 = ( signed_t )( INTPRI_LCD_SPI ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_123 = ( unsigned_t ) ( TDOM_KERNEL );
#line 10 "../../target/ev3_gcc/drivers/lcd/lcd_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_123 = 123;
const unsigned_t TOPPERS_cfg_valueof_isratr_123 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_intno_123 = ( unsigned_t )( LCD_SPI_INT ); const signed_t TOPPERS_cfg_valueof_isrpri_123 = ( signed_t )( TMIN_ISRPRI ); 
#endif
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_124 = ( unsigned_t ) ( TDOM_KERNEL );
#line 13 "../../target/ev3_gcc/drivers/lcd/lcd_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_124 = 124;
#define LCD_DMA_DONE_SEM	(<>)

#line 13 "../../target/ev3_gcc/drivers/lcd/lcd_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_124 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_124 = ( unsigned_t )( 0 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_124 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_125 = ( unsigned_t ) ( TDOM_KERNEL );
#line 14 "../../target/ev3_gcc/drivers/lcd/lcd_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_125 = 125;
#define LCD_REFRESH_TSK	(<>)

#line 14 "../../target/ev3_gcc/drivers/lcd/lcd_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_125 = ( unsigned_t )( TA_NULL ); const signed_t TOPPERS_cfg_valueof_itskpri_125 = ( signed_t )( TPRI_EV3_LCD_TASK ); const unsigned_t TOPPERS_cfg_valueof_stksz_125 = ( unsigned_t )( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_126 = ( unsigned_t ) ( TDOM_KERNEL );
#line 16 "../../target/ev3_gcc/drivers/lcd/lcd_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_126 = 126;
const char TOPPERS_cfg_valueof_section_126[] = ".lcd_vmem"; const unsigned_t TOPPERS_cfg_valueof_mematr_126 = ( unsigned_t )( TA_NULL ); const char TOPPERS_cfg_valueof_memreg_126[] = "RAM"; const unsigned_t TOPPERS_cfg_valueof_acptn1_126 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn2_126 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn3_126 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn4_126 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_127 = ( unsigned_t ) ( TDOM_KERNEL );
#line 18 "../../target/ev3_gcc/drivers/lcd/lcd_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_127 = 127;
const char TOPPERS_cfg_valueof_module_127[] = "lcd_dri.o"; const unsigned_t TOPPERS_cfg_valueof_acptn1_127 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn2_127 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn3_127 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn4_127 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_128 = ( unsigned_t ) ( TDOM_KERNEL );
#line 19 "../../target/ev3_gcc/drivers/lcd/lcd_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_128 = 128;
const char TOPPERS_cfg_valueof_module_128[] = "lcd_font.o"; const unsigned_t TOPPERS_cfg_valueof_acptn1_128 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn2_128 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn3_128 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn4_128 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_129 = ( unsigned_t ) ( TDOM_KERNEL );
#line 24 "../../target/ev3_gcc/drivers/lcd/lcd_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_129 = 129;
#define EV3RT_CONSOLE_MTX	(<>)

#line 24 "../../target/ev3_gcc/drivers/lcd/lcd_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_mtxatr_129 = ( unsigned_t )( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 26 "../../target/ev3_gcc/drivers/lcd/lcd_dri.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 5 "../../target/ev3_gcc/drivers/console/console_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_130 = ( unsigned_t ) ( TDOM_KERNEL );
#line 10 "../../target/ev3_gcc/drivers/console/console_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_130 = 130;
#define CONSOLE_BTN_TSK	(<>)

#line 10 "../../target/ev3_gcc/drivers/console/console_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_130 = ( unsigned_t )( TA_ACT ); const signed_t TOPPERS_cfg_valueof_itskpri_130 = ( signed_t )( TPRI_EV3_MONITOR ); const unsigned_t TOPPERS_cfg_valueof_stksz_130 = ( unsigned_t )( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_131 = ( unsigned_t ) ( TDOM_KERNEL );
#line 14 "../../target/ev3_gcc/drivers/console/console_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_131 = 131;
#define EV3RT_CONSOLE_LOG_MTX	(<>)

#line 14 "../../target/ev3_gcc/drivers/console/console_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_mtxatr_131 = ( unsigned_t )( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 16 "../../target/ev3_gcc/drivers/console/console_dri.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 4 "../../target/ev3_gcc/drivers/motor/motor_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_132 = ( unsigned_t ) ( TDOM_KERNEL );
#line 6 "../../target/ev3_gcc/drivers/motor/motor_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_132 = 132;
const unsigned_t TOPPERS_cfg_valueof_iniatr_132 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_133 = ( unsigned_t ) ( TDOM_KERNEL );
#line 8 "../../target/ev3_gcc/drivers/motor/motor_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_133 = 133;
const char TOPPERS_cfg_valueof_module_133[] = "motor_dri.o"; const unsigned_t TOPPERS_cfg_valueof_acptn1_133 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn2_133 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn3_133 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn4_133 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_134 = ( unsigned_t ) ( TDOM_KERNEL );
#line 10 "../../target/ev3_gcc/drivers/motor/motor_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_134 = 134;
const unsigned_t TOPPERS_cfg_valueof_fncd_134 = ( unsigned_t )( TFN_MOTOR_COMMAND ); const unsigned_t TOPPERS_cfg_valueof_svcatr_134 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_134 = ( unsigned_t )( 1024 ); 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 12 "../../target/ev3_gcc/drivers/motor/motor_dri.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 4 "../../target/ev3_gcc/drivers/newlib/newlib_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_135 = ( unsigned_t ) ( TDOM_KERNEL );
#line 6 "../../target/ev3_gcc/drivers/newlib/newlib_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_135 = 135;
const unsigned_t TOPPERS_cfg_valueof_iniatr_135 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_136 = ( unsigned_t ) ( TDOM_KERNEL );
#line 8 "../../target/ev3_gcc/drivers/newlib/newlib_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_136 = 136;
const unsigned_t TOPPERS_cfg_valueof_fncd_136 = ( unsigned_t )( TFN_NEWLIB_OPEN_R ); const unsigned_t TOPPERS_cfg_valueof_svcatr_136 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_136 = ( unsigned_t )( 1024 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_137 = ( unsigned_t ) ( TDOM_KERNEL );
#line 9 "../../target/ev3_gcc/drivers/newlib/newlib_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_137 = 137;
const unsigned_t TOPPERS_cfg_valueof_fncd_137 = ( unsigned_t )( TFN_NEWLIB_READ_R ); const unsigned_t TOPPERS_cfg_valueof_svcatr_137 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_137 = ( unsigned_t )( 1024 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_138 = ( unsigned_t ) ( TDOM_KERNEL );
#line 10 "../../target/ev3_gcc/drivers/newlib/newlib_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_138 = 138;
const unsigned_t TOPPERS_cfg_valueof_fncd_138 = ( unsigned_t )( TFN_NEWLIB_WRITE_R ); const unsigned_t TOPPERS_cfg_valueof_svcatr_138 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_138 = ( unsigned_t )( 1024 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_139 = ( unsigned_t ) ( TDOM_KERNEL );
#line 11 "../../target/ev3_gcc/drivers/newlib/newlib_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_139 = 139;
const unsigned_t TOPPERS_cfg_valueof_fncd_139 = ( unsigned_t )( TFN_NEWLIB_CLOSE_R ); const unsigned_t TOPPERS_cfg_valueof_svcatr_139 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_139 = ( unsigned_t )( 1024 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_140 = ( unsigned_t ) ( TDOM_KERNEL );
#line 12 "../../target/ev3_gcc/drivers/newlib/newlib_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_140 = 140;
const unsigned_t TOPPERS_cfg_valueof_fncd_140 = ( unsigned_t )( TFN_NEWLIB_LSEEK_R ); const unsigned_t TOPPERS_cfg_valueof_svcatr_140 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_140 = ( unsigned_t )( 1024 ); 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 19 "../../target/ev3_gcc/drivers/newlib/newlib_dri.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#line 25 "../../target/ev3_gcc/drivers/newlib/newlib_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_141 = 141;
const char TOPPERS_cfg_valueof_section_141[] = ".text.*"; const unsigned_t TOPPERS_cfg_valueof_mematr_141 = ( unsigned_t )( TA_NOWRITE ); const char TOPPERS_cfg_valueof_memreg_141[] = "ROM"; 
#line 26 "../../target/ev3_gcc/drivers/newlib/newlib_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_142 = 142;
const char TOPPERS_cfg_valueof_section_142[] = ".data.*"; const unsigned_t TOPPERS_cfg_valueof_mematr_142 = ( unsigned_t )( TA_MEMINI ); const char TOPPERS_cfg_valueof_memreg_142[] = "RAM"; 
#line 27 "../../target/ev3_gcc/drivers/newlib/newlib_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_143 = 143;
const char TOPPERS_cfg_valueof_section_143[] = ".rodata.*"; const unsigned_t TOPPERS_cfg_valueof_mematr_143 = ( unsigned_t )( TA_NOWRITE ); const char TOPPERS_cfg_valueof_memreg_143[] = "ROM"; 
#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 4 "../../target/ev3_gcc/drivers/sensor/i2c/i2c_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_144 = ( unsigned_t ) ( TDOM_KERNEL );
#line 6 "../../target/ev3_gcc/drivers/sensor/i2c/i2c_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_144 = 144;
const unsigned_t TOPPERS_cfg_valueof_iniatr_144 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_145 = ( unsigned_t ) ( TDOM_KERNEL );
#line 8 "../../target/ev3_gcc/drivers/sensor/i2c/i2c_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_145 = 145;
const unsigned_t TOPPERS_cfg_valueof_intno_145 = ( unsigned_t )( INTNO_I2C_TIMER ); const unsigned_t TOPPERS_cfg_valueof_intatr_145 = ( unsigned_t )( TA_ENAINT ); const signed_t TOPPERS_cfg_valueof_intpri_145 = ( signed_t )( INTPRI_I2C_TIMER ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_146 = ( unsigned_t ) ( TDOM_KERNEL );
#line 9 "../../target/ev3_gcc/drivers/sensor/i2c/i2c_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_146 = 146;
const unsigned_t TOPPERS_cfg_valueof_inhno_146 = ( unsigned_t )( INTNO_I2C_TIMER ); const unsigned_t TOPPERS_cfg_valueof_inhatr_146 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_147 = ( unsigned_t ) ( TDOM_KERNEL );
#line 11 "../../target/ev3_gcc/drivers/sensor/i2c/i2c_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_147 = 147;
const char TOPPERS_cfg_valueof_module_147[] = "i2c_dri.o"; const unsigned_t TOPPERS_cfg_valueof_acptn1_147 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn2_147 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn3_147 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn4_147 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_148 = ( unsigned_t ) ( TDOM_KERNEL );
#line 12 "../../target/ev3_gcc/drivers/sensor/i2c/i2c_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_148 = 148;
const char TOPPERS_cfg_valueof_module_148[] = "davinci_iic_dri.o"; const unsigned_t TOPPERS_cfg_valueof_acptn1_148 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn2_148 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn3_148 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn4_148 = ( unsigned_t )( TACP_KERNEL ); 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 14 "../../target/ev3_gcc/drivers/sensor/i2c/i2c_dri.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 4 "../../target/ev3_gcc/drivers/sensor/uart/uart_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_149 = ( unsigned_t ) ( TDOM_KERNEL );
#line 6 "../../target/ev3_gcc/drivers/sensor/uart/uart_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_149 = 149;
const unsigned_t TOPPERS_cfg_valueof_iniatr_149 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_150 = ( unsigned_t ) ( TDOM_KERNEL );
#line 8 "../../target/ev3_gcc/drivers/sensor/uart/uart_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_150 = 150;
const unsigned_t TOPPERS_cfg_valueof_intno_150 = ( unsigned_t )( INTNO_UART_PORT1 ); const unsigned_t TOPPERS_cfg_valueof_intatr_150 = ( unsigned_t )( TA_NULL ); const signed_t TOPPERS_cfg_valueof_intpri_150 = ( signed_t )( INTPRI_UART_PORT1 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_151 = ( unsigned_t ) ( TDOM_KERNEL );
#line 9 "../../target/ev3_gcc/drivers/sensor/uart/uart_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_151 = 151;
const unsigned_t TOPPERS_cfg_valueof_intno_151 = ( unsigned_t )( INTNO_UART_PORT2 ); const unsigned_t TOPPERS_cfg_valueof_intatr_151 = ( unsigned_t )( TA_NULL ); const signed_t TOPPERS_cfg_valueof_intpri_151 = ( signed_t )( INTPRI_UART_PORT2 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_152 = ( unsigned_t ) ( TDOM_KERNEL );
#line 10 "../../target/ev3_gcc/drivers/sensor/uart/uart_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_152 = 152;
const unsigned_t TOPPERS_cfg_valueof_intno_152 = ( unsigned_t )( INTNO_UART_PORT3 ); const unsigned_t TOPPERS_cfg_valueof_intatr_152 = ( unsigned_t )( TA_NULL ); const signed_t TOPPERS_cfg_valueof_intpri_152 = ( signed_t )( INTPRI_UART_PORT3 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_153 = ( unsigned_t ) ( TDOM_KERNEL );
#line 11 "../../target/ev3_gcc/drivers/sensor/uart/uart_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_153 = 153;
const unsigned_t TOPPERS_cfg_valueof_intno_153 = ( unsigned_t )( INTNO_UART_PORT4 ); const unsigned_t TOPPERS_cfg_valueof_intatr_153 = ( unsigned_t )( TA_NULL ); const signed_t TOPPERS_cfg_valueof_intpri_153 = ( signed_t )( INTPRI_UART_PORT4 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_154 = ( unsigned_t ) ( TDOM_KERNEL );
#line 13 "../../target/ev3_gcc/drivers/sensor/uart/uart_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_154 = 154;
const unsigned_t TOPPERS_cfg_valueof_isratr_154 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_intno_154 = ( unsigned_t )( INTNO_UART_PORT2 ); const signed_t TOPPERS_cfg_valueof_isrpri_154 = ( signed_t )( TMIN_ISRPRI ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_155 = ( unsigned_t ) ( TDOM_KERNEL );
#line 14 "../../target/ev3_gcc/drivers/sensor/uart/uart_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_155 = 155;
const unsigned_t TOPPERS_cfg_valueof_isratr_155 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_intno_155 = ( unsigned_t )( INTNO_UART_PORT3 ); const signed_t TOPPERS_cfg_valueof_isrpri_155 = ( signed_t )( TMIN_ISRPRI ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_156 = ( unsigned_t ) ( TDOM_KERNEL );
#line 15 "../../target/ev3_gcc/drivers/sensor/uart/uart_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_156 = 156;
const unsigned_t TOPPERS_cfg_valueof_isratr_156 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_intno_156 = ( unsigned_t )( INTNO_UART_PORT4 ); const signed_t TOPPERS_cfg_valueof_isrpri_156 = ( signed_t )( TMIN_ISRPRI ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_157 = ( unsigned_t ) ( TDOM_KERNEL );
#line 17 "../../target/ev3_gcc/drivers/sensor/uart/uart_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_157 = 157;
#define SUART1_SEM	(<>)

#line 17 "../../target/ev3_gcc/drivers/sensor/uart/uart_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_157 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_157 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_157 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_158 = ( unsigned_t ) ( TDOM_KERNEL );
#line 18 "../../target/ev3_gcc/drivers/sensor/uart/uart_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_158 = 158;
#define SUART2_SEM	(<>)

#line 18 "../../target/ev3_gcc/drivers/sensor/uart/uart_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_158 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_158 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_158 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_159 = ( unsigned_t ) ( TDOM_KERNEL );
#line 20 "../../target/ev3_gcc/drivers/sensor/uart/uart_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_159 = 159;
const char TOPPERS_cfg_valueof_module_159[] = "uart_dri.o"; const unsigned_t TOPPERS_cfg_valueof_acptn1_159 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn2_159 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn3_159 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn4_159 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_160 = ( unsigned_t ) ( TDOM_KERNEL );
#line 21 "../../target/ev3_gcc/drivers/sensor/uart/uart_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_160 = 160;
const char TOPPERS_cfg_valueof_module_160[] = "pru.o"; const unsigned_t TOPPERS_cfg_valueof_acptn1_160 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn2_160 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn3_160 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn4_160 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_161 = ( unsigned_t ) ( TDOM_KERNEL );
#line 22 "../../target/ev3_gcc/drivers/sensor/uart/uart_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_161 = 161;
const char TOPPERS_cfg_valueof_module_161[] = "suart_utils.o"; const unsigned_t TOPPERS_cfg_valueof_acptn1_161 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn2_161 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn3_161 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn4_161 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_162 = ( unsigned_t ) ( TDOM_KERNEL );
#line 23 "../../target/ev3_gcc/drivers/sensor/uart/uart_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_162 = 162;
const char TOPPERS_cfg_valueof_module_162[] = "suart_api.o"; const unsigned_t TOPPERS_cfg_valueof_acptn1_162 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn2_162 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn3_162 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn4_162 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_163 = ( unsigned_t ) ( TDOM_KERNEL );
#line 24 "../../target/ev3_gcc/drivers/sensor/uart/uart_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_163 = 163;
const char TOPPERS_cfg_valueof_module_163[] = "pru_suart.o"; const unsigned_t TOPPERS_cfg_valueof_acptn1_163 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn2_163 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn3_163 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn4_163 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_164 = ( unsigned_t ) ( TDOM_KERNEL );
#line 26 "../../target/ev3_gcc/drivers/sensor/uart/uart_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_164 = 164;
const unsigned_t TOPPERS_cfg_valueof_fncd_164 = ( unsigned_t )( TFN_UART_SENSOR_CONFIG ); const unsigned_t TOPPERS_cfg_valueof_svcatr_164 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_164 = ( unsigned_t )( 1024 ); 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 28 "../../target/ev3_gcc/drivers/sensor/uart/uart_dri.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#line 30 "../../target/ev3_gcc/drivers/sensor/uart/uart_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_165 = 165;
const unsigned_t TOPPERS_cfg_valueof_noisr_165 = ( unsigned_t )( 1 ); 
#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 4 "../../target/ev3_gcc/drivers/soc/soc.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_166 = ( unsigned_t ) ( TDOM_KERNEL );
#line 13 "../../target/ev3_gcc/drivers/soc/soc.cfg"
const unsigned_t TOPPERS_cfg_static_api_166 = 166;
const unsigned_t TOPPERS_cfg_valueof_iniatr_166 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_167 = ( unsigned_t ) ( TDOM_KERNEL );
#line 14 "../../target/ev3_gcc/drivers/soc/soc.cfg"
const unsigned_t TOPPERS_cfg_static_api_167 = 167;
const unsigned_t TOPPERS_cfg_valueof_intno_167 = ( unsigned_t )( SYS_INT_CCINT0 ); const unsigned_t TOPPERS_cfg_valueof_intatr_167 = ( unsigned_t )( TA_ENAINT ); const signed_t TOPPERS_cfg_valueof_intpri_167 = ( signed_t )( TMIN_INTPRI ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_168 = ( unsigned_t ) ( TDOM_KERNEL );
#line 15 "../../target/ev3_gcc/drivers/soc/soc.cfg"
const unsigned_t TOPPERS_cfg_static_api_168 = 168;
const unsigned_t TOPPERS_cfg_valueof_intno_168 = ( unsigned_t )( SYS_INT_CCERRINT ); const unsigned_t TOPPERS_cfg_valueof_intatr_168 = ( unsigned_t )( TA_ENAINT ); const signed_t TOPPERS_cfg_valueof_intpri_168 = ( signed_t )( TMIN_INTPRI ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_169 = ( unsigned_t ) ( TDOM_KERNEL );
#line 16 "../../target/ev3_gcc/drivers/soc/soc.cfg"
const unsigned_t TOPPERS_cfg_static_api_169 = 169;
const unsigned_t TOPPERS_cfg_valueof_isratr_169 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_intno_169 = ( unsigned_t )( SYS_INT_CCINT0 ); const signed_t TOPPERS_cfg_valueof_isrpri_169 = ( signed_t )( TMIN_ISRPRI ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_170 = ( unsigned_t ) ( TDOM_KERNEL );
#line 17 "../../target/ev3_gcc/drivers/soc/soc.cfg"
const unsigned_t TOPPERS_cfg_static_api_170 = 170;
const unsigned_t TOPPERS_cfg_valueof_isratr_170 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_intno_170 = ( unsigned_t )( SYS_INT_CCERRINT ); const signed_t TOPPERS_cfg_valueof_isrpri_170 = ( signed_t )( TMIN_ISRPRI ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_171 = ( unsigned_t ) ( TDOM_KERNEL );
#line 22 "../../target/ev3_gcc/drivers/soc/soc.cfg"
const unsigned_t TOPPERS_cfg_static_api_171 = 171;
const char TOPPERS_cfg_valueof_module_171[] = "soc_cache.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_172 = ( unsigned_t ) ( TDOM_KERNEL );
#line 23 "../../target/ev3_gcc/drivers/soc/soc.cfg"
const unsigned_t TOPPERS_cfg_static_api_172 = 172;
const char TOPPERS_cfg_valueof_module_172[] = "soc_edma.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_173 = ( unsigned_t ) ( TDOM_KERNEL );
#line 24 "../../target/ev3_gcc/drivers/soc/soc.cfg"
const unsigned_t TOPPERS_cfg_static_api_173 = 173;
const char TOPPERS_cfg_valueof_module_173[] = "edma.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_174 = ( unsigned_t ) ( TDOM_KERNEL );
#line 25 "../../target/ev3_gcc/drivers/soc/soc.cfg"
const unsigned_t TOPPERS_cfg_static_api_174 = 174;
const char TOPPERS_cfg_valueof_module_174[] = "uart.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_175 = ( unsigned_t ) ( TDOM_KERNEL );
#line 26 "../../target/ev3_gcc/drivers/soc/soc.cfg"
const unsigned_t TOPPERS_cfg_static_api_175 = 175;
const char TOPPERS_cfg_valueof_module_175[] = "cp15.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_176 = ( unsigned_t ) ( TDOM_KERNEL );
#line 27 "../../target/ev3_gcc/drivers/soc/soc.cfg"
const unsigned_t TOPPERS_cfg_static_api_176 = 176;
const char TOPPERS_cfg_valueof_module_176[] = "psc.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_177 = ( unsigned_t ) ( TDOM_KERNEL );
#line 28 "../../target/ev3_gcc/drivers/soc/soc.cfg"
const unsigned_t TOPPERS_cfg_static_api_177 = 177;
const char TOPPERS_cfg_valueof_module_177[] = "usb.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_178 = ( unsigned_t ) ( TDOM_KERNEL );
#line 29 "../../target/ev3_gcc/drivers/soc/soc.cfg"
const unsigned_t TOPPERS_cfg_static_api_178 = 178;
const char TOPPERS_cfg_valueof_module_178[] = "usbphyGS60.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_179 = ( unsigned_t ) ( TDOM_KERNEL );
#line 30 "../../target/ev3_gcc/drivers/soc/soc.cfg"
const unsigned_t TOPPERS_cfg_static_api_179 = 179;
const char TOPPERS_cfg_valueof_module_179[] = "cppi41dma.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_180 = ( unsigned_t ) ( TDOM_KERNEL );
#line 31 "../../target/ev3_gcc/drivers/soc/soc.cfg"
const unsigned_t TOPPERS_cfg_static_api_180 = 180;
const char TOPPERS_cfg_valueof_module_180[] = "evmAM1808_usb.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_181 = ( unsigned_t ) ( TDOM_KERNEL );
#line 32 "../../target/ev3_gcc/drivers/soc/soc.cfg"
const unsigned_t TOPPERS_cfg_static_api_181 = 181;
const char TOPPERS_cfg_valueof_module_181[] = "soc_interrupt.o"; 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 34 "../../target/ev3_gcc/drivers/soc/soc.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 4 "../../target/ev3_gcc/drivers/sound/sound_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_182 = ( unsigned_t ) ( TDOM_KERNEL );
#line 5 "../../target/ev3_gcc/drivers/sound/sound_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_182 = 182;
const unsigned_t TOPPERS_cfg_valueof_iniatr_182 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_183 = ( unsigned_t ) ( TDOM_KERNEL );
#line 6 "../../target/ev3_gcc/drivers/sound/sound_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_183 = 183;
#define SND_STOP_ALM	(<>)

#line 6 "../../target/ev3_gcc/drivers/sound/sound_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_almatr_183 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_184 = ( unsigned_t ) ( TDOM_KERNEL );
#line 7 "../../target/ev3_gcc/drivers/sound/sound_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_184 = 184;
#define SND_DEV_SEM	(<>)

#line 7 "../../target/ev3_gcc/drivers/sound/sound_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_184 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_184 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_184 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_185 = ( unsigned_t ) ( TDOM_KERNEL );
#line 8 "../../target/ev3_gcc/drivers/sound/sound_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_185 = 185;
const char TOPPERS_cfg_valueof_module_185[] = "sound_dri.o"; const unsigned_t TOPPERS_cfg_valueof_acptn1_185 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn2_185 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn3_185 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn4_185 = ( unsigned_t )( TACP_KERNEL ); 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 9 "../../target/ev3_gcc/drivers/sound/sound_dri.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 5 "../../target/ev3_gcc/drivers/bluetooth/bluetooth_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_186 = ( unsigned_t ) ( TDOM_KERNEL );
#line 7 "../../target/ev3_gcc/drivers/bluetooth/bluetooth_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_186 = 186;
const unsigned_t TOPPERS_cfg_valueof_iniatr_186 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_187 = ( unsigned_t ) ( TDOM_KERNEL );
#line 8 "../../target/ev3_gcc/drivers/bluetooth/bluetooth_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_187 = 187;
#define BT_TSK	(<>)

#line 8 "../../target/ev3_gcc/drivers/bluetooth/bluetooth_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_187 = ( unsigned_t )( TA_NULL ); const signed_t TOPPERS_cfg_valueof_itskpri_187 = ( signed_t )( TPRI_BLUETOOTH_HIGH ); const unsigned_t TOPPERS_cfg_valueof_stksz_187 = ( unsigned_t )( STACK_SIZE ); 
#if !BT_USE_EDMA_MODE
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_188 = ( unsigned_t ) ( TDOM_KERNEL );
#line 11 "../../target/ev3_gcc/drivers/bluetooth/bluetooth_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_188 = 188;
const unsigned_t TOPPERS_cfg_valueof_intno_188 = ( unsigned_t )( UART2_INT ); const unsigned_t TOPPERS_cfg_valueof_intatr_188 = ( unsigned_t )( TA_ENAINT ); const signed_t TOPPERS_cfg_valueof_intpri_188 = ( signed_t )( INTPRI_BLUETOOTH ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_189 = ( unsigned_t ) ( TDOM_KERNEL );
#line 12 "../../target/ev3_gcc/drivers/bluetooth/bluetooth_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_189 = 189;
const unsigned_t TOPPERS_cfg_valueof_inhno_189 = ( unsigned_t )( UART2_INT ); const unsigned_t TOPPERS_cfg_valueof_inhatr_189 = ( unsigned_t )( TA_NULL ); 
#else
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_190 = ( unsigned_t ) ( TDOM_KERNEL );
#line 14 "../../target/ev3_gcc/drivers/bluetooth/bluetooth_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_190 = 190;
#define BT_DMA_CYC	(<>)

#line 14 "../../target/ev3_gcc/drivers/bluetooth/bluetooth_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_cycatr_190 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_cyctim_190 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_cycphs_190 = ( unsigned_t )( 0 ); 
#endif
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_191 = ( unsigned_t ) ( TDOM_KERNEL );
#line 19 "../../target/ev3_gcc/drivers/bluetooth/bluetooth_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_191 = 191;
#define BT_QOS_TSK	(<>)

#line 19 "../../target/ev3_gcc/drivers/bluetooth/bluetooth_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_191 = ( unsigned_t )( TA_NULL ); const signed_t TOPPERS_cfg_valueof_itskpri_191 = ( signed_t )( TPRI_BLUETOOTH_QOS ); const unsigned_t TOPPERS_cfg_valueof_stksz_191 = ( unsigned_t )( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_192 = ( unsigned_t ) ( TDOM_KERNEL );
#line 21 "../../target/ev3_gcc/drivers/bluetooth/bluetooth_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_192 = 192;
#define BT_DB_MTX	(<>)

#line 21 "../../target/ev3_gcc/drivers/bluetooth/bluetooth_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_mtxatr_192 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_193 = ( unsigned_t ) ( TDOM_KERNEL );
#line 26 "../../target/ev3_gcc/drivers/bluetooth/bluetooth_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_193 = 193;
const char TOPPERS_cfg_valueof_module_193[] = "bluetooth_dri.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_194 = ( unsigned_t ) ( TDOM_KERNEL );
#line 27 "../../target/ev3_gcc/drivers/bluetooth/bluetooth_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_194 = 194;
const char TOPPERS_cfg_valueof_module_194[] = "libBTstack.a"; 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 29 "../../target/ev3_gcc/drivers/bluetooth/bluetooth_dri.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 4 "../../target/ev3_gcc/drivers/usbmsc/usbmsc_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_195 = ( unsigned_t ) ( TDOM_KERNEL );
#line 6 "../../target/ev3_gcc/drivers/usbmsc/usbmsc_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_195 = 195;
const unsigned_t TOPPERS_cfg_valueof_iniatr_195 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_196 = ( unsigned_t ) ( TDOM_KERNEL );
#line 8 "../../target/ev3_gcc/drivers/usbmsc/usbmsc_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_196 = 196;
const unsigned_t TOPPERS_cfg_valueof_intno_196 = ( unsigned_t )( SYS_INT_USB0 ); const unsigned_t TOPPERS_cfg_valueof_intatr_196 = ( unsigned_t )( TA_ENAINT ); const signed_t TOPPERS_cfg_valueof_intpri_196 = ( signed_t )( INTPRI_USBMSC ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_197 = ( unsigned_t ) ( TDOM_KERNEL );
#line 9 "../../target/ev3_gcc/drivers/usbmsc/usbmsc_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_197 = 197;
const unsigned_t TOPPERS_cfg_valueof_inhno_197 = ( unsigned_t )( SYS_INT_USB0 ); const unsigned_t TOPPERS_cfg_valueof_inhatr_197 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_198 = ( unsigned_t ) ( TDOM_KERNEL );
#line 11 "../../target/ev3_gcc/drivers/usbmsc/usbmsc_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_198 = 198;
#define USBMSC_TSK	(<>)

#line 11 "../../target/ev3_gcc/drivers/usbmsc/usbmsc_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_198 = ( unsigned_t )( TA_ACT ); const signed_t TOPPERS_cfg_valueof_itskpri_198 = ( signed_t )( TPRI_USBMSC ); const unsigned_t TOPPERS_cfg_valueof_stksz_198 = ( unsigned_t )( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_199 = ( unsigned_t ) ( TDOM_KERNEL );
#line 12 "../../target/ev3_gcc/drivers/usbmsc/usbmsc_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_199 = 199;
#define USBMSC_EVT_FLG	(<>)

#line 12 "../../target/ev3_gcc/drivers/usbmsc/usbmsc_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_flgatr_199 = ( unsigned_t )( TA_CLR ); const unsigned_t TOPPERS_cfg_valueof_iflgptn_199 = ( unsigned_t )( 0 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_200 = ( unsigned_t ) ( TDOM_KERNEL );
#line 14 "../../target/ev3_gcc/drivers/usbmsc/usbmsc_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_200 = 200;
const char TOPPERS_cfg_valueof_module_200[] = "usbmsc_dri.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_201 = ( unsigned_t ) ( TDOM_KERNEL );
#line 15 "../../target/ev3_gcc/drivers/usbmsc/usbmsc_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_201 = 201;
const char TOPPERS_cfg_valueof_module_201[] = "usbmsc_media_functions.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_202 = ( unsigned_t ) ( TDOM_KERNEL );
#line 16 "../../target/ev3_gcc/drivers/usbmsc/usbmsc_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_202 = 202;
const char TOPPERS_cfg_valueof_module_202[] = "usb_dev_msc.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_203 = ( unsigned_t ) ( TDOM_KERNEL );
#line 17 "../../target/ev3_gcc/drivers/usbmsc/usbmsc_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_203 = 203;
const char TOPPERS_cfg_valueof_module_203[] = "usb_msc_structs.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_204 = ( unsigned_t ) ( TDOM_KERNEL );
#line 18 "../../target/ev3_gcc/drivers/usbmsc/usbmsc_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_204 = 204;
const char TOPPERS_cfg_valueof_module_204[] = "libusblib.a"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_205 = ( unsigned_t ) ( TDOM_KERNEL );
#line 26 "../../target/ev3_gcc/drivers/usbmsc/usbmsc_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_205 = 205;
const char TOPPERS_cfg_valueof_section_205[] = ".bss.g_bytesWritten .bss.intStatus .bss.g_bytesRead .bss.gDMAflag .bss.g_sSCSICSW .bss.ulSOFDivide.* .bss.g_eUSBMode .bss.g_pucDataBufferIn .bss.g_bUSBTimerInitialized .bss.g_ulCurrentUSBTick .bss.g_ulUSBSOFCount .bss._PathLocale .bss.__nlocale_changed .bss.__mlocale_changed"; const unsigned_t TOPPERS_cfg_valueof_mematr_205 = ( unsigned_t )( TA_NULL ); const char TOPPERS_cfg_valueof_memreg_205[] = "RAM"; 
#if defined(DEBUG_USBMSC_USBLIB) || 1

#endif

#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 33 "../../target/ev3_gcc/drivers/usbmsc/usbmsc_dri.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#if defined(BUILD_LOADER)

#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 5 "../../target/ev3_gcc/drivers/mbed/mbed_dri.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_206 = ( unsigned_t ) ( TDOM_KERNEL );
#line 7 "../../target/ev3_gcc/drivers/mbed/mbed_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_206 = 206;
const unsigned_t TOPPERS_cfg_valueof_iniatr_206 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_207 = ( unsigned_t ) ( TDOM_KERNEL );
#line 11 "../../target/ev3_gcc/drivers/mbed/mbed_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_207 = 207;
const char TOPPERS_cfg_valueof_module_207[] = "mbed_dri.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_208 = ( unsigned_t ) ( TDOM_KERNEL );
#line 12 "../../target/ev3_gcc/drivers/mbed/mbed_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_208 = 208;
const char TOPPERS_cfg_valueof_module_208[] = "libmbed.a"; 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 14 "../../target/ev3_gcc/drivers/mbed/mbed_dri.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#line 16 "../../target/ev3_gcc/drivers/mbed/mbed_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_209 = 209;
const unsigned_t TOPPERS_cfg_valueof_nodtq_209 = ( unsigned_t )( 64 ); 
#line 17 "../../target/ev3_gcc/drivers/mbed/mbed_dri.cfg"
const unsigned_t TOPPERS_cfg_static_api_210 = 210;
const unsigned_t TOPPERS_cfg_valueof_nompf_210 = ( unsigned_t )( 4 ); 
#endif

#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 42 "../../target/ev3_gcc/ev3.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_211 = ( unsigned_t ) ( TDOM_KERNEL );
#line 44 "../../target/ev3_gcc/ev3.cfg"
const unsigned_t TOPPERS_cfg_static_api_211 = 211;
const unsigned_t TOPPERS_cfg_valueof_acptn1_211 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn2_211 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn3_211 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn4_211 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_212 = ( unsigned_t ) ( TDOM_KERNEL );
#line 46 "../../target/ev3_gcc/ev3.cfg"
const unsigned_t TOPPERS_cfg_static_api_212 = 212;
const unsigned_t TOPPERS_cfg_valueof_kmmsz_212 = ( unsigned_t )( KERNEL_HEAP_SIZE ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_213 = ( unsigned_t ) ( TDOM_KERNEL );
#line 48 "../../target/ev3_gcc/ev3.cfg"
const unsigned_t TOPPERS_cfg_static_api_213 = 213;
const char TOPPERS_cfg_valueof_module_213[] = "ev3main.o"; const unsigned_t TOPPERS_cfg_valueof_acptn1_213 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn2_213 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn3_213 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn4_213 = ( unsigned_t )( TACP_KERNEL ); 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 50 "../../target/ev3_gcc/ev3.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#line 52 "../../target/ev3_gcc/ev3.cfg"
const unsigned_t TOPPERS_cfg_static_api_214 = 214;
const unsigned_t TOPPERS_cfg_valueof_nocyc_214 = ( unsigned_t )( TMAX_EV3_CYC_NUM ); 
#line 53 "../../target/ev3_gcc/ev3.cfg"
const unsigned_t TOPPERS_cfg_static_api_215 = 215;
const unsigned_t TOPPERS_cfg_valueof_notsk_215 = ( unsigned_t )( TMAX_EV3_CYC_NUM ); 
#line 54 "../../target/ev3_gcc/ev3.cfg"
const unsigned_t TOPPERS_cfg_static_api_216 = 216;
const unsigned_t TOPPERS_cfg_valueof_notsk_216 = ( unsigned_t )( TMAX_APP_TSK_NUM ); 
#line 55 "../../target/ev3_gcc/ev3.cfg"
const unsigned_t TOPPERS_cfg_static_api_217 = 217;
const unsigned_t TOPPERS_cfg_valueof_nosem_217 = ( unsigned_t )( TMAX_APP_SEM_NUM ); 
#line 56 "../../target/ev3_gcc/ev3.cfg"
const unsigned_t TOPPERS_cfg_static_api_218 = 218;
const unsigned_t TOPPERS_cfg_valueof_noflg_218 = ( unsigned_t )( TMAX_APP_FLG_NUM ); 
#line 57 "../../target/ev3_gcc/ev3.cfg"
const unsigned_t TOPPERS_cfg_static_api_219 = 219;
const unsigned_t TOPPERS_cfg_valueof_nodtq_219 = ( unsigned_t )( TMAX_APP_DTQ_NUM ); 
#line 58 "../../target/ev3_gcc/ev3.cfg"
const unsigned_t TOPPERS_cfg_static_api_220 = 220;
const unsigned_t TOPPERS_cfg_valueof_nopdq_220 = ( unsigned_t )( TMAX_APP_PDQ_NUM ); 
#line 59 "../../target/ev3_gcc/ev3.cfg"
const unsigned_t TOPPERS_cfg_static_api_221 = 221;
const unsigned_t TOPPERS_cfg_valueof_nomtx_221 = ( unsigned_t )( TMAX_APP_MTX_NUM ); 
#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 8 "../../target/ev3_gcc/pil/pil.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_222 = ( unsigned_t ) ( TDOM_KERNEL );
#line 13 "../../target/ev3_gcc/pil/pil.cfg"
const unsigned_t TOPPERS_cfg_static_api_222 = 222;
const unsigned_t TOPPERS_cfg_valueof_fncd_222 = ( unsigned_t )( TFN_SPP_MASTER_TEST_CONNECT ); const unsigned_t TOPPERS_cfg_valueof_svcatr_222 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_222 = ( unsigned_t )( 1024 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_223 = ( unsigned_t ) ( TDOM_KERNEL );
#line 14 "../../target/ev3_gcc/pil/pil.cfg"
const unsigned_t TOPPERS_cfg_static_api_223 = 223;
const char TOPPERS_cfg_valueof_module_223[] = "driver_interface_bluetooth.o"; const unsigned_t TOPPERS_cfg_valueof_acptn1_223 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn2_223 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn3_223 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn4_223 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_224 = ( unsigned_t ) ( TDOM_KERNEL );
#line 19 "../../target/ev3_gcc/pil/pil.cfg"
const unsigned_t TOPPERS_cfg_static_api_224 = 224;
const unsigned_t TOPPERS_cfg_valueof_fncd_224 = ( unsigned_t )( TFN_FETCH_BRICK_INFO ); const unsigned_t TOPPERS_cfg_valueof_svcatr_224 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_224 = ( unsigned_t )( 1024 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_225 = ( unsigned_t ) ( TDOM_KERNEL );
#line 20 "../../target/ev3_gcc/pil/pil.cfg"
const unsigned_t TOPPERS_cfg_static_api_225 = 225;
const unsigned_t TOPPERS_cfg_valueof_fncd_225 = ( unsigned_t )( TFN_BTN_SET_ON_CLICKED ); const unsigned_t TOPPERS_cfg_valueof_svcatr_225 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_225 = ( unsigned_t )( 1024 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_226 = ( unsigned_t ) ( TDOM_KERNEL );
#line 21 "../../target/ev3_gcc/pil/pil.cfg"
const unsigned_t TOPPERS_cfg_static_api_226 = 226;
const unsigned_t TOPPERS_cfg_valueof_fncd_226 = ( unsigned_t )( TFN_EV3_MISC_COMMAND ); const unsigned_t TOPPERS_cfg_valueof_svcatr_226 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_226 = ( unsigned_t )( 1024 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_227 = ( unsigned_t ) ( TDOM_KERNEL );
#line 22 "../../target/ev3_gcc/pil/pil.cfg"
const unsigned_t TOPPERS_cfg_static_api_227 = 227;
const unsigned_t TOPPERS_cfg_valueof_fncd_227 = ( unsigned_t )( TFN_EV3_ACRE_CYC ); const unsigned_t TOPPERS_cfg_valueof_svcatr_227 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_227 = ( unsigned_t )( 1024 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_228 = ( unsigned_t ) ( TDOM_KERNEL );
#line 23 "../../target/ev3_gcc/pil/pil.cfg"
const unsigned_t TOPPERS_cfg_static_api_228 = 228;
const unsigned_t TOPPERS_cfg_valueof_fncd_228 = ( unsigned_t )( TFN_EV3_STA_CYC ); const unsigned_t TOPPERS_cfg_valueof_svcatr_228 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_228 = ( unsigned_t )( 1024 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_229 = ( unsigned_t ) ( TDOM_KERNEL );
#line 24 "../../target/ev3_gcc/pil/pil.cfg"
const unsigned_t TOPPERS_cfg_static_api_229 = 229;
const unsigned_t TOPPERS_cfg_valueof_fncd_229 = ( unsigned_t )( TFN_EV3_STP_CYC ); const unsigned_t TOPPERS_cfg_valueof_svcatr_229 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_229 = ( unsigned_t )( 1024 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_230 = ( unsigned_t ) ( TDOM_KERNEL );
#line 25 "../../target/ev3_gcc/pil/pil.cfg"
const unsigned_t TOPPERS_cfg_static_api_230 = 230;
const unsigned_t TOPPERS_cfg_valueof_fncd_230 = ( unsigned_t )( TFN_START_I2C_TRANS ); const unsigned_t TOPPERS_cfg_valueof_svcatr_230 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_230 = ( unsigned_t )( 1024 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_231 = ( unsigned_t ) ( TDOM_KERNEL );
#line 26 "../../target/ev3_gcc/pil/pil.cfg"
const unsigned_t TOPPERS_cfg_static_api_231 = 231;
const char TOPPERS_cfg_valueof_module_231[] = "driver_interface_brick.o"; const unsigned_t TOPPERS_cfg_valueof_acptn1_231 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn2_231 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn3_231 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn4_231 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_232 = ( unsigned_t ) ( TDOM_KERNEL );
#line 31 "../../target/ev3_gcc/pil/pil.cfg"
const unsigned_t TOPPERS_cfg_static_api_232 = 232;
const unsigned_t TOPPERS_cfg_valueof_fncd_232 = ( unsigned_t )( TFN_SOUND_SET_VOL ); const unsigned_t TOPPERS_cfg_valueof_svcatr_232 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_232 = ( unsigned_t )( 1024 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_233 = ( unsigned_t ) ( TDOM_KERNEL );
#line 32 "../../target/ev3_gcc/pil/pil.cfg"
const unsigned_t TOPPERS_cfg_static_api_233 = 233;
const unsigned_t TOPPERS_cfg_valueof_fncd_233 = ( unsigned_t )( TFN_SOUND_PLAY_TONE ); const unsigned_t TOPPERS_cfg_valueof_svcatr_233 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_233 = ( unsigned_t )( 1024 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_234 = ( unsigned_t ) ( TDOM_KERNEL );
#line 33 "../../target/ev3_gcc/pil/pil.cfg"
const unsigned_t TOPPERS_cfg_static_api_234 = 234;
const unsigned_t TOPPERS_cfg_valueof_fncd_234 = ( unsigned_t )( TFN_SOUND_PLAY_WAV ); const unsigned_t TOPPERS_cfg_valueof_svcatr_234 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_234 = ( unsigned_t )( 1024 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_235 = ( unsigned_t ) ( TDOM_KERNEL );
#line 34 "../../target/ev3_gcc/pil/pil.cfg"
const unsigned_t TOPPERS_cfg_static_api_235 = 235;
const char TOPPERS_cfg_valueof_module_235[] = "driver_interface_sound.o"; const unsigned_t TOPPERS_cfg_valueof_acptn1_235 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn2_235 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn3_235 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn4_235 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_236 = ( unsigned_t ) ( TDOM_KERNEL );
#line 39 "../../target/ev3_gcc/pil/pil.cfg"
const unsigned_t TOPPERS_cfg_static_api_236 = 236;
const unsigned_t TOPPERS_cfg_valueof_fncd_236 = ( unsigned_t )( TFN_FILESYS_OPENDIR ); const unsigned_t TOPPERS_cfg_valueof_svcatr_236 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_236 = ( unsigned_t )( 1024 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_237 = ( unsigned_t ) ( TDOM_KERNEL );
#line 40 "../../target/ev3_gcc/pil/pil.cfg"
const unsigned_t TOPPERS_cfg_static_api_237 = 237;
const unsigned_t TOPPERS_cfg_valueof_fncd_237 = ( unsigned_t )( TFN_FILESYS_READDIR ); const unsigned_t TOPPERS_cfg_valueof_svcatr_237 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_237 = ( unsigned_t )( 1024 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_238 = ( unsigned_t ) ( TDOM_KERNEL );
#line 41 "../../target/ev3_gcc/pil/pil.cfg"
const unsigned_t TOPPERS_cfg_static_api_238 = 238;
const unsigned_t TOPPERS_cfg_valueof_fncd_238 = ( unsigned_t )( TFN_FILESYS_CLOSEDIR ); const unsigned_t TOPPERS_cfg_valueof_svcatr_238 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_238 = ( unsigned_t )( 1024 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_239 = ( unsigned_t ) ( TDOM_KERNEL );
#line 42 "../../target/ev3_gcc/pil/pil.cfg"
const unsigned_t TOPPERS_cfg_static_api_239 = 239;
const char TOPPERS_cfg_valueof_module_239[] = "driver_interface_filesys.o"; const unsigned_t TOPPERS_cfg_valueof_acptn1_239 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn2_239 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn3_239 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn4_239 = ( unsigned_t )( TACP_KERNEL ); 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 44 "../../target/ev3_gcc/pil/pil.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 8 "../../target/ev3_gcc/platform/platform.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_240 = ( unsigned_t ) ( TDOM_KERNEL );
#line 9 "../../target/ev3_gcc/platform/platform.cfg"
const unsigned_t TOPPERS_cfg_static_api_240 = 240;
#define EV3_INIT_TASK	(<>)

#line 9 "../../target/ev3_gcc/platform/platform.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_240 = ( unsigned_t )( TA_ACT ); const signed_t TOPPERS_cfg_valueof_itskpri_240 = ( signed_t )( TPRI_INIT_TASK ); const unsigned_t TOPPERS_cfg_valueof_stksz_240 = ( unsigned_t )( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_241 = ( unsigned_t ) ( TDOM_KERNEL );
#line 10 "../../target/ev3_gcc/platform/platform.cfg"
const unsigned_t TOPPERS_cfg_static_api_241 = 241;
#define PLATFORM_BUSY_TASK	(<>)

#line 10 "../../target/ev3_gcc/platform/platform.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_241 = ( unsigned_t )( TA_ACT ); const signed_t TOPPERS_cfg_valueof_itskpri_241 = ( signed_t )( TPRI_PLATFORM_BUSY ); const unsigned_t TOPPERS_cfg_valueof_stksz_241 = ( unsigned_t )( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_242 = ( unsigned_t ) ( TDOM_KERNEL );
#line 11 "../../target/ev3_gcc/platform/platform.cfg"
const unsigned_t TOPPERS_cfg_static_api_242 = 242;
#define EV3RT_LOGTASK	(<>)

#line 11 "../../target/ev3_gcc/platform/platform.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_242 = ( unsigned_t )( TA_NULL ); const signed_t TOPPERS_cfg_valueof_itskpri_242 = ( signed_t )( LOGTASK_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_242 = ( unsigned_t )( LOGTASK_STACK_SIZE ); 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 12 "../../target/ev3_gcc/platform/platform.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#if !defined(OMIT_DEFAULT_EXCHDR)

#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 18 "../../target/ev3_gcc/platform/platform.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_243 = ( unsigned_t ) ( TDOM_KERNEL );
#line 19 "../../target/ev3_gcc/platform/platform.cfg"
const unsigned_t TOPPERS_cfg_static_api_243 = 243;
const unsigned_t TOPPERS_cfg_valueof_excno_243 = ( unsigned_t )( EXCH_NO_PABORT ); const unsigned_t TOPPERS_cfg_valueof_excatr_243 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_244 = ( unsigned_t ) ( TDOM_KERNEL );
#line 20 "../../target/ev3_gcc/platform/platform.cfg"
const unsigned_t TOPPERS_cfg_static_api_244 = 244;
const unsigned_t TOPPERS_cfg_valueof_excno_244 = ( unsigned_t )( EXCH_NO_DABORT ); const unsigned_t TOPPERS_cfg_valueof_excatr_244 = ( unsigned_t )( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 21 "../../target/ev3_gcc/platform/platform.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#endif

#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 9 "app.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_245 = ( unsigned_t ) ( TDOM_KERNEL );
#line 11 "app.cfg"
const unsigned_t TOPPERS_cfg_static_api_245 = 245;
#define APP_STATUS_FLAG	(<>)

#line 11 "app.cfg"
const unsigned_t TOPPERS_cfg_valueof_flgatr_245 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_iflgptn_245 = ( unsigned_t )( APP_STATUS_UNLOAD ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_246 = ( unsigned_t ) ( TDOM_KERNEL );
#line 13 "app.cfg"
const unsigned_t TOPPERS_cfg_static_api_246 = 246;
#define APP_TERM_TASK	(<>)

#line 13 "app.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_246 = ( unsigned_t )( TA_NULL ); const signed_t TOPPERS_cfg_valueof_itskpri_246 = ( signed_t )( TPRI_APP_TERM_TASK ); const unsigned_t TOPPERS_cfg_valueof_stksz_246 = ( unsigned_t )( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_247 = ( unsigned_t ) ( TDOM_KERNEL );
#line 18 "app.cfg"
const unsigned_t TOPPERS_cfg_static_api_247 = 247;
const unsigned_t TOPPERS_cfg_valueof_excno_247 = ( unsigned_t )( EXCH_NO_PABORT ); const unsigned_t TOPPERS_cfg_valueof_excatr_247 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_248 = ( unsigned_t ) ( TDOM_KERNEL );
#line 19 "app.cfg"
const unsigned_t TOPPERS_cfg_static_api_248 = 248;
const unsigned_t TOPPERS_cfg_valueof_excno_248 = ( unsigned_t )( EXCH_NO_DABORT ); const unsigned_t TOPPERS_cfg_valueof_excatr_248 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_249 = ( unsigned_t ) ( TDOM_KERNEL );
#line 21 "app.cfg"
const unsigned_t TOPPERS_cfg_static_api_249 = 249;
const char TOPPERS_cfg_valueof_module_249[] = "app.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_250 = ( unsigned_t ) ( TDOM_KERNEL );
#line 22 "app.cfg"
const unsigned_t TOPPERS_cfg_static_api_250 = 250;
const char TOPPERS_cfg_valueof_module_250[] = "apploader.o"; const unsigned_t TOPPERS_cfg_valueof_DOMAIN_251 = ( unsigned_t ) ( TDOM_KERNEL );
#line 23 "app.cfg"
const unsigned_t TOPPERS_cfg_static_api_251 = 251;
const char TOPPERS_cfg_valueof_module_251[] = "cli_main.o"; 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 24 "app.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 5 "../loader/zmodem/zmodem.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_252 = ( unsigned_t ) ( TDOM_KERNEL );
#line 7 "../loader/zmodem/zmodem.cfg"
const unsigned_t TOPPERS_cfg_static_api_252 = 252;
#define ZMODEM_RECV_TASK	(<>)

#line 7 "../loader/zmodem/zmodem.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_252 = ( unsigned_t )( TA_NULL ); const signed_t TOPPERS_cfg_valueof_itskpri_252 = ( signed_t )( TMIN_APP_TPRI ); const unsigned_t TOPPERS_cfg_valueof_stksz_252 = ( unsigned_t )( STACK_SIZE ); 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 9 "../loader/zmodem/zmodem.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#line 11 "../loader/zmodem/zmodem.cfg"
const unsigned_t TOPPERS_cfg_static_api_253 = 253;
const char TOPPERS_cfg_valueof_module_253[] = "zmodem-toppers.o"; const unsigned_t TOPPERS_cfg_valueof_acptn1_253 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn2_253 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn3_253 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn4_253 = ( unsigned_t )( TACP_KERNEL ); 
#line 12 "../loader/zmodem/zmodem.cfg"
const unsigned_t TOPPERS_cfg_static_api_254 = 254;
const char TOPPERS_cfg_valueof_module_254[] = "crc16.o"; const unsigned_t TOPPERS_cfg_valueof_acptn1_254 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn2_254 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn3_254 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn4_254 = ( unsigned_t )( TACP_KERNEL ); 
#line 13 "../loader/zmodem/zmodem.cfg"
const unsigned_t TOPPERS_cfg_static_api_255 = 255;
const char TOPPERS_cfg_valueof_module_255[] = "crc32.o"; const unsigned_t TOPPERS_cfg_valueof_acptn1_255 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn2_255 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn3_255 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn4_255 = ( unsigned_t )( TACP_KERNEL ); /* #include "dmloader.h" */

#ifndef TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED
#define TOPPERS_cfg_valueof_TDOM_KERNEL_DEFINED 1

#line 7 "../../target/ev3_gcc/dmloader/dmloader.cfg"
const unsigned_t TOPPERS_cfg_valueof_TDOM_KERNEL = ( unsigned_t ) (-1);

#endif
#define TOPPERS_cfg_inside_of_TDOM_KERNEL
const unsigned_t TOPPERS_cfg_valueof_DOMAIN_256 = ( unsigned_t ) ( TDOM_KERNEL );
#line 9 "../../target/ev3_gcc/dmloader/dmloader.cfg"
const unsigned_t TOPPERS_cfg_static_api_256 = 256;
const unsigned_t TOPPERS_cfg_valueof_iniatr_256 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_257 = ( unsigned_t ) ( TDOM_KERNEL );
#line 10 "../../target/ev3_gcc/dmloader/dmloader.cfg"
const unsigned_t TOPPERS_cfg_static_api_257 = 257;
#define DMLOADER_MTX	(<>)

#line 10 "../../target/ev3_gcc/dmloader/dmloader.cfg"
const unsigned_t TOPPERS_cfg_valueof_mtxatr_257 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_258 = ( unsigned_t ) ( TDOM_KERNEL );
#line 12 "../../target/ev3_gcc/dmloader/dmloader.cfg"
const unsigned_t TOPPERS_cfg_static_api_258 = 258;
const unsigned_t TOPPERS_cfg_valueof_fncd_258 = ( unsigned_t )( TFN_LDR_INS_LDM ); const unsigned_t TOPPERS_cfg_valueof_svcatr_258 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_258 = ( unsigned_t )( 1024 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_259 = ( unsigned_t ) ( TDOM_KERNEL );
#line 13 "../../target/ev3_gcc/dmloader/dmloader.cfg"
const unsigned_t TOPPERS_cfg_static_api_259 = 259;
const unsigned_t TOPPERS_cfg_valueof_fncd_259 = ( unsigned_t )( TFN_LDR_RMV_LDM ); const unsigned_t TOPPERS_cfg_valueof_svcatr_259 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_stksz_259 = ( unsigned_t )( 1024 ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_260 = ( unsigned_t ) ( TDOM_KERNEL );
#line 15 "../../target/ev3_gcc/dmloader/dmloader.cfg"
const unsigned_t TOPPERS_cfg_static_api_260 = 260;
const char TOPPERS_cfg_valueof_module_260[] = "dmloader.o"; const unsigned_t TOPPERS_cfg_valueof_acptn1_260 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn2_260 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn3_260 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn4_260 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_DOMAIN_261 = ( unsigned_t ) ( TDOM_KERNEL );
#line 16 "../../target/ev3_gcc/dmloader/dmloader.cfg"
const unsigned_t TOPPERS_cfg_static_api_261 = 261;
const char TOPPERS_cfg_valueof_module_261[] = "elf32.o"; const unsigned_t TOPPERS_cfg_valueof_acptn1_261 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn2_261 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn3_261 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn4_261 = ( unsigned_t )( TACP_KERNEL ); 
#ifndef TOPPERS_cfg_inside_of_TDOM_KERNEL

#line 18 "../../target/ev3_gcc/dmloader/dmloader.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_TDOM_KERNEL


#line 20 "../../target/ev3_gcc/dmloader/dmloader.cfg"
const unsigned_t TOPPERS_cfg_static_api_262 = 262;
const char TOPPERS_cfg_valueof_section_262[] = ".app_text_mempool"; const unsigned_t TOPPERS_cfg_valueof_mematr_262 = ( unsigned_t )( TA_NULL ); const char TOPPERS_cfg_valueof_memreg_262[] = "RAM"; const unsigned_t TOPPERS_cfg_valueof_acptn1_262 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn2_262 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn3_262 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn4_262 = ( unsigned_t )( TACP_KERNEL ); 
#line 21 "../../target/ev3_gcc/dmloader/dmloader.cfg"
const unsigned_t TOPPERS_cfg_static_api_263 = 263;
const char TOPPERS_cfg_valueof_section_263[] = ".app_data_mempool"; const unsigned_t TOPPERS_cfg_valueof_mematr_263 = ( unsigned_t )( TA_NULL ); const char TOPPERS_cfg_valueof_memreg_263[] = "RAM"; const unsigned_t TOPPERS_cfg_valueof_acptn1_263 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn2_263 = ( unsigned_t )( TACP_SHARED ); const unsigned_t TOPPERS_cfg_valueof_acptn3_263 = ( unsigned_t )( TACP_KERNEL ); const unsigned_t TOPPERS_cfg_valueof_acptn4_263 = ( unsigned_t )( TACP_KERNEL ); 
#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_APP
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_TDOM_KERNEL
#error missing '}'
#endif

