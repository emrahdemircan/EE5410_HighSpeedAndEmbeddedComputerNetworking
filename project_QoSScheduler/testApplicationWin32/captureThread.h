//---------------------------------------------------------------------------

#ifndef captureThreadH
#define captureThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class captureThread : public TThread
{
        typedef struct tagTHREADNAME_INFO
        {
                DWORD dwType;     // must be 0x1000
                LPCSTR szName;    // pointer to name (in user addr space)
                DWORD dwThreadID; // thread ID (-1=caller thread)
                DWORD dwFlags;    // reserved for future use, must be zero
        } THREADNAME_INFO;
private:
        void SetName();
protected:
        void __fastcall Execute();
public:
        __fastcall captureThread(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
