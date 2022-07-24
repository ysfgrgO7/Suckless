/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 20;       /* vert inner gap between windows */
static const unsigned int gappoh    = 20;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 20;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;     /* 0 means no bar */
static const int topbar             = 1;     /* 0 means bottom bar */
static const char *fonts[]          = { "JetbrainsMono nerd font:size=12",
"Material Design Icons Desktop:size=12"
};

#include "themes/catppuccin.h"

static const char *const autostart[] = {
	"volumeicon", NULL,
	"picom", NULL,
	"lxsession", NULL,
    "slstatus", NULL,
    "nitrogen", "--restore" , NULL,
	"picom", "-b", "--experimental-backends", NULL,
	NULL
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {"st", "-n", "spaud", "-g", "120x34", "-e", "pulsemixer",  NULL };
const char *spcmd3[] = {"st", "-n", "spmus", "-g", "120x34", "-e", "mocp",  NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spaud",       spcmd2},
	{"spmus",       spcmd3},
};

/* tagging */
static const char *tags[] = { " 1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 ", " 7 ", " 8 " };
static const unsigned int ulinepad	= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
	{ "Gimp",	  NULL,	   	  NULL,		0,				1,			 -1 },
	{ "VirtualBox Manager",	  NULL,		NULL,		    0,    1,			 -1 },
	{ "Firefox",  NULL,		  NULL,		1 << 8,			0,			 -1 },
	{ NULL,		  "spterm",	  NULL,		SPTAG(0),		1,			 -1 },
	{ NULL,		  "spaud",	  NULL,		SPTAG(1),		1,			 -1 },
	{ NULL,		  "spmus",	  NULL,		SPTAG(2),		1,			 -1 },
};

static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]     = { "dmenu_run", "-c", "-l", "20", "-g", "2", "-p", "Run :", NULL };
static const char *roficmd[]      = { "rofi", "-show", "drun", NULL };
static const char *rofiwcmd[]     = { "rofi", "-show", "window", NULL };
static const char *termcmd[]      = { "st", NULL };
static const char *fmcmd[]        = { "pcmanfm", NULL };
static const char *tuifmcmd[]     = { "st", "-e", "ranger", NULL };
static const char *webcmd[]       = { "brave", NULL };
static const char *scrotcmd[]     = { "scrot", NULL };


static Key keys[] = {
// Apps 
{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
{ MODKEY,                       XK_w,      spawn,          {.v = webcmd } },
{ MODKEY,                       XK_e,      spawn,          {.v = tuifmcmd } },
{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = scrotcmd } },
{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = roficmd } },
{ MODKEY|ShiftMask,             XK_d,      spawn,          {.v = rofiwcmd } },
{ MODKEY|ShiftMask,             XK_e,      spawn,          {.v = fmcmd } },
// Layout Controls
{ MODKEY,                       XK_f,      togglefloating, {0} },
{ MODKEY,                       XK_Tab,    cyclelayout,    {.i = +1 } },
{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
{ MODKEY|ShiftMask,             XK_space,  togglefullscr,  {0} },
{ MODKEY,                       XK_b,      togglebar,      {0} },
{ MODKEY,                       XK_c,      zoom,           {0} },
// Dwm Stuff
{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
{ MODKEY|ControlMask,           XK_v,      incnmaster,     {.i = +1 } },
{ MODKEY|ControlMask,           XK_h,      incnmaster,     {.i = -1 } },
{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
{ MODKEY,                       XK_space,  focusstack,     {.i = +1 } },
{ MODKEY|ShiftMask,             XK_r,      quit,           {1} }, 
{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
//Scratchpads
{ MODKEY,                       XK_p,        togglescratch,  {.ui = 0 } },
{ MODKEY,                       XK_s,	     togglescratch,  {.ui = 1 } },
{ MODKEY,                       XK_m,	     togglescratch,  {.ui = 2 } },
// Tags
TAGKEYS(                        XK_1,                      0)
TAGKEYS(                        XK_2,                      1)
TAGKEYS(                        XK_3,                      2)
TAGKEYS(                        XK_4,                      3)
TAGKEYS(                        XK_5,                      4)
TAGKEYS(                        XK_6,                      5)
TAGKEYS(                        XK_7,                      6)
TAGKEYS(                        XK_8,                      7)
// Gaps
{ MODKEY|Mod1Mask,              XK_u,      incrgaps,       {.i = +1 } },
{ MODKEY|Mod1Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
{ MODKEY|Mod1Mask,              XK_i,      incrigaps,      {.i = +1 } },
{ MODKEY|Mod1Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
{ MODKEY|Mod1Mask,              XK_o,      incrogaps,      {.i = +1 } },
{ MODKEY|Mod1Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
{ MODKEY|Mod1Mask,              XK_6,      incrihgaps,     {.i = +1 } },
{ MODKEY|Mod1Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
{ MODKEY|Mod1Mask,              XK_7,      incrivgaps,     {.i = +1 } },
{ MODKEY|Mod1Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
{ MODKEY|Mod1Mask,              XK_8,      incrohgaps,     {.i = +1 } },
{ MODKEY|Mod1Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
{ MODKEY|Mod1Mask,              XK_9,      incrovgaps,     {.i = +1 } },
{ MODKEY|Mod1Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
