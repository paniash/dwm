/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2.5;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 4;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 4;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "IBM Plex Mono:size=12",
					"IPAGothic:style=Regular",
					"FontAwesome:style=Regular:size=11:antialias=true:autohint=true",
					"MaterialIcons:style=Regular:size=13:antialias=true:autohint=true"
};
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#050000";
static const char col_gray5[]       = "#9f9ea8";
static const char col_cyan[]        = "#005577";
static const char col_cyan2[]       = "#007777";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, NULL },
	[SchemeSel]  = { col_gray4, col_cyan2,  col_gray5 },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34+460-200", NULL };
const char *spcmd2[] = {"st", "-n", "spcalc", "-g", "50x20+760-360", "-e", "bc", "-lq", NULL };
const char *spcmd3[] = {"st", "-n", "spmusic", "-g", "120x34+520-200", "-e", "ncmpcpp", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spcalc",      spcmd2},
	{"spmusic",     spcmd3},
};

/* tagging */
/* static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" }; */
/* static const char *tags[] = { "1", "2", "3", "4", "5", "6" }; */
/* static const char *tags[] = { "I", "II", "III", "IV", "V", "VI" }; */
/* static const char *tags[] = { "一", "二", "三", "四", "五", "六", "七", "八", "九" }; */
static const char *tags[] = { "一", "二", "三", "四", "五", "六" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       1 << 4,            1,           -1 },
	{ "Slack",     NULL,       NULL,       1 << 5,            0,           -1 },
	{ "Matplotlib",     NULL,       NULL,       0,            1,           -1 },
	{ "R_x11",     NULL,      NULL,       0,            1,           -1 },
	{ NULL,		  "spterm",	  NULL,		SPTAG(0),		1,			 -1 },
	{ NULL,		  "spcalc",	  NULL,		SPTAG(1),		1,			 -1 },
	{ NULL,		  "spmusic",	NULL,		SPTAG(2),		1,			 -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key        function        argument */
	// Spawn keybindings
	{ MODKEY,                       XK_d,      spawn,          SHCMD("dmenu_run") },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask,  			XK_Return, togglescratch,  {.ui = 0 } },
	{ MODKEY,           			XK_c,	   togglescratch,  {.ui = 1 } },
	{ MODKEY,           			XK_b,	   togglescratch,  {.ui = 2 } },
	{ MODKEY,                       XK_w,      spawn,          SHCMD("firefox") },
	{ MODKEY,                       XK_n,      spawn,          SHCMD("st -e lf") },
	{ MODKEY|ShiftMask,             XK_m,      spawn,          SHCMD("st -e neomutt ; pkill -RTMIN+12 dwmblocks") },
	{ MODKEY|ShiftMask,             XK_n,      spawn,          SHCMD("st -e newsboat") },
	{ MODKEY|ShiftMask,             XK_b,      spawn,          SHCMD("buku-dmenu") },
	{ MODKEY,                       XK_p,      spawn,          SHCMD("st -e ytop") },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          SHCMD("slack") },
	{ MODKEY|ShiftMask,             XK_Escape, spawn,          SHCMD("shutdown.sh") },

	// Media keys
	{ 0,                       XF86XK_AudioMute,             spawn,          SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle; pkill -RTMIN+10 dwmblocks") },
	{ 0,                       XF86XK_AudioRaiseVolume,      spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +5%; pkill -RTMIN+10 dwmblocks") },
	{ 0,                       XF86XK_AudioLowerVolume,      spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -5%; pkill -RTMIN+10 dwmblocks") },
	{ 0,                       XF86XK_AudioPlay,      		 spawn,          SHCMD("mpc toggle; pkill -RTMIN+11 dwmblocks") },
	{ 0,                       XF86XK_AudioNext,     		 spawn,          SHCMD("mpc next; pkill -RTMIN+11 dwmblocks") },
	{ 0,                       XF86XK_AudioPrev,     		 spawn,          SHCMD("mpc prev; pkill -RTMIN+11 dwmblocks") },
	{ 0,                       XF86XK_MonBrightnessUp,       spawn,          SHCMD("xbacklight -inc 5; pkill -RTMIN+9 dwmblocks") },
	{ 0,                       XF86XK_MonBrightnessDown,     spawn,          SHCMD("xbacklight -dec 5; pkill -RTMIN+9 dwmblocks") },

	
	/* { MODKEY,                       XK_y,      togglebar,      {0} }, */
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      pushdown,       {0} },
	{ MODKEY|ShiftMask,             XK_k,      pushup,         {0} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.02} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.02} },
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,          		     XK_semicolon, shiftviewclients, { .i = +1 } },
	{ MODKEY,             	        XK_apostrophe,  shiftviewclients, { .i = -1 } },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	/* { MODKEY,                       XK_space,  setlayout,      {0} }, */
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ControlMask,           XK_j,  	   moveresize,     {.v = "0x 40y 0w 0h" } },
	{ MODKEY|ControlMask,           XK_k,      moveresize,     {.v = "0x -40y 0w 0h" } },
	{ MODKEY|ControlMask,			XK_l,      moveresize,     {.v = "40x 0y 0w 0h" } },
	{ MODKEY|ControlMask,        	XK_h,      moveresize,     {.v = "-40x 0y 0w 0h" } },
	{ MODKEY|Mod1Mask, 	            XK_j,      moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|Mod1Mask,              XK_k,      moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|Mod1Mask,              XK_l,      moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|Mod1Mask,              XK_h,      moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_r,      quit,           {0} },
	{ MODKEY,	                	XK_g,      togglegaps,	   {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_h,      incrgaps,       {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_l,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
	{ MODKEY|ControlMask,           XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
	{ MODKEY,                       XK_u,      incrihgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_u,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_y,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask,              XK_u,      incrohgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_u,      incrovgaps,     {.i = -1 } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
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
