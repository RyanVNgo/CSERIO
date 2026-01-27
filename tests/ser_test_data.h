
#ifndef SER_TEST_DATA
#define SER_TEST_DATA

#include <stdint.h>

#include "../cserio.h"

typedef struct __attribute__((__packed__)) DummySERFile {
  char file_id[14];
  int32_t lu_id;
  int32_t color_id;
  int32_t little_endian;
  int32_t image_width;
  int32_t image_height;
  int32_t pixel_depth_per_plane;
  int32_t frame_count;
  char observer[OBSERVER_LEN];
  char instrument[INSTRUMENT_LEN];
  char telescope[TELESCOPE_LEN];
  int64_t date_time;
  int64_t date_time_utc;
} DummySERFile;

static DummySERFile test_data = {
  "LUCAM_RECORDER",
  0,
  0,
  0,
  50,
  50,
  1,
  0,
  "test_observer",
  "test_instrument",
  "test_telescope",
  -1, 
  0
};

static serfile* test_ser;

#endif

