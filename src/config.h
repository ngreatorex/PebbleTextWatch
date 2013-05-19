////////////////////////////////////
// Watch Face Variants
#define TimeRenderOh         true
#define DateSeparatorLine    false
#define DateOutsideJustified true
#define DateFormatUS         false
////////////////////////////////////

// Time/Date Layout Parameters
#define TextLineVOffset 0
#define DateVOffset     140

#if DateFormatUS
#define DateFormat "%m.%d"
#else
#define DateFormat "%a %d/%m/%Y"
#endif

#define DateTruncTo2Char false
#define DateHStart       0
#define DateHStop        143
#define DateRightJust    false

// Line Draw Parameters
#define lineInset   10
#define lineVOffset 128



