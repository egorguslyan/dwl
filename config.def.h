/* appearance */
static const int sloppyfocus        = 1;  /* focus follows mouse */
static const unsigned int borderpx  = 1;  /* border pixel of windows */
static const int lockfullscreen     = 1;  /* 1 will force focus on the fullscreen window */
static const float rootcolor[]      = {0.3, 0.3, 0.3, 1.0};
static const float bordercolor[]    = {0.5, 0.5, 0.5, 1.0};
static const float floatcolor[]     = {0.5, 0.5, 0.5, 1.0};
static const float focuscolor[]     = {1.0, 0.0, 0.0, 1.0};
static const int smartborders       = 1;
static const char cursortheme[]     = "\0"; /* theme from /usr/share/cursors/xorg-x11 */
static const unsigned int cursize   = 24;

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* app_id     title       tags mask     switchtotag     isfloating   monitor	x		y		width	height */
    /* examples:
    { "Gimp",     NULL,       0,            0,              1,          -1,         0,      0,      500,    400 },
    */
    { "firefox",  NULL,       1 << 8,       1,              0,          -1,         200,    100,    0,      0 },
    /* x, y, width, heigh are floating only
    * When x or y == 0 the client is placed at the center of the screen,
    * when width or height == 0 the default size of the client is used*/
};

/* layout(s) */
static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },
    { "><>",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
    { "TTT",      bstack },
    { "===",      bstackhoriz },
    { "[@]",      spiral },
    { "[\\]",     dwindle },
    { "###",      gaplessgrid },
    { "HHH",      grid },
    { "|v|",      vertile },
    { NULL,       NULL },
};

/* monitors */
static const MonitorRule monrules[] = {
    /* name       mfact nmaster scale layout       rotate/reflect x y resx resy rate adaptive*/
    /* example of a HiDPI 4K laptop monitor at 120Hz:
    { "eDP-1",    0.5,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL, 0, 0, 3840, 2160, 120.000, 1 },
    */
    /* defaults */
    { NULL,       0.55, 1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL, 0, 0, 0, 0, 0, 0 },
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
    /* can specify fields: rules, model, layout, variant, options */
    /* example:
    .options = "ctrl:nocaps,compose:ralt",
    */
    .options = "",
};

/* gb will be set the first time togglekblayout is called, then us.. it is
 * recommended to set the same layout in position 0 of kblayouts and in
 * xkb_rules */
static const char *kblayouts[] = {"us", "gb"};

/* numlock and capslock */
static const int numlock = 0;
static const int capslock = 0;

static const int repeat_rate = 25;
static const int repeat_delay = 600;

/* Trackpad */
static const int tap_to_click = 1;
static const int natural_scrolling = 0;

static const int cursor_timeout = 5;

/* Autostart */
static const char *const autostart[] = {
    "sh", "-c", "swaybg --image /xap/local/background", NULL,
    NULL /* terminate */
};

/* If you want to use the windows key change this to WLR_MODIFIER_LOGO */
#define MODKEY WLR_MODIFIER_ALT
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
    { MODKEY|WLR_MODIFIER_CTRL,  KEY,            toggleview,      {.ui = 1 << TAG} }, \
    { MODKEY|WLR_MODIFIER_SHIFT, KEY,           tag,             {.ui = 1 << TAG} }, \
    { MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,KEY,toggletag, {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[] = { "alacritty", NULL };
static const char *menucmd[] = { "bemenu-run", NULL };

static const Key keys[] = {
    /* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
    /* modifier                  key                 function        argument */
    { MODKEY,                    Key_p,          spawn,          {.v = menucmd} },
    { MODKEY|WLR_MODIFIER_SHIFT, Key_Return,     spawn,          {.v = termcmd} },
    { MODKEY,                    Key_j,          focusstack,     {.i = +1} },
    { MODKEY,                    Key_k,          focusstack,     {.i = -1} },
    { MODKEY|WLR_MODIFIER_SHIFT, Key_j,          movestack,      {.i = +1} },
    { MODKEY|WLR_MODIFIER_SHIFT, Key_k,          movestack,      {.i = -1} },
    { MODKEY|WLR_MODIFIER_SHIFT, Key_m,			 focusmaster,	 {0} },
    { MODKEY,                    Key_i,          incnmaster,     {.i = +1} },
    { MODKEY,                    Key_d,          incnmaster,     {.i = -1} },
    { MODKEY,                    Key_h,          setmfact,       {.f = -0.05} },
    { MODKEY,                    Key_l,          setmfact,       {.f = +0.05} },
    { MODKEY,                    Key_Return,     zoom,           {0} },
    { MODKEY,                    Key_Tab,        view,           {0} },
    { MODKEY|WLR_MODIFIER_SHIFT, Key_c,          killclient,     {0} },
    { MODKEY,                    Key_t,          setlayout,      {.v = &layouts[0]} },
    { MODKEY,                    Key_f,          setlayout,      {.v = &layouts[1]} },
    { MODKEY,                    Key_m,          setlayout,      {.v = &layouts[2]} },
    { MODKEY|WLR_MODIFIER_CTRL,  Key_comma,      cyclelayout,    {.i = -1 } },
    { MODKEY|WLR_MODIFIER_CTRL,  Key_period,     cyclelayout,    {.i = +1 } },
    { MODKEY,                    Key_space,      togglekblayout, {0} },
    { MODKEY|WLR_MODIFIER_SHIFT, Key_space,      togglefloating, {0} },
    { MODKEY,                    Key_e,         togglefullscreen, {0} },
    { MODKEY,                    Key_0,          view,           {.ui = ~0} },
    { MODKEY|WLR_MODIFIER_SHIFT, Key_0,          tag,            {.ui = ~0} },
    { MODKEY,                    Key_comma,      focusmon,       {.i = WLR_DIRECTION_LEFT} },
    { MODKEY,                    Key_period,     focusmon,       {.i = WLR_DIRECTION_RIGHT} },
    { MODKEY|WLR_MODIFIER_SHIFT, Key_comma,      tagmon,         {.i = WLR_DIRECTION_LEFT} },
    { MODKEY|WLR_MODIFIER_SHIFT, Key_period,     tagmon,         {.i = WLR_DIRECTION_RIGHT} },
    { MODKEY,                    Key_Left,       shiftview,      { .i = -1 } },
    { MODKEY,                    Key_Right,      shiftview,      { .i = 1 } },
    { MODKEY|WLR_MODIFIER_SHIFT, Key_q,          quit,           {0} },
    TAGKEYS( Key_1, 0 ),
    TAGKEYS( Key_2, 1 ),
    TAGKEYS( Key_3, 2 ),
    TAGKEYS( Key_4, 3 ),
    TAGKEYS( Key_5, 4 ),
    TAGKEYS( Key_6, 5 ),
    TAGKEYS( Key_7, 6 ),
    TAGKEYS( Key_8, 7 ),
    TAGKEYS( Key_9, 8 ),

    /* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
    { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT, Key_BackSpace, quit, {0} },
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,Key_F##n, chvt, {.ui = (n)} }
    CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
    CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
    { MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
    { MODKEY, BTN_MIDDLE, togglefloating, {0} },
/*	{ MODKEY, BTN_MIDDLE, moveresize,     {.ui = Curmfact} },	*/
    { MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
};
