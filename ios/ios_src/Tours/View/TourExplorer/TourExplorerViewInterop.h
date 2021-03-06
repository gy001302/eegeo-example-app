// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ITourExplorerView.h"
#include "TourExplorerViewIncludes.h"
#include "ICallback.h"
#include "CallbackCollection.h"
#include "TourModel.h"
#include "TourWebViewIncludes.h"
#include "URLRequestHandler.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourExplorer
            {
                class TourExplorerViewInterop : public ITourExplorerView
                {
                public:
                    TourExplorerViewInterop(TourExplorerView* pView,
                                            URLRequest::View::URLRequestHandler& urlRequestHandler);
                    
                    void SetCurrentTour(const SdkModel::TourModel& tourModel, int initialCard, bool showBackButton);
                    
                    void OnDismissed();
                    void OnExited();
                    void OnStateSelected(int activeStateIndex);
                    void OnChangeTourRequested(const std::string& name);
                    void ShowExternalURL(const std::string& url);
                    void ShowDeeplinkURL(const std::string& deeplinkUrl, const std::string& httpFallbackUrl);
                    bool CanHandleDeeplinkURL(const std::string& deeplinkUrl);
                    
                    void OnCurrentTourCardTapped();
                    
                    void InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback);
                    void RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback);
                    void InsertExitedCallback(Eegeo::Helpers::ICallback0& callback);
                    void RemoveExitedCallback(Eegeo::Helpers::ICallback0& callback);
                    void InsertStateChangedCallback(Eegeo::Helpers::ICallback1<int>& callback);
                    void RemoveStateChangedCallback(Eegeo::Helpers::ICallback1<int>& callback);
                    void InsertChangeTourRequestCallback(Eegeo::Helpers::ICallback1<std::string>& callback);
                    void RemoveChangeTourRequestCallback(Eegeo::Helpers::ICallback1<std::string>& callback);
                    
                    void SetOnScreenStateToIntermediateValue(float value);
                    void SetFullyOnScreen();
                    void SetFullyOffScreen();
                    
                    const SdkModel::TourModel& GetCurrentTour();
                    
                    void InsertCurrentTourCardTappedCallback(Eegeo::Helpers::ICallback0& callback);
                    void RemoveCurrentTourCardTappedCallback(Eegeo::Helpers::ICallback0& callback);
                    
                private:
                    Eegeo::Helpers::CallbackCollection1<int> m_stateChangedCallbacks;
                    Eegeo::Helpers::CallbackCollection0 m_dismissedCallbacks;
                    Eegeo::Helpers::CallbackCollection0 m_exitedCallbacks;
                    Eegeo::Helpers::CallbackCollection1<std::string> m_changeTourCallbacks;
                    Eegeo::Helpers::CallbackCollection0 m_currentTourCardTappedCallbacks;
                    
                    TourExplorerView* m_pView;
                    URLRequest::View::URLRequestHandler& m_urlRequestHandler;
                    SdkModel::TourModel m_tourModel;
                };
            }
        }
    }
}
