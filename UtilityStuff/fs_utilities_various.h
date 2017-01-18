#ifndef FS_UTILITIESSTRING
#define FS_UTILITIESSTRING

#include <QString>

//various utility and helper functions
//CHS 13JAN2017


// a sleep function called delay(ms)

#if defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(__WINDOWS__) || defined(__TOS_WIN__)

  #include <windows.h>

  inline void delay( unsigned long ms )
    {
    Sleep( ms );
    }

#else  /* presume POSIX */

  #include <unistd.h>

  inline void delay( unsigned long ms )
    {
    usleep( ms * 1000 );
    }

#endif


#endif // FS_UTILITIESSTRING

