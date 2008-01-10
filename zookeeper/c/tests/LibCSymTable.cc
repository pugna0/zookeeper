#include "LibCSymTable.h" 

#define LOAD_SYM(sym) \
    sym=(sym##_sig)dlsym(handle,#sym); \
    assert("Unable to load "#sym" from libc"&&sym)      
    

LibCSymTable& LibCSymTable::instance(){
    static LibCSymTable tbl;
    return tbl;
}

//******************************************************************************
// preload original libc symbols
LibCSymTable::LibCSymTable()
{
    void* handle=getHandle();
    LOAD_SYM(gethostbyname);
    LOAD_SYM(calloc);
    LOAD_SYM(realloc);
    LOAD_SYM(free);
    LOAD_SYM(random);
    LOAD_SYM(srandom);
    LOAD_SYM(printf);
    LOAD_SYM(socket);
    LOAD_SYM(close);
    LOAD_SYM(getsockopt);
    LOAD_SYM(setsockopt);
    LOAD_SYM(fcntl);
    LOAD_SYM(connect);
    LOAD_SYM(send);
    LOAD_SYM(recv);
    LOAD_SYM(select);
    LOAD_SYM(gettimeofday);
#ifdef THREADED
    LOAD_SYM(pthread_create);
    LOAD_SYM(pthread_detach);
    LOAD_SYM(pthread_cond_broadcast);
    LOAD_SYM(pthread_cond_destroy);
    LOAD_SYM(pthread_cond_init);
    LOAD_SYM(pthread_cond_signal);
    LOAD_SYM(pthread_cond_timedwait);
    LOAD_SYM(pthread_cond_wait);
    LOAD_SYM(pthread_join);
    LOAD_SYM(pthread_mutex_destroy);
    LOAD_SYM(pthread_mutex_init);
    LOAD_SYM(pthread_mutex_lock);
    LOAD_SYM(pthread_mutex_trylock);
    LOAD_SYM(pthread_mutex_unlock);
#endif
}

void* LibCSymTable::getHandle(){
    static void* handle=0;
    if(!handle){
#ifdef __CYGWIN__
        handle=dlopen("cygwin1.dll",RTLD_LAZY);
        assert("Unable to dlopen global sym table"&&handle);
#else
        handle=RTLD_NEXT;
#endif
    }
    return handle;
}
