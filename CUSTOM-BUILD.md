# Custom Muse Gadget build — Waveshare ESP32-S3-Touch-AMOLED-2.16

This repo holds Boss's customized Muse Gadget firmware for the
Waveshare ESP32-S3-Touch-AMOLED-2.16 desk gadget, plus the announcement
audio and images the gadget fetches and plays.

**Based on:** upstream `facebookincubator/muse-gadget-sdk`
(Apache-2.0). This snapshot is that SDK at the commit the 2.16 build
was made from, plus the customizations below.

## Customizations (vs. upstream)

- **`audio.play_url` command** (`esp32/main/app.c`,
  `esp32/main/noise_control.cpp`): download an MP3 from a URL and play
  it through the speaker. For announcements and pre-rendered audio —
  gadget replies themselves are text-only by design (the backend does
  not send TTS audio for gadget replies, and the firmware paces
  silence to the text length). `audio.play_url` is the announcement
  path: Secundo generates the MP3, pushes it here, and invokes the
  command on the gadget.
- **HTTPS fetch for audio** (`esp32/main/app.c`): the audio fetcher
  attaches the ESP-IDF certificate bundle
  (`.crt_bundle_attach = esp_crt_bundle_attach`), mirroring
  `image_fetch.c`, so `audio.play_url` works over https — including
  raw.githubusercontent.com URLs from this repo. Without it, https
  handshakes fail and only plain http works.

## Announcement hosting

- **`announcements/`** — MP3s the gadget plays via `audio.play_url`.
  Pushed here (approval-free, via the PAT-backed GitHub CLI), then
  fetched by the gadget over https from
  `https://raw.githubusercontent.com/realtechnick/muse-gadget-esp32-s3/main/announcements/<file>.mp3`.
- **`images/`** — images the gadget shows via `display.draw_url`,
  same pattern.

## Build

Same as upstream for the 2.16 board (ESP-IDF v6.0.1):

```sh
cd esp32
tools/muse/board.sh build s3-216
```

The build needs an SDK token (`CONFIG_GADGET_SDK_TOKEN`) — **never
commit one**. Tokens live only in the local build dir's sdkconfig
(gitignored) and in the flashed binary.

## Notes

- The gadget is paired to one Muse account at a time. Pairing lives
  in NVS, so reflashing does not unpair it.
- The `esp32/build-muse-waveshare-s3-216/` build directory is
  gitignored and is not in this repo.
