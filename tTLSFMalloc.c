/*
 * このファイルは tecsgen によりテンプレートとして自動生成されました
 * このファイルを編集して使用することが意図されていますが
 * tecsgen の再実行により上書きされてしまうため、通常
 *   gen/tTLSFMalloc_template.c => src/tTLSFMalloc.c
 * のように名前, フォルダを変更してから修正します
 */
/* #[<PREAMBLE>]#
 * #[<...>]# から #[</...>]# で囲まれたコメントは編集しないでください
 * tecsmerge によるマージに使用されます
 *
 * 属性アクセスマクロ #_CAAM_#
 * memoryPoolSize   size_t           ATTR_memoryPoolSize
 * pool             uint64_t*        VAR_pool        
 * mallocSize       size_t           VAR_mallocSize  
 * freeSize         size_t           VAR_freeSize    
 * reallocSize      size_t           VAR_reallocSize 
 *
 * #[</PREAMBLE>]# */

/* プロトタイプ宣言や変数の定義をここに書きます #_PAC_# */
#include "tTLSFMalloc_tecsgen.h"

#ifndef E_OK
#define	E_OK	0		/* success */
#define	E_ID	(-18)	/* illegal ID */
#endif

#ifndef USE_PRINTF
#define USE_PRINTF      (1)
#endif

#include <string.h>

#ifndef TLSF_USE_LOCKS
#define	TLSF_USE_LOCKS 	(0)
#endif

#ifndef TLSF_STATISTIC
#define	TLSF_STATISTIC 	(0)
#endif

#ifndef USE_MMAP
#define	USE_MMAP 	(0)
#endif

#ifndef USE_SBRK
#define	USE_SBRK 	(0)
#endif


#if TLSF_USE_LOCKS
#include "kernel.h"
#include "kernel_cfg.h"
#define TLSF_MLOCK_T ID
#define TLSF_CREATE_LOCK(lock) (*lock = TLSF_SEM)
#define TLSF_DESTROY_LOCK(lock) ini_sem(*lock)
#define TLSF_ACQUIRE_LOCK(lock) wai_sem(*lock)
#define TLSF_RELEASE_LOCK(lock) sig_sem(*lock)
#else
#define TLSF_CREATE_LOCK(_unused_)   do{}while(0)
#define TLSF_DESTROY_LOCK(_unused_)  do{}while(0) 
#define TLSF_ACQUIRE_LOCK(_unused_)  do{}while(0)
#define TLSF_RELEASE_LOCK(_unused_)  do{}while(0)
#endif

#if TLSF_STATISTIC
#define	TLSF_ADD_SIZE(tlsf, b) do {									\
		tlsf->used_size += (b->size & BLOCK_SIZE) + BHDR_OVERHEAD;	\
		if (tlsf->used_size > tlsf->max_size) 						\
			tlsf->max_size = tlsf->used_size;						\
		} while(0)

#define	TLSF_REMOVE_SIZE(tlsf, b) do {								\
		tlsf->used_size -= (b->size & BLOCK_SIZE) + BHDR_OVERHEAD;	\
	} while(0)
#else
#define	TLSF_ADD_SIZE(tlsf, b)	     do{}while(0)
#define	TLSF_REMOVE_SIZE(tlsf, b)    do{}while(0)
#endif

#if USE_MMAP || USE_SBRK
#include <unistd.h>
#endif

#if USE_MMAP
#include <sys/mman.h>
#endif

#include "tlsf.h"

#if !defined(__GNUC__)
#ifndef __inline__
#define __inline__
#endif
#endif

/* The  debug functions  only can  be used  when _DEBUG_TLSF_  is set. */
#ifndef _DEBUG_TLSF_
#define _DEBUG_TLSF_  (0)
#endif

/*************************************************************************/
/* Definition of the structures used by TLSF */


/* Some IMPORTANT TLSF parameters */
/* Unlike the preview TLSF versions, now they are statics */
#define BLOCK_ALIGN (sizeof(void *) * 2)

#define MAX_FLI		(30)
#define MAX_LOG2_SLI	(5)
#define MAX_SLI		(1 << MAX_LOG2_SLI)     /* MAX_SLI = 2^MAX_LOG2_SLI */

#define FLI_OFFSET	(6)     /* tlsf structure just will manage blocks bigger */
/* than 128 bytes */
#define SMALL_BLOCK	(128)
#define REAL_FLI	(MAX_FLI - FLI_OFFSET)
#define MIN_BLOCK_SIZE	(sizeof (free_ptr_t))
#define BHDR_OVERHEAD	(sizeof (bhdr_t) - MIN_BLOCK_SIZE)
#define TLSF_SIGNATURE	(0x2A59FA59)

#define	PTR_MASK	(sizeof(void *) - 1)
#define BLOCK_SIZE	(0xFFFFFFFF - PTR_MASK)

#define GET_NEXT_BLOCK(_addr, _r) ((bhdr_t *) ((char *) (_addr) + (_r)))
#define	MEM_ALIGN		  ((BLOCK_ALIGN) - 1)
#define ROUNDUP_SIZE(_r)          (((_r) + MEM_ALIGN) & ~MEM_ALIGN)
#define ROUNDDOWN_SIZE(_r)        ((_r) & ~MEM_ALIGN)
#define ROUNDUP(_x, _v)           ((((~(_x)) + 1) & ((_v)-1)) + (_x))

#define BLOCK_STATE	(0x1)
#define PREV_STATE	(0x2)

/* bit 0 of the block size */
#define FREE_BLOCK	(0x1)
#define USED_BLOCK	(0x0)

/* bit 1 of the block size */
#define PREV_FREE	(0x2)
#define PREV_USED	(0x0)


#define DEFAULT_AREA_SIZE (1024*10)

#ifdef USE_MMAP
#define PAGE_SIZE (getpagesize())
#endif

#ifdef USE_PRINTF
#include <stdio.h>
#include <t_stddef.h>
#include <t_syslog.h>
#define PRINT_MSG(fmt, args...) syslog(LOG_ERROR, fmt, ## args)
#define ERROR_MSG(fmt, args...) syslog(LOG_ERROR, fmt, ## args)
#else
# if !defined(PRINT_MSG)
#  define PRINT_MSG(fmt, args...)
# endif
# if !defined(ERROR_MSG)
#  define ERROR_MSG(fmt, args...)
# endif
#endif

typedef unsigned int u32_t;     /* NOTE: Make sure that this type is 4 bytes long on your computer */
typedef unsigned char u8_t;     /* NOTE: Make sure that this type is 1 byte on your computer */

typedef struct free_ptr_struct {
    struct bhdr_struct *prev;
    struct bhdr_struct *next;
} free_ptr_t;

typedef struct bhdr_struct {
    /* This pointer is just valid if the first bit of size is set */
    struct bhdr_struct *prev_hdr;
    /* The size is stored in bytes */
    size_t size;                /* bit 0 indicates whether the block is used and */
    /* bit 1 allows to know whether the previous block is free */
    union {
        struct free_ptr_struct free_ptr;
        u8_t buffer[1];         /*sizeof(struct free_ptr_struct)]; */
    } ptr;
} bhdr_t;

/* This structure is embedded at the beginning of each area, giving us
 * enough information to cope with a set of areas */

typedef struct area_info_struct {
    bhdr_t *end;
    struct area_info_struct *next;
} area_info_t;

typedef struct TLSF_struct {
    /* the TLSF's structure signature */
    u32_t tlsf_signature;

#if TLSF_USE_LOCKS
    TLSF_MLOCK_T lock;
#endif

#if TLSF_STATISTIC
    /* These can not be calculated outside tlsf because we
     * do not know the sizes when freeing/reallocing memory. */
    size_t used_size;
    size_t max_size;
#endif

    /* A linked list holding all the existing areas */
    area_info_t *area_head;

    /* the first-level bitmap */
    /* This array should have a size of REAL_FLI bits */
    u32_t fl_bitmap;

    /* the second-level bitmap */
    u32_t sl_bitmap[REAL_FLI];

    bhdr_t *matrix[REAL_FLI][MAX_SLI];
} tlsf_t;


/******************************************************************/
/**************     Helping functions    **************************/
/******************************************************************/
static __inline__ void set_bit(int nr, u32_t * addr);
static __inline__ void clear_bit(int nr, u32_t * addr);
static __inline__ int ls_bit(int x);
static __inline__ int ms_bit(int x);
static __inline__ void MAPPING_SEARCH(size_t * _r, int *_fl, int *_sl);
static __inline__ void MAPPING_INSERT(size_t _r, int *_fl, int *_sl);
static __inline__ bhdr_t *FIND_SUITABLE_BLOCK(tlsf_t * _tlsf, int *_fl, int *_sl);
static __inline__ bhdr_t *process_area(void *area, size_t size);
#if USE_SBRK || USE_MMAP
static __inline__ void *get_new_area(size_t * size);
#endif

static const int table[] = {
    -1, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4,
    4, 4,
    4, 4, 4, 4, 4, 4, 4,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5,
    5, 5, 5, 5, 5, 5, 5,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6,
    6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6,
    6, 6, 6, 6, 6, 6, 6,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7,
    7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7,
    7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7,
    7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7,
    7, 7, 7, 7, 7, 7, 7
};

static __inline__ int ls_bit(int i)
{
    unsigned int a;
    unsigned int x = i & -i;

    a = x <= 0xffff ? (x <= 0xff ? 0 : 8) : (x <= 0xffffff ? 16 : 24);
    return table[x >> a] + a;
}

static __inline__ int ms_bit(int i)
{
    unsigned int a;
    unsigned int x = (unsigned int) i;

    a = x <= 0xffff ? (x <= 0xff ? 0 : 8) : (x <= 0xffffff ? 16 : 24);
    return table[x >> a] + a;
}

static __inline__ void set_bit(int nr, u32_t * addr)
{
    addr[nr >> 5] |= 1 << (nr & 0x1f);
}

static __inline__ void clear_bit(int nr, u32_t * addr)
{
    addr[nr >> 5] &= ~(1 << (nr & 0x1f));
}

static __inline__ void MAPPING_SEARCH(size_t * _r, int *_fl, int *_sl)
{
    int _t;

    if (*_r < SMALL_BLOCK) {
        *_fl = 0;
        *_sl = *_r / (SMALL_BLOCK / MAX_SLI);
    } else {
        _t = (1 << (ms_bit(*_r) - MAX_LOG2_SLI)) - 1;
        *_r = *_r + _t;
        *_fl = ms_bit(*_r);
        *_sl = (*_r >> (*_fl - MAX_LOG2_SLI)) - MAX_SLI;
        *_fl -= FLI_OFFSET;
        /*if ((*_fl -= FLI_OFFSET) < 0) // FL wil be always >0!
         *_fl = *_sl = 0;
         */
        *_r &= ~_t;
    }
}

static __inline__ void MAPPING_INSERT(size_t _r, int *_fl, int *_sl)
{
    if (_r < SMALL_BLOCK) {
        *_fl = 0;
        *_sl = _r / (SMALL_BLOCK / MAX_SLI);
    } else {
        *_fl = ms_bit(_r);
        *_sl = (_r >> (*_fl - MAX_LOG2_SLI)) - MAX_SLI;
        *_fl -= FLI_OFFSET;
    }
}


static __inline__ bhdr_t *FIND_SUITABLE_BLOCK(tlsf_t * _tlsf, int *_fl, int *_sl)
{
    u32_t _tmp = _tlsf->sl_bitmap[*_fl] & (~0 << *_sl);
    bhdr_t *_b = NULL;

    if (_tmp) {
        *_sl = ls_bit(_tmp);
        _b = _tlsf->matrix[*_fl][*_sl];
    } else {
        *_fl = ls_bit(_tlsf->fl_bitmap & (~0 << (*_fl + 1)));
        if (*_fl > 0) {         /* likely */
            *_sl = ls_bit(_tlsf->sl_bitmap[*_fl]);
            _b = _tlsf->matrix[*_fl][*_sl];
        }
    }
    return _b;
}


#define EXTRACT_BLOCK_HDR(_b, _tlsf, _fl, _sl) do {					\
		_tlsf -> matrix [_fl] [_sl] = _b -> ptr.free_ptr.next;		\
		if (_tlsf -> matrix[_fl][_sl])								\
			_tlsf -> matrix[_fl][_sl] -> ptr.free_ptr.prev = NULL;	\
		else {														\
			clear_bit (_sl, &_tlsf -> sl_bitmap [_fl]);				\
			if (!_tlsf -> sl_bitmap [_fl])							\
				clear_bit (_fl, &_tlsf -> fl_bitmap);				\
		}															\
		_b -> ptr.free_ptr.prev =  NULL;				\
		_b -> ptr.free_ptr.next =  NULL;				\
	}while(0)


#define EXTRACT_BLOCK(_b, _tlsf, _fl, _sl) do {							\
		if (_b -> ptr.free_ptr.next)									\
			_b -> ptr.free_ptr.next -> ptr.free_ptr.prev = _b -> ptr.free_ptr.prev; \
		if (_b -> ptr.free_ptr.prev)									\
			_b -> ptr.free_ptr.prev -> ptr.free_ptr.next = _b -> ptr.free_ptr.next; \
		if (_tlsf -> matrix [_fl][_sl] == _b) {							\
			_tlsf -> matrix [_fl][_sl] = _b -> ptr.free_ptr.next;		\
			if (!_tlsf -> matrix [_fl][_sl]) {							\
				clear_bit (_sl, &_tlsf -> sl_bitmap[_fl]);				\
				if (!_tlsf -> sl_bitmap [_fl])							\
					clear_bit (_fl, &_tlsf -> fl_bitmap);				\
			}															\
		}																\
		_b -> ptr.free_ptr.prev = NULL;					\
		_b -> ptr.free_ptr.next = NULL;					\
	} while(0)

#define INSERT_BLOCK(_b, _tlsf, _fl, _sl) do {							\
		_b -> ptr.free_ptr.prev = NULL; \
		_b -> ptr.free_ptr.next = _tlsf -> matrix [_fl][_sl]; \
		if (_tlsf -> matrix [_fl][_sl])									\
			_tlsf -> matrix [_fl][_sl] -> ptr.free_ptr.prev = _b;		\
		_tlsf -> matrix [_fl][_sl] = _b;								\
		set_bit (_sl, &_tlsf -> sl_bitmap [_fl]);						\
		set_bit (_fl, &_tlsf -> fl_bitmap);								\
	} while(0)

#if USE_SBRK || USE_MMAP
static __inline__ void *get_new_area(size_t * size) 
{
    void *area;

#if USE_SBRK
    area = (void *)sbrk(0);
    if (((void *)sbrk(*size)) != ((void *) -1))
        return area;
#endif

#ifndef MAP_ANONYMOUS
/* https://dev.openwrt.org/ticket/322 */
# define MAP_ANONYMOUS MAP_ANON
#endif


#if USE_MMAP
    *size = ROUNDUP(*size, PAGE_SIZE);
    if ((area = mmap(0, *size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) != MAP_FAILED)
        return area;
#endif
    return ((void *) ~0);
}
#endif

static __inline__ bhdr_t *process_area(void *area, size_t size)
{
    bhdr_t *b, *lb, *ib;
    area_info_t *ai;

    ib = (bhdr_t *) area;
    ib->size =
        (sizeof(area_info_t) <
         MIN_BLOCK_SIZE) ? MIN_BLOCK_SIZE : ROUNDUP_SIZE(sizeof(area_info_t)) | USED_BLOCK | PREV_USED;
    b = (bhdr_t *) GET_NEXT_BLOCK(ib->ptr.buffer, ib->size & BLOCK_SIZE);
    b->size = ROUNDDOWN_SIZE(size - 3 * BHDR_OVERHEAD - (ib->size & BLOCK_SIZE)) | USED_BLOCK | PREV_USED;
    b->ptr.free_ptr.prev = b->ptr.free_ptr.next = 0;
    lb = GET_NEXT_BLOCK(b->ptr.buffer, b->size & BLOCK_SIZE);
    lb->prev_hdr = b;
    lb->size = 0 | USED_BLOCK | PREV_FREE;
    ai = (area_info_t *) ib->ptr.buffer;
    ai->next = 0;
    ai->end = lb;
    return ib;
}

/******************************************************************/
/******************** Begin of the allocator code *****************/
/******************************************************************/

static char *mp = NULL;         /* Default memory pool. */

/* 受け口関数 #_TEPF_# */
/* #[<ENTRY_PORT>]# eMalloc
 * entry port: eMalloc
 * signature:  sMalloc
 * context:    task
 * #[</ENTRY_PORT>]# */

/* #[<ENTRY_FUNC>]# eMalloc_initializeMemoryPool
 * name:         eMalloc_initializeMemoryPool
 * global_name:  tTLSFMalloc_eMalloc_initializeMemoryPool
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
int
eMalloc_initializeMemoryPool(CELLIDX idx)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* エラー処理コードをここに記述します */
	} /* end if VALID_IDX(idx) */

	size_t mem_pool_size = ATTR_memoryPoolSize;
    void   *mem_pool = VAR_pool;
/******************************************************************/
	tlsf_t *tlsf;
    bhdr_t *b, *ib;

    if (!mem_pool || !mem_pool_size || mem_pool_size < sizeof(tlsf_t) + BHDR_OVERHEAD * 8) {
        ERROR_MSG("init_memory_pool (): memory_pool invalid\n");
        return -1;
    }

    if (((unsigned long) mem_pool & PTR_MASK)) {
        ERROR_MSG("init_memory_pool (): mem_pool must be aligned to a word\n");
        return -1;
    }
    tlsf = (tlsf_t *) mem_pool;
    /* Check if already initialised */
    if (tlsf->tlsf_signature == TLSF_SIGNATURE) {
        mp = mem_pool;
        b = GET_NEXT_BLOCK(mp, ROUNDUP_SIZE(sizeof(tlsf_t)));
        return b->size & BLOCK_SIZE;
    }

    mp = mem_pool;

    /* Zeroing the memory pool */
    memset(mem_pool, 0, sizeof(tlsf_t));

    tlsf->tlsf_signature = TLSF_SIGNATURE;

    TLSF_CREATE_LOCK(&tlsf->lock);

    ib = process_area(GET_NEXT_BLOCK
                      (mem_pool, ROUNDUP_SIZE(sizeof(tlsf_t))), ROUNDDOWN_SIZE(mem_pool_size - sizeof(tlsf_t)));
    b = GET_NEXT_BLOCK(ib->ptr.buffer, ib->size & BLOCK_SIZE);
    free_ex(b->ptr.buffer, tlsf);
    tlsf->area_head = (area_info_t *) ib->ptr.buffer;

#if TLSF_STATISTIC
    tlsf->used_size = mem_pool_size - (b->size & BLOCK_SIZE);
    tlsf->max_size = tlsf->used_size;
#endif

    return (b->size & BLOCK_SIZE);
}

/* #[<ENTRY_FUNC>]# eMalloc_calloc
 * name:         eMalloc_calloc
 * global_name:  tTLSFMalloc_eMalloc_calloc
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
void*
eMalloc_calloc(CELLIDX idx, size_t nelem, size_t elem_size)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* エラー処理コードをここに記述します */
	} /* end if VALID_IDX(idx) */

	void *mem_pool = VAR_pool;
/******************************************************************/
    void *ptr;

    if (nelem <= 0 || elem_size <= 0)
        return NULL;

    if (!(ptr = malloc_ex(nelem * elem_size, mem_pool)))
        return NULL;
    memset(ptr, 0, nelem * elem_size);

    return ptr;
}

/* #[<ENTRY_FUNC>]# eMalloc_malloc
 * name:         eMalloc_malloc
 * global_name:  tTLSFMalloc_eMalloc_malloc
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
void*
eMalloc_malloc(CELLIDX idx, size_t size)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* エラー処理コードをここに記述します */
	} /* end if VALID_IDX(idx) */

	void *mem_pool = VAR_pool;
/******************************************************************/
    tlsf_t *tlsf = (tlsf_t *) mem_pool;
    bhdr_t *b, *b2, *next_b;
    int fl, sl;
    size_t tmp_size;

    size = (size < MIN_BLOCK_SIZE) ? MIN_BLOCK_SIZE : ROUNDUP_SIZE(size);

    /* Rounding up the requested size and calculating fl and sl */
    MAPPING_SEARCH(&size, &fl, &sl);

    /* Searching a free block, recall that this function changes the values of fl and sl,
       so they are not longer valid when the function fails */
    b = FIND_SUITABLE_BLOCK(tlsf, &fl, &sl);
#if USE_MMAP || USE_SBRK
    if (!b) {
        size_t area_size;
        void *area;
        /* Growing the pool size when needed */
        area_size = size + BHDR_OVERHEAD * 8;   /* size plus enough room for the requered headers. */
        area_size = (area_size > DEFAULT_AREA_SIZE) ? area_size : DEFAULT_AREA_SIZE;
        area = get_new_area(&area_size);        /* Call sbrk or mmap */
        if (area == ((void *) ~0))
            return NULL;        /* Not enough system memory */
        add_new_area(area, area_size, mem_pool);
        /* Rounding up the requested size and calculating fl and sl */
        MAPPING_SEARCH(&size, &fl, &sl);
        /* Searching a free block */
        b = FIND_SUITABLE_BLOCK(tlsf, &fl, &sl);
    }
#endif
    if (!b)
        return NULL;            /* Not found */

    EXTRACT_BLOCK_HDR(b, tlsf, fl, sl);

    /*-- found: */
    next_b = GET_NEXT_BLOCK(b->ptr.buffer, b->size & BLOCK_SIZE);
    /* Should the block be split? */
    tmp_size = (b->size & BLOCK_SIZE) - size;
    if (tmp_size >= sizeof(bhdr_t)) {
        tmp_size -= BHDR_OVERHEAD;
        b2 = GET_NEXT_BLOCK(b->ptr.buffer, size);
        b2->size = tmp_size | FREE_BLOCK | PREV_USED;
        next_b->prev_hdr = b2;
        MAPPING_INSERT(tmp_size, &fl, &sl);
        INSERT_BLOCK(b2, tlsf, fl, sl);

        b->size = size | (b->size & PREV_STATE);
    } else {
        next_b->size &= (~PREV_FREE);
        b->size &= (~FREE_BLOCK);       /* Now it's used */
    }

    TLSF_ADD_SIZE(tlsf, b);
    VAR_mallocSize = (b->size & BLOCK_SIZE) + BHDR_OVERHEAD;

    return (void *) b->ptr.buffer;
}

/* #[<ENTRY_FUNC>]# eMalloc_realloc
 * name:         eMalloc_realloc
 * global_name:  tTLSFMalloc_eMalloc_realloc
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
void*
eMalloc_realloc(CELLIDX idx, const void* ptr, size_t new_size)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* エラー処理コードをここに記述します */
	} /* end if VALID_IDX(idx) */

	void *mem_pool = VAR_pool;
/******************************************************************/
    tlsf_t *tlsf = (tlsf_t *) mem_pool;
    void *ptr_aux;
    unsigned int cpsize;
    bhdr_t *b, *tmp_b, *next_b;
    int fl, sl;
    size_t tmp_size;

    if (!ptr) {
        if (new_size)
            return (void *) malloc_ex(new_size, mem_pool);
        if (!new_size)
            return NULL;
    } else if (!new_size) {
        free_ex(ptr, mem_pool);
        return NULL;
    }

    b = (bhdr_t *) ((char *) ptr - BHDR_OVERHEAD);
    next_b = GET_NEXT_BLOCK(b->ptr.buffer, b->size & BLOCK_SIZE);
    new_size = (new_size < MIN_BLOCK_SIZE) ? MIN_BLOCK_SIZE : ROUNDUP_SIZE(new_size);
    tmp_size = (b->size & BLOCK_SIZE);
    if (new_size <= tmp_size) {
	TLSF_REMOVE_SIZE(tlsf, b);
        if (next_b->size & FREE_BLOCK) {
            MAPPING_INSERT(next_b->size & BLOCK_SIZE, &fl, &sl);
            EXTRACT_BLOCK(next_b, tlsf, fl, sl);
            tmp_size += (next_b->size & BLOCK_SIZE) + BHDR_OVERHEAD;
            next_b = GET_NEXT_BLOCK(next_b->ptr.buffer, next_b->size & BLOCK_SIZE);
            /* We allways reenter this free block because tmp_size will
               be greater then sizeof (bhdr_t) */
        }
        tmp_size -= new_size;
        if (tmp_size >= sizeof(bhdr_t)) {
            tmp_size -= BHDR_OVERHEAD;
            tmp_b = GET_NEXT_BLOCK(b->ptr.buffer, new_size);
            tmp_b->size = tmp_size | FREE_BLOCK | PREV_USED;
            next_b->prev_hdr = tmp_b;
            next_b->size |= PREV_FREE;
            MAPPING_INSERT(tmp_size, &fl, &sl);
            INSERT_BLOCK(tmp_b, tlsf, fl, sl);
            b->size = new_size | (b->size & PREV_STATE);
        }
	TLSF_ADD_SIZE(tlsf, b);
    VAR_reallocSize = (b->size & BLOCK_SIZE) + BHDR_OVERHEAD;

        return (void *) b->ptr.buffer;
    }
    if ((next_b->size & FREE_BLOCK)) {
        if (new_size <= (tmp_size + (next_b->size & BLOCK_SIZE))) {
			TLSF_REMOVE_SIZE(tlsf, b);
            MAPPING_INSERT(next_b->size & BLOCK_SIZE, &fl, &sl);
            EXTRACT_BLOCK(next_b, tlsf, fl, sl);
            b->size += (next_b->size & BLOCK_SIZE) + BHDR_OVERHEAD;
            next_b = GET_NEXT_BLOCK(b->ptr.buffer, b->size & BLOCK_SIZE);
            next_b->prev_hdr = b;
            next_b->size &= ~PREV_FREE;
            tmp_size = (b->size & BLOCK_SIZE) - new_size;
            if (tmp_size >= sizeof(bhdr_t)) {
                tmp_size -= BHDR_OVERHEAD;
                tmp_b = GET_NEXT_BLOCK(b->ptr.buffer, new_size);
                tmp_b->size = tmp_size | FREE_BLOCK | PREV_USED;
                next_b->prev_hdr = tmp_b;
                next_b->size |= PREV_FREE;
                MAPPING_INSERT(tmp_size, &fl, &sl);
                INSERT_BLOCK(tmp_b, tlsf, fl, sl);
                b->size = new_size | (b->size & PREV_STATE);
            }
			TLSF_ADD_SIZE(tlsf, b);
            VAR_reallocSize = (b->size & BLOCK_SIZE) + BHDR_OVERHEAD;

            return (void *) b->ptr.buffer;
        }
    }

    if (!(ptr_aux = malloc_ex(new_size, mem_pool))){
        return NULL;
    }

    cpsize = ((b->size & BLOCK_SIZE) > new_size) ? new_size : (b->size & BLOCK_SIZE);

    memcpy(ptr_aux, ptr, cpsize);

    free_ex(ptr, mem_pool);
    return ptr_aux;
}

/* #[<ENTRY_FUNC>]# eMalloc_free
 * name:         eMalloc_free
 * global_name:  tTLSFMalloc_eMalloc_free
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
void
eMalloc_free(CELLIDX idx, const void* ptr)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* エラー処理コードをここに記述します */
	} /* end if VALID_IDX(idx) */

	void *mem_pool = VAR_pool;
/******************************************************************/
    tlsf_t *tlsf = (tlsf_t *) mem_pool;
    bhdr_t *b, *tmp_b;
    int fl = 0, sl = 0;

    if (!ptr) {
        return;
    }
    b = (bhdr_t *) ((char *) ptr - BHDR_OVERHEAD);
    b->size |= FREE_BLOCK;

    TLSF_REMOVE_SIZE(tlsf, b);
    VAR_freeSize = (b->size & BLOCK_SIZE) + BHDR_OVERHEAD;

    b->ptr.free_ptr.prev = NULL;
    b->ptr.free_ptr.next = NULL;
    tmp_b = GET_NEXT_BLOCK(b->ptr.buffer, b->size & BLOCK_SIZE);
    if (tmp_b->size & FREE_BLOCK) {
        MAPPING_INSERT(tmp_b->size & BLOCK_SIZE, &fl, &sl);
        EXTRACT_BLOCK(tmp_b, tlsf, fl, sl);
        b->size += (tmp_b->size & BLOCK_SIZE) + BHDR_OVERHEAD;
    }
    if (b->size & PREV_FREE) {
        tmp_b = b->prev_hdr;
        MAPPING_INSERT(tmp_b->size & BLOCK_SIZE, &fl, &sl);
        EXTRACT_BLOCK(tmp_b, tlsf, fl, sl);
        tmp_b->size += (b->size & BLOCK_SIZE) + BHDR_OVERHEAD;
        b = tmp_b;
    }
    MAPPING_INSERT(b->size & BLOCK_SIZE, &fl, &sl);
    INSERT_BLOCK(b, tlsf, fl, sl);

    tmp_b = GET_NEXT_BLOCK(b->ptr.buffer, b->size & BLOCK_SIZE);
    tmp_b->size |= PREV_FREE;
    tmp_b->prev_hdr = b;
}

/* #[<ENTRY_PORT>]# eMallocStatics
 * entry port: eMallocStatics
 * signature:  sMallocStatics
 * context:    task
 * #[</ENTRY_PORT>]# */

/* #[<ENTRY_FUNC>]# eMallocStatics_getMaxSize
 * name:         eMallocStatics_getMaxSize
 * global_name:  tTLSFMalloc_eMallocStatics_getMaxSize
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
size_t
eMallocStatics_getMaxSize(CELLIDX idx)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* エラー処理コードをここに記述します */
	} /* end if VALID_IDX(idx) */

	return get_max_size(VAR_pool);

}

/* #[<ENTRY_FUNC>]# eMallocStatics_getUsableSize
 * name:         eMallocStatics_getUsableSize
 * global_name:  tTLSFMalloc_eMallocStatics_getUsableSize
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
size_t
eMallocStatics_getUsableSize(CELLIDX idx)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* エラー処理コードをここに記述します */
	} /* end if VALID_IDX(idx) */

	//TODO: Actually it is NOT usable size
	return get_max_size(VAR_pool) - get_used_size(VAR_pool);

}

/* #[<ENTRY_FUNC>]# eMallocStatics_getUsedSize
 * name:         eMallocStatics_getUsedSize
 * global_name:  tTLSFMalloc_eMallocStatics_getUsedSize
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
size_t
eMallocStatics_getUsedSize(CELLIDX idx)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* エラー処理コードをここに記述します */
	} /* end if VALID_IDX(idx) */

	return get_used_size(VAR_pool);

}

/* #[<ENTRY_FUNC>]# eMallocStatics_getMallocSize
 * name:         eMallocStatics_getMallocSize
 * global_name:  tTLSFMalloc_eMallocStatics_getMallocSize
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
size_t
eMallocStatics_getMallocSize(CELLIDX idx)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* エラー処理コードをここに記述します */
	} /* end if VALID_IDX(idx) */

	return VAR_mallocSize;

}

/* #[<ENTRY_FUNC>]# eMallocStatics_getFreeSize
 * name:         eMallocStatics_getFreeSize
 * global_name:  tTLSFMalloc_eMallocStatics_getFreeSize
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
size_t
eMallocStatics_getFreeSize(CELLIDX idx)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* エラー処理コードをここに記述します */
	} /* end if VALID_IDX(idx) */

	return VAR_freeSize;

}

/* #[<ENTRY_FUNC>]# eMallocStatics_getReallocSize
 * name:         eMallocStatics_getReallocSize
 * global_name:  tTLSFMalloc_eMallocStatics_getReallocSize
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
size_t
eMallocStatics_getReallocSize(CELLIDX idx)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* エラー処理コードをここに記述します */
	} /* end if VALID_IDX(idx) */

	return VAR_reallocSize;

}

/* #[<POSTAMBLE>]#
 *   これより下に非受け口関数を書きます
 * #[</POSTAMBLE>]#*/
