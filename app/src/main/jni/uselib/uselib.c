//
// Created by kevin on 8/11/16.
//

#include <jni.h>
#include "../vendor/libjpeg-turbo/libjpeg-turbo-1.4.1/turbojpeg.h"

JNIEXPORT jlong JNICALL
Java_com_kevin_uselibjpegturbo_MainActivity_tjInitDecompress(JNIEnv *env, jobject instance) {

    // TODO
    long add = (long) tjInitDecompress();
    return add;

}

JNIEXPORT jint JNICALL
Java_com_kevin_uselibjpegturbo_MainActivity_tjDecompressHeader2(JNIEnv *env, jobject instance,
                                                                jlong handle, jbyteArray jpegBits_,
                                                                jint jpegBitsLen) {
    jbyte *real_jpegBuf = (*env)->GetByteArrayElements(env, jpegBits_, 0);
    if (!real_jpegBuf) return -1;
    //jsize length = (*env)->GetArrayLength(env, real_jpegBuf);

    /*for (i = 0; i < length; i++) {
        sum += inCArray[i];
    }*/

    int width, height, jpegSubsamp;
    int ret =  tjDecompressHeader2((tjhandle)handle,
                                   (unsigned char *)real_jpegBuf, (unsigned long)jpegBitsLen, &width, &height,
                                   &jpegSubsamp);
    if(ret!=0) {
        return 0;
    }

    // ok, so pack width and height together
    return width<<16 | height;
}

JNIEXPORT void JNICALL
Java_com_kevin_uselibjpegturbo_MainActivity_tjDecompress2(JNIEnv *env, jobject instance,
                                                          jlong handle, jbyteArray jpegBits_,
                                                          jint jpegBitsLen, jintArray outbuffer_,
                                                          jint width, jint pitch, jint height,
                                                          jint pixelFormat, jint flags) {
    jbyte *real_jpegBuf = (*env)->GetByteArrayElements(env, jpegBits_, 0);
    if (!real_jpegBuf) return;
    jint *real_dstBuf = (*env)->GetIntArrayElements(env, outbuffer_, 0);
    if (!real_dstBuf) return;

    jsize length = (*env)->GetArrayLength(env, jpegBits_);
    tjDecompress2((tjhandle)handle,
                  (unsigned char *)real_jpegBuf, (unsigned long)jpegBitsLen, (unsigned char *)real_dstBuf,
                  width, pitch, height, pixelFormat, flags);
}

JNIEXPORT void JNICALL
Java_com_kevin_uselibjpegturbo_MainActivity_tjDestroy(JNIEnv *env, jobject instance, jlong handle) {

    // TODO
    tjDestroy((tjhandle)handle);
}