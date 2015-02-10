// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "OptionsViewModule.h"
#include "Options.h"
#include "OptionsView.h"
#include "OptionsController.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace View
        {
        	OptionsViewModule::OptionsViewModule(
                AndroidNativeState& nativeState,
                IOptionsViewModel& optionsViewModel,
                Eegeo::Android::Cache::AndroidHttpCache& httpCache,
                ExampleAppMessaging::TMessageBus& messageBus
            )
            {
                ASSERT_UI_THREAD

                m_pView = Eegeo_NEW(OptionsView)(nativeState);
                m_pController = Eegeo_NEW(OptionsController)(*m_pView, optionsViewModel, messageBus);
                m_pClearCacheMessageHandler = Eegeo_NEW(SdkModel::ClearCacheMessageHandler)(httpCache, messageBus);
            }

        	OptionsViewModule::~OptionsViewModule()
            {
                ASSERT_UI_THREAD

                Eegeo_DELETE(m_pClearCacheMessageHandler);
                Eegeo_DELETE(m_pController);
                Eegeo_DELETE(m_pView);
            }

        	OptionsController& OptionsViewModule::GetOptionsController() const
            {
                ASSERT_UI_THREAD

                return *m_pController;
            }

        	OptionsView& OptionsViewModule::GetOptionsView() const
            {
                ASSERT_UI_THREAD

                return *m_pView;
            }
        }
    }
}
