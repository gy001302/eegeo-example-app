// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiViewModule.h"
#include "SearchResultPoi.h"
#include "SearchResultPoiView.h"
#include "SearchResultPoiController.h"
#include "WindowsAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            SearchResultPoiViewModule::SearchResultPoiViewModule(
                WindowsNativeState& nativeState,
                ISearchResultPoiViewModel& searchResultPoiViewModel,
                ExampleAppMessaging::TMessageBus& messageBus,
                Metrics::IMetricsService& metricsService
            )
            {
                ASSERT_UI_THREAD
                m_pView = Eegeo_NEW(SearchResultPoiView)(nativeState);
                m_pController = Eegeo_NEW(SearchResultPoiController)(*m_pView, searchResultPoiViewModel, messageBus, metricsService);
            }

            SearchResultPoiViewModule::~SearchResultPoiViewModule()
            {
                ASSERT_UI_THREAD
                Eegeo_DELETE m_pController;
                Eegeo_DELETE m_pView;
            }

            SearchResultPoiView& SearchResultPoiViewModule::GetView() const
            {
                return *m_pView;
            }

            SearchResultPoiController& SearchResultPoiViewModule::GetController() const
            {
                return *m_pController;
            }
        }
    }
}
