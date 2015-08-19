//========================================================================================
//  
//  $File: $
//
//  $Revision: $
//
//  Copyright 1987 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#import <Cocoa/Cocoa.h>

#include "EmptyPanelPluginSuites.h"
#include "AppContext.hpp"
#include "IText.h"
#include "AIPDFFormatAction.h"
#include "AISVGAction.h"

#include "ObjectAttribute.h"
#include "AIEntry.h"

#include "ObjectAttributeController.h"

struct Opaque;


@interface CalcController :  NSViewController <NSTableViewDataSource>
{
	IBOutlet NSButton *addButton;
	IBOutlet NSButton *getButton;
	IBOutlet NSTextField *value1;
	IBOutlet NSTextField *value2;
	IBOutlet NSTextField *output;
    
    IBOutlet NSTableView *tableView;
    NSMutableArray *list;
    
    SPPluginRef context;
}


@property SPPluginRef ctx;
@property  int wew;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil ctx:(SPPluginRef)ctx_;
- (IBAction)add:(id)sender;

- (IBAction)get:(id)sender;


- (void)setContext:(SPPluginRef) input;


- (void) awakeFromNib;

@end
