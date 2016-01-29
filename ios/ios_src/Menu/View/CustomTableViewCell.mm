// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CustomTableViewCell.h"
#include "UIColors.h"
#include "ImageHelpers.h"

@implementation CustomTableViewCell
{
    UIView* pCustomSeparatorContainer;
    bool m_hasSetBackground;
    bool m_hasSetSeparators;
    bool m_highlighted;
    bool m_requiresRefresh;
    bool m_customContentFramesSet;
    bool m_turingHighlightOff;
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    if([self canInteract])
    {
        [self makeHighlighted:YES animated:NO];
    }
}

- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [[event allTouches] anyObject];
    CGPoint touchLocation = [touch locationInView:self];
    if(CGRectContainsPoint(self.bounds, touchLocation) && [self canInteract])
    {
        [self makeHighlighted:YES animated:NO];
    }
    else
    {
        [self makeHighlighted:NO animated:NO];
    }
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [[event allTouches] anyObject];
    CGPoint touchLocation = [touch locationInView:self];
    
    [self makeHighlighted:NO animated:YES];
    if(CGRectContainsPoint(self.bounds, touchLocation) && [self canInteract])
    {
        [self->m_tableDataProvider tableView:self->m_tableView didSelectRowAtIndexPath:[NSIndexPath indexPathForRow:self->m_row inSection:self->m_section]];
    }
    
}

- (void)touchesCancelled:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    [self makeHighlighted:NO animated:NO];
}

-(void) lazySetBackgroundPresentation
{
    if(m_hasSetBackground && !m_tableView.hasDynamicCellPresentation)
    {
        return;
    }
    
    [self setBackgroundPresentation];
}

-(void) setBackgroundPresentation
{
    self.backgroundColor = m_pBackgroundColor;
    if(!m_turingHighlightOff)
    {
        [self.contentView setBackgroundColor:(m_highlighted ? m_pPressColor : m_pContentBackgroundColor)];
    }
    m_hasSetBackground = true;
}

-(bool) requiresVisualRefresh
{
    return !m_hasSetBackground || !m_hasSetSeparators || m_tableView.hasDynamicCellPresentation || m_requiresRefresh;
}

- (CGRect)getContentViewRect
{
    return CGRectMake(m_leftInset,
                      0.0f,
                      m_initialWidth,
                      self.frame.size.height - 1.0f);
}

- (void)layoutSubviews
{
    if([self requiresVisualRefresh])
    {
        m_requiresRefresh = false;
        [super layoutSubviews];
    }
    
    [self setClipsToBounds:YES];
    
    self->pCustomSeparatorContainer.frame = [self getContentViewRect];
    
    [self.contentView setClipsToBounds:YES];
    self.contentView.frame = [self getContentViewRect];
    
    if(m_customContentFramesSet)
    {
        self.imageView.frame = m_imageFrame;
        self.textLabel.frame = m_textFrame;
        self.detailTextLabel.frame = m_detailTextFrame;
    }
    
    [self insertSeparators :[self getContentViewRect]];
    [self lazySetBackgroundPresentation];
}

- (void)initCell:(CGFloat)initialWidth
                :(CGFloat)leftInset
                :(NSIndexPath*)indexPath
                :(CustomTableView*)tableView
                :(UITableViewController<UITableViewDelegate>*)tableDataProvider
{
    m_initialWidth = initialWidth;
    m_leftInset = leftInset;
    m_tableView = tableView;
    m_tableDataProvider = tableDataProvider;
    m_hasSetBackground = false;
    m_hasSetSeparators = false;
    m_highlighted = false;
    m_turingHighlightOff = false;
    m_customContentFramesSet = false;
    m_row = indexPath.row;
    m_section = indexPath.section;
    self->pCustomSeparatorContainer = [[UIView alloc]  initWithFrame:CGRectMake(0,0,0,0)];
    [self addSubview:self->pCustomSeparatorContainer];
}

- (void)setContentFrames:(CGRect)imageFrame
                        :(CGRect)textFrame
                        :(CGRect)detailTextFrame
{
    m_imageFrame = imageFrame;
    m_textFrame = textFrame;
    m_detailTextFrame = detailTextFrame;
    
    m_customContentFramesSet = true;
}

- (void)setInfo :(bool)hasSeparator
                :(UIColor*)pBackgroundColor
                :(UIColor*)pContentBackgroundColor
                :(UIColor*)pPressColor
{
    m_hasSeparator = hasSeparator;
    m_pBackgroundColor = pBackgroundColor;
    m_pContentBackgroundColor = pContentBackgroundColor;
    m_pPressColor = pPressColor;
    m_requiresRefresh = true;
}

- (BOOL)canInteract
{
    if([m_tableView respondsToSelector:@selector(isAnimating)])
    {
        if([m_tableView isAnimating])
        {
            return false;
        }
    }

    return true;
}

- (void)makeHighlighted:(BOOL)highlighted animated:(BOOL)animated
{
    if(![self canInteract])
    {
        m_turingHighlightOff = false;
        [self.contentView setBackgroundColor:m_pContentBackgroundColor];
        return;
    }

    if (highlighted)
    {
        m_highlighted = true;
        m_turingHighlightOff = false;
        [self.contentView setBackgroundColor:m_pPressColor];
    }
    else
    {
        if(m_highlighted)
        {
            m_highlighted = false;
            if(animated)
            {
                m_turingHighlightOff = true;
                double delayInSeconds = 0.2;
                dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
                dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
                    if(m_turingHighlightOff)
                    {
                        m_turingHighlightOff = false;
                        [self.contentView setBackgroundColor:m_pContentBackgroundColor];
                    }
                });
            }
            else
            {
                [self.contentView setBackgroundColor:m_pContentBackgroundColor];
            }
        }
    }
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{

}

- (void)insertSeparators:(CGRect)cellFrame
{
    if(m_hasSetSeparators && !m_tableView.hasDynamicCellPresentation)
    {
        return;
    }
    
    m_hasSetSeparators = true;
    
    if([self->pCustomSeparatorContainer subviews] != nil) {
        for (UIView *subview in [self->pCustomSeparatorContainer subviews]) {
            [subview removeFromSuperview];
        }
    }
    
    if(m_hasSeparator)
    {
        CGFloat topSeparatorY       = 0.f;
        CGFloat separatorHeight     = (1.f / [UIScreen mainScreen].scale);
        CGFloat separatorWidth      = cellFrame.size.width;
        
        UIImageView* topSeparator = [[[UIImageView alloc] initWithFrame:CGRectMake(0.0f,
                                                                                   topSeparatorY,
                                                                                   separatorWidth,
                                                                                   separatorHeight)] autorelease];
        
        topSeparator.backgroundColor = ExampleApp::Helpers::ColorPalette::TableDividerColor;
        
        [self->pCustomSeparatorContainer addSubview: topSeparator];
    }
}

@end
