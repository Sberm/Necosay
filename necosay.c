#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define PADDING 3
#define LEFT_LIMIT 24
#define TWO_LINES 2

struct vec {
    size_t size;
    size_t head;
    void *raw;
};

char const tab2space[] = "        "; /* 8 spaces and \0 */
size_t const tab2space_len = sizeof(tab2space) - 1;

char const bubble_left[] =
"  o"    "\n"
"   o"   "\n"
"     o" "\n";

char const bubble_right[] =
"                        o"  "\n"
"                       o"  "\n"
"                     o"  "\n";

char const cat[] =
"        /\\      /\\"      "\n"
"      -/--\\----/--\\-"    "\n"
"     /  /\\      /\\  \\"  "\n"
"    /  (())    (())  \\"   "\n"
"    \\   \\/      \\/   /" "\n"
"     \\    (_/\\_)    /"   "\n"
"      --------------"      "\n"
;

int print_neco(struct vec * restrict const vec, const size_t line_max)
{
    const int target_len = line_max + PADDING * 2 + TWO_LINES;
    char * str = NULL;

    if (!vec) {
        printf("empty vector\n");
        return -1;
    }

    str = vec->raw;

    for (int i = 0; i < target_len; i++)
        printf("=");
    printf("\n");

    size_t idx = 0;
    while (str[idx]) {
        size_t cur_len = 0;

        printf("|");
        cur_len += TWO_LINES/2;

        for (int i = 0; i < PADDING; i++)
            printf(" ");
        cur_len += PADDING;

        for (; str[idx]; ++idx) {
            if (str[idx] == '\t') {
                printf("%s", tab2space);
                cur_len += tab2space_len;
            } else if (str[idx] == '\n') {
                ++idx;
                break;
            } else {
                printf("%c", str[idx]);
                ++cur_len;
            }
        }
        for (size_t i = 0; (int)i < (int)target_len - (int)cur_len - TWO_LINES/2; i++)
            printf(" ");
        printf("|\n");
    }

    for (int i = 0; i < target_len; i++)
        printf("=");
    printf("\n");

    if (line_max > LEFT_LIMIT)
        printf("%s", bubble_right);
    else
        printf("%s", bubble_left);
    printf("%s", cat);
    return 0;
}

/* off-line because we need the length of the longest line */
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
    ((char *)vec->raw)[vec->head] = 0; // null term
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
    assert(tab2space_len > 0);

    if (argc > 1) {
        vec.raw = argv[1];
        print_neco(&vec, strlen(argv[1]));
    } else {
        size_t line_max = 0;
        char *line = NULL;
        size_t line_cap = 0;

        init(&vec);

        while (getline(&line, &line_cap, stdin) > 0) {
            size_t i = 0;
            size_t cvtd_len = 0; /* length after converted tab to space */

            for (; line[i]; i++) {
                if (line[i] == '\t') {
                    /* replace 1 tab with tab2space spaces */
                    cvtd_len += tab2space_len - 1;
                }
            }
            cvtd_len += i;
            if (i > 0 && line[i - 1] == '\n') {
                assert(cvtd_len > 0);
                cvtd_len -= 1;
            }
            copy(&vec, line, i);
            if (line_max < cvtd_len)
                line_max = cvtd_len;
        }
        print_neco(&vec, line_max);
        free(line);
    }
    return 0;
}
