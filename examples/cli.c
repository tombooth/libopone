
#include <stdio.h>
#include <string.h>

#include "../include/opone.h"

int main(int argc, char *argv[]) {
  char path[] = "/Volumes/NO NAME";
  opone_device device;
  int err;

  err = opone_read(path, &device);
  if (err > 0) { printf("Error on read: %d\n", err); return 1; }

  return 0;
}
