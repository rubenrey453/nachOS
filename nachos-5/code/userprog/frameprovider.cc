#include <time.h>
#include "frameprovider.h"
#include "system.h"

FrameProvider::FrameProvider (int numFrames) {
    this->bitmap = new BitMap(numFrames);
    this->semFrame = new Semaphore("semFrame", 1);
}

FrameProvider::~FrameProvider () {
    delete bitmap;
}

void FrameProvider::ReleaseFrame(int numFrames) {
    this->semFrame->P();
    this->bitmap->Clear(numFrames);
    this->semFrame->V();
}

int FrameProvider::GetEmptyFrame() {
    this->semFrame->P();
    int myFrame = -1;
    int check =0;
    // check any frames available
    check = this->bitmap->NumClear();
    DEBUG ('t'," (I) :Available clear bits %d\n",check);
    if (check > 0){
      myFrame = this->bitmap->Find();
    }
    else{
      DEBUG ('t'," (E) : No free frames to return, retval : -1\n");
   }
    this->semFrame->V();
    return myFrame;
}

int FrameProvider::NumAvailFrame()
{
	return this->bitmap->NumClear();
}
