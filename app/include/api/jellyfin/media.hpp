#pragma once

#include <nlohmann/json.hpp>

namespace jellyfin {

const std::string apiUserViews = "/Users/{}/Views";
const std::string apiUserLibrary = "/Users/{}/Items?{}";
const std::string apiUserItem = "/Users/{}/Items/{}";
const std::string apiUserResume = "/Users/{}/Items/Resume?{}";
const std::string apiUserLatest = "/Users/{}/Items/Latest?{}";
const std::string apiShowNextUp = "/Shows/NextUp?{}";
const std::string apiShowSeanon = "/Shows/{}/Seasons?{}";
const std::string apiShowEpisodes = "/Shows/{}/Episodes?{}";
const std::string apiPrimaryImage = "/Items/{}/Images/Primary?{}";
const std::string apiLogoImage = "/Items/{}/Images/Logo?{}";

const std::string apiPlayback = "/Items/{}/PlaybackInfo";
const std::string apiStream = "/Videos/{}/stream?{}";
const std::string apiPlayStart = "/Sessions/Playing";
const std::string apiPlayStop = "/Sessions/Playing/Stopped";
const std::string apiPlaying = "/Sessions/Playing/Progress";

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

struct UserDataResult {
    bool IsFavorite = false;
    int PlayCount = 0;
    time_t PlaybackPositionTicks = 0;
    bool Played = false;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(UserDataResult, IsFavorite, PlayCount, PlaybackPositionTicks, Played);

struct MediaItem {
    std::string Id;
    std::string Name;
    std::string Type;
    std::map<std::string, std::string> ImageTags;
    bool IsFolder = false;
    long ProductionYear = 0;
    float CommunityRating = 0.0f;
    UserDataResult UserData;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(
    MediaItem, Id, Name, Type, ImageTags, IsFolder, ProductionYear, CommunityRating, UserData);

struct MediaCollection : public MediaItem {
    std::string CollectionType;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(
    MediaCollection, Id, Name, Type, ImageTags, IsFolder, CollectionType);

struct MediaSeason : public MediaItem {
    long IndexNumber = 0;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(MediaSeason, Id, Name, Type, ImageTags, IsFolder, IndexNumber);

struct MediaAttachment {
    std::string Codec;
    std::string Name;
    long Index = 0;
    std::string DeliveryUrl;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(MediaAttachment, Codec, Name, Index, DeliveryUrl);

struct MediaStream {
    std::string Codec;
    std::string DisplayTitle;
    std::string Type;
    long Index = 0;
    bool IsDefault = false;
    bool IsExternal = false;
    std::string DeliveryUrl;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(
    MediaStream, Codec, DisplayTitle, Type, Index, IsDefault, IsExternal, DeliveryUrl);

struct MediaSource {
    std::string Id;
    std::string Name;
    std::string Container;
    int DefaultAudioStreamIndex;
    int DefaultSubtitleStreamIndex;
    bool SupportsDirectPlay;
    bool SupportsTranscoding;
    std::string TranscodingUrl;
    std::string ETag;
    std::vector<MediaStream> MediaStreams;
    std::vector<MediaAttachment> MediaAttachments;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(MediaSource, Id, Name, Container, DefaultAudioStreamIndex,
    DefaultSubtitleStreamIndex, SupportsDirectPlay, SupportsTranscoding, TranscodingUrl, ETag, MediaStreams,
    MediaAttachments);

struct PlaybackResult {
    std::vector<MediaSource> MediaSources;
    std::string PlaySessionId;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PlaybackResult, MediaSources, PlaySessionId);

struct MediaEpisode : public MediaSeason {
    int ParentIndexNumber = 0;
    std::string Overview;
    std::string SeriesId;
    std::string SeriesName;
    std::string SeriesPrimaryImageTag;
    std::vector<MediaSource> MediaSources;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(MediaEpisode, Id, Name, Type, ImageTags, IsFolder, ProductionYear,
    UserData, IndexNumber, ParentIndexNumber, Overview, SeriesId, SeriesName, SeriesPrimaryImageTag, MediaSources);

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