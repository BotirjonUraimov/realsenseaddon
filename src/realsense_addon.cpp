#include <napi.h>
#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API

rs2::pipeline p;
rs2::config cfg;

Napi::Value Init(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    try {
        cfg.enable_stream(RS2_STREAM_DEPTH); // Enable depth stream
        cfg.enable_stream(RS2_STREAM_COLOR); // Enable color stream
        p.start(cfg); // Start pipeline with the configuration
        return Napi::String::New(env, "Camera initialized");
    } catch (const rs2::error & e) {
        Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
        return env.Null();
    }
}

Napi::Value CaptureDepthImage(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    try {
        rs2::frameset frames = p.wait_for_frames(); // Wait for next set of frames
        rs2::depth_frame depth = frames.get_depth_frame(); // Get depth frame
        // Process depth frame data...
        return Napi::String::New(env, "Depth image captured");
    } catch (const rs2::error & e) {
        Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
        return env.Null();
    }
}

Napi::Value CaptureRGBImage(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    try {
        rs2::frameset frames = p.wait_for_frames();
        rs2::frame color = frames.get_color_frame();
        // Process color frame data...
        return Napi::String::New(env, "RGB image captured");
    } catch (const rs2::error & e) {
        Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
        return env.Null();
    }
}


Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "init"), Napi::Function::New(env, Init));
    exports.Set(Napi::String::New(env, "captureDepthImage"), Napi::Function::New(env, CaptureDepthImage));
    exports.Set(Napi::String::New(env, "captureRGBImage"), Napi::Function::New(env, CaptureRGBImage));
    return exports;
}

NODE_API_MODULE(realsense_addon, InitAll)
