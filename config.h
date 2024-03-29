/* See LICENSE file for copyright and license details. */
#include "dwm.h"

/* appearance */
unsigned int borderpx  = 1;        /* border pixel of windows */
unsigned int snap      = 32;       /* snap pixel */
int gappx              = 16;       /* gap between clients and borders */
int showbar            = 1;        /* 0 means no bar */
int topbar             = 1;        /* 0 means bottom bar */
const char *fonts[]          = {
	"monospace:size=11:style=Medium",
	"JoyPixels:size=11",
	"Noto Sans CJK SC:size=11:style=Medium",
	"Material Design Icons:size=13"
};
int barheightmin       = 24;       /* minimum height if > 0 */
int barpaddingh        = 2;        /* horizontal padding for statusbar */
int barpaddingtop      = 2;        /* top padding for statusbar */
int barpaddingbottom   = 0;        /* bottom padding for statusbar */
const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
unsigned int systrayspacing = 8;   /* systray spacing */
unsigned int systrayiconsize = 18;   /* systray icon size */
const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
const int showsystray        = 1;     /* 0 means no systray */
char foreground[] = "#000000";
char background[] = "#ffffff";
char color16[][8] = {
	"#000000", "#AA0000", "#00AA00", "#AAAA00",
	"#0000AA", "#AA00AA", "#00AAAA", "#AAAAAA",
	"#555555", "#FF5555", "#55FF55", "#FFFF55",
	"#5555FF", "#FF55FF", "#55FFFF", "#FFFFFF"
};
const char *colors[][3]      = {
	/*               fg          bg          border   */
	[SchemeNorm] = { foreground, background, color16[0] },
	[SchemeSel]  = { background, color16[6], color16[6] },
 };

/* tagging */
const char *tags[] = { "󰲡", "󰲣", "󰲥", "󰲧", "󰲩" };
const char *tags_busy[] = { "󰲠", "󰲢", "󰲤", "󰲦", "󰲨" };
const char *tags_curr[] = { "󰓏", "󰓏", "󰓏", "󰓏", "󰓏" };

const Rule rules[] = {
	/* class         instance   title  tags    float sticky monitor */
	{ "firefox",     NULL,      NULL,  1 << 1, 0,    0,     -1 },
	{ "firefox",     "Toolkit", NULL,  1 << 1, 1,    1,     -1 },
	{ "firefox",     "Browser", NULL,  1 << 1, 1,    0,     -1 },
	{ "Arandr",      NULL,      NULL,  0,      1,    0,     -1 },
	{ "floating",    NULL,      NULL,  0,      1,    0,     -1 },
	{ "wemeetapp",   NULL,      NULL,  0,      1,    0,     -1 },
};

/* layout(s) */
float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
int nmaster     = 1;    /* number of clients in master area */
int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

const Layout layouts[] = {
	/* symbol     arrange function */
	{ "󰙀",      tile },    /* first entry is default */
	{ "󰄮",      monocle },
	{ "󰕰",      grid },
	{ "󰕬",      centeredmaster },
	{ "󰕕",      NULL },    /* no layout function means floating behavior */
};

/* These symbols will replace the monocle symbol with corresponding client count */
const char *monocle_n[] = { "󰎤", "󰎧", "󰎪", "󰎭", "󰎱", "󰎳", "󰎶", "󰎹", "󰎼", "󰎿" };

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* commands spawned when clicking statusbar, the mouse button pressed is exported as BUTTON */
char statuscmdc[2] = {0};
char *statuscmd[] = { "statusctl", statuscmdc, NULL };
char *dmenucmd[] = { "dmenu_run", NULL };
char *xmenucmd[] = { "xdg-xmenu", NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "borderpx",           INTEGER, &borderpx },
		{ "snap",               INTEGER, &snap },
		{ "showbar",            INTEGER, &showbar },
		{ "topbar",             INTEGER, &topbar },
		{ "barheight",          INTEGER, &barheightmin },
		{ "foreground",         STRING,  &foreground },
		{ "background",         STRING,  &background },
		{ "color0",             STRING,  &color16[0] },
		{ "color1",             STRING,  &color16[1] },
		{ "color2",             STRING,  &color16[2] },
		{ "color3",             STRING,  &color16[3] },
		{ "color4",             STRING,  &color16[4] },
		{ "color5",             STRING,  &color16[5] },
		{ "color6",             STRING,  &color16[6] },
		{ "color7",             STRING,  &color16[7] },
		{ "color8",             STRING,  &color16[8] },
		{ "color9",             STRING,  &color16[9] },
		{ "color10",            STRING,  &color16[10] },
		{ "color11",            STRING,  &color16[11] },
		{ "color12",            STRING,  &color16[12] },
		{ "color13",            STRING,  &color16[13] },
		{ "color14",            STRING,  &color16[14] },
		{ "color15",            STRING,  &color16[15] },
		{ "nmaster",            INTEGER, &nmaster },
		{ "resizehints",        INTEGER, &resizehints },
		{ "systrayiconsize",    INTEGER, &systrayiconsize },
		{ "systrayspacing",     INTEGER, &systrayspacing },
		{ "mfact",              FLOAT,   &mfact },
};

const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_x,      spawn,          {.v = dmenucmd} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_l,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ControlMask,           XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Escape, view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_6,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_7,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_8,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_9,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_space,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_f,      togglefloating, {0} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_a,      togglesticky,   {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY|ControlMask,           XK_minus,  setgap,         {.i = -16 } },
	{ MODKEY|ControlMask,           XK_equal,  setgap,         {.i = +16 } },
	{ MODKEY,                       XK_comma,  shiftview,      {.i = -1 } },
	{ MODKEY,                       XK_period, shiftview,      {.i = +1 } },
	{ MODKEY,                       XK_Up,     focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Down,   focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Left,   shiftview,      {.i = -1 } },
	{ MODKEY,                       XK_Right,  shiftview,      {.i = +1 } },
	{ MODKEY|ControlMask,           XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask|ControlMask, XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask|ControlMask, XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        cyclelayout,    {.i = +1 } },
	{ ClkLtSymbol,          0,              Button3,        cyclelayout,    {.i = -1 } },
	{ ClkLtSymbol,          0,              Button4,        cyclelayout,    {.i = -1 } },
	{ ClkLtSymbol,          0,              Button5,        cyclelayout,    {.i = +1 } },
	{ ClkWinTitle,          0,              Button3,        zoom,           {0} },
	{ ClkWinTitle,          0,              Button4,        focusstack,     {.i = -1 } },
	{ ClkWinTitle,          0,              Button5,        focusstack,     {.i = +1 } },
	{ ClkStatusText,        0,              Button1,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,              Button3,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,              Button4,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,              Button5,        spawn,          {.v = statuscmd } },
	{ ClkRootWin,           0,              Button3,        spawn,          {.v = xmenucmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button2,        tag,            {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            0,              Button4,        shiftview,      {.i = -1 } },
	{ ClkTagBar,            0,              Button5,        shiftview,      {.i = +1 } },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
