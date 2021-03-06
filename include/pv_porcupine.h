/*
    Copyright 2018 Picovoice Inc.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

            http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef PV_PORCUPINE_H
#define PV_PORCUPINE_H

#include <stdbool.h>
#include <stdint.h>

#include "picovoice.h"

/**
 * Forward declaration for keyword spotting object (a.k.a. porcupine).
 * The object detects utterances of a given keyword within incoming stream of audio in real-time.
 * It processes incoming audio in consecutive frames (chucks) and for each frame emits result of detecting the keyword
 * ending at that frame. The number of samples per frame can be attained by calling 'pv_porcupine_frame_length()'.
 * The incoming audio needs to have a sample rate equal to 'pv_sample_rate()' and be 16-bit linearly-encoded. Furthermore,
 * porcupine operates on single channel audio.
 */
typedef struct pv_porcupine_object pv_porcupine_object_t;

/**
 * Constructor.
 *
 * @param model_file_path Absolute path to file containing model parameters.
 * @param keyword_file_path Absolute path to keyword file.
 * @param sensitivity Sensitivity for detecting keyword. It should be a floating-point number within
 * [0, 1]. A higher sensitivity value results in fewer misses at the cost of increasing the false alarm rate.
 * @param object[out] Constructed keyword spotting object.
 * @return Status code. Returns 'PV_STATUS_INVALID_ARGUMENT', 'PV_STATUS_OUT_OF_MEMORY', or 'PV_STATUS_IO_ERROR' on
 * failure.
 */
pv_status_t pv_porcupine_init(
        const char *model_file_path,
        const char *keyword_file_path,
        float sensitivity,
        pv_porcupine_object_t **object);

/**
 * Destructor.
 *
 * @param object Keyword spotting object.
 */
void pv_porcupine_delete(pv_porcupine_object_t *object);

/**
 * Monitors incoming audio stream for a given keyword.
 *
 * @param object Keyword spotting object.
 * @param pcm A frame of audio samples. The number of samples per frame can be attained by calling
 * 'pv_porcupine_frame_length()'. The incoming audio needs to have a sample rate equal to 'pv_sample_rate()' and be 16-bit
 * linearly-encoded. Furthermore, porcupine operates on single channel audio.
 * @param result[out] Flag indicating if the keyword has been observed ending at the current frame.
 * @return Status code. Returns 'PV_STATUS_INVALID_ARGUMENT' on failure.
 */
pv_status_t pv_porcupine_process(pv_porcupine_object_t *object, const int16_t *pcm, bool *result);

/**
 * Getter for version string.
 *
 * @return Version.
 */
const char *pv_porcupine_version(void);

/**
 * Getter for length (number of audio samples) per frame.
 *
 * @return frame length.
 */
int pv_porcupine_frame_length(void);

#endif // PV_PORCUPINE_H
