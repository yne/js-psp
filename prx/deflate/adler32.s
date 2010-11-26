#define zero	$0	/* wired zero */
#define at		$1	/* assembler temp */
#define v0		$2	/* return value */
#define v1		$3
#define a0		$4	/* argument registers */
#define a1		$5
#define a2		$6
#define a3		$7
#define t0		$8	/* caller saved */
#define t1		$9
#define t2		$10
#define t3		$11
#define t4		$12
#define t5		$13
#define t6		$14
#define t7		$15
#define s0		$16 /* callee saved */
#define s1		$17
#define s2		$18
#define s3		$19
#define s4		$20
#define s5		$21
#define s6		$22
#define s7		$23
#define t8		$24 /* code generator */
#define t9		$25
#define k0		$26 /* kernel temporary */
#define k1		$27
#define gp		$28 /* global pointer */
#define sp		$29 /* stack pointer */
#define fp		$30 /* frame pointer */
#define ra		$31 /* return address */


	.set	noreorder

	.text
	.global sceZlibAdler32

#define BASE 65521	  // the biggest prime number less than 65536
#define NMAX 5552

//E calculate Adler-32 checksum
// unsigned int sceZlibAdler32(unsigned int uiAdler, const unsigned char *pSrc, unsigned int uiSize);
//	a0 = uiAdler
//	a1 = pSrc
//	a2 = uiSize
sceZlibAdler32:
		andi		v0, a0, 0xFFFF		// v0 = a0 & 0xFFFF
		srl			v1, a0, 16			// v1 = a0>>16
		li			t2, BASE
		li			t3, NMAX

0:
		beq			a2, zero, _adler32_end
		min			t1, a2, t3			// t1 = min(NMAX, a2) (delay slot)
		subu		a2, a2, t1			// a2 = a2 - t1

1:
		lbu			t0, 0(a1)			// t0 = *(a1)	= s1
		addiu		a1, a1, 1			// a1 = a1 + 1
		addiu		t1, t1, -1			// t1 = t1 - 1
		addu		v0, v0, t0			// v0 = v0 + t0 = s1
		bne			t1, zero, 1b
		addu		v1, v1, v0			// v1 = v1 + v0 = s2 (delay slot)

//E normalize(modulo by BASE)
		divu		v0, t2		// HI = v0 % t2 = s1 % BASE
		mfhi		v0			// v0 = HI
		divu		v1, t2		// HI = v1 % t2 = s2 % BASE
		j			0b
		mfhi		v1			// v1 = HI

//E Adler-32 calculation end
_adler32_end:
		j			ra
		ins			v0, v1, 16, 16		 // v0 |= (v1<<16)
