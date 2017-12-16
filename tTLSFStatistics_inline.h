#ifndef tTLSFStatistics__INLINE_H
#define tTLSFStatistics__INLINE_H

<<<<<<< HEAD
/*
 * このファイルは tecsgen によりテンプレートとして自動生成されました
 * このファイルを編集して使用することが意図されていますが
 * tecsgen の再実行により上書きされてしまうため、通常
 *   gen/tTLSFStatistics_inline_template.h => src/tTLSFStatistics_inline.h
 * のように名前, フォルダを変更してから修正します
 */
/* #[<PREAMBLE>]#
 * #[<...>]# から #[</...>]# で囲まれたコメントは編集しないでください
 * tecsmerge によるマージに使用されます
 *
 * 属性アクセスマクロ #_CAAM_#
 * maxSize          size_t           ATTR_maxSize    
 * time             int32_t*         VAR_time        
 * malloc           int32_t*         VAR_malloc      
 * free             int32_t*         VAR_free        
 * mallocNum        int32_t          VAR_mallocNum   
 * reallocNum       int32_t          VAR_reallocNum  
 * freeNum          int32_t          VAR_freeNum     
 *
 * 呼び口関数 #_TCPF_#
=======
#include "t_syslog.h"

/*
 * 造続造�ﾂッ�促臓促造促谷造�� tecsgen 造��造竪造棚促��促坦促��促狸臓村促��造��造揃造��村束��属��存��速造袖造狸造��造揃造多
 * 造続造�ﾂッ�促臓促造促谷造嘆����遜存造揃造��損������造孫造谷造続造��造測属��多��造袖造狸造��造造造��造孫造測
 * tecsgen 造�ﾂ挫�村��孫��造��造竪造棚他奪遜単造足造袖造狸造��造揃造��造側造多造叩臓蔵����他誰
 *   gen/tTLSFStatistics_inline_template.h => src/tTLSFStatistics_inline.h
 * 造�ﾂっ�造側造����他��属, 促��促息促谷促��造嘆����孫孫造揃造��造束造辿遜造��袖造揃造��造孫
 */
/* #[<PREAMBLE>]#
 * #[<...>]# 造束造辿 #[</...>]# 造��属�昣��造狸造多促続促叩促坦促��造������遜存造揃造��造造造��造俗造��造袖造造
 * tecsmerge 造��造竪造谷促��臓村促存造��損������造袖造狸造��造孫
 *
 * 存��造��存箪卒��多担 #_TCPF_#
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
/* 受け口関数 #_TEPF_# */
=======
 *   size_t         cMallocStatistics_getUsedSize( );
 *   size_t         cMallocStatistics_getMaxSize( );
 *
 * #[</PREAMBLE>]# */

#ifdef SEQUENTIAL
extern SYSTIM start_time;
#endif

/* 村探造賊存箪卒��多担 #_TEPF_# */
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
		/* エラー処理コードをここに記述します */
	} /* end if VALID_IDX(idx) */

	/* ここに処理本体を記述します #_TEFB_# */
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
		/* エラー処理コードをここに記述します */
	} /* end if VALID_IDX(idx) */

	/* ここに処理本体を記述します #_TEFB_# */
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
		/* エラー処理コードをここに記述します */
	} /* end if VALID_IDX(idx) */

	/* ここに処理本体を記述します #_TEFB_# */
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
		/* エラー処理コードをここに記述します */
	} /* end if VALID_IDX(idx) */

	/* ここに処理本体を記述します #_TEFB_# */
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
		/* エラー処理コードをここに記述します */
	} /* end if VALID_IDX(idx) */

	/* ここに処理本体を記述します #_TEFB_# */
	VAR_freeNum++;
	return cMalloc_free((void *)ptr);

}

/* #[<POSTAMBLE>]#
 *   これより下に非受け口関数を書きます
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
 *   造続造狸造竪造棚族村造����坦村探造賊存箪卒��多担造嘆遜単造足造��造孫
>>>>>>> feature-statistics
 * #[</POSTAMBLE>]#*/

#endif /* tTLSFStatistics_INLINEH */
