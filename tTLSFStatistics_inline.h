#ifndef tTLSFStatistics__INLINE_H
#define tTLSFStatistics__INLINE_H

<<<<<<< HEAD
/*
 * §≥§Œ•’•°•§•Î§œ tecsgen §À§Ë§Í•∆•Û•◊•Ï°º•»§»§∑§∆º´∆∞¿∏¿Æ§µ§Ï§ﬁ§∑§ø
 * §≥§Œ•’•°•§•Î§Ú ‘Ω∏§∑§∆ª»Õ—§π§Î§≥§»§¨∞’øﬁ§µ§Ï§∆§§§ﬁ§π§¨
 * tecsgen §Œ∫∆º¬π‘§À§Ë§ÍæÂΩÒ§≠§µ§Ï§∆§∑§ﬁ§¶§ø§·°¢ƒÃæÔ
 *   gen/tTLSFStatistics_inline_template.h => src/tTLSFStatistics_inline.h
 * §Œ§Ë§¶§ÀÃæ¡∞, •’•©•Î•¿§Ú —ππ§∑§∆§´§ÈΩ§¿µ§∑§ﬁ§π
 */
/* #[<PREAMBLE>]#
 * #[<...>]# §´§È #[</...>]# §«∞œ§ﬁ§Ï§ø•≥•·•Û•»§œ ‘Ω∏§∑§ §§§«§Ø§¿§µ§§
 * tecsmerge §À§Ë§Î•ﬁ°º•∏§Àª»Õ—§µ§Ï§ﬁ§π
 *
 * ¬∞¿≠•¢•Ø•ª•π•ﬁ•Ø•Ì #_CAAM_#
 * maxSize          size_t           ATTR_maxSize    
 * time             int32_t*         VAR_time        
 * malloc           int32_t*         VAR_malloc      
 * free             int32_t*         VAR_free        
 * mallocNum        int32_t          VAR_mallocNum   
 * reallocNum       int32_t          VAR_reallocNum  
 * freeNum          int32_t          VAR_freeNum     
 *
 * ∏∆§”∏˝¥ÿøÙ #_TCPF_#
=======
#include "t_syslog.h"

/*
 * ¬§¬≥¬§√é¬•√ï¬•¬°¬•¬§¬•√´¬§√è tecsgen ¬§√ã¬§√®¬§√™¬•√Ü¬•√≥¬•√ó¬•√¨¬°¬º¬•√à¬§√à¬§¬∑¬§√Ü¬º¬´√Ü¬∞√Ä¬∏√Ä¬Æ¬§¬µ¬§√¨¬§√û¬§¬∑¬§¬ø
 * ¬§¬≥¬§√é¬•√ï¬•¬°¬•¬§¬•√´¬§√≤√ä√î¬Ω¬∏¬§¬∑¬§√Ü¬ª√à√ç√ë¬§¬π¬§√´¬§¬≥¬§√à¬§¬¨¬∞√ï¬ø√û¬§¬µ¬§√¨¬§√Ü¬§¬§¬§√û¬§¬π¬§¬¨
 * tecsgen ¬§√é¬∫√Ü¬º√Ç¬π√î¬§√ã¬§√®¬§√™¬æ√•¬Ω√±¬§¬≠¬§¬µ¬§√¨¬§√Ü¬§¬∑¬§√û¬§¬¶¬§¬ø¬§√°¬°¬¢√Ñ√å¬æ√Ø
 *   gen/tTLSFStatistics_inline_template.h => src/tTLSFStatistics_inline.h
 * ¬§√é¬§√®¬§¬¶¬§√ã√å¬æ√Å¬∞, ¬•√ï¬•¬©¬•√´¬•√Ä¬§√≤√ä√ë¬π¬π¬§¬∑¬§√Ü¬§¬´¬§√©¬Ω¬§√Ä¬µ¬§¬∑¬§√û¬§¬π
 */
/* #[<PREAMBLE>]#
 * #[<...>]# ¬§¬´¬§√© #[</...>]# ¬§√á¬∞√è¬§√û¬§√¨¬§¬ø¬•¬≥¬•√°¬•√≥¬•√à¬§√è√ä√î¬Ω¬∏¬§¬∑¬§√ä¬§¬§¬§√á¬§¬Ø¬§√Ä¬§¬µ¬§¬§
 * tecsmerge ¬§√ã¬§√®¬§√´¬•√û¬°¬º¬•¬∏¬§√ã¬ª√à√ç√ë¬§¬µ¬§√¨¬§√û¬§¬π
 *
 * ¬∏√Ü¬§√ì¬∏√Ω¬¥√ò¬ø√¥ #_TCPF_#
>>>>>>> feature-statistics
 * require port: signature:sKernel context:task
 *   ER             sleep( );
 *   ER             sleepTimeout( TMO timeout );
 *   ER             delay( RELTIM delayTime );
 *   ER             exitTask( );
 *   ER             getTaskId( ID* p_taskId );
 *   ER             rotateReadyQueue( PRI taskPriority );
 *   ER             getTime( SYSTIM* p_systemTime );
 *   ER             getMicroTime( SYSUTM* p_systemMicroTime );
 *   ER             lockCpu( );
 *   ER             unlockCpu( );
 *   ER             disableDispatch( );
 *   ER             enableDispatch( );
 *   ER             disableTaskException( );
 *   ER             enableTaskException( );
 *   ER             changeInterruptPriorityMask( PRI interruptPriority );
 *   ER             getInterruptPriorityMask( PRI* p_interruptPriority );
 *   ER             exitKernel( );
 *   bool_t         senseContext( );
 *   bool_t         senseLock( );
 *   bool_t         senseDispatch( );
 *   bool_t         senseDispatchPendingState( );
 *   bool_t         senseKernel( );
 * call port: cMalloc signature: sMalloc context:task
 *   int            cMalloc_initializeMemoryPool( );
 *   void*          cMalloc_calloc( size_t nelem, size_t elem_size );
 *   void*          cMalloc_malloc( size_t size );
 *   void*          cMalloc_realloc( const void* ptr, size_t new_size );
 *   void           cMalloc_free( const void* ptr );
 * call port: cMallocStatistics signature: sMallocStatistics context:task
<<<<<<< HEAD
 *   size_t         cMallocStatistics_getMaxSize( );
 *   size_t         cMallocStatistics_getUsableSize( );
 *   size_t         cMallocStatistics_getUsedSize( );
 *   size_t         cMallocStatistics_getMallocSize( );
 *   size_t         cMallocStatistics_getFreeSize( );
 *   size_t         cMallocStatistics_getReallocSize( );
 *
 * #[</PREAMBLE>]# */
#include <t_syslog.h>
#include <stdio.h>
/* ºı§±∏˝¥ÿøÙ #_TEPF_# */
=======
 *   size_t         cMallocStatistics_getUsedSize( );
 *   size_t         cMallocStatistics_getMaxSize( );
 *
 * #[</PREAMBLE>]# */

#ifdef SEQUENTIAL
extern SYSTIM start_time;
#endif

/* ¬º√µ¬§¬±¬∏√Ω¬¥√ò¬ø√¥ #_TEPF_# */
>>>>>>> feature-statistics
/* #[<ENTRY_PORT>]# eMalloc
 * entry port: eMalloc
 * signature:  sMalloc
 * context:    task
 * #[</ENTRY_PORT>]# */

/* #[<ENTRY_FUNC>]# eMalloc_initializeMemoryPool
 * name:         eMalloc_initializeMemoryPool
 * global_name:  tTLSFStatistics_eMalloc_initializeMemoryPool
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
Inline int
eMalloc_initializeMemoryPool(CELLIDX idx)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
<<<<<<< HEAD
		/* •®•È°ºΩËÕ˝•≥°º•…§Ú§≥§≥§Àµ≠Ω“§∑§ﬁ§π */
	} /* end if VALID_IDX(idx) */

	/* §≥§≥§ÀΩËÕ˝À‹¬Œ§Úµ≠Ω“§∑§ﬁ§π #_TEFB_# */
	VAR_mallocNum = 0;
	VAR_reallocNum = 0;
	VAR_freeNum = 0;
 	return cMalloc_initializeMemoryPool();
=======
	} /* end if VALID_IDX(idx) */

  	return cMalloc_initializeMemoryPool();
>>>>>>> feature-statistics
}

/* #[<ENTRY_FUNC>]# eMalloc_calloc
 * name:         eMalloc_calloc
 * global_name:  tTLSFStatistics_eMalloc_calloc
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
Inline void*
eMalloc_calloc(CELLIDX idx, size_t nelem, size_t elem_size)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
<<<<<<< HEAD
		/* •®•È°ºΩËÕ˝•≥°º•…§Ú§≥§≥§Àµ≠Ω“§∑§ﬁ§π */
	} /* end if VALID_IDX(idx) */

	/* §≥§≥§ÀΩËÕ˝À‹¬Œ§Úµ≠Ω“§∑§ﬁ§π #_TEFB_# */
	return cMalloc_calloc(nelem, elem_size);
=======
	} /* end if VALID_IDX(idx) */

    void *ret;
#ifdef SEQUENTIAL
	SYSTIM now_time;
	getTime(&now_time);
#endif
    ret = cMalloc_calloc(nelem, elem_size);
#ifdef SEQUENTIAL
    syslog(LOG_EMERG, "[TLSF] %d ms || calloc: %d bytes, total: %d bytes",
    		now_time - start_time, nelem * elem_size, cMallocStatistics_getUsedSize());
#endif
    return ret;
>>>>>>> feature-statistics
}

/* #[<ENTRY_FUNC>]# eMalloc_malloc
 * name:         eMalloc_malloc
 * global_name:  tTLSFStatistics_eMalloc_malloc
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
Inline void*
eMalloc_malloc(CELLIDX idx, size_t size)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
<<<<<<< HEAD
		/* •®•È°ºΩËÕ˝•≥°º•…§Ú§≥§≥§Àµ≠Ω“§∑§ﬁ§π */
	} /* end if VALID_IDX(idx) */

	/* §≥§≥§ÀΩËÕ˝À‹¬Œ§Úµ≠Ω“§∑§ﬁ§π #_TEFB_# */
	VAR_mallocNum++;
	return cMalloc_malloc(size);

=======
	} /* end if VALID_IDX(idx) */

	void *ret;
#ifdef SEQUENTIAL
	SYSTIM now_time;
	getTime(&now_time);
#endif
	ret = cMalloc_malloc(size);
#ifdef SEQUENTIAL
	syslog(LOG_EMERG, "[TLSF] %d ms || malloc: %d bytes, total: %d bytes",
			now_time - start_time, size, cMallocStatistics_getUsedSize());
#endif
    return ret;
>>>>>>> feature-statistics
}

/* #[<ENTRY_FUNC>]# eMalloc_realloc
 * name:         eMalloc_realloc
 * global_name:  tTLSFStatistics_eMalloc_realloc
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
Inline void*
eMalloc_realloc(CELLIDX idx, const void* ptr, size_t new_size)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
<<<<<<< HEAD
		/* •®•È°ºΩËÕ˝•≥°º•…§Ú§≥§≥§Àµ≠Ω“§∑§ﬁ§π */
	} /* end if VALID_IDX(idx) */

	/* §≥§≥§ÀΩËÕ˝À‹¬Œ§Úµ≠Ω“§∑§ﬁ§π #_TEFB_# */
	VAR_reallocNum++;
	return cMalloc_realloc((void *)ptr, new_size);

=======
	} /* end if VALID_IDX(idx) */

	void *ret;
#ifdef SEQUENTIAL
	SYSTIM now_time;
	getTime(&now_time);
#endif
	ret = cMalloc_realloc(ptr, new_size);
#ifdef SEQUENTIAL
	syslog(LOG_EMERG, "[TLSF] %d ms || realloc: %d bytes, total: %d bytes",
			now_time - start_time, new_size, cMallocStatistics_getUsedSize());
#endif
    return ret;
>>>>>>> feature-statistics
}

/* #[<ENTRY_FUNC>]# eMalloc_free
 * name:         eMalloc_free
 * global_name:  tTLSFStatistics_eMalloc_free
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
Inline void
eMalloc_free(CELLIDX idx, const void* ptr)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
<<<<<<< HEAD
		/* •®•È°ºΩËÕ˝•≥°º•…§Ú§≥§≥§Àµ≠Ω“§∑§ﬁ§π */
	} /* end if VALID_IDX(idx) */

	/* §≥§≥§ÀΩËÕ˝À‹¬Œ§Úµ≠Ω“§∑§ﬁ§π #_TEFB_# */
	VAR_freeNum++;
	return cMalloc_free((void *)ptr);

}

/* #[<POSTAMBLE>]#
 *   §≥§Ï§Ë§Í≤º§À»Ûºı§±∏˝¥ÿøÙ§ÚΩÒ§≠§ﬁ§π
=======
	} /* end if VALID_IDX(idx) */

#ifdef SEQUENTIAL
	SYSTIM now_time;
	getTime(&now_time);
#endif
	cMalloc_free(ptr);
#ifdef SEQUENTIAL
    syslog(LOG_EMERG, "[TLSF] %d ms || free:  , total: %d bytes",
    		now_time - start_time, cMallocStatistics_getUsedSize());
#endif
    return;
}

/* #[<POSTAMBLE>]#
 *   ¬§¬≥¬§√¨¬§√®¬§√™¬≤¬º¬§√ã√à√≥¬º√µ¬§¬±¬∏√Ω¬¥√ò¬ø√¥¬§√≤¬Ω√±¬§¬≠¬§√û¬§¬π
>>>>>>> feature-statistics
 * #[</POSTAMBLE>]#*/

#endif /* tTLSFStatistics_INLINEH */
