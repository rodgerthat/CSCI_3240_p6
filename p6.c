#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <dlfcn.h>

void* sub(void *arg);

int main(int argc,char *argv[]){

        pthread_t tdid;
        void *handle;
        char *error;
        int (*pthread_create)(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);

        int (*pthread_join)(pthread_t thread, void **value_ptr);

        long int arg;

        //printf("argv[0] : %s \n", argv[0]);
        //printf("argv[1] : %s \n", argv[1]);
        //printf("argv[2] : %s \n", argv[2]);
        //
        
        arg = atoi(argv[1]);
        //printf("arg : %ld\n", arg);

        //printf("variable arg is at address: %p\n", (void*)&arg);

        // Dynamically load shared lib 
        handle = dlopen("/lib/x86_64-linux-gnu/libpthread.so.0",RTLD_LAZY);
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

        printf("starting thread, arg = %ld\n", arg);
        //pthread_create(&tdid,NULL,sub,(void *)NULL);
        // create the thread and pass the sub function to it w/ the pointerto our arg
        //pthread_create(&tdid,NULL,sub,(void *)arg);
        pthread_create(&tdid,NULL,p6test,(void *)arg);
        pthread_join(tdid,NULL);

        if(dlclose(handle)<0){
                fprintf(stderr,"%s\n",dlerror());
                exit(-1);
        }
        return 0;
}

void* sub(void *arg){
        //printf("thread is inside sub arg = %p\n", arg);
        //printf("exiting thread, arg = %ld\n", *arg);
        //printf("\nlVptr[60 ] is  %d \n", *(int*)lVptr);
        //printf("exiting thread, arg = %d\n", *(int*)arg);
        long int inty = (long int) arg;
        printf("exiting thread, arg = %ld\n", inty);
}
