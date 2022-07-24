static const char col_bg[]          = "#002b36";
static const char col_gray[]        = "#446f7a";
static const char col_white[]       = "#839496";
static const char col_border[]      = "#66d9ef";
static const char *colors[][3]      = {
[SchemeNorm]      = { col_gray,    col_bg,     col_bg     },
[SchemeSel]       = { col_white,   col_bg,     col_border },
[SchemeStatus]    = { col_white,   col_bg,   "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
[SchemeTagsSel]   = { col_white,   col_bg, "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
[SchemeTagsNorm]  = { col_gray,   col_bg,   "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
[SchemeInfoSel]   = { col_gray,   col_bg, "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
[SchemeInfoNorm]  = { col_gray,   col_bg,   "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};
