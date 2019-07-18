#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef int (*letter_handler_t)(char *buf, size_t buflen, char letter, intptr_t data);

#define IP (intptr_t)

struct Lower
{
  int apple;
  int banana;
  int cherry;
};

struct Upper
{
  char *xebu;
  char *yak;
  char *zebra;
};

struct Callback
{
  char letter;
  letter_handler_t callback;
  intptr_t data;
};

int lower_handler(char *buf, size_t buflen, char letter, intptr_t data)
{
  if (!buf || (buflen == 0) || (data == 0))
    return -1;

  struct Lower *l = (struct Lower *) data;
  int rc = -1;

  switch (letter)
  {
    case 'a':
      rc = snprintf(buf, buflen, "apple=%d", l->apple);
      break;
    case 'b':
      rc = snprintf(buf, buflen, "banana=%d", l->banana);
      break;
    case 'c':
      rc = snprintf(buf, buflen, "cherry=%d", l->cherry);
      break;
  }

  return rc;
}

int upper_handler(char *buf, size_t buflen, char letter, intptr_t data)
{
  if (!buf || (buflen == 0) || (data == 0))
    return -1;

  struct Upper *u = (struct Upper *) data;
  int rc = -1;

  switch (letter)
  {
    case 'X':
      rc = snprintf(buf, buflen, "%s xebu", u->xebu);
      break;
    case 'Y':
      rc = snprintf(buf, buflen, "%s yak", u->yak);
      break;
    case 'Z':
      rc = snprintf(buf, buflen, "%s zebra", u->zebra);
      break;
  }

  return rc;
}

int expando(char *buf, size_t buflen, const char *fmt, struct Callback cb[])
{
  if (!buf || !fmt || !cb)
    return -1;

  size_t index = 0;

  for (; (fmt[0] != '\0') && (index < buflen); fmt++)
  {
    if (fmt[0] != '%')
    {
      buf[index++] = fmt[0];
      buflen--;
      continue;
    }

    fmt++;
    char letter = fmt[0];

    bool found = false;
    for (size_t i = 0; cb[i].callback; i++)
    {
      if (letter != cb[i].letter)
        continue;

      int rc = cb[i].callback(buf + index, buflen - index, letter, cb[i].data);
      if (rc >= 0)
      {
        index += rc;
        found = true;
        break;
      }
    }

    if (!found)
    {
      buf[index++] = '%';
      buf[index++] = letter;
    }
  }

  buf[index] = '\0';
  return 0;
}

int main(int argc, char *argv[])
{
  if (argc != 2)
    return 1;

  printf("%s\n", argv[1]);

  struct Lower l = { 12, 34, 56 };
  struct Upper u = { "happy", "jolly", "lucky" };

  struct Callback cb[] = {
    { 'a', lower_handler, IP & l },
    { 'b', lower_handler, IP & l },
    { 'c', lower_handler, IP & l },
    { 'X', upper_handler, IP & u },
    { 'Y', upper_handler, IP & u },
    { 'Z', upper_handler, IP & u },
    { '\0', NULL, 0 },
  };

  char buf[256] = { 0 };
  expando(buf, sizeof(buf), argv[1], cb);
  printf("%s\n", buf);
  return 0;
}
