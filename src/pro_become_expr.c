#include "pro_become_expr.h"

#include <assert.h>
#include <stdio.h>


static void become_expr_eval(pro_state* s, pro_expr* t)
{
    assert(pro_expr_get_type(t) == PRO_BECOME_EXPR_TYPE);
}

static void become_expr_print(pro_state* s, pro_expr* t)
{
    pro_expr* left = t->value.binary.left;
    pro_expr* right = t->value.binary.right;

    printf("<Become id:");
    pro_print_expr(s, left);
    printf(" value:");
    pro_print_expr(s, right);
    printf(">\n");
}

const pro_expr_type_info pro_become_expr_type_info = {
    .eval = become_expr_eval,
    .print = become_expr_print
};


PRO_INTERNAL pro_expr* pro_become_expr_create(pro_expr* identifier, pro_expr* value)
{
    pro_expr* t = pro_expr_create(PRO_BECOME_EXPR_TYPE);
    t->value.binary.left = identifier;
    t->value.binary.right = value;
    return t;
}