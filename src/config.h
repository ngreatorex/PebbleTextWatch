////////////////////////////////////
// Watch Face Variants
#define TimeRenderOh         true
#define DateSeparatorLine    true
#define DateOutsideJustified true
#define DateFormatUS         true
////////////////////////////////////

// Time/Date Layout Parameters
#define TextLineVOffset 0
#define DateVOffset     123

#if DateFormatUS
#define DateFormat "%m.%d"
#else
#define DateFormat "%d.%m"
#endif

#if DateOutsideJustified
// Outside -> Weekday is left justified and Date is right justified
#define DateTruncTo2Char false
#define WeekdayHStart    0
#define WeekdayHStop     72
#define DateHStart       64
#define DateHStop        143
#define WeekdayRightJust false
#define DateRightJust    true
#else // Inside Justified
// Inside -> Weekday is right justified and Date is left justified
#define DateTruncTo2Char true
#define WeekdayHStart    0
#define WeekdayHStop     61
#define DateHStart       65
#define DateHStop        144
#define WeekdayRightJust true
#define DateRightJust    false
#endif

// Line Draw Parameters
#define lineInset   10
#define lineVOffset 128



