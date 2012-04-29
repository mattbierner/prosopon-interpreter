#include "pro_identifier_expr.h"

#include <assert.h>
#include <stdio.h>


static pro_ref identifier_expr_eval(pro_state_ref s, pro_ref ref, pro_expr* t)
{
    assert(pro_expr_get_type(t) == PRO_IDENTIFIER_EXPR_TYPE);
    
    pro_ref out;
    pro_env_ref env;
    pro_get_env(s, &env);
    pro_get_binding(s, env, t->value.identifier, &out);
    pro_env_release(s, env);

    return out;
}

static void identifier_expr_print(pro_state_ref s,
    const pro_expr* t, const char* end)
{
    assert(pro_expr_get_type(t) == PRO_IDENTIFIER_EXPR_TYPE);
    char* value = t->value.identifier;
    
    printf("<identifier %s>\n", value);
}

static void identifier_expr_release(pro_state_ref s, void* data)
{
    pro_expr* t = data;
    pro_alloc* alloc;
    pro_get_alloc(s, &alloc);
    alloc(t->value.identifier, 0);
    PRO_DEFAULT_UD_DECONSTRUCTOR(s, data);
}


#pragma mark -
#pragma mark Internal

const pro_expr_type_info pro_identifier_expr_type_info = {
    .eval = identifier_expr_eval,
    .print = identifier_expr_print,
};


PRO_INTERNAL
pro_ref pro_identifier_expr_create(pro_state_ref s, 
    char* value)
{
    pro_expr* t;
    pro_ref ref = pro_expr_create(s, PRO_IDENTIFIER_EXPR_TYPE,
        identifier_expr_release, &t);
    t->value.identifier = value;
    return ref;
}
