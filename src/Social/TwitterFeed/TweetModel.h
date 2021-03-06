// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <vector>
#include "document.h"
#include "LatLongAltitude.h"

namespace ExampleApp
{
    namespace Social
    {
        namespace TwitterFeed
        {
            class TweetModel
            {
            public:
                struct LinkEntity
                {
                    int startIndex;
                    int endIndex;
                    std::string httpAddress;
                    std::string deeplinkAddress;
                    
                    LinkEntity(int _startIndex, int _endIndex, const std::string& _deeplinkAddress, const std::string& _httpAddress)
                    : startIndex(_startIndex)
                    , endIndex(_endIndex)
                    , deeplinkAddress(_deeplinkAddress)
                    , httpAddress(_httpAddress)
                    {
                        
                    }
                };
            private:
                std::string m_tweetId;
                std::string m_text;
                std::string m_userName;
                std::string m_baseUserName;
                std::string m_userScreenName;
                std::string m_baseUserScreenName;
                std::string m_userId;
                std::string m_bannerImageUrl;
                std::string m_profileImageUrl;
                std::string m_baseProfileImageUrl;
                std::string m_profileImageThumbUrl;
                std::string m_baseProfileImageThumbUrl;
                bool m_isRetweet;
                bool m_isReply;
                std::vector<std::string> m_mediaUrls;
                std::string m_expandedMediaUrl;
                bool m_hasAttachedVideo;
                std::vector<LinkEntity> m_linkEntities;
                int m_retweetCount;
                int m_favoriteCount;
                std::string m_createdAt;
                std::string m_placeName;
                std::string m_profileColor;
                int m_mediaIndex;
                bool m_doesLinkOut;
                bool m_hasCoordinates;
                Eegeo::Space::LatLong m_coordinates;
            public:
                TweetModel(const std::string& tweetId,
                           const std::string& text,
                           const std::string& userName,
                           const std::string& baseUserName,
                           const std::string& userScreenName,
                           const std::string& baseUserScreenName,
                           const std::string& userId,
                           const std::string& bannerImageUrl,
                           const std::string& profileImageUrl,
                           const std::string& baseProfileImageUrl,
                           const std::string& profileImageThumbUrl,
                           const std::string& baseProfileImageThumbUrl,
                           bool isRetweet,
                           bool isReply,
                           std::vector<std::string> mediaUrls,
                           std::string expandedMediaUrl,
                           bool hasAttachedVideo,
                           std::vector<LinkEntity> linkEntities,
                           int retweetCount,
                           int favoriteCount,
                           const std::string& createdAt,
                           const std::string& placeName,
                           const std::string& profileColor,
                           int mediaIndex,
                           bool hasCoordinates,
                           Eegeo::Space::LatLong coordinates);
                ~TweetModel();
                
                const std::string& GetTweetId() const;
                const std::string& GetText() const;
                const std::string& GetUserName() const;
                const std::string& GetBaseUserName() const;
                const std::string& GetUserScreenName() const;
                const std::string& GetBaseUserScreenName() const;
                const std::string& GetUserId() const;
                const std::string& GetBannerImageUrl() const;
                const std::string& GetProfileImageUrl() const;
                const std::string& GetBaseProfileImageUrl() const;
                const std::string& GetProfileImageThumbUrl() const;
                const std::string& GetBaseProfileImageThumbUrl() const;
                bool IsRetweet() const;
                bool IsReply() const;
                int GetRetweetCount() const;
                int GetFavouriteCount() const;
                const std::string& GetCreatedAt() const;
                const std::string& GetPlaceName() const;
                const std::string& GetProfileColor() const;
                const std::string& GetFirstAttachedImageUrl() const;
                const std::string& GetExpandedMediaUrl() const;
                const bool HasAttachedVideo() const;
                const std::vector<LinkEntity>& GetLinkEntities() const;
                const int GetMediaIndex() const;
                const bool GetDoesLinkOut() const;
                const bool HasCoordinates() const;
                const Eegeo::Space::LatLong& GetCoordinates() const;
                
                void SetDoesLinkOut(bool doesLinkOut);
                
                
                static TweetModel* GetNewTweetModelFromJsonDocument(rapidjson::Document& jsonDocument, unsigned int index);
                static void GetLatLongFromBoxCoordinates(rapidjson::Value& coordinates, Eegeo::Space::LatLong& out_latLong);
            };
            
            inline bool operator==(const TweetModel& lhs, const TweetModel& rhs)
            {
                return lhs.GetTweetId() == rhs.GetTweetId();
            }
            inline bool operator!=(const TweetModel& lhs, const TweetModel& rhs)
            {
                return !operator==(lhs,rhs);
            }
            inline bool operator< (const TweetModel& lhs, const TweetModel& rhs)
            {
                return lhs.GetTweetId() < rhs.GetTweetId();
            }
            inline bool operator> (const TweetModel& lhs, const TweetModel& rhs)
            {
                return  operator< (rhs,lhs);
            }
            inline bool operator<=(const TweetModel& lhs, const TweetModel& rhs)
            {
                return !operator> (lhs,rhs);
            }
            inline bool operator>=(const TweetModel& lhs, const TweetModel& rhs)
            {
                return !operator< (lhs,rhs);
            }
        }
    }
}