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
 *   size_t         cMallocStatistics_getMaxSize( );
 *   size_t         cMallocStatistics_getUsableSize( );
 *   size_t         cMallocStatistics_getUsedSize( );
 *   size_t         cMallocStatistics_getMallocSize( );
 *   size_t         cMallocStatistics_getFreeSize( );
 *   size_t         cMallocStatistics_getReallocSize( );
 *
 * #[</PREAMBLE>]# */

/* プロトタイプ宣言や変数の定義をここに書きます #_PAC_# */
#include "tTLSFStatistics_tecsgen.h"

#ifndef E_OK
#define	E_OK	0		/* success */
#define	E_ID	(-18)	/* illegal ID */
#endif

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
		/* エラー処理コードをここに記述します */
	} /* end if VALID_IDX(idx) */

	/* ここに処理本体を記述します #_TEFB_# */
	syslog(LOG_NOTICE, "[malloc]: malloc size = %d, malloc number = %d",
								cMallocStatistics_getMallocSize(), VAR_mallocNum);
	syslog(LOG_NOTICE, "[malloc]: realloc size = %d, realloc number = %d",
								cMallocStatistics_getReallocSize(), VAR_reallocNum);
	syslog(LOG_NOTICE, "[malloc]: free size = %d, free number = %d",
								cMallocStatistics_getFreeSize(), VAR_freeNum);
}

/* #[<POSTAMBLE>]#
 *   これより下に非受け口関数を書きます
 * #[</POSTAMBLE>]#*/
