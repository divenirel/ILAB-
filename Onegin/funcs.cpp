#include "funcs.h"

int check_input (char** argv, int argc)
{
    for (int counter = 0 ; counter < argc ; counter++)
    {
        if (argv[counter] == NULL) //запустить от имени администратора
        {
            if (counter == 1)
            {

                //выводить в stderr fpintf ошибку, написать руководство действий при этой ошибке
                //сделать if, для обработки опции /? (--help -h (для линукса))
                //напечатать в stderr как пользоваться и выйти из программ .
                //новый код ошибки для запроса помощи
                //REQUEST_HELP

                return INP_FILE_ERR;
            }

            if (counter == 2)
            {
                return OUTP_FILE_ERR;
            }

        }
    }

    if (argc < 2)
    {
        return INP_FILE_ERR;
    }

    if (argc < 3)
    {
        return OUTP_FILE_ERR;
    }

}

char* buffer_init (size_t buffer_size)
{
    char* buffer = (char*) calloc(buffer_size + 1, sizeof(char));

    return buffer;
}

Onegin* struct_Onegin_init (int buffer_string_counter)
{
    Onegin* lines = (Onegin*) calloc(buffer_string_counter + 1, sizeof(Onegin));// "+ 1" для того, чтобы сделать пустую структуру, как '\0'
    if (lines == NULL)
    {
        return NULL;
    }
    return lines;
}

int read_buffer (FILE* file_stream, char* buffer, size_t* buff_size)
{
    *buff_size = fread (buffer, sizeof(char), *buff_size, file_stream);
    if (buffer == NULL)
    {
        printf ("Input error");
        return INCORRECT;
    }
    int buffer_string_counter = buffer_optimise (buffer, *buff_size);

    return buffer_string_counter;
}

int buffer_optimise (char* buffer, const size_t buff_size)
{
    int buffer_string_counter = 0;
    for (int counter = 0 ; counter < buff_size ; counter++)
    {
        if (buffer[counter] == '\n' && buffer[counter])
        {
            buffer[counter] = '\0';
            buffer_string_counter += 1;
        }
    }
    buffer_string_counter += 1;

    return buffer_string_counter;
}

int cunt_strings(char* buffer)
{
    int buffer_string_counter = 0;
    for (int cunt = 0 ; cunt < strlen(buffer) ; cunt++)
    {
        if (buffer[cunt] == '\0')buffer_string_counter += 1;
    }
    return buffer_string_counter;
}

size_t scanf_file_size (FILE* file_stream)
{
    fseek(file_stream, 0, SEEK_END);
    size_t size_of_file = ftell(file_stream);
    fseek(file_stream, 0, SEEK_SET);
    //rewind
    return size_of_file;
}

int scanf_new_string (Onegin* lines, int* string_number, int* buff_char_number, char* buffer, size_t buff_size)
{
    int tmp_string_len = 0;

    while (buffer[*buff_char_number] != '\0' )  //можно заменить на strlen
    {

        tmp_string_len += 1;
        *buff_char_number += 1;

    }

    if (tmp_string_len == 0)
    {
        *buff_char_number += 1;
        if (*buff_char_number >= buff_size)
            return END_OF_FILE;
        return STRING_END;
    }

    for (int i = tmp_string_len ; i > 0 ; i--)
    {
        if (isalpha(buffer[*buff_char_number - i]) == LETTER)
        {
            lines[*string_number].str = &buffer[*buff_char_number - tmp_string_len];//можно прибавлять к buffer, как к началу массива (указательная арифметика)
            lines[*string_number].str_lenght = tmp_string_len;                      //сдвигать начало на tmp_string_len или создать tmp_buffer
            *buff_char_number += 1; // lenght => length
            *string_number += 1;

            if (*buff_char_number >= buff_size)
                return END_OF_FILE;

            return CORRECT;
        }

    }
    *buff_char_number += 1;
    if (*buff_char_number >= buff_size)
        return END_OF_FILE;

    return CORRECT;
}

int scanf_all_strings (Onegin* lines, int* string_number, int* buff_char_number, char* buffer, size_t buff_size)
{
    int correct_check = DEFAULT;
    while (correct_check != END_OF_FILE)
    {

        correct_check = scanf_new_string (lines, string_number, buff_char_number, buffer, buff_size);

    }
}

int printf_all_strings (Onegin* lines, int* string_number)
{
    for (int neformal = 0 ; neformal < *string_number ; neformal++)
    {
        printf ("%s\n", lines[neformal].str);
    }
    printf ("-------------------------------------------------------------------\n");
}

int trash_clean (Onegin* line)
{
    int cunt = 0;
    while (isalpha(line->str[cunt]) == NOT_A_LETTER)
    {
        cunt++;
        if (cunt >= line->str_lenght - 1)
            break;
    }
    return cunt;
}

int trash_clean_reverse (Onegin* line)
{
    int cunt = 0;
    size_t str_len = line->str_lenght;
    while (isalpha (line->str[str_len - cunt - 1]) == NOT_A_LETTER)
    {
        cunt++;
        if (cunt >= line->str_lenght - 1)
            break;
    }
    return cunt;
}

int compare_two_strings (Onegin* firstString, Onegin* secondString)
{
    size_t first_str_len = firstString->str_lenght;
    size_t second_str_len = secondString->str_lenght;
    int char1 = NULL, char2 = NULL;
    int f_step = 0, s_step = 0;

    f_step = trash_clean(firstString);
    s_step = trash_clean(secondString);

    int limit_for_char_pos = std::min(first_str_len, second_str_len) - std::max(s_step, f_step);// посмотреть написание std::max и std::min!!!
    char* str1 = firstString->str;                                                               // написать свой
    char* str2 = secondString->str;
    for (int char_pos = 0 ; char_pos < limit_for_char_pos ; char_pos++) // можно написать без limit_for_char_pos, а считывать до '\0'!
    {
        char1 = char_pos + f_step;
        char2 = char_pos + s_step;

        if (tolower( str1[char1] ) > tolower( str2[char2]) )
            return FIRST_IS_BIGGER;
        if (tolower( str1[char1] ) < tolower( str2[char2]) )
            return SECOND_IS_BIGGER;
    }

    if (first_str_len > second_str_len)
        return FIRST_IS_BIGGER;

    else
        return SECOND_IS_BIGGER;
}

int compare_two_strings_reverse (Onegin* firstString, Onegin* secondString) // можно сделать один компоратор и trash_clean одной функцией
{                                                                           // путем передачи 3-го параметра.
    int char1 = NULL, char2 = NULL;
    int f_step = 0, s_step = 0;
    size_t first_str_len = firstString->str_lenght - 1;
    size_t second_str_len = secondString->str_lenght - 1;

    f_step = trash_clean_reverse(firstString);
    s_step = trash_clean_reverse(secondString);

    int limit_for_char_pos = std::min(first_str_len, second_str_len) - std::max(f_step, s_step);
    char* str1 = firstString->str;
    char* str2 = secondString->str;
    for (int char_pos = 0 ; char_pos < limit_for_char_pos ; char_pos++)
    {
        char1 = first_str_len - char_pos - f_step;
        char2 = second_str_len - char_pos - s_step;

        if (tolower( str1[char1] ) > tolower( str2[char2]) ) return FIRST_IS_BIGGER;
        if (tolower( str1[char1] ) < tolower( str2[char2]) ) return SECOND_IS_BIGGER;
    }

    if (first_str_len > second_str_len)
        return FIRST_IS_BIGGER;

    else
        return SECOND_IS_BIGGER;

}

int comporator (const void* str1, const void* str2)
{
    int result = compare_two_strings ( ((Onegin*)str1), ((Onegin*)str2));
    if (result == FIRST_IS_BIGGER)  return 1;  // можно возвращать не 1 0 -1, а любое число, главное сохранить знак!
    if (result == SECOND_IS_BIGGER) return -1; // иначе тратится время на сравнение в if.
    else                            return 0;

}

int comporator_reverse (const void* str1, const void* str2)
{
    int result = compare_two_strings_reverse ( ((Onegin*)str1), ((Onegin*)str2));
    if (result == FIRST_IS_BIGGER)  return 1;
    if (result == SECOND_IS_BIGGER) return -1;
    else                            return 0;

}

void sort_strings_alphabet (Onegin* stroka, int* nomer_stroki)
{   /*
    char* tmp_buffer = stroka[0].str;
    int tmp_counter = NULL;
    int lengh = NULL;
    for (int i = 0 ; i < *nomer_stroki; i++)
    {
        for (int j = 0 + i ; j < *nomer_stroki; j++)
        {
            if (compare_two_strings (stroka[j].str, tmp_buffer) == SECOND_IS_BIGGER)
            {
                tmp_buffer = stroka[j].str;
                tmp_counter = j;
            }
        }
    stroka[tmp_counter].str = stroka[i].str;
    stroka[i].str = tmp_buffer;
    tmp_buffer = stroka[i+1].str;
    lengh = stroka[tmp_counter].str_lenght;
    stroka[tmp_counter].str_lenght = stroka[i].str_lenght;
    stroka[i].str_lenght= lengh;
    }
    */
    my_qsort ((char*)stroka, 0, *nomer_stroki - 1, sizeof(Onegin), comporator);// нужно, чтобы параметры совпадали для my_qsort и для оригинального
    //qsort (stroka, *nomer_stroki, sizeof(Onegin), comporator);
    //comparator
}

void sort_strings_alphabet_reverse (Onegin* stroka, int* nomer_stroki)
{
    /*
    char* tmp_buffer = stroka[0].str;
    int tmp_counter = NULL;
    int lengh = NULL;
    for (int i = 0 ; i < *nomer_stroki; i++)
    {
        for (int j = 0 + i ; j < *nomer_stroki; j++)
        {
            if (compare_two_strings_reverse (stroka[j].str, tmp_buffer) == SECOND_IS_BIGGER)
            {
                tmp_buffer = stroka[j].str;
                tmp_counter = j;
            }
        }
    stroka[tmp_counter].str = stroka[i].str;
    stroka[i].str = tmp_buffer;
    tmp_buffer = stroka[i+1].str;
    lengh = stroka[tmp_counter].str_lenght;
    stroka[tmp_counter].str_lenght = stroka[i].str_lenght;
    stroka[i].str_lenght= lengh;
    }
    */
    qsort (stroka, *nomer_stroki, sizeof(Onegin), comporator_reverse);
}

void printf_first_variant (int* buff_char_number, char* buffer, size_t buff_size)
{
    *buff_char_number = 0;
    int correct_check = DEFAULT;
    while (correct_check != END_OF_FILE)
    {

        correct_check = printf_first_variant_string (buff_char_number, buffer, buff_size);

    }

}

int printf_first_variant_string (int* buff_char_number, char* buffer, size_t buff_size) //ГЌГҐ Г§Г ГЎГ»ГІГј ГЇГҐГ°ГҐГ¤Г ГІГј 0 Гў Г­Г Г·Г Г«ГҐ !
{
    int tmp_string_len = 0;
    char tmp_symbol = buffer[*buff_char_number];// можно переписать в 5 строчек.
    while (tmp_symbol != '\0' )
    {

        tmp_string_len += 1;
        *buff_char_number += 1;
        tmp_symbol = buffer[*buff_char_number];

    }

    if (tmp_string_len == 0)
        {
            *buff_char_number += 1;
                return STRING_END;
        }

    for (int i = tmp_string_len ; i > 0 ; i--)
    {
        if (isalpha(buffer[*buff_char_number - i]) == LETTER)
        {
            printf("%s\n", &buffer[*buff_char_number - tmp_string_len]);
            *buff_char_number += 1;
            if (*buff_char_number >= buff_size)
                return END_OF_FILE;

            return CORRECT;
        }

    }

    *buff_char_number += 1;

    if (*buff_char_number >= buff_size)
            return END_OF_FILE;

    return CORRECT;
}

void my_swap(void *first_param, void *second_param, size_t len)
{
    int cunt = 0;

    while (len >= 8)
    {
        int64_t tmp_param = *((int64_t*)second_param + cunt);
        *((int64_t*)second_param + cunt) = *((int64_t*)first_param + cunt);
        *((int64_t*)first_param + cunt) = tmp_param;
        cunt++;
        len -= 8;
    }

    cunt = cunt * 2;

    if (len >= 4)
    {
        int32_t tmp_param = *((int32_t*)second_param + cunt);
        *((int32_t*)second_param + cunt) = *((int32_t*)first_param + cunt);
        *((int32_t*)first_param + cunt) = tmp_param;
        len -= 4;
    }

    cunt = cunt * 2;

    if (len >= 2)
    {
        int16_t tmp_param = *((int16_t*)second_param + cunt);
        *((int16_t*)second_param + cunt) = *((int16_t*)first_param + cunt);
        *((int16_t*)first_param + cunt) = tmp_param;
        len -= 2;
    }

    cunt = cunt * 2;

    if (len >= 1)
    {
        char tmp_param = *((char *)second_param + cunt);
        *((char *)second_param + cunt) = *((char *)first_param + cunt);
        *((char *)first_param + cunt) = tmp_param;
    }

}

void my_qsort(char* mas, int left, int right, size_t sz, int (*comp)(const void*, const void*))
{
    int i = 0, last = 0;    // сделать функцию - обертку. (со стандартными прототипом qsort)

    if (left >= right)
        return;

    my_swap( ((char*)mas + sz * left), ((char*)mas + (left + right) / 2 * sz), sz);

    last = left;
    for (i = left + 1; i <= right; i++)
        if (comp( ((char*)mas + i * sz), ((char*)mas + sz * left) ) < 0)
            my_swap(( (char*)mas + sz * (++last) ), ((char*)mas + sz * i), sz);

    my_swap( ((char*)mas + sz * left), ((char*)mas + sz * last), sz);
    my_qsort(mas, left, last-1, sz, comp);
    my_qsort(mas, last+1, right, sz, comp);
}
