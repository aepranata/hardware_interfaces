/*
 * Copyright (C) 2021 The Android Open Source Project
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

package android.hardware.gnss.measurement_corrections;

/**
 * GNSS measurement corrections callback interface.
 *
 * @hide
 */
@VintfStability
interface IMeasurementCorrectionsCallback {
    /**
     * Flags to indicate supported measurement corrections capabilities
     *
     * Either the LOS_SATS or the EXCESS_PATH_LENGTH capability must be supported.
     */
    /**
     * Capability bit flag indicating that GNSS supports line-of-sight satellite identification
     * measurement corrections
     */
    const int CAPABILITY_LOS_SATS = 1 << 0;
    /**
     * Capability bit flag indicating that GNSS supports per satellite excess-path-length
     * measurement corrections
     */
    const int CAPABILITY_EXCESS_PATH_LENGTH = 1 << 1;
    /**
     * Capability bit flag indicating that GNSS supports reflecting planes measurement
     * corrections
     */
    const int CAPABILITY_REFLECTING_PLANE = 1 << 2;

    /**
     * Callback to inform framework the measurement correction specific capabilities of the GNSS
     * HAL implementation.
     *
     * The GNSS HAL must call this method immediately after the framework opens the measurement
     * corrections interface.
     *
     * @param capabilities A bit field of flags indicating the capabilities of measurement
     *         corrections.
     *        It is mandatory to support either LOS_STATS or EXCESS_PATH_LENGTH capability.
     */
    void setCapabilitiesCb(in int capabilities);
}
