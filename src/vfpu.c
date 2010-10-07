#define VFPU_START ".set push\n.set noreorder\n"
#define VFPU_STOP ".set pop\n"

double floor(double x){
	float s,d = x;
	__asm__ (
		"lv.s			s000, %1\n"// s
		"vf2id.s		s000, s000, 0\n" // s000 = (int)floor(s000)
		"vi2f.s			s000, s000, 0\n" // s000 = (float)s000
		"sv.s			s000, %0\n" // d
		: "=m"(s) : "m"(d)
	);
	double r = s;
	return (r);
}
double fmod(double a, double b) {
	float x = a;
	float y = b;
	float result;
	// return x-y*((int)(x/y));
	__asm__ volatile (
		"mtv       %2, S001\n"
		"mtv       %1, S000\n"
		"vrcp.s    S002, S001\n"
		"vmul.s    S003, S000, S002\n"
		"vf2iz.s   S002, S003, 0\n"
		"vi2f.s    S003, S002, 0\n"
		"vmul.s    S003, S003, S001\n"
		"vsub.s    S000, S000, S003\n"
		"mfv       %0, S000\n"
		: "=r"(result) : "r"(x), "r"(y)
	);
	double r = result;
	return r;
}
double ceil(double x){
	float d,s=x;
	__asm__ (
		"lv.s			s000, %1\n"				// s000 = s
		"vf2iu.s		s000, s000, 0\n"		// s000 = (int)ceil(s000)
		"vi2f.s			s000, s000, 0\n"		// s000 = (float)s000
		"sv.s			s000, %0\n"				// d    = s000
		: "=m"(d) : "m"(s)
	);
	double r = d;
	return (r);
}
double rnd_prod(double da,double db){
	float a=da,b=db;
	__asm__ (
		"mtv	%1, S000\n"//a
		"mtv	%2, S001\n"//b
		"vmul.s	S000, S000, S001\n"//a *= b
		"mfv	%0, S000\n"//a
		: "=r"(a) : "r"(a), "r"(b)
	);
	float result = a;
	return(result);
}
double rnd_quot(double da,double db){
	float a=da,b=db;
	__asm__ (
		"mtv	%1, S000\n"//a
		"mtv	%2, S001\n"//b
		"vdiv.s	S000, S000, S001\n"//a /= b
		"mfv	%0, S000\n"//a
		: "=r"(a) : "r"(a), "r"(b)
	);
	float result = a;
	return(result);
}