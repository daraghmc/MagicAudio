#ifndef _MAAUDIO_MCR
#define _MAAUDIO_MCR 

#define MAAUDIO_CLAMP(value, floor, ceiling ) \
    if ( (value) < (floor) ) \
        (value) = (floor); \
    else if ( (value) > (ceiling) ) \
        (value) = (ceiling);
        
#endif // _MAAUDIO_MCR

