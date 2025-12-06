#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t getFileSize(const char *filepath)
{
  size_t num_lines = 0;
  int c;
  FILE *fp = fopen(filepath, "r");

  while ((c = fgetc(fp)) != EOF)
  {
    if (c == '\n')
    {
      num_lines++;
    }
  }
  fclose(fp);
  return num_lines;
}

int *loadTurns(const char *filepath, size_t *out_count)
{
  *out_count = getFileSize(filepath);

  FILE *fp = fopen(filepath, "r");

  int *values = malloc(*out_count * sizeof(int));
  char *buffer = NULL;
  size_t bufsize = 0;
  ssize_t len;

  for (size_t i = 0; i < *out_count; i++)
  {
    len = getline(&buffer, &bufsize, fp);

    if (len == 0)
    {
      values[i] = 0;
      continue;
    }

    char dir = buffer[0];                  // 'L' or 'R'
    long n = strtol(buffer + 1, NULL, 10); // num

    if (dir == 'L')
    {
      values[i] = (int)(-n);
    }
    else
    {
      values[i] = (int)n;
    }
  }

  free(buffer);
  fclose(fp);
  return values;
}

int main(int argc, char *argv[])
{
  size_t num_values = 0;
  int *values = loadTurns(argv[1], &num_values);

  for (size_t i = 0; i < 10; i++)
  {
    printf("%zu: %d\n", i, values[i]);
  }

  free(values);
  return 0;
}