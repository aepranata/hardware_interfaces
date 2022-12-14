/*
 * Copyright (C) 2022 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AUTOMOTIVE_EVS_VTS_FRAMEHANDLER_H
#define AUTOMOTIVE_EVS_VTS_FRAMEHANDLER_H

#include <aidl/android/hardware/automotive/evs/BnEvsCameraStream.h>
#include <aidl/android/hardware/automotive/evs/EvsEventDesc.h>
#include <aidl/android/hardware/automotive/evs/IEvsCamera.h>
#include <aidl/android/hardware/automotive/evs/IEvsDisplay.h>

#include <mutex>
#include <queue>

/*
 * FrameHandler:
 * This class can be used to receive camera imagery from an IEvsCamera implementation.  Given an
 * IEvsDisplay instance at startup, it will forward the received imagery to the display,
 * providing a trivial implementation of a rear vew camera type application.
 * Note that the video frames are delivered on a background thread, while the control interface
 * is actuated from the applications foreground thread.
 */
class FrameHandler : public ::aidl::android::hardware::automotive::evs::BnEvsCameraStream {
  public:
    enum BufferControlFlag {
        eAutoReturn,
        eNoAutoReturn,
    };

    FrameHandler(
            const std::shared_ptr<::aidl::android::hardware::automotive::evs::IEvsCamera>& pCamera,
            const ::aidl::android::hardware::automotive::evs::CameraDesc& cameraInfo,
            const std::shared_ptr<::aidl::android::hardware::automotive::evs::IEvsDisplay>&
                    pDisplay,
            BufferControlFlag mode = eAutoReturn);
    virtual ~FrameHandler() {
        if (mCamera != nullptr) {
            /* shutdown a camera explicitly */
            shutdown();
        }
    }

    void shutdown();
    bool startStream();
    void asyncStopStream();
    void blockingStopStream();
    bool returnHeldBuffer();
    bool isRunning();
    void waitForFrameCount(unsigned frameCount);
    bool waitForEvent(const ::aidl::android::hardware::automotive::evs::EvsEventDesc& aTargetEvent,
                      ::aidl::android::hardware::automotive::evs::EvsEventDesc& aReceivedEvent,
                      bool ignorePayload = false);
    void getFramesCounters(unsigned* received, unsigned* displayed);
    void getFrameDimension(unsigned* width, unsigned* height);

  private:
    // Methods from ::aidl::android::hardware::automotive::evs::IEvsCameraStream follow.
    ::ndk::ScopedAStatus deliverFrame(
            const std::vector<::aidl::android::hardware::automotive::evs::BufferDesc>& buffer)
            override;
    ::ndk::ScopedAStatus notify(
            const ::aidl::android::hardware::automotive::evs::EvsEventDesc& event) override;

    // Local implementation details
    bool copyBufferContents(
            const ::aidl::android::hardware::automotive::evs::BufferDesc& tgtBuffer,
            const ::aidl::android::hardware::automotive::evs::BufferDesc& srcBuffer);
    const char* eventToString(const ::aidl::android::hardware::automotive::evs::EvsEventType aType);

    std::shared_ptr<::aidl::android::hardware::automotive::evs::IEvsCamera> mCamera;
    ::aidl::android::hardware::automotive::evs::CameraDesc mCameraInfo;
    std::shared_ptr<::aidl::android::hardware::automotive::evs::IEvsDisplay> mDisplay;
    BufferControlFlag mReturnMode;

    // Since we get frames delivered to us asynchronously via the IEvsCameraStream interface,
    // we need to protect all member variables that may be modified while we're streaming
    // (ie: those below)
    std::mutex mLock;
    std::mutex mEventLock;
    std::condition_variable mEventSignal;
    std::condition_variable mFrameSignal;
    std::queue<std::vector<::aidl::android::hardware::automotive::evs::BufferDesc>> mHeldBuffers;

    bool mRunning = false;
    unsigned mFramesReceived = 0;   // Simple counter -- rolls over eventually!
    unsigned mFramesDisplayed = 0;  // Simple counter -- rolls over eventually!
    unsigned mFrameWidth = 0;
    unsigned mFrameHeight = 0;
    ::aidl::android::hardware::automotive::evs::EvsEventDesc mLatestEventDesc;
};

#endif  // AUTOMOTIVE_EVS_VTS_FRAMEHANDLER_H
