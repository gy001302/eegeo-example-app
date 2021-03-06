// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace Tours
    {
        class TourActiveStateChangedMessage
        {
            int m_activeStateIndex;
            
        public:
            TourActiveStateChangedMessage(int activeStateIndex);
            
            int GetActiveStateIndex() const;
        };
    }
}
