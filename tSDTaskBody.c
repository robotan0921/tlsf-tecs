/*
 * このファイルは tecsgen によりテンプレートとして自動生成されました
 * このファイルを編集して使用することが意図されていますが
 * tecsgen の再実行により上書きされてしまうため、通常
 *   gen/tSDTaskBody_template.c => src/tSDTaskBody.c
 * のように名前, フォルダを変更してから修正します
 */
/* #[<PREAMBLE>]#
 * #[<...>]# から #[</...>]# で囲まれたコメントは編集しないでください
 * tecsmerge によるマージに使用されます
 *
 * 属性アクセスマクロ #_CAAM_#
 * fileName         char*            ATTR_fileName
 * fp               FILE*            VAR_fp
 *
 * 呼び口関数 #_TCPF_#
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

/* プロトタイプ宣言や変数の定義をここに書きます #_PAC_# */
#include "tSDTaskBody_tecsgen.h"

#ifndef E_OK
#define	E_OK	0		/* success */
#define	E_ID	(-18)	/* illegal ID */
#endif

#include <t_syslog.h>
#include <ff.h>
#include <ffarch.h>

bool_t sd_open = false;

/* 受け口関数 #_TEPF_# */
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
#ifdef TLSF_USE_SD
	int time, size;
	int count = 0;
	FATFS fs;         	/* Work area (filesystem object) for logical drives */
    FIL fp;      		/* File objects */

	if (sd_open == false) {
    	sd_open = true;
		f_mount(&fs, "1:", 0);
    	f_open(&fp, "1:log.csv", FA_WRITE | FA_CREATE_ALWAYS);
    }

	while (true) {
		if (count++ > 1000) {
            f_sync(&fp);
            count = 0;
            slp_tsk();
        }
        cDataqueue_receive( &time );
		cDataqueue_receive( &size );
        f_printf(&fp, "%d,%d\n", time, size);
	}
#else

#endif 	/* end of #ifdef TLSF_USE_SD */
}

/* #[<POSTAMBLE>]#
 *   これより下に非受け口関数を書きます
 * #[</POSTAMBLE>]#*/
