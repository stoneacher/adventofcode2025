#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIAL_POSITION_START 50

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

int calculate_secret_password(int *values, size_t num_values)
{
  int dial_pos = DIAL_POSITION_START;
  size_t zero_count = 0;

  for (size_t i = 0; i < num_values; i++)
  {
    if (values[i] == 0)
    {
      continue;
    }
    int step = (values[i] > 0) ? 1 : -1;
    int steps = values[i] > 0 ? values[i] : -values[i];

    for (int s = 0; s < steps; s++)
    {
      dial_pos += step;

      if (dial_pos >= 100)
        dial_pos -= 100;
      else if (dial_pos < 0)
        dial_pos += 100;

      if (dial_pos == 0)
        zero_count++;
    }
  }
  return zero_count;
}

int main(int argc, char *argv[])
{
  size_t num_values = 0;
  int *values = loadTurns(argv[1], &num_values);
  int pw = calculate_secret_password(values, num_values);
  printf("Secret pw: %d\n", pw);
  free(values);
  return 0;
}