/*
 * このファイルは tecsgen によりテンプレートとして自動生成されました
 * このファイルを編集して使用することが意図されていますが
 * tecsgen の再実行により上書きされてしまうため、通常
 *   gen/tTLSFStatistics_template.c => src/tTLSFStatistics.c
 * のように名前, フォルダを変更してから修正します
 */
/* #[<PREAMBLE>]#
 * #[<...>]# から #[</...>]# で囲まれたコメントは編集しないでください
 * tecsmerge によるマージに使用されます
 *
 * 呼び口関数 #_TCPF_#
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
 *   size_t         cMallocStatistics_getUsedSize( );
 *   size_t         cMallocStatistics_getMaxSize( );
 *
 * #[</PREAMBLE>]# */

/* プロトタイプ宣言や変数の定義をここに書きます #_PAC_# */
#include "tTLSFStatistics_tecsgen.h"

#ifndef E_OK
#define	E_OK	0		/* success */
#define	E_ID	(-18)	/* illegal ID */
#endif

#include <t_syslog.h>

bool_t flag = false;
SYSTIM start_time = 0;

/* 受け口関数 #_TEPF_# */
/* #[<ENTRY_PORT>]# eBody
 * entry port: eBody
 * signature:  sTaskBody
 * context:    task
 * #[</ENTRY_PORT>]# */

/* #[<ENTRY_FUNC>]# eBody_main
 * name:         eBody_main
 * global_name:  tTLSFStatistics_eBody_main
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
void
eBody_main(CELLIDX idx)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
	} /* end if VALID_IDX(idx) */

    if (flag == false) {
    	flag = true;
    	getTime(&start_time);
    }
#ifndef SEQUENTIAL
    SYSTIM now_time;
	getTime(&now_time);
	syslog(LOG_EMERG, "[TLSF]: %d ms || %d bytes", now_time - start_time, cMallocStatistics_getUsedSize());
#endif
}

/* #[<POSTAMBLE>]#
 *   これより下に非受け口関数を書きます
 * #[</POSTAMBLE>]#*/
