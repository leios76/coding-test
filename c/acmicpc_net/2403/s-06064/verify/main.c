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
    int m;
    int x;
    int y;
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;

    int x = 1;
    int y = 1;

    while (1) {
        result++;
        if (x == ctx->x && y == ctx->y) {
            break;
        }
        if (x == ctx->m && y == ctx->n) {
            result = -1;
            break;
        }
        if (x < ctx->m) {
            x++;
        } else {
            x = 1;
        }
        if (y < ctx->n) {
            y++;
        } else {
            y = 1;
        }
    }
    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->m);
    scanf("%d", &ctx->n);
    scanf("%d", &ctx->x);
    scanf("%d", &ctx->y);
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
