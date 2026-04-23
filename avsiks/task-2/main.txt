#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <errno.h>
#include <ctype.h>

const char *COLORS[] = {"красный","оранжевый","желтый","зеленый","голубой","синий","фиолетовый"};
const int COLORS_COUNT = 7;
const int COORD_MIN = -100;
const int COORD_MAX = 100;
const int R_MIN = 1;
const int R_MAX = 50;
const int RECT_MIN_SIZE = 1;
const int RECT_MAX_SIZE = 100;

typedef enum {
    FIG_CIRCLE,
    FIG_RECTANGLE,
    FIG_TRIANGLE
} FigureType;

typedef struct {
    int x, y, r;
} Circle;

typedef struct {
    int x1, y1, x2, y2;
} RectangleF;

typedef struct {
    int x1, y1, x2, y2, x3, y3;
} TriangleF;

typedef struct {
    FigureType type;
    char *color;
    union {
        Circle c;
        RectangleF r;
        TriangleF t;
    } u;
} Figure;

static int rand_between(int a, int b) {
    return a + rand() % (b - a + 1);
}

static const char *random_color(void) {
    return COLORS[rand_between(0, COLORS_COUNT - 1)];
}

static char *strdup_local(const char *s) {
    if (!s) return NULL;
    size_t n = strlen(s);
    char *p = (char*)malloc(n + 1);
    if (!p) { perror("malloc"); exit(1); }
    memcpy(p, s, n + 1);
    return p;
}

static char *trim_copy(const char *s) {
    if (!s) return strdup_local("");
    const char *start = s;
    while (*start && isspace((unsigned char)*start)) start++;
    const char *end = s + strlen(s) - 1;
    while (end >= start && isspace((unsigned char)*end)) end--;
    size_t len = (end >= start) ? (size_t)(end - start + 1) : 0;
    char *out = (char*)malloc(len + 1);
    if (!out) { perror("malloc"); exit(1); }
    if (len) memcpy(out, start, len);
    out[len] = '\0';
    return out;
}

static char *gen_circle_line(void) {
    int x = rand_between(COORD_MIN, COORD_MAX);
    int y = rand_between(COORD_MIN, COORD_MAX);
    int r = rand_between(R_MIN, R_MAX);
    char *buf = (char*)malloc(128);
    if (!buf) { perror("malloc"); exit(1); }
    snprintf(buf, 128, "круг %d %d %d %s", x, y, r, random_color());
    return buf;
}

static char *gen_rectangle_line(void) {
    int x1 = rand_between(COORD_MIN, COORD_MAX);
    int y1 = rand_between(COORD_MIN, COORD_MAX);
    int w = rand_between(RECT_MIN_SIZE, RECT_MAX_SIZE);
    int h = rand_between(RECT_MIN_SIZE, RECT_MAX_SIZE);
    int x2 = x1 + (rand() % 2 ? w : -w);
    int y2 = y1 + (rand() % 2 ? h : -h);
    char *buf = (char*)malloc(128);
    if (!buf) { perror("malloc"); exit(1); }
    snprintf(buf, 128, "прямоугольник %d %d %d %d %s", x1, y1, x2, y2, random_color());
    return buf;
}

static long triangle_area_raw_long(int x1,int y1,int x2,int y2,int x3,int y3) {
    return (long)x1*(y2-y3) + (long)x2*(y3-y1) + (long)x3*(y1-y2);
}

static char *gen_triangle_line(void) {
    while (1) {
        int x1 = rand_between(COORD_MIN, COORD_MAX);
        int y1 = rand_between(COORD_MIN, COORD_MAX);
        int x2 = rand_between(COORD_MIN, COORD_MAX);
        int y2 = rand_between(COORD_MIN, COORD_MAX);
        int x3 = rand_between(COORD_MIN, COORD_MAX);
        int y3 = rand_between(COORD_MIN, COORD_MAX);
        if (triangle_area_raw_long(x1,y1,x2,y2,x3,y3) != 0) {
            char *buf = (char*)malloc(256);
            if (!buf) { perror("malloc"); exit(1); }
            snprintf(buf, 256, "треугольник %d %d %d %d %d %d %s",
                     x1,y1,x2,y2,x3,y3, random_color());
            return buf;
        }
    }
}

static char *gen_line(void) {
    int t = rand() % 3;
    if (t == 0) return gen_circle_line();
    if (t == 1) return gen_rectangle_line();
    return gen_triangle_line();
}

void write_file(const char *filename, int n) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        fprintf(stderr, "Не удалось создать %s: %s\n", filename, strerror(errno));
        return;
    }
    for (int i = 0; i < n; ++i) {
        char *line = gen_line();
        fprintf(f, "%s\n", line);
        free(line);
    }
    fclose(f);
    printf("Создан %s (%d строк)\n", filename, n);
}

Figure *parse_figure(const char *line_in) {
    if (!line_in) return NULL;
    char *line = trim_copy(line_in);

    char *tokens[16];
    int tc = 0;
    char *p = line;
    while (*p && tc < 16) {
        while (*p && isspace((unsigned char)*p)) p++;
        if (!*p) break;
        char *start = p;
        while (*p && !isspace((unsigned char)*p)) p++;
        size_t len = p - start;
        tokens[tc] = (char*)malloc(len + 1);
        if (!tokens[tc]) { perror("malloc"); exit(1); }
        memcpy(tokens[tc], start, len);
        tokens[tc][len] = '\0';
        tc++;
    }

    if (tc == 0) {
        free(line);
        return NULL;
    }

    Figure *f = (Figure*)malloc(sizeof(Figure));
    if (!f) { perror("malloc"); exit(1); }

    char *type = tokens[0];
    char *color = tokens[tc - 1];
    f->color = strdup_local(color);

    if (strcmp(type, "круг") == 0 && tc >= 5) {
        f->type = FIG_CIRCLE;
        f->u.c.x = atoi(tokens[1]);
        f->u.c.y = atoi(tokens[2]);
        f->u.c.r = atoi(tokens[3]);
    } else if (strcmp(type, "прямоугольник") == 0 && tc >= 6) {
        f->type = FIG_RECTANGLE;
        f->u.r.x1 = atoi(tokens[1]);
        f->u.r.y1 = atoi(tokens[2]);
        f->u.r.x2 = atoi(tokens[3]);
        f->u.r.y2 = atoi(tokens[4]);
    } else if (strcmp(type, "треугольник") == 0 && tc >= 8) {
        f->type = FIG_TRIANGLE;
        f->u.t.x1 = atoi(tokens[1]);
        f->u.t.y1 = atoi(tokens[2]);
        f->u.t.x2 = atoi(tokens[3]);
        f->u.t.y2 = atoi(tokens[4]);
        f->u.t.x3 = atoi(tokens[5]);
        f->u.t.y3 = atoi(tokens[6]);
    } else {
        free(f->color);
        free(f);
        f = NULL;
    }

    for (int i = 0; i < tc; ++i) free(tokens[i]);
    free(line);
    return f;
}

static double dist_d(int x1,int y1,int x2,int y2) {
    double dx = (double)(x2 - x1);
    double dy = (double)(y2 - y1);
    return sqrt(dx*dx + dy*dy);
}

double figure_perimeter(const Figure *f) {
    if (!f) return 0.0;
    if (f->type == FIG_CIRCLE) {
        return 2.0 * M_PI * (double)f->u.c.r;
    } else if (f->type == FIG_RECTANGLE) {
        double w = fabs((double)f->u.r.x2 - (double)f->u.r.x1);
        double h = fabs((double)f->u.r.y2 - (double)f->u.r.y1);
        return 2.0 * (w + h);
    } else {
        double a = dist_d(f->u.t.x1,f->u.t.y1, f->u.t.x2,f->u.t.y2);
        double b = dist_d(f->u.t.x2,f->u.t.y2, f->u.t.x3,f->u.t.y3);
        double c = dist_d(f->u.t.x1,f->u.t.y1, f->u.t.x3,f->u.t.y3);
        return a + b + c;
    }
}

double figure_area(const Figure *f) {
    if (!f) return 0.0;
    if (f->type == FIG_CIRCLE) {
        return M_PI * (double)f->u.c.r * (double)f->u.c.r;
    } else if (f->type == FIG_RECTANGLE) {
        double w = fabs((double)f->u.r.x2 - (double)f->u.r.x1);
        double h = fabs((double)f->u.r.y2 - (double)f->u.r.y1);
        return w * h;
    } else {
        double a = dist_d(f->u.t.x1,f->u.t.y1, f->u.t.x2,f->u.t.y2);
        double b = dist_d(f->u.t.x2,f->u.t.y2, f->u.t.x3,f->u.t.y3);
        double c = dist_d(f->u.t.x1,f->u.t.y1, f->u.t.x3,f->u.t.y3);
        double p = (a + b + c) / 2.0;
        double val = p * (p - a) * (p - b) * (p - c);
        return val > 0.0 ? sqrt(val) : 0.0;
    }
}

char *figure_info_str(const Figure *f) {
    char *buf = (char*)malloc(256);
    if (!buf) { perror("malloc"); exit(1); }
    if (f->type == FIG_CIRCLE) {
        snprintf(buf, 256, "круг: центр=(%d,%d), r=%d, цвет=%s",
                 f->u.c.x, f->u.c.y, f->u.c.r, f->color);
    } else if (f->type == FIG_RECTANGLE) {
        snprintf(buf, 256, "прямоугольник: (%d,%d)-(%d,%d), цвет=%s",
                 f->u.r.x1, f->u.r.y1, f->u.r.x2, f->u.r.y2, f->color);
    } else {
        snprintf(buf, 256, "треугольник: (%d,%d),(%d,%d),(%d,%d), цвет=%s",
                 f->u.t.x1, f->u.t.y1, f->u.t.x2, f->u.t.y2, f->u.t.x3, f->u.t.y3, f->color);
    }
    return buf;
}

void shell_sort_figures(Figure **arr, int n) {
    int gap = n / 2;
    while (gap > 0) {
        for (int i = gap; i < n; ++i) {
            Figure *temp = arr[i];
            double temp_p = figure_perimeter(temp);
            int j = i;
            while (j >= gap && figure_perimeter(arr[j-gap]) > temp_p) {
                arr[j] = arr[j-gap];
                j -= gap;
            }
            arr[j] = temp;
        }
        gap /= 2;
    }
}

void count_file(const char *filename, int *lines, long *chars) {
    *lines = 0;
    *chars = 0;
    FILE *f = fopen(filename, "r");
    if (!f) {
        return;
    }
    int c;
    int prev_newline = 1;
    while ((c = fgetc(f)) != EOF) {
        (*chars)++;
        if (c == '\n') {
            (*lines)++;
            prev_newline = 1;
        } else prev_newline = 0;
    }
    if (!prev_newline && *chars > 0) (*lines)++;
    fclose(f);
}

double timespec_to_ms_diff(struct timespec start, struct timespec end) {
    long sec = end.tv_sec - start.tv_sec;
    long nsec = end.tv_nsec - start.tv_nsec;
    return (double)sec * 1000.0 + (double)nsec / 1e6;
}

void process_file(const char *input_file, const char *output_file) {
    struct timespec tstart, tend;
    clock_gettime(CLOCK_MONOTONIC, &tstart);

    FILE *fin = fopen(input_file, "r");
    if (!fin) {
        fprintf(stderr, "Не удалось открыть %s: %s\n", input_file, strerror(errno));
        return;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char **lines = NULL;
    int lines_count = 0;

    while ((read = getline(&line, &len, fin)) != -1) {
        if (read > 0 && line[read-1] == '\n') line[read-1] = '\0';
        char *dup = strdup_local(line);
        char **tmp = (char**)realloc(lines, (lines_count + 1) * sizeof(char*));
        if (!tmp) { perror("realloc"); exit(1); }
        lines = tmp;
        lines[lines_count++] = dup;
    }
    free(line);
    fclose(fin);

    Figure **figs = NULL;
    int figs_count = 0;
    for (int i = 0; i < lines_count; ++i) {
        Figure *f = parse_figure(lines[i]);
        if (f) {
            Figure **tmp = (Figure**)realloc(figs, (figs_count + 1) * sizeof(Figure*));
            if (!tmp) { perror("realloc"); exit(1); }
            figs = tmp;
            figs[figs_count++] = f;
        } else {
        }
    }

    shell_sort_figures(figs, figs_count);

    clock_gettime(CLOCK_MONOTONIC, &tend);
    double duration_ms = timespec_to_ms_diff(tstart, tend);

    int main_lines = 0;
    long main_chars = 0;
    count_file("main.c", &main_lines, &main_chars);

    FILE *out = fopen(output_file, "w");
    if (!out) {
        fprintf(stderr, "Не удалось создать %s: %s\n", output_file, strerror(errno));
        for (int i = 0; i < lines_count; ++i) free(lines[i]);
        free(lines);
        for (int i = 0; i < figs_count; ++i) {
            free(figs[i]->color);
            free(figs[i]);
        }
        free(figs);
        return;
    }

    fprintf(out, "Исходные строки:\n");
    for (int i = 0; i < lines_count; ++i) fprintf(out, "%s\n", lines[i]);

    fprintf(out, "\nВсего фигур: %d\n", figs_count);
    fprintf(out, "Время обработки файла: %.6f мс\n", duration_ms);
    fprintf(out, "Файл main.c: строк=%d, символов=%ld\n", main_lines, main_chars);

    fprintf(out, "\nОтсортированные фигуры:\n");
    for (int i = 0; i < figs_count; ++i) {
        char *info = figure_info_str(figs[i]);
        double per = figure_perimeter(figs[i]);
        fprintf(out, "%s, периметр=%.6f\n", info, per);
        free(info);
    }

    fclose(out);
    printf("Создан %s\n", output_file);

    for (int i = 0; i < lines_count; ++i) free(lines[i]);
    free(lines);
    for (int i = 0; i < figs_count; ++i) {
        free(figs[i]->color);
        free(figs[i]);
    }
    free(figs);
}

int main(void) {
    srand((unsigned int)time(NULL));

    int sizes[] = {10, 100, 250, 500};
    const char *in_files[] = {"input_10.txt", "input_100.txt", "input_250.txt", "input_500.txt"};

    for (int i = 0; i < 4; ++i) {
        write_file(in_files[i], sizes[i]);
    }

    for (int i = 0; i < 4; ++i) {
        const char *in = in_files[i];
        const char *after_input = strstr(in, "input_");
        char outname[256];
        if (after_input) {
            after_input += 6;
            snprintf(outname, sizeof(outname), "output_%s", after_input);
        } else {
            snprintf(outname, sizeof(outname), "output_%s", in);
        }
        process_file(in, outname);
    }

    return 0;
}