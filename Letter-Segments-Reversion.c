#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

int output_num = 0;

int max( int a, int b)
{
    if(a>b) return a;
    else return b;
}

bool Reflect(char str[])
{
    int len = strlen(str);
    bool bol = false;
    char *str_cpy = (char*)malloc(sizeof(char)*len+1);
    strcpy(str_cpy, str);
    for(int i = 0; i < len; i++){
        str[i] = str_cpy[len-i-1];
        if(str[i] != str_cpy[i]){
            bol = true;
        }
    }
    return bol;
}

void PrintStrForEnWordFirst( char str[10][35], char num[10][35], int len, int now_position, char output_str[40][35])
{
    if(now_position == len)
    {
        for(int i = 0; i < len; i++){
            strcat(output_str[output_num], str[i]);
            strcat(output_str[output_num], num[i]);
        }
        output_num++;
        return;
    }
    PrintStrForEnWordFirst(str, num, len, now_position+1, output_str);
    bool bol = Reflect(str[now_position]);
    if(bol){
        PrintStrForEnWordFirst(str, num, len, now_position+1, output_str);
    }

    return;
}

void PrintStrForNumberFirst( char str[10][35], char num[10][35], int len, int now_position, char output_str[40][35])
{
    if(now_position == len)
    {
        for(int i = 0; i < len; i++){
            strcat(output_str[output_num], num[i]);
            strcat(output_str[output_num], str[i]);
        }
        output_num++;
        return;
    }
    PrintStrForNumberFirst(str, num, len, now_position+1, output_str);
    bool bol = Reflect(str[now_position]);
    if(bol){
        PrintStrForNumberFirst(str, num, len, now_position+1, output_str);
    }

    return;
}

void SortString(char output[40][35], int output_num)
{
    char tmp[35] = {};
    for(int i = 0; i < output_num-1; i++) {
        for(int j = i+1; j < output_num; j++){
            if(strcmp(output[i], output[j]) > 0){
                strcpy(tmp, output[i]);
                strcpy(output[i], output[j]);
                strcpy(output[j], tmp);
            }
        }
    }
    return;
}

int main()
{
    char str[35], str_cpy[35] = {};
    fgets(str, sizeof(str), stdin );
    if(str[strlen(str)-1] == '\n'){
        str[strlen(str)-1] = '\0';
    }
    strcpy(str_cpy, str);

    char *str_token= strtok(str, "1234567890");
    int str_num = 0;
    char str_buffer[10][35] = {};
    while( str_token != NULL ){
        strcpy(str_buffer[str_num], str_token);
        if(str_buffer[str_num][strlen(str_buffer[str_num])-1] == '\n'){
            str_buffer[str_num][strlen(str_buffer[str_num])-1] = '\0';
        }
        str_num++;
        str_token = strtok(NULL, "1234567890");
    }
    char num_num = 0;
    char num_buffer[10][35] = {};
    char *num_token = strtok(str_cpy, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
    while( num_token != NULL ){
        strcpy(num_buffer[num_num], num_token);
        if(num_buffer[num_num][strlen(num_buffer[num_num])-1] == '\n'){
            num_buffer[num_num][strlen(num_buffer[num_num])-1] = '\0';
        }
        num_num++;
        num_token = strtok(NULL, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
    }

    int len = max(str_num, num_num);
    char output_str[40][35] = {};
    if( (65 <= str[0] && str[0] <= 90) || (97 <= str[0] && str[0] <= 122) ){
        PrintStrForEnWordFirst(str_buffer, num_buffer, len, 0, output_str);
    }
    else{
        PrintStrForNumberFirst(str_buffer, num_buffer, len, 0, output_str);
    }
    SortString(output_str, len*4);
    for(int i = 0; i < len*4; i++){
        if(output_str[i][0] == '\0'){
            continue;
        }
        puts(output_str[i]);
    }

    return 0;
}