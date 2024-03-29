#
#  TOPPERS/HRP Kernel
#      Toyohashi Open Platform for Embedded Real-Time Systems/
#      High Reliable system Profile Kernel
#
#  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
#                              Toyohashi Univ. of Technology, JAPAN
#  Copyright (C) 2006-2014 by Embedded and Real-Time Systems Laboratory
#              Graduate School of Information Science, Nagoya Univ., JAPAN
#  Copyright (C) 2014-2015 by Osaka Univ., JAPAN
#
#  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
#  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
#  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
#  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
#      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
#      スコード中に含まれていること．
#  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
#      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
#      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
#      の無保証規定を掲載すること．
#  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
#      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
#      と．
#    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
#        作権表示，この利用条件および下記の無保証規定を掲載すること．
#    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
#        報告すること．
#  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
#      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
#      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
#      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
#      免責すること．
#
#  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
#  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
#  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
#  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
#  の責任を負わない．
#
#  $Id: Makefile 957 2014-01-02 07:00:50Z ertl-hiro $
#

#
# Functions
#
define print_cmd
  @printf "  %-7s %s\n" $1 $2 1>&2
endef

#
#  ターゲットの指定（Makefile.targetで上書きされるのを防ぐため）
#
all:

#
# SDのドライブ文字を指定
SD_DIR = /cygdrive/h/

#
#  ターゲット略称の定義
#
TARGET = ev3_gcc
MRUBY_DIR = ../mruby_app

#  mrubyのアプリケーションファイル名
# APP_NAME = battery_sample.rb
APP_NAME = button_sample.rb
# APP_NAME = color_sample.rb
# APP_NAME = color_sample2.rb
# APP_NAME = color_sample3.rb
# APP_NAME = ev3way_sample.rb
# APP_NAME = gyro_sample.rb
# APP_NAME = lcd_sample.rb
# APP_NAME = lcd_sample2.rb
# APP_NAME = lcd_sample3.rb
# APP_NAME = led_sample.rb
# APP_NAME = motor_sample.rb
# APP_NAME = motor_sample2.rb
# APP_NAME = rtos_sample.rb
# APP_NAME = speaker_sample.rb
# APP_NAME = speaker_sample2.rb
# APP_NAME = touch_sample.rb
# APP_NAME = ultrasonic_sample.rb

APP_RB = $(MRUBY_DIR)/$(APP_NAME)

#
#  プログラミング言語の定義
#
SRCLANG = c
ifeq ($(SRCLANG),c)
  LIBS = -lc -lm
endif
ifeq ($(SRCLANG),c++)
  USE_CXX = true
  CXXLIBS = -lstdc++ -lc -lm -lgcc
  #CXXRTS = crtbegin.o crtend.o
  #CXXRTS = cxxrt.o newlibrt.o
endif

#
#  ソースファイルのディレクトリの定義
#
SRCDIR = ../..

#

#  mruby 関係の設定
MRUBY_SRC_DIR = $(SRCDIR)/../mruby
MRUBY_LIB = $(MRUBY_SRC_DIR)/build/ARM/lib/libmruby.a -lm

# mruby compiler and test driver
ifeq ($(OS),Windows_NT)
MRBC = $(MRUBY_SRC_DIR)/bin/mrbc.exe
EXE := $(TARGET).exe
else
MRBC = $(MRUBY_SRC_DIR)/bin/mrbc
EXE := $(TARGET)
endif
#  オブジェクトファイル名の拡張子の設定
#
OBJEXT =

#
#  実行環境の定義（ターゲット依存に上書きされる場合がある）
#
DBGENV :=

#
#  カーネルライブラリ（libkernel.a）のディレクトリ名
#  （カーネルライブラリもmake対象にする時は，空に定義する）
#
KERNEL_LIB =

#
#  カーネルを関数単位でコンパイルするかどうかの定義
#
KERNEL_FUNCOBJS =

#
#  トレースログを取得するかどうかの定義
#
ENABLE_TRACE =

#
#  ユーティリティプログラムの名称
#
PERL = /usr/bin/perl
RUBY = /usr/bin/ruby
CFG = $(SRCDIR)/cfg/cfg/cfg


#mkimageの設定
#/usr/bin/などパスが通っている場合
#MKIMAGE = mkimage
#WINDOWSの場合
MKIMAGE = $(SRCDIR)/../bin/mkimage.exe


#
#  TECSインタフェースジェネレータ関係の定義
# tecsgen.rb (ruby + racc)を利用する場合は下記のRUBYLIBとTECSGENの定義を利用する

RUBYLIB = $(SRCDIR)/tecsgen/tecsgen -L.
TECSGEN = $(RUBY) $(SRCDIR)/tecsgen/tecsgen/tecsgen.rb -L $(RUBYLIB) -k euc --cpp="$(GCC_TARGET_PREFIX)gcc -E"

TECSLIB_DIR = $(SRCDIR)/tecs_lib
MRUBY_LIB_DIR = $(SRCDIR)/mruby_lib

PRE_TECSGEN_TARGET =
POST_TECSGEN_TARGET =

#
#  オブジェクトファイル名の定義
#
OBJNAME = hrp2
ifdef OBJEXT
  OBJFILE = $(OBJNAME).$(OBJEXT)
  CFG1_OUT = cfg1_out.$(OBJEXT)
  CFG2_OUT = cfg2_out.$(OBJEXT)
  CFG3_OUT = cfg3_out.$(OBJEXT)
else
  OBJFILE = $(OBJNAME)
  CFG1_OUT = cfg1_out
  CFG2_OUT = cfg2_out
  CFG3_OUT = cfg3_out
endif

#
#  ターゲット依存部のディレクトリの定義
#
TARGETDIR = $(SRCDIR)/target/$(TARGET)

#
#  TECSが生成する定義のインクルード
#
-include gen/Makefile.tecsgen

#
#  ターゲット依存の定義のインクルード
#
include $(TARGETDIR)/Makefile.ev3
include $(TARGETDIR)/api/Makefile

# =begin added by ishikawa for tmp
USE_SYSLOG = true
# =end added by ishikawa for tmp

#
#  Syslog関係の定義
#
ifdef USE_SYSLOG
  APPL_COBJS := $(APPL_COBJS) vasyslog.o
else
  COPTS := $(COPTS) -D TOPPERS_OMIT_SYSLOG
endif

#
#  コンフィギュレータ関係の変数の定義
#
CFG_TABS := --api-table $(SRCDIR)/kernel/kernel_api.csv \
			--cfg1-def-table $(SRCDIR)/kernel/kernel_def.csv $(CFG_TABS)

CFG_COBJS := kernel_cfg.o kernel_mem.o $(CFG_COBJS)
CFG_ASMOBJS := $(CFG_ASMOBJS)
CFG_OBJS := $(CFG_ASMOBJS) $(CFG_COBJS)

CFG2_OUT_SRCS := kernel_cfg.h kernel_cfg.c kernel_mem2.c $(CFG2_OUT_SRCS)
CFG2_COBJS := kernel_cfg.o kernel_mem2.o $(CFG2_COBJS)
CFG2_ASMOBJS := $(CFG2_ASMOBJS)
CFG2_OBJS := $(CFG2_ASMOBJS) $(CFG2_COBJS)

CFG3_OUT_SRCS := kernel_cfg.h kernel_cfg.c kernel_mem3.c $(CFG3_OUT_SRCS)
CFG3_COBJS := kernel_cfg.o kernel_mem3.o $(CFG3_COBJS)
CFG3_ASMOBJS := $(CFG3_ASMOBJS)
CFG3_OBJS := $(CFG3_ASMOBJS) $(CFG3_COBJS)

#
#  共通コンパイルオプションの定義
#
COPTS := $(COPTS) -g
ifndef OMIT_WARNING_ALL
  COPTS := $(COPTS) -Wall
endif
ifndef OMIT_OPTIMIZATION
  COPTS := $(COPTS) -O2
endif
CDEFS := $(CDEFS)
INCLUDES := -I. -I./gen -I$(SRCDIR)/tecs_kernel -I$(SRCDIR)/tecs_plugin \
			-I$(SRCDIR)/include -I$(SRCDIR)/arch -I$(SRCDIR) -I$(SRCDIR)/target/ev3_gcc/api/src\
      		-I$(MRUBY_SRC_DIR)/include \
            -I$(SRCDIR)/tecs_lib/mindstorms_ev3 -I$(SRCDIR)/tecs_lib/common \
			-I$(SRCDIR)/tecsgen/tecsgen/tecs/mruby \
			-I$(SRCDIR)/tecsgen/tecsgen/tecs/TLSFMalloc \
            -I$(SRCDIR)/tecsgen/tecsgen/tecs/posix $(INCLUDES)

LDFLAGS := $(LDFLAGS) -L $(MRUBY_SRC_DIR)/build/ARM/lib/
CFG1_OUT_LDFLAGS := $(CFG1_OUT_LDFLAGS) -L $(MRUBY_SRC_DIR)/build/ARM/lib/
CFG2_OUT_LDFLAGS := $(CFG2_OUT_LDFLAGS) -L $(MRUBY_SRC_DIR)/build/ARM/lib/
CFG3_OUT_LDFLAGS := $(CFG3_OUT_LDFLAGS) -L $(MRUBY_SRC_DIR)/build/ARM/lib/
LIBS := $(LIBS) $(CXXLIBS)
CFLAGS = $(COPTS) $(CDEFS) $(INCLUDES)

#
#  アプリケーションプログラムに関する定義
#
APPLNAME = tEV3Sample
APPLDIR = ../tlsf+tecs
APPL_CFG = $(APPLNAME).cfg
APPL_CDL = $(APPLNAME).cdl

APPL_DIR = $(APPLDIR) $(SRCDIR)/library
APPL_ASMOBJS =
ifdef USE_CXX
  APPL_CXXOBJS +=
  APPL_COBJS += $(TECS_COBJS) tecs_init.o
else
  APPL_COBJS += $(TECS_COBJS) tecs_init.o
endif
APPL_COBJS += log_output.o t_perror.o strerror.o
APPL_CFLAGS =
APPL_LIBS +=
ifdef APPLDIR
  INCLUDES := $(INCLUDES) -I$(APPLDIR)/../common $(foreach dir,$(APPLDIR),-I$(dir))
endif


#
#  システムサービスに関する定義
#
SYSSVC_DIR := $(SYSSVC_DIR) $(SRCDIR)/syssvc $(SRCDIR)/library
SYSSVC_ASMOBJS := $(SYSSVC_ASMOBJS)
SYSSVC_COBJS := $(SYSSVC_COBJS) banner.o syslog.o serial.o logtask.o \
				 $(CXXRTS)
SYSSVC_CFLAGS := $(SYSSVC_CFLAGS) -DTOPPERS_SVC_CALL
SYSSVC_LIBS := $(SYSSVC_LIBS)
INCLUDES := $(INCLUDES)

#
#  カーネルに関する定義
#
#  KERNEL_ASMOBJS: カーネルライブラリに含める，ソースがアセンブリ言語の
#				   オブジェクトファイル．
#  KERNEL_COBJS: カーネルのライブラリに含める，ソースがC言語で，ソース
#				 ファイルと1対1に対応するオブジェクトファイル．
#  KERNEL_LCSRCS: カーネルのライブラリに含めるC言語のソースファイルで，
#				  1つのソースファイルから複数のオブジェクトファイルを生
#				  成するもの．
#  KERNEL_LCOBJS: 上のソースファイルから生成されるオブジェクトファイル．
#  KERNEL_AUX_COBJS: ロードモジュールに含めないが，カーネルのソースファ
#					 イルと同じオプションを適用してコンパイルすべき，ソー
#					 スがC言語のオブジェクトファイル．
#
KERNEL_DIR := $(KERNEL_DIR) $(SRCDIR)/kernel $(SRCDIR)/tecs_kernel
KERNEL_ASMOBJS := $(KERNEL_ASMOBJS)
KERNEL_COBJS := $(KERNEL_COBJS) svc_table.o
KERNEL_CFLAGS := $(KERNEL_CFLAGS) -I$(SRCDIR)/kernel
ifdef OMIT_MAKEOFFSET
  OFFSET_H =
else
  OFFSET_H = offset.h
ifndef OFFSET_TF
  KERNEL_AUX_COBJS := $(KERNEL_AUX_COBJS) makeoffset.o
endif
endif

#
#  ターゲットファイル（複数を同時に選択してはならない）
#
#all: $(OBJFILE)
all: $(OBJNAME).bin uImage
#all: $(OBJNAME).srec

##### 以下は編集しないこと #####

#
#  環境に依存するコンパイルオプションの定義
#
ifdef DBGENV
  CDEFS := $(CDEFS) -D$(DBGENV)
endif

#
#  カーネルのファイル構成の定義
#
include $(SRCDIR)/kernel/Makefile.kernel
ifdef KERNEL_FUNCOBJS
  KERNEL_LCSRCS := $(KERNEL_FCSRCS)
  KERNEL_LCOBJS := $(foreach file,$(KERNEL_FCSRCS),$($(file:.c=)))
else
  KERNEL_CFLAGS := -DALLFUNC $(KERNEL_CFLAGS)
  KERNEL_COBJS := $(KERNEL_COBJS) \
					$(foreach file,$(KERNEL_FCSRCS),$(file:.c=.o))
endif

#
#  ソースファイルのあるディレクトリに関する定義
#
INCLUDES += $(foreach dir,$(shell find $(APPLDIR) -type d -name include),-I$(dir))
APPL_DIR += $(foreach dir,$(shell find $(APPLDIR) -type d -name src),$(dir))
vpath %.c ./gen $(KERNEL_DIR) $(SYSSVC_DIR) $(APPL_DIR) $(SRCDIR)/tecs_lib/mindstorms_ev3 $(SRCDIR)/tecs_lib/common $(SRCDIR)/tecsgen/tecsgen/tecs/mruby
vpath %.cpp /gen $(KERNEL_DIR) $(SYSSVC_DIR) $(APPL_DIR)
vpath %.S ./gen $(KERNEL_DIR) $(SYSSVC_DIR) $(APPL_DIR)
vpath %.cfg ./gen $(APPL_DIR)

#
#  コンパイルのための変数の定義
#
KERNEL_LIB_OBJS = $(KERNEL_ASMOBJS) $(KERNEL_COBJS) $(KERNEL_LCOBJS)
SYSSVC_OBJS = $(SYSSVC_ASMOBJS) $(SYSSVC_COBJS)
APPL_OBJS = $(APPL_ASMOBJS) $(APPL_COBJS) $(APPL_CXXOBJS) $(MRUBY_COBJS)
ALL2_OBJS = $(START_OBJS) $(APPL_OBJS) $(SYSSVC_OBJS) $(CFG2_OBJS) \
											$(END_OBJS) $(HIDDEN_OBJS)
ALL3_OBJS = $(START_OBJS) $(APPL_OBJS) $(SYSSVC_OBJS) $(CFG3_OBJS) \
											$(END_OBJS) $(HIDDEN_OBJS)
ALL_OBJS = $(START_OBJS) $(APPL_OBJS) $(SYSSVC_OBJS) $(CFG_OBJS) \
											$(END_OBJS) $(HIDDEN_OBJS)
ifdef KERNEL_LIB
  ALL_LIBS = $(APPL_LIBS) $(SYSSVC_LIBS) -lkernel $(LIBS)
  LIBS_DEP = $(filter %.a,$(ALL_LIBS)) $(KERNEL_LIB)/libkernel.a
  LDFLAGS := $(LDFLAGS) -L$(KERNEL_LIB) -L $(MRUBY_SRC_DIR)/build/ARM/lib/
  CFG2_OUT_LDFLAGS := $(CFG2_OUT_LDFLAGS) -L$(KERNEL_LIB)
  CFG3_OUT_LDFLAGS := $(CFG3_OUT_LDFLAGS) -L$(KERNEL_LIB)
  REALCLEAN_FILES := libkernel.a $(REALCLEAN_FILES)
else
  ALL_LIBS = $(APPL_LIBS) $(SYSSVC_LIBS) libkernel.a $(LIBS)
  LIBS_DEP = $(filter %.a,$(ALL_LIBS))
endif

ifdef TEXT_START_ADDRESS
  LDFLAGS := $(LDFLAGS) -Wl,-Ttext,$(TEXT_START_ADDRESS)
  CFG1_OUT_LDFLAGS := $(CFG1_OUT_LDFLAGS) -Wl,-Ttext,$(TEXT_START_ADDRESS)
  CFG2_OUT_LDFLAGS := $(CFG2_OUT_LDFLAGS) -Wl,-Ttext,$(TEXT_START_ADDRESS)
  CFG3_OUT_LDFLAGS := $(CFG3_OUT_LDFLAGS) -Wl,-Ttext,$(TEXT_START_ADDRESS)
endif
ifdef DATA_START_ADDRESS
  LDFLAGS := $(LDFLAGS) -Wl,-Tdata,$(DATA_START_ADDRESS)
  CFG1_OUT_LDFLAGS := $(CFG1_OUT_LDFLAGS) -Wl,-Tdata,$(DATA_START_ADDRESS)
  CFG2_OUT_LDFLAGS := $(CFG2_OUT_LDFLAGS) -Wl,-Tdata,$(DATA_START_ADDRESS)
  CFG3_OUT_LDFLAGS := $(CFG3_OUT_LDFLAGS) -Wl,-Tdata,$(DATA_START_ADDRESS)
endif
ifdef LDSCRIPT
  LDFLAGS := $(LDFLAGS) -T $(LDSCRIPT)
endif
ifdef CFG1_OUT_LDSCRIPT
  CFG1_OUT_LDFLAGS := $(CFG1_OUT_LDFLAGS) -T $(CFG1_OUT_LDSCRIPT)
endif
ifdef CFG2_OUT_LDSCRIPT
  CFG2_OUT_LDFLAGS := $(CFG2_OUT_LDFLAGS) -T $(CFG2_OUT_LDSCRIPT)
endif
ifdef CFG3_OUT_LDSCRIPT
  CFG3_OUT_LDFLAGS := $(CFG3_OUT_LDFLAGS) -T $(CFG3_OUT_LDSCRIPT)
endif

#
#  オフセットファイル（offset.h）の生成規則
#
ifdef OFFSET_TF
offset.h: $(APPL_CFG) kernel_cfg.timestamp
	$(call print_cmd, "CFG[3]", $@)
	@$(CFG) --pass 3 --kernel hrp2 $(INCLUDES) \
				--rom-image cfg1_out.srec --symbol-table cfg1_out.syms \
				-T $(OFFSET_TF) $(CFG_TABS) $<
else
offset.h: makeoffset.s $(SRCDIR)/utils/genoffset
	$(PERL) $(SRCDIR)/utils/genoffset makeoffset.s > offset.h
endif

#
#  omit_svc.hの生成規則（ファイルがなければ空のファイルを生成する）
#
omit_svc.h:
	touch omit_svc.h

#
#  カーネルのコンフィギュレーションファイルの生成
#
cfg1_out.c: $(APPL_CFG)
	$(call print_cmd, "CFG[1]", $@)
	@$(CFG) --pass 1 --kernel hrp2 $(INCLUDES) $(CFG_TABS) $<

$(CFG2_OUT_SRCS): kernel_cfg.timestamp
kernel_cfg.timestamp: $(APPL_CFG) \
						$(START_OBJS) cfg1_out.o $(END_OBJS) $(HIDDEN_OBJS)
	$(call print_cmd, "LINK", $(CFG1_OUT))
	@$(LINK) $(CFLAGS) $(CFG1_OUT_LDFLAGS) -o $(CFG1_OUT) \
						$(START_OBJS) cfg1_out.o $(END_OBJS)
	$(call print_cmd, "NM", cfg1_out.syms)
	@$(NM) -n $(CFG1_OUT) > cfg1_out.syms
	$(call print_cmd, "OBJCOPY", cfg1_out.srec)
	@$(OBJCOPY) -O srec -S $(CFG1_OUT) cfg1_out.srec
	$(call print_cmd, "CFG[2]", $@)
	@$(CFG) --pass 2 --kernel hrp2 $(INCLUDES) \
				-T $(TARGETDIR)/target.tf $(CFG_TABS) $<
	touch -r kernel_cfg.c kernel_cfg.timestamp

#
#	パス3を使用する場合
#
ifdef USE_CFG_PASS3
kernel_mem3.c: $(APPL_CFG) kernel_cfg.timestamp $(ALL2_OBJS) $(LIBS_DEP)
	$(LINK) $(CFLAGS) $(CFG2_OUT_LDFLAGS)  -o $(CFG2_OUT) $(START_OBJS)  \
			$(APPL_OBJS) $(MRUBY_LIB) $(SYSSVC_OBJS) $(CFG2_OBJS) $(ALL_LIBS)  $(END_OBJS)
	$(NM) -n $(CFG2_OUT) > cfg2_out.syms
	$(OBJCOPY) -O srec -S $(CFG2_OUT) cfg2_out.srec
	rm -f $(CFG3_OUT_LDSCRIPT)
	$(CFG) --pass 3 --kernel hrp2 $(INCLUDES) \
				--rom-image cfg2_out.srec --symbol-table cfg2_out.syms \
				-T $(TARGETDIR)/target_opt.tf $(CFG_TABS) $<
	if ! [ -f $(CFG3_OUT_LDSCRIPT) ]; then \
		sed "s/kernel_mem2\.o/kernel_mem3\.o/g" < $(CFG2_OUT_LDSCRIPT) \
													> $(CFG3_OUT_LDSCRIPT); \
	fi

kernel_mem.c: $(APPL_CFG) kernel_cfg.timestamp $(ALL3_OBJS) $(LIBS_DEP)
	$(LINK) $(CFLAGS) $(CFG3_OUT_LDFLAGS) -o $(CFG3_OUT) $(START_OBJS) \
			$(APPL_OBJS) $(MRUBY_LIB) $(SYSSVC_OBJS) $(CFG3_OBJS) $(ALL_LIBS) -lm $(END_OBJS)
	$(NM) -n $(CFG3_OUT) > cfg3_out.syms
	$(OBJCOPY) -O srec -S $(CFG3_OUT) cfg3_out.srec
	rm -f $(LDSCRIPT)
	$(CFG) --pass 4 --kernel hrp2 $(INCLUDES) \
				--rom-image cfg3_out.srec --symbol-table cfg3_out.syms \
				-T $(TARGETDIR)/target_mem.tf $(CFG_TABS) $<
	if ! [ -f $(LDSCRIPT) ]; then \
		sed "s/kernel_mem3\.o/kernel_mem\.o/g" < $(CFG3_OUT_LDSCRIPT) \
															> $(LDSCRIPT); \
	fi
endif

#
#	パス3を使用しない場合
#
ifndef USE_CFG_PASS3
kernel_mem.c: $(APPL_CFG) kernel_cfg.timestamp $(ALL2_OBJS) $(LIBS_DEP)
	$(LINK) $(CFLAGS) $(CFG2_OUT_LDFLAGS) -o $(CFG2_OUT) $(START_OBJS) \
			$(APPL_OBJS) $(SYSSVC_OBJS) $(CFG2_OBJS) $(ALL_LIBS) $(END_OBJS)
	$(NM) -n $(CFG2_OUT) > cfg2_out.syms
	$(OBJCOPY) -O srec -S $(CFG2_OUT) cfg2_out.srec
	rm -f $(LDSCRIPT)
	touch cfg3_out.tf
	$(CFG) --pass 4 --kernel hrp2 $(INCLUDES) \
				--rom-image cfg2_out.srec --symbol-table cfg2_out.syms \
				-T $(TARGETDIR)/target_mem.tf $(CFG_TABS) $<
	if ! [ -f $(LDSCRIPT) ]; then \
		sed "s/kernel_mem2\.o/kernel_mem\.o/g" < $(CFG2_OUT_LDSCRIPT) \
															> $(LDSCRIPT); \
	fi
endif

#
#  カーネルライブラリファイルの生成
#
libkernel.a: $(OFFSET_H) $(KERNEL_LIB_OBJS)
	rm -f libkernel.a
	$(AR) -rcs libkernel.a $(KERNEL_LIB_OBJS)
	$(RANLIB) libkernel.a

#
#  特別な依存関係の定義
#
svc_table.o: omit_svc.h
svc_table.d: omit_svc.h
banner.o: kernel_cfg.timestamp $(filter-out banner.o,$(ALL2_OBJS)) $(LIBS_DEP)

#
#  全体のリンク
#
$(OBJFILE): $(APPL_CFG) kernel_cfg.timestamp $(ALL_OBJS) $(LIBS_DEP)
	$(LINK) $(CFLAGS) $(LDFLAGS) -o $(OBJFILE) $(START_OBJS) \
			$(APPL_OBJS) $(MRUBY_LIB) $(SYSSVC_OBJS) $(CFG_OBJS) $(ALL_LIBS) $(END_OBJS)
	$(NM) -n $(OBJFILE) > $(OBJNAME).syms
ifdef USE_CFG_PASS3
	# TODO: remove to ignore wornings
	# diff cfg3_out.syms $(OBJNAME).syms
else
	# diff cfg2_out.syms $(OBJNAME).syms
endif
#
#  バイナリファイルの生成
#
$(OBJNAME).bin: $(OBJFILE)
	$(OBJCOPY) -O binary -S $(OBJFILE) $(OBJNAME).bin

.PHONY: uImage
uImage:$(OBJNAME).bin
	$(MKIMAGE) -A arm -O linux -T kernel -C none -a 0xc0008000 -e 0xc0008000 -n "hrp2 kernel" -d hrp2.bin uImage
	chmod +x uImage
	cp uImage $(SD_DIR)
#
#  Sレコードファイルの生成
#
$(OBJNAME).srec: $(OBJFILE)
	$(OBJCOPY) -O srec -S $(OBJFILE) $(OBJNAME).srec

#
#  コンパイル結果の消去
#
.PHONY: clean
clean:
	rm -f \#* *~ *.o $(CLEAN_FILES)
	rm -f $(OBJFILE) $(OBJNAME).syms $(OBJNAME).srec $(OBJNAME).bin
	rm -f kernel_mem.c $(CFG2_OUT) cfg2_out.tf cfg2_out.syms cfg2_out.srec
	rm -f $(CFG3_OUT) cfg3_out.tf cfg3_out.syms cfg3_out.srec
	rm -f kernel_cfg.timestamp $(CFG2_OUT_SRCS) $(CFG3_OUT_SRCS)
	rm -f cfg1_out.c $(CFG1_OUT) cfg1_out.syms cfg1_out.srec
	rm -f ev3api_cfg.c ev3api_cfg.h omit_svc.h
ifndef KERNEL_LIB
	rm -f libkernel.a
endif
	rm -f makeoffset.s offset.h
	rm -f $(MLIB) $(CLIB) $(RLIB) $(DLIB) $(DEPLIB)
.PHONY: cleankernel
cleankernel:
	rm -rf $(KERNEL_LIB_OBJS)
	rm -f makeoffset.s offset.h

.PHONY: cleandep
cleandep:
	if ! [ -f Makefile.depend ]; then \
		rm -f kernel_cfg.timestamp $(CFG2_OUT_SRCS); \
		rm -f cfg1_out.c cfg1_out.o $(CFG1_OUT) cfg1_out.syms cfg1_out.srec; \
		rm -f makeoffset.s offset.h; \
	fi
	rm -f Makefile.depend

.PHONY: cleantecs
cleantecs:
	rm -rf gen
	rm -f tecs.timestamp
.PHONY: clean_mrb_c
.PHONY: realclean
realclean: cleantecs cleandep clean clean_mrb_c
	rm -f $(REALCLEAN_FILES)

#
#  TECSインタフェースジェネレータの実行
#
tecs.timestamp: $(APPL_CDL) $(TECS_IMPORTS)
	$(call print_cmd, "TECSGEN", $<)
	$(TECSGEN) -R -D TECSGEN -D TECS_CPP \
					-I$(SRCDIR)/tecs_plugin $(INCLUDES) $(APPL_CDL)
	touch tecs.timestamp

.PHONY: tecs
tecs: tecs.timestamp

#
#  コンフィギュレータが生成したファイルのコンパイルルールと依存関係作成
#  ルールの定義
#
#  コンフィギュレータが生成したファイルは，アプリケーションプログラム用，
#  システムサービス用，カーネル用のすべてのオプションを付けてコンパイル
#  する．
#
ALL_CFG_COBJS = $(sort $(CFG_COBJS) $(CFG2_COBJS) $(CFG3_COBJS) cfg1_out.o)
ALL_CFG_ASMOBJS = $(sort $(CFG_ASMOBJS) $(CFG2_ASMOBJS) $(CFG3_ASMOBJS))
CFG_CFLAGS = $(APPL_CFLAGS) $(SYSSVC_CFLAGS) $(KERNEL_CFLAGS)

$(ALL_CFG_COBJS): %.o: %.c
	$(call print_cmd, "CC", $<)
	@$(CC) -c $(CFLAGS) $(CFG_CFLAGS) $<

$(ALL_CFG_COBJS:.o=.s): %.s: %.c
	$(CC) -S $(CFLAGS) $(CFG_CFLAGS) $<

$(ALL_CFG_COBJS:.o=.d): %.d: %.c
	@$(PERL) $(SRCDIR)/utils/makedep -C $(CC) $(MAKEDEP_OPTS) \
		-O "$(CFLAGS) $(CFG_CFLAGS)" $< >> Makefile.depend

$(ALL_CFG_ASMOBJS): %.o: %.S
	$(CC) -c $(CFLAGS) $(CFG_CFLAGS) $<

$(ALL_CFG_ASMOBJS:.o=.d): %.d: %.S
	@$(PERL) $(SRCDIR)/utils/makedep -C $(CC) $(MAKEDEP_OPTS) \
		-O "$(CFLAGS) $(CFG_CFLAGS)" $< >> Makefile.depend

#
#  特殊な依存関係作成ルールの定義
#
cfg1_out.depend: $(APPL_CFG)
	@$(CFG) -M cfg1_out.c $(INCLUDES) $< >> Makefile.depend

makeoffset.d: makeoffset.c
	@$(PERL) $(SRCDIR)/utils/makedep -C $(CC) $(MAKEDEP_OPTS) \
		-T "makeoffset.s" -O "$(CFLAGS) $(KERNEL_CFLAGS)" $< >> Makefile.depend

#
#  依存関係ファイルの生成
#
.PHONY: gendepend
gendepend:
	@echo "Generating Makefile.depend."

.PHONY: depend
ifdef KERNEL_LIB
depend: cleandep kernel_cfg.timestamp gendepend \
		cfg1_out.depend cfg1_out.d \
		$(ALL2_OBJS:.o=.d)
else
depend: cleandep $(OFFSET_H) kernel_cfg.timestamp gendepend \
		cfg1_out.depend cfg1_out.d \
		$(KERNEL_AUX_COBJS:.o=.d) $(KERNEL_ASMOBJS:.o=.d) \
		$(KERNEL_COBJS:.o=.d) $(KERNEL_LCSRCS:.c=.d) $(ALL2_OBJS:.o=.d)
endif

#
#  依存関係ファイルをインクルード
#
-include Makefile.depend

#
#  開発ツールのコマンド名の定義
#
ifeq ($(TOOL),gcc)
  #
  #  GNU開発環境用
  #
  ifdef GCC_TARGET
    GCC_TARGET_PREFIX = $(GCC_TARGET)-
  else
    GCC_TARGET_PREFIX =
  endif
  CC = $(GCC_TARGET_PREFIX)gcc -std=gnu99
  #CXX = $(GCC_TARGET_PREFIX)g++ -std=gnu++11 -fno-exceptions
  CXX = $(GCC_TARGET_PREFIX)g++ -std=gnu++11
  AS = $(GCC_TARGET_PREFIX)as
  LD = $(GCC_TARGET_PREFIX)ld
  AR = $(GCC_TARGET_PREFIX)ar
  NM = $(GCC_TARGET_PREFIX)nm
  RANLIB = $(GCC_TARGET_PREFIX)ranlib
  OBJCOPY = $(GCC_TARGET_PREFIX)objcopy
  OBJDUMP = $(GCC_TARGET_PREFIX)objdump
endif

ifdef USE_CXX
  LINK = $(CXX)
else
  LINK = $(CC)
endif

#
#  コンパイルルールの定義
#
KERNEL_ALL_COBJS = $(KERNEL_COBJS) $(KERNEL_AUX_COBJS)

$(KERNEL_ALL_COBJS): %.o: %.c
	$(call print_cmd, "CC[K]", $<)
	@$(CC) -c $(CFLAGS) $(KERNEL_CFLAGS) $<

$(KERNEL_ALL_COBJS:.o=.s): %.s: %.c
	$(call print_cmd, "CC[K]", $<)
	@$(CC) -S $(CFLAGS) $(KERNEL_CFLAGS) $<

$(KERNEL_LCOBJS): %.o:
	$(CC) -DTOPPERS_$(*F) -o $@ -c $(CFLAGS) $(KERNEL_CFLAGS) $<

$(KERNEL_LCOBJS:.o=.s): %.s:
	$(CC) -DTOPPERS_$(*F) -o $@ -S $(CFLAGS) $(KERNEL_CFLAGS) $<

$(KERNEL_ASMOBJS): %.o: %.S
	$(call print_cmd, "CC[K]", $<)
	@$(CC) -c $(CFLAGS) $(KERNEL_CFLAGS) $<

$(SYSSVC_COBJS): %.o: %.c
	$(call print_cmd, "CC[SYSSVC]", $<)
	@$(CC) -c $(CFLAGS) $(SYSSVC_CFLAGS) $<

$(SYSSVC_COBJS:.o=.s): %.s: %.c
	$(call print_cmd, "CC[SYSSVC]", $<)
	@$(CC) -S $(CFLAGS) $(SYSSVC_CFLAGS) $<

$(SYSSVC_ASMOBJS): %.o: %.S
	$(CC) -c $(CFLAGS) $(SYSSVC_CFLAGS) $<

$(APPL_COBJS): %.o: %.c
	$(call print_cmd, "CC", $<)
	@$(CC) -c $(CFLAGS) $(APPL_CFLAGS) $<

$(APPL_COBJS:.o=.s): %.s: %.c
	$(CC) -S $(CFLAGS) $(APPL_CFLAGS) $<

$(APPL_CXXOBJS): %.o: %.cpp
	$(CXX) -c $(CFLAGS) $(APPL_CFLAGS) $<

$(APPL_CXXOBJS:.o=.s): %.s: %.cpp
	$(CXX) -S $(CFLAGS) $(APPL_CFLAGS) $<

$(APPL_ASMOBJS): %.o: %.S
	$(CC) -c $(CFLAGS) $(APPL_CFLAGS) $<

#
#  依存関係作成ルールの定義
#
$(KERNEL_COBJS:.o=.d): %.d: %.c
	@$(PERL) $(SRCDIR)/utils/makedep -C $(CC) $(MAKEDEP_OPTS) \
		-O "$(CFLAGS) $(KERNEL_CFLAGS)" $< >> Makefile.depend

$(KERNEL_LCSRCS:.c=.d): %.d: %.c
	@$(PERL) $(SRCDIR)/utils/makedep -C $(CC) $(MAKEDEP_OPTS) -T "$($*)" \
		-O "-DALLFUNC $(CFLAGS) $(KERNEL_CFLAGS)" $< >> Makefile.depend

$(KERNEL_ASMOBJS:.o=.d): %.d: %.S
	@$(PERL) $(SRCDIR)/utils/makedep -C $(CC) $(MAKEDEP_OPTS) \
		-O "$(CFLAGS) $(KERNEL_CFLAGS)" $< >> Makefile.depend

$(SYSSVC_COBJS:.o=.d): %.d: %.c
	@$(PERL) $(SRCDIR)/utils/makedep -C $(CC) $(MAKEDEP_OPTS) \
		-O "$(CFLAGS) $(SYSSVC_CFLAGS)" $< >> Makefile.depend

$(SYSSVC_ASMOBJS:.o=.d): %.d: %.S
	@$(PERL) $(SRCDIR)/utils/makedep -C $(CC) $(MAKEDEP_OPTS) \
		-O "$(CFLAGS) $(SYSSVC_CFLAGS)" $< >> Makefile.depend

$(APPL_COBJS:.o=.d): %.d: %.c
	@$(PERL) $(SRCDIR)/utils/makedep -C $(CC) $(MAKEDEP_OPTS) \
		-O "$(CFLAGS) $(APPL_CFLAGS)" $< >> Makefile.depend

$(APPL_CXXOBJS:.o=.d): %.d: %.cpp
	@$(PERL) $(SRCDIR)/utils/makedep -C $(CXX) $(MAKEDEP_OPTS) \
		-O "$(CFLAGS) $(APPL_CFLAGS)" $< >> Makefile.depend

$(APPL_ASMOBJS:.o=.d): %.d: %.S
	@$(PERL) $(SRCDIR)/utils/makedep -C $(CC) $(MAKEDEP_OPTS) \
		-O "$(CFLAGS) $(APPL_CFLAGS)" $< >> Makefile.depend

#
#  デフォルトコンパイルルールを上書き
#
%.o: %.c
	@echo "*** Default compile rules should not be used."
	$(CC) -c $(CFLAGS) $<

%.s: %.c
	@echo "*** Default compile rules should not be used."
	$(CC) -S $(CFLAGS) $<

%.o: %.cpp
	@echo "*** Default compile rules should not be used."
	$(CXX) -c $(CFLAGS) $<

%.s: %.cpp
	@echo "*** Default compile rules should not be used."
	$(CXX) -S $(CFLAGS) $<

%.o: %.S
	@echo "*** Default compile rules should not be used."
	$(CC) -c $(CFLAGS) $<
