#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif

struct context_t {
    int a;
    int b;
    int c;
};
struct context_t context;

void solve(struct context_t * ctx)
{
    uint64_t result = 1;
    for (int b = 0; b < ctx->b; b++) {
        result = (result * ctx->a) % ctx->c;
    }
    printf("%ld\n", result);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->a);
    scanf("%d", &ctx->b);
    scanf("%d", &ctx->c);
}

int main(int argc, char ** argv)
{
    int t = 1;

    //scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        init_data(&context);
        solve(&context);
    }
    return 0;
}
