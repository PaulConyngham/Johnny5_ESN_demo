#ifndef ATTO_H
#define ATTO_H

#include "atto_internals.h"

// -----------------------------------------------------------------------------------
// ---------------- Handler Types and Setup Function ---------------------------------
// -----------------------------------------------------------------------------------

typedef void (*AttoKeyDownFunction)(int code);
typedef void (*AttoKeyUpFunction)(int code);
typedef void (*AttoMouseDownFunction)(int x, int y, int button);
typedef void (*AttoMouseDragFunction)(int x, int y, int button);
typedef void (*AttoMouseUpFunction)(int x, int y, int button);
typedef void (*AttoDrawFunction)();
typedef void (*AttoGenericFunction)(void *custom);
typedef void (*AttoMouseScroll)(int scroll);

// set the size of your area and the event handlers before atto_main
void atto_setup(int w, int h,
		AttoKeyDownFunction keydown,
		AttoKeyUpFunction keyup,
		AttoMouseDownFunction down,
		AttoMouseDragFunction drag,
		AttoMouseUpFunction up,
		AttoDrawFunction draw,
        AttoMouseScroll scroll);
       

// hand control over to atto and start the GUI running
int atto_main(int argc, char **argv);

// -----------------------------------------------------------------------------------
// ---------------- Drawing Functions ------------------------------------------------
// -----------------------------------------------------------------------------------

void atto_color(float r, float g, float b);
void atto_frame(int left, int top, int w, int h);
void atto_fill(int left, int top, int w, int h);
void atto_line(int x1, int y1, int x2, int y2);
void atto_string(int left, int baseline, const char *string);
void atto_gif(int left, int top, const char *path_to_image);
void atto_arc(int left, int top, int w, int h, double degree1, double degree2);

// get the size a string will draw
void atto_measure_string(const char *string, int *w, int *h);

// cause a redraw of the area (will call your draw() handler)
void atto_redraw(void);

// -----------------------------------------------------------------------------------
// ---------------- Debugging Macros -------------------------------------------------
/* -----------------------------------------------------------------------------------
Require, Assert, Check Usage:
	Set DEBUG_LEVEL in your application source.

        Generally use Assert and change to Require or Check in these cases:
                Require should be used for conditions that absolutely must hold
                or data will be lost, machines will crash, lives will be endangered.

                Check should be used for conditions that are non-critical AND expensive
                to check (either called very frequently or computationally hard to check).

        If you're not sure which to use, then use Assert and tweak the level later by changing
        Asserts to Checks or Requires.

        Note, these are used to catch software bugs or to enforce interfaces, not for
        expected errors like a disk being full or a network timing out.
---------------------------------------------------------------------------------*/

#define REQUIRE_DEBUG_LEVEL 1
#define ASSERT_DEBUG_LEVEL 2
#define CHECK_DEBUG_LEVEL 3

#if DEBUG_LEVEL >= REQUIRE_DEBUG_LEVEL
#define Require(x) if(DEBUG_LEVEL >= REQUIRE_DEBUG_LEVEL && !(x)) on_debug_failure(__FILE__, __LINE__)
#else
#define Require(x)
#endif

#if DEBUG_LEVEL >= ASSERT_DEBUG_LEVEL
#define Assert(x) if(DEBUG_LEVEL >= ASSERT_DEBUG_LEVEL && !(x)) on_debug_failure(__FILE__, __LINE__)
#else
#define Assert(x)
#endif

#if DEBUG_LEVEL >= CHECK_DEBUG_LEVEL
#define Check(x) if(DEBUG_LEVEL >= CHECK_DEBUG_LEVEL && !(x)) on_debug_failure(__FILE__, __LINE__)
#else
#define Check(x)
#endif

void on_debug_failure(const char *file, int line);

// -----------------------------------------------------------------------------------
// ---------------- Extra / Rarely Used Functions ------------------------------------
// -----------------------------------------------------------------------------------

// atto will call f(custom) after a delay of secs_from_now
void atto_timeout(float secs_from_now, AttoGenericFunction f, void *custom);

// atto will call f(custom) whenever there is nothing else going on
void atto_idle_start(AttoGenericFunction f, void *custom);
// removes a previously installed idle function (do not use with atto_timeout)
void atto_idle_end(AttoGenericFunction f);

// get the current status of a key or the mouse
int atto_key_is_down(int code);
void atto_get_mouse(int *x, int *y);

// Interaction Functions:
// The string values returned from some of these functions are ONLY valid until
// the next time that function is called.  Copy the strings if you want to keep them.
void atto_message(const char *string);
const char *atto_input(const char *prompt, const char *default_string);
int atto_choice(const char *question, const char *option0, const char *option1, const char *option2);
const char *atto_file_chooser(const char *prompt, const char *tabSeparatedPatterns);
const char *atto_dir_chooser(const char *prompt);
int atto_color_chooser(const char *title, float *r, float *g, float *b);
void atto_beep();

// some useful key constants (provided by FLTK) for use in your key(code) function
/*
FL_BackSpace - The backspace key.
FL_Tab - The tab key.
FL_Enter - The enter key.
FL_Escape - The escape key.
FL_Left - The left arrow key.
FL_Up - The up arrow key.
FL_Right - The right arrow key.
FL_Down - The down arrow key.
FL_KP - One of the keypad numbers; use FL_KP + n for number n.
FL_KP_Enter - The enter key on the keypad.
FL_F - One of the function keys; use FL_F + n for function key n.
FL_Shift_L - The lefthand shift key.
FL_Shift_R - The righthand shift key.
FL_Control_L - The lefthand control key.
FL_Control_R - The righthand control key.
FL_Caps_Lock - The caps lock key.
FL_Alt_L - The left alt key.
FL_Alt_R - The right alt key.
FL_Delete - The delete key.
*/

#endif


