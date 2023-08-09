#pragma once
#include <cstdint>
#include <limits>
#include <memory>
#include <optional>
#include <vector>

#include <ltproto/peer2peer/capture_video_frame.pb.h>

#include <rtc/rtc.h>

namespace lt {

class VideoEncoder {
public:
    enum class Backend {
        Unknown,
        NvEnc,
        IntelMediaSDK,
        Amf,
    };

    enum class FrameType {
        IFrame,
        PFrame,
    };

    struct EncodedFrame : rtc::VideoFrame {
        bool is_black_frame = false;
        std::shared_ptr<uint8_t> internal_data;
    };

    struct InitParams {
        Backend backend = Backend::Unknown;
        std::optional<int64_t> luid;
        rtc::VideoCodecType codec_type = rtc::VideoCodecType::H264;
        uint32_t width = 0;
        uint32_t height = 0;
        uint32_t bitrate_bps = 0;

        bool validate() const;
    };

    struct ReconfigureParams {
        std::optional<uint32_t> bitrate_bps;
        std::optional<uint32_t> fps;
    };

    struct Ability {
        Backend backend;
        rtc::VideoCodecType codec_type;
    };

public:
    static std::unique_ptr<VideoEncoder> create(const InitParams& params);
    virtual ~VideoEncoder();
    virtual void reconfigure(const ReconfigureParams& params) = 0;
    EncodedFrame encode(std::shared_ptr<ltproto::peer2peer::CaptureVideoFrame> input_frame,
                        bool force_idr);

    static std::vector<Ability> check_encode_abilities(uint32_t width, uint32_t height);
    static std::vector<Ability> check_encode_abilities_with_luid(int64_t luid, uint32_t width,
                                                                 uint32_t height);

protected:
    VideoEncoder(void* d3d11_dev, void* d3d11_ctx);
    virtual EncodedFrame encode_one_frame(void* input_frame, bool force_idr) = 0;

private:
    void* d3d11_dev_ = nullptr;
    void* d3d11_ctx_ = nullptr;
    uint64_t frame_id_ = 0;
};

} // namespace lt