/*
 * このファイルは tecsgen によりテンプレートとして自動生成されました
 * このファイルを編集して使用することが意図されていますが
 * tecsgen の再実行により上書きされてしまうため、通常
 *   gen/tMainTaskBody_template.c => src/tMainTaskBody.c
 * のように名前, フォルダを変更してから修正します
 */
/* #[<PREAMBLE>]#
 * #[<...>]# から #[</...>]# で囲まれたコメントは編集しないでください
 * tecsmerge によるマージに使用されます
 *
 * #[</PREAMBLE>]# */

/* プロトタイプ宣言や変数の定義をここに書きます #_PAC_# */
#include "tMainTaskBody_tecsgen.h"

#ifndef E_OK
#define	E_OK	0		/* success */
#define	E_ID	(-18)	/* illegal ID */
#endif

#include <t_syslog.h>
#include <ff.h>
#include <ffarch.h>

/* 受け口関数 #_TEPF_# */
/* #[<ENTRY_PORT>]# eMainTask
 * entry port: eMainTask
 * signature:  sTaskBody
 * context:    task
 * #[</ENTRY_PORT>]# */

/* #[<ENTRY_FUNC>]# eMainTask_main
 * name:         eMainTask_main
 * global_name:  tMainTaskBody_eMainTask_main
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
void
eMainTask_main(CELLIDX idx)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* エラー処理コードをここに記述します */
	} /* end if VALID_IDX(idx) */

	/* ここに処理本体を記述します #_TEFB_# */
	syslog(LOG_NOTICE, "***** Main Task *****");

	/* Initialize FatFs */
	initialize_fatfs();

}

/* #[<POSTAMBLE>]#
 *   これより下に非受け口関数を書きます
 * #[</POSTAMBLE>]#*/
