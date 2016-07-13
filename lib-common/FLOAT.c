#include "FLOAT.h"

FLOAT F_mul_F(FLOAT a, FLOAT b) {
	long long my_a,my_b;
	FLOAT result;
	if(a>0)
		my_a=(long long)a;
	else
		my_a=(long long)(-a);
	if(b>0)
		my_b=(long long)b;
	else
		my_b=(long long)(-b);
	my_a=my_a*my_b;
	result=(FLOAT)(my_a>>16);
	if((a>0&&b<0)||(a<0&&!b>0))
		return -result;
	else
		return result;
}

FLOAT F_div_F(FLOAT a, FLOAT b) {
	FLOAT my_a=a,my_b=b;
	FLOAT my_integer,my_residue;
	if(a<0)
		my_a=-a;
	if(b<0)
		my_b=-b;
	if(my_a>=my_b)
		my_integer=my_a/my_b;
	else
		my_integer=0;
	my_residue=my_a-my_b*my_integer;
	int i;
	FLOAT my_mantissa=0;
	for(i=0;i<16;i++){
		my_residue=my_residue*2;
		my_mantissa*=2;
		if(my_residue>=my_b){
			my_residue=my_residue-my_b;
			my_mantissa=my_mantissa|0x1;
		}
	}
	if((a>0&&b<0)||(a<0&&b>0))
		return -((my_integer<<16)|my_mantissa);
	else
		return (my_integer<<16)|my_mantissa;
}

FLOAT f2F(float a) {
	FLOAT my_a=*(FLOAT *)&a;
	FLOAT my_mantissa=(my_a&0x007fffff)|0x00800000;
	FLOAT my_order=(my_a&0x7f800000)>>23;
	FLOAT my_move=my_order-127;
	if(my_move>=7){
		if(my_a>0)
			return (my_mantissa<<(my_move-7));
		else
			return -(my_mantissa<<(my_move-7));
	}
	else{
		if(my_a>0)
			return (my_mantissa>>(7-my_move));
		else
			return -(my_mantissa>>(7-my_move));
	}


}

FLOAT Fabs(FLOAT a) {
	if (a<0) return -a;
	return a;
}

FLOAT sqrt(FLOAT x) {
	FLOAT dt, t = int2F(2);
	do {
		dt = F_div_int((F_div_F(x, t) - t), 2);
		t += dt;
	} while(Fabs(dt) > f2F(1e-4));

	return t;
}

FLOAT pow(FLOAT x, FLOAT y) {
	/* we only compute x^0.333 */
	FLOAT t2, dt, t = int2F(2);

	do {
		t2 = F_mul_F(t, t);
		dt = (F_div_F(x, t2) - t) / 3;
		t += dt;
	} while(Fabs(dt) > f2F(1e-4));

	return t;
}

