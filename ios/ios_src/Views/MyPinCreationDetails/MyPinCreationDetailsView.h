// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "MyPinCreationDetailsViewController.h"

@class MyPinCreationDetailsView;

@interface MyPinCreationDetailsView : UIView <UINavigationControllerDelegate, UIImagePickerControllerDelegate, UITextViewDelegate, UITextFieldDelegate, UIPopoverControllerDelegate>
{
    __weak MyPinCreationDetailsViewController* m_pController;
    float m_stateChangeAnimationTimeSeconds;
    
    BOOL m_imageAttached;
    float m_maxImageWidth;

    BOOL m_usePopover;
    float m_popoverX;
    float m_popoverY;

    float m_controlContainerWidth;
    float m_controlContainerHeight;
    float m_yCursor;
    
    float m_scrollContentBottomMargin;
    
    BOOL m_hasNetworkConnectivity;
}

- (id) initWithController:(MyPinCreationDetailsViewController *)controller
   andNetworkConnectivity:(BOOL) hasConnectivity;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) setFullyActive;

- (void) setFullyInactive;

- (void) setActiveStateToIntermediateValue:(float)activeState;

- (void) addDoneToolBarToKeyboard:(UITextView *)textView;

- (void) resizeImageViewToFit:(CGFloat)sourceImageWidth :(CGFloat)sourceImageHeight;

- (void) setHasNetworkConnectivity:(BOOL) hasNetworkConnectivity
                                  :(BOOL) shouldVerifyShareSettings;

@property (nonatomic, retain) UIView* pControlContainer;

@property (nonatomic, retain) UIView* pTitleContainer;
@property (nonatomic, retain) UIImageView* pTitleImage;
@property (nonatomic, retain) UITextField* pTitleText;

@property (nonatomic, retain) UIView* pBodyContainer;
@property (nonatomic, retain) UIScrollView* pBodyScrollView;
@property (nonatomic, retain) UITextView* pPoiDescriptionBox;
@property (nonatomic, retain) UILabel* pDescriptionPlaceholder;
@property (nonatomic, retain) UIImage* pPlaceholderImage;
@property (nonatomic, retain) UIImageView* pPoiImage;
@property (nonatomic, retain) UIButton* pCheckbox;
@property (nonatomic, retain) UILabel* pShareLabel;
@property (nonatomic, retain) UILabel* pTermsLabel;

@property (nonatomic, retain) UIView* pFooterContainer;
@property (nonatomic, retain) UIButton* pCloseButton;
@property (nonatomic, retain) UIButton* pCameraButton;
@property (nonatomic, retain) UIButton* pGalleryButton;
@property (nonatomic, retain) UIButton* pConfirmButton;

@property (nonatomic, retain) UIImageView* pBodyShadow;
@property (nonatomic, retain) UIImageView* pFooterShadow;

@property (nonatomic, retain) UIPopoverController* pPopover;

@end
