//========================================================================================
//  
//  $File: $
//
//  $Revision: $
//
//  Copyright 2012 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================


#import "BarController.h"

@implementation BarController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) 
	{
    }
    
    return self;
}

- (IBAction)move:(id)sender
{
	int xIn = [x intValue];
	int yIn = [y intValue];
	AIPoint point = {xIn,yIn};
	sAIControlBar->Move(fControlBar,point);
    
    if (ctx)
    {
        sAIUser->MessageAlert(ai::UnicodeString("sses"));
    }
    
    AppContext _context(ctx);
    
    
    AIDictionaryRef dict = NULL;
    
    AIErr error = sAIDocument->GetDictionary(&dict);
    
    if (error) {
        sAIUser->MessageAlert(ai::UnicodeString("error"));
        
    }
    
    if (dict == NULL) {
        sAIUser->MessageAlert(ai::UnicodeString("wew"));
    }else{
        sAIUser->MessageAlert(ai::UnicodeString("wowza"));
    }
    
    const char* stringvalue = "Sample Persistance data.";
    
    std::string sKey("SP");
    
    AIDictKey fStringKey = sAIDictionary->Key(sKey.c_str());
    sAIDictionary->SetStringEntry(dict,fStringKey,stringvalue);
    
    sAIDictionary->Release( dict );
    
}

- (IBAction)get:(id)sender
{
	AIReal width, minWidth, maxWidth;
	sAIControlBar->GetWidth(fControlBar,width);
	sAIControlBar->GetMinimumWidth(fControlBar,minWidth);
	sAIControlBar->GetMaximumWidth(fControlBar,maxWidth);
	[current_width setIntValue:width];
	[min_width setIntValue:minWidth];
	[max_width setIntValue:maxWidth];
}

- (IBAction)commit_min_width:(id)sender
{
	AIReal min = [min_width intValue];
	sAIControlBar->SetMinimumWidth(fControlBar,min);
}

- (IBAction)commit_max_width:(id)sender
{
	AIReal max = [max_width intValue];
	sAIControlBar->SetMaximumWidth(fControlBar,max);
}

- (IBAction)commit_current_width:(id)sender
{
	AIReal current = [current_width intValue];
	sAIControlBar->SetWidth(fControlBar,current);
}

- (void)setControlBarRef:(AIControlBarRef)input
{
	fControlBar = input;
}

- (void)setCtx:(SPPluginRef)input
{
    sAIUser->MessageAlert(ai::UnicodeString("set 6 msg"));
    
	ctx = input;
}

@end
