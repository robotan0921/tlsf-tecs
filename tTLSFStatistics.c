/*
 * ���Υե������ tecsgen �ˤ��ƥ�ץ졼�ȤȤ��Ƽ�ư��������ޤ���
 * ���Υե�������Խ����ƻ��Ѥ��뤳�Ȥ��տޤ���Ƥ��ޤ���
 * tecsgen �κƼ¹Ԥˤ���񤭤���Ƥ��ޤ����ᡢ�̾�
 *   gen/tTLSFStatistics_template.c => src/tTLSFStatistics.c
 * �Τ褦��̾��, �ե�������ѹ����Ƥ��齤�����ޤ�
 */
/* #[<PREAMBLE>]#
 * #[<...>]# ���� #[</...>]# �ǰϤޤ줿�����Ȥ��Խ����ʤ��Ǥ�������
 * tecsmerge �ˤ��ޡ����˻��Ѥ���ޤ�
 *
 * �ƤӸ��ؿ� #_TCPF_#
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
 * call port: cDataqueue signature: sDataqueue context:task
 *   ER             cDataqueue_send( intptr_t data );
 *   ER             cDataqueue_sendPolling( intptr_t data );
 *   ER             cDataqueue_sendTimeout( intptr_t data, TMO timeout );
 *   ER             cDataqueue_sendForce( intptr_t data );
 *   ER             cDataqueue_receive( intptr_t* p_data );
 *   ER             cDataqueue_receivePolling( intptr_t* p_data );
 *   ER             cDataqueue_receiveTimeout( intptr_t* p_data, TMO timeout );
 *   ER             cDataqueue_initialize( );
 *   ER             cDataqueue_refer( T_RDTQ* pk_dataqueueStatus );
 *
 * #[</PREAMBLE>]# */

/* �ץ�ȥ�����������ѿ�������򤳤��˽񤭤ޤ� #_PAC_# */
#include "tTLSFStatistics_tecsgen.h"

#ifndef E_OK
#define	E_OK	0		/* success */
#define	E_ID	(-18)	/* illegal ID */
#endif

#include <t_syslog.h>

bool_t flag = false;
SYSTIM start_time = 0;

/* �������ؿ� #_TEPF_# */
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
#ifdef SEQUENTIAL
#else
    SYSTIM now_time;
	getTime(&now_time);
#ifdef TLSF_USE_SD
	// TODO: Fix for ensuring real-time
	cDataqueue_send( now_time - start_time );
	cDataqueue_send( cMallocStatistics_getUsedSize() );
#else
	syslog(LOG_EMERG, "[TLSF]: %d ms || %d bytes", now_time - start_time, cMallocStatistics_getUsedSize());
#endif 	/* end of #ifdef TLSF_USE_SD */
#endif 	/* end of #ifdef SEQUENTIAL */
}

/* #[<POSTAMBLE>]#
 *   �����겼����������ؿ���񤭤ޤ�
 * #[</POSTAMBLE>]#*/
