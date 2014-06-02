
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#include "../include/opone.h"

// An OP-1 has a directory structure as follows:
//
//   /album - Contains the 2 sides of the recording vinyl
//   /tape - Contains the 4 tracks
//   /(drum|synth) - All sounds
//   /(drum|synth)/user - Sounds mapped to keys 1-8
//   /(drum|synth)/<group> - User controlled group of settings (appears in menu)
//

const int true = 1;
const int false = 0;

extern int aiffc_read_header(const char *path);

int is_directory(char *path);
int has_opone_directories(char *path);

int opone_read(char *path, opone_device *device_out) {
  if (!has_opone_directories(path)) return 1;
  else {
    size_t synth_sound_len = strlen(path) + 18;
    char synth_sound[synth_sound_len];

    snprintf(synth_sound, synth_sound_len, "%s/synth/user/1.aif", path);

    aiffc_read_header(synth_sound);
    return 0;
  }
}

int has_opone_directories(char *path) {
  size_t path_len = strlen(path);
  size_t album_len = path_len + 7;
  size_t drum_len = path_len + 6;
  char album[album_len];
  char synth[album_len];
  char drum[drum_len];
  char tape[drum_len];

  snprintf(album, album_len, "%s/album", path);
  snprintf(synth, album_len, "%s/synth", path);
  snprintf(drum, drum_len, "%s/drum", path);
  snprintf(tape, drum_len, "%s/tape", path);

  return is_directory(album) &&
    is_directory(tape) &&
    is_directory(synth) &&
    is_directory(drum);
}

int is_directory(char *path) {
  DIR *directory = opendir(path);
  int is_dir = directory != NULL;

  printf("%s is directory? %s [%p] %d\n", path, is_dir ? "true" : "false", directory, errno);

  if (is_dir) { 
    closedir(directory);
  }

  return is_dir;
}
