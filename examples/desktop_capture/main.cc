#include "examples/desktop_capture/desktop_capture.h"
#include "test/video_renderer.h"
#include "rtc_base/logging.h"
#include "examples/desktop_capture/video_encode_handler.h"

#include <thread>

int main() {
  std::unique_ptr<webrtc_demo::DesktopCapture> capturer(webrtc_demo::DesktopCapture::Create(30,0));

  capturer->StartCapture();

  std::unique_ptr<webrtc::test::VideoRenderer> renderer(webrtc::test::VideoRenderer::Create(capturer->GetWindowTitle().c_str(), 720, 480));
  capturer->AddOrUpdateSink(renderer.get(), rtc::VideoSinkWants());

  std::unique_ptr<webrtc_demo::VideoEncodeHandler> video_encode(webrtc_demo::VideoEncodeHandler::Create(webrtc_demo::VideoEncodeHandler::VideoEncodeType::VP8));
  capturer->AddOrUpdateSink(video_encode.get(), rtc::VideoSinkWants());

  std::this_thread::sleep_for(std::chrono::seconds(30));
  capturer->RemoveSink(renderer.get());
  capturer->RemoveSink(video_encode.get());

  RTC_LOG(WARNING) << "Demo exit";
  return 0;
}