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
    int h;
    int m;
};
struct context_t context;

void solve(struct context_t * ctx)
{
    ctx->h = (ctx->h + 23 + (ctx->m + 15)/60) % 24;
    ctx->m = (ctx->m + 15) % 60;
    printf("%d %d\n", ctx->h, ctx->m);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d %d", &ctx->h, &ctx->m);
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
