#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int str_len(const char* str){
    int i = 0;
    while (str[i]) ++i; // str[i] == *(str + i) == *(i + str) == i[str]
    return i;
}

char* str_cpy(char* str1, const char* str2){
    int i = 0;
    while (str2[i]) {
        str1[i++] = str2[i];
    }
    str1[i + 1] = '\0';
    return str1;
}

const char* str_chr(const char* str, const char symbol){
    int i = 0;
    while (str[i] && str[i] != symbol) ++i;
    if (i == strlen(str)) return NULL;
    return str + i;
}

int str_cmp(const char* str1, const char* str2){
    int raz = 0, i = 0;
    for (i = 0; str1[i] && !raz; ++i){
        raz = str1[i] - str2[i];
    }
    if (!str1[i])
        raz = str1[i] - str2[i];
    return raz;
}

char* str_cat(char* str1, const char* str2){
    int len_str1 = strlen(str1);
    int i = 0;
    for (i = 0; str2[i]; ++i) {
        str1[len_str1 + i] = str2[i];
    }
    str1[len_str1 + i] = '\0';
    return str1;
}

int my_puts(const char* str){
    if (str == NULL) return 0;
   
    while (*str) putchar(*str++);
    return 1;
}

char* strn_cpy(char* destptr, const char* srcptr, int num){
    int i = 0;
    while (srcptr[i] && i < num){
        destptr[i++] = srcptr[i];
    }
    if (i < num) destptr[i] = '\0';
    return destptr;
}

char* strn_cat (char* destination, const char* append, size_t num){
    int len_destination = str_len(destination);
    int i = 0;
    while (append[i] && i < num){
        destination[len_destination + i++] = append[i];
    }
    if (i < num)
        destination[len_destination + i] = '\0';
    return destination;
}

char *f_gets(char *str, int num, FILE *stream){
    if (stream == NULL) return NULL;
    int i = 0;
    char symbol = getc(stream);
    str[0] = symbol;
    while (i < num - 1 and symbol != EOF and symbol != '\n'){
        str[i] = symbol;
        symbol = getc(stream);
        ++i;
    }
    return str;
}

char* str_dup(const char *str){
    char* new_str = (char*) calloc(str_len(str) + 1, sizeof(char));
    int i = 0;
    while (str[i]){
        new_str[i] = str[i];
        ++i;
    }
    new_str[i] = '\0';
    return new_str;
}

size_t get_line (char **string, size_t *n, FILE *stream){
    size_t i = 0;
    char symbol = getc(stream);
    char* new_str = (char*) calloc(*n, sizeof(char));
    while (i < *n - 1 and symbol != EOF and symbol != '\n'){
        new_str[i] = symbol;
        symbol = getc(stream);
        ++i;
    }
    new_str[i] = '\0';
    *string = new_str;
    return i;
}

int test(void) {
    int errors = 0;
    if (strlen("bac") != str_len("bac") || strlen("") != str_len("") || str_len("aue") != strlen("aue")) {
        printf("Error in str_len function\n");
        errors++;
    }

    char str_cpy_test_my[100] = "", str_cpy_test_include[100] = "";
    if (!str_cpy(str_cpy_test_my, "bac")    || !strcpy(str_cpy_test_include, "bac")    || strcmp(str_cpy_test_my, str_cpy_test_include) != 0
    ||  !str_cpy(str_cpy_test_my, "aueeee") || !strcpy(str_cpy_test_include, "aueeee") || strcmp(str_cpy_test_my, str_cpy_test_include) != 0) {
        printf("Error in str_cpy function\n");
        errors++;
    }

    char* str_chr_test_my = "aufff", *str_chr_test_include = "aufff", *str_chr1_test_my = "abc", *str_chr1_test_include = "abc";
    if (str_chr(str_chr1_test_my, 'a') != strchr(str_chr1_test_include, 'a') || str_chr(str_chr1_test_my, 'r') != strchr(str_chr1_test_include, 'r') 
                                                                             || str_chr(str_chr_test_my, 'f') != strchr(str_chr_test_include, 'f')) {
        printf("Error in str_chr function %s %s\n", str_chr(str_chr1_test_my, 'a'), strchr(str_chr1_test_include, 'a'));
        errors++;
    }

    char str_cat_test_my[100] = "", str_cat_test_include[100] = "";
    if (!str_cat(str_cat_test_my, "bac") || !strcat(str_cat_test_include, "bac") || strcmp(str_cat_test_my, str_cat_test_include) != 0
     || !str_cat(str_cat_test_my, "isdfjisdfj") || !strcat(str_cat_test_include, "isdfjisdfj") || strcmp(str_cat_test_my, str_cat_test_include)) {
        printf("Error in str_cat function\n");
        errors++;
    }
    if (!(str_cmp("bac", "baca") < 0 && strcmp("bac", "baca") < 0) || !(str_cmp("abc", "rddfsa") < 0 && strcmp("abc", "rddfsa") < 0)) {
        printf("Error in str_cmp function %d %d\n", str_cmp("bac", "baca"), strcmp("bac", "baca"));
        errors++;
    }
    char* str_dup_test = "abcdef";
    if (strcmp(str_dup_test, str_dup(str_dup_test)) != 0) {
        printf("Error in str_dup function\n");
        errors++;
    }
    char my_fgets[50] = "", include_fgets[50] = "";
    if (!f_gets(my_fgets, 50, fopen("input.txt", "r")) && !fgets(include_fgets, 50, fopen("input.txt", "r")) && strcmp(my_fgets, include_fgets)) {
        printf("Error in f_gets function\n");
        errors++;
    }
    printf("%s\n", (errors ? "Errors" : "All accepted"));
    return 0;
}
//puts, strncpy, strncat, fgets, strdup, getline
int main(){
    test();
    size_t bufsize = 32;
    char* p = NULL;
    get_line(&p, &bufsize, fopen("input.txt", "r"));
    printf("%s\n", p);
    return 0;
}