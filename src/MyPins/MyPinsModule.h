// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IMyPinsModule.h"
#include "MyPins.h"
#include "Pins.h"
#include "WorldPins.h"
#include "PersistentSettings.h"
#include "Modules.h"

namespace ExampleApp
{
    namespace MyPins
    {
        class MyPinsModule : public IMyPinsModule
        {
        public:
            MyPinsModule(Eegeo::Pins::PinRepository& pinRepository,
                         WorldPins::IWorldPinsFactory& pinFactory,
                         Eegeo::Modules::IPlatformAbstractionModule& platformAbstractions,
                         PersistentSettings::IPersistentSettingsModel& persistentSettings);
            
            ~MyPinsModule();
            
            IMyPinsService& GetMyPinsService() const;
            
        private:
            MyPinsRepository* m_pMyPinsRepository;
            MyPinsFileIO* m_pMyPinsFileIO;
            MyPinsService* m_pMyPinsService;
        };
    }
}