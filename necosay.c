#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define PADDING 3

struct vec {
    size_t size;
    size_t head;
    void *raw;
};

int print_neco(struct vec *vec, const size_t line_max)
{
    const int line_len = line_max + PADDING * 2 + 2;
    char *str = NULL;

    if (!vec) {
        printf("empty vector\n");
        return -1;
    }

    str = vec->raw;
    
    for (int i = 0; i < line_len; i++)
        printf("=");
    printf("\n");

    size_t idx = 0;
    while (str[idx]) {
        size_t cur_len = 0;

        printf("|");
        ++cur_len;

        for (int i = 0; i < PADDING; i++)
            printf(" ");
        cur_len += PADDING;

        for (; str[idx] && str[idx] != '\n'; ++idx) {
            printf("%c", str[idx]);
            ++cur_len;
        }
        if (str[idx] == '\n') // skip the new line
            ++idx;

        /* -1: the last | */
        for (int i = 0; i < (int)line_len - (int)cur_len - 1; i++)
            printf(" ");
        printf("|\n");
    }

    for (int i = 0; i < line_len; i++)
        printf("=");
    printf("\n");

    char bubble_left[] = 
"  o"    "\n"
"   o"   "\n"
"     o" "\n";

    char bubble_right[] = 
"                        o"  "\n"
"                       o"  "\n"
"                     o"  "\n";

    char cat[] = 
"        /\\      /\\"      "\n"
"      -/--\\----/--\\-"    "\n"
"     /  /\\      /\\  \\"  "\n"
"    /  (())    (())  \\"   "\n"
"    \\   \\/      \\/   /" "\n"
"     \\    (_/\\_)    /"   "\n"
"      --------------"      "\n"
;
    if (line_max > 24)
        printf("%s", bubble_right);
    else
        printf("%s", bubble_left);
    printf("%s", cat);
    return 0;
}

/* we need to hold the data */
void copy(struct vec *vec, void *src, size_t len)
{
    if (!vec) {
        printf("vec is empty\n");
        return;
    }
    while (vec->head + len + 1 > vec->size) {
        vec->size <<= 2;
        vec->raw = realloc(vec->raw, vec->size);
        if (!vec->raw) {
            printf("realloc failed\n");
            return;
        }
    }
    memcpy(vec->raw + vec->head, src, len);
    vec->head += len;

    assert(vec->head < vec->size);
    ((char *)vec->raw)[vec->head] = 0;
}

void free_vec(struct vec *vec)
{
    if (!vec) {
        printf("empty vector\n");
        return;
    }
    free(vec->raw);
}

#define VEC_MIN 16
void init(struct vec *vec)
{
    if (!vec) {
        printf("empty vector\n");
        return;
    }

    vec->raw = malloc(VEC_MIN);
    if (!vec->raw) {
        printf("malloc failed\n");
        return;
    }
    vec->size = VEC_MIN;
    vec->head = 0;
}

int main(int argc, char **argv)
{
    struct vec vec;
    memset(&vec, 0, sizeof(struct vec));
    init(&vec);
    if (argc > 1) {
        size_t str_len = strlen(argv[1]);

        vec.raw = malloc(str_len + 1);
        if (!vec.raw) {
            printf("malloc failed\n");
            return -1;
        }
        memcpy(vec.raw, argv[1], str_len);
        ((char *)vec.raw)[str_len] = 0; // null term
        print_neco(&vec, str_len);
        free_vec(&vec);
    } else {
        size_t line_max = 0;
        char *line = NULL;
        size_t line_cap = 0;

        while (getline(&line, &line_cap, stdin) > 0) {
            size_t cur_line_len = strlen(line);
            
            if (line_max < cur_line_len)
                line_max = cur_line_len;

            copy(&vec, line, cur_line_len);
        }
        print_neco(&vec, line_max);
        free_vec(&vec);
    }
    return 0;
}
