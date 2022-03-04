/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int topbar = 1;                      /* -b  option; if 0, dmenu appears at bottom     */
static int centered = 0;                    /* -c option; centers dmenu on screen */
static int min_width = 500;                    /* minimum width when centered */
/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = {
	"JetbrainsMono nerd font:size=11"
};

#include "themes/catppuccin.h"
/* #include "themes/darkplus.h" */
/* #include "themes/onedarker.h" */
/* #include "themes/tokyonight.h" */

static const char *prompt      = NULL;      /* -p  option; prompt to the left of input field */
/* -l and -g options; controls number of lines and columns in grid if > 0 */
static unsigned int lines      = 0;
static unsigned int columns    = 0;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";

/* Size of the window border */
static const unsigned int border_width = 0;
