
struct __AIFFC_Chunk {
  char id[4];
  struct __AIFFC_Chunk *next;
}
typedef struct __Chunk AIFFC_Chunk;

typedef struct {
  char id[4];
  AIFFC_Chunk *next;

  char form_type[4];
} AIFFC_FormChunk

typedef struct {
  char id[4];
  AIFFC_Chunk *next;

  uint32_t timestamp;
} AIFFC_FverChunk

/*
 * short numChannels; 
 * unsigned long numSampleFrames; 
 * short sampleSize; 
 * extended sampleRate; 
 * ID compressionType; 
 * pstring compressionName; 
 */
typedef struct {
  char id[4];
  AIFFC_Chunk *next;

  int16_t num_channels;
  uint32_t num_sample_frames;
  int16_t sample_size;
  long double sample_rate; // 80-bit extended precision float
  char compression_type[4];
  char *compression_name;
} AIFFC_CommChunk

typedef struct {
  char id[4];
  AIFFC_Chunk *next;

  char os_type[4];
  char *data;
} AIFFC_ApplChunk


int aiffc_read_header(const char *path, AIFFC_FormChunk *form_chunk);
