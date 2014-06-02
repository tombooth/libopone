
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
  char id[4];
  int32_t size;
} Chunk;

typedef struct {
  char id[4];
  int32_t size;
  char form_type[4];
} FormChunk;

typedef struct {
  char id[4];
  int32_t size;
  char os_type[4];
  char data[];
} APPLChunk;

int32_t to_little_endian(int32_t num) {
  return ((num>>24)&0xff) |
          ((num<<8)&0xff0000) |
          ((num>>8)&0xff00) |
          ((num<<24)&0xff000000);
}

int aiffc_read_header(const char *path) {
  int fd = open(path, O_RDONLY);
  off_t file_offset = 0;
  FormChunk form_chunk;
  Chunk curr_chunk;

  printf("Reading aiffc file: %s\n", path);

  if (fd < 0) return 1;

  pread(fd, &form_chunk, sizeof(FormChunk), 0);
  file_offset += sizeof(FormChunk);

  while (pread(fd, &curr_chunk, sizeof(Chunk), file_offset) >= 0) {
    int32_t size = to_little_endian(curr_chunk.size);

    if (strcmp(curr_chunk.id, "SSND") == 0) break;
    else if (strcmp(curr_chunk.id, "APPL") == 0) {
      APPLChunk *appl_chunk = malloc(sizeof(Chunk) + size);
      pread(fd, appl_chunk, sizeof(Chunk) + size, file_offset);
      // strings are not null terminated so everything gets a bit wonky
      printf("%.4s: %.20s\n", appl_chunk->os_type, appl_chunk->data);
      free(appl_chunk);
    }

    file_offset += size + sizeof(Chunk);
  }

  close(fd);

  return 0;
}
