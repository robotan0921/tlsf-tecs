/*
 * ���Υե������ tecsgen �ˤ��ƥ�ץ졼�ȤȤ��Ƽ�ư��������ޤ���
 * ���Υե�������Խ����ƻ��Ѥ��뤳�Ȥ��տޤ���Ƥ��ޤ���
 * tecsgen �κƼ¹Ԥˤ���񤭤���Ƥ��ޤ����ᡢ�̾�
 *   gen/tSDTaskBody_template.c => src/tSDTaskBody.c
 * �Τ褦��̾��, �ե�������ѹ����Ƥ��齤�����ޤ�
 */
/* #[<PREAMBLE>]#
 * #[<...>]# ���� #[</...>]# �ǰϤޤ줿�����Ȥ��Խ����ʤ��Ǥ�������
 * tecsmerge �ˤ��ޡ����˻��Ѥ���ޤ�
 *
 * °�����������ޥ��� #_CAAM_#
 * fileName         char*            ATTR_fileName
 * fp               FILE*            VAR_fp
 *
 * �ƤӸ��ؿ� #_TCPF_#
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
#include "tSDTaskBody_tecsgen.h"

#ifndef E_OK
#define	E_OK	0		/* success */
#define	E_ID	(-18)	/* illegal ID */
#endif

#include <t_syslog.h>

/* �������ؿ� #_TEPF_# */
/* #[<ENTRY_PORT>]# eBody
 * entry port: eBody
 * signature:  sTaskBody
 * context:    task
 * #[</ENTRY_PORT>]# */

/* #[<ENTRY_FUNC>]# eBody_main
 * name:         eBody_main
 * global_name:  tSDTaskBody_eBody_main
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

	int time, size;
	int count = 0;

	VAR_fp = fopen(ATTR_fileName, "a");

	while (true) {
		if (count++ > 100) {
			fclose(VAR_fp);
			VAR_fp = fopen(ATTR_fileName, "a");
			count = 0;
		}
		cDataqueue_receive( &time );
		cDataqueue_receive( &size );
		fprintf(VAR_fp, "%d,%d\n", time, size);
	}
}

/* #[<POSTAMBLE>]#
 *   �����겼����������ؿ���񤭤ޤ�
 * #[</POSTAMBLE>]#*/
