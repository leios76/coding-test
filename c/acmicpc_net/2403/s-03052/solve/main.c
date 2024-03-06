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
    int n[10];
    int count[42];
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;
    for (int i = 0; i < 10; i++) {
        ctx->count[ctx->n[i]%42]++;
    }
    for (int i = 0; i < 42; i++) {
        if (ctx->count[i] > 0) {
            result++;
        }
    }
    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    for (int n = 0; n < 10; n++) {
        scanf("%d", &ctx->n[n]);
    }
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
