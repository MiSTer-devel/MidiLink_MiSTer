int  ini_read_ini(char * fileName);
void ini_print_settings();
char ini_replace_char(char * str, int strLen, char old, char new);
char ini_process_key_value(char * key, char * value);
char ini_first_char(char * str, int len);
int  ini_split_line(char * str, int len, char * key, int keyLen, char * value, int valLen);
int  ini_read_loop (char * fileName, char * key, int keyLen, char * value, int valLen);