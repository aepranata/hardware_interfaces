/*
 * Copyright (C) 2016 The Android Open Source Project
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

#ifndef WIFI_NAN_IFACE_H_
#define WIFI_NAN_IFACE_H_

#include <android-base/macros.h>
#include <android/hardware/wifi/1.6/IWifiNanIface.h>
#include <android/hardware/wifi/1.6/IWifiNanIfaceEventCallback.h>

#include "hidl_callback_util.h"
#include "wifi_iface_util.h"
#include "wifi_legacy_hal.h"

namespace android {
namespace hardware {
namespace wifi {
namespace V1_6 {
namespace implementation {
using namespace android::hardware::wifi::V1_0;
using namespace android::hardware::wifi::V1_2;
using namespace android::hardware::wifi::V1_4;
using namespace android::hardware::wifi::V1_6;

/**
 * HIDL interface object used to control a NAN Iface instance.
 */
class WifiNanIface : public V1_6::IWifiNanIface {
  public:
    WifiNanIface(const std::string& ifname, bool is_dedicated_iface,
                 const std::weak_ptr<legacy_hal::WifiLegacyHal> legacy_hal,
                 const std::weak_ptr<iface_util::WifiIfaceUtil> iface_util);
    // Refer to |WifiChip::invalidate()|.
    void invalidate();
    bool isValid();
    std::string getName();

    // HIDL methods exposed.
    Return<void> getName(getName_cb hidl_status_cb) override;
    Return<void> getType(getType_cb hidl_status_cb) override;
    Return<void> registerEventCallback(const sp<V1_0::IWifiNanIfaceEventCallback>& callback,
                                       registerEventCallback_cb hidl_status_cb) override;
    Return<void> getCapabilitiesRequest(uint16_t cmd_id,
                                        getCapabilitiesRequest_cb hidl_status_cb) override;
    Return<void> enableRequest(uint16_t cmd_id, const V1_0::NanEnableRequest& msg,
                               enableRequest_cb hidl_status_cb) override;
    Return<void> configRequest(uint16_t cmd_id, const V1_0::NanConfigRequest& msg,
                               configRequest_cb hidl_status_cb) override;
    Return<void> disableRequest(uint16_t cmd_id, disableRequest_cb hidl_status_cb) override;
    Return<void> startPublishRequest(uint16_t cmd_id, const V1_0::NanPublishRequest& msg,
                                     startPublishRequest_cb hidl_status_cb) override;
    Return<void> stopPublishRequest(uint16_t cmd_id, uint8_t sessionId,
                                    stopPublishRequest_cb hidl_status_cb) override;
    Return<void> startSubscribeRequest(uint16_t cmd_id, const V1_0::NanSubscribeRequest& msg,
                                       startSubscribeRequest_cb hidl_status_cb) override;
    Return<void> stopSubscribeRequest(uint16_t cmd_id, uint8_t sessionId,
                                      stopSubscribeRequest_cb hidl_status_cb) override;
    Return<void> transmitFollowupRequest(uint16_t cmd_id, const NanTransmitFollowupRequest& msg,
                                         transmitFollowupRequest_cb hidl_status_cb) override;
    Return<void> createDataInterfaceRequest(uint16_t cmd_id, const hidl_string& iface_name,
                                            createDataInterfaceRequest_cb hidl_status_cb) override;
    Return<void> deleteDataInterfaceRequest(uint16_t cmd_id, const hidl_string& iface_name,
                                            deleteDataInterfaceRequest_cb hidl_status_cb) override;
    Return<void> initiateDataPathRequest(uint16_t cmd_id,
                                         const V1_0::NanInitiateDataPathRequest& msg,
                                         initiateDataPathRequest_cb hidl_status_cb) override;
    Return<void> respondToDataPathIndicationRequest(
            uint16_t cmd_id, const V1_0::NanRespondToDataPathIndicationRequest& msg,
            respondToDataPathIndicationRequest_cb hidl_status_cb) override;
    Return<void> terminateDataPathRequest(uint16_t cmd_id, uint32_t ndpInstanceId,
                                          terminateDataPathRequest_cb hidl_status_cb) override;

    Return<void> registerEventCallback_1_2(const sp<V1_2::IWifiNanIfaceEventCallback>& callback,
                                           registerEventCallback_1_2_cb hidl_status_cb) override;
    Return<void> enableRequest_1_2(uint16_t cmd_id, const V1_0::NanEnableRequest& msg1,
                                   const V1_2::NanConfigRequestSupplemental& msg2,
                                   enableRequest_1_2_cb hidl_status_cb) override;
    Return<void> configRequest_1_2(uint16_t cmd_id, const V1_0::NanConfigRequest& msg1,
                                   const V1_2::NanConfigRequestSupplemental& msg2,
                                   configRequest_1_2_cb hidl_status_cb) override;
    Return<void> enableRequest_1_4(uint16_t cmd_id, const V1_4::NanEnableRequest& msg1,
                                   const V1_2::NanConfigRequestSupplemental& msg2,
                                   enableRequest_1_4_cb hidl_status_cb) override;
    Return<void> configRequest_1_4(uint16_t cmd_id, const V1_4::NanConfigRequest& msg1,
                                   const V1_2::NanConfigRequestSupplemental& msg2,
                                   configRequest_1_4_cb hidl_status_cb) override;
    Return<void> registerEventCallback_1_5(const sp<V1_5::IWifiNanIfaceEventCallback>& callback,
                                           registerEventCallback_1_5_cb hidl_status_cb) override;
    Return<void> enableRequest_1_5(uint16_t cmd_id, const V1_4::NanEnableRequest& msg1,
                                   const V1_5::NanConfigRequestSupplemental& msg2,
                                   enableRequest_1_5_cb hidl_status_cb) override;
    Return<void> configRequest_1_5(uint16_t cmd_id, const V1_4::NanConfigRequest& msg1,
                                   const V1_5::NanConfigRequestSupplemental& msg2,
                                   configRequest_1_5_cb hidl_status_cb) override;
    Return<void> getCapabilitiesRequest_1_5(uint16_t cmd_id,
                                            getCapabilitiesRequest_cb hidl_status_cb) override;
    Return<void> registerEventCallback_1_6(const sp<V1_6::IWifiNanIfaceEventCallback>& callback,
                                           registerEventCallback_1_6_cb hidl_status_cb) override;
    Return<void> initiateDataPathRequest_1_6(
            uint16_t cmd_id, const V1_6::NanInitiateDataPathRequest& msg,
            initiateDataPathRequest_1_6_cb hidl_status_cb) override;
    Return<void> respondToDataPathIndicationRequest_1_6(
            uint16_t cmd_id, const V1_6::NanRespondToDataPathIndicationRequest& msg,
            respondToDataPathIndicationRequest_1_6_cb hidl_status_cb) override;
    Return<void> enableRequest_1_6(uint16_t cmd_id, const V1_4::NanEnableRequest& msg1,
                                   const V1_6::NanConfigRequestSupplemental& msg2,
                                   enableRequest_1_6_cb hidl_status_cb) override;
    Return<void> configRequest_1_6(uint16_t cmd_id, const V1_4::NanConfigRequest& msg1,
                                   const V1_6::NanConfigRequestSupplemental& msg2,
                                   configRequest_1_6_cb hidl_status_cb) override;
    Return<void> startPublishRequest_1_6(uint16_t cmd_id, const V1_6::NanPublishRequest& msg,
                                         startPublishRequest_cb hidl_status_cb) override;

  private:
    // Corresponding worker functions for the HIDL methods.
    std::pair<WifiStatus, std::string> getNameInternal();
    std::pair<WifiStatus, IfaceType> getTypeInternal();
    WifiStatus registerEventCallbackInternal(const sp<V1_0::IWifiNanIfaceEventCallback>& callback);
    WifiStatus getCapabilitiesRequestInternal(uint16_t cmd_id);
    WifiStatus enableRequestInternal(uint16_t cmd_id, const V1_0::NanEnableRequest& msg);
    WifiStatus configRequestInternal(uint16_t cmd_id, const V1_0::NanConfigRequest& msg);
    WifiStatus disableRequestInternal(uint16_t cmd_id);
    WifiStatus startPublishRequestInternal(uint16_t cmd_id, const V1_0::NanPublishRequest& msg);
    WifiStatus stopPublishRequestInternal(uint16_t cmd_id, uint8_t sessionId);
    WifiStatus startSubscribeRequestInternal(uint16_t cmd_id, const V1_0::NanSubscribeRequest& msg);
    WifiStatus stopSubscribeRequestInternal(uint16_t cmd_id, uint8_t sessionId);
    WifiStatus transmitFollowupRequestInternal(uint16_t cmd_id,
                                               const NanTransmitFollowupRequest& msg);
    WifiStatus createDataInterfaceRequestInternal(uint16_t cmd_id, const std::string& iface_name);
    WifiStatus deleteDataInterfaceRequestInternal(uint16_t cmd_id, const std::string& iface_name);
    WifiStatus initiateDataPathRequestInternal(uint16_t cmd_id,
                                               const V1_0::NanInitiateDataPathRequest& msg);
    WifiStatus respondToDataPathIndicationRequestInternal(
            uint16_t cmd_id, const V1_0::NanRespondToDataPathIndicationRequest& msg);
    WifiStatus terminateDataPathRequestInternal(uint16_t cmd_id, uint32_t ndpInstanceId);

    WifiStatus registerEventCallback_1_2Internal(
            const sp<V1_2::IWifiNanIfaceEventCallback>& callback);
    WifiStatus enableRequest_1_2Internal(uint16_t cmd_id, const V1_0::NanEnableRequest& msg1,
                                         const V1_2::NanConfigRequestSupplemental& msg2);
    WifiStatus configRequest_1_2Internal(uint16_t cmd_id, const V1_0::NanConfigRequest& msg,
                                         const V1_2::NanConfigRequestSupplemental& msg2);
    WifiStatus enableRequest_1_4Internal(uint16_t cmd_id, const V1_4::NanEnableRequest& msg1,
                                         const V1_2::NanConfigRequestSupplemental& msg2);
    WifiStatus configRequest_1_4Internal(uint16_t cmd_id, const V1_4::NanConfigRequest& msg,
                                         const V1_2::NanConfigRequestSupplemental& msg2);
    WifiStatus registerEventCallback_1_5Internal(
            const sp<V1_5::IWifiNanIfaceEventCallback>& callback);
    WifiStatus enableRequest_1_5Internal(uint16_t cmd_id, const V1_4::NanEnableRequest& msg1,
                                         const V1_5::NanConfigRequestSupplemental& msg2);
    WifiStatus configRequest_1_5Internal(uint16_t cmd_id, const V1_4::NanConfigRequest& msg,
                                         const V1_5::NanConfigRequestSupplemental& msg2);
    WifiStatus getCapabilitiesRequest_1_5Internal(uint16_t cmd_id);
    WifiStatus registerEventCallback_1_6Internal(
            const sp<V1_6::IWifiNanIfaceEventCallback>& callback);

    WifiStatus enableRequest_1_6Internal(uint16_t cmd_id, const V1_4::NanEnableRequest& msg1,
                                         const V1_6::NanConfigRequestSupplemental& msg2);
    WifiStatus configRequest_1_6Internal(uint16_t cmd_id, const V1_4::NanConfigRequest& msg,
                                         const V1_6::NanConfigRequestSupplemental& msg2);
    WifiStatus startPublishRequest_1_6Internal(uint16_t cmd_id, const V1_6::NanPublishRequest& msg);
    WifiStatus initiateDataPathRequest_1_6Internal(uint16_t cmd_id,
                                                   const V1_6::NanInitiateDataPathRequest& msg);
    WifiStatus respondToDataPathIndicationRequest_1_6Internal(
            uint16_t cmd_id, const V1_6::NanRespondToDataPathIndicationRequest& msg);

    // all 1_0 and descendant callbacks
    std::set<sp<V1_0::IWifiNanIfaceEventCallback>> getEventCallbacks();
    // all 1_2 and descendant callbacks
    std::set<sp<V1_2::IWifiNanIfaceEventCallback>> getEventCallbacks_1_2();
    // all 1_5 and descendant callbacks
    std::set<sp<V1_5::IWifiNanIfaceEventCallback>> getEventCallbacks_1_5();
    // all 1_6 and descendant callbacks
    std::set<sp<V1_6::IWifiNanIfaceEventCallback>> getEventCallbacks_1_6();

    std::string ifname_;
    bool is_dedicated_iface_;
    std::weak_ptr<legacy_hal::WifiLegacyHal> legacy_hal_;
    std::weak_ptr<iface_util::WifiIfaceUtil> iface_util_;
    bool is_valid_;
    hidl_callback_util::HidlCallbackHandler<V1_0::IWifiNanIfaceEventCallback> event_cb_handler_;
    hidl_callback_util::HidlCallbackHandler<V1_2::IWifiNanIfaceEventCallback> event_cb_handler_1_2_;
    hidl_callback_util::HidlCallbackHandler<V1_5::IWifiNanIfaceEventCallback> event_cb_handler_1_5_;
    hidl_callback_util::HidlCallbackHandler<V1_6::IWifiNanIfaceEventCallback> event_cb_handler_1_6_;

    DISALLOW_COPY_AND_ASSIGN(WifiNanIface);
};

}  // namespace implementation
}  // namespace V1_6
}  // namespace wifi
}  // namespace hardware
}  // namespace android

#endif  // WIFI_NAN_IFACE_H_
