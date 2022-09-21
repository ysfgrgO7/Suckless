/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int default_border = 0;   /* to switch back to default border after dynamic border resizing via keybinds */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails,display systray on the 1st monitor,False: display systray on last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int showtab            = showtab_auto;
static const int toptab             = 1;        /* 0 means bottom tab */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 5;
static const int vertpadbar         = 11;
static const int vertpadtab         = 35;
static const int horizpadtabi       = 15;
static const int horizpadtabo       = 15;
static const int scalepreview       = 4;
static const int tag_preview        = 0;        /* 1 means enable, 0 is off */
static const int colorfultag        = 1;        /* 0 means use SchemeSel for selected non vacant tag */

static const char *fonts[]          = { "JetbrainsMono nerd font:size=12",
"Material Design Icons Desktop:size=12"
};

// theme
#include "themes/catppuccin.h"

static const char *colors[][3]      = {
    /*                     fg       bg      border */
    [SchemeNorm]       = { gray3,   black,  gray2 },
    [SchemeSel]        = { gray4,   blue,   blue  },
    [SchemeTitle]      = { white,   black,  black  }, // active window title
    [TabSel]           = { blue,    gray2,  black },
    [TabNorm]          = { gray3,   black,  black },
    [SchemeTag]        = { gray3,   black,  black },
    [SchemeTag1]       = { blue,    black,  black },
    [SchemeTag2]       = { red,     black,  black },
    [SchemeTag3]       = { orange,  black,  black },
    [SchemeTag4]       = { green,   black,  black },
    [SchemeTag5]       = { pink,    black,  black },
    [SchemeLayout]     = { green,   black,  black },
    [SchemeBtnPrev]    = { green,   black,  black },
    [SchemeBtnNext]    = { yellow,  black,  black },
    [SchemeBtnClose]   = { red,     black,  black },
};

static const char *const autostart[] = {
	"volumeicon", NULL,
	"picom", NULL,
	"lxsession", NULL,
    "slstatus", NULL,
    "nitrogen", "--restore" , NULL,
	"picom", "-b", "--experimental-backends", NULL,
	NULL
};

/* tagging */
static char *tags[] = {"", "", "", "", ""};

static const int tagschemes[] = {
    SchemeTag1, SchemeTag2, SchemeTag3, SchemeTag4, SchemeTag5
};

static const unsigned int ulinepad      = 5; /* horizontal padding between the underline and tag */
static const unsigned int ulinestroke   = 2; /* thickness / height of the underline */
static const unsigned int ulinevoffset  = 0; /* how far above the bottom of the bar the line should appear */
static const int ulineall               = 0; /* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     iscentered   isfloating   monitor */
    { "Gimp",     NULL,       NULL,       0,            0,           1,           -1 },
    { "Firefox",  NULL,       NULL,       1 << 8,       0,           0,           -1 },
    { "eww",      NULL,       NULL,       0,            0,           1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "functions.h"


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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]     = { "dmenu_run", "-c", "-l", "20", "-g", "2", "-p", "Run :", NULL };
static const char *roficmd[]      = { "rofi", "-show", "drun", NULL };
static const char *rofiwcmd[]     = { "rofi", "-show", "window", NULL };
static const char *termcmd[]      = { "alacritty", NULL };
static const char *fmcmd[]        = { "pcmanfm", NULL };
static const char *tuifmcmd[]     = { "alacritty", "-e", "ranger", NULL };
static const char *webcmd[]       = { "brave", NULL };
static const char *scrotcmd[]     = { "scrot", NULL };

/* commands */

static Key keys[] = {
// Audio and brightness
{0,                     XF86XK_AudioMute,       spawn,          SHCMD("pamixer -t")},
{0,              XF86XK_AudioRaiseVolume,       spawn,          SHCMD("pamixer -i 5")},
{0,              XF86XK_AudioLowerVolume,       spawn,          SHCMD("pamixer -d 5")},
{0,              XF86XK_MonBrightnessDown,      spawn,          SHCMD("xbacklight -dec 5")},
{0,              XF86XK_MonBrightnessUp,        spawn,          SHCMD("xbacklight -inc 5")},
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
{ MODKEY,                       XK_o,      focusmon,       {.i = +1 } },
{ MODKEY|ShiftMask,             XK_o,      tagmon,         {.i = +1 } },
//Scratchpads
// { MODKEY,                       XK_p,        togglescratch,  {.ui = 0 } },
// { MODKEY,                       XK_s,	     togglescratch,  {.ui = 1 } },
// { MODKEY,                       XK_m,	     togglescratch,  {.ui = 2 } },
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
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          SHCMD("st") },

    /* Keep movemouse? */
    /* { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} }, */

    /* placemouse options, choose which feels more natural:
    *    0 - tiled position is relative to mouse cursor
    *    1 - tiled position is relative to window center
    *    2 - mouse pointer warps to window center
    *
    * The moveorplace uses movemouse or placemouse depending on the floating state
    * of the selected client. Set up individual keybindings for the two if you want
    * to control these separately (i.e. to retain the feature to move a tiled window
    * into a floating position).
    */
    { ClkClientWin,         MODKEY,         Button1,        moveorplace,    {.i = 0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkClientWin,         ControlMask,    Button1,        dragmfact,      {0} },
    { ClkClientWin,         ControlMask,    Button3,        dragcfact,      {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
    { ClkTabBar,            0,              Button1,        focuswin,       {0} },
    { ClkTabBar,            0,              Button1,        focuswin,       {0} },
    { ClkTabPrev,           0,              Button1,        movestack,      { .i = -1 } },
    { ClkTabNext,           0,              Button1,        movestack,      { .i = +1 } },
    { ClkTabClose,          0,              Button1,        killclient,     {0} },
};
