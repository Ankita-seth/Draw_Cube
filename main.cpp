#include "framework.h"

int WINAPI WinMain(HINSTANCE hInstance,    //Main windows function
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nShowCmd)
{
    Tutorial* tutorial = new Tutorial();
    if (tutorial)
    {
        //create the window
        if (!tutorial->InitializeWindow(hInstance, nShowCmd, tutorial->FullScreen))
        {
            MessageBox(0, L"Window Initialization - Failed",
                L"Error", MB_OK);
            return 1;
        }

        //initialize direct3d
        if (!tutorial->InitD3D())
        {
            MessageBox(0, L"Failed to initialize direct3d 12",
                L"Error", MB_OK);
            tutorial->Cleanup();
            return 1;
        }

        //start the main loop
        tutorial->mainloop();

        //we want to wait for the gpu to finish executing the command list before we start releasing everything
        tutorial->WaitForPreviousFrame();

        //close the fence event
        CloseHandle(tutorial->fenceEvent);

        //clean up everything
        tutorial->Cleanup();
    }
    delete tutorial;
    tutorial = NULL;
    return 0;
}