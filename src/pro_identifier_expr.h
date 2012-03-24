#ifndef prosopon_pro_identifier_expr_h
#define prosopon_pro_identifier_expr_h

#include "prosopon.h"

#include "pro_expr.h"
#include "pro_expr_type.h"


extern const pro_expr_type_info pro_identifier_expr_type_info;


PRO_INTERNAL pro_expr* pro_identifier_expr_create(char* value);




#endif