﻿using ExampleApp;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Shapes;

namespace ExampleAppWPF
{
    public abstract class MenuView : Control
    {
        protected ControlClickHandler m_dragTabClickHandler = null;

        protected ListBox m_list = null;
        protected Button m_menuIcon;
        protected bool m_loggingEnabled = false;

        protected IntPtr m_nativeCallerPointer;

        protected double m_animationTimeMilliseconds = 200;

        protected Grid m_menuIconGrid;
        protected Grid m_menuViewContainer;
        protected Grid m_mainContainer;

        protected Storyboard m_openSearchIconAnim;
        protected Storyboard m_closeSearchIconAnim;

        protected Storyboard m_openSearchContainerAnim;
        protected Storyboard m_closeSearchContainerAnim;

        protected Storyboard m_openBackgroundRect;
        protected Storyboard m_closeBackgroundRect;
        protected Rectangle m_backgroundRectangle;

        protected MainWindow m_mainWindow;

        protected bool m_isAnimating;
        protected bool m_isOffScreen;
        protected float m_openState;

        protected const float MENU_CLOSED = 0.0f;
        protected const float MENU_OFFSCREEN = 0.0f;
        protected const float MENU_OPEN = 1.0f;
        protected const float MENU_CLOSING = 0.4f;
        protected const float MENU_OPENING = 0.5f;
        protected const float MENU_OFFSCREENING = 0.6f;

        private Action<object, EventArgs> m_animationCompleteCallback;

        protected abstract void RefreshListData(List<string> groups, List<bool> groupsExpandable, Dictionary<string, List<string>> groupToChildrenMap);

        static MenuView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(MenuView), new FrameworkPropertyMetadata(typeof(MenuView)));
        }

        public MenuView(IntPtr nativeCallerPointer)
        {
            m_nativeCallerPointer = nativeCallerPointer;

            m_mainWindow = (MainWindow)Application.Current.MainWindow;

            m_openState = -1.0f;
            m_isAnimating = false;
            m_isOffScreen = true;
        }

        protected void SetAnimationCompleteCallback(Action<object, EventArgs> callback)
        {
            m_animationCompleteCallback = callback;
        }
        
        public override void OnApplyTemplate()
        {
            base.OnApplyTemplate();
        }

        protected void OnDragTabMouseClick(object sender, MouseButtonEventArgs e)
        {
            if(IsAnimating())
            {
                return;
            }

            MenuViewCLIMethods.ViewClicked(m_nativeCallerPointer);
        }

        protected void OnDragTabMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            e.Handled = true;
        }

        protected void OnDragTabMouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            e.Handled = false;
        }

        public void Destroy()
        {
            m_mainWindow.MainGrid.Children.Remove(this);
        }

        public virtual bool IsAnimating()
        {
            return m_isAnimating;
        }

        public virtual void UpdateAnimation(float deltaSeconds)
        {
            
        }

        void AnimateToCurrentPos(bool animationCompleteAndOpen)
        {
            m_list.IsHitTestVisible = animationCompleteAndOpen;
        }

        public virtual float NormalisedAnimationProgress()
        {
            return m_openState;
        }

        private void OnAnimCompleted(object sender, EventArgs e)
        {
            m_isAnimating = false;

            if (m_openState == MENU_CLOSING)
            {
                m_closeSearchIconAnim.Completed -= OnAnimCompleted;

                m_openState = 0.0f;

                MenuViewCLIMethods.ViewCloseCompleted(m_nativeCallerPointer);
                m_isOffScreen = false;
            }
            else if (m_openState == MENU_OPENING)
            {
                m_openSearchIconAnim.Completed -= OnAnimCompleted;
                m_openState = 1.0f;

                MenuViewCLIMethods.ViewOpenCompleted(m_nativeCallerPointer);

                m_isOffScreen = false;
            }
            else if (m_openState == MENU_OFFSCREENING)
            {
                MenuViewCLIMethods.ViewCloseCompleted(m_nativeCallerPointer);
                m_openState = 0.0f;
            }

            if (m_animationCompleteCallback != null)
            {
                m_animationCompleteCallback(sender, e);
            }
        }

        public virtual void AnimateToClosedOnScreen()
        {
            if (m_openState == MENU_CLOSED)
                return;

            m_closeSearchIconAnim.Completed += OnAnimCompleted;
            m_closeSearchIconAnim.Begin(m_menuIconGrid);
            m_closeSearchContainerAnim.Begin(m_mainContainer);
            m_closeBackgroundRect.Begin(m_backgroundRectangle);

            m_openState = MENU_CLOSING;
            m_isAnimating = true;

            if (m_isOffScreen)
            {
                var mainGrid = (Application.Current.MainWindow as MainWindow).MainGrid;

                var screenWidth = mainGrid.ActualWidth;
                var totalWidth = m_mainContainer.ActualWidth + m_menuIcon.ActualWidth;

                var db = new DoubleAnimation(-(screenWidth / 2), TimeSpan.FromMilliseconds(200));
                m_menuViewContainer.RenderTransform.BeginAnimation(TranslateTransform.XProperty, db);

                m_isOffScreen = true;
            }
        }

        public virtual void AnimateToOpenOnScreen()
        {
            if (m_openState == MENU_OPEN)
                return;

            m_openSearchIconAnim.Completed += OnAnimCompleted;
            m_openSearchIconAnim.Begin(m_menuIconGrid);
            m_openSearchContainerAnim.Begin(m_mainContainer);
            m_openBackgroundRect.Begin(m_backgroundRectangle);

            m_isAnimating = true;

            m_openState = MENU_OPENING;
        }

        public virtual void AnimateOffScreen()
        {
            Dispatcher.Invoke(() =>
            {
                var mainGrid = (Application.Current.MainWindow as MainWindow).MainGrid;

                var screenWidth = mainGrid.ActualWidth;
                var totalWidth = m_mainContainer.ActualWidth + m_menuIcon.ActualWidth;

                m_openState = MENU_OFFSCREENING;

                var db = new DoubleAnimation(-(screenWidth / 2) - (totalWidth / 2), TimeSpan.FromMilliseconds(m_animationTimeMilliseconds));
                db.Completed += OnAnimCompleted;
                m_menuViewContainer.RenderTransform.BeginAnimation(TranslateTransform.XProperty, db);

                m_isOffScreen = true;
            });
        }

        public void AnimateToIntermediateOnScreenState(float onScreenState)
        {
            if (IsAnimating())
            {
                return;
            }
        }

        public void AnimateToIntermediateOpenState(float openState)
        {
            if (IsAnimating())
            {
                return;
            }
        }

        public void PopulateData(
            IntPtr nativeCallerPointer,
            string[] groupNames,
            int[] groupSizes,
            bool[] groupIsExpandable,
            string[] childJson)
        {
            List<string> groups = groupNames.ToList();
            List<bool> groupsExpandable = groupIsExpandable.ToList();
            Dictionary<string, List<string>> childMap = new Dictionary<string, List<string>>();
            int childIndex = 0;
            for (int groupIndex = 0; groupIndex < groups.Count; groupIndex++)
            {
                int size = groupSizes[groupIndex];
                List<string> children = new List<string>();
                for (int i = 0; i < size; i++)
                {
                    children.Add(childJson[childIndex]);
                    childIndex++;
                }

                childMap[groupNames[groupIndex]] = children;
            }

            RefreshListData(groups, groupsExpandable, childMap);
        }

        protected bool StartedClosed(double controlStartPosXDip)
        {
            return false;
        }

        protected bool CanInteract()
        {
            return IsClosed() || IsOpen();
        }

        protected bool IsClosed()
        {
            return m_openState == MENU_CLOSED;
        }

        protected bool IsOpen()
        {
            return m_openState == MENU_OPEN;
        }
    }
}
