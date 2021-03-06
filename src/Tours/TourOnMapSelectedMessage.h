// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "TourModel.h"

namespace ExampleApp
{
    namespace Tours
    {
        class TourOnMapSelectedMessage
        {
            SdkModel::TourModel m_tourModel;
            int m_initialCard;
            bool m_showBackButton;
            
        public:
            TourOnMapSelectedMessage(const SdkModel::TourModel& tourModel, const int initialCard, bool showBackButton);
            
            const SdkModel::TourModel& GetTourModel() const;
            const int GetInitialCard() const;
            bool GetShowBackButton() const;
        };
    }
}
