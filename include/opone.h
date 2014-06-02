//
// libopone Public API
//

// Data Structures
//

typedef struct {
  char *something;
} opone_device;



// Functions
//

// Read all metadata from a mounted OP-1, this will be
// returned through the modification of the device_out
// pointer
int opone_read(char *path, opone_device *device_out);

