/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const char font[]            = "Cousine for Powerline:size=10";
/*static const char font[]	    = "-misc-xbmicons-medium-r-normal--12-120-72-72-c-60-iso10646-1";*/


#define NUMCOLORS 15
static const char colors[NUMCOLORS][ColLast][9] = {
  // border foreground background
  { "#555555", "#5e646e", "#1d1f21" }, // 1 = normal (grey on black)
  { "#cccccc", "#c5c8c6", "#000000" }, // 2 = selected (white on black)
  { "#dc322f", "#1d1f21", "#73510d" }, // 3 = urgent (black on yellow)
  { "#cccccc", "#999999", "#1d1f21" }, // 4 = darkgrey on black (for glyphs)
  { "#aaaaaa", "#aaaaaa", "#282a2e" }, // 5 = black on darkgrey (for glyphs)
  { "#282a2e", "#c5c8c6", "#282a2e" }, // 6
  { "#282a2e", "#222222", "#c5c8c6" }, // 7
  { "#282a2e", "#de935f", "#c5c8c6" }, // 8 = red on black
  { "#282a2e", "#222222", "#de935f" }, // 9 = green on black
  { "#282a2e", "#ffffff", "#de935f" }, // a = orange on black
  { "#282a2e", "#81a2be", "#de935f" }, // b = yellow on darkgrey
  { "#282a2e", "#222222", "#81a2be" }, // c = blue on darkgrey
  { "#282a2e", "#8abeb7", "#81a2be" }, // d = magenta on darkgrey
  { "#282a2e", "#222222", "#8abeb7" }, // e = cyan on darkgrey
  { "#282a2e", "#c5c8c6", "#282a2e" }, // f
};


/* #bcbcbc = lys grå
 * #586e75 = koksgrå
 * #258bd2 = lys blå
 * #ffaf00 = orange
 * #585858 = mellem grå
 * #002236 = Mørke blå
 * #d7ff00 = snot grøn
 */


static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 0;        /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */
static const Bool showsystray       = False;     /* False means no systray */
static const char scratchpadname[]  = "Scratchpad";
static const unsigned int systrayspacing = 12;

static const char clock_fmt[] = "%d/%m %H:%M";

static const char plopensym[]	 = "";     /* powerline: left open glyph */
static const char plclosedsym[]	 = "";	    /* powerline: left closed glyph */
static const char plsystraysym[] = "";	    /* powerline: right closed glyph */

/* layout(s) */
static const float mfact      = 0.50;	/* factor of master area size [0.05..0.95] */
static const int nmaster      = 2;	/* number of clients in master area */
static const Bool resizehints = False;	/* True means respect size hints in tiled resizals */
#include "gaplessgrid.c"
static const Layout layouts[] = {
	/* symbol   gaps    arrange function */
	{ "[]=",    True,   tile },    /* first entry is default */
	{ "[M]",    False,  monocle },
	{ "><>",    False,  NULL },    /* no layout function means floating behavior */
	{ "G",	    False,  gaplessgrid },
};

/* tagging */
static Tag tags[] = {
	/* name     layout      mfact   nmaster */
	{ "web",   &layouts[0], -1,    -1 },
	{ "code",   &layouts[0], -1,    -1 },
	{ "term",   &layouts[0], -1,    -1 },
	{ "etc",    &layouts[0], -1,    -1 },
	{ "music",   &layouts[0], -1,    -1 },
};

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Chromium", NULL,       NULL,       1 << 3,       False,       -1 },
	{ "Skype",    NULL,       NULL,       0,	    True,	 -1 },
};

/* key definitions */
#define MODKEY Mod1Mask
#define WINKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenu[]	= { "dmenu_run", "-p", "$: ", "-fn", font, "-nb", "#282a2e", "-nf", "#c5c8c6", "-sb", "#222222", "-sf", "#888888", NULL };
static const char *scratchpad[] = { "st", "-g", "98x15", "-t", scratchpadname, "-e", "bash", NULL };
static const char *term[]	= { "xfce4-terminal" };
static const char *volup[]	= { "amixer", "-q", "set", "Master", "5%+", NULL };
static const char *voldown[]	= { "amixer", "-q", "set", "Master", "5%-", NULL };
static const char *volmute[]	= { "amixer", "-q", "set", "Master", "toggle", NULL };
static const char *lock[]	= { "slock", NULL };
static const char *suspend[]	= { "systemctl", "suspend", NULL };
static const char *play[]	= { "ncmpcpp", "toggle", NULL };
static const char *next[]	= { "ncmpcpp", "next", NULL };
static const char *prev[]	= { "ncmpcpp", "prev", NULL };

static Key keys[] = {
	/* modifier                 key        function        argument */
	{ MODKEY,		XK_p,			    spawn,          {.v = dmenu } },
	{ MODKEY,		XK_Return,		    spawn,          {.v = term } },
	{ 0,			XK_F12,			    togglescratch,  {.v = scratchpad } },
	{ 0,			XF86XK_AudioRaiseVolume,    spawn,	    {.v = volup } },
	{ 0,			XF86XK_AudioLowerVolume,    spawn,	    {.v = voldown } },
	{ 0,			XF86XK_AudioMute,	    spawn,	    {.v = volmute } },
	{ 0,			XF86XK_AudioPlay,	    spawn,	    {.v = play } },
	{ 0,			XF86XK_AudioNext,	    spawn,	    {.v = next } },
	{ 0,			XF86XK_AudioPrev,	    spawn,	    {.v = prev } },
	{ WINKEY,		XK_Escape,		    spawn,	    {.v = suspend } },
	{ WINKEY,		XK_l,			    spawn,	    {.v = lock } },
	{ MODKEY,		XK_b,			    togglebar,      {0} },
	{ MODKEY,		XK_j,			    focusstack,     {.i = +1 } },
	{ MODKEY,		XK_k,			    focusstack,     {.i = -1 } },
	{ MODKEY,		XK_i,			    incnmaster,     {.i = +1 } },
	{ MODKEY,		XK_d,			    incnmaster,     {.i = -1 } },
	{ MODKEY,		XK_period,		    setmfact,       {.f = -0.05} },
	{ MODKEY,		XK_minus,			    setmfact,       {.f = +0.05} },
	{ MODKEY,		XK_Return,		    zoom,           {0} },
	{ MODKEY,		XK_Tab,			    focusstack,     {.i = +1 } },
	{ MODKEY,		XK_q,			    killclient,     {0} },
	{ MODKEY,		XK_t,			    setlayout,      {.v = &layouts[0]} },
	{ MODKEY,		XK_f,			    setlayout,      {.v = &layouts[1]} },
	{ MODKEY,		XK_m,			    setlayout,      {.v = &layouts[2]} },
	{ MODKEY,		XK_g,			    setlayout,	    {.v = &layouts[3]} },
	{ MODKEY,		XK_space,		    setlayout,      {0} },
	{ MODKEY|ShiftMask,	XK_space,		    togglefloating, {0} },
	{ MODKEY,		XK_0,			    view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,	XK_0,			    tag,            {.ui = ~0 } },
	{ MODKEY,		XK_comma,		    focusmon,       {.i = -1 } },
	{ MODKEY,		XK_e,			    focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,	XK_comma,		    tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,	XK_period,		    tagmon,         {.i = +1 } },
	TAGKEYS(		XK_1,			    0)
	TAGKEYS(		XK_2,			    1)
	TAGKEYS(		XK_3,			    2)
	TAGKEYS(		XK_4,			    3)
	TAGKEYS(		XK_5,			    4)
	{ MODKEY|ShiftMask,	XK_q,			    quit,	    {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkClock, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
//	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = term } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
