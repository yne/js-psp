#ifndef __MKVINFO_EBML_ID_H__
#define __MKVINFO_EBML_ID_H__

/* EBML version supported */
#define EBML_VERSION 1

/*
 * EBML element IDs. max. 32-bit.
 */

/* top-level master-IDs */
#define EBML_ID_HEADER                   0x1A45DFA3

/* IDs in the HEADER master */
#define EBML_ID_EBMLVERSION              0x4286
#define EBML_ID_EBMLREADVERSION          0x42F7
#define EBML_ID_EBMLMAXIDLENGTH          0x42F2
#define EBML_ID_EBMLMAXSIZELENGTH        0x42F3
#define EBML_ID_DOCTYPE                  0x4282
#define EBML_ID_DOCTYPEVERSION           0x4287
#define EBML_ID_DOCTYPEREADVERSION       0x4285

/* general EBML types */
#define EBML_ID_VOID                     0xEC

/* ID returned in error cases */
#define EBML_ID_INVALID                  0xFFFFFFFF


/*
 * Matroska element IDs. max. 32-bit.
 */

/* toplevel segment */
#define MATROSKA_ID_SEGMENT              0x18538067

/* matroska top-level master IDs */
#define MATROSKA_ID_INFO                 0x1549A966
#define MATROSKA_ID_TRACKS               0x1654AE6B
#define MATROSKA_ID_CUES                 0x1C53BB6B
#define MATROSKA_ID_TAGS                 0x1254C367
#define MATROSKA_ID_SEEKHEAD             0x114D9B74
#define MATROSKA_ID_ATTACHMENTS          0x1941A469
#define MATROSKA_ID_CHAPTERS             0x1043A770
#define MATROSKA_ID_CLUSTER              0x1F43B675

/* IDs in the info master */
#define MATROSKA_ID_TIMECODESCALE        0x2AD7B1
#define MATROSKA_ID_DURATION             0x4489
#define MATROSKA_ID_WRITINGAPP           0x5741
#define MATROSKA_ID_MUXINGAPP            0x4D80
#define MATROSKA_ID_DATEUTC              0x4461

/* ID in the tracks master */
#define MATROSKA_ID_TRACKENTRY           0xAE

/* IDs in the trackentry master */
#define MATROSKA_ID_TRACKNUMBER          0xD7
#define MATROSKA_ID_TRACKUID             0x73C5
#define MATROSKA_ID_TRACKTYPE            0x83
#define MATROSKA_ID_TRACKAUDIO           0xE1
#define MATROSKA_ID_TRACKVIDEO           0xE0
#define MATROSKA_ID_CODECID              0x86
#define MATROSKA_ID_CODECPRIVATE         0x63A2
#define MATROSKA_ID_CODECNAME            0x258688
#define MATROSKA_ID_CODECINFOURL         0x3B4040
#define MATROSKA_ID_CODECDOWNLOADURL     0x26B240
#define MATROSKA_ID_TRACKNAME            0x536E
#define MATROSKA_ID_TRACKLANGUAGE        0x22B59C
#define MATROSKA_ID_TRACKFLAGENABLED     0xB9
#define MATROSKA_ID_TRACKFLAGDEFAULT     0x88
#define MATROSKA_ID_TRACKFLAGLACING      0x9C
#define MATROSKA_ID_TRACKMINCACHE        0x6DE7
#define MATROSKA_ID_TRACKMAXCACHE        0x6DF8
#define MATROSKA_ID_TRACKDEFAULTDURATION 0x23E383
#define MATROSKA_ID_TRACKENCODINGS       0x6D80

/* IDs in the trackaudio master */
#define MATROSKA_ID_AUDIOSAMPLINGFREQ    0xB5
#define MATROSKA_ID_AUDIOBITDEPTH        0x6264
#define MATROSKA_ID_AUDIOCHANNELS        0x9F

/* IDs in the trackvideo master */
#define MATROSKA_ID_VIDEOFRAMERATE       0x2383E3
#define MATROSKA_ID_VIDEODISPLAYWIDTH    0x54B0
#define MATROSKA_ID_VIDEODISPLAYHEIGHT   0x54BA
#define MATROSKA_ID_VIDEOPIXELWIDTH      0xB0
#define MATROSKA_ID_VIDEOPIXELHEIGHT     0xBA
#define MATROSKA_ID_VIDEOFLAGINTERLACED  0x9A
#define MATROSKA_ID_VIDEOSTEREOMODE      0x53B9
#define MATROSKA_ID_VIDEODISPLAYUNIT     0x54B2
#define MATROSKA_ID_VIDEOASPECTRATIO     0x54B3
#define MATROSKA_ID_VIDEOCOLOURSPACE     0x2EB524
#define MATROSKA_ID_VIDEOGAMMA           0x2FB523

/* IDs in the trackencodings master */
#define MATROSKA_ID_CONTENTENCODING      0x6240
#define MATROSKA_ID_CONTENTENCODINGORDER 0x5031
#define MATROSKA_ID_CONTENTENCODINGSCOPE 0x5032
#define MATROSKA_ID_CONTENTENCODINGTYPE  0x5033
#define MATROSKA_ID_CONTENTCOMPRESSION   0x5034
#define MATROSKA_ID_CONTENTCOMPALGO      0x4254
#define MATROSKA_ID_CONTENTCOMPSETTINGS  0x4255

/* ID in the cues master */
#define MATROSKA_ID_POINTENTRY           0xBB

/* IDs in the pointentry master */
#define MATROSKA_ID_CUETIME              0xB3
#define MATROSKA_ID_CUETRACKPOSITION     0xB7

/* IDs in the cuetrackposition master */
#define MATROSKA_ID_CUETRACK             0xF7
#define MATROSKA_ID_CUECLUSTERPOSITION   0xF1
#define MATROSKA_ID_CUEBLOCKNUMBER       0x5378

/* IDs in the seekhead master */
#define MATROSKA_ID_SEEKENTRY            0x4DBB

/* IDs in the seekpoint master */
#define MATROSKA_ID_SEEKID               0x53AB
#define MATROSKA_ID_SEEKPOSITION         0x53AC

/* IDs in the chapters master */
#define MATROSKA_ID_EDITIONENTRY         0x45B9
#define MATROSKA_ID_CHAPTERATOM          0xB6
#define MATROSKA_ID_CHAPTERTIMESTART     0x91
#define MATROSKA_ID_CHAPTERTIMEEND       0x92
#define MATROSKA_ID_CHAPTERDISPLAY       0x80
#define MATROSKA_ID_CHAPSTRING           0x85

/* IDs in the cluster master */
#define MATROSKA_ID_CLUSTERTIMECODE      0xE7
#define MATROSKA_ID_BLOCKGROUP           0xA0

/* IDs in the blockgroup master */
#define MATROSKA_ID_BLOCKDURATION        0x9B
#define MATROSKA_ID_BLOCK                0xA1
#define MATROSKA_ID_SIMPLEBLOCK          0xA3
#define MATROSKA_ID_REFERENCEBLOCK       0xFB

/* IDs in the attachments master */
#define MATROSKA_ID_ATTACHEDFILE	 0x61A7
#define MATROSKA_ID_FILENAME		 0x466E
#define MATROSKA_ID_FILEMIMETYPE	 0x4660
#define MATROSKA_ID_FILEDATA		 0x465C
#define MATROSKA_ID_FILEUID		 0x46AE


#ifndef UINT64_MAX
#define UINT64_MAX 18446744073709551615ULL
#endif

#ifndef INT64_MAX
#define INT64_MAX 9223372036854775807LL
#endif

#define EBML_UINT_INVALID   UINT64_MAX
#define EBML_INT_INVALID    INT64_MAX
#define EBML_FLOAT_INVALID  -1000000000.0

#define MKV_A_AAC_2MAIN  "A_AAC/MPEG2/MAIN"
#define MKV_A_AAC_2LC    "A_AAC/MPEG2/LC"
#define MKV_A_AAC_2SBR   "A_AAC/MPEG2/LC/SBR"
#define MKV_A_AAC_2SSR   "A_AAC/MPEG2/SSR"
#define MKV_A_AAC_4MAIN  "A_AAC/MPEG4/MAIN"
#define MKV_A_AAC_4LC    "A_AAC/MPEG4/LC"
#define MKV_A_AAC_4SBR   "A_AAC/MPEG4/LC/SBR"
#define MKV_A_AAC_4SSR   "A_AAC/MPEG4/SSR"
#define MKV_A_AAC_4LTP   "A_AAC/MPEG4/LTP"
#define MKV_A_AAC        "A_AAC"
#define MKV_A_AC3        "A_AC3"
#define MKV_A_DTS        "A_DTS"
#define MKV_A_MP2        "A_MPEG/L2"
#define MKV_A_MP3        "A_MPEG/L3"
#define MKV_A_PCM        "A_PCM/INT/LIT"
#define MKV_A_PCM_BE     "A_PCM/INT/BIG"
#define MKV_A_VORBIS     "A_VORBIS"
#define MKV_A_ACM        "A_MS/ACM"
#define MKV_A_REAL28     "A_REAL/28_8"
#define MKV_A_REALATRC   "A_REAL/ATRC"
#define MKV_A_REALCOOK   "A_REAL/COOK"
#define MKV_A_REALDNET   "A_REAL/DNET"
#define MKV_A_REALSIPR   "A_REAL/SIPR"
#define MKV_A_QDMC       "A_QUICKTIME/QDMC"
#define MKV_A_QDMC2      "A_QUICKTIME/QDM2"
#define MKV_A_FLAC       "A_FLAC"
#define MKV_A_WAVPACK    "A_WAVPACK4"

#define MKV_V_MSCOMP     "V_MS/VFW/FOURCC"
#define MKV_V_REALV10    "V_REAL/RV10"
#define MKV_V_REALV20    "V_REAL/RV20"
#define MKV_V_REALV30    "V_REAL/RV30"
#define MKV_V_REALV40    "V_REAL/RV40"
#define MKV_V_SORENSONV1 "V_SORENSON/V1"
#define MKV_V_SORENSONV2 "V_SORENSON/V2"
#define MKV_V_SORENSONV3 "V_SORENSON/V3"
#define MKV_V_CINEPAK    "V_CINEPAK"
#define MKV_V_QUICKTIME  "V_QUICKTIME"
#define MKV_V_MPEG1      "V_MPEG1"
#define MKV_V_MPEG2      "V_MPEG2"
#define MKV_V_MPEG4_SP   "V_MPEG4/ISO/SP"
#define MKV_V_MPEG4_ASP  "V_MPEG4/ISO/ASP"
#define MKV_V_MPEG4_AP   "V_MPEG4/ISO/AP"
#define MKV_V_MPEG4_AVC  "V_MPEG4/ISO/AVC"
#define MKV_V_THEORA     "V_THEORA"

#define MKV_S_TEXTASCII  "S_TEXT/ASCII"
#define MKV_S_TEXTUTF8   "S_TEXT/UTF8"
#define MKV_S_TEXTSSA    "S_TEXT/SSA"
#define MKV_S_TEXTASS    "S_TEXT/ASS"
#define MKV_S_VOBSUB     "S_VOBSUB"
#define MKV_S_SSA        "S_SSA" // Deprecated
#define MKV_S_ASS        "S_ASS" // Deprecated

#define MKV_INPUT_PADDING 8

#endif