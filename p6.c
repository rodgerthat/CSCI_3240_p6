#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <dlfcn.h>

void* sub_function(void *arg);

int main(int argc,char *argv[]){

        alarm(60);

        pthread_t tdid;
        void *handle;
        char *error;
        int (*pthread_create)(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);

        int (*pthread_join)(pthread_t thread, void **value_ptr);

        long arg;

        //printf("argv[0] : %s \n", argv[0]);
        //printf("argv[1] : %s \n", argv[1]);
        //printf("argv[2] : %s \n", argv[2]);
        
        arg = atol(argv[1]);
        //printf("arg : %ld\n", arg);

        //printf("variable arg is at address: %p\n", (void*)&arg);

        // Dynamically load shared lib 
        handle = dlopen("/lib/x86_64-linux-gnu/libpthread.so.0",RTLD_LAZY);
        // error handling if dlopen cannot open lub
        if(!handle){
                //printf("Hello Error");
                fprintf(stderr,"%s\n",dlerror());
                exit(-1);
        }

        // dynamically get a pointer to create and join
        pthread_create = dlsym(handle,"pthread_create");
        pthread_join = dlsym(handle,"pthread_join");
        if ((error = dlerror()) != NULL) {
                fprintf(stderr, "%s\n", error);
                exit(1);
        }

        //printf("starting thread, arg = %ld\n", arg);
        //pthread_create(&tdid,NULL,sub,(void *)NULL);
        // create the thread and pass the sub function to it w/ the pointerto our arg
        pthread_create(&tdid,NULL,sub_function,(void *)arg);
        pthread_join(tdid,NULL);

        // error handling 
        if(dlclose(handle)<0){
                fprintf(stderr,"%s\n",dlerror());
                exit(-1);
        }
        return 0;
}

void* sub_function(void *arg){

        p6test(&arg);

        //long int inty = (long int) arg;
        //printf("exiting thread, arg = %ld\n", (long int)arg);
}
