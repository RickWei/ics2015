#define DATA_BYTE 2
#include "movcc-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "movcc-template.h"
#undef DATA_BYTE

make_helper_v(movcc_rm2r)

