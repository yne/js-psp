#define HUGE_VAL (__builtin_huge_val())
#define VFPU_START ".set push\n.set noreorder\n"
double floor(double x);
double fmod(double a, double b);
double ceil(double x);
//more optimization
double rnd_prod(double da,double db);
double rnd_quot(double da,double db);