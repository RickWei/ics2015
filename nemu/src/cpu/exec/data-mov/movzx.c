#include "cpu/exec/helper.h"

#define DATA_BYTE 2
#include "movzx-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "movzx-template.h"
#undef DATA_BYTE

/* for instruction encoding overloading */
make_helper_v(movzx_rmb2r)
make_helper_v(movzx_rml2r)
