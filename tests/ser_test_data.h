
#ifndef SER_TEST_DATA
#define SER_TEST_DATA

#include <stdint.h>

#include "../cserio.h"


#define TEST_TIMESTAMP_VALUE    0x08d126583cd43bb0

typedef struct SERHdrStructureNonPacked {
    char file_id[FILEID_LEN];
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
} SERHdrStructureNonPacked;

typedef struct __attribute__((__packed__)) SERHdrStructure {
    char file_id[FILEID_LEN];
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
} SERHdrStructure;

typedef struct __attribute__((__packed__)) SERTest3x50Structure {
    SERHdrStructure hdr;
    uint8_t data[3 * 50 * 50];
    int64_t trlr[3];
} SERTest3x50Structure;

static SERTest3x50Structure test_data_3x50 = {
    .hdr = {
        "LUCAM-RECORDER",
        0,
        BAYER_RGGB,
        1,
        50,
        50,
        8,
        3,
        "test_observer",
        "test_instrument",
        "test_telescope",
        TEST_TIMESTAMP_VALUE,
        TEST_TIMESTAMP_VALUE
    },
    .data = {},
    .trlr = {TEST_TIMESTAMP_VALUE, TEST_TIMESTAMP_VALUE, TEST_TIMESTAMP_VALUE}
};

static serfile* test_ser_3x50;

static const int key_map[HDR_UNIT_COUNT] = {
    FILEID_KEY              ,
    LUID_KEY                ,
    COLORID_KEY             ,
    LITTLEENDIAN_KEY        ,
    IMAGEWIDTH_KEY          ,
    IMAGEHEIGHT_KEY         ,
    PIXELDEPTHPERPLANE_KEY  ,
    FRAMECOUNT_KEY          ,
    OBSERVER_KEY            , 
    INSTRUMENT_KEY          , 
    TELESCOPE_KEY           , 
    DATETIME_KEY            ,
    DATETIMEUTC_KEY         
};

static const int len_map[HDR_UNIT_COUNT] = {
    FILEID_LEN              ,
    LUID_LEN                ,
    COLORID_LEN             ,
    LITTLEENDIAN_LEN        ,
    IMAGEWIDTH_LEN          ,
    IMAGEHEIGHT_LEN         ,
    PIXELDEPTHPERPLANE_LEN  ,
    FRAMECOUNT_LEN          ,
    OBSERVER_LEN            , 
    INSTRUMENT_LEN          , 
    TELESCOPE_LEN           , 
    DATETIME_LEN            ,
    DATETIMEUTC_LEN         
};


#endif

