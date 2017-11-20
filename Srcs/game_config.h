/*
Ahmed Al Shebli
*/

#include <QtCore>

#define frameRate 60
#define displyFrameRate false
#define gameName "Kout"

/*****************/
// for the setting, until the stars like the above, just comment any feature to disable

/* This setting is used to switch openGL on and Off on windows, and to switch to simulator and windows, this will automatically be off if the system doesn't support openGL, switch off the first one for windows and simulator, the second one is for all other OSes including mobile devices */


#ifdef WIN32
//#ifdef QT_NO_DEBUG
#define useOpenGL
//#endif
#else
#define useOpenGL
#endif

#ifdef Q_OS_MAC64
#define COMPUTER
#endif
#ifdef Q_OS_WIN
#define COMPUTER
#endif

/* If you like to use simulator use full screen, use win32W and win32H to specify width and height if not full screen */
//#define fullScreen


/*****************/
// E6 = 640 x 480 pixels
// ipad = 1024 x 768 pixels
// N900 = 800 x 480 pixels

#define win32W 1024
#define win32H 768


/**************************************************************************/
/*Pixmap cache limit, this setting is in MB and it's for both svg and pngs*/
/**************************************************************************/

#ifdef COMPUTER
#define pixmapCacheKey 100
#else
#ifdef Q_OS_SYMBIAN
#define pixmapCacheKey 20
#else
#define pixmapCacheKey 100
#endif
#endif

/**************************************************************************/
/*   OpenGL Settings, default settings are set to give best performance   */
/**************************************************************************/

/**************************************************************************/
/*    make openGL Alpha false to improve performance on mobile devices    */
/**************************************************************************/

#define openGLAlpha false
#define openGLdoubleBuffering true
#define openGLdepthBuffer true
