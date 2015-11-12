#include <pebble.h>
#include "pebble_fonts.h"
#include "num2words-en.h"
#include "config.h"

#define DEBUG false
#define BUFFER_SIZE 44

Window *window;

typedef struct {
	TextLayer *currentLayer;
	TextLayer *nextLayer;	
	PropertyAnimation *currentAnimation;
	PropertyAnimation *nextAnimation;
} Line;

Line line1;
Line line2;
Line line3;
Line line4;

GRect bounds;

static char line1Str[2][BUFFER_SIZE];
static char line2Str[2][BUFFER_SIZE];
static char line3Str[2][BUFFER_SIZE];
static char line4Str[2][BUFFER_SIZE];

// Animation handler
void animationStoppedHandler(struct Animation *animation, bool finished, void *context)
{
	Layer *current = (Layer *)context;
	GRect rect = layer_get_frame(current);
	rect.origin.x = bounds.size.w;
	layer_set_frame(current, rect);
}

// Animate line
void makeAnimationsForLayers(Line *line, TextLayer *current, TextLayer *next)
{
	if (line->nextAnimation != NULL)
		property_animation_destroy(line->nextAnimation);

	if (line->currentAnimation != NULL)
		property_animation_destroy(line->currentAnimation);

	GRect rect = layer_get_frame((Layer *)next);
	rect.origin.x -= bounds.size.w;
	
	line->nextAnimation = property_animation_create_layer_frame((Layer *)next, NULL, &rect);
	animation_set_duration(property_animation_get_animation(line->nextAnimation), 400);
	animation_set_curve(property_animation_get_animation(line->nextAnimation), AnimationCurveEaseOut);

	animation_schedule(property_animation_get_animation(line->nextAnimation));
	
	GRect rect2 = layer_get_frame((Layer *)current);
	rect2.origin.x -= bounds.size.w;
	
	line->currentAnimation = property_animation_create_layer_frame((Layer *)current, NULL, &rect2);
	animation_set_duration(property_animation_get_animation(line->currentAnimation), 400);
	animation_set_curve(property_animation_get_animation(line->currentAnimation), AnimationCurveEaseOut);
	
	animation_set_handlers(property_animation_get_animation(line->currentAnimation), (AnimationHandlers) {
		.stopped = (AnimationStoppedHandler)animationStoppedHandler
	}, current);
	
	animation_schedule(property_animation_get_animation(line->currentAnimation));
}

// Update line
void updateLineTo(Line *line, char lineStr[2][BUFFER_SIZE], char *value)
{
	TextLayer *next, *current;
	
	GRect rect = layer_get_frame((Layer *)line->currentLayer);
	current = (rect.origin.x == 0) ? line->currentLayer : line->nextLayer;
	next = (current == line->currentLayer) ? line->nextLayer : line->currentLayer;
	
	// Update correct text only
	if (current == line->currentLayer) {
		memset(lineStr[1], 0, BUFFER_SIZE);
		memcpy(lineStr[1], value, strlen(value));
		text_layer_set_text(next, lineStr[1]);
	} else {
		memset(lineStr[0], 0, BUFFER_SIZE);
		memcpy(lineStr[0], value, strlen(value));
		text_layer_set_text(next, lineStr[0]);
	}
	
	makeAnimationsForLayers(line, current, next);
}

// Check to see if the current line needs to be updated
bool needToUpdateLine(Line *line, char lineStr[2][BUFFER_SIZE], char *nextValue)
{
	char *currentStr;
	GRect rect = layer_get_frame((Layer *)line->currentLayer);
	currentStr = (rect.origin.x == 0) ? lineStr[0] : lineStr[1];

	if (memcmp(currentStr, nextValue, strlen(nextValue)) != 0 ||
		(strlen(nextValue) == 0 && strlen(currentStr) != 0)) {
		return true;
	}
	return false;
}

// Represent the date as displayable string
void date_to_string(struct tm *t, char *line, size_t length) {
  memset(line, 0, length);
 
  strftime(line, length, DateFormat, t);
  
  // day of week to lowercase
  line[0] += 32;
}

// Update screen based on new time
void display_time(struct tm *t)
{
	// The current time text will be stored in the following 3 strings
	char textLine1[BUFFER_SIZE];
	char textLine2[BUFFER_SIZE];
	char textLine3[BUFFER_SIZE];
	char textLine4[BUFFER_SIZE];
	
	time_to_3words(t->tm_hour, t->tm_min, textLine1, textLine2, textLine3, BUFFER_SIZE);
    date_to_string(t, textLine4, BUFFER_SIZE);
	
	if (needToUpdateLine(&line1, line1Str, textLine1)) {
		updateLineTo(&line1, line1Str, textLine1);	
	}
	if (needToUpdateLine(&line2, line2Str, textLine2)) {
		updateLineTo(&line2, line2Str, textLine2);	
	}
	if (needToUpdateLine(&line3, line3Str, textLine3)) {
		updateLineTo(&line3, line3Str, textLine3);	
	}
	if (needToUpdateLine(&line4, line4Str, textLine4)) {
        memset(line4Str[0], 0, BUFFER_SIZE);
        memcpy(line4Str[0], textLine4, strlen(textLine4));
        text_layer_set_text(line4.currentLayer, line4Str[0]);
	}
}

// Update screen without animation first time we start the watchface
void display_initial_time(struct tm *t)
{
	time_to_3words(t->tm_hour, t->tm_min, line1Str[0], line2Str[0], line3Str[0], BUFFER_SIZE);
    date_to_string(t, line4Str[0], BUFFER_SIZE);
        
	text_layer_set_text(line1.currentLayer, line1Str[0]);
	text_layer_set_text(line2.currentLayer, line2Str[0]);
	text_layer_set_text(line3.currentLayer, line3Str[0]);
	text_layer_set_text(line4.currentLayer, line4Str[0]);
}


// Configure the first line of text
void configureBoldLayer(TextLayer *textlayer, bool right)
{
	text_layer_set_font(textlayer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
	text_layer_set_text_color(textlayer, FORE_COLOR);
	text_layer_set_background_color(textlayer, GColorClear);
        if (right) {
          text_layer_set_text_alignment(textlayer, GTextAlignmentRight);
        } else {
          text_layer_set_text_alignment(textlayer, GTextAlignmentCenter);
        }
}

// Configure for the 2nd and 3rd lines
void configureLightLayer(TextLayer *textlayer, bool right)
{
	text_layer_set_font(textlayer, fonts_get_system_font(FONT_KEY_BITHAM_42_LIGHT));
	text_layer_set_text_color(textlayer, FORE_COLOR);
	text_layer_set_background_color(textlayer, GColorClear);
        if (right) {
          text_layer_set_text_alignment(textlayer, GTextAlignmentRight);
        } else {
          text_layer_set_text_alignment(textlayer, GTextAlignmentCenter);
        }
}

void configureDateLayer(TextLayer *textlayer, bool right)
{
	text_layer_set_font(textlayer, fonts_get_system_font(FONT_KEY_GOTHIC_18));
	text_layer_set_text_color(textlayer, FORE_COLOR);
	text_layer_set_background_color(textlayer, GColorClear);
        if (right) {
          text_layer_set_text_alignment(textlayer, GTextAlignmentRight);
        } else {
          text_layer_set_text_alignment(textlayer, GTextAlignmentCenter);
        }
}

// Time handler called every minute by the system
static void handle_minute_tick(struct tm *tick_time, TimeUnits units_changed) 
{
	display_time(tick_time);
}

void handle_init() 
{
	window = window_create();
	window_stack_push(window, true);
	window_set_background_color(window, BACK_COLOR);
	
	Layer *root = window_get_root_layer(window);
	bounds = layer_get_bounds(root);

	int offset = (bounds.size.h - 130) / 2;
	
	// 1st line layer
	line1.currentLayer = text_layer_create(GRect(bounds.origin.x, offset, bounds.size.w, 50));
	line1.nextLayer = text_layer_create(GRect(bounds.size.w, offset, bounds.size.w, 50));
	configureBoldLayer(line1.currentLayer, false);
	configureBoldLayer(line1.nextLayer, false);

	// 2nd line layer
	line2.currentLayer = text_layer_create(
                        GRect(0, 37 + offset, bounds.size.w, 50));
	line2.nextLayer = text_layer_create(
                        GRect(bounds.size.w, 37 + offset, bounds.size.w, 50));
	configureLightLayer(line2.currentLayer, false);
	configureLightLayer(line2.nextLayer, false);

	// 3rd line layer
	line3.currentLayer = text_layer_create(
                        GRect(0, 74 + offset, bounds.size.w, 50));
	line3.nextLayer = text_layer_create(
                        GRect(bounds.size.w, 74 + offset, bounds.size.w, 50));
	configureLightLayer(line3.currentLayer, false);
	configureLightLayer(line3.nextLayer, false);

	// 4th layer - Date
	line4.currentLayer = text_layer_create(
          GRect(0, bounds.origin.y + bounds.size.h - (25 + DATE_VOFFSET),
                bounds.size.w, 25));
	configureDateLayer(line4.currentLayer, false);

	// Configure time on init
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	display_time(t);

	// Register for minute ticks
	tick_timer_service_subscribe(MINUTE_UNIT, (TickHandler)handle_minute_tick);
	
	// Load layers

  	layer_add_child(root, (Layer *)line1.currentLayer);
	layer_add_child(root, (Layer *)line1.nextLayer);
	layer_add_child(root, (Layer *)line2.currentLayer);
	layer_add_child(root, (Layer *)line2.nextLayer);
	layer_add_child(root, (Layer *)line3.currentLayer);
	layer_add_child(root, (Layer *)line3.nextLayer);
	layer_add_child(root, (Layer *)line4.currentLayer);
}

void handle_deinit()
{
	tick_timer_service_unsubscribe();

	text_layer_destroy(line1.currentLayer);
	text_layer_destroy(line1.nextLayer);
	text_layer_destroy(line2.currentLayer);
	text_layer_destroy(line2.nextLayer);
	text_layer_destroy(line3.currentLayer);
	text_layer_destroy(line3.nextLayer);
	text_layer_destroy(line4.currentLayer);

	window_destroy(window);
}

int main(void) 
{
	handle_init();
	app_event_loop();
	handle_deinit();
}
