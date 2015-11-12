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
#define DateFormat "%a %m/%d"
#else
#define DateFormat "%a %d/%m"
#endif

#define DateTruncTo2Char false

// Line Draw Parameters
#define lineInset   10
#define lineVOffset 128

#ifdef PBL_COLOR
	#define FORE_COLOR GColorWhite
	#define BACK_COLOR GColorJazzberryJam 
#else 
	#define FORE_COLOR GColorWhite
	#define BACK_COLOR GColorBlack
#endif 

#ifdef PBL_ROUND
	#define DATE_VOFFSET 5
#else
	#define DATE_VOFFSET 0
#endif




