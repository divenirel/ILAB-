#ifndef FUNCS_H_INCLUDED
#define FUNCS_H_INCLUDED

#include <iostream>
#include <cstring>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
enum for_memory_alloc_check
{
    INCORRECT_MEMORY_ALLOC
};

enum for_correct_check
{
    CORRECT,
    INCORRECT = -1,
    DEFAULT,
};
//
enum for_file_check
{
    INP_FILE_ERR,
    OUTP_FILE_ERR
};

enum for_string_check
{
    STRING_END,
    END_OF_FILE,
};

enum compare_string
{
    FIRST_IS_BIGGER,
    SECOND_IS_BIGGER,
    EQUAL
};


enum for_letter_check
{
    NOT_A_LETTER,
    LETTER
};

struct buffer
{
    char* buffer;
    int buff_char_number;
    int string_number;
    size_t buff_size;
};

struct buffer buf;

struct Onegin
{
    char* str;
    size_t str_lenght;
};

Onegin*     struct_Onegin_init              (int buffer_string_counter);

char*       buffer_init                     (size_t buffer_size);

int         check_input                     (char** argv, int argc);

size_t      scanf_file_size                 (FILE* file_stream);

int         read_buffer                     (FILE* file_stream, char* buffer, size_t* buff_size);

int         trash_clean                     (char* str);

int         trash_clean_reverse             (char* str);

void        sort_strings_alphabet           (Onegin* stroka, int* string_number);

void        sort_strings_alphabet_reverse   (Onegin* stroka, int* string_number);

void        printf_first_variant            (int* nomer_elementa_v_buffere, char* buffer, size_t buff_size);

int         buffer_optimise                 (char* buffer, const size_t buff_size);

int         compare_two_strings             (Onegin* firstString, Onegin* secondString);

int         compare_two_strings_reverse     (char* firstString, char* secondString);

int         cunt_strings                    (char* buffer);

int         printf_first_variant_string     (int* nomer_elementa_v_buffere, char* buffer, size_t buff_size);

int         scanf_all_strings               (Onegin* lines, int* string_number, int* buff_char_number, char* buffer, size_t buff_size);

int         printf_all_strings              (Onegin* lines, int* string_number);

int         scanf_new_string                (Onegin* lines, int* string_number, int* buff_char_number, char* buffer, size_t buff_size);

int         comporator                      (const void* str1, const void* str2);

int         comporator_reverse              (const void* str1, const void* str2);

void        my_swap                         (void *dst, void *src, size_t len);

void        my_qsort                        (char* mas, int left, int right, size_t sz,int (*comp)(const void *, const void *));
//void        my_qsort                         (void *arr, size_t ssize, int left, int right, int (*comp)(const void *, const void *));



#endif // FUNCS_H_INCLUDED
