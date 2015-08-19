//
//  ObjectAttributeTableController.h
//  EmptyPanel
//
//  Created by xcorex on 7/23/15.
//
//

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#import "ObjectAttribute.h"

@interface ObjectAttributeTableController : NSObject <NSTableViewDataSource>
{
    @private
    IBOutlet NSTableView *tableView;
    NSMutableArray *list;
}


- (IBAction)get:(id)sender;


@end
