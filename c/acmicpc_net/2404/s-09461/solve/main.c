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
    int n;
    uint64_t dp[100];
};
struct context_t context;

void solve(struct context_t * ctx)
{
    ctx->dp[0] = 0;
    ctx->dp[1] = 1;
    ctx->dp[2] = 1;
    ctx->dp[3] = 1;
    ctx->dp[4] = 2;

    for (int n = 5; n <= ctx->n; n++) {
        ctx->dp[n] = ctx->dp[n - 1] + ctx->dp[n - 5];
    }
    printf("%lu\n", ctx->dp[ctx->n]);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
}

int main(int argc, char ** argv)
{
    int t = 1;

    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        init_data(&context);
        solve(&context);
    }
    return 0;
}
