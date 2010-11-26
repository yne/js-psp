#define zero    $0  /* wired zero */
#define at      $1  /* assembler temp */
#define v0      $2  /* return value */
#define v1      $3
#define a0      $4  /* argument registers */
#define a1      $5
#define a2      $6
#define a3      $7
#define t0      $8  /* caller saved */
#define t1      $9
#define t2      $10
#define t3      $11
#define t4      $12
#define t5      $13
#define t6      $14
#define t7      $15
#define s0      $16 /* callee saved */
#define s1      $17
#define s2      $18
#define s3      $19
#define s4      $20
#define s5      $21
#define s6      $22
#define s7      $23
#define t8      $24 /* code generator */
#define t9      $25
#define k0      $26 /* kernel temporary */
#define k1      $27
#define gp      $28 /* global pointer */
#define sp      $29 /* stack pointer */
#define fp      $30 /* frame pointer */
#define ra      $31 /* return address */

#define ERROR_DECMODE   0xFF
#define ERROR_READLEN   0xFF
#define ERROR_MKHUFFMAN 0xFF
#define ERROR_LZ77      0xFF
#define ERROR_LENNLEN   0xFF
#define ERROR_BUFOVER   0xFF

//#undef NEEDSPEED

#ifdef NEEDSPEED
# define FASTMKHUFFMAN 1
# define FASTMEMCOPY 1
#else
# define FASTMKHUFFMAN 0
# define FASTMEMCOPY 0
#endif

    .set    noreorder
    .set    noat

    .text
    .align  4
    .global sceDeflateDecompress
    .ent    sceDeflateDecompress

#define HT_MINLEN       (0x0000)	
#define HT_OFFSET       (0x0002)	
#define HT_MAXCODE      (0x001e)	
#define HT_SYMBOL       (0x003c)	
#if FASTMKHUFFMAN
# define HT_SUBBUF      636
#endif


#define WK_HTLITERAL    (0)
#define WK_HTDISTANCE   (636)
#if FASTMKHUFFMAN
# define WK_HTLENGTH    (1212)
	
# define WK_FRAMESIZE   (1336+8)
#else
# define WK_HTLENGTH    (636+124)
	
# define WK_FRAMESIZE   (896)
#endif

#define WK_SAVES4   (WK_HTLENGTH+HT_OFFSET+14) 
#define WK_SAVESRA  (WK_HTLENGTH+HT_OFFSET+22) 
#define WK_hENDMODE (WK_HTLENGTH+HT_OFFSET+26) 
#define WK_hHLEN    (WK_HTLENGTH+HT_SYMBOL+40) 

	.macro      GETBITS	idx, r
	addu	t9, t9, \r	      
	bgtz	t9, getbs_sub\idx       
	rotrv       v0, t8, t9	      
getbs_ret\idx:
	.endm
	.macro      GETBITS_SUB    idx
getbs_sub\idx:
	lw	  t8, 4(a2)       
	sllv	v0, v0, t9      
	addiu       a2, a2, 4       
	addiu       t9, t9, -32     
	ins	 v0, t8, 0, 16   
	j	   getbs_ret\idx   
	rotrv       v0, v0, t9      
	.endm
sceDeflateDecompress:
	addiu       sp, sp, -WK_FRAMESIZE   
	sw	  s4, WK_SAVES4(sp)       
	addu	a1, a0, a1	      
	move	t6, a0		  
	la	  t7, fixhuff_huffcodes   
	sw	  ra, WK_SAVESRA(sp)      
deflate_lop0:
	andi	t9, a2, 3	       
	subu	a2, a2, t9	      
	lw	  t8, 0(a2)	       
	sll	 t9, t9, 3	       
	addiu       t9, t9, -32
deflate_lop:
	GETBITS     0, 3		    
	ext	 v1, v0, 30, 2	   
	beq	 v1, zero, decmode_0     
	ext	 t2, v0, 29, 1	   
	addiu       t0, v1, -2	      
	beq	 t0, t0, decmode_2       
	sh	  t2, WK_hENDMODE(sp)     
	bgtz	t0, unknownmode	 
	addiu       t2, sp, WK_HTLITERAL    
	addiu       s4, t7, 108     
1:
	lw	  t3,  (t7)       
	addiu       t2, t2, 4       
	addiu       t7, t7, 4       
	bne	 s4, t7, 1b      
	sw	  t3,  -4(t2)     
	addiu       t1, zero, 0x00  
	addiu       s4, zero, 0x90  
3:
	sh	  t1, 0(t2)       
	addiu       t1, t1, 1       
	bne	 t1, s4, 3b      
	addiu       t2, t2, 2       
	addiu       s4, t7, 16      
5:
	lw	  t3,  (t7)       
	addiu       t2, t2, 4       
	addiu       t7, t7, 4       
	bne	 s4, t7, 5b      
	sw	  t3,  -4(t2)     
	addiu       s4, zero, 256+30
4:
	sh	  t1, 0(t2)
	addiu       t1, t1, 1
	bne	 t1, s4, 4b
	addiu       t2, t2, 2
	addiu       s4, t7, 64      
2:
	lw	  t3,  (t7)       
	addiu       t2, t2, 4       
	addiu       t7, t7, 4       
	bne	 s4, t7, 2b      
	sw	  t3,  -4(t2)     
	addiu       t7, t7, -188    
	sh	  t3, WK_HTDISTANCE+HT_MAXCODE(sp)
	j	   decodeSub	   
	sh	  t3, WK_HTDISTANCE+HT_MINLEN(sp)     
	GETBITS_SUB    0
	GETBITS_SUB    2
	GETBITS_SUB    3
decmode_2:
	GETBITS     2, 14
	sw	  v0, WK_hHLEN(sp)	    
	ext	 s4, v0, 28, 4	   
	addiu       s4, s4, 4
	addiu       t3, sp, WK_HTLENGTH
	move	t0, t7		  
	addu	s4, s4, t7
0:
	beq	 t0, s4, dht_lenskip     
	addiu       t0, t0, 1	       
	GETBITS     3, 3		    
	srl	 v0, v0, (32-3)	  
	beq	 v0, zero, 0b	    
	lb	  t2, 6-1(t0)	     
	addiu       t3, t3, 2	       
	ins	 t2, v0, 9, 6	    
	j	   0b
	sh	  t2, HT_SYMBOL-2(t3)     
dht_lenskip:
	jal	 MakeHuffmanTable
	addiu       s4, sp, WK_HTLENGTH     
	lw	  t5, WK_hHLEN(sp)	
	beq	 t0, zero, mht_error     
	addiu       s4, sp, WK_HTLITERAL    
	ext	 t5, t5, 18, 5	   
	jal	 ReadLengths
	addiu       t5, t5, 257	     
	beq	 t0, zero, mht_error     
	addiu       t0, sp, WK_HTLITERAL
0:
	lh	  t1, HT_SYMBOL(t0)   
	addu	t0, t0, 2	   
	andi	t2, t1, 0xff	
	beq	 t2, t1, 1f	  
	addu	t2, t2, t2	  
	addu	t2, t2, t7
	lh	  t1, 60(t2)	  
1:
	bne	 t0, t3, 0b	  
	sh	  t1, HT_SYMBOL-2(t0) 
	lw	  t5, WK_hHLEN(sp)
	addiu       s4, sp, WK_HTDISTANCE   
	jal	 ReadLengths2
	ext	 t5, t5, 23, 5	   
	addiu       t0, sp, -32*2
lenRewrite:
	lh	  t1, WK_HTDISTANCE+32*2+HT_SYMBOL(t0)
	andi	t1, t1, 31  
	addu	t1, t1, t1
	addu	t1, t1, t7
	lh	  t1, 124(t1) 
	addu	t0, t0, 2
	bne	 t0, sp, lenRewrite
	sh	  t1, WK_HTDISTANCE+32*2-2+HT_SYMBOL(t0)  
decodeSub:
lz77_lop:	
	lb      t2, WK_HTLITERAL+HT_MINLEN(sp)
	lhu     v1, WK_HTLITERAL+HT_MAXCODE(sp)
	jal     DecodeHuffman
	addiu   t0, sp, WK_HTLITERAL+2  
	addiu   t0, sp, WK_HTDISTANCE+2 
	bitrev  t2, v0		  
	bgez    v0, lz77_rawstore       
	sra     s4, v0, 4	       
	bltzal  t2, lz77_len0	   
	lhu     v1, WK_HTDISTANCE+HT_MAXCODE(sp)	
	lb      t2, WK_HTDISTANCE+HT_MINLEN(sp)
	jal     DecodeHuffman
	subu    at, a0, s4	      
	sltu    s4, a1, at	      
	bne     s4, zero, bufoverrun    
	clz     t2, v0		  
	addiu   t2, t2, -30
	bltzal  t2, lz77_dist0	  
	subu    s4, a0, v0	      
	sltu    t2, t6, s4	      
	beq     t2, zero, lz77_error    
	addiu   a0, a0, 1	       
#if FASTMEMCPY
	beq     s4, a0, lz77_copy_samelop
#endif
	lbu     t0, -1(s4)	      
lz77_copy_lop:
	addiu   s4, s4, 1	       
	beq     at, a0, lz77_lop	
	sb      t0, -1(a0)	      
	addiu   a0, a0, 1	       
	j       lz77_copy_lop	   
	lbu     t0, -1(s4)	      
#if FASTMEMCPY
lz77_copy_samelop:
	beq     at, a0, lz77_lop	
	sb      t0, -1(a0)	      
	j       lz77_copy_samelop       
	addiu   a0, a0, 1	       
#endif
getbs_sub200:
	lw      t8, 4(a2)       
	sllv    v0, v0, t9      
	addiu   a2, a2, 4       
	addiu   t9, t9, -32     
	ins     v0, t8, 0, 16   
	rotrv   v0, v0, t9      
	srlv    v0, v0, t2
	jr      ra	      
	subu    s4, s4, v0      
lz77_rawstore:
	beq     a0, a1, bufoverrun  
	addiu   a0, a0, 1	   
	j       lz77_lop	    
	sb      v0, -1(a0)	  
lz77_dist0:
	bltz    v0, lz77_error      
	subu    t9, t9, t2	  
	bgtz    t9, getbs_sub200    
	rotrv   v0, t8, t9	  
	srlv    v0, v0, t2	  
	jr      ra		  
	subu    s4, s4, v0	  
lz77_len0:
	sra     t2, t2, 28	  
	beq     s4, t2, lz77_len2   
	subu    t9, t9, t2	  
	bgtz    t9, getbs_sub200    
	rotrv   v0, t8, t9	  
	srlv    v0, v0, t2	  
	jr      ra		  
	subu    s4, s4, v0	  
lz77_len2:
	addiu   v0, v0, 1	       
	beq     v0, zero, lz77_error    
	lh      t0, WK_hENDMODE(sp)     
	beq     t0, zero, deflate_lop   
	addu    t9, t9, t2	      
decmode_end:
	beq     a3, zero, deflate_end   
	subu    v0, a0, t6	      
	addiu   t9, t9, 39	      
	srl     t1, t9, 3	       
	addu    a2, a2, t1	      
	sw      a2, 0(a3)	       
deflate_end:
	lw      ra, WK_SAVESRA(sp)      
	lw      s4, WK_SAVES4(sp)       
	jr      ra		      
	addiu   sp, sp, +WK_FRAMESIZE   
getbs_sub100:
	addiu   a2, a2, 4       
	lw      t8, 0(a2)       
	sllv    v0, v0, t9      
	addiu   t9, t9, -32     
	ins     v0, t8, 0, 16   
	rotrv   v0, v0, t9      
	j       getbs_ret100    
	ins     v0, zero, 0, 16 

DecodeHuffman:
	srlv    v0, t8, t9	  
	subu    t9, t9, t2	  
	bgtz    t9, getbs_sub100    
	sllv    v0, v0, t2	  
getbs_ret100:
	bitrev  v0, v0	      
	sltu    t2, v0, v1	  
	beq     t2, zero, dechuff_lop0 
	addu    v0, v0, v0	  
	addu    v0, v0, t0	  
	jr      ra		  
	lh      v0, HT_SYMBOL-2(v0) 
dechuff_end:
	lh      t2, HT_OFFSET-2(t0) 
	addu    v0, v0, t0	  
	bgtz    t2, dechuff_end2    
	addu    v0, v0, t2	  
	jr      ra		  
	lh      v0, HT_SYMBOL(v0)   
dechuff_end2:
	addiu   v0, v0, 0x8000	      
	jr      ra			  
	lh      v0, HT_SYMBOL-0x8000(v0)    
dechuff_lop0:
	beq     t9, zero, get1b_sub1    
	lhu     v1, HT_MAXCODE(t0)      
	srlv    t2, t8, t9	      
	ins     v0, t2, 0, 1	    
dechuff_lop:
	slt     v1, v0, v1	      
	addu    v0, v0, v0	      
	bne     v1, zero, dechuff_end   
	addiu   t9, t9, 1	       
	j       dechuff_lop0	
	addiu   t0, t0, 2	   
get1b_sub1:
	addiu   a2, a2, 4	   
	lw      t8, 0(a2)	   
	addiu   t9, zero, -32       
	j       dechuff_lop	 
	ins     v0, t8, 0, 1	
ReadLengths2:
	addiu   t5, t5, 1
ReadLengths:
	sw      zero, HT_MAXCODE+26(s4) 
	move    t4, zero		
	addiu   at, zero, -1	    
	sw      zero, HT_MAXCODE+14(s4) 
	move    t3, s4		  
	mthi    ra		      
	sw      zero, HT_MAXCODE+22(s4) 
	addiu   t1, zero, 7
readlen_lop:
	sltu    t0, t4, t5	      
	beq     t0, zero, MakeHuffman2  

	lb      t2, WK_HTLENGTH+HT_MINLEN(sp)  
	lhu     v1, WK_HTLENGTH+HT_MAXCODE(sp) 
	jal     DecodeHuffman	   
	addiu   t0, sp, WK_HTLENGTH+2   

	addiu   t0, v0, -16	     
	blez    t0, readlen_0_16	

	
	min     t2, t0, t1	      
	GETBITS 5, t2		   
	neg     t2, t2
	srlv    v0, v0, t2	      
	addu    t0, t0, v0	      
readlen_16_zero:	
	addu    t4, t4, t0	      
	j       readlen_lop	     
	addiu   at, t4, -1	      

readlen_0_16:
	beq     t0, zero, readlen_16    
	addiu   t4, t4, 1	       

	beq     v0, zero, readlen_lop   
	addiu   at, t4, -1	      

	
	ins     at, v0, 9, 6	    
	sh      at, HT_SYMBOL(t3)       
	j       readlen_lop	     
	addiu   t3, t3, 2	       

	GETBITS_SUB    5

readlen_16:
	
	bltz    at, readlen_error       

	GETBITS 1, 2		    
	srl     v0, v0, (32-2)	  
	andi    t0, at, 0x7e00	  
	beq     t0, zero, readlen_16_zero   
	addiu   t0, v0, 3	       
	addu    t0, t0, at	      
	
readlen_16_lop:
	addiu   at, at, 1	       
	sh      at, HT_SYMBOL(t3)       
	bne     at, t0, readlen_16_lop  
	addiu   t3, t3, 2	       

	andi    t4, at, 0x01ff	  
	j       readlen_lop	     
	addiu   t4, t4, 1	       
	GETBITS_SUB    1
#if FASTMKHUFFMAN
MakeHuffman2:
	sw	  zero, HT_MAXCODE+18(s4) 
	bne	 t4, t5, readlen_error   
	sw	  zero, HT_MAXCODE+2(s4)  
	move	t0, zero		
	addiu       ra, zero, 0x7fff
	sw	  zero, HT_MAXCODE+6(s4)  
	addiu       t1, s4, 2
	addiu       at, zero, -1	    
	sw	  zero, HT_MAXCODE+10(s4) 
	move	t4, s4
	move	t5, s4		  
mht_2copylop:
	lh	  v0, HT_SYMBOL(t4)       
	addiu       t4, t4, 2
	min	 ra, ra, v0	      
	bne	 t3, t4, mht_2copylop    
	sh	  v0, HT_SUBBUF-2(t4)
	andi	ra, ra, 0x7e00	  
mht_2sortlop1:
	addiu       ra, ra, 512	     
	move	v1, s4		  
mht_2sortlop3:
	beq	 t3, t5, mht2_ret	
	addiu       t2, zero, -1
mht_2sortlop2:
	lhu	 v0, HT_SUBBUF(v1)       
	beq	 t3, v1, mht_2sortlop1   
	min	 v0, v0, ra	      
	beq	 v0, ra, mht_2sortlop2
	addiu       v1, v1, 2	       

	
	
	addiu       at, at, 1	       
	sh	  t2, HT_SUBBUF-2(v1)     
	srl	 t4, v0, 9
	andi	v0, v0, 511
	sh	  v0, HT_SYMBOL(t5)       
	beq	 t0, t4, mht_2sortlop3   
	addiu       t5, t5, 2	       

	
	subu	t2, t0, t4	      
	beq	 t0, zero, mht_2skip2    
	move	t0, t4		  

	sh	  at, HT_MAXCODE-2(t1)    

	rotrv       at, at, t2	      
	addu	t2, t2, t2	      
	subu	t1, t1, t2	      

	subu	t2, t5, at	      
	subu	t2, t2, at
	subu	t2, t2, t1
mht_2skip2:
	blez	t2, mht_2sortlop3       
	sh	  t2, HT_OFFSET-4(t1)     

	j	   deflate_error	   
	li	  v0, (ERROR_MKHUFFMAN&0xffff)	
#endif
#if FASTMKHUFFMAN
mht2_ret:
	mfhi	ra
#endif
mht_ret:
	addiu       at, zero, -1
	jr	  ra		      
	sh	  at, HT_MAXCODE-2(t1)    
#if !FASTMKHUFFMAN
MakeHuffman2:
	sw	  zero, HT_MAXCODE+18(s4) 
	bne	 t4, t5, readlen_error   
	mfhi	ra
#endif
MakeHuffmanTable:
	sw	  zero, HT_MAXCODE+2(s4)  
	move	t0, zero		
	sw	  zero, HT_MAXCODE+6(s4)  
	addiu       t1, s4, 2
	addiu       at, zero, -1	    
	sw	  zero, HT_MAXCODE+10(s4) 
mht_sortlop1:
	beq	 t3, s4, mht_ret	 
	addiu       at, at, 1	       
	addiu       t4, s4, 2	       
	lh	  v0, HT_SYMBOL(s4)       
mht_sortlop2:
	lh	  v1, HT_SYMBOL(t4)       
	beq	 t3, t4, mht_sortlop2end 
	addiu       t4, t4, 2	       
	max	 t2, v1, v0	      
	sh	  t2, HT_SYMBOL-2(t4)     
	j	   mht_sortlop2
	min	 v0, v1, v0	      

mht_sortlop2end:
	
	srl	 t4, v0, 9	       
	andi	v0, v0, 511	     
	sh	  v0, HT_SYMBOL(s4)       
	beq	 t0, t4, mht_sortlop1    
	addiu       s4, s4, 2	       

	
	subu	t2, t0, t4	      
	beq	 t0, zero, mht_skip2     
	move	t0, t4		  

	sh	  at, HT_MAXCODE-2(t1)    

	rotrv       at, at, t2	      
	addu	t2, t2, t2	      
	subu	t1, t1, t2	      

	subu	t2, s4, at	      
	subu	t2, t2, at
	subu	t2, t2, t1
mht_skip2:
	blez	t2, mht_sortlop1	
	sh	  t2, HT_OFFSET-4(t1)     



mht_error:
	j       deflate_error
	li      v0, (ERROR_MKHUFFMAN&0xffff)    

lz77_error:
	j       deflate_error
	li      v0, (ERROR_LZ77&0xffff)	 

bufoverrun:
	j       deflate_error
	li      v0, (ERROR_BUFOVER&0xffff)      

readlen_error:  
	j       deflate_error
	li      v0, (ERROR_READLEN&0xffff)      

unknownmode:
	li      v0, (ERROR_DECMODE&0xffff)      

deflate_error:
	lui     v1, (ERROR_MKHUFFMAN >> 16)
	j       deflate_end
	or      v0, v0, v1





decmode_0:
	neg	 t0, t9
	srl	 t0, t0, 3	       
	subu	a2, a2, t0	      

	ulw	 t0, 4(a2)
	
	andi	v1, t0, 0xFFFF	  
	addu	v1, v1, a0	      
	sltu	t1, a1, v1	      
	bne	 t1, zero, bufoverrun    

	not	 t1, t0		  
	rotr	t1, t1, 16	      
	bne	 t1, t0, deflate_error   
	li	  v0, (ERROR_LENNLEN&0xffff)
0:
	lbu	 t1, 8(a2)	       
	addiu       a2, a2, 1
	addiu       a0, a0, 1
	bne	 v1, a0, 0b	      
	sb	  t1, -1(a0)	      
	bne	 t2, zero, decmode_end   
	addiu       t9, zero, 32	    
	j	   deflate_lop0	    
	addiu       a2, a2, 8	       
    .end    sceDeflateDecompress
    .section    .rodata
    .p2align    6
#define PAD 0
fixhuff_huffcodes:
    .half   -7

    .half   -0x18*2-2, -0xe0*2-4

    .byte   16, 3+16,11+16,    0,    8,    7,    9,    6
    .byte   10,    5,   11,    4,   12,    3,   13,    2
    .byte   14,    1,   15

    .byte   PAD,PAD,PAD,PAD,PAD

    .half   24, 200, 512
    .half   PAD, PAD, PAD, PAD, PAD, PAD, PAD, PAD, PAD, PAD, PAD, PAD /* 12 word */

    .half   0xffe7, 0xffd0, 0xffc0, 0xffb0, 0xffa0, 0xff90, 0xff80, 0xff70
    .half   0xff60, 0xff5f, 0xff3f, 0xff1f, 0xfeff, 0xfed7, 0xfe97, 0xfe57
    .half   0xfe17, 0xfddb, 0xfd5b, 0xfcdb, 0xfc5b, 0xfbd3, 0xfad3, 0xf9d3

    .half   0xf8d3, 0xf7dd, 0xf5dd, 0xf3dd, 0xf1dd, 0xefe0, 0xffff, 0xffff

    .half      0,    1,    2,    3,    4,    6,    8,   12
    .half     16,   24,   32,   48,   64,   96,  128,  192
    .half    256,  384,  512,  768, 1024, 1536, 2048, 3072
    .half   4096, 6144, 8192,12288,16384,24576,   -5,   -5
