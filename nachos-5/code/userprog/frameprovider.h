#ifndef FRAMEPROVIDER_H
#define FRAMEPROVIDER_H

#include "copyright.h"
#include "bitmap.h"
#include "filesys.h"
#include "synch.h"

class FrameProvider {
    public:
         FrameProvider (int numFrames);
        ~FrameProvider ();
        int  GetEmptyFrame();
        void ReleaseFrame(int numFrames);
        int  NumAvailFrame();

    private:
        int nFrames;
        BitMap * bitmap;
        Semaphore * semFrame;
};

#endif 
