#include <unistd.h>
// #include <stdio.h>
#include <windows.h>
// #include <string.h>
// #include <wchar.h>
#include <locale.h>
/*
1. Get parameters
2. Get working dir
3.

*/

int main(int argc, char **argv)
{
  setlocale(LC_ALL, "");
  

  LPTSTR cmd = (LPTSTR)GetCommandLine();
  size_t len = strlen(cmd);

  char* PREFIX = "start \"\" "; //required empty quotes to close console upon open

  char is_exe = 0;
  char offset = 0;

  char prefix_length = strlen(PREFIX);


  len = len + prefix_length + 1 + 1; //new_cmd length

  LPTSTR new_cmd = (LPTSTR)malloc(sizeof(TCHAR) * (len));
  *(new_cmd + len - 1) = L'\0';

  for (size_t i = 0; i < len; ++i)
  {
    if (i < prefix_length)
    {
      *(new_cmd + i) = *(PREFIX + i);
    }
    else
    {
      if (offset == 0) {
        LPTSTR current_character = cmd + i - prefix_length;
        is_exe =  *current_character == '.' && 
                  *(current_character + 1) == 'e' && 
                  *(current_character + 2) == 'x' && 
                  *(current_character + 3) == 'e';
      }
      
      if (is_exe)
      {
        *(new_cmd + i) = '_'; //insert "_" before ".exe" eg. mpc.exe to mpc_.exe
        offset = 1;
        is_exe = 0;
      }
      else
      {
        *(new_cmd + i) = *(cmd + i - prefix_length - offset);
      }
    }
  }

  system(new_cmd);
  // printf("(%s)", new_cmd);

  // getchar();

  return 0;
}