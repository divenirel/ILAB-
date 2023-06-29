#include "funcs.h"

int main(int argc, char* argv[])
{
    int check = check_input (argv, argc);
    if (check == INP_FILE_ERR)
    {
        printf ("Input file address Error");
        return 0;
    }
    if (check == OUTP_FILE_ERR)
    {
        printf ("Output file address Error");
        return 0;
    }

    FILE* file_stream = fopen (argv[1], "r");
    if (file_stream == NULL)
    {
        printf("File stream error!");
        return 0;
    }
    freopen(argv[2], "w", stdout);
    int correct_check = DEFAULT;
    size_t buffer_size = scanf_file_size(file_stream);// ftell, long long >> size_t

    char* buffer = buffer_init (buffer_size);
    if (buffer == NULL)
    {
        printf("Buffer memory Error");
        return 0;//return 0 - завершилось без ошибок, можно возвращать коды ошибок
                  //на гитхабе сделать файл с кодами ошибок и значениями
    }

    int buffer_string_counter = read_buffer(file_stream, buffer, &buffer_size);
    if (buffer_string_counter == INCORRECT)
    {
        printf ("Incorrect buffer read");
        return 0;
    }
    Onegin* lines = struct_Onegin_init (buffer_string_counter);
    if (lines == NULL)
    {
        printf("Struct Onegin memory error");
        return 0;
    }

    int string_number = 0;
    int buff_char_number = 0;

    correct_check = scanf_all_strings (lines, &string_number, &buff_char_number, buffer, buffer_size);

    sort_strings_alphabet (lines, &string_number);
    printf_all_strings (lines, &string_number);

    sort_strings_alphabet_reverse (lines, &string_number);
    printf_all_strings (lines, &string_number);

    printf_first_variant (&buff_char_number, buffer, buffer_size);


    fclose(file_stream);

    free (buffer);
    free (lines);

    return 0;
}
