#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif



struct queue_entity_t {
    char op;
    int prev_index;
    int next_index;
};

struct queue_t {
    struct queue_entity_t queue_pool[100];
    int queue_head_index;
    int queue_tail_index;
    int queue_size;
};

void remove_queue(struct queue_t * queue, int index)
{
    #ifdef DEBUG_QUEUE
    debug("remove queue %d / %d %d\n", index);
    #endif
    queue->queue_size--;
    if (index == queue->queue_tail_index) {
        #ifdef DEBUG_QUEUE
        debug(" update tail index: %d -> %d\n", queue->queue_tail_index, queue->queue_pool[index].prev_index);
        #endif
        queue->queue_tail_index = queue->queue_pool[index].prev_index;
    }
    if (index == queue->queue_head_index) {
        #ifdef DEBUG_QUEUE
        debug(" update head index: %d -> %d\n", queue->queue_head_index, queue->queue_pool[index].next_index);
        #endif
        queue->queue_head_index = queue->queue_pool[index].next_index;
    }

    if (queue->queue_pool[index].prev_index != -1) {
        #ifdef DEBUG_QUEUE
        debug(" update next index (%d): %d -> %d\n", queue->queue_pool[index].prev_index, queue->queue_pool[queue->queue_pool[index].prev_index].next_index, queue->queue_pool[index].next_index);
        #endif
        queue->queue_pool[queue->queue_pool[index].prev_index].next_index = queue->queue_pool[index].next_index;
    }
    if (queue->queue_pool[index].next_index != -1) {
        #ifdef DEBUG_QUEUE
        debug(" update prev index (%d): %d -> %d\n", queue->queue_pool[index].next_index, queue->queue_pool[queue->queue_pool[index].next_index].prev_index, queue->queue_pool[index].prev_index);
        #endif
        queue->queue_pool[queue->queue_pool[index].next_index].prev_index = queue->queue_pool[index].prev_index;
    }
}

void insert_queue(struct queue_t * queue, int after, int before, int index)
{
    #ifdef DEBUG_QUEUE
    debug("insert queue %d / %d / %d\n", after, index, before);
    #endif
    queue->queue_size++;
    if (queue->queue_head_index == -1 && queue->queue_tail_index == -1) {
        #ifdef DEBUG_QUEUE
        debug(" update head index: %d -> %d\n", queue->queue_head_index, index);
        #endif
        queue->queue_head_index = index;
        #ifdef DEBUG_QUEUE
        debug(" update tail index: %d -> %d\n", queue->queue_tail_index, index);
        #endif
        queue->queue_tail_index = index;
        queue->queue_pool[index].prev_index = -1;
        queue->queue_pool[index].next_index = -1;
    } else {
        if (after != -1) {
            #ifdef DEBUG_QUEUE
            debug(" update next index (%d): %d -> %d\n", index, -1, queue->queue_pool[after].next_index);
            #endif
            queue->queue_pool[index].next_index = queue->queue_pool[after].next_index;
            #ifdef DEBUG_QUEUE
            debug(" update next index (%d): %d -> %d\n", after, queue->queue_pool[after].next_index, index);
            #endif
            queue->queue_pool[after].next_index = index;
            #ifdef DEBUG_QUEUE
            debug(" update prev index (%d): %d -> %d\n", index, queue->queue_pool[after].prev_index, after);
            #endif
            queue->queue_pool[index].prev_index = queue->queue_tail_index;
            if (after == queue->queue_tail_index) {
                #ifdef DEBUG_QUEUE
                debug(" update tail index: %d -> %d\n", queue->queue_tail_index, index);
                #endif
                queue->queue_tail_index = index;
            } else {
                #ifdef DEBUG_QUEUE
                debug(" update prev index (%d): %d -> %d\n", queue->queue_pool[index].next_index, queue->queue_pool[queue->queue_pool[index].next_index].prev_index, index);
                #endif
                queue->queue_pool[queue->queue_pool[index].next_index].prev_index = index;
            }
        } else if (before != -1) {
            #ifdef DEBUG_QUEUE
            debug(" update prev index (%d): %d -> %d\n", index, -1, queue->queue_pool[before].prev_index);
            #endif
            queue->queue_pool[index].prev_index = queue->queue_pool[before].prev_index;
            #ifdef DEBUG_QUEUE
            debug(" update prev index (%d): %d -> %d\n", before, queue->queue_pool[before].prev_index, index);
            #endif
            queue->queue_pool[before].prev_index = index;
            #ifdef DEBUG_QUEUE
            debug(" update next index (%d): %d -> %d\n", index, queue->queue_pool[index].next_index, before);
            #endif
            queue->queue_pool[index].next_index = before;
            if (before == queue->queue_head_index) {
                #ifdef DEBUG_QUEUE
                debug(" update head index: %d -> %d\n", queue->queue_head_index, index);
                #endif
                queue->queue_head_index = index;
            } else {
                #ifdef DEBUG_QUEUE
                debug(" update next index (%d): %d -> %d\n", queue->queue_pool[index].prev_index, queue->queue_pool[queue->queue_pool[index].prev_index].next_index, index);
                #endif
                queue->queue_pool[queue->queue_pool[index].prev_index].next_index = index;
            }
        }
    }
}

struct context_t {
    char line[102];
    int line_length;
    struct queue_t queue;
};
struct context_t context;

char stdin_buffer[128];

int running = 1;

void solve(struct context_t * ctx)
{
    int result = 1;
    if (ctx->line[0] == '.' && ctx->line[1] == 0) {
        running = 0;
        return;
    }

    for (int l = 0; l < ctx->line_length; l++) {
        if (ctx->line[l] == '(') {
            ctx->queue.queue_pool[l].op = ctx->line[l];
            insert_queue(&ctx->queue, ctx->queue.queue_tail_index, -1, l);
        } else if (ctx->line[l] == '[') {
            ctx->queue.queue_pool[l].op = ctx->line[l];
            insert_queue(&ctx->queue, ctx->queue.queue_tail_index, -1, l);
        } else if (ctx->line[l] == ')') {
            if (ctx->queue.queue_size == 0 || ctx->queue.queue_pool[ctx->queue.queue_tail_index].op != '(') {
                result = 0;
                break;
            }
            remove_queue(&ctx->queue, ctx->queue.queue_tail_index);
        } else if (ctx->line[l] == ']') {
            if (ctx->queue.queue_size == 0 || ctx->queue.queue_pool[ctx->queue.queue_tail_index].op != '[') {
                result = 0;
                break;
            }
            remove_queue(&ctx->queue, ctx->queue.queue_tail_index);
        } else if (ctx->line[l] == '.') {
            break;
        }
    }
    if (ctx->queue.queue_size != 0) {
        result = 0;
    }
    printf("%s\n", result ? "yes":"no");
}

int main(int argc, char ** argv)
{
    memset(&context, 0, sizeof(struct context_t));
    memset(&context.queue, -1, sizeof(context.queue));
    context.queue.queue_size = 0;
    while (running) {
        if (fgets(stdin_buffer, sizeof(stdin_buffer) - 1, stdin) == 0) {
            solve(&context);
            memset(&context, 0, sizeof(struct context_t));
            memset(&context.queue, -1, sizeof(context.queue));
            context.queue.queue_size = 0;
        }
        for (int l = 0; l < strlen(stdin_buffer); l++) {
            if (stdin_buffer[l] == '\n') {
                solve(&context);
                memset(&context, 0, sizeof(struct context_t));
                memset(&context.queue, -1, sizeof(context.queue));
                context.queue.queue_size = 0;
            } else {
                context.line[context.line_length++] = stdin_buffer[l];
            }
        }
    }
    return 0;
}
