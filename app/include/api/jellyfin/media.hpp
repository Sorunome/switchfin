#pragma once

#include <nlohmann/json.hpp>

namespace jellyfin {

const std::string apiUserViews = "/Users/{}/Views";
const std::string apiUserLibrary = "/Users/{}/Items?{}";
const std::string apiUserItem = "/Users/{}/Items/{}";
const std::string apiShowSeanon = "/Shows/{}/Seasons?{}";
const std::string apiShowEpisodes = "/Shows/{}/Episodes?{}";
const std::string apiPrimaryImage = "/Items/{}/Images/Primary?{}";
const std::string apiLogoImage = "/Items/{}/Images/Logo?{}";
const std::string apiPlayback = "/Items/{}/PlaybackInfo";
const std::string apiStream = "/Videos/{}/stream?{}";

const std::string imageTypePrimary = "Primary";
const std::string imageTypeLogo = "Logo";

const std::string mediaTypeFolder = "Folder";
const std::string mediaTypeSeries = "Series";
const std::string mediaTypeSeason = "Season";
const std::string mediaTypeEpisode = "Episode";
const std::string mediaTypeMovie = "Movie";

const std::string streamTypeVideo = "Video";
const std::string streamTypeAudio = "Audio";
const std::string streamTypeSubtitle = "Subtitle";

struct MediaItem {
    std::string Id;
    std::string Name;
    std::string Type;
    std::map<std::string, std::string> ImageTags;
    bool IsFolder = false;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(MediaItem, Id, Name, Type, ImageTags, IsFolder);

struct MediaSeries : public MediaItem {
    long ProductionYear = 0;
    float CommunityRating = 0.0f;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(
    MediaSeries, Id, Name, Type, ImageTags, IsFolder, ProductionYear, CommunityRating);

struct MediaSeason : public MediaItem {
    long ProductionYear = 0;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(MediaSeason, Id, Name, Type, ImageTags, IsFolder, ProductionYear);

struct UserData {
    bool IsFavorite = false;
    int PlayCount = 0;
    time_t PlaybackPositionTicks = 0;
    bool Played = false;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(UserData, IsFavorite, PlayCount, PlaybackPositionTicks, Played);

struct MediaStream {
    std::string Codec;
    std::string DisplayTitle;
    std::string Type;
    long Index;
    bool IsDefault;
    bool IsExternal;
    std::string DeliveryUrl;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(MediaStream, Codec, DisplayTitle, Type, Index, IsDefault, IsExternal, DeliveryUrl);

struct MediaSource {
    std::string Id;
    std::string Name;
    std::string Container;
    int DefaultAudioStreamIndex;
    int DefaultSubtitleStreamIndex;
    std::string ETag;
    time_t RunTimeTicks;
    std::vector<MediaStream> MediaStreams;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(MediaSource, Id, Name, Container, DefaultAudioStreamIndex,
    DefaultSubtitleStreamIndex, ETag, RunTimeTicks, MediaStreams);

struct PlaybackResult {
    std::vector<MediaSource> MediaSources;
    std::string PlaySessionId;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PlaybackResult, MediaSources, PlaySessionId);

struct MediaEpisode : public MediaItem {
    std::string Overview;
    long IndexNumber;
    std::string SeriesPrimaryImageTag;
    std::vector<MediaSource> MediaSources;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(
    MediaEpisode, Id, Name, Type, ImageTags, IsFolder, Overview, IndexNumber, MediaSources, SeriesPrimaryImageTag);

template <typename T>
struct MediaQueryResult {
    std::vector<T> Items;
    long TotalRecordCount = 0;
    long StartIndex = 0;
};

template <typename T>
inline void to_json(nlohmann::json& nlohmann_json_j, const MediaQueryResult<T>& nlohmann_json_t) {
    NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(NLOHMANN_JSON_TO, Items, TotalRecordCount, StartIndex))
}

template <typename T>
inline void from_json(const nlohmann::json& nlohmann_json_j, MediaQueryResult<T>& nlohmann_json_t) {
    NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(NLOHMANN_JSON_FROM, Items, TotalRecordCount, StartIndex))
}

}  // namespace jellyfin