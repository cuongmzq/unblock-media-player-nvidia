#include <stdio.h>
// #include <fcntl.h>
#include <windows.h>
#include <locale.h>

/*
1. Get parameters
2. Get working dir
3.

*/
int windows_systemW(wchar_t* cmd);

int main(int argc, const char **argv)
{
  setlocale(LC_ALL, "");
  // _setmode(_fileno(stdout), _O_U16TEXT);

  wchar_t* cmd = (wchar_t*)GetCommandLine();
  size_t len = wcslen(cmd);

  char* PREFIX = "start \"\" "; //required empty quotes to close console upon open

  char is_exe = 0;
  char offset = 0;

  char prefix_length = strlen(PREFIX);

  len = len + prefix_length + 1 + 1; //new_cmd length

  wchar_t* new_cmd = (wchar_t*)malloc(sizeof(TCHAR) * (len));
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
        wchar_t* current_character = cmd + i - prefix_length;
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

  _wsystem(new_cmd);

  return 0;
}