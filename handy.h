//
//  handy.h
//  HandyGraphic
//
//  Created by Takeshi Ogihara on 08/05/13.
//  Copyright Takeshi Ogihara 2008, 2015. All rights reserved.
//
//  Last Update: 2011-12-14 (version 0.5.4)
//  Last Update: 2015-03-24 (version 0.6.5)

#ifndef __HANDY_H__
#define __HANDY_H__

/*
 *  HGTypes.h
 *  HandyGraphic Library
 *
 *  Created by Takeshi Ogihara on 08/05/10.
 *  Copyright 2008 Takeshi Ogihara. All rights reserved.
 *  Original. Handy Graphic version 0.3 (Level 3)
 */
//  Last Update: 2011-12-14 (version 0.5.4)
//  Last Update: 2015-03-15 (version 0.6.4)

#ifndef HANDY_TYPES_H
#define HANDY_TYPES_H

#define HG_ERROR	(-1)
#define HG_SUCCESS	(0)

/* Handy Graphic version */
#define HG_LEVEL	2
#define HG_VERSION	0.6

/* Window ID */
#define HG_MAX_WINDOW_IDS    511
#define HG_WINDOW_ID_MASK    0x01FF
#define HG_WINDOW_ID_SHIFT   9         // 0xF..FFE00
#define HG_WINDOW_ID(x)      ((x) & HG_WINDOW_ID_MASK)
#define HG_LAYER_NO_MASK     0x01FF
#define HG_LAYER_NO(x)       (((x) >> HG_WINDOW_ID_SHIFT) & HG_LAYER_NO_MASK)
#define HG_IMAGE_TAG         0x0C0000  // b1100 + 9bit + 9bit
#define HG_IMAGE_MASK        0x03FFFF  // 18bit
#define HG_IS_IMAGE_ID(x)    (((x) & HG_IMAGE_TAG) != 0)
/* max windows */
#define HG_MAX_WINDOWS       127
#define HG_MAX_LAYERS        127
// Because "intset" type can hold 16x8 = 128 ids.

enum {
    HGL_clear = 0, HGL_remove, HGL_setVisible, HGL_move, HGL_copy
};

/* default window */
#define HG_DEF_WIDTH    400
#define HG_DEF_HEIGHT   400

/* colors */
typedef unsigned long hgcolor;
#define HG_WHITE	0xffffffUL
#define HG_BLACK	0x000000UL
#define HG_GRAY 	0x7f7f7fUL
#define HG_LGRAY	0xaaaaaaUL
#define HG_DGRAY	0x555555UL
#define HG_RED  	0xff0000UL
#define HG_GREEN	0x00ff00UL
#define HG_BLUE 	0x0000ffUL
#define HG_YELLOW	0xffff00UL
#define HG_PURPLE	0x7f007fUL
#define HG_CYAN 	0x00ffffUL
#define HG_ORANGE	0xff7f00UL
#define HG_PINK 	0xffc0cbUL
#define HG_MAGENTA	0xff00ffUL
#define HG_BROWN	0x996633UL
#define HG_SKYBLUE  0x89BDFFUL
#define HG_DRED     0x990000UL
#define HG_DGREEN   0x007e00UL
#define HG_DBLUE    0x000080UL
#define HG_CLEAR	0xFF000000UL

enum {
    HG_ColorDraw, HG_ColorFill, HG_CompositeMode
};

/* text cording */
#define HG_AVAILABLE_CODING \
	((1<<HG_UTF8_CODE)|(1<<HG_JIS_CODE)|(1<<HG_SJIS_CODE)|(1<<HG_EUCJP_CODE))
#define HG_UTF8_CODE     0	/* Unicode UTF-8 */
#define HG_JIS_CODE      1	/* JIS Kanji Code */
#define HG_SJIS_CODE     2	/* Shift JIS Kanji Code */
#define HG_EUCJP_CODE    3	/* Japanese EUC Kanji Code */
#define HG_NOTHING_CODE  4	/* not exists */
#define INVALID_CODE(x) \
	((x)<0 || (x)>=HG_NOTHING_CODE || (HG_AVAILABLE_CODING & (1<<(x)))==0)

/* fonts */
typedef int hgfont;
#define HG_T	0x00
#define HG_TI	0x01
#define HG_TB	0x02
#define HG_TBI	0x03
#define HG_H	0x10
#define HG_HI	0x11
#define HG_HB	0x12
#define HG_HBI	0x13
#define HG_C	0x20
#define HG_CI	0x21
#define HG_CB	0x22
#define HG_CBI	0x23
#define HG_M	0x30
#define HG_MI	0x31
#define HG_MB	0x32
#define HG_MBI	0x33
#define HG_G	0x40
#define HG_GI	0x41
#define HG_GB	0x42
#define HG_GBI	0x43
#define INVALID_FONTID(x)	((x)<0 || ((x)&0xf0)>=0x50 || ((x)&0xf)>=0x4)

/* event mask */
#define HG_NO_EVENT     0
#define HG_MOUSE_DOWN   ( 1 << 0 )
#define HG_MOUSE_UP     ( 1 << 1 )
#define HG_MOUSE_MOVE   ( 1 << 2 )
#define HG_MOUSE_DRAG   ( 1 << 3 )
#define HG_MOUSE_ENTER  ( 1 << 4 )
#define HG_MOUSE_EXIT   ( 1 << 5 )
#define HG_MOUSE_EVENT_MASK   0x3f
#define HG_KEY_DOWN     ( 1 << 6 )
#define HG_KEY_UP       ( 1 << 7 )
#define HG_KEY_EVENT_MASK     0xc0
#define HG_WINDOW_EVENT_MASK  0xff
#define HG_TIMER_FIRE   ( 1 << 8 )

/* modkey */
#define HG_SHIFT_KEY    ( 1 << 0 )
#define HG_CONTROL_KEY  ( 1 << 1 )
#define HG_OPTION_KEY   ( 1 << 2 )

/* Arrow Keys */
#define HG_U_ARROW	0xF700
#define HG_D_ARROW	0xF701
#define HG_L_ARROW	0xF702
#define HG_R_ARROW	0xF703

/* Mac OS X
 * NSUpArrowFunctionKey = 0xF700,
 * NSDownArrowFunctionKey = 0xF701,
 * NSLeftArrowFunctionKey = 0xF702,
 * NSRightArrowFunctionKey = 0xF703,
 */

typedef struct {
    int width;
    int height;
    char hasalpha;  // 0: NO, 1: with Alpha
} imageinfo;

#define HG_FLIP_NONE            0
#define HG_FLIP_HORIZONTAL      1
#define HG_FLIP_VERTICAL        2

/* drawing (NSCompositingOperation) */
enum {
    HGCompositeClear           = 0,
    HGCompositeCopy            = 1,
    HGCompositeSourceOver      = 2,
    HGCompositeSourceIn        = 3,
    HGCompositeSourceOut       = 4,
    HGCompositeSourceAtop      = 5,
    HGCompositeDestinationOver = 6,
    HGCompositeDestinationIn   = 7,
    HGCompositeDestinationOut  = 8,
    HGCompositeDestinationAtop = 9,
    HGCompositeXOR             = 10,
    HGCompositePlusDarker      = 11,
    HGCompositeHighlight       = 12,
    HGCompositePlusLighter     = 13
};
#define HG_BLEND_COPY     HGCompositeCopy
#define HG_BLEND_SOVER    HGCompositeSourceOver

#define HGFloat     float

/* event structure */
typedef struct {
    unsigned long type;
    HGFloat x;
    HGFloat y;
    int count;
    int wid;
    unsigned int modkey;
    unsigned int ch;
} hgevent;

#endif /* HANDY_TYPES_H */

#define __HG_inline   static inline __attribute__((always_inline))

/********** Support **********/
int HGCSetColor(int wid, hgcolor clr, int kind);
int HGCMoveTo(int wid, double x, double y, int flag);
int HGCCircle(int wid, double x, double y, double r, int fill, int stroke);
int HGCBox(int wid, double x, double y, double w, double h, int fill, int stroke);
int HGCOval(int wid, double x, double y,
            double r1, double r2, double a, int fill, int stroke);
int HGCRectangle(int wid, double x, double y,
                 double r1, double r2, double a, int fill, int stroke);
int HGCFan(int wid, double x, double y, double r,
           double a0, double a1, int fill, int stroke);
int HGCPolygon(int wid, int n,
               const double *xp, const double *yp, int fill, int stroke);
int HgAlert(const char *str,
            const char *btn1, const char *btn2, const char *btn3, ...);
hgevent *HgCFetchEvent(int block);
void HgSleep(double);

/********** Level 2 **********/
void HgScreenSize(double *width, double *height);
int HgWOpen(double x, double y, double w, double h);
int HgWClose(int wid);
void HgCloseAll(void);
int HgWGetSize(int wid, double *xp, double *yp);
#define HgGetSize(xp, yp)    HgWGetSize(0, xp, yp)
int HgWCoordinate(int wid, double sx, double sy, double scale);
void HgWCoordinateEnable(int wid, int flag);
void HgWTransWtoA(int wid, double wx, double wy, double *ax, double *ay);
void HgWTransAtoW(int wid, double ax, double ay, double *wx, double *wy);
#define HgWSetColor(wid, clr)     HGCSetColor(wid, clr, HG_ColorDraw)
#define HgWSetFillColor(wid, clr) HGCSetColor(wid, clr, HG_ColorFill)
int HgWClear(int wid);
int HgWSetWidth(int wid, double t);
#define HgWMoveTo(wid, x, y)    HGCMoveTo(wid, x, y, 0)
#define HgWLineTo(wid, x, y)    HGCMoveTo(wid, x, y, 1)
int HgWLine(int wid, double x0, double y0, double x1, double y1);
#define HgWCircle(wid, x, y, r)            HGCCircle(wid, x, y, r, 0, 1)
#define HgWCircleFill(wid, x, y, r, stk)   HGCCircle(wid, x, y, r, 1, stk)
#define HgWBox(wid, x, y, w, h)            HGCBox(wid, x, y, w, h, 0, 1)
#define HgWBoxFill(wid, x, y, w, h, stk)   HGCBox(wid, x, y, w, h, 1, stk)
#define HgWArc(wid, x, y, r, a0, a1)       HGCFan(wid, x, y, r, a0, a1, 0, 0)
#define HgFan(x, y, r, a0, a1)             HGCFan(0, x, y, r, a0, a1, 0, 1)
#define HgWFan(wid, x, y, r, a0, a1)       HGCFan(wid, x, y, r, a0, a1, 0, 1)
#define HgFanFill(x, y, r, a0, a1, stk)    HGCFan(0, x, y, r, a0, a1, 1, stk)
#define HgWFanFill(w, x, y, r, a0, a1, s)  HGCFan(w, x, y, r, a0, a1, 1, s)
#define HgPolygon(n, xp, yp)                 HGCPolygon(0, n, xp, yp, 0, 1)
#define HgWPolygon(wid, n, xp, yp)           HGCPolygon(wid, n, xp, yp, 0, 1)
#define HgPolygonFill(n, xp, yp, stroke)     HGCPolygon(0, n, xp, yp, 1, stroke)
#define HgWPolygonFill(wid, n, xp, yp, stk)  HGCPolygon(wid, n, xp, yp, 1, stk)
#define HgLines(n, xp, yp)         HGCPolygon(0, n, xp, yp, 0, 0)
#define HgWLines(wid, n, xp, yp)   HGCPolygon(wid, n, xp, yp, 0, 0)
int HgEncoding(int coding);
int HgWSetFont(int wid, hgfont font, double size);
int HgWText(int wid, double x, double y, const char *str, ...);
int HgWTextSize(int wid, double *wp, double *hp, const char *str, ...);
// int HgTextSize(double *wp, double *hp, const char *str, ...);
#define HgTextSize(wp,hp,...)		HgWTextSize(0,(wp),(hp),__VA_ARGS__)

int HgWSave(int wid, const char *str);
#define HgSave(str)    HgWSave(0, str)
int HgLSave(int lid, const char *str);

/* Image */
int HgImageLoad(const char *str);
int HgImageUnload(int gid);
int HgImageSize(int gid, double *xp, double *yp);
int HgImageDup(int gid, double scale, int flip);
int HgImageDupRect(int gid, double scale, int flip,
                   double sx, double sy, double sw, double sh);
int HgWImagePut(int wid, double x, double y, int gid, double scale, double a);
int HgWImageDraw(int wid, double dx, double dy, int gid);
int HgWImageDrawRect(int wid, double dx, double dy, double dw, double dh,
                     int gid, double sx, double sy, double sw, double sh);
#define HgImagePut(x, y, gid, scale, a)    HgWImagePut(0, x, y, gid, scale, a)
#define HgImageDraw(x, y, gid)    HgWImageDraw(0, x, y, gid)
#define HgImageDrawRect(dx, dy, dw, dh, gid, sx, sy, sw, sh) \
    HgWImageDrawRect(0, dx, dy, dw, dh, gid, sx, sy, sw, sh)

/********** Level 1 **********/
int HgOpen(double w, double h);
int HgClose(void);
#define HgCoordinate(sx, sy, scale)    HgWCoordinate(0, sx, sy, scale)
#define HgCoordinateEnable(flag)       HgWCoordinateEnable(0, flag)
#define HgTransWtoA(wx, wy, ax, ay)    HgWTransWtoA(0, wx, wy, ax, ay)
#define HgTransAtoW(ax, ay, wx, wy)    HgWTransAtoW(0, ax, ay, wx, wy)
hgcolor HgRGB(double r, double g, double b);
hgcolor HgGray(double g);
// hgcolor HgWebColor(const char *str); deprecated
__HG_inline hgcolor HgColorCode(unsigned int hex) { return (hgcolor)hex; }
#define HgSetColor(clr)        HGCSetColor(0, clr, HG_ColorDraw)
#define HgSetFillColor(clr)    HGCSetColor(0, clr, HG_ColorFill)
#define HgClear()         HgWClear(0)
#define HgSetWidth(t)     HgWSetWidth(0, t)
#define HgMoveTo(x, y)    HGCMoveTo(0, x, y, 0)
#define HgLineTo(x, y)    HGCMoveTo(0, x, y, 1)
#define HgLine(x0, y0, x1, y1)    HgWLine(0, x0, y0, x1, y1)
#define HgCircle(x, y, r)               HGCCircle(0, x, y, r, 0, 1)
#define HgCircleFill(x, y, r, stroke)   HGCCircle(0, x, y, r, 1, stroke)
#define HgBox(x, y, w, h)             HGCBox(0, x, y, w, h, 0, 1)
#define HgBoxFill(x, y, w, h, stk)    HGCBox(0, x, y, w, h, 1, stk)
#define HgArc(x, y, r, a0, a1)  HGCFan(0, x, y, r, a0, a1, 0, 0)
#define HgSetFont(font, size)   HgWSetFont(0, font, size)
#define HgText(x,y,...)		    HgWText(0,(x),(y),__VA_ARGS__)

/********** Level 3 **********/
#define HgRect(x, y, r1, r2, a)             HGCRectangle(0, x, y, r1, r2, a, 0, 1)
#define HgWRect(wid, x, y, r1, r2, a)       HGCRectangle(wid, x, y, r1, r2, a, 0, 1)
#define HgRectFill(x, y, r1, r2, a, s)      HGCRectangle(0, x, y, r1, r2, a, 1, s)
#define HgWRectFill(w, x, y, r1, r2, a, s)  HGCRectangle(w, x, y, r1, r2, a, 1, s)

#define HgOval(x, y, r1, r2, a)              HGCOval(0, x, y, r1, r2, a, 0, 1)
#define HgWOval(wid, x, y, r1, r2, a)        HGCOval(wid, x, y, r1, r2, a, 0, 1)
#define HgOvalFill(x, y, r1, r2, a, s)       HGCOval(0, x, y, r1, r2, a, 1, s)
#define HgWOvalFill(w, x, y, r1, r2, a, s)   HGCOval(w, x, y, r1, r2, a, 1, s)
int HgWSetFontByName(int wid, const char *fontname, double size);
#define HgSetFontByName(fontname, size)    HgWSetFontByName(0, fontname, size)
int HgWSetEventMask(int wid, unsigned int mask);
#define HgSetEventMask(mask)    HgWSetEventMask(0, mask)
unsigned int HgWGetEventMask(int wid);
#define HgGetEventMask()      HgWGetEventMask(0)
#define HgEvent()             HgCFetchEvent(1)
#define HgEventNonBlocking()  HgCFetchEvent(0)
int HgSetIntervalTimer(double t);
int HgSetAlarmTimer(double t);

int HgWSetTitle(int wid, const char *fmt, ...);
#define HgSetTitle(...)		HgWSetTitle(0, __VA_ARGS__);

/****** Layer ******/
int HgWAddLayer(int wid);
int HgWLayers(int wid);
int HgCOperateLayer(int wid, int op, int arg);
#define HgLRemove(lid)      HgCOperateLayer(lid, HGL_remove, 0)
#define HgLClear(lid)       HgCOperateLayer(lid, HGL_clear, 0)
#define HgLCopy(lid, other) HgCOperateLayer(lid, HGL_copy, other)
#define HgLShow(lid, flag)  HgCOperateLayer(lid, HGL_setVisible, flag)
int HgLSetVisible(int lid, int flag, ...);
#define HgLMove(lid, pos)   HgCOperateLayer(lid, HGL_move, pos)
#define HgWindowOfLayer(lid)    HG_WINDOW_ID(lid)
hgcolor HgRGBA(double r, double g, double b, double a);
hgcolor HgGrayA(double g, double a);
#define HgSetComposite(compo)   HGCSetColor(0, (hgcolor)(compo), HG_CompositeMode)
#define HgWSetComposite(wid, compo)   HGCSetColor(wid, (hgcolor)(compo), HG_CompositeMode)
int HgCPDFRecord(int lid, int flag);
#define HgLPDFRecord(lid)   HgCPDFRecord(lid, 1)
#define HgLPDFCancel(lid)   HgCPDFRecord(lid, 0)
int HgLPDFSave(int lid, const char *str);
int HgWPDFSave(int wid, const char *str);

typedef struct {
    int display;
    int hidden;
} doubleLayer;

doubleLayer HgWAddDoubleLayer(int wid);
int HgLSwitch(doubleLayer *dp);
int HgLRemoveDoubleLayer(doubleLayer dp);

/****** Sound ******/
typedef unsigned int  hgsound;
#define NoSound       ((hgsound)0)
hgsound HgSoundLoad(const char *path);
hgsound HgSoundWithName(const char *name);
void HgSoundPlay(hgsound sid);
void HgSoundVolume(hgsound sid, double volume, int loop);
void HgSoundStop(hgsound sid);
void HgSoundPause(hgsound sid);
void HgSoundResume(hgsound sid);
int HgSoundUnload(hgsound sid);
void HgBeep(void);

/****** Easy Use ******/
int HgWGetChar(int wid);
#define HgGetChar()    HgWGetChar(0)

/******* For Compatibility : __attribute__((deprecated(s))) *******/
#if defined(__has_feature) && defined(__has_attribute) && \
  __has_attribute(deprecated) && __has_feature(attribute_deprecated_with_message)
static int HgSetPaintColor(hgcolor clr)
    __attribute__((deprecated("Use HgSetFillColor instead")));
__HG_inline int HgSetPaintColor(hgcolor clr) {
    return HGCSetColor(0, clr, HG_ColorFill);
}

static int HgWSetPaintColor(int wid, hgcolor clr)
    __attribute__((deprecated("Use HgWSetFillColor instead")));
__HG_inline int HgWSetPaintColor(int wid, hgcolor clr) {
    return HGCSetColor(wid, clr, HG_ColorFill);
}

static int HgEventMask(unsigned int mask)
    __attribute__((deprecated("Use HgSetEventMask instead")));
__HG_inline int HgEventMask(unsigned int mask) {
    return HgWSetEventMask(0, mask);
}

static int HgWEventMask(int wid, unsigned int mask)
    __attribute__((deprecated("Use HgWSetEventMask instead")));
__HG_inline int HgWEventMask(int wid, unsigned int mask) {
    return HgWSetEventMask(wid, mask);
}

static int HgSetTimerInterval(double t)
__attribute__((deprecated("Use HgSetIntervalTimer instead")));
__HG_inline int HgSetTimerInterval(double t) {
    return HgSetIntervalTimer(t);
}

#else
# define  HgSetPaintColor   HgSetFillColor
# define  HgWSetPaintColor  HgWSetFillColor
# define  HgEventMask       HgSetEventMask
# define  HgWEventMask      HgWSetEventMask
#endif


#endif /* HANDY_H */
