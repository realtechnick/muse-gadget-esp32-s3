/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <stdint.h>

// The harness drives the clock.
int64_t esp_timer_get_time(void);

// Minimal esp_timer fakes for the retry logic. The harness does not fire
// timers; tests that need the retry path drive it manually.
typedef void *esp_timer_handle_t;
typedef void (*esp_timer_cb_t)(void *arg);
typedef struct {
    esp_timer_cb_t callback;
    void *arg;
    const char *name;
} esp_timer_create_args_t;
int esp_timer_create(const esp_timer_create_args_t *args, esp_timer_handle_t *out);
int esp_timer_start_once(esp_timer_handle_t timer, uint64_t us);
int esp_timer_delete(esp_timer_handle_t timer);
