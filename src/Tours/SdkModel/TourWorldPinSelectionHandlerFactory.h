// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Tours.h"
#include "WorldPins.h"
#include "BidirectionalBus.h"
#include "Types.h"
#include "Search.h"
#include "AppModes.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            class TourWorldPinSelectionHandlerFactory : private Eegeo::NonCopyable
            {
                ITourService& m_tourService;
                AppModes::SdkModel::IAppModeModel& m_appModeModel;
                
            public:
                TourWorldPinSelectionHandlerFactory(ITourService& tourService,
                                                    AppModes::SdkModel::IAppModeModel& appModeModel);
                
                ExampleApp::WorldPins::SdkModel::IWorldPinSelectionHandler* CreateSelectionHandler(TourModel& model);
            };
        }
    }
}
