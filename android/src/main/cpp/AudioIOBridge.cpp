#include <jni.h>
#include <string>
#include <AndroidIO/SuperpoweredAndroidAudioIO.h>
#include <SuperpoweredMixer.h>
#include <SuperpoweredSimple.h>
#include <malloc.h>

static SuperpoweredAndroidAudioIO *audioIO;
static SuperpoweredStereoMixer *mixer;

static float *floatBuffer;

static float inputLevels[8] = { 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
static float outputLevels[2] = { 1.0f, 1.0f };

static bool audioProcessing (
        void * __unused clientdata,
        short int *audio,
        int numberOfFrames,
        int __unused samplerate
) {
    SuperpoweredShortIntToFloat(audio, floatBuffer, (unsigned int)numberOfFrames);

    float *inputs[4] = { floatBuffer, NULL, NULL, NULL };
    float *outputs[2] = { floatBuffer, NULL };

    mixer->process(inputs, outputs, inputLevels, outputLevels, NULL, NULL, (unsigned int)numberOfFrames);
    SuperpoweredFloatToShortInt(outputs[0], audio, (unsigned int)numberOfFrames);
    return true;
}

// StartAudio - Start audio engine.
extern "C" JNIEXPORT void
Java_com_reactlibrary_superpowerediobridge_RNSuperpoweredIoBridgeModule_StartAudio (
        JNIEnv * __unused env,
        jobject  __unused obj,
        jint samplerate,
        jint buffersize
) {
    floatBuffer = (float *)malloc(sizeof(float) * 2 * buffersize);

    audioIO = new SuperpoweredAndroidAudioIO (
            samplerate,
            buffersize,
            true,
            true,
            audioProcessing,
            NULL,
            -1,
            -1,
            buffersize * 2
    );

    mixer = new SuperpoweredStereoMixer();
}

// StopAudio - Stop audio engine and free resources.
extern "C" JNIEXPORT void
Java_com_reactlibrary_superpowerediobridge_RNSuperpoweredIoBridgeModule_StopAudio (
        JNIEnv * __unused env,
        jobject __unused obj
) {
    delete audioIO;
    free(floatBuffer);
}

// SetPanning
extern "C" JNIEXPORT void
Java_com_reactlibrary_superpowerediobridge_RNSuperpoweredIoBridgeModule_SetPanning (
        JNIEnv * __unused env,
        jobject  __unused obj,
        jfloat left,
        jfloat right
) {
    outputLevels[0] = left;
    outputLevels[1] = right;
}

// onBackground - Put audio processing to sleep.
extern "C" JNIEXPORT void
Java_com_reactlibrary_superpowerediobridge_RNSuperpoweredIoBridgeModule_onBackground (
        JNIEnv * __unused env,
        jobject __unused obj
) {
    audioIO->onBackground();
}

// onForeground - Resume audio processing.
extern "C" JNIEXPORT void
Java_com_reactlibrary_superpowerediobridge_RNSuperpoweredIoBridgeModule_onForeground (
        JNIEnv * __unused env,
        jobject __unused obj
) {
    audioIO->onForeground();
}
